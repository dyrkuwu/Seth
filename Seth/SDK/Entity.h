#pragma once

#include <functional>

#include "../Config.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../Netvars.h"

#include "ClientClass.h"
#include "CommandContext.h"
#include "Conditions.h"
#include "Cvar.h"
#include "Datamap.h"
#include "Engine.h"
#include "EngineTrace.h"
#include "EntityList.h"
#include "GlobalVars.h"
#include "LocalPlayer.h"
#include "matrix3x4.h"
#include "MDLCache.h"
#include "ModelRender.h"
#include "Utils.h"
#include "UtlVector.h"
#include "Vector.h"
#include "VirtualMethod.h"
#include "WeaponId.h"

struct AnimState;

struct AnimationLayer
{
public:
    float animationTime; //0
    float fadeOut; //4
    CStudioHdr* dispatchedStudioHdr; //8
    int dispatchedSrc; //12
    int dispatchedDst; //16
    unsigned int order; //20, networked
    unsigned int sequence; //24, networked
    float prevCycle; //28, networked
    float weight; //32, networked
    float weightDeltaRate; //36, networked
    float playbackRate; //40, networked
    float cycle; //44, networked
    void* owner; //48
    int invalidatePhysicsBits; //52

    void reset()
    {
        sequence = 0;
        weight = 0;
        weightDeltaRate = 0;
        playbackRate = 0;
        prevCycle = 0;
        cycle = 0;
    }
};

enum class MoveType {
    NONE = 0,
    ISOMETRIC,
    WALK,
    STEP,
    FLY,
    FLYGRAVITY,
    vPHYSICS,
    PUSH,
    NOCLIP,
    LADDER,
    OBSERVER,
    CUSTOM,

    LAST = CUSTOM,

    MAX_BITS = 4
};

enum class ObsMode {
    None = 0,
    Deathcam,
    Freezecam,
    Fixed,
    InEye,
    Chase,
    Roaming
};

enum class Team {
    None = 0,
    Spectators,
    BLU,
    RED
};

enum class TFClass {
    NONE = 0,
    SCOUT,
    SNIPER,
    SOLDIER,
    DEMOMAN,
    MEDIC,
    HEAVY,
    PYRO,
    SPY,
    ENGINEER
};

class Collideable {
public:
    VIRTUAL_METHOD(const Vector&, obbMins, 3, (), (this))
    VIRTUAL_METHOD(const Vector&, obbMaxs, 4, (), (this))
};

class Entity {
public:
    VIRTUAL_METHOD(void, release, 1, (), (this + sizeof(uintptr_t) * 2))
    VIRTUAL_METHOD(ClientClass*, getClientClass, 2, (), (this + sizeof(uintptr_t) * 2))
    VIRTUAL_METHOD(bool, isDormant, 8, (), (this + sizeof(uintptr_t) * 2))
    VIRTUAL_METHOD(int, index, 9, (), (this + sizeof(uintptr_t) * 2))

    VIRTUAL_METHOD(Vector&, getRenderOrigin, 1, (), (this + sizeof(uintptr_t)))
    VIRTUAL_METHOD(Vector&, getRenderAngles, 2, (), (this + sizeof(uintptr_t)))
    VIRTUAL_METHOD(bool, shouldDraw, 3, (), (this + sizeof(uintptr_t)))
    VIRTUAL_METHOD(const Model*, getModel, 9, (), (this + sizeof(uintptr_t)))
    VIRTUAL_METHOD(const matrix3x4&, toWorldTransform, 34, (), (this + sizeof(uintptr_t)))

    VIRTUAL_METHOD(int&, handle, 2, (), (this))
    VIRTUAL_METHOD(Collideable*, getCollideable, 3, (), (this))

    VIRTUAL_METHOD(const Vector&, getAbsOrigin, 9, (), (this))
    VIRTUAL_METHOD(Vector&, getAbsAngle, 10, (), (this))
    VIRTUAL_METHOD(int, getMaxHealth, 107, (), (this))


    VIRTUAL_METHOD(Vector&, bulletSpread, 286, (), (this))
    VIRTUAL_METHOD(int, slot, 330, (), (this))
    VIRTUAL_METHOD(const char*, getPrintName, 333, (), (this))
    VIRTUAL_METHOD(int, damageType, 340, (), (this))
    VIRTUAL_METHOD(WeaponId, weaponId, 381, (), (this))

