#include "../Config.h"

#include "Animations.h"
#include "Backtrack.h"

#include "../SDK/ConVar.h"
#include "../SDK/Entity.h"
#include "../SDK/FrameStage.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/NetworkChannel.h"
#include "../SDK/UserCmd.h"
#include "../SDK/Utils.h"

static std::deque<Backtrack::IncomingSequence> sequences;
float latencyRampup = 0.0f;

struct Cvars {
    ConVar* updateRate;
    ConVar* maxUpdateRate;
    ConVar* interp;
    ConVar* interpRatio;
    ConVar* minInterpRatio;
    ConVar* maxInterpRatio;
    ConVar* maxUnlag;
};

static Cvars cvars;

float Backtrack::getLerp() noexcept
{
    auto ratio = std::clamp(cvars.interpRatio->getFloat(), cvars.minInterpRatio->getFloat(), cvars.maxInterpRatio->getFloat());
    return (std::max)(cvars.interp->getFloat(), (ratio / ((cvars.maxUpdateRate) ? cvars.maxUpdateRate->getFloat() : cvars.updateRate->getFloat())));
}

float getLatency() noexcept
{
    return latencyRampup * std::clamp(static_cast<float>(config->backtrack.fakeLatencyAmount), 0.f, 800.f);
}

float Backtrack::getExtraTicks() noexcept
{
    if (!config->backtrack.fakeLatency || config->backtrack.fakeLatencyAmount <= 0)
        return 0.f;
    return getLatency() / 1000.f;
}

void Backtrack::run(UserCmd* cmd) noexcept
{
    if (!config->backtrack.enabled)
        return;

    if (!(cmd->buttons & UserCmd::IN_ATTACK))
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    auto localPlayerEyePosition = localPlayer->getEyePosition();

    auto bestFov{ 255.f };
    int bestTargetIndex{ };
    int bestRecord{ };

    for (int i = 1; i <= interfaces->engine->getMaxClients(); i++) {
        const auto player = Animations::getPlayer(i);
        if (!player.gotMatrix || player.backtrackRecords.empty())
            continue;

        auto entity = interfaces->entityList->getEntityFromHandle(player.handle);
        if (!entity || entity->isDormant() || !entity->isAlive()
            || !entity->isEnemy(localPlayer.get()))
            continue;

        for (int j = static_cast<int>(player.backtrackRecords.size() - 1); j >= 0; j--)
        {
            if (Backtrack::valid(player.backtrackRecords.at(j).simulationTime))
            {
                for (auto position : player.backtrackRecords.at(j).positions) {
                    auto angle = calculateRelativeAngle(localPlayerEyePosition, position, cmd->viewangles);
                    auto fov = std::hypotf(angle.x, angle.y);
                    if (fov < bestFov) {
                        bestFov = fov;
                        bestRecord = j;
                        bestTargetIndex = i;
                    }
                }
            }
        }
    }

    const auto player = Animations::getPlayer(bestTargetIndex);
    if (!player.gotMatrix)
        return;

    if (bestRecord) {
        const auto& record = player.backtrackRecords[bestRecord];
        cmd->tickCount = timeToTicks(record.simulationTime + getLerp());
    }
}

void Backtrack::updateLatency(NetworkChannel* network) noexcept
{
    for (auto& sequence : sequences)
    {
        if (memory->globalVars->serverTime() - sequence.currentTime >= (getLatency() / 1000.0f))
        {
            network->inReliableState = sequence.inReliableState;
            network->inSequenceNr = sequence.inSequenceNr;
            break;
        }
    }
}

static int lastIncomingSequenceNumber = 0;

void Backtrack::updateIncomingSequences() noexcept
{
    if (!localPlayer)
    {
        lastIncomingSequenceNumber = 0;
        sequences.clear();
        return;
    }

    const auto network = interfaces->engine->getNetworkChannel();
    if (!network)
    {
        lastIncomingSequenceNumber = 0;
        sequences.clear();
        return;
    }

    if (network->inSequenceNr > lastIncomingSequenceNumber)
    {
        lastIncomingSequenceNumber = network->inSequenceNr;

        IncomingSequence sequence{ };
        sequence.inReliableState = network->inReliableState;
        sequence.inSequenceNr = network->inSequenceNr;
        sequence.currentTime = memory->globalVars->serverTime();
        sequences.push_front(sequence);
    }

    while (sequences.size() > 2048)
        sequences.pop_back();
}

void Backtrack::updateRampUp() noexcept
{
    if (!localPlayer || !config->backtrack.fakeLatency)
    {
        latencyRampup = 0.0f;
        return;
    }

    const auto network = interfaces->engine->getNetworkChannel();
    if (!network)
        return;

    latencyRampup += memory->globalVars->intervalPerTick / 2.0f;
    latencyRampup = min(1.0f, latencyRampup);
}

bool Backtrack::valid(float simtime) noexcept
{
    const auto network = interfaces->engine->getNetworkChannel();
    if (!network)
        return false;

    const auto deadTime = static_cast<int>(memory->globalVars->serverTime() - cvars.maxUnlag->getFloat());
    if (simtime < deadTime)
        return false;

    const auto delta = std::clamp(network->getLatency(0) + network->getLatency(1) + getLerp(), 0.f, cvars.maxUnlag->getFloat()) 
        - (memory->globalVars->serverTime() - simtime);
    return std::abs(delta) <= 0.2f;
}

void Backtrack::init() noexcept
{
    cvars.updateRate = interfaces->cvar->findVar("cl_updaterate");
    cvars.maxUpdateRate = interfaces->cvar->findVar("sv_maxupdaterate");
    cvars.interp = interfaces->cvar->findVar("cl_interp");
    cvars.interpRatio = interfaces->cvar->findVar("cl_interp_ratio");
    cvars.minInterpRatio = interfaces->cvar->findVar("sv_client_min_interp_ratio");
    cvars.maxInterpRatio = interfaces->cvar->findVar("sv_client_max_interp_ratio");
    cvars.maxUnlag = interfaces->cvar->findVar("sv_maxunlag");
}

void Backtrack::reset() noexcept
{
    latencyRampup = 0.0f;
    lastIncomingSequenceNumber = 0;
    sequences.clear();
}

float Backtrack::getMaxUnlag() noexcept
{
    return cvars.maxUnlag->getFloat();
}
