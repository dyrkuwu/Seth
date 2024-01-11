#pragma once

#include "Server.h"

enum class ClassId
{
    _TFWeaponBuilder = 0,
    AI_BaseNPC = 0,
    BossAlpha = 0,
    BotNPC = 0,
    BotNPCMinion = 0,
    PropJeep = 0,
    PropVehicleChoreoGeneric = 0,
    TFBuffBanner = 0,
    BaseAnimating,
    BaseAnimatingOverlay,
    BaseAttributableItem,
    BaseCombatCharacter,
    BaseCombatWeapon,
    BaseDoor,
    BaseEntity,
    BaseFlex,
    BaseGrenade,
    BaseObject,
    BaseObjectUpgrade,
    BaseParticleEntity,
    BasePlayer,
    BaseProjectile,
    BasePropDoor,
    BaseTeamObjectiveResource,
    BaseTempEntity,
    BaseViewModel,
    Beam,
    BoneFollower,
    BonusDuckPickup,
    BonusPack,
    BonusRoundLogic,
    BreakableProp,
    BreakableSurface,
    CaptureFlag,
    CaptureFlagReturnIcon,
    CaptureZone,
    ColorCorrection,
    ColorCorrectionVolume,
    CurrencyPack,
    DynamicLight,
    DynamicProp,
    EconEntity,
    EconWearable,
    Embers,
    EntityDissolve,
    EntityFlame,
    EntityParticleTrail,
    EnvDetailController,
    EnvParticleScript,
    EnvProjectedTexture,
    EnvQuadraticBeam,
    EnvScreenEffect,
    EnvScreenOverlay,
    EnvTonemapController,
    EnvWind,
    EyeballBoss,
    FireSmoke,
    FireTrail,
    Fish,
    FogController,
    Func_Dust,
    Func_LOD,
    FuncAreaPortalWindow,
    FuncConveyor,
    FuncForceField,
    FuncLadder,
    FuncMonitor,
    FuncOccluder,
    FuncPasstimeGoal,
    FuncReflectiveGlass,
    FuncRespawnRoom,
    FuncRespawnRoomVisualizer,
    FuncRotating,
    FuncSmokeVolume,
    FuncTrackTrain,
    GameRulesProxy,
    HalloweenGiftPickup,
    HalloweenPickup,
    HalloweenSoulPack,
    HandleTest,
    HeadlessHatman,
    Hightower_TeleportVortex,
    InfoLadderDismount,
    InfoLightingRelative,
    InfoOverlayAccessor,
    LaserDot,
    LightGlow,
    MannVsMachineStats,
    MaterialModifyControl,
    Merasmus,
    MerasmusDancer,
    MonsterResource,
    ObjectCartDispenser,
    ObjectDispenser,
    ObjectSapper,
    ObjectSentrygun,
    ObjectTeleporter,
    ParticleFire,
    ParticlePerformanceMonitor,
    ParticleSystem,
    PasstimeBall,
    PasstimeGun,
    PhysBox,
    PhysBoxMultiplayer,
    PhysicsProp,
    PhysicsPropMultiplayer,
    PhysMagnet,
    Plasma,
    PlayerDestructionDispenser,
    PlayerResource,
    PointCamera,
    PointCommentaryNode,
    PointWorldText,
    PoseController,
    Precipitation,
    PropVehicleDriveable,
    RagdollManager,
    RagdollProp,
    RagdollPropAttached,
    RobotDispenser,
    RopeKeyframe,
    SceneEntity,
    ShadowControl,
    SlideshowDisplay,
    SmokeStack,
    SniperDot,
    SpotlightEnd,
    Sprite,
    SpriteOriented,
    SpriteTrail,
    SteamJet,
    Sun,
    Team,
    TeamplayRoundBasedRulesProxy,
    TeamRoundTimer,
    TeamTrainWatcher,
    TEArmorRicochet,
    TEBaseBeam,
    TEBeamEntPoint,
    TEBeamEnts,
    TEBeamFollow,
    TEBeamLaser,
    TEBeamPoints,
    TEBeamRing,
    TEBeamRingPoint,
    TEBeamSpline,
    TEBloodSprite,
    TEBloodStream,
    TEBreakModel,
    TEBSPDecal,
    TEBubbles,
    TEBubbleTrail,
    TEClientProjectile,
    TEDecal,
    TEDust,
    TEDynamicLight,
    TEEffectDispatch,
    TEEnergySplash,
    TEExplosion,
    TEFireBullets,
    TEFizz,
    TEFootprintDecal,
    TEGaussExplosion,
    TEGlowSprite,
    TEImpact,
    TEKillPlayerAttachments,
    TELargeFunnel,
    TeleportVortex,
    TEMetalSparks,
    TEMuzzleFlash,
    TEParticleSystem,
    TEPhysicsProp,
    TEPlayerAnimEvent,
    TEPlayerDecal,
    TEProjectedDecal,
    TEShatterSurface,
    TEShowLine,
    Tesla,
    TESmoke,
    TESparks,
    TESprite,
    TESpriteSpray,
    Test_ProxyToggle_Networkable,
    TestTraceline,
    TETFBlood,
    TETFExplosion,
    TETFParticleEffect,
    TEWorldDecal,
    TFAmmoPack,
    TFBall_Ornament,
    TFBaseBoss,
    TFBaseProjectile,
    TFBaseRocket,
    TFBat,
    TFBat_Fish,
    TFBat_Giftwrap,
    TFBat_Wood,
    TFBonesaw,
    TFBotHintEngineerNest,
    TFBottle,
    TFBreakableMelee,
    TFBreakableSign,
    TFBuffItem,
    TFCannon,
    TFChargedSMG,
    TFCleaver,
    TFClub,
    TFCompoundBow,
    TFCrossbow,
    TFDRGPomson,
    TFDroppedWeapon,
    TFFireAxe,
    TFFists,
    TFFlameManager,
    TFFlameRocket,
    TFFlameThrower,
    TFFlareGun,
    TFFlareGun_Revenge,
    TFGameRulesProxy,
    TFGasManager,
    TFGenericBomb,
    TFGlow,
    TFGrapplingHook,
    TFGrenadeLauncher,
    TFGrenadePipebombProjectile,
    TFHalloweenMinigame,
    TFHalloweenMinigame_FallingPlatforms,
    TFHellZap,
    TFItem,
    TFJar,
    TFJarGas,
    TFJarMilk,
    TFKatana,
    TFKnife,
    TFLaserPointer,
    TFLunchBox,
    TFLunchBox_Drink,
    TFMechanicalArm,
    TFMedigunShield,
    TFMiniGame,
    TFMinigameLogic,
    TFMinigun,
    TFObjectiveResource,
    TFParachute,
    TFParachute_Primary,
    TFParachute_Secondary,
    TFParticleCannon,
    TFPasstimeLogic,
    TFPEPBrawlerBlaster,
    TFPipebombLauncher,
    TFPistol,
    TFPistol_Scout,
    TFPistol_ScoutPrimary,
    TFPistol_ScoutSecondary,
    TFPlayer,
    TFPlayerDestructionLogic,
    TFPlayerResource,
    TFPointManager,
    TFPowerupBottle,
    TFProjectile_Arrow,
    TFProjectile_BallOfFire,
    TFProjectile_Cleaver,
    TFProjectile_EnergyBall,
    TFProjectile_EnergyRing,
    TFProjectile_Flare,
    TFProjectile_GrapplingHook,
    TFProjectile_HealingBolt,
    TFProjectile_Jar,
    TFProjectile_JarGas,
    TFProjectile_JarMilk,
    TFProjectile_MechanicalArmOrb,
    TFProjectile_Rocket,
    TFProjectile_SentryRocket,
    TFProjectile_SpellBats,
    TFProjectile_SpellFireball,
    TFProjectile_SpellKartBats,
    TFProjectile_SpellKartOrb,
    TFProjectile_SpellLightningOrb,
    TFProjectile_SpellMeteorShower,
    TFProjectile_SpellMirv,
    TFProjectile_SpellPumpkin,
    TFProjectile_SpellSpawnBoss,
    TFProjectile_SpellSpawnHorde,
    TFProjectile_SpellSpawnZombie,
    TFProjectile_SpellTransposeTeleport,
    TFProjectile_Throwable,
    TFProjectile_ThrowableBreadMonster,
    TFProjectile_ThrowableBrick,
    TFProjectile_ThrowableRepel,
    TFPumpkinBomb,
    TFRagdoll,
    TFRaygun,
    TFReviveMarker,
    TFRevolver,
    TFRobotArm,
    TFRobotDestruction_Robot,
    TFRobotDestruction_RobotGroup,
    TFRobotDestruction_RobotSpawn,
    TFRobotDestructionLogic,
    TFRocketLauncher,
    TFRocketLauncher_AirStrike,
    TFRocketLauncher_DirectHit,
    TFRocketLauncher_Mortar,
    TFRocketPack,
    TFScatterGun,
    TFShotgun,
    TFShotgun_HWG,
    TFShotgun_Pyro,
    TFShotgun_Revenge,
    TFShotgun_Soldier,
    TFShotgunBuildingRescue,
    TFShovel,
    TFSlap,
    TFSMG,
    TFSniperRifle,
    TFSniperRifleClassic,
    TFSniperRifleDecap,
    TFSodaPopper,
    TFSpellBook,
    TFStickBomb,
    TFStunBall,
    TFSword,
    TFSyringeGun,
    TFTankBoss,
    TFTauntProp,
    TFTeam,
    TFThrowable,
    TFViewModel,
    TFWeaponBase,
    TFWeaponBaseGrenadeProj,
    TFWeaponBaseGun,
    TFWeaponBaseMelee,
    TFWeaponBaseMerasmusGrenade,
    TFWeaponBuilder,
    TFWeaponFlameBall,
    TFWeaponInvis,
    TFWeaponPDA,
    TFWeaponPDA_Engineer_Build,
    TFWeaponPDA_Engineer_Destroy,
    TFWeaponPDA_Spy,
    TFWeaponPDAExpansion_Dispenser,
    TFWeaponPDAExpansion_Teleporter,
    TFWeaponSapper,
    TFWearable,
    TFWearableCampaignItem,
    TFWearableDemoShield,
    TFWearableItem,
    TFWearableLevelableItem,
    TFWearableRazorback,
    TFWearableRobotArm,
    TFWearableVM,
    TFWrench,
    VGuiScreen,
    VoteController,
    WaterBullet,
    WaterLODControl,
    WeaponIFMBase,
    WeaponIFMBaseCamera,
    WeaponIFMSteadyCam,
    WeaponMedigun,
    World,
    Zombie,
	DustTrail,
	MovieExplosion,
	NextBotCombatCharacter,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};