    bool isPlayer() noexcept
    {
        return getClassId() == ClassId::TFPlayer;
    }

    bool isAlive() noexcept
    {
        return lifeState() == 0;
    }

    bool isOnGround() noexcept
    {
        return groundEntity() >= 0 || flags() & 1;
    }

    bool isEnemy(Entity* entity) noexcept
    {
        return entity->teamNumber() != teamNumber();
    }

    Entity* getActiveWeapon() noexcept
    {
        return reinterpret_cast<Entity*>(interfaces->entityList->getEntityFromHandle(activeWeapon()));
    }

    std::string getPlayerName() noexcept;

    Vector getEyePosition() noexcept
    {
        return viewOffset() + getAbsOrigin();
    }

    ClassId getClassId() noexcept
    {
        const auto clientClass = getClientClass();
        return clientClass ? clientClass->classId : ClassId(0);
    }

    UtlVector<matrix3x4>& getBoneCache() noexcept
    {
        return *reinterpret_cast<UtlVector<matrix3x4>*>(reinterpret_cast<uintptr_t>(this) + 0x848);
    }

    CONDITION(isCharging, condition(), TFCond_Charging)
    CONDITION(isScoped, condition(), TFCond_Zoomed)
    CONDITION(isUbered, condition(), TFCond_Ubercharged)
    CONDITION(isBonked, condition(), TFCond_Bonked)
    CONDITION(inMilk, condition(), TFCond_Milked)
    CONDITION(inJarate, condition(), TFCond_Jarated)
    CONDITION(isBleeding, condition(), TFCond_Bleeding)
    CONDITION(isDisguised, condition(), TFCond_Disguised)
    CONDITION(isCloaked, condition(), TFCond_Cloaked)
    CONDITION(isTaunting, condition(), TFCond_Taunting)
    CONDITION(isOnFire, condition(), TFCond_OnFire)
    CONDITION(isStunned, condition(), TFCond_Stunned)
    CONDITION(isSlowed, condition(), TFCond_Slowed)
    CONDITION(isMegaHealed, condition(), TFCond_MegaHeal)
    CONDITION(isAGhost, conditionEx2(), TFCondEx2_HalloweenGhostMode)
    CONDITION(isInBumperKart, conditionEx2(), TFCondEx_InKart)
    CONDITION(isPhlogUbered, conditionEx(), TFCondEx_PhlogUber)
    CONDITION(isBlastImmune, conditionEx2(), TFCondEx2_BlastImmune)
    CONDITION(isBulletImmune, conditionEx2(), TFCondEx2_BulletImmune)
    CONDITION(isFireImmune, conditionEx2(), TFCondEx2_FireImmune)
    CONDITION(hasStrengthRune, conditionEx2(), TFCondEx2_StrengthRune)
    CONDITION(hasHasteRune, conditionEx2(), TFCondEx2_HasteRune)
    CONDITION(hasRegenRune, conditionEx2(), TFCondEx2_RegenRune)
    CONDITION(hasResistRune, conditionEx2(), TFCondEx2_ResistRune)
    CONDITION(hasVampireRune, conditionEx2(), TFCondEx2_VampireRune)
    CONDITION(hasReflectRune, conditionEx2(), TFCondEx2_ReflectRune)
    CONDITION(hasPrecisionRune, conditionEx3(), TFCondEx3_PrecisionRune)
    CONDITION(hasAgilityRune, conditionEx3(), TFCondEx3_AgilityRune)
    CONDITION(hasKnockoutRune, conditionEx3(), TFCondEx3_KnockoutRune)
    CONDITION(hasImbalanceRune, conditionEx3(), TFCondEx3_ImbalanceRune)
    CONDITION(hasCritTempRune, conditionEx3(), TFCondEx3_CritboostedTempRune)
    CONDITION(hasKingRune, conditionEx3(), TFCondEx3_KingRune)
    CONDITION(hasPlagueRune, conditionEx3(), TFCondEx3_PlagueRune)
    CONDITION(hasSupernovaRune, conditionEx3(), TFCondEx3_SupernovaRune)
    CONDITION(hasBuffedByKing, conditionEx3(), TFCondEx3_KingBuff)
    CONDITION(hasBlastResist, conditionEx(), TFCondEx_ExplosiveCharge)
    CONDITION(hasBulletResist, conditionEx(), TFCondEx_BulletCharge)
    CONDITION(hasFireResist, conditionEx(), TFCondEx_FireCharge)

    NETVAR(body, "CBaseAnimating", "m_nBody", int)
    NETVAR(clientSideAnimation, "CBaseAnimating", "m_bClientSideAnimation", bool)
    NETVAR(hitboxSet, "CBaseAnimating", "m_nHitboxSet", int)
    NETVAR(sequence, "CBaseAnimating", "m_nSequence", int)

    NETVAR(modelIndex, "CBaseEntity", "m_nModelIndex", unsigned)
    NETVAR(origin, "CBaseEntity", "m_vecOrigin", Vector)
    NETVAR_OFFSET(moveType, "CBaseEntity", "m_nRenderMode", 1, MoveType)
    NETVAR(simulationTime, "CBaseEntity", "m_flSimulationTime", float)
    NETVAR(ownerEntity, "CBaseEntity", "m_hOwnerEntity", int)
    NETVAR(spotted, "CBaseEntity", "m_bSpotted", bool)
    NETVAR(lifeState, "CBasePlayer", "m_lifeState", unsigned char)
    NETVAR(teamNumber, "CBaseEntity", "m_iTeamNum", Team)

    NETVAR(condition, "CTFPlayer", "m_nPlayerCond", int)
    NETVAR(conditionEx, "CTFPlayer", "m_nPlayerCondEx", int)
    NETVAR(conditionEx2, "CTFPlayer", "m_nPlayerCondEx2", int)
    NETVAR(conditionEx3, "CTFPlayer", "m_nPlayerCondEx3", int)
    NETVAR(getPlayerClass, "CTFPlayer", "m_iClass", TFClass)

    NETVAR(weapons, "CBaseCombatCharacter", "m_hMyWeapons", int[64])
    PNETVAR(wearables, "CBaseCombatCharacter", "m_hMyWearables", int)

    NETVAR(viewModel, "CBasePlayer", "m_hViewModel[0]", int)
    NETVAR(fov, "CBasePlayer", "m_iFOV", int)
    NETVAR(fovStart, "CBasePlayer", "m_iFOVStart", int)
    NETVAR(defaultFov, "CBasePlayer", "m_iDefaultFOV", int)
    NETVAR(flags, "CBasePlayer", "m_fFlags", int)
    NETVAR(tickBase, "CBasePlayer", "m_nTickBase", int)
    NETVAR(aimPunchAngle, "CBasePlayer", "m_aimPunchAngle", Vector)
    NETVAR(aimPunchAngleVelocity, "CBasePlayer", "m_aimPunchAngleVel", Vector)
    NETVAR(baseVelocity, "CBasePlayer", "m_vecBaseVelocity", Vector)
    NETVAR(viewPunchAngle, "CBasePlayer", "m_viewPunchAngle", Vector)
    NETVAR(viewOffset, "CBasePlayer", "m_vecViewOffset[0]", Vector)
    NETVAR(velocity, "CBasePlayer", "m_vecVelocity[0]", Vector)
    NETVAR(lastPlaceName, "CBasePlayer", "m_szLastPlaceName", char[18])
    NETVAR(getLadderNormal, "CBasePlayer", "m_vecLadderNormal", Vector)
    NETVAR(duckAmount, "CBasePlayer", "m_flDuckAmount", float)
    NETVAR(duckSpeed, "CBasePlayer", "m_flDuckSpeed", float)
    NETVAR(fallVelocity, "CBasePlayer", "m_flFallVelocity", float)
    NETVAR(groundEntity, "CBasePlayer", "m_hGroundEntity", int)
    NETVAR(health, "CBasePlayer", "m_iHealth", int)

    NETVAR(armor, "CCSPlayer", "m_ArmorValue", int)
    NETVAR(hasHeavyArmor, "CCSPlayer", "m_bHasHeavyArmor", bool)
    NETVAR(eyeAngles, "CCSPlayer", "m_angEyeAngles", Vector)
    NETVAR(gunGameImmunity, "CCSPlayer", "m_bGunGameImmunity", bool)
    NETVAR(account, "CCSPlayer", "m_iAccount", int)
    NETVAR(lby, "CCSPlayer", "m_flLowerBodyYawTarget", float)
    NETVAR(ragdoll, "CCSPlayer", "m_hRagdoll", int)
    NETVAR(shotsFired, "CCSPlayer", "m_iShotsFired", int)
    NETVAR(money, "CCSPlayer", "m_iAccount", int)
    NETVAR(waitForNoAttack, "CCSPlayer", "m_bWaitForNoAttack", bool)
    NETVAR(isStrafing, "CCSPlayer", "m_bStrafing", bool)
    NETVAR(moveState, "CCSPlayer", "m_iMoveState", int)
    NETVAR(duckOverride, "CCSPlayer", "m_bDuckOverride", bool)
    NETVAR(stamina, "CCSPlayer", "m_flStamina", float)
    NETVAR(thirdPersonRecoil, "CCSPlayer", "m_flThirdpersonRecoil", float)
    NETVAR(velocityModifier, "CCSPlayer", "m_flVelocityModifier", float)

    NETVAR(viewModelIndex, "CBaseCombatWeapon", "m_iViewModelIndex", int)
    NETVAR(worldModelIndex, "CBaseCombatWeapon", "m_iWorldModelIndex", int)
    NETVAR(worldDroppedModelIndex, "CBaseCombatWeapon", "m_iWorldDroppedModelIndex", int)
    NETVAR(weaponWorldModel, "CBaseCombatWeapon", "m_hWeaponWorldModel", int)
    NETVAR(clip, "CBaseCombatWeapon", "m_iClip1", int)
    NETVAR(reserveAmmoCount, "CBaseCombatWeapon", "m_iPrimaryReserveAmmoCount", int)
    NETVAR(nextPrimaryAttack, "CBaseCombatWeapon", "m_flNextPrimaryAttack", float)
    NETVAR(nextSecondaryAttack, "CBaseCombatWeapon", "m_flNextSecondaryAttack", float)
    NETVAR(recoilIndex, "CBaseCombatWeapon", "m_flRecoilIndex", float)

    NETVAR(activeWeapon, "CBaseCombatCharacter", "m_hActiveWeapon", int)

    NETVAR(nextAttack, "CBaseCombatCharacter", "m_flNextAttack", float)

    NETVAR(readyTime, "CWeaponCSBase", "m_flPostponeFireReadyTime", float)
    NETVAR(burstMode, "CWeaponCSBase", "m_bBurstMode", bool)

    NETVAR(burstShotRemaining, "CWeaponCSBaseGun", "m_iBurstShotsRemaining", int)
    NETVAR(zoomLevel, "CWeaponCSBaseGun", "m_zoomLevel", int)

    NETVAR(accountID, "CBaseAttributableItem", "m_iAccountID", int)
    NETVAR(itemDefinitionIndex, "CBaseAttributableItem", "m_iItemDefinitionIndex", short)
    NETVAR(itemDefinitionIndex2, "CBaseAttributableItem", "m_iItemDefinitionIndex", WeaponId)
    NETVAR(itemIDHigh, "CBaseAttributableItem", "m_iItemIDHigh", int)
    NETVAR(entityQuality, "CBaseAttributableItem", "m_iEntityQuality", int)
    NETVAR(customName, "CBaseAttributableItem", "m_szCustomName", char[32])
    NETVAR(fallbackPaintKit, "CBaseAttributableItem", "m_nFallbackPaintKit", unsigned)
    NETVAR(fallbackSeed, "CBaseAttributableItem", "m_nFallbackSeed", unsigned)
    NETVAR(fallbackWear, "CBaseAttributableItem", "m_flFallbackWear", float)
    NETVAR(fallbackStatTrak, "CBaseAttributableItem", "m_nFallbackStatTrak", unsigned)
    NETVAR(initialized, "CBaseAttributableItem", "m_bInitialized", bool)

    NETVAR(owner, "CBaseViewModel", "m_hOwner", int)
    NETVAR(weapon, "CBaseViewModel", "m_hWeapon", int)
    
    NETVAR(freezePeriod, "CCSGameRulesProxy", "m_bFreezePeriod", bool)
    NETVAR(isValveDS, "CCSGameRulesProxy", "m_bIsValveDS", bool)
};