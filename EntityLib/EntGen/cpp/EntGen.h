
// /!\ This code is GENERATED! Do not modify it.

#pragma once

#include <EntityLib.h>
#include "EntGenHelpers.h"

namespace Ent
{
    namespace Gen
    {
        struct variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_; // Union
        struct TypedValue;
        struct variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_; // Union
        struct variant_Pasta_Easing_Curve_string_; // Union
        struct sPhysicsShapeSphere;
        struct sPhysicsShapeMesh;
        struct sPhysicsShapeCylinder;
        struct sPhysicsShapeCapsule;
        struct sJointFixedDesc;
        struct sJointBallDesc;
        struct sGameEffectTemplate;
        struct sBoneInfluenceDataTemplate;
        struct sNodeBoneInfluenceDataTemplate;
        struct eventStringHash;
        struct sPhysicsShapeBox;
        struct sEnvStamp;
        struct sJointUniversalDesc;
        struct sJointSwingTwistDesc;
        struct sJointSliderDesc;
        struct sJointHingeDesc;
        struct VomitData;
        struct UnionObjectArrayItem;
        struct TransitionNeighborData;
        struct TestPropertyDefaultValues;
        struct TestPropertyDefaultValues2;
        struct Terrain_TerrainMeta;
        struct TagsList;
        struct TaggedEntityRef;
        struct SyncTempoMode; // enum
        enum class SyncTempoModeEnum
        {
            None_,
            OnGrid,
            OnBeat,
            OnBar,
            OnEnterCue,
            OnExitCue,
            OnCustomCue,
            OnSwitchTransition,
            SyncTempoMode_COUNT,
            SyncTempoMode_FIRST,
        };
        struct StyleMode; // enum
        enum class StyleModeEnum
        {
            default_,
            stick,
            sword,
            do_,
            hammer,
            knife,
            squirrel,
            lush,
            StyleMode_COUNT,
        };
        struct StunData;
        struct StickToGround;
        struct StateGauge;
        struct StunGauge;
        struct SpeedMode; // enum
        enum class SpeedModeEnum
        {
            speed0,
            speed1,
            speed2,
            speed3,
            speed4,
            SpeedMode_COUNT,
        };
        struct SpeedFastMinDuration;
        struct Specie; // enum
        enum class SpecieEnum
        {
            auroch,
            bear,
            babybear,
            catfish,
            eagle,
            elk,
            fox,
            giantbear,
            human,
            cannibal,
            babyhuman,
            horse,
            ibex,
            rabbit,
            rat,
            ram,
            raven,
            schmetre,
            seagull,
            snake,
            spermwhale,
            squirrel,
            stag,
            toad,
            trout,
            wildboar,
            babyboar,
            wolf,
            shark,
            dolphin,
            whale,
            goddess,
            clothboots,
            clothbrace,
            clothhelmet,
            clothskirt,
            clothtorso,
            clothbody,
            weapon,
            outfit,
            drivable,
            fruit,
            darkstone,
            destructible,
            environment,
            regeneration,
            insect,
            Specie_COUNT,
        };
        struct SpawningParameter;
        struct SoundEventMapping;
        struct SoundEmissionStrength; // enum
        enum class SoundEmissionStrengthEnum
        {
            none,
            low,
            medium,
            high,
            SoundEmissionStrength_COUNT,
        };
        struct ShootSequenceData;
        struct ShootData;
        struct SeedPatchData;
        struct SeedPatchDataList;
        struct ScriptPathAndDataSet;
        struct ScaleConverter;
        struct ReviveSide; // enum
        enum class ReviveSideEnum
        {
            neutral,
            sacred,
            cursed,
            ReviveSide_COUNT,
        };
        struct RevivedData;
        struct ReviveSideEvent;
        struct ResponsiblePointer_CineEvent_; // Union
        struct ResponsiblePointer_ActorState_; // Union
        struct RegenSwitchBehavior; // enum
        enum class RegenSwitchBehaviorEnum
        {
            CrossFade,
            CrossMetamorphosis,
            SequentialMetamorphosis,
        };
        struct sPhysicsJointDesc;
        struct sPhysicShape;
        struct sRigidBodyDesc;
        struct Transform3D;
        struct ProgressSoundEventData;
        struct PrimitiveData;
        struct PrimitiveColliderType; // enum
        enum class PrimitiveColliderTypeEnum
        {
            Undefined,
            Sphere,
            Box,
            Capsule,
            Cylinder,
            Mesh,
            PrimitiveColliderType_COUNT,
        };
        struct PredictionBehaviorDuration;
        struct PredictionBehaviorData;
        struct Precision; // enum
        enum class PrecisionEnum
        {
            full,
            half,
            quarter,
            eighth,
            sixteenth,
            highest,
            lowest,
        };
        using Position = Ent::Gen::Tuple<Ent::Gen::Int, Ent::Gen::Int, Ent::Gen::Float, Ent::Gen::Float, Ent::Gen::Float>; // Tuple
        struct OutfitPieceType; // enum
        enum class OutfitPieceTypeEnum
        {
            OutfitPieceType_NONE,
            Head,
            Torso,
            Skirt,
            Boots,
            Brace,
            Body,
            Hair,
            OutfitPieceType_COUNT,
        };
        struct OutfitPiece;
        struct Orientation;
        struct Object_MaxActivationLevel; // enum
        enum class Object_MaxActivationLevelEnum
        {
            Created,
            InWorld,
            Loading,
            Started,
        };
        struct NavmeshGenerationParameters;
        struct MoveCapacityData_OrientationSpeed;
        struct MountableSnapLine_ControlPoint;
        struct MountData;
        struct MeshesItem;
        struct RUNTIME_LODsItem;
        struct MeshNavigationAllowedMode; // enum
        enum class MeshNavigationAllowedModeEnum
        {
            Never,
            PlayerOnly,
            Always,
            MeshNavigationAllowedMode_COUNT,
        };
        struct MeshNavigationBehaviorData;
        struct MenaceSelection; // enum
        enum class MenaceSelectionEnum
        {
            closest,
            weakest,
            strongest,
            MenaceSelection_COUNT,
        };
        struct MaxActivationLevel; // enum
        enum class MaxActivationLevelEnum
        {
            Created,
            InWorld,
            Loading,
            Started,
        };
        struct VolumeConstraintDataGD;
        struct LocomotionMode; // enum
        enum class LocomotionModeEnum
        {
            standup,
            quadstandup,
            crouch,
            prone,
            swim,
            ride,
            fly,
            dive,
            fall,
            cinematic,
            ridden,
            riddenfly,
            clamber,
            buried,
            count,
        };
        struct MoveCapacityData_ReachSpeed;
        struct ListItem;
        struct LightType; // enum
        enum class LightTypeEnum
        {
            Omni,
            Hemi,
            Spot,
            Dir,
            LightType_Count,
        };
        struct LifeAndDamageData;
        struct LastAliveReviveSide;
        struct InteractData;
        struct InputCollisionBehaviorData;
        struct ImmersedBehaviorData;
        struct HotSpotType; // enum
        enum class HotSpotTypeEnum
        {
            all,
            none,
            back,
            beam,
            bite,
            biter,
            breakablestrong,
            breakableweak,
            camera,
            center,
            head,
            heal,
            ride,
            root,
            snap,
            slot,
            spawnlife,
            shoot,
            take,
            takehandle,
            vertebra,
            respawnslot,
            HotSpotType_COUNT,
        };
        struct PickableDistributorComponentData;
        struct HotspotData;
        struct HeadCollisionBehaviorData;
        struct GrowingState; // enum
        enum class GrowingStateEnum
        {
            invalid,
            nogrow,
            growing,
            grown,
            manualgrow,
            degrowing,
            GrowingState_COUNT,
        };
        struct GPEType; // enum
        enum class GPETypeEnum
        {
            BendTree,
            Geyser,
            PossessFlocking,
            GPEType_COUNT,
        };
        struct FusionData;
        struct FreezeData;
        struct ProjectileData;
        struct FluidVolumeComponentGD_SimulationParameters;
        struct FluidVolumeComponentGD_HeightMapData;
        struct FluidVolumeComponentGD_FluidVolumeData;
        struct FluidType; // enum
        enum class FluidTypeEnum
        {
            water,
            lava,
            mud,
            FluidType_COUNT,
        };
        struct FloatRange;
        struct VegetationPCloudData;
        struct EventCameraData;
        struct EntityLODData;
        struct RegenData;
        struct EDITOR_Mesh;
        struct EDITOR_LODsItem;
        struct DisplaceNoiseListItem;
        struct CreatureDangerousness;
        struct ConditionalRigidityAttribute_RigidityParameter;
        struct ConditionalRigidityAttribute_Conditions;
        struct ConditionalRigidityAttribute_Attributes;
        struct ConditionalRigidityAttribute;
        struct ComponentGD;
        struct WorldScalePathFindGD;
        struct WildObject;
        struct VoxelSimulationGD;
        struct VolumeConstraintGD;
        struct VisualGD;
        struct VelocityObstacleGD;
        struct UnifiedPhysicsDataGD;
        struct TriggerEventCameraGD;
        struct TransformGD;
        struct TestUnion;
        struct TestSetOfObject;
        struct TestEntityRef;
        struct TestDefaultValues;
        struct TestCreature;
        struct TestArrays;
        struct TerrainSurfaceObject;
        struct TerrainGD;
        struct TeamGD;
        struct SystemicCreature;
        struct SubScene;
        struct StickToTerrain;
        struct StaticObjectGD;
        struct StaffVertebrasGD;
        struct SoundEmitterGD;
        struct SoundAreaGD;
        struct SoulSpotGD;
        struct SoulRespawnOpportunityGD;
        struct SmoothScaleComponentGD;
        struct SmallActorSpawnerGD;
        struct SmallActorGD;
        struct SideMapGateGD;
        struct ShapeshiftStatueGD;
        struct ShamanVisionGD;
        struct ShamanItemGD;
        struct SensorControllerGD;
        struct SeedPatch;
        struct ScriptComponentGD;
        struct ReviveSideSwitcherGD;
        struct ReviveEnergyGD;
        struct RespawnPlaceGD;
        struct RegenerableVegetationGD;
        struct RegenSwitcherGD;
        struct RegenMeshGD;
        struct RegenFXGD;
        struct RagdollGD;
        struct QuickCreatureSwitchGD;
        struct ProtoComponentGD;
        struct ProjectileShooterGD;
        struct PossessableGPEGD;
        struct PlayerComponentGD;
        struct PickableDistributorComponentGD;
        struct PickableComponentGD;
        struct PhysicsTriggerGD;
        struct PhysicsMeshProviderGD;
        struct PhysicsMeshDeformerGD;
        struct PhysicsGD;
        struct PhysicsDataGD;
        struct PerceiverGD;
        struct PerceivableGD;
        struct PathNodeGD;
        struct PathMotionControllerGD;
        struct PathGD;
        struct PathBoneRigidBodyGD;
        struct PathBoneInfluenceGD;
        struct PathBoneAnimGD;
        struct OutfitWearerGD;
        struct OutfitGD;
        struct NotVisibleInSubscene;
        struct NetworkNode;
        struct NetworkLink;
        struct NetGD;
        struct MultiThumbnail;
        struct MounterGD;
        struct MountableGD;
        struct MountIKControllerGD;
        struct MissionHolderGD;
        struct MeshNavigationInfosGD;
        struct Mesh;
        struct LDPrimitive;
        struct ItemHolderGD;
        struct InventoryGD;
        struct InfoboardRegistererGD;
        struct HotspotsGD;
        struct HitTriggerGD;
        struct HeightObj;
        struct HeightMapComponentGD;
        struct HealthAreaGD;
        struct HealerGD;
        struct HealTriggerGD;
        struct HealPumpGD;
        struct GroundTypeSamplerGD;
        struct GameEffectSpawnerGD;
        struct FluidVolumeComponentGD;
        struct FluidViewGD;
        struct FluidToRegenInjectorGD;
        struct FluidNavMeshTaggerGD;
        struct FluidGD;
        struct FluidFXEntitySpawnerGD;
        struct FireSensorGD;
        struct EventTriggerGD;
        struct EventHandlerGD;
        struct EnvStampGD;
        struct EnergySpoutGD;
        struct EnergySourceGD;
        struct EnergyProbeGD;
        struct EnergyPoolGD;
        struct EnergyNetworkListenerGD;
        struct EnergyDrainGD;
        struct EnergyCrookGD;
        struct DummyComponentGD;
        struct DistanceTriggerGD;
        struct FightDistanceTriggerGD;
        struct DebugGridGD;
        struct CustomThumbnail;
        struct CreatureUIGD;
        struct ConnectorGD;
        struct ComponentWithProtoCodeGD;
        struct ClothAnimationGD;
        struct ChildEntityPoolComponentGD;
        struct CharacterPlatformGD;
        struct CameraDataGD;
        struct BreakableGD;
        struct BittenGD;
        struct BeamGeneratorGD;
        struct AttackTriggerGD;
        struct AssemblyGD;
        struct AnimationRegenConstraintsGD;
        struct AnimationPlaylistGD;
        struct AnimationPhysicsChainConstraintsGD;
        struct AnimationModelGD;
        struct AnimationHitsConstraintsGD;
        struct Component; // Union
        struct Object_Components; // union_set
        struct Components; // union_set
        struct LightComponentGD;
        struct BoidsGD;
        struct Collider;
        struct AnimationTailConstraintsGD;
        struct CinematicUpdateType; // enum
        enum class CinematicUpdateTypeEnum
        {
            none,
            Internal,
            Pesto,
            CinematicUpdateType_COUNT,
        };
        struct CinematicSlot;
        struct Sequence;
        struct CinematicGD;
        struct CineEvent;
        struct CineEventTrigger;
        struct CineEventTriggerPlaySound;
        struct CineEventTriggerPlaySequence;
        struct CineEventTriggerGameStateChange;
        struct CineEventTriggerEventHandlerPost;
        struct CineEventTest;
        struct CineEventTestWait;
        struct CineEventTestIsCanceled;
        struct CineEventTestInput;
        struct CineEventTestEndCurrentSequence;
        struct CineEventTestCurrentGameState;
        struct CharacterControllerSlideData;
        struct CharacterControllerGroundNormalData;
        struct CharacterControllerFallData;
        struct CharacterControllerClamberData;
        struct CameraType; // enum
        enum class CameraTypeEnum
        {
            NONE,
            Death,
            Editor,
            Event,
            Free,
            ThirdPerson,
            ThirdPersonFollow,
            ThirdPersonAim,
            ThirdPersonClamber,
            MotionConstraint,
            OnSpline,
            OnBones,
            TopView,
            EntitySwap,
            Locked,
            Pan,
            CameraType_COUNT,
        };
        struct CameraSetterGD;
        struct CameraShakeData;
        struct BiteData;
        struct BehaviorScriptData;
        struct CreatureAIGD;
        struct BeamStaffMode; // enum
        enum class BeamStaffModeEnum
        {
            Off,
            Searching,
            Creature,
            PossessingGPE,
            Shapeshifting,
            Item,
            UpgradeStaff,
            SideMap,
            PickUp,
            Hatching,
            Any,
            BeamStaffMode_COUNT,
        };
        struct BeamTargetGD;
        struct AttackType; // enum
        enum class AttackTypeEnum
        {
            Short,
            Long,
            Backward,
            Charged,
            Distant,
            Push,
            Unmount,
            Dodge,
            Uppercut,
            Landing,
            JumpOnto,
            Bite,
            Stomp,
            AttackType_COUNT,
        };
        struct AttackAbility;
        struct AttackWeaponAbility;
        struct AttackData;
        struct Archetype; // enum
        enum class ArchetypeEnum
        {
            flying,
            swimming,
            quadripede,
            bipede,
            item,
            structure,
            activator,
            Archetype_COUNT,
        };
        struct AnimationTreeConstraintsGD_GrowData;
        struct AnimationTreeConstraintsGD_ForceData;
        struct AnimationTreeConstraintsGD_BendData;
        struct AnimationTreeConstraintsGD;
        struct AnimationLegsConstraints_SlopeOffsetInfo;
        struct AnimationLegsConstraintsGD;
        struct AnimationEventsGeneratorGD_TrackedBone;
        struct AnimationEventsGeneratorGD;
        struct AnimTagTimelineTransition; // enum
        enum class AnimTagTimelineTransitionEnum
        {
            beginning,
            copy,
            reverse,
            AnimTagTimelineTransition_COUNT,
        };
        struct AnimTag; // enum
        enum class AnimTagEnum
        {
            none,
            apex,
            forward,
            forwardright,
            right,
            backwardright,
            backward,
            backwardleft,
            left,
            forwardleft,
            regular,
            alignedregular,
            goofy,
            alignedgoofy,
            top,
            bottom,
            up,
            upforward,
            upward,
            down,
            downforward,
            downward,
            in_,
            out,
            horizontal,
            vertical,
            count,
        };
        struct MoveCapacityData_AnimTagTimelineTransitionItem;
        struct MoveCapacityData_AnimTagTimelineTransitionTable;
        struct MoveCapacityData;
        struct CharacterControllerGD;
        struct AnimMirroringSpecData;
        struct AnimMirroringData;
        struct AnimationControllerGD;
        struct ActorStates; // union_set
        struct Object;
        struct UnitTestComponent;
        struct Entity;
        struct ActorStateTeleport_Inputs;
        struct ActorState;
        struct EntityStateVoxelsVolume;
        struct EntityStatePlayer;
        struct EntityStateMask;
        struct EntityStateForceCanBeTargeted;
        struct EntityStateEnergySpoutState;
        struct EntityStateEnergyRootState;
        struct EntityStateBoidsHomePos;
        struct ActorStateTeleport;
        struct ActorStateRegenerationLow;
        struct ActorStateRegenerationFull;
        struct ActorStateInvincible;
        struct ActorStateHoldingItem;
        struct ActorStateHasNoBody;
        struct ActorStateDead;
        struct ActorStateBuried;
        struct ActorStateBeingOnGround;
        struct ActorStateBeingInAir;
        struct ActorStateBeingImmersed;
        struct ActorStateAlive;
        struct AbilityData;
        struct ActorGD;
        struct ProjectileGD;
        struct CreatureGD;
        struct ClothGD;
        struct AIContextSlot;
        struct AIContextGD;
        struct ActorAbility; // enum
        enum class ActorAbilityEnum
        {
            landing,
            crouch,
            fly,
            ride,
            dive,
            stinky,
            ActorAbility_COUNT,
        };
        struct ActorCategory; // enum
        enum class ActorCategoryEnum
        {
            CATEGORY_All,
            CATEGORY_Action,
            CATEGORY_AnimationLegConstraint,
            CATEGORY_ActionAttack,
            CATEGORY_Attitude,
            CATEGORY_Context,
            CATEGORY_ActionCosmetic,
            CATEGORY_ActionDamage,
            CATEGORY_ActionDefault,
            CATEGORY_ActionDie,
            CATEGORY_Environment,
            CATEGORY_Fall,
            CATEGORY_Hint,
            CATEGORY_LookAt,
            CATEGORY_ActionJump,
            CATEGORY_ActionLand,
            CATEGORY_Life,
            CATEGORY_Locomotion,
            CATEGORY_ActionMove,
            CATEGORY_Persistent,
            CATEGORY_Purgatory,
            CATEGORY_ActionSlide,
            CATEGORY_ActionStop,
            CATEGORY_ActionStrafe,
            CATEGORY_Transition,
            CATEGORY_Trigger,
            CATEGORY_ActionWingFlutter,
            CATEGORY_Health,
            CATEGORY_HealthAlive,
            CATEGORY_HealthDead,
            CATEGORY_Regeneration,
            CATEGORY_EntitySwitchTransition,
            CATEGORY_EnergyRoot,
            CATEGORY_EnergySpout,
            CATEGORY_GPE,
            ActorCategory_COUNT,
        };
        struct InventoryTags; // enum
        enum class InventoryTagsEnum
        {
            outfit,
            item,
            default_,
            neutral,
            sacred,
            cursed,
            skeleton,
            zombie,
            full,
            soul,
            disguise,
            soulfreedflying,
            soulfreednormal,
            InventoryTags_COUNT,
        };
        struct MapOfObjectItem_A;
        struct Pasta_Easing_Curve; // enum
        enum class Pasta_Easing_CurveEnum
        {
            Linear,
            EaseInSin,
            EaseInQuad,
            EaseInCubic,
            EaseInQuart,
            EaseInQuint,
            EaseInExp,
            EaseOutSin,
            EaseOutQuad,
            EaseOutCubic,
            EaseOutQuart,
            EaseOutQuint,
            EaseOutExp,
            EaseInoutSin,
            EaseInoutQuad,
            EaseInoutCubic,
            EaseInoutQuart,
            EaseInoutQuint,
            EaseInoutExp,
            EaseInCirc,
            EaseOutCirc,
            EaseInoutCirc,
            EaseOutElastic,
            Count,
        };
        struct PhysicsLayer; // enum
        enum class PhysicsLayerEnum
        {
            Default,
            Ground,
            Static,
            Raycast,
            Trigger,
            Walkable,
            Camera,
            ClimbEdge,
            Kinematic,
            Ragdoll,
            Projectile,
            Hit,
            MotionConstraint,
            Heal,
            Body,
            Fluid,
            Hitable,
            None_,
            All,
            PHYSICLAYER_COUNT,
        };
        struct ProjectileShooterData;
        struct RegenerationState; // enum
        enum class RegenerationStateEnum
        {
            None_,
            Sacred,
            Cursed,
            Lush,
            Neutral,
            Dead,
            RegenerationState_COUNT,
        };
        struct ReviveSideData;
        struct Scene;
        struct SetOfObjectItem;
        struct Size; // enum
        enum class SizeEnum
        {
            tiny,
            small,
            medium,
            big,
            enormous,
            Size_COUNT,
        };
        using Vector3 = PrimArray<Ent::Gen::Float>;
        using Vector2 = PrimArray<Ent::Gen::Float>;
        using ThumbPath = Ent::Gen::String;
        using Quat = PrimArray<Ent::Gen::Float>;
        using Matrix44 = PrimArray<Ent::Gen::Float>;
        using Matrix33 = PrimArray<Ent::Gen::Float>;
        using Color = PrimArray<Ent::Gen::Float>;

        struct variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_ : Base // Union
        {
            variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_(Ent::Node* _node): Base(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/eastl::variant&lt;eastl::string,bool,s32,float,EntityRef,Vector2,Vector3,Position,eastl::vector&lt;eastl::string&gt;,eastl::vector&lt;bool&gt;,eastl::vector&lt;s32&gt;,eastl::vector&lt;float&gt;,eastl::vector&lt;EntityRef&gt;,eastl::vector&lt;Vector2&gt;,eastl::vector&lt;Vector3&gt;,eastl::vector&lt;Position&gt;&gt;";
            char const* getType() const;
            std::optional<Ent::Gen::String> string() const;
            Ent::Gen::String setstring() const;
            std::optional<Ent::Gen::Bool> bool_() const;
            Ent::Gen::Bool setbool_() const;
            std::optional<Ent::Gen::Int> s32() const;
            Ent::Gen::Int sets32() const;
            std::optional<Ent::Gen::Float> float_() const;
            Ent::Gen::Float setfloat_() const;
            std::optional<Ent::Gen::EntityRef> EntityRef() const;
            Ent::Gen::EntityRef setEntityRef() const;
            std::optional<Ent::Gen::Vector2> Vector2() const;
            Ent::Gen::Vector2 setVector2() const;
            std::optional<Ent::Gen::Vector3> Vector3() const;
            Ent::Gen::Vector3 setVector3() const;
            std::optional<Ent::Gen::Position> Position() const;
            Ent::Gen::Position setPosition() const;
            std::optional<PrimArray<Ent::Gen::String>> stringVec() const;
            PrimArray<Ent::Gen::String> setstringVec() const;
            std::optional<PrimArray<Ent::Gen::Bool>> boolVec() const;
            PrimArray<Ent::Gen::Bool> setboolVec() const;
            std::optional<PrimArray<Ent::Gen::Int>> s32Vec() const;
            PrimArray<Ent::Gen::Int> sets32Vec() const;
            std::optional<PrimArray<Ent::Gen::Float>> floatVec() const;
            PrimArray<Ent::Gen::Float> setfloatVec() const;
            std::optional<PrimArray<Ent::Gen::EntityRef>> EntityRefVec() const;
            PrimArray<Ent::Gen::EntityRef> setEntityRefVec() const;
            std::optional<Array<Ent::Gen::Vector2>> Vector2Vec() const;
            Array<Ent::Gen::Vector2> setVector2Vec() const;
            std::optional<Array<Ent::Gen::Vector3>> Vector3Vec() const;
            Array<Ent::Gen::Vector3> setVector3Vec() const;
            std::optional<Array<Ent::Gen::Position>> PositionVec() const;
            Array<Ent::Gen::Position> setPositionVec() const;
        };

        struct TypedValue : HelperObject // Object
        {
            TypedValue(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/TypedValue";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String Alias() const;
            Ent::Gen::String Reference() const;
            Ent::Gen::variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_ Value() const;
            Ent::Gen::String _comment() const;
        };

        struct variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ : Base // Union
        {
            variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(Ent::Node* _node): Base(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/eastl::variant&lt;s32,float,bool,eastl::string,Vector2,Vector3,Quat,Position&gt;";
            char const* getType() const;
            std::optional<Ent::Gen::Int> s32() const;
            Ent::Gen::Int sets32() const;
            std::optional<Ent::Gen::Float> float_() const;
            Ent::Gen::Float setfloat_() const;
            std::optional<Ent::Gen::Bool> bool_() const;
            Ent::Gen::Bool setbool_() const;
            std::optional<Ent::Gen::String> string() const;
            Ent::Gen::String setstring() const;
            std::optional<Ent::Gen::Vector2> Vector2() const;
            Ent::Gen::Vector2 setVector2() const;
            std::optional<Ent::Gen::Vector3> Vector3() const;
            Ent::Gen::Vector3 setVector3() const;
            std::optional<Ent::Gen::Quat> Quat() const;
            Ent::Gen::Quat setQuat() const;
            std::optional<Ent::Gen::Position> Position() const;
            Ent::Gen::Position setPosition() const;
        };

        struct variant_Pasta_Easing_Curve_string_ : Base // Union
        {
            variant_Pasta_Easing_Curve_string_(Ent::Node* _node): Base(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/eastl::variant&lt;Pasta::Easing::Curve,eastl::string&gt;";
            char const* getType() const;
            std::optional<Ent::Gen::Pasta_Easing_Curve> Pasta_Easing_Curve() const;
            Ent::Gen::Pasta_Easing_Curve setPasta_Easing_Curve() const;
            std::optional<Ent::Gen::String> string() const;
            Ent::Gen::String setstring() const;
        };

        struct sPhysicsShapeSphere : HelperObject // Object
        {
            sPhysicsShapeSphere(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sPhysicsShapeSphere";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float radius() const;
        };

        struct sPhysicsShapeMesh : HelperObject // Object
        {
            sPhysicsShapeMesh(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sPhysicsShapeMesh";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::String path() const;
        };

        struct sPhysicsShapeCylinder : HelperObject // Object
        {
            sPhysicsShapeCylinder(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sPhysicsShapeCylinder";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float length() const;
            Ent::Gen::Float radius() const;
        };

        struct sPhysicsShapeCapsule : HelperObject // Object
        {
            sPhysicsShapeCapsule(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sPhysicsShapeCapsule";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float length() const;
            Ent::Gen::Float radius() const;
        };

        struct sJointFixedDesc : HelperObject // Object
        {
            sJointFixedDesc(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sJointFixedDesc";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
        
        };

        struct sJointBallDesc : HelperObject // Object
        {
            sJointBallDesc(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sJointBallDesc";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
        
        };

        struct sGameEffectTemplate : HelperObject // Object
        {
            sGameEffectTemplate(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sGameEffectTemplate";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Int BoneID() const;
            Ent::Gen::String BoneName() const;
            Ent::Gen::String EffectName() const;
            Ent::Gen::String _comment() const;
        };

        struct sBoneInfluenceDataTemplate : HelperObject // Object
        {
            sBoneInfluenceDataTemplate(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sBoneInfluenceDataTemplate";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String BoneName() const;
            Ent::Gen::Float Influence() const;
            Ent::Gen::String _comment() const;
        };

        struct sNodeBoneInfluenceDataTemplate : HelperObject // Object
        {
            sNodeBoneInfluenceDataTemplate(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sNodeBoneInfluenceDataTemplate";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::sBoneInfluenceDataTemplate> Data() const;
            Ent::Gen::String NodeName() const;
            Ent::Gen::String _comment() const;
        };

        struct eventStringHash : HelperObject // Object
        {
            eventStringHash(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool engaged() const;
            Ent::Gen::String val() const;
        };


        struct sPhysicsShapeBox : HelperObject // Object
        {
            sPhysicsShapeBox(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sPhysicsShapeBox";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Vector3 size() const;
        };

        struct sEnvStamp : HelperObject // Object
        {
            sEnvStamp(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sEnvStamp";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AffectCoverage() const;
            Ent::Gen::Bool AffectFogColor() const;
            Ent::Gen::Bool AffectFogDensity() const;
            Ent::Gen::Bool AffectFogFalloff() const;
            Ent::Gen::Bool AffectFogHeight() const;
            Ent::Gen::Bool AffectPull() const;
            Ent::Gen::Bool AffectType() const;
            Ent::Gen::Bool AffectWetness() const;
            Ent::Gen::Int AtlasID() const;
            Ent::Gen::Vector3 FogColor() const;
            Ent::Gen::Bool IsCloud() const;
            Ent::Gen::Vector3 PositionOffset() const;
            Ent::Gen::Float Rotation() const;
            Ent::Gen::Float Size() const;
            Ent::Gen::Float Strength() const;
            Ent::Gen::String _comment() const;
        };


        struct sJointUniversalDesc : HelperObject // Object
        {
            sJointUniversalDesc(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sJointUniversalDesc";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Vector2 angleSwing1() const;
            Ent::Gen::Vector2 angleSwing2() const;
        };

        struct sJointSwingTwistDesc : HelperObject // Object
        {
            sJointSwingTwistDesc(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sJointSwingTwistDesc";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Vector2 swingAngle() const;
            Ent::Gen::Vector2 twistAngle() const;
        };

        struct sJointSliderDesc : HelperObject // Object
        {
            sJointSliderDesc(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sJointSliderDesc";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Vector3 direction() const;
            Ent::Gen::Vector2 distance() const;
        };

        struct sJointHingeDesc : HelperObject // Object
        {
            sJointHingeDesc(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sJointHingeDesc";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Vector2 angle() const;
            Ent::Gen::Vector3 axis() const;
        };

        struct VomitData : HelperObject // Object
        {
            VomitData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/VomitData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Vector2 AngleRangeHysteresis() const;
            Ent::Gen::Vector2 AngleRangeMax() const;
            Ent::Gen::Bool CanVomit() const;
            Ent::Gen::String ProjectileName() const;
            Ent::Gen::Float VomitCost() const;
            Ent::Gen::Float VomitMinTimer() const;
            Ent::Gen::Float VomitRate() const;
            Ent::Gen::String _comment() const;
        };

        struct UnionObjectArrayItem : HelperObject // Object
        {
            UnionObjectArrayItem(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ Union() const;
            Ent::Gen::String _comment() const;
        };

        struct TransitionNeighborData : HelperObject // Object
        {
            TransitionNeighborData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/TransitionNeighborData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::Int> Backward() const;
            PrimArray<Ent::Gen::Int> Forward() const;
            Ent::Gen::String _comment() const;
        };


        struct TestPropertyDefaultValues : HelperObject // Object
        {
            TestPropertyDefaultValues(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TestPropertyDefaultValues";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Int A() const;
            Ent::Gen::Int B() const;
            Ent::Gen::String _comment() const;
        };

        struct TestPropertyDefaultValues2 : HelperObject // Object
        {
            TestPropertyDefaultValues2(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TestPropertyDefaultValues2";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::TestPropertyDefaultValues propertyWithDefault2() const;
            Ent::Gen::TestPropertyDefaultValues propertyWithDefault3() const;
        };

        struct Terrain_TerrainMeta : HelperObject // Object
        {
            Terrain_TerrainMeta(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/Terrain::TerrainMeta";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String DataPath() const;
            Ent::Gen::Float HeightScaleMeters() const;
            Ent::Gen::String Material() const;
            Ent::Gen::Float RegionWidthMeters() const;
            Ent::Gen::Float SkirtScale() const;
            Ent::Gen::Float TexelsPerMeter() const;
            Ent::Gen::String _comment() const;
        };

        struct TagsList : HelperObject // Object
        {
            TagsList(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/TagsList";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Map<char const*, Ent::Gen::PrimitiveSet<char const*>> Tags() const;
            Ent::Gen::String _comment() const;
        };

        struct TaggedEntityRef : HelperObject // Object
        {
            TaggedEntityRef(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/TaggedEntityRef";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef EntityRef() const;
            PrimArray<Ent::Gen::InventoryTags> Tags() const;
            Ent::Gen::String _comment() const;
        };

        struct SyncTempoMode : EnumPropHelper<SyncTempoMode, SyncTempoModeEnum> // Enum
        {
            using Enum = SyncTempoModeEnum;
            using PropHelper<SyncTempoMode, Enum>::operator=;
            SyncTempoMode(Ent::Node* _node): EnumPropHelper<SyncTempoMode, Enum>(_node) {}
            static constexpr char schemaName[] = "SyncTempoMode";
            static constexpr char const* enumToString[] = {
                "None",
                "OnGrid",
                "OnBeat",
                "OnBar",
                "OnEnterCue",
                "OnExitCue",
                "OnCustomCue",
                "OnSwitchTransition",
                "SyncTempoMode_COUNT",
                "SyncTempoMode_FIRST",
            };
        };
        inline char const* toString(SyncTempoModeEnum value)
        {
            if(size_t(value) >= std::size(SyncTempoMode::enumToString))
                throw std::runtime_error("Wrong enum value");
            return SyncTempoMode::enumToString[size_t(value)];
        }
        inline char const* toInternal(SyncTempoModeEnum value) { return toString(value); }
        template<> inline SyncTempoModeEnum strToEnum<SyncTempoModeEnum>(char const* value)
        {
            return static_cast<SyncTempoModeEnum>(details::indexInEnum(value, SyncTempoMode::enumToString));
        }

        struct StyleMode : EnumPropHelper<StyleMode, StyleModeEnum> // Enum
        {
            using Enum = StyleModeEnum;
            using PropHelper<StyleMode, Enum>::operator=;
            StyleMode(Ent::Node* _node): EnumPropHelper<StyleMode, Enum>(_node) {}
            static constexpr char schemaName[] = "StyleMode";
            static constexpr char const* enumToString[] = {
                "default",
                "stick",
                "sword",
                "do",
                "hammer",
                "knife",
                "squirrel",
                "lush",
                "StyleMode_COUNT",
            };
        };
        inline char const* toString(StyleModeEnum value)
        {
            if(size_t(value) >= std::size(StyleMode::enumToString))
                throw std::runtime_error("Wrong enum value");
            return StyleMode::enumToString[size_t(value)];
        }
        inline char const* toInternal(StyleModeEnum value) { return toString(value); }
        template<> inline StyleModeEnum strToEnum<StyleModeEnum>(char const* value)
        {
            return static_cast<StyleModeEnum>(details::indexInEnum(value, StyleMode::enumToString));
        }

        struct StunData : HelperObject // Object
        {
            StunData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/StunData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Int damageHitBig() const;
            Ent::Gen::Int damageHitBite() const;
            Ent::Gen::Int damageHitEject() const;
            Ent::Gen::Int damageHitEjectFar() const;
            Ent::Gen::Int damageHitLight() const;
            Ent::Gen::Int damageHitMedium() const;
            Ent::Gen::Int malus() const;
            Ent::Gen::Float orientHitBig() const;
            Ent::Gen::Float orientHitEject() const;
            Ent::Gen::Float orientHitEjectFar() const;
            Ent::Gen::Float orientHitLight() const;
            Ent::Gen::Float orientHitMedium() const;
            Ent::Gen::Float recoverTime() const;
            Ent::Gen::Int resistance() const;
            Ent::Gen::Float stunTime() const;
        };

        struct StickToGround : HelperObject // Object
        {
            StickToGround(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/StickToGround";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String BoneNameEnd() const;
            Ent::Gen::String BoneNameStart() const;
            Ent::Gen::String _comment() const;
        };

        struct StateGauge : HelperObject // Object
        {
            StateGauge(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/StateGauge";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float m_amount() const;
            Ent::Gen::Float m_maxAmount() const;
            Ent::Gen::Float m_pendingDiff() const;
        };

        struct StunGauge : HelperObject // Object
        {
            StunGauge(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/StunGauge";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::StateGauge Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SpeedMode : EnumPropHelper<SpeedMode, SpeedModeEnum> // Enum
        {
            using Enum = SpeedModeEnum;
            using PropHelper<SpeedMode, Enum>::operator=;
            SpeedMode(Ent::Node* _node): EnumPropHelper<SpeedMode, Enum>(_node) {}
            static constexpr char schemaName[] = "SpeedMode";
            static constexpr char const* enumToString[] = {
                "speed0",
                "speed1",
                "speed2",
                "speed3",
                "speed4",
                "SpeedMode_COUNT",
            };
        };
        inline char const* toString(SpeedModeEnum value)
        {
            if(size_t(value) >= std::size(SpeedMode::enumToString))
                throw std::runtime_error("Wrong enum value");
            return SpeedMode::enumToString[size_t(value)];
        }
        inline char const* toInternal(SpeedModeEnum value) { return toString(value); }
        template<> inline SpeedModeEnum strToEnum<SpeedModeEnum>(char const* value)
        {
            return static_cast<SpeedModeEnum>(details::indexInEnum(value, SpeedMode::enumToString));
        }

        struct SpeedFastMinDuration : HelperObject // Object
        {
            SpeedFastMinDuration(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool engaged() const;
            Ent::Gen::Float val() const;
        };

        struct Specie : EnumPropHelper<Specie, SpecieEnum> // Enum
        {
            using Enum = SpecieEnum;
            using PropHelper<Specie, Enum>::operator=;
            Specie(Ent::Node* _node): EnumPropHelper<Specie, Enum>(_node) {}
            static constexpr char schemaName[] = "Specie";
            static constexpr char const* enumToString[] = {
                "auroch",
                "bear",
                "babybear",
                "catfish",
                "eagle",
                "elk",
                "fox",
                "giantbear",
                "human",
                "cannibal",
                "babyhuman",
                "horse",
                "ibex",
                "rabbit",
                "rat",
                "ram",
                "raven",
                "schmetre",
                "seagull",
                "snake",
                "spermwhale",
                "squirrel",
                "stag",
                "toad",
                "trout",
                "wildboar",
                "babyboar",
                "wolf",
                "shark",
                "dolphin",
                "whale",
                "goddess",
                "clothboots",
                "clothbrace",
                "clothhelmet",
                "clothskirt",
                "clothtorso",
                "clothbody",
                "weapon",
                "outfit",
                "drivable",
                "fruit",
                "darkstone",
                "destructible",
                "environment",
                "regeneration",
                "insect",
                "Specie_COUNT",
            };
        };
        inline char const* toString(SpecieEnum value)
        {
            if(size_t(value) >= std::size(Specie::enumToString))
                throw std::runtime_error("Wrong enum value");
            return Specie::enumToString[size_t(value)];
        }
        inline char const* toInternal(SpecieEnum value) { return toString(value); }
        template<> inline SpecieEnum strToEnum<SpecieEnum>(char const* value)
        {
            return static_cast<SpecieEnum>(details::indexInEnum(value, Specie::enumToString));
        }

        struct SpawningParameter : HelperObject // Object
        {
            SpawningParameter(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SpawningParameter";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String EntityName() const;
            Ent::Gen::Float MinimumDepth() const;
            Ent::Gen::Float PeriodRandomness() const;
            Ent::Gen::Float SpawningPeriod() const;
            Ent::Gen::String State() const;
            Ent::Gen::String _comment() const;
        };

        struct SoundEventMapping : HelperObject // Object
        {
            SoundEventMapping(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SoundEventMapping";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Map<char const*, Ent::Gen::String> Explicit() const;
            Ent::Gen::PrimitiveSet<char const*> Ignored() const;
            Ent::Gen::Map<char const*, Ent::Gen::String> Prefixed() const;
            Ent::Gen::String _comment() const;
        };

        struct SoundEmissionStrength : EnumPropHelper<SoundEmissionStrength, SoundEmissionStrengthEnum> // Enum
        {
            using Enum = SoundEmissionStrengthEnum;
            using PropHelper<SoundEmissionStrength, Enum>::operator=;
            SoundEmissionStrength(Ent::Node* _node): EnumPropHelper<SoundEmissionStrength, Enum>(_node) {}
            static constexpr char schemaName[] = "SoundEmissionStrength";
            static constexpr char const* enumToString[] = {
                "none",
                "low",
                "medium",
                "high",
                "SoundEmissionStrength_COUNT",
            };
        };
        inline char const* toString(SoundEmissionStrengthEnum value)
        {
            if(size_t(value) >= std::size(SoundEmissionStrength::enumToString))
                throw std::runtime_error("Wrong enum value");
            return SoundEmissionStrength::enumToString[size_t(value)];
        }
        inline char const* toInternal(SoundEmissionStrengthEnum value) { return toString(value); }
        template<> inline SoundEmissionStrengthEnum strToEnum<SoundEmissionStrengthEnum>(char const* value)
        {
            return static_cast<SoundEmissionStrengthEnum>(details::indexInEnum(value, SoundEmissionStrength::enumToString));
        }

        struct ShootSequenceData : HelperObject // Object
        {
            ShootSequenceData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ShootSequenceData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float Param() const;
            Ent::Gen::String Type_() const;
            Ent::Gen::String _comment() const;
        };

        struct ShootData : HelperObject // Object
        {
            ShootData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ShootData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::String ammoName() const;
            Ent::Gen::Float anticipationImprecision() const;
            Ent::Gen::Bool canShoot() const;
            Ent::Gen::Int chargeTierCount() const;
            Ent::Gen::Float gravity() const;
            Ent::Gen::Float lifeCost() const;
            Ent::Gen::Float lifeCostCharged() const;
            Ent::Gen::Float maxChargeDuration() const;
            Ent::Gen::Float maxShootDistance() const;
            Ent::Gen::Float minDelayBetweenShots() const;
            Ent::Gen::Bool randomAngleShoot() const;
            Ent::Gen::Float shootMaxAngle() const;
            Ent::Gen::Float shootSpeed() const;
            Ent::Gen::Float zoneImprecision() const;
        };

        struct SeedPatchData : HelperObject // Object
        {
            SeedPatchData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/SeedPatchData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float NoiseBlur() const;
            Ent::Gen::Float NoiseContrast() const;
            Ent::Gen::Bool NoiseInvert() const;
            Ent::Gen::String NoiseName() const;
            Ent::Gen::Float NoiseOffsetX() const;
            Ent::Gen::Float NoiseOffsetY() const;
            Ent::Gen::Float NoiseOpacity() const;
            Ent::Gen::Float NoisePosition() const;
            Ent::Gen::Float NoiseSizeX() const;
            Ent::Gen::Float NoiseSizeY() const;
            Ent::Gen::String SeedName() const;
            Ent::Gen::String _comment() const;
        };

        struct SeedPatchDataList : HelperObject // Object
        {
            SeedPatchDataList(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/SeedPatchDataList";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::SeedPatchData> Data() const;
            Ent::Gen::String _comment() const;
        };

        struct ScriptPathAndDataSet : HelperObject // Object
        {
            ScriptPathAndDataSet(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ScriptPathAndDataSet";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AutoLaunch() const;
            Ent::Gen::Map<char const*, Ent::Gen::TypedValue> DataMap() const;
            Ent::Gen::String NickName() const;
            Ent::Gen::String Path() const;
            Array<Ent::Gen::ScriptPathAndDataSet> SpawnDataSets() const;
            Ent::Gen::String _comment() const;
        };

        struct ScaleConverter : HelperObject // Object
        {
            ScaleConverter(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ScaleConverter";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::variant_Pasta_Easing_Curve_string_ easing() const;
            Ent::Gen::Vector2 in_() const;
            Ent::Gen::String inText() const;
            Ent::Gen::Vector2 out() const;
            Ent::Gen::String outText() const;
        };

        struct ReviveSide : EnumPropHelper<ReviveSide, ReviveSideEnum> // Enum
        {
            using Enum = ReviveSideEnum;
            using PropHelper<ReviveSide, Enum>::operator=;
            ReviveSide(Ent::Node* _node): EnumPropHelper<ReviveSide, Enum>(_node) {}
            static constexpr char schemaName[] = "ReviveSide";
            static constexpr char const* enumToString[] = {
                "neutral",
                "sacred",
                "cursed",
                "ReviveSide_COUNT",
            };
        };
        inline char const* toString(ReviveSideEnum value)
        {
            if(size_t(value) >= std::size(ReviveSide::enumToString))
                throw std::runtime_error("Wrong enum value");
            return ReviveSide::enumToString[size_t(value)];
        }
        inline char const* toInternal(ReviveSideEnum value) { return toString(value); }
        template<> inline ReviveSideEnum strToEnum<ReviveSideEnum>(char const* value)
        {
            return static_cast<ReviveSideEnum>(details::indexInEnum(value, ReviveSide::enumToString));
        }

        struct RevivedData : HelperObject // Object
        {
            RevivedData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/RevivedData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool CanBeFreed() const;
            Ent::Gen::Float DecreaseOverTimeSpeed() const;
            Ent::Gen::Float LifeMinHysteresis() const;
            Ent::Gen::Float LifeMinReviveSideNeutral() const;
            Ent::Gen::Float NonCreatureConvertRatio() const;
            Ent::Gen::Bool RequestReviveLocked() const;
            Ent::Gen::Float ReviveEnergyMax() const;
            Ent::Gen::Float ReviveSinAmplitude() const;
            Ent::Gen::ReviveSide StartSide() const;
            PrimArray<Ent::Gen::Float> StateThresholds() const;
            Ent::Gen::Float TimeBeforeFree() const;
            Ent::Gen::VomitData VomitData() const;
            Ent::Gen::String _comment() const;
        };

        struct ReviveSideEvent : HelperObject // Object
        {
            ReviveSideEvent(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ReviveSideEvent";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float ElapsedTime() const;
            Ent::Gen::ReviveSide ReviveSide() const;
            Ent::Gen::String _comment() const;
        };

        struct ResponsiblePointer_CineEvent_ : Base // Union
        {
            ResponsiblePointer_CineEvent_(Ent::Node* _node): Base(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ResponsiblePointer&lt;CineEvent&gt;";
            char const* getType() const;
            std::optional<Ent::Gen::CineEventTestCurrentGameState> CineEventTestCurrentGameState() const;
            Ent::Gen::CineEventTestCurrentGameState setCineEventTestCurrentGameState() const;
            std::optional<Ent::Gen::CineEventTestEndCurrentSequence> CineEventTestEndCurrentSequence() const;
            Ent::Gen::CineEventTestEndCurrentSequence setCineEventTestEndCurrentSequence() const;
            std::optional<Ent::Gen::CineEventTestInput> CineEventTestInput() const;
            Ent::Gen::CineEventTestInput setCineEventTestInput() const;
            std::optional<Ent::Gen::CineEventTestIsCanceled> CineEventTestIsCanceled() const;
            Ent::Gen::CineEventTestIsCanceled setCineEventTestIsCanceled() const;
            std::optional<Ent::Gen::CineEventTestWait> CineEventTestWait() const;
            Ent::Gen::CineEventTestWait setCineEventTestWait() const;
            std::optional<Ent::Gen::CineEventTriggerEventHandlerPost> CineEventTriggerEventHandlerPost() const;
            Ent::Gen::CineEventTriggerEventHandlerPost setCineEventTriggerEventHandlerPost() const;
            std::optional<Ent::Gen::CineEventTriggerGameStateChange> CineEventTriggerGameStateChange() const;
            Ent::Gen::CineEventTriggerGameStateChange setCineEventTriggerGameStateChange() const;
            std::optional<Ent::Gen::CineEventTriggerPlaySequence> CineEventTriggerPlaySequence() const;
            Ent::Gen::CineEventTriggerPlaySequence setCineEventTriggerPlaySequence() const;
            std::optional<Ent::Gen::CineEventTriggerPlaySound> CineEventTriggerPlaySound() const;
            Ent::Gen::CineEventTriggerPlaySound setCineEventTriggerPlaySound() const;
        };

        struct ResponsiblePointer_ActorState_ : Base // Union
        {
            ResponsiblePointer_ActorState_(Ent::Node* _node): Base(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ResponsiblePointer&lt;ActorState&gt;";
            char const* getType() const;
            std::optional<Ent::Gen::ActorStateAlive> ActorStateAlive() const;
            Ent::Gen::ActorStateAlive setActorStateAlive() const;
            std::optional<Ent::Gen::ActorStateBeingImmersed> ActorStateBeingImmersed() const;
            Ent::Gen::ActorStateBeingImmersed setActorStateBeingImmersed() const;
            std::optional<Ent::Gen::ActorStateBeingInAir> ActorStateBeingInAir() const;
            Ent::Gen::ActorStateBeingInAir setActorStateBeingInAir() const;
            std::optional<Ent::Gen::ActorStateBeingOnGround> ActorStateBeingOnGround() const;
            Ent::Gen::ActorStateBeingOnGround setActorStateBeingOnGround() const;
            std::optional<Ent::Gen::ActorStateBuried> ActorStateBuried() const;
            Ent::Gen::ActorStateBuried setActorStateBuried() const;
            std::optional<Ent::Gen::ActorStateDead> ActorStateDead() const;
            Ent::Gen::ActorStateDead setActorStateDead() const;
            std::optional<Ent::Gen::ActorStateHasNoBody> ActorStateHasNoBody() const;
            Ent::Gen::ActorStateHasNoBody setActorStateHasNoBody() const;
            std::optional<Ent::Gen::ActorStateHoldingItem> ActorStateHoldingItem() const;
            Ent::Gen::ActorStateHoldingItem setActorStateHoldingItem() const;
            std::optional<Ent::Gen::ActorStateInvincible> ActorStateInvincible() const;
            Ent::Gen::ActorStateInvincible setActorStateInvincible() const;
            std::optional<Ent::Gen::ActorStateRegenerationFull> ActorStateRegenerationFull() const;
            Ent::Gen::ActorStateRegenerationFull setActorStateRegenerationFull() const;
            std::optional<Ent::Gen::ActorStateRegenerationLow> ActorStateRegenerationLow() const;
            Ent::Gen::ActorStateRegenerationLow setActorStateRegenerationLow() const;
            std::optional<Ent::Gen::ActorStateTeleport> ActorStateTeleport() const;
            Ent::Gen::ActorStateTeleport setActorStateTeleport() const;
            std::optional<Ent::Gen::EntityStateBoidsHomePos> EntityStateBoidsHomePos() const;
            Ent::Gen::EntityStateBoidsHomePos setEntityStateBoidsHomePos() const;
            std::optional<Ent::Gen::EntityStateEnergyRootState> EntityStateEnergyRootState() const;
            Ent::Gen::EntityStateEnergyRootState setEntityStateEnergyRootState() const;
            std::optional<Ent::Gen::EntityStateEnergySpoutState> EntityStateEnergySpoutState() const;
            Ent::Gen::EntityStateEnergySpoutState setEntityStateEnergySpoutState() const;
            std::optional<Ent::Gen::EntityStateForceCanBeTargeted> EntityStateForceCanBeTargeted() const;
            Ent::Gen::EntityStateForceCanBeTargeted setEntityStateForceCanBeTargeted() const;
            std::optional<Ent::Gen::EntityStateMask> EntityStateMask() const;
            Ent::Gen::EntityStateMask setEntityStateMask() const;
            std::optional<Ent::Gen::EntityStatePlayer> EntityStatePlayer() const;
            Ent::Gen::EntityStatePlayer setEntityStatePlayer() const;
            std::optional<Ent::Gen::EntityStateVoxelsVolume> EntityStateVoxelsVolume() const;
            Ent::Gen::EntityStateVoxelsVolume setEntityStateVoxelsVolume() const;
        };

        struct RegenSwitchBehavior : EnumPropHelper<RegenSwitchBehavior, RegenSwitchBehaviorEnum> // Enum
        {
            using Enum = RegenSwitchBehaviorEnum;
            using PropHelper<RegenSwitchBehavior, Enum>::operator=;
            RegenSwitchBehavior(Ent::Node* _node): EnumPropHelper<RegenSwitchBehavior, Enum>(_node) {}
            static constexpr char schemaName[] = "RegenSwitchBehavior";
            static constexpr char const* enumToString[] = {
                "CrossFade",
                "CrossMetamorphosis",
                "SequentialMetamorphosis",
            };
        };
        inline char const* toString(RegenSwitchBehaviorEnum value)
        {
            if(size_t(value) >= std::size(RegenSwitchBehavior::enumToString))
                throw std::runtime_error("Wrong enum value");
            return RegenSwitchBehavior::enumToString[size_t(value)];
        }
        inline char const* toInternal(RegenSwitchBehaviorEnum value) { return toString(value); }
        template<> inline RegenSwitchBehaviorEnum strToEnum<RegenSwitchBehaviorEnum>(char const* value)
        {
            return static_cast<RegenSwitchBehaviorEnum>(details::indexInEnum(value, RegenSwitchBehavior::enumToString));
        }


        struct sPhysicsJointDesc : HelperObject // Object
        {
            sPhysicsJointDesc(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sPhysicsJointDesc";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::sJointBallDesc Ball() const;
            Ent::Gen::sJointFixedDesc Fixed() const;
            Ent::Gen::sJointHingeDesc Hinge() const;
            Ent::Gen::String JointType() const;
            Ent::Gen::sJointSliderDesc Slider() const;
            Ent::Gen::sJointSwingTwistDesc SwingTwist() const;
            Ent::Gen::sJointUniversalDesc Universal() const;
            Ent::Gen::String _comment() const;
            PrimArray<Ent::Gen::String> flags() const;
            Ent::Gen::Int idRigodBodyA() const;
            Ent::Gen::Int idRigodBodyB() const;
            Ent::Gen::Quat orientation() const;
            Ent::Gen::String parent() const;
            Ent::Gen::Vector3 translation() const;
        };

        struct sPhysicShape : HelperObject // Object
        {
            sPhysicShape(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sPhysicShape";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::sPhysicsShapeBox Box() const;
            Ent::Gen::sPhysicsShapeCapsule Capsule() const;
            Ent::Gen::sPhysicsShapeCylinder Cylinder() const;
            Ent::Gen::sPhysicsShapeMesh Mesh() const;
            Ent::Gen::String PhysicsMaterial() const;
            Ent::Gen::sPhysicsShapeSphere Sphere() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Vector3 angles() const;
            Ent::Gen::Quat orientation() const;
            Ent::Gen::Float scale() const;
            Ent::Gen::Vector3 translation() const;
        };

        struct sRigidBodyDesc : HelperObject // Object
        {
            sRigidBodyDesc(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/sRigidBodyDesc";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Vector3 angles() const;
            PrimArray<Ent::Gen::String> flags() const;
            Ent::Gen::Int id() const;
            Ent::Gen::String motionType() const;
            Ent::Gen::Quat orientation() const;
            Ent::Gen::String parent() const;
            Ent::Gen::Float scale() const;
            Array<Ent::Gen::sPhysicShape> shapes() const;
            Ent::Gen::Vector3 translation() const;
        };

        struct Transform3D : HelperObject // Object
        {
            Transform3D(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/Transform3D";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Quat orientation() const;
            Ent::Gen::Vector3 scale() const;
            Ent::Gen::Vector3 translation() const;
        };

        struct ProgressSoundEventData : HelperObject // Object
        {
            ProgressSoundEventData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ProgressSoundEventData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String DecreaseEventName() const;
            Ent::Gen::Float DecreaseStartThreshold() const;
            Ent::Gen::Float DecreaseStopThreshold() const;
            Ent::Gen::String EventBank() const;
            Ent::Gen::Bool EventLooping() const;
            Ent::Gen::String IncreaseEventName() const;
            Ent::Gen::Float IncreaseStartThreshold() const;
            Ent::Gen::Float IncreaseStopThreshold() const;
            Ent::Gen::String _comment() const;
        };

        struct PrimitiveData : HelperObject // Object
        {
            PrimitiveData(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::Float Height() const;
            Ent::Gen::Float Length() const;
            Ent::Gen::Float Radius() const;
            Ent::Gen::Float Width() const;
            Ent::Gen::String _comment() const;
        };

        struct PrimitiveColliderType : EnumPropHelper<PrimitiveColliderType, PrimitiveColliderTypeEnum> // Enum
        {
            using Enum = PrimitiveColliderTypeEnum;
            using PropHelper<PrimitiveColliderType, Enum>::operator=;
            PrimitiveColliderType(Ent::Node* _node): EnumPropHelper<PrimitiveColliderType, Enum>(_node) {}
            static constexpr char schemaName[] = "PrimitiveColliderType";
            static constexpr char const* enumToString[] = {
                "Undefined",
                "Sphere",
                "Box",
                "Capsule",
                "Cylinder",
                "Mesh",
                "PrimitiveColliderType_COUNT",
            };
        };
        inline char const* toString(PrimitiveColliderTypeEnum value)
        {
            if(size_t(value) >= std::size(PrimitiveColliderType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return PrimitiveColliderType::enumToString[size_t(value)];
        }
        inline char const* toInternal(PrimitiveColliderTypeEnum value) { return toString(value); }
        template<> inline PrimitiveColliderTypeEnum strToEnum<PrimitiveColliderTypeEnum>(char const* value)
        {
            return static_cast<PrimitiveColliderTypeEnum>(details::indexInEnum(value, PrimitiveColliderType::enumToString));
        }

        struct PredictionBehaviorDuration : HelperObject // Object
        {
            PredictionBehaviorDuration(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PredictionBehaviorDuration";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float Locked() const;
            Ent::Gen::Float Step() const;
            Ent::Gen::Float Total() const;
            Ent::Gen::String _comment() const;
        };

        struct PredictionBehaviorData : HelperObject // Object
        {
            PredictionBehaviorData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PredictionBehaviorData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::PredictionBehaviorDuration Duration() const;
            Ent::Gen::String _comment() const;
        };

        struct Precision : EnumPropHelper<Precision, PrecisionEnum> // Enum
        {
            using Enum = PrecisionEnum;
            using PropHelper<Precision, Enum>::operator=;
            Precision(Ent::Node* _node): EnumPropHelper<Precision, Enum>(_node) {}
            static constexpr char schemaName[] = "Precision";
            static constexpr char const* enumToString[] = {
                "full",
                "half",
                "quarter",
                "eighth",
                "sixteenth",
                "highest",
                "lowest",
            };
        };
        inline char const* toString(PrecisionEnum value)
        {
            if(size_t(value) >= std::size(Precision::enumToString))
                throw std::runtime_error("Wrong enum value");
            return Precision::enumToString[size_t(value)];
        }
        inline char const* toInternal(PrecisionEnum value) { return toString(value); }
        template<> inline PrecisionEnum strToEnum<PrecisionEnum>(char const* value)
        {
            return static_cast<PrecisionEnum>(details::indexInEnum(value, Precision::enumToString));
        }


        struct OutfitPieceType : EnumPropHelper<OutfitPieceType, OutfitPieceTypeEnum> // Enum
        {
            using Enum = OutfitPieceTypeEnum;
            using PropHelper<OutfitPieceType, Enum>::operator=;
            OutfitPieceType(Ent::Node* _node): EnumPropHelper<OutfitPieceType, Enum>(_node) {}
            static constexpr char schemaName[] = "OutfitPieceType";
            static constexpr char const* enumToString[] = {
                "OutfitPieceType_NONE",
                "Head",
                "Torso",
                "Skirt",
                "Boots",
                "Brace",
                "Body",
                "Hair",
                "OutfitPieceType_COUNT",
            };
        };
        inline char const* toString(OutfitPieceTypeEnum value)
        {
            if(size_t(value) >= std::size(OutfitPieceType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return OutfitPieceType::enumToString[size_t(value)];
        }
        inline char const* toInternal(OutfitPieceTypeEnum value) { return toString(value); }
        template<> inline OutfitPieceTypeEnum strToEnum<OutfitPieceTypeEnum>(char const* value)
        {
            return static_cast<OutfitPieceTypeEnum>(details::indexInEnum(value, OutfitPieceType::enumToString));
        }

        struct OutfitPiece : HelperObject // Object
        {
            OutfitPiece(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/OutfitPiece";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef EntityRef() const;
            Ent::Gen::OutfitPieceType Slot() const;
            Ent::Gen::String _comment() const;
        };

        struct Orientation : HelperObject // Object
        {
            Orientation(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool engaged() const;
            Ent::Gen::Quat val() const;
        };

        struct Object_MaxActivationLevel : EnumPropHelper<Object_MaxActivationLevel, Object_MaxActivationLevelEnum> // Enum
        {
            using Enum = Object_MaxActivationLevelEnum;
            using PropHelper<Object_MaxActivationLevel, Enum>::operator=;
            Object_MaxActivationLevel(Ent::Node* _node): EnumPropHelper<Object_MaxActivationLevel, Enum>(_node) {}
            
            static constexpr char const* enumToString[] = {
                "Created",
                "InWorld",
                "Loading",
                "Started",
            };
        };
        inline char const* toString(Object_MaxActivationLevelEnum value)
        {
            if(size_t(value) >= std::size(Object_MaxActivationLevel::enumToString))
                throw std::runtime_error("Wrong enum value");
            return Object_MaxActivationLevel::enumToString[size_t(value)];
        }
        inline char const* toInternal(Object_MaxActivationLevelEnum value) { return toString(value); }
        template<> inline Object_MaxActivationLevelEnum strToEnum<Object_MaxActivationLevelEnum>(char const* value)
        {
            return static_cast<Object_MaxActivationLevelEnum>(details::indexInEnum(value, Object_MaxActivationLevel::enumToString));
        }

        struct NavmeshGenerationParameters : HelperObject // Object
        {
            NavmeshGenerationParameters(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/NavmeshGenerationParameters";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float CreatureHeight() const;
            Ent::Gen::Float CreatureRadius() const;
            Ent::Gen::Bool MarkWaterAreas() const;
            Ent::Gen::Float MaxClimbHeight() const;
            Ent::Gen::Float MaxWalkableSlopeAngle() const;
            Ent::Gen::Float MinWaterDepth() const;
            PrimArray<Ent::Gen::String> SizeLayerMask() const;
            Ent::Gen::Float TileWorldSize() const;
            Ent::Gen::String _comment() const;
        };

        struct MoveCapacityData_OrientationSpeed : HelperObject // Object
        {
            MoveCapacityData_OrientationSpeed(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MoveCapacityData::OrientationSpeed";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Vector3 factor() const;
            Ent::Gen::Vector3 rate() const;
            Ent::Gen::ScaleConverter rotationRollFromAngularSpeed() const;
            Ent::Gen::ScaleConverter speedFactorFromSpeedSlow() const;
            Ent::Gen::Vector3 speedMax() const;
            Ent::Gen::Vector3 steeringAngle() const;
        };

        struct MountableSnapLine_ControlPoint : HelperObject // Object
        {
            MountableSnapLine_ControlPoint(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MountableSnapLine::ControlPoint";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Int boneId() const;
            Ent::Gen::Vector3 offset() const;
            Ent::Gen::Float radius() const;
        };

        struct MountData : HelperObject // Object
        {
            MountData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MountData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float acrobaticJumpDistance() const;
            Ent::Gen::Float angle() const;
            Ent::Gen::Float blindAngle() const;
            Ent::Gen::Float distance() const;
            Ent::Gen::Float offset() const;
        };

        struct MeshesItem : HelperObject // Object
        {
            MeshesItem(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String _comment() const;
            Ent::Gen::String mesh() const;
        };

        struct RUNTIME_LODsItem : HelperObject // Object
        {
            RUNTIME_LODsItem(Ent::Node* _node): HelperObject(_node) {}
            
            Array<Ent::Gen::MeshesItem> Meshes() const;
            Ent::Gen::String _comment() const;
        };

        struct MeshNavigationAllowedMode : EnumPropHelper<MeshNavigationAllowedMode, MeshNavigationAllowedModeEnum> // Enum
        {
            using Enum = MeshNavigationAllowedModeEnum;
            using PropHelper<MeshNavigationAllowedMode, Enum>::operator=;
            MeshNavigationAllowedMode(Ent::Node* _node): EnumPropHelper<MeshNavigationAllowedMode, Enum>(_node) {}
            static constexpr char schemaName[] = "MeshNavigationAllowedMode";
            static constexpr char const* enumToString[] = {
                "Never",
                "PlayerOnly",
                "Always",
                "MeshNavigationAllowedMode_COUNT",
            };
        };
        inline char const* toString(MeshNavigationAllowedModeEnum value)
        {
            if(size_t(value) >= std::size(MeshNavigationAllowedMode::enumToString))
                throw std::runtime_error("Wrong enum value");
            return MeshNavigationAllowedMode::enumToString[size_t(value)];
        }
        inline char const* toInternal(MeshNavigationAllowedModeEnum value) { return toString(value); }
        template<> inline MeshNavigationAllowedModeEnum strToEnum<MeshNavigationAllowedModeEnum>(char const* value)
        {
            return static_cast<MeshNavigationAllowedModeEnum>(details::indexInEnum(value, MeshNavigationAllowedMode::enumToString));
        }

        struct MeshNavigationBehaviorData : HelperObject // Object
        {
            MeshNavigationBehaviorData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MeshNavigationBehaviorData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool EdgeTransitionConstraintAllowed() const;
            Ent::Gen::Float EdgeTransitionConstraintLedgeAngle() const;
            Ent::Gen::Float EdgeTransitionConstraintWallAngle() const;
            Ent::Gen::Float MaxNormalAngle() const;
            Ent::Gen::MeshNavigationAllowedMode MeshNavigationAllowedMode() const;
            Ent::Gen::Float RayCastLengthLegFactor() const;
            Ent::Gen::Float RayCastLengthSpeedFactor() const;
            Ent::Gen::Bool RollAllowed() const;
            Ent::Gen::Bool StickToAnyNormalAllowed() const;
            Ent::Gen::String _comment() const;
        };

        struct MenaceSelection : EnumPropHelper<MenaceSelection, MenaceSelectionEnum> // Enum
        {
            using Enum = MenaceSelectionEnum;
            using PropHelper<MenaceSelection, Enum>::operator=;
            MenaceSelection(Ent::Node* _node): EnumPropHelper<MenaceSelection, Enum>(_node) {}
            static constexpr char schemaName[] = "MenaceSelection";
            static constexpr char const* enumToString[] = {
                "closest",
                "weakest",
                "strongest",
                "MenaceSelection_COUNT",
            };
        };
        inline char const* toString(MenaceSelectionEnum value)
        {
            if(size_t(value) >= std::size(MenaceSelection::enumToString))
                throw std::runtime_error("Wrong enum value");
            return MenaceSelection::enumToString[size_t(value)];
        }
        inline char const* toInternal(MenaceSelectionEnum value) { return toString(value); }
        template<> inline MenaceSelectionEnum strToEnum<MenaceSelectionEnum>(char const* value)
        {
            return static_cast<MenaceSelectionEnum>(details::indexInEnum(value, MenaceSelection::enumToString));
        }

        struct MaxActivationLevel : EnumPropHelper<MaxActivationLevel, MaxActivationLevelEnum> // Enum
        {
            using Enum = MaxActivationLevelEnum;
            using PropHelper<MaxActivationLevel, Enum>::operator=;
            MaxActivationLevel(Ent::Node* _node): EnumPropHelper<MaxActivationLevel, Enum>(_node) {}
            
            static constexpr char const* enumToString[] = {
                "Created",
                "InWorld",
                "Loading",
                "Started",
            };
        };
        inline char const* toString(MaxActivationLevelEnum value)
        {
            if(size_t(value) >= std::size(MaxActivationLevel::enumToString))
                throw std::runtime_error("Wrong enum value");
            return MaxActivationLevel::enumToString[size_t(value)];
        }
        inline char const* toInternal(MaxActivationLevelEnum value) { return toString(value); }
        template<> inline MaxActivationLevelEnum strToEnum<MaxActivationLevelEnum>(char const* value)
        {
            return static_cast<MaxActivationLevelEnum>(details::indexInEnum(value, MaxActivationLevel::enumToString));
        }


        struct VolumeConstraintDataGD : HelperObject // Object
        {
            VolumeConstraintDataGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/VolumeConstraintDataGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Matrix44 Matrix() const;
            Ent::Gen::TransitionNeighborData Neighbors() const;
            Ent::Gen::Vector3 Size() const;
            PrimArray<Ent::Gen::String> Tags() const;
            Ent::Gen::String _comment() const;
        };


        struct LocomotionMode : EnumPropHelper<LocomotionMode, LocomotionModeEnum> // Enum
        {
            using Enum = LocomotionModeEnum;
            using PropHelper<LocomotionMode, Enum>::operator=;
            LocomotionMode(Ent::Node* _node): EnumPropHelper<LocomotionMode, Enum>(_node) {}
            static constexpr char schemaName[] = "LocomotionMode";
            static constexpr char const* enumToString[] = {
                "standup",
                "quadstandup",
                "crouch",
                "prone",
                "swim",
                "ride",
                "fly",
                "dive",
                "fall",
                "cinematic",
                "ridden",
                "riddenfly",
                "clamber",
                "buried",
                "count",
            };
        };
        inline char const* toString(LocomotionModeEnum value)
        {
            if(size_t(value) >= std::size(LocomotionMode::enumToString))
                throw std::runtime_error("Wrong enum value");
            return LocomotionMode::enumToString[size_t(value)];
        }
        inline char const* toInternal(LocomotionModeEnum value) { return toString(value); }
        template<> inline LocomotionModeEnum strToEnum<LocomotionModeEnum>(char const* value)
        {
            return static_cast<LocomotionModeEnum>(details::indexInEnum(value, LocomotionMode::enumToString));
        }

        struct MoveCapacityData_ReachSpeed : HelperObject // Object
        {
            MoveCapacityData_ReachSpeed(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MoveCapacityData::ReachSpeed";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float acceleration() const;
            Ent::Gen::Float deceleration() const;
            Ent::Gen::LocomotionMode name() const;
        };

        struct ListItem : HelperObject // Object
        {
            ListItem(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String EntityPath() const;
            Ent::Gen::EntityRef EntityRef() const;
            Ent::Gen::String Tag() const;
            Ent::Gen::String Thumbnail() const;
            Ent::Gen::String _comment() const;
        };

        struct LightType : EnumPropHelper<LightType, LightTypeEnum> // Enum
        {
            using Enum = LightTypeEnum;
            using PropHelper<LightType, Enum>::operator=;
            LightType(Ent::Node* _node): EnumPropHelper<LightType, Enum>(_node) {}
            static constexpr char schemaName[] = "LightType";
            static constexpr char const* enumToString[] = {
                "Omni",
                "Hemi",
                "Spot",
                "Dir",
                "LightType_Count",
            };
        };
        inline char const* toString(LightTypeEnum value)
        {
            if(size_t(value) >= std::size(LightType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return LightType::enumToString[size_t(value)];
        }
        inline char const* toInternal(LightTypeEnum value) { return toString(value); }
        template<> inline LightTypeEnum strToEnum<LightTypeEnum>(char const* value)
        {
            return static_cast<LightTypeEnum>(details::indexInEnum(value, LightType::enumToString));
        }

        struct LifeAndDamageData : HelperObject // Object
        {
            LifeAndDamageData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/LifeAndDamageData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float attackCancelThreshold() const;
            Ent::Gen::Float damageThreshold() const;
            Ent::Gen::Float dyingSolidity() const;
            Ent::Gen::Float energyMax() const;
            Ent::Gen::Float energyRecoverSpeed() const;
            PrimArray<Ent::Gen::Float> impactPercent() const;
            Ent::Gen::Float lifeInjuredCoeff() const;
            Ent::Gen::Float lifeMax() const;
            Ent::Gen::Float lifeRecoverSpeed() const;
            Ent::Gen::Float lifeStunCoeff() const;
            Ent::Gen::Float minLifeWhenSpending() const;
            Ent::Gen::Bool shouldCrashWhenFlyingInjured() const;
            Ent::Gen::Float solidity() const;
            Ent::Gen::Bool unbreakable() const;
            Ent::Gen::Float velocityDamageMax() const;
            Ent::Gen::Float velocityImpactMax() const;
        };

        struct LastAliveReviveSide : HelperObject // Object
        {
            LastAliveReviveSide(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool engaged() const;
            Ent::Gen::ReviveSide val() const;
        };

        struct InteractData : HelperObject // Object
        {
            InteractData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/InteractData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float distance() const;
        };

        struct InputCollisionBehaviorData : HelperObject // Object
        {
            InputCollisionBehaviorData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/InputCollisionBehaviorData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float AltitudeMax() const;
            Ent::Gen::Float DepthMax() const;
            Ent::Gen::Float FrontAngle() const;
            Ent::Gen::Float RadiusCoeff() const;
            Ent::Gen::String _comment() const;
        };

        struct ImmersedBehaviorData : HelperObject // Object
        {
            ImmersedBehaviorData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ImmersedBehaviorData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float depth() const;
            Ent::Gen::Float depthHysteresisCoeff() const;
            Ent::Gen::ScaleConverter depthMaxRange() const;
            Ent::Gen::Float flotation() const;
            Ent::Gen::Bool isAllowed() const;
            Ent::Gen::Float minTooDeepPushSpeed() const;
            Ent::Gen::Float reachSurfaceAccelerationCoeff() const;
        };

        struct HotSpotType : EnumPropHelper<HotSpotType, HotSpotTypeEnum> // Enum
        {
            using Enum = HotSpotTypeEnum;
            using PropHelper<HotSpotType, Enum>::operator=;
            HotSpotType(Ent::Node* _node): EnumPropHelper<HotSpotType, Enum>(_node) {}
            static constexpr char schemaName[] = "HotSpotType";
            static constexpr char const* enumToString[] = {
                "all",
                "none",
                "back",
                "beam",
                "bite",
                "biter",
                "breakablestrong",
                "breakableweak",
                "camera",
                "center",
                "head",
                "heal",
                "ride",
                "root",
                "snap",
                "slot",
                "spawnlife",
                "shoot",
                "take",
                "takehandle",
                "vertebra",
                "respawnslot",
                "HotSpotType_COUNT",
            };
        };
        inline char const* toString(HotSpotTypeEnum value)
        {
            if(size_t(value) >= std::size(HotSpotType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return HotSpotType::enumToString[size_t(value)];
        }
        inline char const* toInternal(HotSpotTypeEnum value) { return toString(value); }
        template<> inline HotSpotTypeEnum strToEnum<HotSpotTypeEnum>(char const* value)
        {
            return static_cast<HotSpotTypeEnum>(details::indexInEnum(value, HotSpotType::enumToString));
        }

        struct PickableDistributorComponentData : HelperObject // Object
        {
            PickableDistributorComponentData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PickableDistributorComponentData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef EntityRef() const;
            Ent::Gen::HotSpotType HotspotType() const;
            Ent::Gen::String _comment() const;
        };

        struct HotspotData : HelperObject // Object
        {
            HotspotData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HotspotData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String Bone() const;
            Ent::Gen::Vector3 Offset() const;
            Ent::Gen::Quat Orientation() const;
            Ent::Gen::Float Scale() const;
            Ent::Gen::PrimitiveSet<char const*> Tags() const;
            Ent::Gen::EntityRef TargetEntityRef() const;
            Ent::Gen::HotSpotType Type_() const;
            Ent::Gen::String _comment() const;
        };

        struct HeadCollisionBehaviorData : HelperObject // Object
        {
            HeadCollisionBehaviorData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HeadCollisionBehaviorData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float disableDuration() const;
            Ent::Gen::Float enableDuration() const;
            Ent::Gen::Vector3 headOffset() const;
            Ent::Gen::Bool isEnabled() const;
            Ent::Gen::Float radiusCoeff() const;
            Ent::Gen::ScaleConverter slopeInfluence() const;
            Ent::Gen::Float softCollisionRigidbodyCoeff() const;
            Ent::Gen::Float softCollisionVisualCoeff() const;
            Ent::Gen::ScaleConverter speedInfluence() const;
            Ent::Gen::ScaleConverter visualSmoothOut() const;
        };

        struct GrowingState : EnumPropHelper<GrowingState, GrowingStateEnum> // Enum
        {
            using Enum = GrowingStateEnum;
            using PropHelper<GrowingState, Enum>::operator=;
            GrowingState(Ent::Node* _node): EnumPropHelper<GrowingState, Enum>(_node) {}
            static constexpr char schemaName[] = "GrowingState";
            static constexpr char const* enumToString[] = {
                "invalid",
                "nogrow",
                "growing",
                "grown",
                "manualgrow",
                "degrowing",
                "GrowingState_COUNT",
            };
        };
        inline char const* toString(GrowingStateEnum value)
        {
            if(size_t(value) >= std::size(GrowingState::enumToString))
                throw std::runtime_error("Wrong enum value");
            return GrowingState::enumToString[size_t(value)];
        }
        inline char const* toInternal(GrowingStateEnum value) { return toString(value); }
        template<> inline GrowingStateEnum strToEnum<GrowingStateEnum>(char const* value)
        {
            return static_cast<GrowingStateEnum>(details::indexInEnum(value, GrowingState::enumToString));
        }

        struct GPEType : EnumPropHelper<GPEType, GPETypeEnum> // Enum
        {
            using Enum = GPETypeEnum;
            using PropHelper<GPEType, Enum>::operator=;
            GPEType(Ent::Node* _node): EnumPropHelper<GPEType, Enum>(_node) {}
            static constexpr char schemaName[] = "GPEType";
            static constexpr char const* enumToString[] = {
                "BendTree",
                "Geyser",
                "PossessFlocking",
                "GPEType_COUNT",
            };
        };
        inline char const* toString(GPETypeEnum value)
        {
            if(size_t(value) >= std::size(GPEType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return GPEType::enumToString[size_t(value)];
        }
        inline char const* toInternal(GPETypeEnum value) { return toString(value); }
        template<> inline GPETypeEnum strToEnum<GPETypeEnum>(char const* value)
        {
            return static_cast<GPETypeEnum>(details::indexInEnum(value, GPEType::enumToString));
        }

        struct FusionData : HelperObject // Object
        {
            FusionData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FusionData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool IsSoul() const;
            Ent::Gen::EntityRef SoulEntityRef() const;
            Ent::Gen::Float WarriorDamageFactor() const;
            Ent::Gen::Float WarriorImpactFactor() const;
            Ent::Gen::String _comment() const;
        };

        struct FreezeData : HelperObject // Object
        {
            FreezeData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FreezeData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float deltaTimeFactor() const;
            Ent::Gen::eventStringHash eventStringHash() const;
            Ent::Gen::Float stateDuration() const;
            Ent::Gen::Float transitionInDuration() const;
            Ent::Gen::Float transitionOutDuration() const;
        };

        struct ProjectileData : HelperObject // Object
        {
            ProjectileData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ProjectileData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool canCollideWithOtherProjectiles() const;
            Ent::Gen::Float damages() const;
            Ent::Gen::Float deleteAfterPlantTimer() const;
            Ent::Gen::Bool destroyOnHit() const;
            Ent::Gen::Float distanceFromBodyAtLaunch() const;
            Ent::Gen::Bool explodeOnFire() const;
            Ent::Gen::Float explosionShockForce() const;
            Ent::Gen::FreezeData freezeData() const;
            PrimArray<Ent::Gen::String> gameEffectOnHit() const;
            Ent::Gen::Float gravity() const;
            Ent::Gen::Bool hasNoCollision() const;
            Ent::Gen::Vector3 hitSourceOffset() const;
            Ent::Gen::Float homingInRangeAnticipationDist() const;
            Ent::Gen::Float homingMaxAngle() const;
            Ent::Gen::Float homingMaxFlightTime() const;
            Ent::Gen::Float homingMaxInFrontAnticipationDist() const;
            Ent::Gen::Float homingMaxTotalAnticipationDist() const;
            PrimArray<Ent::Gen::Float> homingTotalAnticipationRatioSpeeds() const;
            Ent::Gen::Float impact() const;
            Ent::Gen::Bool isRegenProjectile() const;
            Ent::Gen::Bool isThrowable() const;
            Ent::Gen::Vector3 launchRotation() const;
            Ent::Gen::Float launchSpeed() const;
            Ent::Gen::Float noiseLevelOnImpact() const;
            Ent::Gen::Bool shouldBeVisibleBeforeShoot() const;
            Ent::Gen::Float smoothTime() const;
            Ent::Gen::Bool stopOnWater() const;
            Ent::Gen::Float straightDistance() const;
            Ent::Gen::Bool visibleInFlight() const;
        };

        struct FluidVolumeComponentGD_SimulationParameters : HelperObject // Object
        {
            FluidVolumeComponentGD_SimulationParameters(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::SimulationParameters";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float Evaporation() const;
            Ent::Gen::Float Momentum() const;
            Ent::Gen::Float Precision() const;
            Ent::Gen::Float Viscosity() const;
            Ent::Gen::String _comment() const;
        };

        struct FluidVolumeComponentGD_HeightMapData : HelperObject // Object
        {
            FluidVolumeComponentGD_HeightMapData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::HeightMapData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String Path() const;
            Ent::Gen::String TerrainName() const;
            Ent::Gen::Vector2 WorldSize() const;
            Ent::Gen::String _comment() const;
        };

        struct FluidVolumeComponentGD_FluidVolumeData : HelperObject // Object
        {
            FluidVolumeComponentGD_FluidVolumeData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::FluidVolumeData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::FluidVolumeComponentGD_HeightMapData HeightMap() const;
            Ent::Gen::Vector2 InHeightMapWorldSizeOffset() const;
            Ent::Gen::String Material() const;
            Ent::Gen::FluidVolumeComponentGD_SimulationParameters Simulation() const;
            Ent::Gen::Vector2 WorldSize() const;
            Ent::Gen::String _comment() const;
        };

        struct FluidType : EnumPropHelper<FluidType, FluidTypeEnum> // Enum
        {
            using Enum = FluidTypeEnum;
            using PropHelper<FluidType, Enum>::operator=;
            FluidType(Ent::Node* _node): EnumPropHelper<FluidType, Enum>(_node) {}
            static constexpr char schemaName[] = "FluidType";
            static constexpr char const* enumToString[] = {
                "water",
                "lava",
                "mud",
                "FluidType_COUNT",
            };
        };
        inline char const* toString(FluidTypeEnum value)
        {
            if(size_t(value) >= std::size(FluidType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return FluidType::enumToString[size_t(value)];
        }
        inline char const* toInternal(FluidTypeEnum value) { return toString(value); }
        template<> inline FluidTypeEnum strToEnum<FluidTypeEnum>(char const* value)
        {
            return static_cast<FluidTypeEnum>(details::indexInEnum(value, FluidType::enumToString));
        }

        struct FloatRange : HelperObject // Object
        {
            FloatRange(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FloatRange";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Vector2 MinMax() const;
            Ent::Gen::String _comment() const;
        };

        struct VegetationPCloudData : HelperObject // Object
        {
            VegetationPCloudData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/VegetationPCloudData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String PCloudPath() const;
            Ent::Gen::FloatRange RegenRange() const;
            PrimArray<Ent::Gen::String> UsedVegetations() const;
            Ent::Gen::String _comment() const;
        };

        struct EventCameraData : HelperObject // Object
        {
            EventCameraData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EventCameraData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float BlendCameraTime() const;
            Ent::Gen::Bool CameraAimTriggerActor() const;
            Array<Ent::Gen::Vector3> CameraOffsets() const;
            Ent::Gen::Float DOFFarStart() const;
            Ent::Gen::Float DOFFarStop() const;
            Ent::Gen::Float DOFMultiplier() const;
            Ent::Gen::Float DOFNearStart() const;
            Ent::Gen::Float DOFNearStop() const;
            Ent::Gen::Bool DOFRelativeTarget() const;
            Ent::Gen::Float EventCameraTime() const;
            Ent::Gen::Float FOV() const;
            Ent::Gen::Bool FixedCam() const;
            Ent::Gen::Bool FollowCam() const;
            Ent::Gen::Bool FollowTarget() const;
            Ent::Gen::Float OffsetsBlendTime() const;
            Ent::Gen::Bool PositionsAngularBlend() const;
            Ent::Gen::Float PositionsBlendTime() const;
            Array<Ent::Gen::Vector3> TargetOffsets() const;
            Ent::Gen::Bool UseDOF() const;
            Ent::Gen::Bool UseOffsetsSpline() const;
            Ent::Gen::Bool UsePositionsSpline() const;
            Ent::Gen::Bool UseTriggerActorPosition() const;
            Ent::Gen::Bool UseTriggerActorSight() const;
            Ent::Gen::String _comment() const;
        };

        struct EntityLODData : HelperObject // Object
        {
            EntityLODData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EntityLODData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef EntityRef() const;
            Ent::Gen::Float MaxDist() const;
            Ent::Gen::String _comment() const;
        };

        struct RegenData : HelperObject // Object
        {
            RegenData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/RegenData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::EntityLODData> LODData() const;
            Ent::Gen::FloatRange RegenRange() const;
            Ent::Gen::Float RegenRangeHysteresis() const;
            Ent::Gen::String _comment() const;
        };

        struct EDITOR_Mesh : HelperObject // Object
        {
            EDITOR_Mesh(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/EDITOR_Mesh";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Int id() const;
            Ent::Gen::String path() const;
        };

        struct EDITOR_LODsItem : HelperObject // Object
        {
            EDITOR_LODsItem(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String _comment() const;
            Ent::Gen::Int lod() const;
            PrimArray<Ent::Gen::String> wvis() const;
        };

        struct DisplaceNoiseListItem : HelperObject // Object
        {
            DisplaceNoiseListItem(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::Float DisplaceDistance() const;
            Ent::Gen::Float LuminanceCenter() const;
            Ent::Gen::Int MapChannel() const;
            Ent::Gen::String MotifName() const;
            Ent::Gen::Float MotifOffsetX() const;
            Ent::Gen::Float MotifOffsetY() const;
            Ent::Gen::Float MotifRotationZ() const;
            Ent::Gen::Float MotifSizeX() const;
            Ent::Gen::Float MotifSizeY() const;
            Ent::Gen::String _comment() const;
        };

        struct CreatureDangerousness : HelperObject // Object
        {
            CreatureDangerousness(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CreatureDangerousness";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Int dangerousness() const;
            Ent::Gen::Float multiplierWhenInjured() const;
        };

        struct ConditionalRigidityAttribute_RigidityParameter : HelperObject // Object
        {
            ConditionalRigidityAttribute_RigidityParameter(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::RigidityParameter";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ScaleConverter Rigidity() const;
            Ent::Gen::Float SpeedDown() const;
            Ent::Gen::Float SpeedUp() const;
            Ent::Gen::String _comment() const;
        };

        struct ConditionalRigidityAttribute_Conditions : HelperObject // Object
        {
            ConditionalRigidityAttribute_Conditions(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::Conditions";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::ActorCategory> ActorCategories() const;
            PrimArray<Ent::Gen::String> ActorStates() const;
            Ent::Gen::Vector2 AngularVelocityFactorRange() const;
            Ent::Gen::Vector2 DirectionDotRange() const;
            Ent::Gen::Vector2 LinearVelocityFactorRange() const;
            Ent::Gen::String _comment() const;
        };

        struct ConditionalRigidityAttribute_Attributes : HelperObject // Object
        {
            ConditionalRigidityAttribute_Attributes(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::Attributes";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ConditionalRigidityAttribute_RigidityParameter DirectionAngular() const;
            Ent::Gen::ConditionalRigidityAttribute_RigidityParameter DirectionLinear() const;
            Ent::Gen::ConditionalRigidityAttribute_RigidityParameter OscillationAngular() const;
            Ent::Gen::ConditionalRigidityAttribute_RigidityParameter OscillationLinear() const;
            Ent::Gen::String _comment() const;
        };

        struct ConditionalRigidityAttribute : HelperObject // Object
        {
            ConditionalRigidityAttribute(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ConditionalRigidityAttribute_Attributes Attributes() const;
            Ent::Gen::ConditionalRigidityAttribute_Conditions Conditions() const;
            Ent::Gen::Bool Default() const;
            Ent::Gen::String Name() const;
            Ent::Gen::String _comment() const;
        };

        struct ComponentGD : HelperObject // Object
        {
            ComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
        
        };

        struct WorldScalePathFindGD : HelperObject // Object
        {
            WorldScalePathFindGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/WorldScalePathFindGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String FilePath() const;
            Array<Ent::Gen::NavmeshGenerationParameters> GenerationParameters() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct WildObject : HelperObject // Object
        {
            WildObject(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/WildObject";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String GdPath() const;
            Ent::Gen::String ObjectType() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct VoxelSimulationGD : HelperObject // Object
        {
            VoxelSimulationGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/VoxelSimulationGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String FilePath() const;
            Ent::Gen::Float LossBySecond() const;
            Ent::Gen::Float LostRatio() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Float TransmissionBySecond() const;
            Ent::Gen::Float TransmittedRatio() const;
            Ent::Gen::String _comment() const;
        };

        struct VolumeConstraintGD : HelperObject // Object
        {
            VolumeConstraintGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/VolumeConstraintGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::VolumeConstraintDataGD> Constraints() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct VisualGD : HelperObject // Object
        {
            VisualGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./MergedComponents.json#/definitions/VisualGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AlwaysStatic() const;
            Ent::Gen::Bool EDITOR_GenerateFur() const;
            Array<Ent::Gen::EDITOR_LODsItem> EDITOR_LODs() const;
            Ent::Gen::Float RUNTIME_LODScale() const;
            Array<Ent::Gen::RUNTIME_LODsItem> RUNTIME_LODs() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String VisualResourcePath() const;
            Ent::Gen::String _comment() const;
        };

        struct VelocityObstacleGD : HelperObject // Object
        {
            VelocityObstacleGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/VelocityObstacleGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float AccelerationAfterAvoidance() const;
            Ent::Gen::Float Radius() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct UnifiedPhysicsDataGD : HelperObject // Object
        {
            UnifiedPhysicsDataGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/UnifiedPhysicsDataGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct TriggerEventCameraGD : HelperObject // Object
        {
            TriggerEventCameraGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/TriggerEventCameraGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EventCameraData EventCameraData() const;
            Ent::Gen::String PlayAnimBeforeTrigger() const;
            PrimArray<Ent::Gen::String> PlayAnimsWhenTriggered() const;
            Ent::Gen::Float Radius() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Bool UseDuration() const;
            Ent::Gen::Bool UsePhysics() const;
            Ent::Gen::Bool UseRadius() const;
            Ent::Gen::String _comment() const;
        };

        struct TransformGD : HelperObject // Object
        {
            TransformGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./MergedComponents.json#/definitions/TransformGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool EDITOR_InheritScaleFromSubSceneHolder() const;
            Ent::Gen::Bool EDITOR_PropagateScaleToSubScene() const;
            Ent::Gen::Matrix33 Matrix() const;
            Ent::Gen::Quat Orientation() const;
            Ent::Gen::Vector3 Position() const;
            Ent::Gen::Vector3 Scale() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct TestUnion : HelperObject // Object
        {
            TestUnion(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TestUnion";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ Union() const;
            Array<Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_> UnionArray() const;
            Array<Ent::Gen::UnionObjectArrayItem> UnionObjectArray() const;
            Ent::Gen::String _comment() const;
        };

        struct TestSetOfObject : HelperObject // Object
        {
            TestSetOfObject(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TestSetOfObject";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Map<char const*, Ent::Gen::MapOfObjectItem_A> MapOfObject() const;
            Ent::Gen::ObjectSet<char const*, Ent::Gen::SetOfObjectItem> SetOfObject() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct TestEntityRef : HelperObject // Object
        {
            TestEntityRef(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TestEntityRef";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::EntityRef TestRef() const;
            Ent::Gen::String _comment() const;
        };

        struct TestDefaultValues : HelperObject // Object
        {
            TestDefaultValues(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TestDefaultValues";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Matrix33 Matrix() const;
            Ent::Gen::Matrix33 Matrix2() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::TestPropertyDefaultValues2 propertyWithDefault() const;
        };

        struct TestCreature : HelperObject // Object
        {
            TestCreature(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TestCreature";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef FullCursed() const;
            Ent::Gen::EntityRef FullLush() const;
            Ent::Gen::EntityRef SklCursed() const;
            Ent::Gen::EntityRef SklLush() const;
            Ent::Gen::EntityRef SklNeutral() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct TestArrays : HelperObject // Object
        {
            TestArrays(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TestArrays";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::Float> DefaultValue() const;
            PrimArray<Ent::Gen::Float> OverridedDefaultValue() const;
            PrimArray<Ent::Gen::Float> OverridedPrefabValue() const;
            PrimArray<Ent::Gen::Float> PrefabValue() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ Variant() const;
            Ent::Gen::String _comment() const;
        };

        struct TerrainSurfaceObject : HelperObject // Object
        {
            TerrainSurfaceObject(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/TerrainSurfaceObject";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String EDITOR_tso() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct TerrainGD : HelperObject // Object
        {
            TerrainGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./MergedComponents.json#/definitions/TerrainGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Int EDITOR_AlbedoType() const;
            Ent::Gen::Float EDITOR_CavityAlbedoStrength() const;
            Ent::Gen::Float EDITOR_CavityStrength() const;
            Ent::Gen::Float EDITOR_CollisionDecimateHmm() const;
            Ent::Gen::Bool EDITOR_ComputeSurfaceObjectTerrain() const;
            Ent::Gen::Bool EDITOR_DebugMode() const;
            Ent::Gen::Int EDITOR_DetailMapFalloff() const;
            Ent::Gen::Float EDITOR_DetailScale() const;
            Ent::Gen::Bool EDITOR_DisableSeedParams() const;
            Ent::Gen::Bool EDITOR_DisplayAlbedo() const;
            Ent::Gen::Bool EDITOR_DisplayFinal() const;
            Ent::Gen::Bool EDITOR_Distributed() const;
            Ent::Gen::Bool EDITOR_Erosion() const;
            Ent::Gen::Int EDITOR_ErosionType() const;
            Ent::Gen::Bool EDITOR_ExportCollision() const;
            Ent::Gen::Int EDITOR_ExportQuality() const;
            Ent::Gen::Bool EDITOR_LocalSndbs() const;
            Ent::Gen::Bool EDITOR_MergeTSOPreview() const;
            Ent::Gen::Bool EDITOR_MultiLayerHeightmap() const;
            Ent::Gen::String EDITOR_Path() const;
            Ent::Gen::Int EDITOR_PreviewQuality() const;
            Ent::Gen::Bool EDITOR_ProcessDetailMap() const;
            Ent::Gen::Int EDITOR_SeedTextureSizeReduce() const;
            Ent::Gen::Bool EDITOR_SuperimposeSeeds() const;
            Ent::Gen::Float EDITOR_SurfaceObjectDecimate() const;
            Ent::Gen::Float EDITOR_SurfaceObjectDecimateHmm() const;
            Ent::Gen::String EDITOR_TerrainWildMat() const;
            Ent::Gen::Int EDITOR_TriPerMeter() const;
            Ent::Gen::Bool EDITOR_WMErosionComputeDistant() const;
            Ent::Gen::Bool EDITOR_WMErosionPreview() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Terrain_TerrainMeta TerrainMeta() const;
            Ent::Gen::String _comment() const;
        };

        struct TeamGD : HelperObject // Object
        {
            TeamGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/TeamGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SystemicCreature : HelperObject // Object
        {
            SystemicCreature(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/SystemicCreature";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> BehaviorModifierTagList() const;
            Ent::Gen::String BehaviorPath() const;
            Ent::Gen::String BehaviorState() const;
            Ent::Gen::Bool Burried() const;
            Ent::Gen::Bool CameraTarget() const;
            Ent::Gen::Bool CanBeMaster() const;
            Ent::Gen::String Faction() const;
            Ent::Gen::String Inventory() const;
            Ent::Gen::Bool Invincible() const;
            Ent::Gen::Float Life() const;
            Ent::Gen::String Name() const;
            Ent::Gen::Bool PlayerSpawn() const;
            PrimArray<Ent::Gen::String> ScriptList() const;
            Ent::Gen::String Spawner() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String UniqueID() const;
            Ent::Gen::Bool Warrior() const;
            Ent::Gen::String _comment() const;
        };

        struct SubScene : HelperObject // Object
        {
            SubScene(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/SubScene";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ObjectSet<char const*, Ent::Gen::Entity> Embedded() const;
            Ent::Gen::String File() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool isEmbedded() const;
        };

        struct StickToTerrain : HelperObject // Object
        {
            StickToTerrain(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/StickToTerrain";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float NormalRatio() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Float ZOffset() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Float precisionRadius() const;
            Ent::Gen::Bool useNormal() const;
        };

        struct StaticObjectGD : HelperObject // Object
        {
            StaticObjectGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./MergedComponents.json#/definitions/StaticObjectGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool EDITOR_IsCave() const;
            Ent::Gen::Bool EDITOR_UsedInMultiLayerHeightmap() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Bool Visual() const;
            Ent::Gen::String _comment() const;
        };

        struct StaffVertebrasGD : HelperObject // Object
        {
            StaffVertebrasGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/StaffVertebrasGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> HotspotNames() const;
            Ent::Gen::Int MaxVertebraCount() const;
            Ent::Gen::Int OwnedVertebraStartCount() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String VertebraGRCPath1() const;
            Ent::Gen::String VertebraGRCPath2() const;
            Ent::Gen::String VertebraGRCPath3() const;
            Ent::Gen::String VertebraGRCPath4() const;
            Ent::Gen::VomitData VomitData() const;
            Ent::Gen::String _comment() const;
        };

        struct SoundEmitterGD : HelperObject // Object
        {
            SoundEmitterGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SoundEmitterGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float ActivationDistance() const;
            PrimArray<Ent::Gen::String> ActivationSound() const;
            Ent::Gen::SyncTempoMode ActivationSync() const;
            Ent::Gen::String AuxSend() const;
            PrimArray<Ent::Gen::String> Bank() const;
            Ent::Gen::Float BoidRadius() const;
            Ent::Gen::Float BoidRadiusToInnerEdgeRatio() const;
            Ent::Gen::Float BoidRadiusToOuterEdgeRatio() const;
            Ent::Gen::Bool BoidRealPositionComputation() const;
            Ent::Gen::String CreatureType() const;
            Ent::Gen::Bool Echoes() const;
            Ent::Gen::Float EchoesSend() const;
            Ent::Gen::Float EventDistance() const;
            Ent::Gen::SoundEventMapping EventMapping() const;
            Ent::Gen::Map<char const*, Ent::Gen::String> ExplicitEventMapping() const;
            PrimArray<Ent::Gen::String> InEvents() const;
            PrimArray<Ent::Gen::String> OutEvents() const;
            Ent::Gen::ComponentGD Super() const;
            PrimArray<Ent::Gen::String> UnactivationSound() const;
            Ent::Gen::SyncTempoMode UnactivationSync() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool dopplerActivated() const;
            Ent::Gen::Int relativeHeightPriority() const;
            Ent::Gen::Bool sendSoundAreaEvents() const;
            Ent::Gen::Float waterDeepAltitude() const;
            Ent::Gen::Float waterPuddleAltitude() const;
        };

        struct SoundAreaGD : HelperObject // Object
        {
            SoundAreaGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SoundAreaGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String EventEnter() const;
            Ent::Gen::String EventExit() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SoulSpotGD : HelperObject // Object
        {
            SoulSpotGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SoulSpotGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            PrimArray<Ent::Gen::String> Tags() const;
            Ent::Gen::String _comment() const;
        };

        struct SoulRespawnOpportunityGD : HelperObject // Object
        {
            SoulRespawnOpportunityGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SoulRespawnOpportunityGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ReviveSide ForceReviveSide() const;
            Ent::Gen::Int MaxDensityCount() const;
            Ent::Gen::Float MaxDensityRadius() const;
            Ent::Gen::Vector3 Offset() const;
            Ent::Gen::Int SlotCount() const;
            Ent::Gen::Specie Specie() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SmoothScaleComponentGD : HelperObject // Object
        {
            SmoothScaleComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SmoothScaleComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SmallActorSpawnerGD : HelperObject // Object
        {
            SmallActorSpawnerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SmallActorSpawnerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SmallActorGD : HelperObject // Object
        {
            SmallActorGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SmallActorGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SideMapGateGD : HelperObject // Object
        {
            SideMapGateGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SideMapGateGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String SideMapName() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ShapeshiftStatueGD : HelperObject // Object
        {
            ShapeshiftStatueGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ShapeshiftStatueGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef AssociatedEntityRef() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ShamanVisionGD : HelperObject // Object
        {
            ShamanVisionGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ShamanVisionGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ShamanItemGD : HelperObject // Object
        {
            ShamanItemGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ShamanItemGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> BoneNames() const;
            Ent::Gen::EntityRef OppositeItemEntityRef() const;
            Ent::Gen::ReviveSide ReviveSide() const;
            Ent::Gen::Int StartPartCount() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SensorControllerGD : HelperObject // Object
        {
            SensorControllerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/SensorControllerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct SeedPatch : HelperObject // Object
        {
            SeedPatch(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/SeedPatch";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AddVertexColor() const;
            Ent::Gen::Matrix33 LocalMatrix() const;
            Ent::Gen::String MeshFile() const;
            Ent::Gen::String NoiseName() const;
            Ent::Gen::Float NoiseOffsetX() const;
            Ent::Gen::Float NoiseOffsetY() const;
            Ent::Gen::Float NoiseSizeX() const;
            Ent::Gen::Float NoiseSizeY() const;
            Ent::Gen::String SeedName() const;
            Ent::Gen::Bool SeedOverride() const;
            Ent::Gen::SeedPatchDataList SeedPatchDataList() const;
            Ent::Gen::Int Subdivision() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ScriptComponentGD : HelperObject // Object
        {
            ScriptComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ScriptComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Map<char const*, Ent::Gen::TypedValue> CommonDataMap() const;
            Ent::Gen::Map<char const*, Ent::Gen::ScriptPathAndDataSet> ScriptsMap() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ReviveSideSwitcherGD : HelperObject // Object
        {
            ReviveSideSwitcherGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ReviveSideSwitcherGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef ReviveEnergyEntityRef() const;
            Ent::Gen::Map<ReviveSideEnum, Ent::Gen::ReviveSideData> ReviveSideData() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ReviveEnergyGD : HelperObject // Object
        {
            ReviveEnergyGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ReviveEnergyGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float EnergyMinNeutral() const;
            Ent::Gen::Float HatchingEnergyMinHysteresis() const;
            Ent::Gen::Float HatchingFightBackSpeedModifier() const;
            Ent::Gen::Float HatchingMaxDuration() const;
            Ent::Gen::Float HatchingMinDuration() const;
            Ent::Gen::Float InitEnergy() const;
            Ent::Gen::ReviveSide InitReviveSide() const;
            Ent::Gen::Float MaxEnergy() const;
            Ent::Gen::Float MaxWaitingTime() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct RespawnPlaceGD : HelperObject // Object
        {
            RespawnPlaceGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/RespawnPlaceGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AlwaysAvailable() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct RegenerableVegetationGD : HelperObject // Object
        {
            RegenerableVegetationGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/RegenerableVegetationGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String PCloudPath() const;
            Ent::Gen::FloatRange RegenRange() const;
            Ent::Gen::ComponentGD Super() const;
            PrimArray<Ent::Gen::String> UsedVegetations() const;
            Array<Ent::Gen::VegetationPCloudData> VegetationPClouds() const;
            Ent::Gen::String _comment() const;
        };

        struct RegenSwitcherGD : HelperObject // Object
        {
            RegenSwitcherGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/RegenSwitcherGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool ParentTransforms() const;
            Array<Ent::Gen::RegenData> RegenData() const;
            Ent::Gen::RegenSwitchBehavior RegenSwitchBehavior() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct RegenMeshGD : HelperObject // Object
        {
            RegenMeshGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/RegenMeshGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String FilePath() const;
            Ent::Gen::Float FrontierHeightDetection() const;
            Ent::Gen::Float FrontierTolerance() const;
            Ent::Gen::Float LossBySecond() const;
            Ent::Gen::Float LostRatio() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Float TransmissionPerSecond() const;
            Ent::Gen::Float TransmissionRatio() const;
            Ent::Gen::String _comment() const;
        };

        struct RegenFXGD : HelperObject // Object
        {
            RegenFXGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/RegenFXGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct RagdollGD : HelperObject // Object
        {
            RagdollGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/RagdollGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String RagdollType() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct QuickCreatureSwitchGD : HelperObject // Object
        {
            QuickCreatureSwitchGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/QuickCreatureSwitchGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::EntityRef> CreatureEntityRefs() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ProtoComponentGD : HelperObject // Object
        {
            ProtoComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ProtoComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ProjectileShooterGD : HelperObject // Object
        {
            ProjectileShooterGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ProjectileShooterGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Map<char const*, Ent::Gen::ProjectileShooterData> ProjectileShooterData() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PossessableGPEGD : HelperObject // Object
        {
            PossessableGPEGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PossessableGPEGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String GPEActorStateName() const;
            Ent::Gen::GPEType GPEType() const;
            Ent::Gen::String HotspotName() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PlayerComponentGD : HelperObject // Object
        {
            PlayerComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PlayerComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PickableDistributorComponentGD : HelperObject // Object
        {
            PickableDistributorComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PickableDistributorComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float PickableGrowingTime() const;
            Ent::Gen::Float PickablePickedUpCooldownTime() const;
            Array<Ent::Gen::PickableDistributorComponentData> PickablesList() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PickableComponentGD : HelperObject // Object
        {
            PickableComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PickableComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::ResponsiblePointer_ActorState_> StatesForPicker() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PhysicsTriggerGD : HelperObject // Object
        {
            PhysicsTriggerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PhysicsTriggerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> RequiredComponents() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PhysicsMeshProviderGD : HelperObject // Object
        {
            PhysicsMeshProviderGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PhysicsMeshProviderGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool EdgeTransitionConstraintAllowed() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PhysicsMeshDeformerGD : HelperObject // Object
        {
            PhysicsMeshDeformerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PhysicsMeshDeformerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PhysicsGD : HelperObject // Object
        {
            PhysicsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./MergedComponents.json#/definitions/PhysicsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AffectByHit() const;
            Ent::Gen::Float AngularDamping() const;
            Ent::Gen::Vector3 AxisRestriction() const;
            Ent::Gen::Bool CameraIgnored() const;
            Ent::Gen::Bool Ccd() const;
            PrimArray<Ent::Gen::String> EDITOR_MeshColliders() const;
            Ent::Gen::String EDITOR_MeshEdges() const;
            Ent::Gen::String EDITOR_NavMeshStamper() const;
            Ent::Gen::Float EnergyLoss() const;
            Ent::Gen::Float Friction() const;
            Ent::Gen::Bool HasGravity() const;
            Ent::Gen::Float LinearDamping() const;
            Ent::Gen::Float Mass() const;
            PrimArray<Ent::Gen::String> MeshColliders() const;
            Ent::Gen::String MeshEdges() const;
            Ent::Gen::String MotionType() const;
            Ent::Gen::String NavMeshStamper() const;
            Ent::Gen::Vector3 Offset() const;
            Ent::Gen::Vector3 OffsetRotation() const;
            Ent::Gen::String PhysicsMaterial() const;
            Ent::Gen::PrimitiveColliderType PrimitiveCollider() const;
            PrimArray<Ent::Gen::Size> PrimitiveColliderSizeLayerMask() const;
            Ent::Gen::Float Radius() const;
            Ent::Gen::Float Restitution() const;
            PrimArray<Ent::Gen::PhysicsLayer> SelfFilter() const;
            Ent::Gen::Vector3 Size() const;
            Ent::Gen::Bool Sleep() const;
            Ent::Gen::ComponentGD Super() const;
            PrimArray<Ent::Gen::PhysicsLayer> TargetFilter() const;
            Ent::Gen::Bool Walkable() const;
            Ent::Gen::String WalkableSoundSwitch() const;
            Ent::Gen::String _comment() const;
        };

        struct PhysicsDataGD : HelperObject // Object
        {
            PhysicsDataGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./MergedComponents.json#/definitions/PhysicsDataGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::EDITOR_Mesh> EDITOR_Shapes() const;
            Ent::Gen::Bool EDITOR_isTrigger() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Array<Ent::Gen::sPhysicsJointDesc> joints() const;
            Array<Ent::Gen::sRigidBodyDesc> rigidBodies() const;
        };

        struct PerceiverGD : HelperObject // Object
        {
            PerceiverGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PerceiverGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Float m_coneAngle() const;
            Ent::Gen::Float m_farSoundDistance() const;
            Ent::Gen::Float m_longRangeDistance() const;
            Ent::Gen::Float m_lowRangeDistance() const;
            Ent::Gen::Float m_middleRangeDistance() const;
            Ent::Gen::Float m_middleSoundDistance() const;
            Ent::Gen::Float m_nearSoundDistance() const;
            Ent::Gen::Float m_perceptionHeightMultiplier() const;
            Ent::Gen::Float m_perceptionHeightMultiplierHeightMax() const;
            Ent::Gen::Bool m_rayCastCheck() const;
        };

        struct PerceivableGD : HelperObject // Object
        {
            PerceivableGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PerceivableGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Float m_perceivedDistanceMultiplier() const;
            Ent::Gen::SoundEmissionStrength m_soundCrouch() const;
            Ent::Gen::SoundEmissionStrength m_soundImmobile() const;
            Ent::Gen::SoundEmissionStrength m_soundRun() const;
            Ent::Gen::SoundEmissionStrength m_soundWalk() const;
            PrimArray<Ent::Gen::String> m_tags() const;
        };

        struct PathNodeGD : HelperObject // Object
        {
            PathNodeGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PathNodeGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float Radius() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::TagsList Tags() const;
            Ent::Gen::String _comment() const;
        };

        struct PathMotionControllerGD : HelperObject // Object
        {
            PathMotionControllerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PathMotionControllerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PathGD : HelperObject // Object
        {
            PathGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PathGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String FilePath() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PathBoneRigidBodyGD : HelperObject // Object
        {
            PathBoneRigidBodyGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PathBoneRigidBodyGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PathBoneInfluenceGD : HelperObject // Object
        {
            PathBoneInfluenceGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PathBoneInfluenceGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::sNodeBoneInfluenceDataTemplate> Data() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct PathBoneAnimGD : HelperObject // Object
        {
            PathBoneAnimGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/PathBoneAnimGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct OutfitWearerGD : HelperObject // Object
        {
            OutfitWearerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/OutfitWearerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef InventoryEntityRef() const;
            Ent::Gen::Float OutfitFadeDelay() const;
            Ent::Gen::Float OutfitFadeDuration() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct OutfitGD : HelperObject // Object
        {
            OutfitGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/OutfitGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::MountableSnapLine_ControlPoint> SnapLine() const;
            Ent::Gen::SoundEventMapping SoundEventMappingRules() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Array<Ent::Gen::OutfitPiece> clothes() const;
            Ent::Gen::String faction() const;
            Ent::Gen::String overrideSpeciesAudioCategory() const;
            PrimArray<Ent::Gen::String> soundBank() const;
            Ent::Gen::String soundTag() const;
            Ent::Gen::StyleMode specialOutfitStyle() const;
            Ent::Gen::Bool spirit() const;
        };

        struct NotVisibleInSubscene : HelperObject // Object
        {
            NotVisibleInSubscene(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/NotVisibleInSubscene";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct NetworkNode : HelperObject // Object
        {
            NetworkNode(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/NetworkNode";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String Tag() const;
            Ent::Gen::String ThumbnailMesh() const;
            Ent::Gen::String Type_() const;
            Ent::Gen::String _comment() const;
        };

        struct NetworkLink : HelperObject // Object
        {
            NetworkLink(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/NetworkLink";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String Source() const;
            Ent::Gen::EntityRef SourceEntityRef() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String Target() const;
            Ent::Gen::EntityRef TargetEntityRef() const;
            Ent::Gen::String ThumbnailMesh() const;
            Ent::Gen::String _comment() const;
        };

        struct NetGD : HelperObject // Object
        {
            NetGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/NetGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct MultiThumbnail : HelperObject // Object
        {
            MultiThumbnail(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/MultiThumbnail";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::ListItem> List() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct MounterGD : HelperObject // Object
        {
            MounterGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MounterGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String HotspotName() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct MountableGD : HelperObject // Object
        {
            MountableGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MountableGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> HotspotNames() const;
            Array<Ent::Gen::MountableSnapLine_ControlPoint> SnapLine() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct MountIKControllerGD : HelperObject // Object
        {
            MountIKControllerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MountIKControllerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Float horizontalSpineLeanFactor() const;
        };

        struct MissionHolderGD : HelperObject // Object
        {
            MissionHolderGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MissionHolderGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool Private() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct MeshNavigationInfosGD : HelperObject // Object
        {
            MeshNavigationInfosGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MeshNavigationInfosGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct Mesh : HelperObject // Object
        {
            Mesh(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/Mesh";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String File() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct LDPrimitive : HelperObject // Object
        {
            LDPrimitive(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/LDPrimitive";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool NonDisuptive() const;
            Ent::Gen::PrimitiveData PrimitiveData() const;
            Ent::Gen::String PrimitiveType() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ItemHolderGD : HelperObject // Object
        {
            ItemHolderGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ItemHolderGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String HotspotDefault() const;
            Ent::Gen::String HotspotHandLeft() const;
            Ent::Gen::String HotspotHandRight() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Bool Visible() const;
            Ent::Gen::String _comment() const;
        };

        struct InventoryGD : HelperObject // Object
        {
            InventoryGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/InventoryGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Array<Ent::Gen::TaggedEntityRef> TaggedEntityRefs() const;
            Ent::Gen::String _comment() const;
        };

        struct InfoboardRegistererGD : HelperObject // Object
        {
            InfoboardRegistererGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/InfoboardRegistererGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String InfoboardName() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct HotspotsGD : HelperObject // Object
        {
            HotspotsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HotspotsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Map<char const*, Ent::Gen::HotspotData> HotspotsMap() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct HitTriggerGD : HelperObject // Object
        {
            HitTriggerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HitTriggerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct HeightObj : HelperObject // Object
        {
            HeightObj(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/HeightObj";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Array<Ent::Gen::DisplaceNoiseListItem> DisplaceNoiseList() const;
            Ent::Gen::Int EditorSubdivision() const;
            Ent::Gen::Matrix33 LocalMatrix() const;
            Ent::Gen::String MeshFile() const;
            Ent::Gen::String MeshName() const;
            Ent::Gen::Int Priority() const;
            Ent::Gen::Int Subdivision() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct HeightMapComponentGD : HelperObject // Object
        {
            HeightMapComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HeightMapComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String HeightMapArchivePath() const;
            PrimArray<Ent::Gen::String> HeightMapPaths() const;
            Ent::Gen::Float HeightScale() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Bool SwapX() const;
            Ent::Gen::Bool SwapY() const;
            Ent::Gen::Vector2 WorldSize() const;
            Ent::Gen::String _comment() const;
        };

        struct HealthAreaGD : HelperObject // Object
        {
            HealthAreaGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HealthAreaGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float EnergyRestorationRate() const;
            Ent::Gen::ReviveSide FactionSide() const;
            Ent::Gen::Float LifeRestorationRate() const;
            Ent::Gen::Float Radius() const;
            Ent::Gen::Float ReviveRestorationRate() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct HealerGD : HelperObject // Object
        {
            HealerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HealerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct HealTriggerGD : HelperObject // Object
        {
            HealTriggerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HealTriggerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct HealPumpGD : HelperObject // Object
        {
            HealPumpGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/HealPumpGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float AlliesLifeAgentPerSecond() const;
            Ent::Gen::Float EnemiesLifeAgentPerSecond() const;
            Ent::Gen::Float LifeAmountRatio() const;
            Ent::Gen::Float Range() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct GroundTypeSamplerGD : HelperObject // Object
        {
            GroundTypeSamplerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/GroundTypeSamplerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String GroundTypeMapPath() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct GameEffectSpawnerGD : HelperObject // Object
        {
            GameEffectSpawnerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/GameEffectSpawnerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Vector3 GameEffectOffset() const;
            Array<Ent::Gen::sGameEffectTemplate> StartGameEffects() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct FluidVolumeComponentGD : HelperObject // Object
        {
            FluidVolumeComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::FluidVolumeComponentGD_FluidVolumeData FluidVolume() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct FluidViewGD : HelperObject // Object
        {
            FluidViewGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidViewGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct FluidToRegenInjectorGD : HelperObject // Object
        {
            FluidToRegenInjectorGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidToRegenInjectorGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float EnergyPerSecond() const;
            Ent::Gen::Float MinDepth() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Float UpdatePeriod() const;
            Ent::Gen::String _comment() const;
        };

        struct FluidNavMeshTaggerGD : HelperObject // Object
        {
            FluidNavMeshTaggerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidNavMeshTaggerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float MinDepth() const;
            Ent::Gen::Precision SamplingPrecision() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Float UpdatePeriod() const;
            Ent::Gen::String _comment() const;
        };

        struct FluidGD : HelperObject // Object
        {
            FluidGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::FluidType type() const;
            Ent::Gen::Bool useHalfShape() const;
        };

        struct FluidFXEntitySpawnerGD : HelperObject // Object
        {
            FluidFXEntitySpawnerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FluidFXEntitySpawnerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Precision SamplingPrecision() const;
            Array<Ent::Gen::SpawningParameter> SpawningParameters() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Float UpdatePeriod() const;
            Ent::Gen::String _comment() const;
        };

        struct FireSensorGD : HelperObject // Object
        {
            FireSensorGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FireSensorGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EventTriggerGD : HelperObject // Object
        {
            EventTriggerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EventTriggerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> Events() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EventHandlerGD : HelperObject // Object
        {
            EventHandlerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EventHandlerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EnvStampGD : HelperObject // Object
        {
            EnvStampGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EnvStampGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float RegenStateChangeDuration() const;
            Ent::Gen::Map<RegenerationStateEnum, Array<Ent::Gen::sEnvStamp>> Stamps() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EnergySpoutGD : HelperObject // Object
        {
            EnergySpoutGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EnergySpoutGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float EnergySpeed() const;
            Ent::Gen::EntityRef ListenerEntityRef() const;
            Ent::Gen::Float MinDistanceBetweenRegen() const;
            Ent::Gen::Float MinTimeBetweenRegen() const;
            Ent::Gen::Float Radius() const;
            Ent::Gen::String SplineRegenEffectName() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EnergySourceGD : HelperObject // Object
        {
            EnergySourceGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EnergySourceGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float MaxBuffDuration() const;
            Ent::Gen::Float NearbyReactionRadius() const;
            Ent::Gen::Float Radius() const;
            Ent::Gen::Float RefreshFrequency() const;
            Ent::Gen::ReviveSide ReviveSide() const;
            Ent::Gen::String SourceRegenEffectName() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EnergyProbeGD : HelperObject // Object
        {
            EnergyProbeGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EnergyProbeGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EnergyPoolGD : HelperObject // Object
        {
            EnergyPoolGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EnergyPoolGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float DrainConnectionRadius() const;
            Ent::Gen::Bool FactionOverride() const;
            Ent::Gen::Float ProbeDetectionRadius() const;
            PrimArray<Ent::Gen::String> RegenEffectsOnConversion() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EnergyNetworkListenerGD : HelperObject // Object
        {
            EnergyNetworkListenerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EnergyNetworkListenerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EnergyDrainGD : HelperObject // Object
        {
            EnergyDrainGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EnergyDrainGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef PoolEntityRef() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EnergyCrookGD : HelperObject // Object
        {
            EnergyCrookGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EnergyCrookGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef FatherEntityRef() const;
            Ent::Gen::Float Radius() const;
            Ent::Gen::Float RegenScale() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct DummyComponentGD : HelperObject // Object
        {
            DummyComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/DummyComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct DistanceTriggerGD : HelperObject // Object
        {
            DistanceTriggerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/DistanceTriggerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::Float> Distances() const;
            PrimArray<Ent::Gen::Float> Hystereses() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct FightDistanceTriggerGD : HelperObject // Object
        {
            FightDistanceTriggerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/FightDistanceTriggerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::DistanceTriggerGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct DebugGridGD : HelperObject // Object
        {
            DebugGridGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/DebugGridGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Int Height() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Int Width() const;
            Ent::Gen::String _comment() const;
        };

        struct CustomThumbnail : HelperObject // Object
        {
            CustomThumbnail(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/CustomThumbnail";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::ThumbPath Thumbnail() const;
            Ent::Gen::String _comment() const;
        };

        struct CreatureUIGD : HelperObject // Object
        {
            CreatureUIGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CreatureUIGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float LifeBarLength() const;
            Ent::Gen::Float LifeBarWidth() const;
            Ent::Gen::Float LifeBarZOffset() const;
            Ent::Gen::Bool ShowLifeBar() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ConnectorGD : HelperObject // Object
        {
            ConnectorGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ConnectorGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ComponentWithProtoCodeGD : HelperObject // Object
        {
            ComponentWithProtoCodeGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ComponentWithProtoCodeGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ClothAnimationGD : HelperObject // Object
        {
            ClothAnimationGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ClothAnimationGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String ClothSkeletonPath() const;
            Ent::Gen::Float PhysicsDamping() const;
            Ent::Gen::Bool PhysicsFixedDt() const;
            Ent::Gen::Vector3 PhysicsGravity() const;
            Ent::Gen::Float PhysicsMass() const;
            Ent::Gen::Float PhysicsSpeedInfluence() const;
            Ent::Gen::Bool PhysicsUseDefaultProperties() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ChildEntityPoolComponentGD : HelperObject // Object
        {
            ChildEntityPoolComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ChildEntityPoolComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::EntityRef> EntityRefs() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CharacterPlatformGD : HelperObject // Object
        {
            CharacterPlatformGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CharacterPlatformGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CameraDataGD : HelperObject // Object
        {
            CameraDataGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CameraDataGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String CameraDataResourcePath() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct BreakableGD : HelperObject // Object
        {
            BreakableGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/BreakableGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String BreakSoundBank() const;
            Ent::Gen::String BreakSoundEvent() const;
            Ent::Gen::String GameEffectOnBroken() const;
            Ent::Gen::String GameEffectOnDestruction() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool isBreakableWithAttack() const;
        };

        struct BittenGD : HelperObject // Object
        {
            BittenGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/BittenGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct BeamGeneratorGD : HelperObject // Object
        {
            BeamGeneratorGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/BeamGeneratorGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> BonesStartPoints() const;
            Ent::Gen::Float ExtraDistanceBeyondTarget() const;
            Ent::Gen::Float LengthDuration() const;
            Ent::Gen::String PathBeamEffect() const;
            Ent::Gen::Int PointsPerBeam() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AttackTriggerGD : HelperObject // Object
        {
            AttackTriggerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AttackTriggerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AssemblyGD : HelperObject // Object
        {
            AssemblyGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AssemblyGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationRegenConstraintsGD : HelperObject // Object
        {
            AnimationRegenConstraintsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationRegenConstraintsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float MaxDisplace() const;
            Ent::Gen::Float MaxRegenSpeed() const;
            Ent::Gen::Float MinDisplace() const;
            Ent::Gen::Float RegenMultiplier() const;
            Ent::Gen::String RegenToDisplaceCurve() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationPlaylistGD : HelperObject // Object
        {
            AnimationPlaylistGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationPlaylistGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> PlayAnim() const;
            Ent::Gen::Int PlayAnimInputID() const;
            Ent::Gen::Bool RandomizeStartTime() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationPhysicsChainConstraintsGD : HelperObject // Object
        {
            AnimationPhysicsChainConstraintsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationPhysicsChainConstraintsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String BoneNamePrefix() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationModelGD : HelperObject // Object
        {
            AnimationModelGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationModelGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool isLandAnimDriven() const;
            Ent::Gen::Bool isTurnAllowed() const;
            Ent::Gen::Float playRatioFactor() const;
            Ent::Gen::Float scalePlayRatioCoeffInfluence() const;
            Ent::Gen::Float startRunPlayRatioFactor() const;
            Ent::Gen::Float turnPlayRatioFactor() const;
        };

        struct AnimationHitsConstraintsGD : HelperObject // Object
        {
            AnimationHitsConstraintsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationHitsConstraintsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct Component : Base // Union
        {
            Component(Ent::Node* _node): Base(_node) {}
            static constexpr char schemaName[] = "./MergedComponents.json#/definitions/Component";
            char const* getType() const;
            std::optional<Ent::Gen::StaticObjectGD> StaticObjectGD() const;
            Ent::Gen::StaticObjectGD setStaticObjectGD() const;
            std::optional<Ent::Gen::AnimationControllerGD> AnimationControllerGD() const;
            Ent::Gen::AnimationControllerGD setAnimationControllerGD() const;
            std::optional<Ent::Gen::PhysicsDataGD> PhysicsDataGD() const;
            Ent::Gen::PhysicsDataGD setPhysicsDataGD() const;
            std::optional<Ent::Gen::VisualGD> VisualGD() const;
            Ent::Gen::VisualGD setVisualGD() const;
            std::optional<Ent::Gen::TransformGD> TransformGD() const;
            Ent::Gen::TransformGD setTransformGD() const;
            std::optional<Ent::Gen::TerrainGD> TerrainGD() const;
            Ent::Gen::TerrainGD setTerrainGD() const;
            std::optional<Ent::Gen::PhysicsGD> PhysicsGD() const;
            Ent::Gen::PhysicsGD setPhysicsGD() const;
            std::optional<Ent::Gen::CustomThumbnail> CustomThumbnail() const;
            Ent::Gen::CustomThumbnail setCustomThumbnail() const;
            std::optional<Ent::Gen::HeightObj> HeightObj() const;
            Ent::Gen::HeightObj setHeightObj() const;
            std::optional<Ent::Gen::LDPrimitive> LDPrimitive() const;
            Ent::Gen::LDPrimitive setLDPrimitive() const;
            std::optional<Ent::Gen::Mesh> Mesh() const;
            Ent::Gen::Mesh setMesh() const;
            std::optional<Ent::Gen::MultiThumbnail> MultiThumbnail() const;
            Ent::Gen::MultiThumbnail setMultiThumbnail() const;
            std::optional<Ent::Gen::NetworkLink> NetworkLink() const;
            Ent::Gen::NetworkLink setNetworkLink() const;
            std::optional<Ent::Gen::NetworkNode> NetworkNode() const;
            Ent::Gen::NetworkNode setNetworkNode() const;
            std::optional<Ent::Gen::NotVisibleInSubscene> NotVisibleInSubscene() const;
            Ent::Gen::NotVisibleInSubscene setNotVisibleInSubscene() const;
            std::optional<Ent::Gen::SeedPatch> SeedPatch() const;
            Ent::Gen::SeedPatch setSeedPatch() const;
            std::optional<Ent::Gen::StickToTerrain> StickToTerrain() const;
            Ent::Gen::StickToTerrain setStickToTerrain() const;
            std::optional<Ent::Gen::SubScene> SubScene() const;
            Ent::Gen::SubScene setSubScene() const;
            std::optional<Ent::Gen::SystemicCreature> SystemicCreature() const;
            Ent::Gen::SystemicCreature setSystemicCreature() const;
            std::optional<Ent::Gen::TerrainSurfaceObject> TerrainSurfaceObject() const;
            Ent::Gen::TerrainSurfaceObject setTerrainSurfaceObject() const;
            std::optional<Ent::Gen::TestArrays> TestArrays() const;
            Ent::Gen::TestArrays setTestArrays() const;
            std::optional<Ent::Gen::TestCreature> TestCreature() const;
            Ent::Gen::TestCreature setTestCreature() const;
            std::optional<Ent::Gen::TestDefaultValues> TestDefaultValues() const;
            Ent::Gen::TestDefaultValues setTestDefaultValues() const;
            std::optional<Ent::Gen::TestEntityRef> TestEntityRef() const;
            Ent::Gen::TestEntityRef setTestEntityRef() const;
            std::optional<Ent::Gen::TestSetOfObject> TestSetOfObject() const;
            Ent::Gen::TestSetOfObject setTestSetOfObject() const;
            std::optional<Ent::Gen::TestUnion> TestUnion() const;
            Ent::Gen::TestUnion setTestUnion() const;
            std::optional<Ent::Gen::UnitTestComponent> UnitTestComponent() const;
            Ent::Gen::UnitTestComponent setUnitTestComponent() const;
            std::optional<Ent::Gen::WildObject> WildObject() const;
            Ent::Gen::WildObject setWildObject() const;
            std::optional<Ent::Gen::EnergyCrookGD> EnergyCrookGD() const;
            Ent::Gen::EnergyCrookGD setEnergyCrookGD() const;
            std::optional<Ent::Gen::AIContextGD> AIContextGD() const;
            Ent::Gen::AIContextGD setAIContextGD() const;
            std::optional<Ent::Gen::EventTriggerGD> EventTriggerGD() const;
            Ent::Gen::EventTriggerGD setEventTriggerGD() const;
            std::optional<Ent::Gen::BeamGeneratorGD> BeamGeneratorGD() const;
            Ent::Gen::BeamGeneratorGD setBeamGeneratorGD() const;
            std::optional<Ent::Gen::WorldScalePathFindGD> WorldScalePathFindGD() const;
            Ent::Gen::WorldScalePathFindGD setWorldScalePathFindGD() const;
            std::optional<Ent::Gen::NetGD> NetGD() const;
            Ent::Gen::NetGD setNetGD() const;
            std::optional<Ent::Gen::BittenGD> BittenGD() const;
            Ent::Gen::BittenGD setBittenGD() const;
            std::optional<Ent::Gen::PathBoneAnimGD> PathBoneAnimGD() const;
            Ent::Gen::PathBoneAnimGD setPathBoneAnimGD() const;
            std::optional<Ent::Gen::AnimationRegenConstraintsGD> AnimationRegenConstraintsGD() const;
            Ent::Gen::AnimationRegenConstraintsGD setAnimationRegenConstraintsGD() const;
            std::optional<Ent::Gen::HealPumpGD> HealPumpGD() const;
            Ent::Gen::HealPumpGD setHealPumpGD() const;
            std::optional<Ent::Gen::GroundTypeSamplerGD> GroundTypeSamplerGD() const;
            Ent::Gen::GroundTypeSamplerGD setGroundTypeSamplerGD() const;
            std::optional<Ent::Gen::UnifiedPhysicsDataGD> UnifiedPhysicsDataGD() const;
            Ent::Gen::UnifiedPhysicsDataGD setUnifiedPhysicsDataGD() const;
            std::optional<Ent::Gen::FluidGD> FluidGD() const;
            Ent::Gen::FluidGD setFluidGD() const;
            std::optional<Ent::Gen::ProjectileGD> ProjectileGD() const;
            Ent::Gen::ProjectileGD setProjectileGD() const;
            std::optional<Ent::Gen::CameraSetterGD> CameraSetterGD() const;
            Ent::Gen::CameraSetterGD setCameraSetterGD() const;
            std::optional<Ent::Gen::AssemblyGD> AssemblyGD() const;
            Ent::Gen::AssemblyGD setAssemblyGD() const;
            std::optional<Ent::Gen::SmoothScaleComponentGD> SmoothScaleComponentGD() const;
            Ent::Gen::SmoothScaleComponentGD setSmoothScaleComponentGD() const;
            std::optional<Ent::Gen::FluidViewGD> FluidViewGD() const;
            Ent::Gen::FluidViewGD setFluidViewGD() const;
            std::optional<Ent::Gen::RegenMeshGD> RegenMeshGD() const;
            Ent::Gen::RegenMeshGD setRegenMeshGD() const;
            std::optional<Ent::Gen::ReviveEnergyGD> ReviveEnergyGD() const;
            Ent::Gen::ReviveEnergyGD setReviveEnergyGD() const;
            std::optional<Ent::Gen::DebugGridGD> DebugGridGD() const;
            Ent::Gen::DebugGridGD setDebugGridGD() const;
            std::optional<Ent::Gen::ChildEntityPoolComponentGD> ChildEntityPoolComponentGD() const;
            Ent::Gen::ChildEntityPoolComponentGD setChildEntityPoolComponentGD() const;
            std::optional<Ent::Gen::ProtoComponentGD> ProtoComponentGD() const;
            Ent::Gen::ProtoComponentGD setProtoComponentGD() const;
            std::optional<Ent::Gen::GameEffectSpawnerGD> GameEffectSpawnerGD() const;
            Ent::Gen::GameEffectSpawnerGD setGameEffectSpawnerGD() const;
            std::optional<Ent::Gen::ClothGD> ClothGD() const;
            Ent::Gen::ClothGD setClothGD() const;
            std::optional<Ent::Gen::FireSensorGD> FireSensorGD() const;
            Ent::Gen::FireSensorGD setFireSensorGD() const;
            std::optional<Ent::Gen::HealerGD> HealerGD() const;
            Ent::Gen::HealerGD setHealerGD() const;
            std::optional<Ent::Gen::AnimationLegsConstraintsGD> AnimationLegsConstraintsGD() const;
            Ent::Gen::AnimationLegsConstraintsGD setAnimationLegsConstraintsGD() const;
            std::optional<Ent::Gen::PathBoneRigidBodyGD> PathBoneRigidBodyGD() const;
            Ent::Gen::PathBoneRigidBodyGD setPathBoneRigidBodyGD() const;
            std::optional<Ent::Gen::FightDistanceTriggerGD> FightDistanceTriggerGD() const;
            Ent::Gen::FightDistanceTriggerGD setFightDistanceTriggerGD() const;
            std::optional<Ent::Gen::SoulSpotGD> SoulSpotGD() const;
            Ent::Gen::SoulSpotGD setSoulSpotGD() const;
            std::optional<Ent::Gen::HealTriggerGD> HealTriggerGD() const;
            Ent::Gen::HealTriggerGD setHealTriggerGD() const;
            std::optional<Ent::Gen::AnimationTailConstraintsGD> AnimationTailConstraintsGD() const;
            Ent::Gen::AnimationTailConstraintsGD setAnimationTailConstraintsGD() const;
            std::optional<Ent::Gen::VolumeConstraintGD> VolumeConstraintGD() const;
            Ent::Gen::VolumeConstraintGD setVolumeConstraintGD() const;
            std::optional<Ent::Gen::EnvStampGD> EnvStampGD() const;
            Ent::Gen::EnvStampGD setEnvStampGD() const;
            std::optional<Ent::Gen::FluidFXEntitySpawnerGD> FluidFXEntitySpawnerGD() const;
            Ent::Gen::FluidFXEntitySpawnerGD setFluidFXEntitySpawnerGD() const;
            std::optional<Ent::Gen::EnergyDrainGD> EnergyDrainGD() const;
            Ent::Gen::EnergyDrainGD setEnergyDrainGD() const;
            std::optional<Ent::Gen::AnimationEventsGeneratorGD> AnimationEventsGeneratorGD() const;
            Ent::Gen::AnimationEventsGeneratorGD setAnimationEventsGeneratorGD() const;
            std::optional<Ent::Gen::MountableGD> MountableGD() const;
            Ent::Gen::MountableGD setMountableGD() const;
            std::optional<Ent::Gen::InfoboardRegistererGD> InfoboardRegistererGD() const;
            Ent::Gen::InfoboardRegistererGD setInfoboardRegistererGD() const;
            std::optional<Ent::Gen::EventHandlerGD> EventHandlerGD() const;
            Ent::Gen::EventHandlerGD setEventHandlerGD() const;
            std::optional<Ent::Gen::SoulRespawnOpportunityGD> SoulRespawnOpportunityGD() const;
            Ent::Gen::SoulRespawnOpportunityGD setSoulRespawnOpportunityGD() const;
            std::optional<Ent::Gen::HealthAreaGD> HealthAreaGD() const;
            Ent::Gen::HealthAreaGD setHealthAreaGD() const;
            std::optional<Ent::Gen::SoundAreaGD> SoundAreaGD() const;
            Ent::Gen::SoundAreaGD setSoundAreaGD() const;
            std::optional<Ent::Gen::PathBoneInfluenceGD> PathBoneInfluenceGD() const;
            Ent::Gen::PathBoneInfluenceGD setPathBoneInfluenceGD() const;
            std::optional<Ent::Gen::ComponentWithProtoCodeGD> ComponentWithProtoCodeGD() const;
            Ent::Gen::ComponentWithProtoCodeGD setComponentWithProtoCodeGD() const;
            std::optional<Ent::Gen::CharacterControllerGD> CharacterControllerGD() const;
            Ent::Gen::CharacterControllerGD setCharacterControllerGD() const;
            std::optional<Ent::Gen::PickableComponentGD> PickableComponentGD() const;
            Ent::Gen::PickableComponentGD setPickableComponentGD() const;
            std::optional<Ent::Gen::CameraDataGD> CameraDataGD() const;
            Ent::Gen::CameraDataGD setCameraDataGD() const;
            std::optional<Ent::Gen::RegenFXGD> RegenFXGD() const;
            Ent::Gen::RegenFXGD setRegenFXGD() const;
            std::optional<Ent::Gen::PhysicsMeshDeformerGD> PhysicsMeshDeformerGD() const;
            Ent::Gen::PhysicsMeshDeformerGD setPhysicsMeshDeformerGD() const;
            std::optional<Ent::Gen::AnimationHitsConstraintsGD> AnimationHitsConstraintsGD() const;
            Ent::Gen::AnimationHitsConstraintsGD setAnimationHitsConstraintsGD() const;
            std::optional<Ent::Gen::FluidVolumeComponentGD> FluidVolumeComponentGD() const;
            Ent::Gen::FluidVolumeComponentGD setFluidVolumeComponentGD() const;
            std::optional<Ent::Gen::RegenerableVegetationGD> RegenerableVegetationGD() const;
            Ent::Gen::RegenerableVegetationGD setRegenerableVegetationGD() const;
            std::optional<Ent::Gen::ShamanVisionGD> ShamanVisionGD() const;
            Ent::Gen::ShamanVisionGD setShamanVisionGD() const;
            std::optional<Ent::Gen::CinematicGD> CinematicGD() const;
            Ent::Gen::CinematicGD setCinematicGD() const;
            std::optional<Ent::Gen::ConnectorGD> ConnectorGD() const;
            Ent::Gen::ConnectorGD setConnectorGD() const;
            std::optional<Ent::Gen::BeamTargetGD> BeamTargetGD() const;
            Ent::Gen::BeamTargetGD setBeamTargetGD() const;
            std::optional<Ent::Gen::ActorGD> ActorGD() const;
            Ent::Gen::ActorGD setActorGD() const;
            std::optional<Ent::Gen::CharacterPlatformGD> CharacterPlatformGD() const;
            Ent::Gen::CharacterPlatformGD setCharacterPlatformGD() const;
            std::optional<Ent::Gen::ReviveSideSwitcherGD> ReviveSideSwitcherGD() const;
            Ent::Gen::ReviveSideSwitcherGD setReviveSideSwitcherGD() const;
            std::optional<Ent::Gen::EnergyPoolGD> EnergyPoolGD() const;
            Ent::Gen::EnergyPoolGD setEnergyPoolGD() const;
            std::optional<Ent::Gen::PlayerComponentGD> PlayerComponentGD() const;
            Ent::Gen::PlayerComponentGD setPlayerComponentGD() const;
            std::optional<Ent::Gen::HotspotsGD> HotspotsGD() const;
            Ent::Gen::HotspotsGD setHotspotsGD() const;
            std::optional<Ent::Gen::SmallActorSpawnerGD> SmallActorSpawnerGD() const;
            Ent::Gen::SmallActorSpawnerGD setSmallActorSpawnerGD() const;
            std::optional<Ent::Gen::PathMotionControllerGD> PathMotionControllerGD() const;
            Ent::Gen::PathMotionControllerGD setPathMotionControllerGD() const;
            std::optional<Ent::Gen::CreatureAIGD> CreatureAIGD() const;
            Ent::Gen::CreatureAIGD setCreatureAIGD() const;
            std::optional<Ent::Gen::CreatureUIGD> CreatureUIGD() const;
            Ent::Gen::CreatureUIGD setCreatureUIGD() const;
            std::optional<Ent::Gen::SoundEmitterGD> SoundEmitterGD() const;
            Ent::Gen::SoundEmitterGD setSoundEmitterGD() const;
            std::optional<Ent::Gen::EnergySourceGD> EnergySourceGD() const;
            Ent::Gen::EnergySourceGD setEnergySourceGD() const;
            std::optional<Ent::Gen::ClothAnimationGD> ClothAnimationGD() const;
            Ent::Gen::ClothAnimationGD setClothAnimationGD() const;
            std::optional<Ent::Gen::CreatureGD> CreatureGD() const;
            Ent::Gen::CreatureGD setCreatureGD() const;
            std::optional<Ent::Gen::HitTriggerGD> HitTriggerGD() const;
            Ent::Gen::HitTriggerGD setHitTriggerGD() const;
            std::optional<Ent::Gen::ProjectileShooterGD> ProjectileShooterGD() const;
            Ent::Gen::ProjectileShooterGD setProjectileShooterGD() const;
            std::optional<Ent::Gen::LightComponentGD> LightComponentGD() const;
            Ent::Gen::LightComponentGD setLightComponentGD() const;
            std::optional<Ent::Gen::MounterGD> MounterGD() const;
            Ent::Gen::MounterGD setMounterGD() const;
            std::optional<Ent::Gen::AttackTriggerGD> AttackTriggerGD() const;
            Ent::Gen::AttackTriggerGD setAttackTriggerGD() const;
            std::optional<Ent::Gen::PossessableGPEGD> PossessableGPEGD() const;
            Ent::Gen::PossessableGPEGD setPossessableGPEGD() const;
            std::optional<Ent::Gen::OutfitGD> OutfitGD() const;
            Ent::Gen::OutfitGD setOutfitGD() const;
            std::optional<Ent::Gen::BreakableGD> BreakableGD() const;
            Ent::Gen::BreakableGD setBreakableGD() const;
            std::optional<Ent::Gen::PathNodeGD> PathNodeGD() const;
            Ent::Gen::PathNodeGD setPathNodeGD() const;
            std::optional<Ent::Gen::VelocityObstacleGD> VelocityObstacleGD() const;
            Ent::Gen::VelocityObstacleGD setVelocityObstacleGD() const;
            std::optional<Ent::Gen::ShapeshiftStatueGD> ShapeshiftStatueGD() const;
            Ent::Gen::ShapeshiftStatueGD setShapeshiftStatueGD() const;
            std::optional<Ent::Gen::RagdollGD> RagdollGD() const;
            Ent::Gen::RagdollGD setRagdollGD() const;
            std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD> AnimationPhysicsChainConstraintsGD() const;
            Ent::Gen::AnimationPhysicsChainConstraintsGD setAnimationPhysicsChainConstraintsGD() const;
            std::optional<Ent::Gen::ScriptComponentGD> ScriptComponentGD() const;
            Ent::Gen::ScriptComponentGD setScriptComponentGD() const;
            std::optional<Ent::Gen::FluidToRegenInjectorGD> FluidToRegenInjectorGD() const;
            Ent::Gen::FluidToRegenInjectorGD setFluidToRegenInjectorGD() const;
            std::optional<Ent::Gen::PerceivableGD> PerceivableGD() const;
            Ent::Gen::PerceivableGD setPerceivableGD() const;
            std::optional<Ent::Gen::InventoryGD> InventoryGD() const;
            Ent::Gen::InventoryGD setInventoryGD() const;
            std::optional<Ent::Gen::ItemHolderGD> ItemHolderGD() const;
            Ent::Gen::ItemHolderGD setItemHolderGD() const;
            std::optional<Ent::Gen::PathGD> PathGD() const;
            Ent::Gen::PathGD setPathGD() const;
            std::optional<Ent::Gen::PerceiverGD> PerceiverGD() const;
            Ent::Gen::PerceiverGD setPerceiverGD() const;
            std::optional<Ent::Gen::DummyComponentGD> DummyComponentGD() const;
            Ent::Gen::DummyComponentGD setDummyComponentGD() const;
            std::optional<Ent::Gen::FluidNavMeshTaggerGD> FluidNavMeshTaggerGD() const;
            Ent::Gen::FluidNavMeshTaggerGD setFluidNavMeshTaggerGD() const;
            std::optional<Ent::Gen::EnergySpoutGD> EnergySpoutGD() const;
            Ent::Gen::EnergySpoutGD setEnergySpoutGD() const;
            std::optional<Ent::Gen::PickableDistributorComponentGD> PickableDistributorComponentGD() const;
            Ent::Gen::PickableDistributorComponentGD setPickableDistributorComponentGD() const;
            std::optional<Ent::Gen::ShamanItemGD> ShamanItemGD() const;
            Ent::Gen::ShamanItemGD setShamanItemGD() const;
            std::optional<Ent::Gen::TeamGD> TeamGD() const;
            Ent::Gen::TeamGD setTeamGD() const;
            std::optional<Ent::Gen::SmallActorGD> SmallActorGD() const;
            Ent::Gen::SmallActorGD setSmallActorGD() const;
            std::optional<Ent::Gen::PhysicsMeshProviderGD> PhysicsMeshProviderGD() const;
            Ent::Gen::PhysicsMeshProviderGD setPhysicsMeshProviderGD() const;
            std::optional<Ent::Gen::SideMapGateGD> SideMapGateGD() const;
            Ent::Gen::SideMapGateGD setSideMapGateGD() const;
            std::optional<Ent::Gen::HeightMapComponentGD> HeightMapComponentGD() const;
            Ent::Gen::HeightMapComponentGD setHeightMapComponentGD() const;
            std::optional<Ent::Gen::MountIKControllerGD> MountIKControllerGD() const;
            Ent::Gen::MountIKControllerGD setMountIKControllerGD() const;
            std::optional<Ent::Gen::StaffVertebrasGD> StaffVertebrasGD() const;
            Ent::Gen::StaffVertebrasGD setStaffVertebrasGD() const;
            std::optional<Ent::Gen::SensorControllerGD> SensorControllerGD() const;
            Ent::Gen::SensorControllerGD setSensorControllerGD() const;
            std::optional<Ent::Gen::BoidsGD> BoidsGD() const;
            Ent::Gen::BoidsGD setBoidsGD() const;
            std::optional<Ent::Gen::AnimationTreeConstraintsGD> AnimationTreeConstraintsGD() const;
            Ent::Gen::AnimationTreeConstraintsGD setAnimationTreeConstraintsGD() const;
            std::optional<Ent::Gen::DistanceTriggerGD> DistanceTriggerGD() const;
            Ent::Gen::DistanceTriggerGD setDistanceTriggerGD() const;
            std::optional<Ent::Gen::QuickCreatureSwitchGD> QuickCreatureSwitchGD() const;
            Ent::Gen::QuickCreatureSwitchGD setQuickCreatureSwitchGD() const;
            std::optional<Ent::Gen::EnergyProbeGD> EnergyProbeGD() const;
            Ent::Gen::EnergyProbeGD setEnergyProbeGD() const;
            std::optional<Ent::Gen::RespawnPlaceGD> RespawnPlaceGD() const;
            Ent::Gen::RespawnPlaceGD setRespawnPlaceGD() const;
            std::optional<Ent::Gen::OutfitWearerGD> OutfitWearerGD() const;
            Ent::Gen::OutfitWearerGD setOutfitWearerGD() const;
            std::optional<Ent::Gen::VoxelSimulationGD> VoxelSimulationGD() const;
            Ent::Gen::VoxelSimulationGD setVoxelSimulationGD() const;
            std::optional<Ent::Gen::AnimationModelGD> AnimationModelGD() const;
            Ent::Gen::AnimationModelGD setAnimationModelGD() const;
            std::optional<Ent::Gen::TriggerEventCameraGD> TriggerEventCameraGD() const;
            Ent::Gen::TriggerEventCameraGD setTriggerEventCameraGD() const;
            std::optional<Ent::Gen::AnimationPlaylistGD> AnimationPlaylistGD() const;
            Ent::Gen::AnimationPlaylistGD setAnimationPlaylistGD() const;
            std::optional<Ent::Gen::MeshNavigationInfosGD> MeshNavigationInfosGD() const;
            Ent::Gen::MeshNavigationInfosGD setMeshNavigationInfosGD() const;
            std::optional<Ent::Gen::PhysicsTriggerGD> PhysicsTriggerGD() const;
            Ent::Gen::PhysicsTriggerGD setPhysicsTriggerGD() const;
            std::optional<Ent::Gen::EnergyNetworkListenerGD> EnergyNetworkListenerGD() const;
            Ent::Gen::EnergyNetworkListenerGD setEnergyNetworkListenerGD() const;
            std::optional<Ent::Gen::MissionHolderGD> MissionHolderGD() const;
            Ent::Gen::MissionHolderGD setMissionHolderGD() const;
            std::optional<Ent::Gen::RegenSwitcherGD> RegenSwitcherGD() const;
            Ent::Gen::RegenSwitcherGD setRegenSwitcherGD() const;
        };

        struct Object_Components : UnionSetBase<Component> // union_set
        {
            Object_Components(Ent::Node* _node)
                : UnionSetBase<Component>(_node)
            {
            }
            
            char const* getType() const;
            std::optional<Ent::Gen::StaticObjectGD> StaticObjectGD() const;
            Ent::Gen::StaticObjectGD addStaticObjectGD() const;
            std::optional<Ent::Gen::AnimationControllerGD> AnimationControllerGD() const;
            Ent::Gen::AnimationControllerGD addAnimationControllerGD() const;
            std::optional<Ent::Gen::PhysicsDataGD> PhysicsDataGD() const;
            Ent::Gen::PhysicsDataGD addPhysicsDataGD() const;
            std::optional<Ent::Gen::VisualGD> VisualGD() const;
            Ent::Gen::VisualGD addVisualGD() const;
            std::optional<Ent::Gen::TransformGD> TransformGD() const;
            Ent::Gen::TransformGD addTransformGD() const;
            std::optional<Ent::Gen::TerrainGD> TerrainGD() const;
            Ent::Gen::TerrainGD addTerrainGD() const;
            std::optional<Ent::Gen::PhysicsGD> PhysicsGD() const;
            Ent::Gen::PhysicsGD addPhysicsGD() const;
            std::optional<Ent::Gen::CustomThumbnail> CustomThumbnail() const;
            Ent::Gen::CustomThumbnail addCustomThumbnail() const;
            std::optional<Ent::Gen::HeightObj> HeightObj() const;
            Ent::Gen::HeightObj addHeightObj() const;
            std::optional<Ent::Gen::LDPrimitive> LDPrimitive() const;
            Ent::Gen::LDPrimitive addLDPrimitive() const;
            std::optional<Ent::Gen::Mesh> Mesh() const;
            Ent::Gen::Mesh addMesh() const;
            std::optional<Ent::Gen::MultiThumbnail> MultiThumbnail() const;
            Ent::Gen::MultiThumbnail addMultiThumbnail() const;
            std::optional<Ent::Gen::NetworkLink> NetworkLink() const;
            Ent::Gen::NetworkLink addNetworkLink() const;
            std::optional<Ent::Gen::NetworkNode> NetworkNode() const;
            Ent::Gen::NetworkNode addNetworkNode() const;
            std::optional<Ent::Gen::NotVisibleInSubscene> NotVisibleInSubscene() const;
            Ent::Gen::NotVisibleInSubscene addNotVisibleInSubscene() const;
            std::optional<Ent::Gen::SeedPatch> SeedPatch() const;
            Ent::Gen::SeedPatch addSeedPatch() const;
            std::optional<Ent::Gen::StickToTerrain> StickToTerrain() const;
            Ent::Gen::StickToTerrain addStickToTerrain() const;
            std::optional<Ent::Gen::SubScene> SubScene() const;
            Ent::Gen::SubScene addSubScene() const;
            std::optional<Ent::Gen::SystemicCreature> SystemicCreature() const;
            Ent::Gen::SystemicCreature addSystemicCreature() const;
            std::optional<Ent::Gen::TerrainSurfaceObject> TerrainSurfaceObject() const;
            Ent::Gen::TerrainSurfaceObject addTerrainSurfaceObject() const;
            std::optional<Ent::Gen::TestArrays> TestArrays() const;
            Ent::Gen::TestArrays addTestArrays() const;
            std::optional<Ent::Gen::TestCreature> TestCreature() const;
            Ent::Gen::TestCreature addTestCreature() const;
            std::optional<Ent::Gen::TestDefaultValues> TestDefaultValues() const;
            Ent::Gen::TestDefaultValues addTestDefaultValues() const;
            std::optional<Ent::Gen::TestEntityRef> TestEntityRef() const;
            Ent::Gen::TestEntityRef addTestEntityRef() const;
            std::optional<Ent::Gen::TestSetOfObject> TestSetOfObject() const;
            Ent::Gen::TestSetOfObject addTestSetOfObject() const;
            std::optional<Ent::Gen::TestUnion> TestUnion() const;
            Ent::Gen::TestUnion addTestUnion() const;
            std::optional<Ent::Gen::UnitTestComponent> UnitTestComponent() const;
            Ent::Gen::UnitTestComponent addUnitTestComponent() const;
            std::optional<Ent::Gen::WildObject> WildObject() const;
            Ent::Gen::WildObject addWildObject() const;
            std::optional<Ent::Gen::EnergyCrookGD> EnergyCrookGD() const;
            Ent::Gen::EnergyCrookGD addEnergyCrookGD() const;
            std::optional<Ent::Gen::AIContextGD> AIContextGD() const;
            Ent::Gen::AIContextGD addAIContextGD() const;
            std::optional<Ent::Gen::EventTriggerGD> EventTriggerGD() const;
            Ent::Gen::EventTriggerGD addEventTriggerGD() const;
            std::optional<Ent::Gen::BeamGeneratorGD> BeamGeneratorGD() const;
            Ent::Gen::BeamGeneratorGD addBeamGeneratorGD() const;
            std::optional<Ent::Gen::WorldScalePathFindGD> WorldScalePathFindGD() const;
            Ent::Gen::WorldScalePathFindGD addWorldScalePathFindGD() const;
            std::optional<Ent::Gen::NetGD> NetGD() const;
            Ent::Gen::NetGD addNetGD() const;
            std::optional<Ent::Gen::BittenGD> BittenGD() const;
            Ent::Gen::BittenGD addBittenGD() const;
            std::optional<Ent::Gen::PathBoneAnimGD> PathBoneAnimGD() const;
            Ent::Gen::PathBoneAnimGD addPathBoneAnimGD() const;
            std::optional<Ent::Gen::AnimationRegenConstraintsGD> AnimationRegenConstraintsGD() const;
            Ent::Gen::AnimationRegenConstraintsGD addAnimationRegenConstraintsGD() const;
            std::optional<Ent::Gen::HealPumpGD> HealPumpGD() const;
            Ent::Gen::HealPumpGD addHealPumpGD() const;
            std::optional<Ent::Gen::GroundTypeSamplerGD> GroundTypeSamplerGD() const;
            Ent::Gen::GroundTypeSamplerGD addGroundTypeSamplerGD() const;
            std::optional<Ent::Gen::UnifiedPhysicsDataGD> UnifiedPhysicsDataGD() const;
            Ent::Gen::UnifiedPhysicsDataGD addUnifiedPhysicsDataGD() const;
            std::optional<Ent::Gen::FluidGD> FluidGD() const;
            Ent::Gen::FluidGD addFluidGD() const;
            std::optional<Ent::Gen::ProjectileGD> ProjectileGD() const;
            Ent::Gen::ProjectileGD addProjectileGD() const;
            std::optional<Ent::Gen::CameraSetterGD> CameraSetterGD() const;
            Ent::Gen::CameraSetterGD addCameraSetterGD() const;
            std::optional<Ent::Gen::AssemblyGD> AssemblyGD() const;
            Ent::Gen::AssemblyGD addAssemblyGD() const;
            std::optional<Ent::Gen::SmoothScaleComponentGD> SmoothScaleComponentGD() const;
            Ent::Gen::SmoothScaleComponentGD addSmoothScaleComponentGD() const;
            std::optional<Ent::Gen::FluidViewGD> FluidViewGD() const;
            Ent::Gen::FluidViewGD addFluidViewGD() const;
            std::optional<Ent::Gen::RegenMeshGD> RegenMeshGD() const;
            Ent::Gen::RegenMeshGD addRegenMeshGD() const;
            std::optional<Ent::Gen::ReviveEnergyGD> ReviveEnergyGD() const;
            Ent::Gen::ReviveEnergyGD addReviveEnergyGD() const;
            std::optional<Ent::Gen::DebugGridGD> DebugGridGD() const;
            Ent::Gen::DebugGridGD addDebugGridGD() const;
            std::optional<Ent::Gen::ChildEntityPoolComponentGD> ChildEntityPoolComponentGD() const;
            Ent::Gen::ChildEntityPoolComponentGD addChildEntityPoolComponentGD() const;
            std::optional<Ent::Gen::ProtoComponentGD> ProtoComponentGD() const;
            Ent::Gen::ProtoComponentGD addProtoComponentGD() const;
            std::optional<Ent::Gen::GameEffectSpawnerGD> GameEffectSpawnerGD() const;
            Ent::Gen::GameEffectSpawnerGD addGameEffectSpawnerGD() const;
            std::optional<Ent::Gen::ClothGD> ClothGD() const;
            Ent::Gen::ClothGD addClothGD() const;
            std::optional<Ent::Gen::FireSensorGD> FireSensorGD() const;
            Ent::Gen::FireSensorGD addFireSensorGD() const;
            std::optional<Ent::Gen::HealerGD> HealerGD() const;
            Ent::Gen::HealerGD addHealerGD() const;
            std::optional<Ent::Gen::AnimationLegsConstraintsGD> AnimationLegsConstraintsGD() const;
            Ent::Gen::AnimationLegsConstraintsGD addAnimationLegsConstraintsGD() const;
            std::optional<Ent::Gen::PathBoneRigidBodyGD> PathBoneRigidBodyGD() const;
            Ent::Gen::PathBoneRigidBodyGD addPathBoneRigidBodyGD() const;
            std::optional<Ent::Gen::FightDistanceTriggerGD> FightDistanceTriggerGD() const;
            Ent::Gen::FightDistanceTriggerGD addFightDistanceTriggerGD() const;
            std::optional<Ent::Gen::SoulSpotGD> SoulSpotGD() const;
            Ent::Gen::SoulSpotGD addSoulSpotGD() const;
            std::optional<Ent::Gen::HealTriggerGD> HealTriggerGD() const;
            Ent::Gen::HealTriggerGD addHealTriggerGD() const;
            std::optional<Ent::Gen::AnimationTailConstraintsGD> AnimationTailConstraintsGD() const;
            Ent::Gen::AnimationTailConstraintsGD addAnimationTailConstraintsGD() const;
            std::optional<Ent::Gen::VolumeConstraintGD> VolumeConstraintGD() const;
            Ent::Gen::VolumeConstraintGD addVolumeConstraintGD() const;
            std::optional<Ent::Gen::EnvStampGD> EnvStampGD() const;
            Ent::Gen::EnvStampGD addEnvStampGD() const;
            std::optional<Ent::Gen::FluidFXEntitySpawnerGD> FluidFXEntitySpawnerGD() const;
            Ent::Gen::FluidFXEntitySpawnerGD addFluidFXEntitySpawnerGD() const;
            std::optional<Ent::Gen::EnergyDrainGD> EnergyDrainGD() const;
            Ent::Gen::EnergyDrainGD addEnergyDrainGD() const;
            std::optional<Ent::Gen::AnimationEventsGeneratorGD> AnimationEventsGeneratorGD() const;
            Ent::Gen::AnimationEventsGeneratorGD addAnimationEventsGeneratorGD() const;
            std::optional<Ent::Gen::MountableGD> MountableGD() const;
            Ent::Gen::MountableGD addMountableGD() const;
            std::optional<Ent::Gen::InfoboardRegistererGD> InfoboardRegistererGD() const;
            Ent::Gen::InfoboardRegistererGD addInfoboardRegistererGD() const;
            std::optional<Ent::Gen::EventHandlerGD> EventHandlerGD() const;
            Ent::Gen::EventHandlerGD addEventHandlerGD() const;
            std::optional<Ent::Gen::SoulRespawnOpportunityGD> SoulRespawnOpportunityGD() const;
            Ent::Gen::SoulRespawnOpportunityGD addSoulRespawnOpportunityGD() const;
            std::optional<Ent::Gen::HealthAreaGD> HealthAreaGD() const;
            Ent::Gen::HealthAreaGD addHealthAreaGD() const;
            std::optional<Ent::Gen::SoundAreaGD> SoundAreaGD() const;
            Ent::Gen::SoundAreaGD addSoundAreaGD() const;
            std::optional<Ent::Gen::PathBoneInfluenceGD> PathBoneInfluenceGD() const;
            Ent::Gen::PathBoneInfluenceGD addPathBoneInfluenceGD() const;
            std::optional<Ent::Gen::ComponentWithProtoCodeGD> ComponentWithProtoCodeGD() const;
            Ent::Gen::ComponentWithProtoCodeGD addComponentWithProtoCodeGD() const;
            std::optional<Ent::Gen::CharacterControllerGD> CharacterControllerGD() const;
            Ent::Gen::CharacterControllerGD addCharacterControllerGD() const;
            std::optional<Ent::Gen::PickableComponentGD> PickableComponentGD() const;
            Ent::Gen::PickableComponentGD addPickableComponentGD() const;
            std::optional<Ent::Gen::CameraDataGD> CameraDataGD() const;
            Ent::Gen::CameraDataGD addCameraDataGD() const;
            std::optional<Ent::Gen::RegenFXGD> RegenFXGD() const;
            Ent::Gen::RegenFXGD addRegenFXGD() const;
            std::optional<Ent::Gen::PhysicsMeshDeformerGD> PhysicsMeshDeformerGD() const;
            Ent::Gen::PhysicsMeshDeformerGD addPhysicsMeshDeformerGD() const;
            std::optional<Ent::Gen::AnimationHitsConstraintsGD> AnimationHitsConstraintsGD() const;
            Ent::Gen::AnimationHitsConstraintsGD addAnimationHitsConstraintsGD() const;
            std::optional<Ent::Gen::FluidVolumeComponentGD> FluidVolumeComponentGD() const;
            Ent::Gen::FluidVolumeComponentGD addFluidVolumeComponentGD() const;
            std::optional<Ent::Gen::RegenerableVegetationGD> RegenerableVegetationGD() const;
            Ent::Gen::RegenerableVegetationGD addRegenerableVegetationGD() const;
            std::optional<Ent::Gen::ShamanVisionGD> ShamanVisionGD() const;
            Ent::Gen::ShamanVisionGD addShamanVisionGD() const;
            std::optional<Ent::Gen::CinematicGD> CinematicGD() const;
            Ent::Gen::CinematicGD addCinematicGD() const;
            std::optional<Ent::Gen::ConnectorGD> ConnectorGD() const;
            Ent::Gen::ConnectorGD addConnectorGD() const;
            std::optional<Ent::Gen::BeamTargetGD> BeamTargetGD() const;
            Ent::Gen::BeamTargetGD addBeamTargetGD() const;
            std::optional<Ent::Gen::ActorGD> ActorGD() const;
            Ent::Gen::ActorGD addActorGD() const;
            std::optional<Ent::Gen::CharacterPlatformGD> CharacterPlatformGD() const;
            Ent::Gen::CharacterPlatformGD addCharacterPlatformGD() const;
            std::optional<Ent::Gen::ReviveSideSwitcherGD> ReviveSideSwitcherGD() const;
            Ent::Gen::ReviveSideSwitcherGD addReviveSideSwitcherGD() const;
            std::optional<Ent::Gen::EnergyPoolGD> EnergyPoolGD() const;
            Ent::Gen::EnergyPoolGD addEnergyPoolGD() const;
            std::optional<Ent::Gen::PlayerComponentGD> PlayerComponentGD() const;
            Ent::Gen::PlayerComponentGD addPlayerComponentGD() const;
            std::optional<Ent::Gen::HotspotsGD> HotspotsGD() const;
            Ent::Gen::HotspotsGD addHotspotsGD() const;
            std::optional<Ent::Gen::SmallActorSpawnerGD> SmallActorSpawnerGD() const;
            Ent::Gen::SmallActorSpawnerGD addSmallActorSpawnerGD() const;
            std::optional<Ent::Gen::PathMotionControllerGD> PathMotionControllerGD() const;
            Ent::Gen::PathMotionControllerGD addPathMotionControllerGD() const;
            std::optional<Ent::Gen::CreatureAIGD> CreatureAIGD() const;
            Ent::Gen::CreatureAIGD addCreatureAIGD() const;
            std::optional<Ent::Gen::CreatureUIGD> CreatureUIGD() const;
            Ent::Gen::CreatureUIGD addCreatureUIGD() const;
            std::optional<Ent::Gen::SoundEmitterGD> SoundEmitterGD() const;
            Ent::Gen::SoundEmitterGD addSoundEmitterGD() const;
            std::optional<Ent::Gen::EnergySourceGD> EnergySourceGD() const;
            Ent::Gen::EnergySourceGD addEnergySourceGD() const;
            std::optional<Ent::Gen::ClothAnimationGD> ClothAnimationGD() const;
            Ent::Gen::ClothAnimationGD addClothAnimationGD() const;
            std::optional<Ent::Gen::CreatureGD> CreatureGD() const;
            Ent::Gen::CreatureGD addCreatureGD() const;
            std::optional<Ent::Gen::HitTriggerGD> HitTriggerGD() const;
            Ent::Gen::HitTriggerGD addHitTriggerGD() const;
            std::optional<Ent::Gen::ProjectileShooterGD> ProjectileShooterGD() const;
            Ent::Gen::ProjectileShooterGD addProjectileShooterGD() const;
            std::optional<Ent::Gen::LightComponentGD> LightComponentGD() const;
            Ent::Gen::LightComponentGD addLightComponentGD() const;
            std::optional<Ent::Gen::MounterGD> MounterGD() const;
            Ent::Gen::MounterGD addMounterGD() const;
            std::optional<Ent::Gen::AttackTriggerGD> AttackTriggerGD() const;
            Ent::Gen::AttackTriggerGD addAttackTriggerGD() const;
            std::optional<Ent::Gen::PossessableGPEGD> PossessableGPEGD() const;
            Ent::Gen::PossessableGPEGD addPossessableGPEGD() const;
            std::optional<Ent::Gen::OutfitGD> OutfitGD() const;
            Ent::Gen::OutfitGD addOutfitGD() const;
            std::optional<Ent::Gen::BreakableGD> BreakableGD() const;
            Ent::Gen::BreakableGD addBreakableGD() const;
            std::optional<Ent::Gen::PathNodeGD> PathNodeGD() const;
            Ent::Gen::PathNodeGD addPathNodeGD() const;
            std::optional<Ent::Gen::VelocityObstacleGD> VelocityObstacleGD() const;
            Ent::Gen::VelocityObstacleGD addVelocityObstacleGD() const;
            std::optional<Ent::Gen::ShapeshiftStatueGD> ShapeshiftStatueGD() const;
            Ent::Gen::ShapeshiftStatueGD addShapeshiftStatueGD() const;
            std::optional<Ent::Gen::RagdollGD> RagdollGD() const;
            Ent::Gen::RagdollGD addRagdollGD() const;
            std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD> AnimationPhysicsChainConstraintsGD() const;
            Ent::Gen::AnimationPhysicsChainConstraintsGD addAnimationPhysicsChainConstraintsGD() const;
            std::optional<Ent::Gen::ScriptComponentGD> ScriptComponentGD() const;
            Ent::Gen::ScriptComponentGD addScriptComponentGD() const;
            std::optional<Ent::Gen::FluidToRegenInjectorGD> FluidToRegenInjectorGD() const;
            Ent::Gen::FluidToRegenInjectorGD addFluidToRegenInjectorGD() const;
            std::optional<Ent::Gen::PerceivableGD> PerceivableGD() const;
            Ent::Gen::PerceivableGD addPerceivableGD() const;
            std::optional<Ent::Gen::InventoryGD> InventoryGD() const;
            Ent::Gen::InventoryGD addInventoryGD() const;
            std::optional<Ent::Gen::ItemHolderGD> ItemHolderGD() const;
            Ent::Gen::ItemHolderGD addItemHolderGD() const;
            std::optional<Ent::Gen::PathGD> PathGD() const;
            Ent::Gen::PathGD addPathGD() const;
            std::optional<Ent::Gen::PerceiverGD> PerceiverGD() const;
            Ent::Gen::PerceiverGD addPerceiverGD() const;
            std::optional<Ent::Gen::DummyComponentGD> DummyComponentGD() const;
            Ent::Gen::DummyComponentGD addDummyComponentGD() const;
            std::optional<Ent::Gen::FluidNavMeshTaggerGD> FluidNavMeshTaggerGD() const;
            Ent::Gen::FluidNavMeshTaggerGD addFluidNavMeshTaggerGD() const;
            std::optional<Ent::Gen::EnergySpoutGD> EnergySpoutGD() const;
            Ent::Gen::EnergySpoutGD addEnergySpoutGD() const;
            std::optional<Ent::Gen::PickableDistributorComponentGD> PickableDistributorComponentGD() const;
            Ent::Gen::PickableDistributorComponentGD addPickableDistributorComponentGD() const;
            std::optional<Ent::Gen::ShamanItemGD> ShamanItemGD() const;
            Ent::Gen::ShamanItemGD addShamanItemGD() const;
            std::optional<Ent::Gen::TeamGD> TeamGD() const;
            Ent::Gen::TeamGD addTeamGD() const;
            std::optional<Ent::Gen::SmallActorGD> SmallActorGD() const;
            Ent::Gen::SmallActorGD addSmallActorGD() const;
            std::optional<Ent::Gen::PhysicsMeshProviderGD> PhysicsMeshProviderGD() const;
            Ent::Gen::PhysicsMeshProviderGD addPhysicsMeshProviderGD() const;
            std::optional<Ent::Gen::SideMapGateGD> SideMapGateGD() const;
            Ent::Gen::SideMapGateGD addSideMapGateGD() const;
            std::optional<Ent::Gen::HeightMapComponentGD> HeightMapComponentGD() const;
            Ent::Gen::HeightMapComponentGD addHeightMapComponentGD() const;
            std::optional<Ent::Gen::MountIKControllerGD> MountIKControllerGD() const;
            Ent::Gen::MountIKControllerGD addMountIKControllerGD() const;
            std::optional<Ent::Gen::StaffVertebrasGD> StaffVertebrasGD() const;
            Ent::Gen::StaffVertebrasGD addStaffVertebrasGD() const;
            std::optional<Ent::Gen::SensorControllerGD> SensorControllerGD() const;
            Ent::Gen::SensorControllerGD addSensorControllerGD() const;
            std::optional<Ent::Gen::BoidsGD> BoidsGD() const;
            Ent::Gen::BoidsGD addBoidsGD() const;
            std::optional<Ent::Gen::AnimationTreeConstraintsGD> AnimationTreeConstraintsGD() const;
            Ent::Gen::AnimationTreeConstraintsGD addAnimationTreeConstraintsGD() const;
            std::optional<Ent::Gen::DistanceTriggerGD> DistanceTriggerGD() const;
            Ent::Gen::DistanceTriggerGD addDistanceTriggerGD() const;
            std::optional<Ent::Gen::QuickCreatureSwitchGD> QuickCreatureSwitchGD() const;
            Ent::Gen::QuickCreatureSwitchGD addQuickCreatureSwitchGD() const;
            std::optional<Ent::Gen::EnergyProbeGD> EnergyProbeGD() const;
            Ent::Gen::EnergyProbeGD addEnergyProbeGD() const;
            std::optional<Ent::Gen::RespawnPlaceGD> RespawnPlaceGD() const;
            Ent::Gen::RespawnPlaceGD addRespawnPlaceGD() const;
            std::optional<Ent::Gen::OutfitWearerGD> OutfitWearerGD() const;
            Ent::Gen::OutfitWearerGD addOutfitWearerGD() const;
            std::optional<Ent::Gen::VoxelSimulationGD> VoxelSimulationGD() const;
            Ent::Gen::VoxelSimulationGD addVoxelSimulationGD() const;
            std::optional<Ent::Gen::AnimationModelGD> AnimationModelGD() const;
            Ent::Gen::AnimationModelGD addAnimationModelGD() const;
            std::optional<Ent::Gen::TriggerEventCameraGD> TriggerEventCameraGD() const;
            Ent::Gen::TriggerEventCameraGD addTriggerEventCameraGD() const;
            std::optional<Ent::Gen::AnimationPlaylistGD> AnimationPlaylistGD() const;
            Ent::Gen::AnimationPlaylistGD addAnimationPlaylistGD() const;
            std::optional<Ent::Gen::MeshNavigationInfosGD> MeshNavigationInfosGD() const;
            Ent::Gen::MeshNavigationInfosGD addMeshNavigationInfosGD() const;
            std::optional<Ent::Gen::PhysicsTriggerGD> PhysicsTriggerGD() const;
            Ent::Gen::PhysicsTriggerGD addPhysicsTriggerGD() const;
            std::optional<Ent::Gen::EnergyNetworkListenerGD> EnergyNetworkListenerGD() const;
            Ent::Gen::EnergyNetworkListenerGD addEnergyNetworkListenerGD() const;
            std::optional<Ent::Gen::MissionHolderGD> MissionHolderGD() const;
            Ent::Gen::MissionHolderGD addMissionHolderGD() const;
            std::optional<Ent::Gen::RegenSwitcherGD> RegenSwitcherGD() const;
            Ent::Gen::RegenSwitcherGD addRegenSwitcherGD() const;
        };

        struct Components : UnionSetBase<Component> // union_set
        {
            Components(Ent::Node* _node)
                : UnionSetBase<Component>(_node)
            {
            }
            
            char const* getType() const;
            std::optional<Ent::Gen::StaticObjectGD> StaticObjectGD() const;
            Ent::Gen::StaticObjectGD addStaticObjectGD() const;
            std::optional<Ent::Gen::AnimationControllerGD> AnimationControllerGD() const;
            Ent::Gen::AnimationControllerGD addAnimationControllerGD() const;
            std::optional<Ent::Gen::PhysicsDataGD> PhysicsDataGD() const;
            Ent::Gen::PhysicsDataGD addPhysicsDataGD() const;
            std::optional<Ent::Gen::VisualGD> VisualGD() const;
            Ent::Gen::VisualGD addVisualGD() const;
            std::optional<Ent::Gen::TransformGD> TransformGD() const;
            Ent::Gen::TransformGD addTransformGD() const;
            std::optional<Ent::Gen::TerrainGD> TerrainGD() const;
            Ent::Gen::TerrainGD addTerrainGD() const;
            std::optional<Ent::Gen::PhysicsGD> PhysicsGD() const;
            Ent::Gen::PhysicsGD addPhysicsGD() const;
            std::optional<Ent::Gen::CustomThumbnail> CustomThumbnail() const;
            Ent::Gen::CustomThumbnail addCustomThumbnail() const;
            std::optional<Ent::Gen::HeightObj> HeightObj() const;
            Ent::Gen::HeightObj addHeightObj() const;
            std::optional<Ent::Gen::LDPrimitive> LDPrimitive() const;
            Ent::Gen::LDPrimitive addLDPrimitive() const;
            std::optional<Ent::Gen::Mesh> Mesh() const;
            Ent::Gen::Mesh addMesh() const;
            std::optional<Ent::Gen::MultiThumbnail> MultiThumbnail() const;
            Ent::Gen::MultiThumbnail addMultiThumbnail() const;
            std::optional<Ent::Gen::NetworkLink> NetworkLink() const;
            Ent::Gen::NetworkLink addNetworkLink() const;
            std::optional<Ent::Gen::NetworkNode> NetworkNode() const;
            Ent::Gen::NetworkNode addNetworkNode() const;
            std::optional<Ent::Gen::NotVisibleInSubscene> NotVisibleInSubscene() const;
            Ent::Gen::NotVisibleInSubscene addNotVisibleInSubscene() const;
            std::optional<Ent::Gen::SeedPatch> SeedPatch() const;
            Ent::Gen::SeedPatch addSeedPatch() const;
            std::optional<Ent::Gen::StickToTerrain> StickToTerrain() const;
            Ent::Gen::StickToTerrain addStickToTerrain() const;
            std::optional<Ent::Gen::SubScene> SubScene() const;
            Ent::Gen::SubScene addSubScene() const;
            std::optional<Ent::Gen::SystemicCreature> SystemicCreature() const;
            Ent::Gen::SystemicCreature addSystemicCreature() const;
            std::optional<Ent::Gen::TerrainSurfaceObject> TerrainSurfaceObject() const;
            Ent::Gen::TerrainSurfaceObject addTerrainSurfaceObject() const;
            std::optional<Ent::Gen::TestArrays> TestArrays() const;
            Ent::Gen::TestArrays addTestArrays() const;
            std::optional<Ent::Gen::TestCreature> TestCreature() const;
            Ent::Gen::TestCreature addTestCreature() const;
            std::optional<Ent::Gen::TestDefaultValues> TestDefaultValues() const;
            Ent::Gen::TestDefaultValues addTestDefaultValues() const;
            std::optional<Ent::Gen::TestEntityRef> TestEntityRef() const;
            Ent::Gen::TestEntityRef addTestEntityRef() const;
            std::optional<Ent::Gen::TestSetOfObject> TestSetOfObject() const;
            Ent::Gen::TestSetOfObject addTestSetOfObject() const;
            std::optional<Ent::Gen::TestUnion> TestUnion() const;
            Ent::Gen::TestUnion addTestUnion() const;
            std::optional<Ent::Gen::UnitTestComponent> UnitTestComponent() const;
            Ent::Gen::UnitTestComponent addUnitTestComponent() const;
            std::optional<Ent::Gen::WildObject> WildObject() const;
            Ent::Gen::WildObject addWildObject() const;
            std::optional<Ent::Gen::EnergyCrookGD> EnergyCrookGD() const;
            Ent::Gen::EnergyCrookGD addEnergyCrookGD() const;
            std::optional<Ent::Gen::AIContextGD> AIContextGD() const;
            Ent::Gen::AIContextGD addAIContextGD() const;
            std::optional<Ent::Gen::EventTriggerGD> EventTriggerGD() const;
            Ent::Gen::EventTriggerGD addEventTriggerGD() const;
            std::optional<Ent::Gen::BeamGeneratorGD> BeamGeneratorGD() const;
            Ent::Gen::BeamGeneratorGD addBeamGeneratorGD() const;
            std::optional<Ent::Gen::WorldScalePathFindGD> WorldScalePathFindGD() const;
            Ent::Gen::WorldScalePathFindGD addWorldScalePathFindGD() const;
            std::optional<Ent::Gen::NetGD> NetGD() const;
            Ent::Gen::NetGD addNetGD() const;
            std::optional<Ent::Gen::BittenGD> BittenGD() const;
            Ent::Gen::BittenGD addBittenGD() const;
            std::optional<Ent::Gen::PathBoneAnimGD> PathBoneAnimGD() const;
            Ent::Gen::PathBoneAnimGD addPathBoneAnimGD() const;
            std::optional<Ent::Gen::AnimationRegenConstraintsGD> AnimationRegenConstraintsGD() const;
            Ent::Gen::AnimationRegenConstraintsGD addAnimationRegenConstraintsGD() const;
            std::optional<Ent::Gen::HealPumpGD> HealPumpGD() const;
            Ent::Gen::HealPumpGD addHealPumpGD() const;
            std::optional<Ent::Gen::GroundTypeSamplerGD> GroundTypeSamplerGD() const;
            Ent::Gen::GroundTypeSamplerGD addGroundTypeSamplerGD() const;
            std::optional<Ent::Gen::UnifiedPhysicsDataGD> UnifiedPhysicsDataGD() const;
            Ent::Gen::UnifiedPhysicsDataGD addUnifiedPhysicsDataGD() const;
            std::optional<Ent::Gen::FluidGD> FluidGD() const;
            Ent::Gen::FluidGD addFluidGD() const;
            std::optional<Ent::Gen::ProjectileGD> ProjectileGD() const;
            Ent::Gen::ProjectileGD addProjectileGD() const;
            std::optional<Ent::Gen::CameraSetterGD> CameraSetterGD() const;
            Ent::Gen::CameraSetterGD addCameraSetterGD() const;
            std::optional<Ent::Gen::AssemblyGD> AssemblyGD() const;
            Ent::Gen::AssemblyGD addAssemblyGD() const;
            std::optional<Ent::Gen::SmoothScaleComponentGD> SmoothScaleComponentGD() const;
            Ent::Gen::SmoothScaleComponentGD addSmoothScaleComponentGD() const;
            std::optional<Ent::Gen::FluidViewGD> FluidViewGD() const;
            Ent::Gen::FluidViewGD addFluidViewGD() const;
            std::optional<Ent::Gen::RegenMeshGD> RegenMeshGD() const;
            Ent::Gen::RegenMeshGD addRegenMeshGD() const;
            std::optional<Ent::Gen::ReviveEnergyGD> ReviveEnergyGD() const;
            Ent::Gen::ReviveEnergyGD addReviveEnergyGD() const;
            std::optional<Ent::Gen::DebugGridGD> DebugGridGD() const;
            Ent::Gen::DebugGridGD addDebugGridGD() const;
            std::optional<Ent::Gen::ChildEntityPoolComponentGD> ChildEntityPoolComponentGD() const;
            Ent::Gen::ChildEntityPoolComponentGD addChildEntityPoolComponentGD() const;
            std::optional<Ent::Gen::ProtoComponentGD> ProtoComponentGD() const;
            Ent::Gen::ProtoComponentGD addProtoComponentGD() const;
            std::optional<Ent::Gen::GameEffectSpawnerGD> GameEffectSpawnerGD() const;
            Ent::Gen::GameEffectSpawnerGD addGameEffectSpawnerGD() const;
            std::optional<Ent::Gen::ClothGD> ClothGD() const;
            Ent::Gen::ClothGD addClothGD() const;
            std::optional<Ent::Gen::FireSensorGD> FireSensorGD() const;
            Ent::Gen::FireSensorGD addFireSensorGD() const;
            std::optional<Ent::Gen::HealerGD> HealerGD() const;
            Ent::Gen::HealerGD addHealerGD() const;
            std::optional<Ent::Gen::AnimationLegsConstraintsGD> AnimationLegsConstraintsGD() const;
            Ent::Gen::AnimationLegsConstraintsGD addAnimationLegsConstraintsGD() const;
            std::optional<Ent::Gen::PathBoneRigidBodyGD> PathBoneRigidBodyGD() const;
            Ent::Gen::PathBoneRigidBodyGD addPathBoneRigidBodyGD() const;
            std::optional<Ent::Gen::FightDistanceTriggerGD> FightDistanceTriggerGD() const;
            Ent::Gen::FightDistanceTriggerGD addFightDistanceTriggerGD() const;
            std::optional<Ent::Gen::SoulSpotGD> SoulSpotGD() const;
            Ent::Gen::SoulSpotGD addSoulSpotGD() const;
            std::optional<Ent::Gen::HealTriggerGD> HealTriggerGD() const;
            Ent::Gen::HealTriggerGD addHealTriggerGD() const;
            std::optional<Ent::Gen::AnimationTailConstraintsGD> AnimationTailConstraintsGD() const;
            Ent::Gen::AnimationTailConstraintsGD addAnimationTailConstraintsGD() const;
            std::optional<Ent::Gen::VolumeConstraintGD> VolumeConstraintGD() const;
            Ent::Gen::VolumeConstraintGD addVolumeConstraintGD() const;
            std::optional<Ent::Gen::EnvStampGD> EnvStampGD() const;
            Ent::Gen::EnvStampGD addEnvStampGD() const;
            std::optional<Ent::Gen::FluidFXEntitySpawnerGD> FluidFXEntitySpawnerGD() const;
            Ent::Gen::FluidFXEntitySpawnerGD addFluidFXEntitySpawnerGD() const;
            std::optional<Ent::Gen::EnergyDrainGD> EnergyDrainGD() const;
            Ent::Gen::EnergyDrainGD addEnergyDrainGD() const;
            std::optional<Ent::Gen::AnimationEventsGeneratorGD> AnimationEventsGeneratorGD() const;
            Ent::Gen::AnimationEventsGeneratorGD addAnimationEventsGeneratorGD() const;
            std::optional<Ent::Gen::MountableGD> MountableGD() const;
            Ent::Gen::MountableGD addMountableGD() const;
            std::optional<Ent::Gen::InfoboardRegistererGD> InfoboardRegistererGD() const;
            Ent::Gen::InfoboardRegistererGD addInfoboardRegistererGD() const;
            std::optional<Ent::Gen::EventHandlerGD> EventHandlerGD() const;
            Ent::Gen::EventHandlerGD addEventHandlerGD() const;
            std::optional<Ent::Gen::SoulRespawnOpportunityGD> SoulRespawnOpportunityGD() const;
            Ent::Gen::SoulRespawnOpportunityGD addSoulRespawnOpportunityGD() const;
            std::optional<Ent::Gen::HealthAreaGD> HealthAreaGD() const;
            Ent::Gen::HealthAreaGD addHealthAreaGD() const;
            std::optional<Ent::Gen::SoundAreaGD> SoundAreaGD() const;
            Ent::Gen::SoundAreaGD addSoundAreaGD() const;
            std::optional<Ent::Gen::PathBoneInfluenceGD> PathBoneInfluenceGD() const;
            Ent::Gen::PathBoneInfluenceGD addPathBoneInfluenceGD() const;
            std::optional<Ent::Gen::ComponentWithProtoCodeGD> ComponentWithProtoCodeGD() const;
            Ent::Gen::ComponentWithProtoCodeGD addComponentWithProtoCodeGD() const;
            std::optional<Ent::Gen::CharacterControllerGD> CharacterControllerGD() const;
            Ent::Gen::CharacterControllerGD addCharacterControllerGD() const;
            std::optional<Ent::Gen::PickableComponentGD> PickableComponentGD() const;
            Ent::Gen::PickableComponentGD addPickableComponentGD() const;
            std::optional<Ent::Gen::CameraDataGD> CameraDataGD() const;
            Ent::Gen::CameraDataGD addCameraDataGD() const;
            std::optional<Ent::Gen::RegenFXGD> RegenFXGD() const;
            Ent::Gen::RegenFXGD addRegenFXGD() const;
            std::optional<Ent::Gen::PhysicsMeshDeformerGD> PhysicsMeshDeformerGD() const;
            Ent::Gen::PhysicsMeshDeformerGD addPhysicsMeshDeformerGD() const;
            std::optional<Ent::Gen::AnimationHitsConstraintsGD> AnimationHitsConstraintsGD() const;
            Ent::Gen::AnimationHitsConstraintsGD addAnimationHitsConstraintsGD() const;
            std::optional<Ent::Gen::FluidVolumeComponentGD> FluidVolumeComponentGD() const;
            Ent::Gen::FluidVolumeComponentGD addFluidVolumeComponentGD() const;
            std::optional<Ent::Gen::RegenerableVegetationGD> RegenerableVegetationGD() const;
            Ent::Gen::RegenerableVegetationGD addRegenerableVegetationGD() const;
            std::optional<Ent::Gen::ShamanVisionGD> ShamanVisionGD() const;
            Ent::Gen::ShamanVisionGD addShamanVisionGD() const;
            std::optional<Ent::Gen::CinematicGD> CinematicGD() const;
            Ent::Gen::CinematicGD addCinematicGD() const;
            std::optional<Ent::Gen::ConnectorGD> ConnectorGD() const;
            Ent::Gen::ConnectorGD addConnectorGD() const;
            std::optional<Ent::Gen::BeamTargetGD> BeamTargetGD() const;
            Ent::Gen::BeamTargetGD addBeamTargetGD() const;
            std::optional<Ent::Gen::ActorGD> ActorGD() const;
            Ent::Gen::ActorGD addActorGD() const;
            std::optional<Ent::Gen::CharacterPlatformGD> CharacterPlatformGD() const;
            Ent::Gen::CharacterPlatformGD addCharacterPlatformGD() const;
            std::optional<Ent::Gen::ReviveSideSwitcherGD> ReviveSideSwitcherGD() const;
            Ent::Gen::ReviveSideSwitcherGD addReviveSideSwitcherGD() const;
            std::optional<Ent::Gen::EnergyPoolGD> EnergyPoolGD() const;
            Ent::Gen::EnergyPoolGD addEnergyPoolGD() const;
            std::optional<Ent::Gen::PlayerComponentGD> PlayerComponentGD() const;
            Ent::Gen::PlayerComponentGD addPlayerComponentGD() const;
            std::optional<Ent::Gen::HotspotsGD> HotspotsGD() const;
            Ent::Gen::HotspotsGD addHotspotsGD() const;
            std::optional<Ent::Gen::SmallActorSpawnerGD> SmallActorSpawnerGD() const;
            Ent::Gen::SmallActorSpawnerGD addSmallActorSpawnerGD() const;
            std::optional<Ent::Gen::PathMotionControllerGD> PathMotionControllerGD() const;
            Ent::Gen::PathMotionControllerGD addPathMotionControllerGD() const;
            std::optional<Ent::Gen::CreatureAIGD> CreatureAIGD() const;
            Ent::Gen::CreatureAIGD addCreatureAIGD() const;
            std::optional<Ent::Gen::CreatureUIGD> CreatureUIGD() const;
            Ent::Gen::CreatureUIGD addCreatureUIGD() const;
            std::optional<Ent::Gen::SoundEmitterGD> SoundEmitterGD() const;
            Ent::Gen::SoundEmitterGD addSoundEmitterGD() const;
            std::optional<Ent::Gen::EnergySourceGD> EnergySourceGD() const;
            Ent::Gen::EnergySourceGD addEnergySourceGD() const;
            std::optional<Ent::Gen::ClothAnimationGD> ClothAnimationGD() const;
            Ent::Gen::ClothAnimationGD addClothAnimationGD() const;
            std::optional<Ent::Gen::CreatureGD> CreatureGD() const;
            Ent::Gen::CreatureGD addCreatureGD() const;
            std::optional<Ent::Gen::HitTriggerGD> HitTriggerGD() const;
            Ent::Gen::HitTriggerGD addHitTriggerGD() const;
            std::optional<Ent::Gen::ProjectileShooterGD> ProjectileShooterGD() const;
            Ent::Gen::ProjectileShooterGD addProjectileShooterGD() const;
            std::optional<Ent::Gen::LightComponentGD> LightComponentGD() const;
            Ent::Gen::LightComponentGD addLightComponentGD() const;
            std::optional<Ent::Gen::MounterGD> MounterGD() const;
            Ent::Gen::MounterGD addMounterGD() const;
            std::optional<Ent::Gen::AttackTriggerGD> AttackTriggerGD() const;
            Ent::Gen::AttackTriggerGD addAttackTriggerGD() const;
            std::optional<Ent::Gen::PossessableGPEGD> PossessableGPEGD() const;
            Ent::Gen::PossessableGPEGD addPossessableGPEGD() const;
            std::optional<Ent::Gen::OutfitGD> OutfitGD() const;
            Ent::Gen::OutfitGD addOutfitGD() const;
            std::optional<Ent::Gen::BreakableGD> BreakableGD() const;
            Ent::Gen::BreakableGD addBreakableGD() const;
            std::optional<Ent::Gen::PathNodeGD> PathNodeGD() const;
            Ent::Gen::PathNodeGD addPathNodeGD() const;
            std::optional<Ent::Gen::VelocityObstacleGD> VelocityObstacleGD() const;
            Ent::Gen::VelocityObstacleGD addVelocityObstacleGD() const;
            std::optional<Ent::Gen::ShapeshiftStatueGD> ShapeshiftStatueGD() const;
            Ent::Gen::ShapeshiftStatueGD addShapeshiftStatueGD() const;
            std::optional<Ent::Gen::RagdollGD> RagdollGD() const;
            Ent::Gen::RagdollGD addRagdollGD() const;
            std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD> AnimationPhysicsChainConstraintsGD() const;
            Ent::Gen::AnimationPhysicsChainConstraintsGD addAnimationPhysicsChainConstraintsGD() const;
            std::optional<Ent::Gen::ScriptComponentGD> ScriptComponentGD() const;
            Ent::Gen::ScriptComponentGD addScriptComponentGD() const;
            std::optional<Ent::Gen::FluidToRegenInjectorGD> FluidToRegenInjectorGD() const;
            Ent::Gen::FluidToRegenInjectorGD addFluidToRegenInjectorGD() const;
            std::optional<Ent::Gen::PerceivableGD> PerceivableGD() const;
            Ent::Gen::PerceivableGD addPerceivableGD() const;
            std::optional<Ent::Gen::InventoryGD> InventoryGD() const;
            Ent::Gen::InventoryGD addInventoryGD() const;
            std::optional<Ent::Gen::ItemHolderGD> ItemHolderGD() const;
            Ent::Gen::ItemHolderGD addItemHolderGD() const;
            std::optional<Ent::Gen::PathGD> PathGD() const;
            Ent::Gen::PathGD addPathGD() const;
            std::optional<Ent::Gen::PerceiverGD> PerceiverGD() const;
            Ent::Gen::PerceiverGD addPerceiverGD() const;
            std::optional<Ent::Gen::DummyComponentGD> DummyComponentGD() const;
            Ent::Gen::DummyComponentGD addDummyComponentGD() const;
            std::optional<Ent::Gen::FluidNavMeshTaggerGD> FluidNavMeshTaggerGD() const;
            Ent::Gen::FluidNavMeshTaggerGD addFluidNavMeshTaggerGD() const;
            std::optional<Ent::Gen::EnergySpoutGD> EnergySpoutGD() const;
            Ent::Gen::EnergySpoutGD addEnergySpoutGD() const;
            std::optional<Ent::Gen::PickableDistributorComponentGD> PickableDistributorComponentGD() const;
            Ent::Gen::PickableDistributorComponentGD addPickableDistributorComponentGD() const;
            std::optional<Ent::Gen::ShamanItemGD> ShamanItemGD() const;
            Ent::Gen::ShamanItemGD addShamanItemGD() const;
            std::optional<Ent::Gen::TeamGD> TeamGD() const;
            Ent::Gen::TeamGD addTeamGD() const;
            std::optional<Ent::Gen::SmallActorGD> SmallActorGD() const;
            Ent::Gen::SmallActorGD addSmallActorGD() const;
            std::optional<Ent::Gen::PhysicsMeshProviderGD> PhysicsMeshProviderGD() const;
            Ent::Gen::PhysicsMeshProviderGD addPhysicsMeshProviderGD() const;
            std::optional<Ent::Gen::SideMapGateGD> SideMapGateGD() const;
            Ent::Gen::SideMapGateGD addSideMapGateGD() const;
            std::optional<Ent::Gen::HeightMapComponentGD> HeightMapComponentGD() const;
            Ent::Gen::HeightMapComponentGD addHeightMapComponentGD() const;
            std::optional<Ent::Gen::MountIKControllerGD> MountIKControllerGD() const;
            Ent::Gen::MountIKControllerGD addMountIKControllerGD() const;
            std::optional<Ent::Gen::StaffVertebrasGD> StaffVertebrasGD() const;
            Ent::Gen::StaffVertebrasGD addStaffVertebrasGD() const;
            std::optional<Ent::Gen::SensorControllerGD> SensorControllerGD() const;
            Ent::Gen::SensorControllerGD addSensorControllerGD() const;
            std::optional<Ent::Gen::BoidsGD> BoidsGD() const;
            Ent::Gen::BoidsGD addBoidsGD() const;
            std::optional<Ent::Gen::AnimationTreeConstraintsGD> AnimationTreeConstraintsGD() const;
            Ent::Gen::AnimationTreeConstraintsGD addAnimationTreeConstraintsGD() const;
            std::optional<Ent::Gen::DistanceTriggerGD> DistanceTriggerGD() const;
            Ent::Gen::DistanceTriggerGD addDistanceTriggerGD() const;
            std::optional<Ent::Gen::QuickCreatureSwitchGD> QuickCreatureSwitchGD() const;
            Ent::Gen::QuickCreatureSwitchGD addQuickCreatureSwitchGD() const;
            std::optional<Ent::Gen::EnergyProbeGD> EnergyProbeGD() const;
            Ent::Gen::EnergyProbeGD addEnergyProbeGD() const;
            std::optional<Ent::Gen::RespawnPlaceGD> RespawnPlaceGD() const;
            Ent::Gen::RespawnPlaceGD addRespawnPlaceGD() const;
            std::optional<Ent::Gen::OutfitWearerGD> OutfitWearerGD() const;
            Ent::Gen::OutfitWearerGD addOutfitWearerGD() const;
            std::optional<Ent::Gen::VoxelSimulationGD> VoxelSimulationGD() const;
            Ent::Gen::VoxelSimulationGD addVoxelSimulationGD() const;
            std::optional<Ent::Gen::AnimationModelGD> AnimationModelGD() const;
            Ent::Gen::AnimationModelGD addAnimationModelGD() const;
            std::optional<Ent::Gen::TriggerEventCameraGD> TriggerEventCameraGD() const;
            Ent::Gen::TriggerEventCameraGD addTriggerEventCameraGD() const;
            std::optional<Ent::Gen::AnimationPlaylistGD> AnimationPlaylistGD() const;
            Ent::Gen::AnimationPlaylistGD addAnimationPlaylistGD() const;
            std::optional<Ent::Gen::MeshNavigationInfosGD> MeshNavigationInfosGD() const;
            Ent::Gen::MeshNavigationInfosGD addMeshNavigationInfosGD() const;
            std::optional<Ent::Gen::PhysicsTriggerGD> PhysicsTriggerGD() const;
            Ent::Gen::PhysicsTriggerGD addPhysicsTriggerGD() const;
            std::optional<Ent::Gen::EnergyNetworkListenerGD> EnergyNetworkListenerGD() const;
            Ent::Gen::EnergyNetworkListenerGD addEnergyNetworkListenerGD() const;
            std::optional<Ent::Gen::MissionHolderGD> MissionHolderGD() const;
            Ent::Gen::MissionHolderGD addMissionHolderGD() const;
            std::optional<Ent::Gen::RegenSwitcherGD> RegenSwitcherGD() const;
            Ent::Gen::RegenSwitcherGD addRegenSwitcherGD() const;
        };


        struct LightComponentGD : HelperObject // Object
        {
            LightComponentGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/LightComponentGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Vector3 AngleOffset() const;
            Ent::Gen::Float Brightness() const;
            Ent::Gen::Bool CastShadow() const;
            Ent::Gen::Color Color() const;
            Ent::Gen::Vector3 Direction() const;
            Ent::Gen::Bool Enabled() const;
            Ent::Gen::Float LinearAttenuationStart() const;
            Ent::Gen::Float LinearAttenuationStop() const;
            Ent::Gen::Vector3 Offset() const;
            Ent::Gen::Float RadialAttenuationStart() const;
            Ent::Gen::Float RadialAttenuationStop() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::LightType Type_() const;
            Ent::Gen::Bool VolumetricFog() const;
            Ent::Gen::String _comment() const;
        };

        struct BoidsGD : HelperObject // Object
        {
            BoidsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/BoidsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AffectedByFluid() const;
            Ent::Gen::Bool AllowMerge() const;
            Ent::Gen::Bool AutoMoveRoot() const;
            Ent::Gen::EntityRef BudEntityRef() const;
            Ent::Gen::Float BudVisualScaleMax() const;
            Ent::Gen::Float BudVisualScaleMin() const;
            Ent::Gen::Bool DisplayMaster() const;
            Ent::Gen::Float FlockingAttackDamages() const;
            Ent::Gen::Float FluidSurfaceHeightOffset() const;
            Ent::Gen::Bool ForceOutsideWater() const;
            Ent::Gen::EntityRef FullEntityPoolRef() const;
            Ent::Gen::Float GetBackToFlockingDuration() const;
            Ent::Gen::Float GhostDuration() const;
            Ent::Gen::Float HierarchyDistanceMultiplier() const;
            Ent::Gen::Float InitialRadius() const;
            Ent::Gen::Float LightBrightness() const;
            Ent::Gen::Color LightColor() const;
            Ent::Gen::Float MainTargetHeight() const;
            Ent::Gen::Float MainTargetRotateDistance() const;
            Ent::Gen::Float MainTargetSpeedMultiplier() const;
            Ent::Gen::Float MinRegenToWakeUp() const;
            Ent::Gen::Int NbAgents() const;
            Ent::Gen::Int NbAgentsPerZone() const;
            Ent::Gen::String ParamBlock() const;
            Ent::Gen::String ParamBudAppear() const;
            Ent::Gen::String ParamBudOpen() const;
            Ent::Gen::String ParamHome() const;
            Ent::Gen::String ParamMove() const;
            Ent::Gen::String ParamSwim() const;
            Ent::Gen::String ParamWakeUp() const;
            Ent::Gen::Float PointCloudSearchRadius() const;
            Ent::Gen::String PointCloudTag() const;
            Ent::Gen::String PresetName() const;
            Ent::Gen::String PresetNameBud() const;
            Ent::Gen::Float RegenMaxThreshold() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Float VisualScaleMax() const;
            Ent::Gen::Float VisualScaleMin() const;
            Ent::Gen::Float WakeUpDuration() const;
            Ent::Gen::String _comment() const;
        };

        struct Collider : HelperObject // Object
        {
            Collider(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/Collider";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String BoneName() const;
            Ent::Gen::Float RadiusFactor() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationTailConstraintsGD : HelperObject // Object
        {
            AnimationTailConstraintsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationTailConstraintsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float AngularSpeedMaxForSpeedModeFurious() const;
            Ent::Gen::Float AngularSpeedMaxForSpeedModeNone() const;
            Ent::Gen::Bool BoneInjectDirectionFromUseAmplitudeFactor() const;
            Ent::Gen::String BoneNameEnd() const;
            Ent::Gen::String BoneNameInjectDirectionFrom() const;
            Ent::Gen::String BoneNameStart() const;
            Array<Ent::Gen::Collider> Colliders() const;
            Ent::Gen::Float CollidersRadiusFactorGrounded() const;
            Ent::Gen::Float CompensateSegmentStretchFactor() const;
            Array<Ent::Gen::ConditionalRigidityAttribute> ConditionalRigidityAttributes() const;
            Array<Ent::Gen::StickToGround> StickToGrounds() const;
            Ent::Gen::Float StickToGroundsGravity() const;
            Ent::Gen::Float StickToGroundsGravityUnderwater() const;
            Ent::Gen::Float StickToGroundsRadiusFactorDead() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CinematicUpdateType : EnumPropHelper<CinematicUpdateType, CinematicUpdateTypeEnum> // Enum
        {
            using Enum = CinematicUpdateTypeEnum;
            using PropHelper<CinematicUpdateType, Enum>::operator=;
            CinematicUpdateType(Ent::Node* _node): EnumPropHelper<CinematicUpdateType, Enum>(_node) {}
            static constexpr char schemaName[] = "CinematicUpdateType";
            static constexpr char const* enumToString[] = {
                "none",
                "Internal",
                "Pesto",
                "CinematicUpdateType_COUNT",
            };
        };
        inline char const* toString(CinematicUpdateTypeEnum value)
        {
            if(size_t(value) >= std::size(CinematicUpdateType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return CinematicUpdateType::enumToString[size_t(value)];
        }
        inline char const* toInternal(CinematicUpdateTypeEnum value) { return toString(value); }
        template<> inline CinematicUpdateTypeEnum strToEnum<CinematicUpdateTypeEnum>(char const* value)
        {
            return static_cast<CinematicUpdateTypeEnum>(details::indexInEnum(value, CinematicUpdateType::enumToString));
        }

        struct CinematicSlot : HelperObject // Object
        {
            CinematicSlot(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CinematicSlot";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String ActorBone() const;
            Ent::Gen::String Anim() const;
            Ent::Gen::Bool CameraHolder() const;
            Ent::Gen::Bool CanBeInstanciated() const;
            Ent::Gen::Bool DestroyAfter() const;
            Ent::Gen::EntityRef EntityRef() const;
            Ent::Gen::Bool EventCameraHolder() const;
            Ent::Gen::Float FOV() const;
            Ent::Gen::Float FadeInDelay() const;
            Ent::Gen::Float FadeOutDelay() const;
            Ent::Gen::Transform3D InitTransform() const;
            Ent::Gen::Bool MainRole() const;
            Ent::Gen::Bool Mandatory() const;
            Ent::Gen::String Role() const;
            Ent::Gen::String RoleInNextSequence() const;
            Ent::Gen::Bool Visible() const;
            Ent::Gen::String _comment() const;
        };

        struct Sequence : HelperObject // Object
        {
            Sequence(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/Sequence";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float ActivationDelay() const;
            Ent::Gen::Bool AutoSwitchToNextSequence() const;
            Ent::Gen::String _comment() const;
            Array<Ent::Gen::CinematicSlot> actors() const;
            Ent::Gen::Bool loop() const;
            Ent::Gen::String name() const;
        };

        struct CinematicGD : HelperObject // Object
        {
            CinematicGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CinematicGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float ActivationDistance() const;
            Array<Ent::Gen::ResponsiblePointer_CineEvent_> ScriptEvents() const;
            Array<Ent::Gen::Sequence> Sequences() const;
            Ent::Gen::Bool Skippable() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::CinematicUpdateType UpdateType() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEvent : HelperObject // Object
        {
            CineEvent(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEvent";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool Active() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTrigger : HelperObject // Object
        {
            CineEventTrigger(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTrigger";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::CineEvent Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTriggerPlaySound : HelperObject // Object
        {
            CineEventTriggerPlaySound(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTriggerPlaySound";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String SoundEventName() const;
            Ent::Gen::CineEventTrigger Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTriggerPlaySequence : HelperObject // Object
        {
            CineEventTriggerPlaySequence(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTriggerPlaySequence";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Int SequenceID() const;
            Ent::Gen::CineEventTrigger Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTriggerGameStateChange : HelperObject // Object
        {
            CineEventTriggerGameStateChange(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTriggerGameStateChange";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String GameStateName() const;
            Ent::Gen::CineEventTrigger Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTriggerEventHandlerPost : HelperObject // Object
        {
            CineEventTriggerEventHandlerPost(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTriggerEventHandlerPost";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String EventCategory() const;
            Ent::Gen::String EventName() const;
            Ent::Gen::CineEventTrigger Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTest : HelperObject // Object
        {
            CineEventTest(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTest";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool InvertTest() const;
            Ent::Gen::CineEvent Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTestWait : HelperObject // Object
        {
            CineEventTestWait(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTestWait";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float Duration() const;
            Ent::Gen::CineEventTest Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTestIsCanceled : HelperObject // Object
        {
            CineEventTestIsCanceled(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTestIsCanceled";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::CineEventTest Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTestInput : HelperObject // Object
        {
            CineEventTestInput(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTestInput";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AnyButtonInput() const;
            Ent::Gen::Bool AnyJoyInput() const;
            Ent::Gen::CineEventTest Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTestEndCurrentSequence : HelperObject // Object
        {
            CineEventTestEndCurrentSequence(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTestEndCurrentSequence";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::CineEventTest Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CineEventTestCurrentGameState : HelperObject // Object
        {
            CineEventTestCurrentGameState(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CineEventTestCurrentGameState";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String GameStateName() const;
            Ent::Gen::CineEventTest Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CharacterControllerSlideData : HelperObject // Object
        {
            CharacterControllerSlideData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CharacterControllerSlideData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::ScaleConverter adherenceRecoverSpeedDependingOnTheSlope() const;
            Ent::Gen::Float adherenceThresholdHysteresis() const;
            Ent::Gen::ScaleConverter adherenceThresholdRequiredToKeepControl() const;
            Ent::Gen::Float adherenceUsingDownwardSlopeDirection() const;
            Ent::Gen::Float adherenceUsingSideSlopeDirection() const;
            Ent::Gen::Float adherenceUsingUpwardSlopeDirection() const;
            Ent::Gen::Float animblendInTime() const;
            Ent::Gen::Float friction() const;
            Ent::Gen::Float maxSlopeAngle() const;
            Ent::Gen::Float speedMediumCoeffHysteresis() const;
            Ent::Gen::ScaleConverter speedMediumCoeffIn() const;
            Ent::Gen::Float speedMediumCoeffMin() const;
        };

        struct CharacterControllerGroundNormalData : HelperObject // Object
        {
            CharacterControllerGroundNormalData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CharacterControllerGroundNormalData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AllowOtherCreatureCast() const;
            Ent::Gen::Float PercentageEdgeTolerance() const;
            Ent::Gen::Float PercentageExtirpate() const;
            Ent::Gen::String _comment() const;
        };

        struct CharacterControllerFallData : HelperObject // Object
        {
            CharacterControllerFallData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CharacterControllerFallData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ScaleConverter DamagesPerHeightFall() const;
            Ent::Gen::Float MinHeightForDamageFall() const;
            Ent::Gen::Float MinHeightForDeathFall() const;
            Ent::Gen::Float MinHeightForRecoveryFall() const;
            Ent::Gen::String _comment() const;
        };

        struct CharacterControllerClamberData : HelperObject // Object
        {
            CharacterControllerClamberData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CharacterControllerClamberData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float DropOffAngle() const;
            Ent::Gen::Float EnterAngle() const;
            Ent::Gen::Float ExitAngle() const;
            Ent::Gen::Bool IsAllowed() const;
            Ent::Gen::ScaleConverter VerticalOrientationRatio() const;
            Ent::Gen::String _comment() const;
        };

        struct CameraType : EnumPropHelper<CameraType, CameraTypeEnum> // Enum
        {
            using Enum = CameraTypeEnum;
            using PropHelper<CameraType, Enum>::operator=;
            CameraType(Ent::Node* _node): EnumPropHelper<CameraType, Enum>(_node) {}
            static constexpr char schemaName[] = "CameraType";
            static constexpr char const* enumToString[] = {
                "NONE",
                "Death",
                "Editor",
                "Event",
                "Free",
                "ThirdPerson",
                "ThirdPersonFollow",
                "ThirdPersonAim",
                "ThirdPersonClamber",
                "MotionConstraint",
                "OnSpline",
                "OnBones",
                "TopView",
                "EntitySwap",
                "Locked",
                "Pan",
                "CameraType_COUNT",
            };
        };
        inline char const* toString(CameraTypeEnum value)
        {
            if(size_t(value) >= std::size(CameraType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return CameraType::enumToString[size_t(value)];
        }
        inline char const* toInternal(CameraTypeEnum value) { return toString(value); }
        template<> inline CameraTypeEnum strToEnum<CameraTypeEnum>(char const* value)
        {
            return static_cast<CameraTypeEnum>(details::indexInEnum(value, CameraType::enumToString));
        }

        struct CameraSetterGD : HelperObject // Object
        {
            CameraSetterGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CameraSetterGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool SetPositionToHotspot() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Bool SwitchToType() const;
            Ent::Gen::CameraType Type_() const;
            Ent::Gen::String _comment() const;
        };

        struct CameraShakeData : HelperObject // Object
        {
            CameraShakeData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CameraShakeData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float shakeDuration() const;
            Ent::Gen::Float shakeFrequency() const;
            Ent::Gen::Float shakeIntensity() const;
            Ent::Gen::Vector3 shakeRotation() const;
        };

        struct BiteData : HelperObject // Object
        {
            BiteData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/BiteData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool CanBiteBiped() const;
            Ent::Gen::Bool CanBiteFriends() const;
            Ent::Gen::Bool CheckHotspotOrientation() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Bool bezierMove() const;
            Ent::Gen::Float biteDamagePerSec() const;
            Ent::Gen::Float biteDefenseDamages() const;
            Ent::Gen::Float biteDuration() const;
            Ent::Gen::Float biteMaxRange() const;
        };

        struct BehaviorScriptData : HelperObject // Object
        {
            BehaviorScriptData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/BehaviorScriptData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float additionalDangerousnessDiffToFlee() const;
            Ent::Gen::Float aimingDuration() const;
            Ent::Gen::Int answerAttackRunSpeed() const;
            Ent::Gen::Float artificialArenaRadius() const;
            Ent::Gen::Int attackAggressivityDecrease() const;
            Ent::Gen::Float attackIfEnemyHasBeenSeenSince() const;
            Ent::Gen::Bool attackInPack() const;
            Ent::Gen::Bool attackOrderCanFlee() const;
            Ent::Gen::Int attackRunSpeed() const;
            Ent::Gen::Float attackWaitCircle_Offset_Z() const;
            Ent::Gen::Bool avoidGroundMovements() const;
            Ent::Gen::Bool avoidWaterMovements() const;
            Ent::Gen::Bool blockedByScaryWeather() const;
            Ent::Gen::Bool canBite() const;
            Ent::Gen::Bool canFlee() const;
            Ent::Gen::Float closeAttack_Offset_Z() const;
            Ent::Gen::Float closeCombatDistance() const;
            Ent::Gen::Float combatFlyingHeightOffset() const;
            Ent::Gen::Int combatSpeedModeOnNodes() const;
            Ent::Gen::Float combatStopOnNodeCoolDown() const;
            Ent::Gen::Float combatStopOnNodeMaxTime() const;
            Ent::Gen::Float combatTooCloseDistance() const;
            Ent::Gen::Float combatTriggerStopOnNodeTimerDistance() const;
            Ent::Gen::Bool considersRunnerAsAMenace() const;
            Ent::Gen::Float coolDownBetweenProjectileDodge() const;
            Ent::Gen::Float drivingAimAngle() const;
            Ent::Gen::Float drivingAimSpeed() const;
            Ent::Gen::Int enemyAggressivity() const;
            Ent::Gen::Float energyAttackProbability() const;
            Ent::Gen::Float engageInCombatDistance() const;
            Ent::Gen::Float farCombatDistance() const;
            Ent::Gen::Float feelsSafeWhenDangerIsThisFar() const;
            Ent::Gen::Float fleeDistToEnemy() const;
            Ent::Gen::Float fleeMaxDist() const;
            Ent::Gen::Float fleeTime() const;
            Ent::Gen::Float flockingArenaRadius() const;
            Ent::Gen::Int friendAggressivity() const;
            Ent::Gen::Float goToTargetCheckDistance() const;
            Ent::Gen::Float guideFollowMalusScorePerSec() const;
            Ent::Gen::Float guideFollowMaxBonusScorePerSec() const;
            Ent::Gen::Float guideFollowMaxDistToScore() const;
            Ent::Gen::Float guideFollowMaxDistanceToTrail() const;
            Ent::Gen::Float guideFollowMinBonusScorePerSec() const;
            Ent::Gen::Float guideFollowMinDistToScore() const;
            Ent::Gen::Float guideFollowScoreThreshold() const;
            Ent::Gen::Float guideFollowTimeBetweenTeleport() const;
            Ent::Gen::Float guideMinSpeed() const;
            Ent::Gen::Float guideRepulsiveDistIn() const;
            Ent::Gen::Float guideRepulsiveDistOut() const;
            Ent::Gen::Int hardFeelingsFriendlyHitCount() const;
            Ent::Gen::Int hardFeelingsNotFriendlyHitCount() const;
            Ent::Gen::Float helpOtherDoneIfLifeAboveThreshold() const;
            Ent::Gen::Float helpOtherIfLifeBelowThreshold() const;
            Ent::Gen::Float innerArenaRatio() const;
            Ent::Gen::Bool isAffectedByStench() const;
            Ent::Gen::Bool isCourageous() const;
            Ent::Gen::Bool isScaredBySoundEffect() const;
            Ent::Gen::Float jumpAttackProbability() const;
            Ent::Gen::Float lifeInDangerThreshold() const;
            Ent::Gen::Float lifeInNoMoreDangerThreshold() const;
            Ent::Gen::Float lockEnemyFollowMaxDistFromGuide() const;
            Ent::Gen::Float maxDistanceToFollowBeam() const;
            Ent::Gen::Int maxFollowerCount() const;
            Ent::Gen::Float maxLookOutModeTimer() const;
            Ent::Gen::Float maxTimeBeforeStoppingToWaitForBeam() const;
            Ent::Gen::MenaceSelection menaceSelection() const;
            Ent::Gen::Float middleCombatDistance() const;
            Ent::Gen::Float minAbsoluteDistanceToTeleportToMaster() const;
            Ent::Gen::Float minDistanceToBeamPosition() const;
            Ent::Gen::Float minDistanceToFollowBeam() const;
            Ent::Gen::Float minNavmeshDistanceToTeleportToMaster() const;
            Ent::Gen::Float minTimeBeforeStoppingToWaitForBeam() const;
            Ent::Gen::Float noAttackTimeAfterAttack() const;
            Ent::Gen::Bool offerAGiftWhenChosen() const;
            Ent::Gen::Int panicAggressivityDecrease() const;
            Ent::Gen::Int panicsWhenGameEffect() const;
            Ent::Gen::Int returnOnCircleAfterMaxAttacks() const;
            Ent::Gen::Int roamSpeedModeOnNodes() const;
            Ent::Gen::Float runsForDistancesSuperiorTo() const;
            Ent::Gen::Bool searchSoulOpportunity() const;
            Ent::Gen::Float shootPreferedEnemyDistance() const;
            Array<Ent::Gen::ShootSequenceData> shootSequence() const;
            Ent::Gen::Float shootingMistakeMaxDelta() const;
            Ent::Gen::Bool shouldConquer() const;
            Ent::Gen::Bool shouldDodgeAfterAttack() const;
            Ent::Gen::Bool shouldHealPools() const;
            Ent::Gen::Bool shouldJumpInArena() const;
            Ent::Gen::Bool shouldStrafe() const;
            Ent::Gen::Bool shouldTranshumance() const;
            Ent::Gen::Float staffAngleFullHint() const;
            Ent::Gen::Float staffMaxTimeInAlert() const;
            Ent::Gen::Int staffMinScoreToAlert() const;
            Ent::Gen::Float staffTimeBeforeAlertAgain() const;
            Ent::Gen::Bool usesWarningShot() const;
        };

        struct CreatureAIGD : HelperObject // Object
        {
            CreatureAIGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CreatureAIGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            PrimArray<Ent::Gen::String> BehaviorModifiersTags() const;
            Ent::Gen::String BehaviorPath() const;
            Ent::Gen::String BehaviorState() const;
            Ent::Gen::Bool CanBeMaster() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::BehaviorScriptData behaviorScriptData() const;
            Ent::Gen::Float m_oblivionTimerAfterSuspicious() const;
            Ent::Gen::Float m_oblivionTimerBeforeSuspicious() const;
            Ent::Gen::Float m_timerBeforeCertain() const;
            Ent::Gen::Float m_timerBeforeSuspicious() const;
        };

        struct BeamStaffMode : EnumPropHelper<BeamStaffMode, BeamStaffModeEnum> // Enum
        {
            using Enum = BeamStaffModeEnum;
            using PropHelper<BeamStaffMode, Enum>::operator=;
            BeamStaffMode(Ent::Node* _node): EnumPropHelper<BeamStaffMode, Enum>(_node) {}
            static constexpr char schemaName[] = "BeamStaffMode";
            static constexpr char const* enumToString[] = {
                "Off",
                "Searching",
                "Creature",
                "PossessingGPE",
                "Shapeshifting",
                "Item",
                "UpgradeStaff",
                "SideMap",
                "PickUp",
                "Hatching",
                "Any",
                "BeamStaffMode_COUNT",
            };
        };
        inline char const* toString(BeamStaffModeEnum value)
        {
            if(size_t(value) >= std::size(BeamStaffMode::enumToString))
                throw std::runtime_error("Wrong enum value");
            return BeamStaffMode::enumToString[size_t(value)];
        }
        inline char const* toInternal(BeamStaffModeEnum value) { return toString(value); }
        template<> inline BeamStaffModeEnum strToEnum<BeamStaffModeEnum>(char const* value)
        {
            return static_cast<BeamStaffModeEnum>(details::indexInEnum(value, BeamStaffMode::enumToString));
        }

        struct BeamTargetGD : HelperObject // Object
        {
            BeamTargetGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/BeamTargetGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool CheckHotspotOrientation() const;
            Ent::Gen::String EventTriggered() const;
            Ent::Gen::HotSpotType HotspotType() const;
            Ent::Gen::Bool IsCollectable() const;
            Ent::Gen::Bool Levitate() const;
            Ent::Gen::Float MaxTargetableDistance() const;
            Ent::Gen::BeamStaffMode Mode() const;
            Ent::Gen::Bool SpendEnergy() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AttackType : EnumPropHelper<AttackType, AttackTypeEnum> // Enum
        {
            using Enum = AttackTypeEnum;
            using PropHelper<AttackType, Enum>::operator=;
            AttackType(Ent::Node* _node): EnumPropHelper<AttackType, Enum>(_node) {}
            static constexpr char schemaName[] = "AttackType";
            static constexpr char const* enumToString[] = {
                "Short",
                "Long",
                "Backward",
                "Charged",
                "Distant",
                "Push",
                "Unmount",
                "Dodge",
                "Uppercut",
                "Landing",
                "JumpOnto",
                "Bite",
                "Stomp",
                "AttackType_COUNT",
            };
        };
        inline char const* toString(AttackTypeEnum value)
        {
            if(size_t(value) >= std::size(AttackType::enumToString))
                throw std::runtime_error("Wrong enum value");
            return AttackType::enumToString[size_t(value)];
        }
        inline char const* toInternal(AttackTypeEnum value) { return toString(value); }
        template<> inline AttackTypeEnum strToEnum<AttackTypeEnum>(char const* value)
        {
            return static_cast<AttackTypeEnum>(details::indexInEnum(value, AttackType::enumToString));
        }

        struct AttackAbility : HelperObject // Object
        {
            AttackAbility(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AttackAbility";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float Damage() const;
            Ent::Gen::Float DistanceMax() const;
            Ent::Gen::Float DistanceMin() const;
            Ent::Gen::Float Duration() const;
            Ent::Gen::Float EnergyCost() const;
            Ent::Gen::FreezeData FreezeData() const;
            Ent::Gen::Float Impact() const;
            Ent::Gen::CameraShakeData ShakeData() const;
            Ent::Gen::String _comment() const;
        };

        struct AttackWeaponAbility : HelperObject // Object
        {
            AttackWeaponAbility(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AttackWeaponAbility";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::AttackAbility Backward() const;
            Ent::Gen::AttackAbility Bite() const;
            Ent::Gen::AttackAbility Charged() const;
            Ent::Gen::AttackAbility Dash() const;
            Ent::Gen::AttackAbility Distant() const;
            Ent::Gen::AttackAbility Dodge() const;
            Ent::Gen::AttackAbility JumpOnto() const;
            Ent::Gen::AttackAbility Landing() const;
            Ent::Gen::AttackAbility Long() const;
            Ent::Gen::AttackAbility Push() const;
            Ent::Gen::AttackAbility Short() const;
            Ent::Gen::AttackAbility Stomp() const;
            Ent::Gen::AttackAbility Unmount() const;
            Ent::Gen::AttackAbility Uppercut() const;
            Ent::Gen::String _comment() const;
        };

        struct AttackData : HelperObject // Object
        {
            AttackData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AttackData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::AttackType DefaultAttackType() const;
            Ent::Gen::AttackWeaponAbility Hammer() const;
            Ent::Gen::AttackWeaponAbility Knife() const;
            Ent::Gen::AttackWeaponAbility None_() const;
            Ent::Gen::AttackWeaponAbility Stick() const;
            Ent::Gen::AttackWeaponAbility Sword() const;
            Ent::Gen::String _comment() const;
        };

        struct Archetype : EnumPropHelper<Archetype, ArchetypeEnum> // Enum
        {
            using Enum = ArchetypeEnum;
            using PropHelper<Archetype, Enum>::operator=;
            Archetype(Ent::Node* _node): EnumPropHelper<Archetype, Enum>(_node) {}
            static constexpr char schemaName[] = "Archetype";
            static constexpr char const* enumToString[] = {
                "flying",
                "swimming",
                "quadripede",
                "bipede",
                "item",
                "structure",
                "activator",
                "Archetype_COUNT",
            };
        };
        inline char const* toString(ArchetypeEnum value)
        {
            if(size_t(value) >= std::size(Archetype::enumToString))
                throw std::runtime_error("Wrong enum value");
            return Archetype::enumToString[size_t(value)];
        }
        inline char const* toInternal(ArchetypeEnum value) { return toString(value); }
        template<> inline ArchetypeEnum strToEnum<ArchetypeEnum>(char const* value)
        {
            return static_cast<ArchetypeEnum>(details::indexInEnum(value, Archetype::enumToString));
        }

        struct AnimationTreeConstraintsGD_GrowData : HelperObject // Object
        {
            AnimationTreeConstraintsGD_GrowData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::GrowData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float DegrowShakeForce() const;
            Ent::Gen::Float GrowShakeForce() const;
            Ent::Gen::Float GrowSpeed() const;
            Ent::Gen::GrowingState GrowingState() const;
            Ent::Gen::ProgressSoundEventData ProgressSoundEventData() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationTreeConstraintsGD_ForceData : HelperObject // Object
        {
            AnimationTreeConstraintsGD_ForceData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::ForceData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AutoSetupForceInfluence() const;
            Ent::Gen::Int AutoSetupForceInfluenceLevelStart() const;
            Ent::Gen::Int AutoSetupForceInfluenceLevelStop() const;
            Ent::Gen::Float AutoSetupForceInfluenceValueAfterStop() const;
            Ent::Gen::Float AutoSetupForceInfluenceValueBeforeStart() const;
            Ent::Gen::Float AutoSetupForceInfluenceValueStart() const;
            Ent::Gen::Float AutoSetupForceInfluenceValueStop() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationTreeConstraintsGD_BendData : HelperObject // Object
        {
            AnimationTreeConstraintsGD_BendData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::BendData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AcceptDrag() const;
            Ent::Gen::Bool AcceptDragOnBaseBone() const;
            Ent::Gen::Float AttractDuration() const;
            Ent::Gen::Float DragOnBaseBoneAttractionStartFactor() const;
            Ent::Gen::Int MaxBendAngleFirstBone() const;
            Ent::Gen::Float MaxBendAngleValueAtFirstBone() const;
            Ent::Gen::Float MaxBendAngleValueAtLastBone() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationTreeConstraintsGD : HelperObject // Object
        {
            AnimationTreeConstraintsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::AnimationTreeConstraintsGD_BendData BendData() const;
            Ent::Gen::AnimationTreeConstraintsGD_ForceData ForceData() const;
            Ent::Gen::AnimationTreeConstraintsGD_GrowData GrowData() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationLegsConstraints_SlopeOffsetInfo : HelperObject // Object
        {
            AnimationLegsConstraints_SlopeOffsetInfo(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationLegsConstraints::SlopeOffsetInfo";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float MaxSlopeAngle() const;
            Ent::Gen::Vector3 RotationOffset() const;
            Ent::Gen::Vector3 TranslationOffset() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationLegsConstraintsGD : HelperObject // Object
        {
            AnimationLegsConstraintsGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationLegsConstraintsGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AllowHeightMapCastFallback() const;
            Ent::Gen::AnimationLegsConstraints_SlopeOffsetInfo AscendingSlopeOffsetInfo() const;
            Ent::Gen::Float BackLegsCompensateExtensionThreshold() const;
            Ent::Gen::Vector2 BackLegsHeightRangeForIKInfluence() const;
            Ent::Gen::Bool BoneBending() const;
            Ent::Gen::Float BoneBendingAnticipation() const;
            Ent::Gen::Float BoneBendingAnticipationBackward() const;
            Ent::Gen::Float BoneBendingLocomotionInfluenceSpeed() const;
            Ent::Gen::Float CastDeltaDistToTriggerSmooth() const;
            Ent::Gen::AnimationLegsConstraints_SlopeOffsetInfo DescendingSlopeOffsetInfo() const;
            Ent::Gen::Float FeetInfluence() const;
            Ent::Gen::Float FrontLegsCompensateExtensionThreshold() const;
            Ent::Gen::Vector2 FrontLegsHeightRangeForIKInfluence() const;
            Ent::Gen::Float GlobalInfluence() const;
            Ent::Gen::Float LegInfluence() const;
            Ent::Gen::Bool LegLock() const;
            Ent::Gen::Float MaxHeightForFootInfluence() const;
            Ent::Gen::Float ObstructionCastHitPosMarginOffsetFactor() const;
            Ent::Gen::Float ObstructionCastOffsetFactor() const;
            Ent::Gen::Float ObstructionCastSafeRadiusFactor() const;
            Ent::Gen::ScaleConverter SpeedFactorFromLockedRootDistance() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Bool UseObstructionCast() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationEventsGeneratorGD_TrackedBone : HelperObject // Object
        {
            AnimationEventsGeneratorGD_TrackedBone(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationEventsGeneratorGD::TrackedBone";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String Name() const;
            Ent::Gen::Int OffsetFrameCountStart() const;
            Ent::Gen::Int OffsetFrameCountStop() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimationEventsGeneratorGD : HelperObject // Object
        {
            AnimationEventsGeneratorGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimationEventsGeneratorGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ComponentGD Super() const;
            Array<Ent::Gen::AnimationEventsGeneratorGD_TrackedBone> TrackedBones() const;
            Ent::Gen::String _comment() const;
        };

        struct AnimTagTimelineTransition : EnumPropHelper<AnimTagTimelineTransition, AnimTagTimelineTransitionEnum> // Enum
        {
            using Enum = AnimTagTimelineTransitionEnum;
            using PropHelper<AnimTagTimelineTransition, Enum>::operator=;
            AnimTagTimelineTransition(Ent::Node* _node): EnumPropHelper<AnimTagTimelineTransition, Enum>(_node) {}
            static constexpr char schemaName[] = "AnimTagTimelineTransition";
            static constexpr char const* enumToString[] = {
                "beginning",
                "copy",
                "reverse",
                "AnimTagTimelineTransition_COUNT",
            };
        };
        inline char const* toString(AnimTagTimelineTransitionEnum value)
        {
            if(size_t(value) >= std::size(AnimTagTimelineTransition::enumToString))
                throw std::runtime_error("Wrong enum value");
            return AnimTagTimelineTransition::enumToString[size_t(value)];
        }
        inline char const* toInternal(AnimTagTimelineTransitionEnum value) { return toString(value); }
        template<> inline AnimTagTimelineTransitionEnum strToEnum<AnimTagTimelineTransitionEnum>(char const* value)
        {
            return static_cast<AnimTagTimelineTransitionEnum>(details::indexInEnum(value, AnimTagTimelineTransition::enumToString));
        }

        struct AnimTag : EnumPropHelper<AnimTag, AnimTagEnum> // Enum
        {
            using Enum = AnimTagEnum;
            using PropHelper<AnimTag, Enum>::operator=;
            AnimTag(Ent::Node* _node): EnumPropHelper<AnimTag, Enum>(_node) {}
            static constexpr char schemaName[] = "AnimTag";
            static constexpr char const* enumToString[] = {
                "none",
                "apex",
                "forward",
                "forwardright",
                "right",
                "backwardright",
                "backward",
                "backwardleft",
                "left",
                "forwardleft",
                "regular",
                "alignedregular",
                "goofy",
                "alignedgoofy",
                "top",
                "bottom",
                "up",
                "upforward",
                "upward",
                "down",
                "downforward",
                "downward",
                "in",
                "out",
                "horizontal",
                "vertical",
                "count",
            };
        };
        inline char const* toString(AnimTagEnum value)
        {
            if(size_t(value) >= std::size(AnimTag::enumToString))
                throw std::runtime_error("Wrong enum value");
            return AnimTag::enumToString[size_t(value)];
        }
        inline char const* toInternal(AnimTagEnum value) { return toString(value); }
        template<> inline AnimTagEnum strToEnum<AnimTagEnum>(char const* value)
        {
            return static_cast<AnimTagEnum>(details::indexInEnum(value, AnimTag::enumToString));
        }

        struct MoveCapacityData_AnimTagTimelineTransitionItem : HelperObject // Object
        {
            MoveCapacityData_AnimTagTimelineTransitionItem(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MoveCapacityData::AnimTagTimelineTransitionItem";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::AnimTag to() const;
            Ent::Gen::AnimTagTimelineTransition type() const;
        };

        struct MoveCapacityData_AnimTagTimelineTransitionTable : HelperObject // Object
        {
            MoveCapacityData_AnimTagTimelineTransitionTable(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MoveCapacityData::AnimTagTimelineTransitionTable";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::AnimTag from_() const;
            Array<Ent::Gen::MoveCapacityData_AnimTagTimelineTransitionItem> transitions() const;
        };

        struct MoveCapacityData : HelperObject // Object
        {
            MoveCapacityData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/MoveCapacityData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::Float airControlFactor() const;
            Ent::Gen::Bool allowClampSpeedBiggerThanLocomotionDuringBlend() const;
            Ent::Gen::Bool allowKeepAnimationPlayRatioUnclamped() const;
            Ent::Gen::Float angularSpeedMaxFlyDumpFactor() const;
            Ent::Gen::Float angularSpeedMaxGroundDumpFactor() const;
            Ent::Gen::Float angularSpeedMaxRiderDumpFactor() const;
            Ent::Gen::Float angularSpeedMaxWaterDumpFactor() const;
            Ent::Gen::MoveCapacityData_AnimTagTimelineTransitionTable animTagTimelineTransitionTable() const;
            Ent::Gen::Float brakeDeceleration() const;
            Ent::Gen::Float capsuleBigRadius() const;
            Ent::Gen::Float capsuleEnormousRadius() const;
            Ent::Gen::Float capsuleMediumRadius() const;
            Ent::Gen::Float capsuleSmallRadius() const;
            Ent::Gen::Float capsuleTinyRadius() const;
            Ent::Gen::ScaleConverter constraintDetectionAnticipation() const;
            Ent::Gen::Vector3 constraintDetectionOffset() const;
            Ent::Gen::ScaleConverter constraintDetectionRadius() const;
            Ent::Gen::Float coyoteJumpMaxTime() const;
            Ent::Gen::Float crashPreventionSafeguardFactor() const;
            Ent::Gen::Bool doubleJump() const;
            Ent::Gen::ScaleConverter dropPlaneLegLenFactor() const;
            Ent::Gen::Bool dropSyncTrajectoryAndVisual() const;
            Ent::Gen::Float ellipseCoeff() const;
            Ent::Gen::ScaleConverter extirpateObstacleAcceleration() const;
            Ent::Gen::Float extirpateObstacleDuration() const;
            Ent::Gen::ScaleConverter flyCentrifugalCoeff() const;
            Ent::Gen::Float flyCentrifugalRate() const;
            Ent::Gen::Float jumpAnalogScale() const;
            Ent::Gen::Bool jumpOntoPosition() const;
            Ent::Gen::Float ledgeApproachSpeedMaxZ() const;
            Ent::Gen::Float ledgeDepthRadiusCoeff() const;
            Ent::Gen::Float ledgeMaxDistance() const;
            Ent::Gen::Float ledgeMaxHeightEpsilon() const;
            Ent::Gen::Float ledgeMinDepthEpsilon() const;
            Ent::Gen::Float ledgeMinWidthEpsilon() const;
            Ent::Gen::Float legLength() const;
            Ent::Gen::Float mass() const;
            Ent::Gen::Float maxAverageSpeedDuringJumpOnto() const;
            Ent::Gen::Float maxFlapTime() const;
            Ent::Gen::Float maxTimeBetweenFlaps() const;
            Ent::Gen::Float minFlapTime() const;
            Ent::Gen::Float minSpeedToSteerPitch() const;
            Ent::Gen::Float minTimeBetweenFlaps() const;
            Ent::Gen::MoveCapacityData_OrientationSpeed orientationSpeedFly() const;
            Ent::Gen::MoveCapacityData_OrientationSpeed orientationSpeedGround() const;
            Ent::Gen::MoveCapacityData_OrientationSpeed orientationSpeedWater() const;
            Ent::Gen::Float patinateSpeedMinEnter() const;
            Ent::Gen::Float patinateSpeedMinExit() const;
            Ent::Gen::Float reachSpeedAcceleration() const;
            Array<Ent::Gen::MoveCapacityData_ReachSpeed> reachSpeedByLocomotion() const;
            Ent::Gen::Float reachSpeedDeceleration() const;
            Ent::Gen::Bool reactToOtherCharacterBodyCollision() const;
            Ent::Gen::Float sphereCastRadiusRatio() const;
            Ent::Gen::Float sphereOverrideRadius() const;
            Ent::Gen::Float strafeBlendIn() const;
            Ent::Gen::Float strafeBlendWeightMinToChangeAnim() const;
            Ent::Gen::Float strafeOrientationRateFactor() const;
            Ent::Gen::SpeedMode strafeSpeedModeMax() const;
            Ent::Gen::Float strafeStopOrientationRateFactor() const;
            Ent::Gen::Float strafeTurnAngleMin() const;
            Ent::Gen::Float trajectoryRateFactorDuringLateralLand() const;
            Ent::Gen::Float turnAroundInputDirectionAngleDeltaMin() const;
        };

        struct CharacterControllerGD : HelperObject // Object
        {
            CharacterControllerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CharacterControllerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool AllowHeightMapFallback() const;
            Ent::Gen::CharacterControllerClamberData ClamberData() const;
            Ent::Gen::CharacterControllerFallData FallData() const;
            Ent::Gen::CharacterControllerGroundNormalData GroundNormalData() const;
            Ent::Gen::HeadCollisionBehaviorData HeadCollisionData() const;
            Ent::Gen::ImmersedBehaviorData ImmersedData() const;
            Ent::Gen::InputCollisionBehaviorData InputCollisionData() const;
            Ent::Gen::MeshNavigationBehaviorData MeshNavigationData() const;
            Ent::Gen::PredictionBehaviorData PredictionData() const;
            Ent::Gen::Vector3 RotationSmooth() const;
            Ent::Gen::CharacterControllerSlideData SlideData() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::MoveCapacityData moveCapacityData() const;
        };

        struct AnimMirroringSpecData : HelperObject // Object
        {
            AnimMirroringSpecData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimMirroringSpecData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Ent::Gen::String name() const;
            Ent::Gen::String name2() const;
            Ent::Gen::String spec() const;
        };

        struct AnimMirroringData : HelperObject // Object
        {
            AnimMirroringData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AnimMirroringData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            Array<Ent::Gen::AnimMirroringSpecData> specs() const;
        };

        struct AnimationControllerGD : HelperObject // Object
        {
            AnimationControllerGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./MergedComponents.json#/definitions/AnimationControllerGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String EDITOR_skeleton() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::String animDatabase() const;
            Ent::Gen::AnimMirroringData mirroringData() const;
            Ent::Gen::Float romLookAtInfluence() const;
            Ent::Gen::String skeleton() const;
            Ent::Gen::String syncDataName() const;
        };

        struct ActorStates : UnionSetBase<ResponsiblePointer_ActorState_> // union_set
        {
            ActorStates(Ent::Node* _node)
                : UnionSetBase<ResponsiblePointer_ActorState_>(_node)
            {
            }
            static constexpr char schemaName[] = "./Scene-schema.json#/definitions/ActorStates";
            char const* getType() const;
            std::optional<Ent::Gen::ActorStateAlive> ActorStateAlive() const;
            Ent::Gen::ActorStateAlive addActorStateAlive() const;
            std::optional<Ent::Gen::ActorStateBeingImmersed> ActorStateBeingImmersed() const;
            Ent::Gen::ActorStateBeingImmersed addActorStateBeingImmersed() const;
            std::optional<Ent::Gen::ActorStateBeingInAir> ActorStateBeingInAir() const;
            Ent::Gen::ActorStateBeingInAir addActorStateBeingInAir() const;
            std::optional<Ent::Gen::ActorStateBeingOnGround> ActorStateBeingOnGround() const;
            Ent::Gen::ActorStateBeingOnGround addActorStateBeingOnGround() const;
            std::optional<Ent::Gen::ActorStateBuried> ActorStateBuried() const;
            Ent::Gen::ActorStateBuried addActorStateBuried() const;
            std::optional<Ent::Gen::ActorStateDead> ActorStateDead() const;
            Ent::Gen::ActorStateDead addActorStateDead() const;
            std::optional<Ent::Gen::ActorStateHasNoBody> ActorStateHasNoBody() const;
            Ent::Gen::ActorStateHasNoBody addActorStateHasNoBody() const;
            std::optional<Ent::Gen::ActorStateHoldingItem> ActorStateHoldingItem() const;
            Ent::Gen::ActorStateHoldingItem addActorStateHoldingItem() const;
            std::optional<Ent::Gen::ActorStateInvincible> ActorStateInvincible() const;
            Ent::Gen::ActorStateInvincible addActorStateInvincible() const;
            std::optional<Ent::Gen::ActorStateRegenerationFull> ActorStateRegenerationFull() const;
            Ent::Gen::ActorStateRegenerationFull addActorStateRegenerationFull() const;
            std::optional<Ent::Gen::ActorStateRegenerationLow> ActorStateRegenerationLow() const;
            Ent::Gen::ActorStateRegenerationLow addActorStateRegenerationLow() const;
            std::optional<Ent::Gen::ActorStateTeleport> ActorStateTeleport() const;
            Ent::Gen::ActorStateTeleport addActorStateTeleport() const;
            std::optional<Ent::Gen::EntityStateBoidsHomePos> EntityStateBoidsHomePos() const;
            Ent::Gen::EntityStateBoidsHomePos addEntityStateBoidsHomePos() const;
            std::optional<Ent::Gen::EntityStateEnergyRootState> EntityStateEnergyRootState() const;
            Ent::Gen::EntityStateEnergyRootState addEntityStateEnergyRootState() const;
            std::optional<Ent::Gen::EntityStateEnergySpoutState> EntityStateEnergySpoutState() const;
            Ent::Gen::EntityStateEnergySpoutState addEntityStateEnergySpoutState() const;
            std::optional<Ent::Gen::EntityStateForceCanBeTargeted> EntityStateForceCanBeTargeted() const;
            Ent::Gen::EntityStateForceCanBeTargeted addEntityStateForceCanBeTargeted() const;
            std::optional<Ent::Gen::EntityStateMask> EntityStateMask() const;
            Ent::Gen::EntityStateMask addEntityStateMask() const;
            std::optional<Ent::Gen::EntityStatePlayer> EntityStatePlayer() const;
            Ent::Gen::EntityStatePlayer addEntityStatePlayer() const;
            std::optional<Ent::Gen::EntityStateVoxelsVolume> EntityStateVoxelsVolume() const;
            Ent::Gen::EntityStateVoxelsVolume addEntityStateVoxelsVolume() const;
        };

        struct Object : HelperObject // Object
        {
            Object(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./Scene-schema.json#/definitions/Object";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorStates ActorStates() const;
            Ent::Gen::Color Color() const;
            Ent::Gen::Object_Components Components() const;
            Ent::Gen::String InstanceOf() const;
            Ent::Gen::Object_MaxActivationLevel MaxActivationLevel() const;
            Ent::Gen::String Name() const;
            Ent::Gen::String Thumbnail() const;
            Ent::Gen::Bool __removed__() const;
            Ent::Gen::String _comment() const;
        };

        struct UnitTestComponent : HelperObject // Object
        {
            UnitTestComponent(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./EditionComponents.json#/definitions/UnitTestComponent";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Object Entity() const;
            Ent::Gen::PrimitiveSet<ReviveSideEnum> EnumSet() const;
            Ent::Gen::Position Position() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct Entity : HelperObject // Object
        {
            Entity(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./Scene-schema.json#/definitions/Entity";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorStates ActorStates() const;
            Ent::Gen::Color Color() const;
            Ent::Gen::Components Components() const;
            Ent::Gen::String InstanceOf() const;
            Ent::Gen::MaxActivationLevel MaxActivationLevel() const;
            Ent::Gen::String Name() const;
            Ent::Gen::String Thumbnail() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateTeleport_Inputs : HelperObject // Object
        {
            ActorStateTeleport_Inputs(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateTeleport::Inputs";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Orientation Orientation() const;
            Ent::Gen::Position Position() const;
            Ent::Gen::Bool ResetCamera() const;
            Ent::Gen::Bool TouchGround() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorState : HelperObject // Object
        {
            ActorState(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorState";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
        
        };

        struct EntityStateVoxelsVolume : HelperObject // Object
        {
            EntityStateVoxelsVolume(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EntityStateVoxelsVolume";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String VoxelsState() const;
            Ent::Gen::String _comment() const;
        };

        struct EntityStatePlayer : HelperObject // Object
        {
            EntityStatePlayer(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EntityStatePlayer";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EntityStateMask : HelperObject // Object
        {
            EntityStateMask(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EntityStateMask";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String MaskMeshPath() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EntityStateForceCanBeTargeted : HelperObject // Object
        {
            EntityStateForceCanBeTargeted(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EntityStateForceCanBeTargeted";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool CanBeTargeted() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EntityStateEnergySpoutState : HelperObject // Object
        {
            EntityStateEnergySpoutState(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EntityStateEnergySpoutState";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ReviveSide ReviveSide() const;
            Array<Ent::Gen::ReviveSideEvent> ReviveSideEvents() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EntityStateEnergyRootState : HelperObject // Object
        {
            EntityStateEnergyRootState(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EntityStateEnergyRootState";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float Energy() const;
            Ent::Gen::ReviveSide ReviveSide() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct EntityStateBoidsHomePos : HelperObject // Object
        {
            EntityStateBoidsHomePos(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/EntityStateBoidsHomePos";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Position HomePosition() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateTeleport : HelperObject // Object
        {
            ActorStateTeleport(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateTeleport";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorStateTeleport_Inputs Inputs() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateRegenerationLow : HelperObject // Object
        {
            ActorStateRegenerationLow(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateRegenerationLow";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool NeedToBeFreed() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateRegenerationFull : HelperObject // Object
        {
            ActorStateRegenerationFull(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateRegenerationFull";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateInvincible : HelperObject // Object
        {
            ActorStateInvincible(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateInvincible";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateHoldingItem : HelperObject // Object
        {
            ActorStateHoldingItem(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateHoldingItem";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef InventoryEntityRef() const;
            Ent::Gen::EntityRef ItemEntityRef() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateHasNoBody : HelperObject // Object
        {
            ActorStateHasNoBody(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateHasNoBody";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateDead : HelperObject // Object
        {
            ActorStateDead(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateDead";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::LastAliveReviveSide LastAliveReviveSide() const;
            Ent::Gen::Float ReviveLifeSigned() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateBuried : HelperObject // Object
        {
            ActorStateBuried(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateBuried";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateBeingOnGround : HelperObject // Object
        {
            ActorStateBeingOnGround(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateBeingOnGround";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateBeingInAir : HelperObject // Object
        {
            ActorStateBeingInAir(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateBeingInAir";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateBeingImmersed : HelperObject // Object
        {
            ActorStateBeingImmersed(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateBeingImmersed";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct ActorStateAlive : HelperObject // Object
        {
            ActorStateAlive(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorStateAlive";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float Life() const;
            Ent::Gen::ReviveSide ReviveSide() const;
            Ent::Gen::StunGauge StunGauge() const;
            Ent::Gen::ActorState Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AbilityData : HelperObject // Object
        {
            AbilityData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AbilityData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String _comment() const;
            PrimArray<Ent::Gen::ActorAbility> abilities() const;
        };

        struct ActorGD : HelperObject // Object
        {
            ActorGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ActorGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Archetype Archetype() const;
            Ent::Gen::StyleMode ClassStyleTag() const;
            Ent::Gen::String FactionName() const;
            Ent::Gen::String Icon() const;
            Ent::Gen::Bool InSpiritWorld() const;
            Ent::Gen::Specie Specie() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::Bool Weapon() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::AbilityData abilityData() const;
            Ent::Gen::AttackData attackData() const;
            Ent::Gen::LifeAndDamageData lifeAndDamageData() const;
            Ent::Gen::ProjectileData projectileData() const;
            Ent::Gen::Float radius() const;
            Ent::Gen::ShootData shootData() const;
            Ent::Gen::StunData stunData() const;
            Ent::Gen::Float volume() const;
        };

        struct ProjectileGD : HelperObject // Object
        {
            ProjectileGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ProjectileGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ActorGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct CreatureGD : HelperObject // Object
        {
            CreatureGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/CreatureGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Bool DisableLookAt() const;
            Ent::Gen::Float DivePitchAngleMax() const;
            Ent::Gen::Float DivePitchAngleMin() const;
            Ent::Gen::Float FlyPitchAngleMax() const;
            Ent::Gen::Float FlyPitchAngleMin() const;
            Ent::Gen::Bool IsBig() const;
            Ent::Gen::Bool IsDivinity() const;
            Ent::Gen::Bool IsGuardian() const;
            Ent::Gen::Bool IsStaff() const;
            Ent::Gen::Bool SpawnSoulIfNoEnemy() const;
            Ent::Gen::SpeedFastMinDuration SpeedFastMinDuration() const;
            Ent::Gen::ActorGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::BiteData biteData() const;
            Ent::Gen::CreatureDangerousness dangerousnessData() const;
            Ent::Gen::FusionData fusionData() const;
            Ent::Gen::InteractData interactData() const;
            Ent::Gen::MountData mountData() const;
            Ent::Gen::RevivedData revivedData() const;
        };

        struct ClothGD : HelperObject // Object
        {
            ClothGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ClothGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::String BodyEventsPath() const;
            Ent::Gen::String BodyNamePath() const;
            PrimArray<Ent::Gen::String> SoundBanks() const;
            Ent::Gen::SoundEventMapping SoundEventMappingRules() const;
            Ent::Gen::ActorGD Super() const;
            Ent::Gen::String _comment() const;
        };

        struct AIContextSlot : HelperObject // Object
        {
            AIContextSlot(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AIContextSlot";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Int Count() const;
            Ent::Gen::String Name() const;
            Ent::Gen::String _comment() const;
        };

        struct AIContextGD : HelperObject // Object
        {
            AIContextGD(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/AIContextGD";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::Float FollowAccelerationCoeff() const;
            Ent::Gen::Float FollowCanStopMaxStateDuration() const;
            Ent::Gen::Float FollowCanStopMaxTimeInExpandedZone() const;
            Ent::Gen::Float FollowDecelerationCoeff() const;
            Ent::Gen::Float FollowDeltaAngleTarget() const;
            Ent::Gen::Float FollowHotspotRadius() const;
            Ent::Gen::Float FollowHotspotSpace() const;
            Ent::Gen::Float FollowRandomSpeedZoneInBeginCoeffMax() const;
            Ent::Gen::Float FollowRandomSpeedZoneInBeginCoeffMin() const;
            Ent::Gen::Float FollowRandomSpeedZoneInEndCoeffMax() const;
            Ent::Gen::Float FollowRandomSpeedZoneInEndCoeffMin() const;
            Ent::Gen::Float FollowRandomSynchroDelayMax() const;
            Ent::Gen::Float FollowRandomSynchroDelayMin() const;
            Ent::Gen::Float FollowSpeedChangeThreshold() const;
            Ent::Gen::Float FollowSpeedZoneInBegin() const;
            Ent::Gen::Float FollowSpeedZoneInEnd() const;
            Ent::Gen::Float FollowSpeedZoneOutEnd() const;
            Ent::Gen::Float FollowTargetDistRadiusFactor() const;
            Ent::Gen::ComponentGD Super() const;
            Ent::Gen::String _comment() const;
            Ent::Gen::Float attackCircleRadius() const;
            Ent::Gen::Float distanceBetweenCreatures() const;
            Ent::Gen::Float distantReachCircleRadius() const;
            Ent::Gen::Float followCircleRadius() const;
            Ent::Gen::Float lockTargetCircleRadius() const;
            Array<Ent::Gen::AIContextSlot> slots() const;
        };

        struct ActorAbility : EnumPropHelper<ActorAbility, ActorAbilityEnum> // Enum
        {
            using Enum = ActorAbilityEnum;
            using PropHelper<ActorAbility, Enum>::operator=;
            ActorAbility(Ent::Node* _node): EnumPropHelper<ActorAbility, Enum>(_node) {}
            static constexpr char schemaName[] = "ActorAbility";
            static constexpr char const* enumToString[] = {
                "landing",
                "crouch",
                "fly",
                "ride",
                "dive",
                "stinky",
                "ActorAbility_COUNT",
            };
        };
        inline char const* toString(ActorAbilityEnum value)
        {
            if(size_t(value) >= std::size(ActorAbility::enumToString))
                throw std::runtime_error("Wrong enum value");
            return ActorAbility::enumToString[size_t(value)];
        }
        inline char const* toInternal(ActorAbilityEnum value) { return toString(value); }
        template<> inline ActorAbilityEnum strToEnum<ActorAbilityEnum>(char const* value)
        {
            return static_cast<ActorAbilityEnum>(details::indexInEnum(value, ActorAbility::enumToString));
        }

        struct ActorCategory : EnumPropHelper<ActorCategory, ActorCategoryEnum> // Enum
        {
            using Enum = ActorCategoryEnum;
            using PropHelper<ActorCategory, Enum>::operator=;
            ActorCategory(Ent::Node* _node): EnumPropHelper<ActorCategory, Enum>(_node) {}
            static constexpr char schemaName[] = "ActorCategory";
            static constexpr char const* enumToString[] = {
                "CATEGORY_All",
                "CATEGORY_Action",
                "CATEGORY_AnimationLegConstraint",
                "CATEGORY_ActionAttack",
                "CATEGORY_Attitude",
                "CATEGORY_Context",
                "CATEGORY_ActionCosmetic",
                "CATEGORY_ActionDamage",
                "CATEGORY_ActionDefault",
                "CATEGORY_ActionDie",
                "CATEGORY_Environment",
                "CATEGORY_Fall",
                "CATEGORY_Hint",
                "CATEGORY_LookAt",
                "CATEGORY_ActionJump",
                "CATEGORY_ActionLand",
                "CATEGORY_Life",
                "CATEGORY_Locomotion",
                "CATEGORY_ActionMove",
                "CATEGORY_Persistent",
                "CATEGORY_Purgatory",
                "CATEGORY_ActionSlide",
                "CATEGORY_ActionStop",
                "CATEGORY_ActionStrafe",
                "CATEGORY_Transition",
                "CATEGORY_Trigger",
                "CATEGORY_ActionWingFlutter",
                "CATEGORY_Health",
                "CATEGORY_HealthAlive",
                "CATEGORY_HealthDead",
                "CATEGORY_Regeneration",
                "CATEGORY_EntitySwitchTransition",
                "CATEGORY_EnergyRoot",
                "CATEGORY_EnergySpout",
                "CATEGORY_GPE",
                "ActorCategory_COUNT",
            };
        };
        inline char const* toString(ActorCategoryEnum value)
        {
            if(size_t(value) >= std::size(ActorCategory::enumToString))
                throw std::runtime_error("Wrong enum value");
            return ActorCategory::enumToString[size_t(value)];
        }
        inline char const* toInternal(ActorCategoryEnum value) { return toString(value); }
        template<> inline ActorCategoryEnum strToEnum<ActorCategoryEnum>(char const* value)
        {
            return static_cast<ActorCategoryEnum>(details::indexInEnum(value, ActorCategory::enumToString));
        }

        struct InventoryTags : EnumPropHelper<InventoryTags, InventoryTagsEnum> // Enum
        {
            using Enum = InventoryTagsEnum;
            using PropHelper<InventoryTags, Enum>::operator=;
            InventoryTags(Ent::Node* _node): EnumPropHelper<InventoryTags, Enum>(_node) {}
            static constexpr char schemaName[] = "InventoryTags";
            static constexpr char const* enumToString[] = {
                "outfit",
                "item",
                "default",
                "neutral",
                "sacred",
                "cursed",
                "skeleton",
                "zombie",
                "full",
                "soul",
                "disguise",
                "soulfreedflying",
                "soulfreednormal",
                "InventoryTags_COUNT",
            };
        };
        inline char const* toString(InventoryTagsEnum value)
        {
            if(size_t(value) >= std::size(InventoryTags::enumToString))
                throw std::runtime_error("Wrong enum value");
            return InventoryTags::enumToString[size_t(value)];
        }
        inline char const* toInternal(InventoryTagsEnum value) { return toString(value); }
        template<> inline InventoryTagsEnum strToEnum<InventoryTagsEnum>(char const* value)
        {
            return static_cast<InventoryTagsEnum>(details::indexInEnum(value, InventoryTags::enumToString));
        }

        struct MapOfObjectItem_A : HelperObject // Object
        {
            MapOfObjectItem_A(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String Value() const;
            Ent::Gen::String _comment() const;
        };

        struct Pasta_Easing_Curve : EnumPropHelper<Pasta_Easing_Curve, Pasta_Easing_CurveEnum> // Enum
        {
            using Enum = Pasta_Easing_CurveEnum;
            using PropHelper<Pasta_Easing_Curve, Enum>::operator=;
            Pasta_Easing_Curve(Ent::Node* _node): EnumPropHelper<Pasta_Easing_Curve, Enum>(_node) {}
            static constexpr char schemaName[] = "Pasta::Easing::Curve";
            static constexpr char const* enumToString[] = {
                "Linear",
                "EaseInSin",
                "EaseInQuad",
                "EaseInCubic",
                "EaseInQuart",
                "EaseInQuint",
                "EaseInExp",
                "EaseOutSin",
                "EaseOutQuad",
                "EaseOutCubic",
                "EaseOutQuart",
                "EaseOutQuint",
                "EaseOutExp",
                "EaseInoutSin",
                "EaseInoutQuad",
                "EaseInoutCubic",
                "EaseInoutQuart",
                "EaseInoutQuint",
                "EaseInoutExp",
                "EaseInCirc",
                "EaseOutCirc",
                "EaseInoutCirc",
                "EaseOutElastic",
                "Count",
            };
        };
        inline char const* toString(Pasta_Easing_CurveEnum value)
        {
            if(size_t(value) >= std::size(Pasta_Easing_Curve::enumToString))
                throw std::runtime_error("Wrong enum value");
            return Pasta_Easing_Curve::enumToString[size_t(value)];
        }
        inline char const* toInternal(Pasta_Easing_CurveEnum value) { return toString(value); }
        template<> inline Pasta_Easing_CurveEnum strToEnum<Pasta_Easing_CurveEnum>(char const* value)
        {
            return static_cast<Pasta_Easing_CurveEnum>(details::indexInEnum(value, Pasta_Easing_Curve::enumToString));
        }

        struct PhysicsLayer : EnumPropHelper<PhysicsLayer, PhysicsLayerEnum> // Enum
        {
            using Enum = PhysicsLayerEnum;
            using PropHelper<PhysicsLayer, Enum>::operator=;
            PhysicsLayer(Ent::Node* _node): EnumPropHelper<PhysicsLayer, Enum>(_node) {}
            static constexpr char schemaName[] = "PhysicsLayer";
            static constexpr char const* enumToString[] = {
                "Default",
                "Ground",
                "Static",
                "Raycast",
                "Trigger",
                "Walkable",
                "Camera",
                "ClimbEdge",
                "Kinematic",
                "Ragdoll",
                "Projectile",
                "Hit",
                "MotionConstraint",
                "Heal",
                "Body",
                "Fluid",
                "Hitable",
                "None",
                "All",
                "PHYSICLAYER_COUNT",
            };
        };
        inline char const* toString(PhysicsLayerEnum value)
        {
            if(size_t(value) >= std::size(PhysicsLayer::enumToString))
                throw std::runtime_error("Wrong enum value");
            return PhysicsLayer::enumToString[size_t(value)];
        }
        inline char const* toInternal(PhysicsLayerEnum value) { return toString(value); }
        template<> inline PhysicsLayerEnum strToEnum<PhysicsLayerEnum>(char const* value)
        {
            return static_cast<PhysicsLayerEnum>(details::indexInEnum(value, PhysicsLayer::enumToString));
        }

        struct ProjectileShooterData : HelperObject // Object
        {
            ProjectileShooterData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ProjectileShooterData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef SubEntity() const;
            Ent::Gen::String _comment() const;
        };

        struct RegenerationState : EnumPropHelper<RegenerationState, RegenerationStateEnum> // Enum
        {
            using Enum = RegenerationStateEnum;
            using PropHelper<RegenerationState, Enum>::operator=;
            RegenerationState(Ent::Node* _node): EnumPropHelper<RegenerationState, Enum>(_node) {}
            static constexpr char schemaName[] = "RegenerationState";
            static constexpr char const* enumToString[] = {
                "None",
                "Sacred",
                "Cursed",
                "Lush",
                "Neutral",
                "Dead",
                "RegenerationState_COUNT",
            };
        };
        inline char const* toString(RegenerationStateEnum value)
        {
            if(size_t(value) >= std::size(RegenerationState::enumToString))
                throw std::runtime_error("Wrong enum value");
            return RegenerationState::enumToString[size_t(value)];
        }
        inline char const* toInternal(RegenerationStateEnum value) { return toString(value); }
        template<> inline RegenerationStateEnum strToEnum<RegenerationStateEnum>(char const* value)
        {
            return static_cast<RegenerationStateEnum>(details::indexInEnum(value, RegenerationState::enumToString));
        }

        struct ReviveSideData : HelperObject // Object
        {
            ReviveSideData(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./RuntimeComponents.json#/definitions/ReviveSideData";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::EntityRef EntityRef() const;
            Ent::Gen::String _comment() const;
        };

        struct Scene : HelperObject // Object
        {
            Scene(Ent::Node* _node): HelperObject(_node) {}
            static constexpr char schemaName[] = "./Scene-schema.json#/definitions/Scene";
            static Ent::Node load(Ent::EntityLib& _entlib, std::filesystem::path const& _sourceFile)
            {
                return _entlib.loadFileAsNode(_sourceFile, *_entlib.getSchema(schemaName));
            }
            static Ent::Node create(Ent::EntityLib& _entlib)
            {
                return _entlib.makeNode(schemaName);
            }
            Ent::Gen::ObjectSet<char const*, Ent::Gen::Entity> Objects() const;
            Ent::Gen::Int Version() const;
            Ent::Gen::String _comment() const;
        };

        struct SetOfObjectItem : HelperObject // Object
        {
            SetOfObjectItem(Ent::Node* _node): HelperObject(_node) {}
            
            Ent::Gen::String Name() const;
            Ent::Gen::String Value() const;
            Ent::Gen::String _comment() const;
        };

        struct Size : EnumPropHelper<Size, SizeEnum> // Enum
        {
            using Enum = SizeEnum;
            using PropHelper<Size, Enum>::operator=;
            Size(Ent::Node* _node): EnumPropHelper<Size, Enum>(_node) {}
            static constexpr char schemaName[] = "Size";
            static constexpr char const* enumToString[] = {
                "tiny",
                "small",
                "medium",
                "big",
                "enormous",
                "Size_COUNT",
            };
        };
        inline char const* toString(SizeEnum value)
        {
            if(size_t(value) >= std::size(Size::enumToString))
                throw std::runtime_error("Wrong enum value");
            return Size::enumToString[size_t(value)];
        }
        inline char const* toInternal(SizeEnum value) { return toString(value); }
        template<> inline SizeEnum strToEnum<SizeEnum>(char const* value)
        {
            return static_cast<SizeEnum>(details::indexInEnum(value, Size::enumToString));
        }


        // variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_
        inline char const* variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::String> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::string() const
        {
            return strcmp(node->getUnionType(), "string") != 0? std::optional<Ent::Gen::String>{}: std::optional<Ent::Gen::String>(node->getUnionData());
        }
        inline Ent::Gen::String variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setstring() const
        {
            return Ent::Gen::String(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Ent::Gen::Bool> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::bool_() const
        {
            return strcmp(node->getUnionType(), "bool_") != 0? std::optional<Ent::Gen::Bool>{}: std::optional<Ent::Gen::Bool>(node->getUnionData());
        }
        inline Ent::Gen::Bool variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setbool_() const
        {
            return Ent::Gen::Bool(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Ent::Gen::Int> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::s32() const
        {
            return strcmp(node->getUnionType(), "s32") != 0? std::optional<Ent::Gen::Int>{}: std::optional<Ent::Gen::Int>(node->getUnionData());
        }
        inline Ent::Gen::Int variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::sets32() const
        {
            return Ent::Gen::Int(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Ent::Gen::Float> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::float_() const
        {
            return strcmp(node->getUnionType(), "float_") != 0? std::optional<Ent::Gen::Float>{}: std::optional<Ent::Gen::Float>(node->getUnionData());
        }
        inline Ent::Gen::Float variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setfloat_() const
        {
            return Ent::Gen::Float(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Ent::Gen::EntityRef> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::EntityRef() const
        {
            return strcmp(node->getUnionType(), "EntityRef") != 0? std::optional<Ent::Gen::EntityRef>{}: std::optional<Ent::Gen::EntityRef>(node->getUnionData());
        }
        inline Ent::Gen::EntityRef variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setEntityRef() const
        {
            return Ent::Gen::EntityRef(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Ent::Gen::Vector2> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::Vector2() const
        {
            return strcmp(node->getUnionType(), "Vector2") != 0? std::optional<Ent::Gen::Vector2>{}: std::optional<Ent::Gen::Vector2>(node->getUnionData());
        }
        inline Ent::Gen::Vector2 variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setVector2() const
        {
            return Ent::Gen::Vector2(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Ent::Gen::Vector3> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::Vector3() const
        {
            return strcmp(node->getUnionType(), "Vector3") != 0? std::optional<Ent::Gen::Vector3>{}: std::optional<Ent::Gen::Vector3>(node->getUnionData());
        }
        inline Ent::Gen::Vector3 variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setVector3() const
        {
            return Ent::Gen::Vector3(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Ent::Gen::Position> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::Position() const
        {
            return strcmp(node->getUnionType(), "Position") != 0? std::optional<Ent::Gen::Position>{}: std::optional<Ent::Gen::Position>(node->getUnionData());
        }
        inline Ent::Gen::Position variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setPosition() const
        {
            return Ent::Gen::Position(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<PrimArray<Ent::Gen::String>> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::stringVec() const
        {
            return strcmp(node->getUnionType(), "stringVec") != 0? std::optional<PrimArray<Ent::Gen::String>>{}: std::optional<PrimArray<Ent::Gen::String>>(node->getUnionData());
        }
        inline PrimArray<Ent::Gen::String> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setstringVec() const
        {
            return PrimArray<Ent::Gen::String>(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<PrimArray<Ent::Gen::Bool>> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::boolVec() const
        {
            return strcmp(node->getUnionType(), "boolVec") != 0? std::optional<PrimArray<Ent::Gen::Bool>>{}: std::optional<PrimArray<Ent::Gen::Bool>>(node->getUnionData());
        }
        inline PrimArray<Ent::Gen::Bool> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setboolVec() const
        {
            return PrimArray<Ent::Gen::Bool>(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<PrimArray<Ent::Gen::Int>> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::s32Vec() const
        {
            return strcmp(node->getUnionType(), "s32Vec") != 0? std::optional<PrimArray<Ent::Gen::Int>>{}: std::optional<PrimArray<Ent::Gen::Int>>(node->getUnionData());
        }
        inline PrimArray<Ent::Gen::Int> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::sets32Vec() const
        {
            return PrimArray<Ent::Gen::Int>(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<PrimArray<Ent::Gen::Float>> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::floatVec() const
        {
            return strcmp(node->getUnionType(), "floatVec") != 0? std::optional<PrimArray<Ent::Gen::Float>>{}: std::optional<PrimArray<Ent::Gen::Float>>(node->getUnionData());
        }
        inline PrimArray<Ent::Gen::Float> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setfloatVec() const
        {
            return PrimArray<Ent::Gen::Float>(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<PrimArray<Ent::Gen::EntityRef>> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::EntityRefVec() const
        {
            return strcmp(node->getUnionType(), "EntityRefVec") != 0? std::optional<PrimArray<Ent::Gen::EntityRef>>{}: std::optional<PrimArray<Ent::Gen::EntityRef>>(node->getUnionData());
        }
        inline PrimArray<Ent::Gen::EntityRef> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setEntityRefVec() const
        {
            return PrimArray<Ent::Gen::EntityRef>(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Array<Ent::Gen::Vector2>> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::Vector2Vec() const
        {
            return strcmp(node->getUnionType(), "Vector2Vec") != 0? std::optional<Array<Ent::Gen::Vector2>>{}: std::optional<Array<Ent::Gen::Vector2>>(node->getUnionData());
        }
        inline Array<Ent::Gen::Vector2> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setVector2Vec() const
        {
            return Array<Ent::Gen::Vector2>(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Array<Ent::Gen::Vector3>> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::Vector3Vec() const
        {
            return strcmp(node->getUnionType(), "Vector3Vec") != 0? std::optional<Array<Ent::Gen::Vector3>>{}: std::optional<Array<Ent::Gen::Vector3>>(node->getUnionData());
        }
        inline Array<Ent::Gen::Vector3> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setVector3Vec() const
        {
            return Array<Ent::Gen::Vector3>(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        inline std::optional<Array<Ent::Gen::Position>> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::PositionVec() const
        {
            return strcmp(node->getUnionType(), "PositionVec") != 0? std::optional<Array<Ent::Gen::Position>>{}: std::optional<Array<Ent::Gen::Position>>(node->getUnionData());
        }
        inline Array<Ent::Gen::Position> variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_::setPositionVec() const
        {
            return Array<Ent::Gen::Position>(node->setUnionType("variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_"));
        }
        // TypedValue
        inline Ent::Gen::String TypedValue::Alias() const
        {
            return Ent::Gen::String(node->at("Alias"));
        }
        inline Ent::Gen::String TypedValue::Reference() const
        {
            return Ent::Gen::String(node->at("Reference"));
        }
        inline Ent::Gen::variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_ TypedValue::Value() const
        {
            return Ent::Gen::variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_(node->at("Value"));
        }
        inline Ent::Gen::String TypedValue::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_
        inline char const* variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::Int> variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::s32() const
        {
            return strcmp(node->getUnionType(), "s32") != 0? std::optional<Ent::Gen::Int>{}: std::optional<Ent::Gen::Int>(node->getUnionData());
        }
        inline Ent::Gen::Int variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::sets32() const
        {
            return Ent::Gen::Int(node->setUnionType("variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_"));
        }
        inline std::optional<Ent::Gen::Float> variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::float_() const
        {
            return strcmp(node->getUnionType(), "float_") != 0? std::optional<Ent::Gen::Float>{}: std::optional<Ent::Gen::Float>(node->getUnionData());
        }
        inline Ent::Gen::Float variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::setfloat_() const
        {
            return Ent::Gen::Float(node->setUnionType("variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_"));
        }
        inline std::optional<Ent::Gen::Bool> variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::bool_() const
        {
            return strcmp(node->getUnionType(), "bool_") != 0? std::optional<Ent::Gen::Bool>{}: std::optional<Ent::Gen::Bool>(node->getUnionData());
        }
        inline Ent::Gen::Bool variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::setbool_() const
        {
            return Ent::Gen::Bool(node->setUnionType("variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_"));
        }
        inline std::optional<Ent::Gen::String> variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::string() const
        {
            return strcmp(node->getUnionType(), "string") != 0? std::optional<Ent::Gen::String>{}: std::optional<Ent::Gen::String>(node->getUnionData());
        }
        inline Ent::Gen::String variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::setstring() const
        {
            return Ent::Gen::String(node->setUnionType("variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_"));
        }
        inline std::optional<Ent::Gen::Vector2> variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::Vector2() const
        {
            return strcmp(node->getUnionType(), "Vector2") != 0? std::optional<Ent::Gen::Vector2>{}: std::optional<Ent::Gen::Vector2>(node->getUnionData());
        }
        inline Ent::Gen::Vector2 variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::setVector2() const
        {
            return Ent::Gen::Vector2(node->setUnionType("variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_"));
        }
        inline std::optional<Ent::Gen::Vector3> variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::Vector3() const
        {
            return strcmp(node->getUnionType(), "Vector3") != 0? std::optional<Ent::Gen::Vector3>{}: std::optional<Ent::Gen::Vector3>(node->getUnionData());
        }
        inline Ent::Gen::Vector3 variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::setVector3() const
        {
            return Ent::Gen::Vector3(node->setUnionType("variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_"));
        }
        inline std::optional<Ent::Gen::Quat> variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::Quat() const
        {
            return strcmp(node->getUnionType(), "Quat") != 0? std::optional<Ent::Gen::Quat>{}: std::optional<Ent::Gen::Quat>(node->getUnionData());
        }
        inline Ent::Gen::Quat variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::setQuat() const
        {
            return Ent::Gen::Quat(node->setUnionType("variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_"));
        }
        inline std::optional<Ent::Gen::Position> variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::Position() const
        {
            return strcmp(node->getUnionType(), "Position") != 0? std::optional<Ent::Gen::Position>{}: std::optional<Ent::Gen::Position>(node->getUnionData());
        }
        inline Ent::Gen::Position variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_::setPosition() const
        {
            return Ent::Gen::Position(node->setUnionType("variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_"));
        }
        // variant_Pasta_Easing_Curve_string_
        inline char const* variant_Pasta_Easing_Curve_string_::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::Pasta_Easing_Curve> variant_Pasta_Easing_Curve_string_::Pasta_Easing_Curve() const
        {
            return strcmp(node->getUnionType(), "Pasta_Easing_Curve") != 0? std::optional<Ent::Gen::Pasta_Easing_Curve>{}: std::optional<Ent::Gen::Pasta_Easing_Curve>(node->getUnionData());
        }
        inline Ent::Gen::Pasta_Easing_Curve variant_Pasta_Easing_Curve_string_::setPasta_Easing_Curve() const
        {
            return Ent::Gen::Pasta_Easing_Curve(node->setUnionType("variant_Pasta_Easing_Curve_string_"));
        }
        inline std::optional<Ent::Gen::String> variant_Pasta_Easing_Curve_string_::string() const
        {
            return strcmp(node->getUnionType(), "string") != 0? std::optional<Ent::Gen::String>{}: std::optional<Ent::Gen::String>(node->getUnionData());
        }
        inline Ent::Gen::String variant_Pasta_Easing_Curve_string_::setstring() const
        {
            return Ent::Gen::String(node->setUnionType("variant_Pasta_Easing_Curve_string_"));
        }
        // sPhysicsShapeSphere
        inline Ent::Gen::String sPhysicsShapeSphere::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float sPhysicsShapeSphere::radius() const
        {
            return Ent::Gen::Float(node->at("radius"));
        }
        // sPhysicsShapeMesh
        inline Ent::Gen::String sPhysicsShapeMesh::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::String sPhysicsShapeMesh::path() const
        {
            return Ent::Gen::String(node->at("path"));
        }
        // sPhysicsShapeCylinder
        inline Ent::Gen::String sPhysicsShapeCylinder::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float sPhysicsShapeCylinder::length() const
        {
            return Ent::Gen::Float(node->at("length"));
        }
        inline Ent::Gen::Float sPhysicsShapeCylinder::radius() const
        {
            return Ent::Gen::Float(node->at("radius"));
        }
        // sPhysicsShapeCapsule
        inline Ent::Gen::String sPhysicsShapeCapsule::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float sPhysicsShapeCapsule::length() const
        {
            return Ent::Gen::Float(node->at("length"));
        }
        inline Ent::Gen::Float sPhysicsShapeCapsule::radius() const
        {
            return Ent::Gen::Float(node->at("radius"));
        }
        // sJointFixedDesc
        // sJointBallDesc
        // sGameEffectTemplate
        inline Ent::Gen::Int sGameEffectTemplate::BoneID() const
        {
            return Ent::Gen::Int(node->at("BoneID"));
        }
        inline Ent::Gen::String sGameEffectTemplate::BoneName() const
        {
            return Ent::Gen::String(node->at("BoneName"));
        }
        inline Ent::Gen::String sGameEffectTemplate::EffectName() const
        {
            return Ent::Gen::String(node->at("EffectName"));
        }
        inline Ent::Gen::String sGameEffectTemplate::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // sBoneInfluenceDataTemplate
        inline Ent::Gen::String sBoneInfluenceDataTemplate::BoneName() const
        {
            return Ent::Gen::String(node->at("BoneName"));
        }
        inline Ent::Gen::Float sBoneInfluenceDataTemplate::Influence() const
        {
            return Ent::Gen::Float(node->at("Influence"));
        }
        inline Ent::Gen::String sBoneInfluenceDataTemplate::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // sNodeBoneInfluenceDataTemplate
        inline Array<Ent::Gen::sBoneInfluenceDataTemplate> sNodeBoneInfluenceDataTemplate::Data() const
        {
            return Array<Ent::Gen::sBoneInfluenceDataTemplate>(node->at("Data"));
        }
        inline Ent::Gen::String sNodeBoneInfluenceDataTemplate::NodeName() const
        {
            return Ent::Gen::String(node->at("NodeName"));
        }
        inline Ent::Gen::String sNodeBoneInfluenceDataTemplate::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // eventStringHash
        inline Ent::Gen::String eventStringHash::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool eventStringHash::engaged() const
        {
            return Ent::Gen::Bool(node->at("engaged"));
        }
        inline Ent::Gen::String eventStringHash::val() const
        {
            return Ent::Gen::String(node->at("val"));
        }
        // sPhysicsShapeBox
        inline Ent::Gen::String sPhysicsShapeBox::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Vector3 sPhysicsShapeBox::size() const
        {
            return Ent::Gen::Vector3(node->at("size"));
        }
        // sEnvStamp
        inline Ent::Gen::Bool sEnvStamp::AffectCoverage() const
        {
            return Ent::Gen::Bool(node->at("AffectCoverage"));
        }
        inline Ent::Gen::Bool sEnvStamp::AffectFogColor() const
        {
            return Ent::Gen::Bool(node->at("AffectFogColor"));
        }
        inline Ent::Gen::Bool sEnvStamp::AffectFogDensity() const
        {
            return Ent::Gen::Bool(node->at("AffectFogDensity"));
        }
        inline Ent::Gen::Bool sEnvStamp::AffectFogFalloff() const
        {
            return Ent::Gen::Bool(node->at("AffectFogFalloff"));
        }
        inline Ent::Gen::Bool sEnvStamp::AffectFogHeight() const
        {
            return Ent::Gen::Bool(node->at("AffectFogHeight"));
        }
        inline Ent::Gen::Bool sEnvStamp::AffectPull() const
        {
            return Ent::Gen::Bool(node->at("AffectPull"));
        }
        inline Ent::Gen::Bool sEnvStamp::AffectType() const
        {
            return Ent::Gen::Bool(node->at("AffectType"));
        }
        inline Ent::Gen::Bool sEnvStamp::AffectWetness() const
        {
            return Ent::Gen::Bool(node->at("AffectWetness"));
        }
        inline Ent::Gen::Int sEnvStamp::AtlasID() const
        {
            return Ent::Gen::Int(node->at("AtlasID"));
        }
        inline Ent::Gen::Vector3 sEnvStamp::FogColor() const
        {
            return Ent::Gen::Vector3(node->at("FogColor"));
        }
        inline Ent::Gen::Bool sEnvStamp::IsCloud() const
        {
            return Ent::Gen::Bool(node->at("IsCloud"));
        }
        inline Ent::Gen::Vector3 sEnvStamp::PositionOffset() const
        {
            return Ent::Gen::Vector3(node->at("PositionOffset"));
        }
        inline Ent::Gen::Float sEnvStamp::Rotation() const
        {
            return Ent::Gen::Float(node->at("Rotation"));
        }
        inline Ent::Gen::Float sEnvStamp::Size() const
        {
            return Ent::Gen::Float(node->at("Size"));
        }
        inline Ent::Gen::Float sEnvStamp::Strength() const
        {
            return Ent::Gen::Float(node->at("Strength"));
        }
        inline Ent::Gen::String sEnvStamp::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // sJointUniversalDesc
        inline Ent::Gen::String sJointUniversalDesc::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Vector2 sJointUniversalDesc::angleSwing1() const
        {
            return Ent::Gen::Vector2(node->at("angleSwing1"));
        }
        inline Ent::Gen::Vector2 sJointUniversalDesc::angleSwing2() const
        {
            return Ent::Gen::Vector2(node->at("angleSwing2"));
        }
        // sJointSwingTwistDesc
        inline Ent::Gen::String sJointSwingTwistDesc::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Vector2 sJointSwingTwistDesc::swingAngle() const
        {
            return Ent::Gen::Vector2(node->at("swingAngle"));
        }
        inline Ent::Gen::Vector2 sJointSwingTwistDesc::twistAngle() const
        {
            return Ent::Gen::Vector2(node->at("twistAngle"));
        }
        // sJointSliderDesc
        inline Ent::Gen::String sJointSliderDesc::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Vector3 sJointSliderDesc::direction() const
        {
            return Ent::Gen::Vector3(node->at("direction"));
        }
        inline Ent::Gen::Vector2 sJointSliderDesc::distance() const
        {
            return Ent::Gen::Vector2(node->at("distance"));
        }
        // sJointHingeDesc
        inline Ent::Gen::String sJointHingeDesc::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Vector2 sJointHingeDesc::angle() const
        {
            return Ent::Gen::Vector2(node->at("angle"));
        }
        inline Ent::Gen::Vector3 sJointHingeDesc::axis() const
        {
            return Ent::Gen::Vector3(node->at("axis"));
        }
        // VomitData
        inline Ent::Gen::Vector2 VomitData::AngleRangeHysteresis() const
        {
            return Ent::Gen::Vector2(node->at("AngleRangeHysteresis"));
        }
        inline Ent::Gen::Vector2 VomitData::AngleRangeMax() const
        {
            return Ent::Gen::Vector2(node->at("AngleRangeMax"));
        }
        inline Ent::Gen::Bool VomitData::CanVomit() const
        {
            return Ent::Gen::Bool(node->at("CanVomit"));
        }
        inline Ent::Gen::String VomitData::ProjectileName() const
        {
            return Ent::Gen::String(node->at("ProjectileName"));
        }
        inline Ent::Gen::Float VomitData::VomitCost() const
        {
            return Ent::Gen::Float(node->at("VomitCost"));
        }
        inline Ent::Gen::Float VomitData::VomitMinTimer() const
        {
            return Ent::Gen::Float(node->at("VomitMinTimer"));
        }
        inline Ent::Gen::Float VomitData::VomitRate() const
        {
            return Ent::Gen::Float(node->at("VomitRate"));
        }
        inline Ent::Gen::String VomitData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // UnionObjectArrayItem
        inline Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ UnionObjectArrayItem::Union() const
        {
            return Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(node->at("Union"));
        }
        inline Ent::Gen::String UnionObjectArrayItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TransitionNeighborData
        inline PrimArray<Ent::Gen::Int> TransitionNeighborData::Backward() const
        {
            return PrimArray<Ent::Gen::Int>(node->at("Backward"));
        }
        inline PrimArray<Ent::Gen::Int> TransitionNeighborData::Forward() const
        {
            return PrimArray<Ent::Gen::Int>(node->at("Forward"));
        }
        inline Ent::Gen::String TransitionNeighborData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TestPropertyDefaultValues
        inline Ent::Gen::Int TestPropertyDefaultValues::A() const
        {
            return Ent::Gen::Int(node->at("A"));
        }
        inline Ent::Gen::Int TestPropertyDefaultValues::B() const
        {
            return Ent::Gen::Int(node->at("B"));
        }
        inline Ent::Gen::String TestPropertyDefaultValues::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TestPropertyDefaultValues2
        inline Ent::Gen::String TestPropertyDefaultValues2::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::TestPropertyDefaultValues TestPropertyDefaultValues2::propertyWithDefault2() const
        {
            return Ent::Gen::TestPropertyDefaultValues(node->at("propertyWithDefault2"));
        }
        inline Ent::Gen::TestPropertyDefaultValues TestPropertyDefaultValues2::propertyWithDefault3() const
        {
            return Ent::Gen::TestPropertyDefaultValues(node->at("propertyWithDefault3"));
        }
        // Terrain_TerrainMeta
        inline Ent::Gen::String Terrain_TerrainMeta::DataPath() const
        {
            return Ent::Gen::String(node->at("DataPath"));
        }
        inline Ent::Gen::Float Terrain_TerrainMeta::HeightScaleMeters() const
        {
            return Ent::Gen::Float(node->at("HeightScaleMeters"));
        }
        inline Ent::Gen::String Terrain_TerrainMeta::Material() const
        {
            return Ent::Gen::String(node->at("Material"));
        }
        inline Ent::Gen::Float Terrain_TerrainMeta::RegionWidthMeters() const
        {
            return Ent::Gen::Float(node->at("RegionWidthMeters"));
        }
        inline Ent::Gen::Float Terrain_TerrainMeta::SkirtScale() const
        {
            return Ent::Gen::Float(node->at("SkirtScale"));
        }
        inline Ent::Gen::Float Terrain_TerrainMeta::TexelsPerMeter() const
        {
            return Ent::Gen::Float(node->at("TexelsPerMeter"));
        }
        inline Ent::Gen::String Terrain_TerrainMeta::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TagsList
        inline Ent::Gen::Map<char const*, Ent::Gen::PrimitiveSet<char const*>> TagsList::Tags() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::PrimitiveSet<char const*>>(node->at("Tags"));
        }
        inline Ent::Gen::String TagsList::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TaggedEntityRef
        inline Ent::Gen::EntityRef TaggedEntityRef::EntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("EntityRef"));
        }
        inline PrimArray<Ent::Gen::InventoryTags> TaggedEntityRef::Tags() const
        {
            return PrimArray<Ent::Gen::InventoryTags>(node->at("Tags"));
        }
        inline Ent::Gen::String TaggedEntityRef::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // StunData
        inline Ent::Gen::String StunData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Int StunData::damageHitBig() const
        {
            return Ent::Gen::Int(node->at("damageHitBig"));
        }
        inline Ent::Gen::Int StunData::damageHitBite() const
        {
            return Ent::Gen::Int(node->at("damageHitBite"));
        }
        inline Ent::Gen::Int StunData::damageHitEject() const
        {
            return Ent::Gen::Int(node->at("damageHitEject"));
        }
        inline Ent::Gen::Int StunData::damageHitEjectFar() const
        {
            return Ent::Gen::Int(node->at("damageHitEjectFar"));
        }
        inline Ent::Gen::Int StunData::damageHitLight() const
        {
            return Ent::Gen::Int(node->at("damageHitLight"));
        }
        inline Ent::Gen::Int StunData::damageHitMedium() const
        {
            return Ent::Gen::Int(node->at("damageHitMedium"));
        }
        inline Ent::Gen::Int StunData::malus() const
        {
            return Ent::Gen::Int(node->at("malus"));
        }
        inline Ent::Gen::Float StunData::orientHitBig() const
        {
            return Ent::Gen::Float(node->at("orientHitBig"));
        }
        inline Ent::Gen::Float StunData::orientHitEject() const
        {
            return Ent::Gen::Float(node->at("orientHitEject"));
        }
        inline Ent::Gen::Float StunData::orientHitEjectFar() const
        {
            return Ent::Gen::Float(node->at("orientHitEjectFar"));
        }
        inline Ent::Gen::Float StunData::orientHitLight() const
        {
            return Ent::Gen::Float(node->at("orientHitLight"));
        }
        inline Ent::Gen::Float StunData::orientHitMedium() const
        {
            return Ent::Gen::Float(node->at("orientHitMedium"));
        }
        inline Ent::Gen::Float StunData::recoverTime() const
        {
            return Ent::Gen::Float(node->at("recoverTime"));
        }
        inline Ent::Gen::Int StunData::resistance() const
        {
            return Ent::Gen::Int(node->at("resistance"));
        }
        inline Ent::Gen::Float StunData::stunTime() const
        {
            return Ent::Gen::Float(node->at("stunTime"));
        }
        // StickToGround
        inline Ent::Gen::String StickToGround::BoneNameEnd() const
        {
            return Ent::Gen::String(node->at("BoneNameEnd"));
        }
        inline Ent::Gen::String StickToGround::BoneNameStart() const
        {
            return Ent::Gen::String(node->at("BoneNameStart"));
        }
        inline Ent::Gen::String StickToGround::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // StateGauge
        inline Ent::Gen::String StateGauge::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float StateGauge::m_amount() const
        {
            return Ent::Gen::Float(node->at("m_amount"));
        }
        inline Ent::Gen::Float StateGauge::m_maxAmount() const
        {
            return Ent::Gen::Float(node->at("m_maxAmount"));
        }
        inline Ent::Gen::Float StateGauge::m_pendingDiff() const
        {
            return Ent::Gen::Float(node->at("m_pendingDiff"));
        }
        // StunGauge
        inline Ent::Gen::StateGauge StunGauge::Super() const
        {
            return Ent::Gen::StateGauge(node->at("Super"));
        }
        inline Ent::Gen::String StunGauge::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SpeedFastMinDuration
        inline Ent::Gen::String SpeedFastMinDuration::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool SpeedFastMinDuration::engaged() const
        {
            return Ent::Gen::Bool(node->at("engaged"));
        }
        inline Ent::Gen::Float SpeedFastMinDuration::val() const
        {
            return Ent::Gen::Float(node->at("val"));
        }
        // SpawningParameter
        inline Ent::Gen::String SpawningParameter::EntityName() const
        {
            return Ent::Gen::String(node->at("EntityName"));
        }
        inline Ent::Gen::Float SpawningParameter::MinimumDepth() const
        {
            return Ent::Gen::Float(node->at("MinimumDepth"));
        }
        inline Ent::Gen::Float SpawningParameter::PeriodRandomness() const
        {
            return Ent::Gen::Float(node->at("PeriodRandomness"));
        }
        inline Ent::Gen::Float SpawningParameter::SpawningPeriod() const
        {
            return Ent::Gen::Float(node->at("SpawningPeriod"));
        }
        inline Ent::Gen::String SpawningParameter::State() const
        {
            return Ent::Gen::String(node->at("State"));
        }
        inline Ent::Gen::String SpawningParameter::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SoundEventMapping
        inline Ent::Gen::Map<char const*, Ent::Gen::String> SoundEventMapping::Explicit() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::String>(node->at("Explicit"));
        }
        inline Ent::Gen::PrimitiveSet<char const*> SoundEventMapping::Ignored() const
        {
            return Ent::Gen::PrimitiveSet<char const*>(node->at("Ignored"));
        }
        inline Ent::Gen::Map<char const*, Ent::Gen::String> SoundEventMapping::Prefixed() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::String>(node->at("Prefixed"));
        }
        inline Ent::Gen::String SoundEventMapping::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ShootSequenceData
        inline Ent::Gen::Float ShootSequenceData::Param() const
        {
            return Ent::Gen::Float(node->at("Param"));
        }
        inline Ent::Gen::String ShootSequenceData::Type_() const
        {
            return Ent::Gen::String(node->at("Type_"));
        }
        inline Ent::Gen::String ShootSequenceData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ShootData
        inline Ent::Gen::String ShootData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::String ShootData::ammoName() const
        {
            return Ent::Gen::String(node->at("ammoName"));
        }
        inline Ent::Gen::Float ShootData::anticipationImprecision() const
        {
            return Ent::Gen::Float(node->at("anticipationImprecision"));
        }
        inline Ent::Gen::Bool ShootData::canShoot() const
        {
            return Ent::Gen::Bool(node->at("canShoot"));
        }
        inline Ent::Gen::Int ShootData::chargeTierCount() const
        {
            return Ent::Gen::Int(node->at("chargeTierCount"));
        }
        inline Ent::Gen::Float ShootData::gravity() const
        {
            return Ent::Gen::Float(node->at("gravity"));
        }
        inline Ent::Gen::Float ShootData::lifeCost() const
        {
            return Ent::Gen::Float(node->at("lifeCost"));
        }
        inline Ent::Gen::Float ShootData::lifeCostCharged() const
        {
            return Ent::Gen::Float(node->at("lifeCostCharged"));
        }
        inline Ent::Gen::Float ShootData::maxChargeDuration() const
        {
            return Ent::Gen::Float(node->at("maxChargeDuration"));
        }
        inline Ent::Gen::Float ShootData::maxShootDistance() const
        {
            return Ent::Gen::Float(node->at("maxShootDistance"));
        }
        inline Ent::Gen::Float ShootData::minDelayBetweenShots() const
        {
            return Ent::Gen::Float(node->at("minDelayBetweenShots"));
        }
        inline Ent::Gen::Bool ShootData::randomAngleShoot() const
        {
            return Ent::Gen::Bool(node->at("randomAngleShoot"));
        }
        inline Ent::Gen::Float ShootData::shootMaxAngle() const
        {
            return Ent::Gen::Float(node->at("shootMaxAngle"));
        }
        inline Ent::Gen::Float ShootData::shootSpeed() const
        {
            return Ent::Gen::Float(node->at("shootSpeed"));
        }
        inline Ent::Gen::Float ShootData::zoneImprecision() const
        {
            return Ent::Gen::Float(node->at("zoneImprecision"));
        }
        // SeedPatchData
        inline Ent::Gen::Float SeedPatchData::NoiseBlur() const
        {
            return Ent::Gen::Float(node->at("NoiseBlur"));
        }
        inline Ent::Gen::Float SeedPatchData::NoiseContrast() const
        {
            return Ent::Gen::Float(node->at("NoiseContrast"));
        }
        inline Ent::Gen::Bool SeedPatchData::NoiseInvert() const
        {
            return Ent::Gen::Bool(node->at("NoiseInvert"));
        }
        inline Ent::Gen::String SeedPatchData::NoiseName() const
        {
            return Ent::Gen::String(node->at("NoiseName"));
        }
        inline Ent::Gen::Float SeedPatchData::NoiseOffsetX() const
        {
            return Ent::Gen::Float(node->at("NoiseOffsetX"));
        }
        inline Ent::Gen::Float SeedPatchData::NoiseOffsetY() const
        {
            return Ent::Gen::Float(node->at("NoiseOffsetY"));
        }
        inline Ent::Gen::Float SeedPatchData::NoiseOpacity() const
        {
            return Ent::Gen::Float(node->at("NoiseOpacity"));
        }
        inline Ent::Gen::Float SeedPatchData::NoisePosition() const
        {
            return Ent::Gen::Float(node->at("NoisePosition"));
        }
        inline Ent::Gen::Float SeedPatchData::NoiseSizeX() const
        {
            return Ent::Gen::Float(node->at("NoiseSizeX"));
        }
        inline Ent::Gen::Float SeedPatchData::NoiseSizeY() const
        {
            return Ent::Gen::Float(node->at("NoiseSizeY"));
        }
        inline Ent::Gen::String SeedPatchData::SeedName() const
        {
            return Ent::Gen::String(node->at("SeedName"));
        }
        inline Ent::Gen::String SeedPatchData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SeedPatchDataList
        inline Array<Ent::Gen::SeedPatchData> SeedPatchDataList::Data() const
        {
            return Array<Ent::Gen::SeedPatchData>(node->at("Data"));
        }
        inline Ent::Gen::String SeedPatchDataList::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ScriptPathAndDataSet
        inline Ent::Gen::Bool ScriptPathAndDataSet::AutoLaunch() const
        {
            return Ent::Gen::Bool(node->at("AutoLaunch"));
        }
        inline Ent::Gen::Map<char const*, Ent::Gen::TypedValue> ScriptPathAndDataSet::DataMap() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::TypedValue>(node->at("DataMap"));
        }
        inline Ent::Gen::String ScriptPathAndDataSet::NickName() const
        {
            return Ent::Gen::String(node->at("NickName"));
        }
        inline Ent::Gen::String ScriptPathAndDataSet::Path() const
        {
            return Ent::Gen::String(node->at("Path"));
        }
        inline Array<Ent::Gen::ScriptPathAndDataSet> ScriptPathAndDataSet::SpawnDataSets() const
        {
            return Array<Ent::Gen::ScriptPathAndDataSet>(node->at("SpawnDataSets"));
        }
        inline Ent::Gen::String ScriptPathAndDataSet::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ScaleConverter
        inline Ent::Gen::String ScaleConverter::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::variant_Pasta_Easing_Curve_string_ ScaleConverter::easing() const
        {
            return Ent::Gen::variant_Pasta_Easing_Curve_string_(node->at("easing"));
        }
        inline Ent::Gen::Vector2 ScaleConverter::in_() const
        {
            return Ent::Gen::Vector2(node->at("in_"));
        }
        inline Ent::Gen::String ScaleConverter::inText() const
        {
            return Ent::Gen::String(node->at("inText"));
        }
        inline Ent::Gen::Vector2 ScaleConverter::out() const
        {
            return Ent::Gen::Vector2(node->at("out"));
        }
        inline Ent::Gen::String ScaleConverter::outText() const
        {
            return Ent::Gen::String(node->at("outText"));
        }
        // RevivedData
        inline Ent::Gen::Bool RevivedData::CanBeFreed() const
        {
            return Ent::Gen::Bool(node->at("CanBeFreed"));
        }
        inline Ent::Gen::Float RevivedData::DecreaseOverTimeSpeed() const
        {
            return Ent::Gen::Float(node->at("DecreaseOverTimeSpeed"));
        }
        inline Ent::Gen::Float RevivedData::LifeMinHysteresis() const
        {
            return Ent::Gen::Float(node->at("LifeMinHysteresis"));
        }
        inline Ent::Gen::Float RevivedData::LifeMinReviveSideNeutral() const
        {
            return Ent::Gen::Float(node->at("LifeMinReviveSideNeutral"));
        }
        inline Ent::Gen::Float RevivedData::NonCreatureConvertRatio() const
        {
            return Ent::Gen::Float(node->at("NonCreatureConvertRatio"));
        }
        inline Ent::Gen::Bool RevivedData::RequestReviveLocked() const
        {
            return Ent::Gen::Bool(node->at("RequestReviveLocked"));
        }
        inline Ent::Gen::Float RevivedData::ReviveEnergyMax() const
        {
            return Ent::Gen::Float(node->at("ReviveEnergyMax"));
        }
        inline Ent::Gen::Float RevivedData::ReviveSinAmplitude() const
        {
            return Ent::Gen::Float(node->at("ReviveSinAmplitude"));
        }
        inline Ent::Gen::ReviveSide RevivedData::StartSide() const
        {
            return Ent::Gen::ReviveSide(node->at("StartSide"));
        }
        inline PrimArray<Ent::Gen::Float> RevivedData::StateThresholds() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("StateThresholds"));
        }
        inline Ent::Gen::Float RevivedData::TimeBeforeFree() const
        {
            return Ent::Gen::Float(node->at("TimeBeforeFree"));
        }
        inline Ent::Gen::VomitData RevivedData::VomitData() const
        {
            return Ent::Gen::VomitData(node->at("VomitData"));
        }
        inline Ent::Gen::String RevivedData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ReviveSideEvent
        inline Ent::Gen::Float ReviveSideEvent::ElapsedTime() const
        {
            return Ent::Gen::Float(node->at("ElapsedTime"));
        }
        inline Ent::Gen::ReviveSide ReviveSideEvent::ReviveSide() const
        {
            return Ent::Gen::ReviveSide(node->at("ReviveSide"));
        }
        inline Ent::Gen::String ReviveSideEvent::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ResponsiblePointer_CineEvent_
        inline char const* ResponsiblePointer_CineEvent_::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::CineEventTestCurrentGameState> ResponsiblePointer_CineEvent_::CineEventTestCurrentGameState() const
        {
            return strcmp(node->getUnionType(), "CineEventTestCurrentGameState") != 0? std::optional<Ent::Gen::CineEventTestCurrentGameState>{}: std::optional<Ent::Gen::CineEventTestCurrentGameState>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTestCurrentGameState ResponsiblePointer_CineEvent_::setCineEventTestCurrentGameState() const
        {
            return Ent::Gen::CineEventTestCurrentGameState(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        inline std::optional<Ent::Gen::CineEventTestEndCurrentSequence> ResponsiblePointer_CineEvent_::CineEventTestEndCurrentSequence() const
        {
            return strcmp(node->getUnionType(), "CineEventTestEndCurrentSequence") != 0? std::optional<Ent::Gen::CineEventTestEndCurrentSequence>{}: std::optional<Ent::Gen::CineEventTestEndCurrentSequence>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTestEndCurrentSequence ResponsiblePointer_CineEvent_::setCineEventTestEndCurrentSequence() const
        {
            return Ent::Gen::CineEventTestEndCurrentSequence(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        inline std::optional<Ent::Gen::CineEventTestInput> ResponsiblePointer_CineEvent_::CineEventTestInput() const
        {
            return strcmp(node->getUnionType(), "CineEventTestInput") != 0? std::optional<Ent::Gen::CineEventTestInput>{}: std::optional<Ent::Gen::CineEventTestInput>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTestInput ResponsiblePointer_CineEvent_::setCineEventTestInput() const
        {
            return Ent::Gen::CineEventTestInput(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        inline std::optional<Ent::Gen::CineEventTestIsCanceled> ResponsiblePointer_CineEvent_::CineEventTestIsCanceled() const
        {
            return strcmp(node->getUnionType(), "CineEventTestIsCanceled") != 0? std::optional<Ent::Gen::CineEventTestIsCanceled>{}: std::optional<Ent::Gen::CineEventTestIsCanceled>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTestIsCanceled ResponsiblePointer_CineEvent_::setCineEventTestIsCanceled() const
        {
            return Ent::Gen::CineEventTestIsCanceled(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        inline std::optional<Ent::Gen::CineEventTestWait> ResponsiblePointer_CineEvent_::CineEventTestWait() const
        {
            return strcmp(node->getUnionType(), "CineEventTestWait") != 0? std::optional<Ent::Gen::CineEventTestWait>{}: std::optional<Ent::Gen::CineEventTestWait>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTestWait ResponsiblePointer_CineEvent_::setCineEventTestWait() const
        {
            return Ent::Gen::CineEventTestWait(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        inline std::optional<Ent::Gen::CineEventTriggerEventHandlerPost> ResponsiblePointer_CineEvent_::CineEventTriggerEventHandlerPost() const
        {
            return strcmp(node->getUnionType(), "CineEventTriggerEventHandlerPost") != 0? std::optional<Ent::Gen::CineEventTriggerEventHandlerPost>{}: std::optional<Ent::Gen::CineEventTriggerEventHandlerPost>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTriggerEventHandlerPost ResponsiblePointer_CineEvent_::setCineEventTriggerEventHandlerPost() const
        {
            return Ent::Gen::CineEventTriggerEventHandlerPost(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        inline std::optional<Ent::Gen::CineEventTriggerGameStateChange> ResponsiblePointer_CineEvent_::CineEventTriggerGameStateChange() const
        {
            return strcmp(node->getUnionType(), "CineEventTriggerGameStateChange") != 0? std::optional<Ent::Gen::CineEventTriggerGameStateChange>{}: std::optional<Ent::Gen::CineEventTriggerGameStateChange>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTriggerGameStateChange ResponsiblePointer_CineEvent_::setCineEventTriggerGameStateChange() const
        {
            return Ent::Gen::CineEventTriggerGameStateChange(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        inline std::optional<Ent::Gen::CineEventTriggerPlaySequence> ResponsiblePointer_CineEvent_::CineEventTriggerPlaySequence() const
        {
            return strcmp(node->getUnionType(), "CineEventTriggerPlaySequence") != 0? std::optional<Ent::Gen::CineEventTriggerPlaySequence>{}: std::optional<Ent::Gen::CineEventTriggerPlaySequence>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTriggerPlaySequence ResponsiblePointer_CineEvent_::setCineEventTriggerPlaySequence() const
        {
            return Ent::Gen::CineEventTriggerPlaySequence(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        inline std::optional<Ent::Gen::CineEventTriggerPlaySound> ResponsiblePointer_CineEvent_::CineEventTriggerPlaySound() const
        {
            return strcmp(node->getUnionType(), "CineEventTriggerPlaySound") != 0? std::optional<Ent::Gen::CineEventTriggerPlaySound>{}: std::optional<Ent::Gen::CineEventTriggerPlaySound>(node->getUnionData());
        }
        inline Ent::Gen::CineEventTriggerPlaySound ResponsiblePointer_CineEvent_::setCineEventTriggerPlaySound() const
        {
            return Ent::Gen::CineEventTriggerPlaySound(node->setUnionType("ResponsiblePointer_CineEvent_"));
        }
        // ResponsiblePointer_ActorState_
        inline char const* ResponsiblePointer_ActorState_::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::ActorStateAlive> ResponsiblePointer_ActorState_::ActorStateAlive() const
        {
            return strcmp(node->getUnionType(), "ActorStateAlive") != 0? std::optional<Ent::Gen::ActorStateAlive>{}: std::optional<Ent::Gen::ActorStateAlive>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateAlive ResponsiblePointer_ActorState_::setActorStateAlive() const
        {
            return Ent::Gen::ActorStateAlive(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateBeingImmersed> ResponsiblePointer_ActorState_::ActorStateBeingImmersed() const
        {
            return strcmp(node->getUnionType(), "ActorStateBeingImmersed") != 0? std::optional<Ent::Gen::ActorStateBeingImmersed>{}: std::optional<Ent::Gen::ActorStateBeingImmersed>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateBeingImmersed ResponsiblePointer_ActorState_::setActorStateBeingImmersed() const
        {
            return Ent::Gen::ActorStateBeingImmersed(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateBeingInAir> ResponsiblePointer_ActorState_::ActorStateBeingInAir() const
        {
            return strcmp(node->getUnionType(), "ActorStateBeingInAir") != 0? std::optional<Ent::Gen::ActorStateBeingInAir>{}: std::optional<Ent::Gen::ActorStateBeingInAir>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateBeingInAir ResponsiblePointer_ActorState_::setActorStateBeingInAir() const
        {
            return Ent::Gen::ActorStateBeingInAir(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateBeingOnGround> ResponsiblePointer_ActorState_::ActorStateBeingOnGround() const
        {
            return strcmp(node->getUnionType(), "ActorStateBeingOnGround") != 0? std::optional<Ent::Gen::ActorStateBeingOnGround>{}: std::optional<Ent::Gen::ActorStateBeingOnGround>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateBeingOnGround ResponsiblePointer_ActorState_::setActorStateBeingOnGround() const
        {
            return Ent::Gen::ActorStateBeingOnGround(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateBuried> ResponsiblePointer_ActorState_::ActorStateBuried() const
        {
            return strcmp(node->getUnionType(), "ActorStateBuried") != 0? std::optional<Ent::Gen::ActorStateBuried>{}: std::optional<Ent::Gen::ActorStateBuried>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateBuried ResponsiblePointer_ActorState_::setActorStateBuried() const
        {
            return Ent::Gen::ActorStateBuried(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateDead> ResponsiblePointer_ActorState_::ActorStateDead() const
        {
            return strcmp(node->getUnionType(), "ActorStateDead") != 0? std::optional<Ent::Gen::ActorStateDead>{}: std::optional<Ent::Gen::ActorStateDead>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateDead ResponsiblePointer_ActorState_::setActorStateDead() const
        {
            return Ent::Gen::ActorStateDead(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateHasNoBody> ResponsiblePointer_ActorState_::ActorStateHasNoBody() const
        {
            return strcmp(node->getUnionType(), "ActorStateHasNoBody") != 0? std::optional<Ent::Gen::ActorStateHasNoBody>{}: std::optional<Ent::Gen::ActorStateHasNoBody>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateHasNoBody ResponsiblePointer_ActorState_::setActorStateHasNoBody() const
        {
            return Ent::Gen::ActorStateHasNoBody(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateHoldingItem> ResponsiblePointer_ActorState_::ActorStateHoldingItem() const
        {
            return strcmp(node->getUnionType(), "ActorStateHoldingItem") != 0? std::optional<Ent::Gen::ActorStateHoldingItem>{}: std::optional<Ent::Gen::ActorStateHoldingItem>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateHoldingItem ResponsiblePointer_ActorState_::setActorStateHoldingItem() const
        {
            return Ent::Gen::ActorStateHoldingItem(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateInvincible> ResponsiblePointer_ActorState_::ActorStateInvincible() const
        {
            return strcmp(node->getUnionType(), "ActorStateInvincible") != 0? std::optional<Ent::Gen::ActorStateInvincible>{}: std::optional<Ent::Gen::ActorStateInvincible>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateInvincible ResponsiblePointer_ActorState_::setActorStateInvincible() const
        {
            return Ent::Gen::ActorStateInvincible(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateRegenerationFull> ResponsiblePointer_ActorState_::ActorStateRegenerationFull() const
        {
            return strcmp(node->getUnionType(), "ActorStateRegenerationFull") != 0? std::optional<Ent::Gen::ActorStateRegenerationFull>{}: std::optional<Ent::Gen::ActorStateRegenerationFull>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateRegenerationFull ResponsiblePointer_ActorState_::setActorStateRegenerationFull() const
        {
            return Ent::Gen::ActorStateRegenerationFull(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateRegenerationLow> ResponsiblePointer_ActorState_::ActorStateRegenerationLow() const
        {
            return strcmp(node->getUnionType(), "ActorStateRegenerationLow") != 0? std::optional<Ent::Gen::ActorStateRegenerationLow>{}: std::optional<Ent::Gen::ActorStateRegenerationLow>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateRegenerationLow ResponsiblePointer_ActorState_::setActorStateRegenerationLow() const
        {
            return Ent::Gen::ActorStateRegenerationLow(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::ActorStateTeleport> ResponsiblePointer_ActorState_::ActorStateTeleport() const
        {
            return strcmp(node->getUnionType(), "ActorStateTeleport") != 0? std::optional<Ent::Gen::ActorStateTeleport>{}: std::optional<Ent::Gen::ActorStateTeleport>(node->getUnionData());
        }
        inline Ent::Gen::ActorStateTeleport ResponsiblePointer_ActorState_::setActorStateTeleport() const
        {
            return Ent::Gen::ActorStateTeleport(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::EntityStateBoidsHomePos> ResponsiblePointer_ActorState_::EntityStateBoidsHomePos() const
        {
            return strcmp(node->getUnionType(), "EntityStateBoidsHomePos") != 0? std::optional<Ent::Gen::EntityStateBoidsHomePos>{}: std::optional<Ent::Gen::EntityStateBoidsHomePos>(node->getUnionData());
        }
        inline Ent::Gen::EntityStateBoidsHomePos ResponsiblePointer_ActorState_::setEntityStateBoidsHomePos() const
        {
            return Ent::Gen::EntityStateBoidsHomePos(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::EntityStateEnergyRootState> ResponsiblePointer_ActorState_::EntityStateEnergyRootState() const
        {
            return strcmp(node->getUnionType(), "EntityStateEnergyRootState") != 0? std::optional<Ent::Gen::EntityStateEnergyRootState>{}: std::optional<Ent::Gen::EntityStateEnergyRootState>(node->getUnionData());
        }
        inline Ent::Gen::EntityStateEnergyRootState ResponsiblePointer_ActorState_::setEntityStateEnergyRootState() const
        {
            return Ent::Gen::EntityStateEnergyRootState(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::EntityStateEnergySpoutState> ResponsiblePointer_ActorState_::EntityStateEnergySpoutState() const
        {
            return strcmp(node->getUnionType(), "EntityStateEnergySpoutState") != 0? std::optional<Ent::Gen::EntityStateEnergySpoutState>{}: std::optional<Ent::Gen::EntityStateEnergySpoutState>(node->getUnionData());
        }
        inline Ent::Gen::EntityStateEnergySpoutState ResponsiblePointer_ActorState_::setEntityStateEnergySpoutState() const
        {
            return Ent::Gen::EntityStateEnergySpoutState(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::EntityStateForceCanBeTargeted> ResponsiblePointer_ActorState_::EntityStateForceCanBeTargeted() const
        {
            return strcmp(node->getUnionType(), "EntityStateForceCanBeTargeted") != 0? std::optional<Ent::Gen::EntityStateForceCanBeTargeted>{}: std::optional<Ent::Gen::EntityStateForceCanBeTargeted>(node->getUnionData());
        }
        inline Ent::Gen::EntityStateForceCanBeTargeted ResponsiblePointer_ActorState_::setEntityStateForceCanBeTargeted() const
        {
            return Ent::Gen::EntityStateForceCanBeTargeted(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::EntityStateMask> ResponsiblePointer_ActorState_::EntityStateMask() const
        {
            return strcmp(node->getUnionType(), "EntityStateMask") != 0? std::optional<Ent::Gen::EntityStateMask>{}: std::optional<Ent::Gen::EntityStateMask>(node->getUnionData());
        }
        inline Ent::Gen::EntityStateMask ResponsiblePointer_ActorState_::setEntityStateMask() const
        {
            return Ent::Gen::EntityStateMask(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::EntityStatePlayer> ResponsiblePointer_ActorState_::EntityStatePlayer() const
        {
            return strcmp(node->getUnionType(), "EntityStatePlayer") != 0? std::optional<Ent::Gen::EntityStatePlayer>{}: std::optional<Ent::Gen::EntityStatePlayer>(node->getUnionData());
        }
        inline Ent::Gen::EntityStatePlayer ResponsiblePointer_ActorState_::setEntityStatePlayer() const
        {
            return Ent::Gen::EntityStatePlayer(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        inline std::optional<Ent::Gen::EntityStateVoxelsVolume> ResponsiblePointer_ActorState_::EntityStateVoxelsVolume() const
        {
            return strcmp(node->getUnionType(), "EntityStateVoxelsVolume") != 0? std::optional<Ent::Gen::EntityStateVoxelsVolume>{}: std::optional<Ent::Gen::EntityStateVoxelsVolume>(node->getUnionData());
        }
        inline Ent::Gen::EntityStateVoxelsVolume ResponsiblePointer_ActorState_::setEntityStateVoxelsVolume() const
        {
            return Ent::Gen::EntityStateVoxelsVolume(node->setUnionType("ResponsiblePointer_ActorState_"));
        }
        // sPhysicsJointDesc
        inline Ent::Gen::sJointBallDesc sPhysicsJointDesc::Ball() const
        {
            return Ent::Gen::sJointBallDesc(node->at("Ball"));
        }
        inline Ent::Gen::sJointFixedDesc sPhysicsJointDesc::Fixed() const
        {
            return Ent::Gen::sJointFixedDesc(node->at("Fixed"));
        }
        inline Ent::Gen::sJointHingeDesc sPhysicsJointDesc::Hinge() const
        {
            return Ent::Gen::sJointHingeDesc(node->at("Hinge"));
        }
        inline Ent::Gen::String sPhysicsJointDesc::JointType() const
        {
            return Ent::Gen::String(node->at("JointType"));
        }
        inline Ent::Gen::sJointSliderDesc sPhysicsJointDesc::Slider() const
        {
            return Ent::Gen::sJointSliderDesc(node->at("Slider"));
        }
        inline Ent::Gen::sJointSwingTwistDesc sPhysicsJointDesc::SwingTwist() const
        {
            return Ent::Gen::sJointSwingTwistDesc(node->at("SwingTwist"));
        }
        inline Ent::Gen::sJointUniversalDesc sPhysicsJointDesc::Universal() const
        {
            return Ent::Gen::sJointUniversalDesc(node->at("Universal"));
        }
        inline Ent::Gen::String sPhysicsJointDesc::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline PrimArray<Ent::Gen::String> sPhysicsJointDesc::flags() const
        {
            return PrimArray<Ent::Gen::String>(node->at("flags"));
        }
        inline Ent::Gen::Int sPhysicsJointDesc::idRigodBodyA() const
        {
            return Ent::Gen::Int(node->at("idRigodBodyA"));
        }
        inline Ent::Gen::Int sPhysicsJointDesc::idRigodBodyB() const
        {
            return Ent::Gen::Int(node->at("idRigodBodyB"));
        }
        inline Ent::Gen::Quat sPhysicsJointDesc::orientation() const
        {
            return Ent::Gen::Quat(node->at("orientation"));
        }
        inline Ent::Gen::String sPhysicsJointDesc::parent() const
        {
            return Ent::Gen::String(node->at("parent"));
        }
        inline Ent::Gen::Vector3 sPhysicsJointDesc::translation() const
        {
            return Ent::Gen::Vector3(node->at("translation"));
        }
        // sPhysicShape
        inline Ent::Gen::sPhysicsShapeBox sPhysicShape::Box() const
        {
            return Ent::Gen::sPhysicsShapeBox(node->at("Box"));
        }
        inline Ent::Gen::sPhysicsShapeCapsule sPhysicShape::Capsule() const
        {
            return Ent::Gen::sPhysicsShapeCapsule(node->at("Capsule"));
        }
        inline Ent::Gen::sPhysicsShapeCylinder sPhysicShape::Cylinder() const
        {
            return Ent::Gen::sPhysicsShapeCylinder(node->at("Cylinder"));
        }
        inline Ent::Gen::sPhysicsShapeMesh sPhysicShape::Mesh() const
        {
            return Ent::Gen::sPhysicsShapeMesh(node->at("Mesh"));
        }
        inline Ent::Gen::String sPhysicShape::PhysicsMaterial() const
        {
            return Ent::Gen::String(node->at("PhysicsMaterial"));
        }
        inline Ent::Gen::sPhysicsShapeSphere sPhysicShape::Sphere() const
        {
            return Ent::Gen::sPhysicsShapeSphere(node->at("Sphere"));
        }
        inline Ent::Gen::String sPhysicShape::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Vector3 sPhysicShape::angles() const
        {
            return Ent::Gen::Vector3(node->at("angles"));
        }
        inline Ent::Gen::Quat sPhysicShape::orientation() const
        {
            return Ent::Gen::Quat(node->at("orientation"));
        }
        inline Ent::Gen::Float sPhysicShape::scale() const
        {
            return Ent::Gen::Float(node->at("scale"));
        }
        inline Ent::Gen::Vector3 sPhysicShape::translation() const
        {
            return Ent::Gen::Vector3(node->at("translation"));
        }
        // sRigidBodyDesc
        inline Ent::Gen::String sRigidBodyDesc::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Vector3 sRigidBodyDesc::angles() const
        {
            return Ent::Gen::Vector3(node->at("angles"));
        }
        inline PrimArray<Ent::Gen::String> sRigidBodyDesc::flags() const
        {
            return PrimArray<Ent::Gen::String>(node->at("flags"));
        }
        inline Ent::Gen::Int sRigidBodyDesc::id() const
        {
            return Ent::Gen::Int(node->at("id"));
        }
        inline Ent::Gen::String sRigidBodyDesc::motionType() const
        {
            return Ent::Gen::String(node->at("motionType"));
        }
        inline Ent::Gen::Quat sRigidBodyDesc::orientation() const
        {
            return Ent::Gen::Quat(node->at("orientation"));
        }
        inline Ent::Gen::String sRigidBodyDesc::parent() const
        {
            return Ent::Gen::String(node->at("parent"));
        }
        inline Ent::Gen::Float sRigidBodyDesc::scale() const
        {
            return Ent::Gen::Float(node->at("scale"));
        }
        inline Array<Ent::Gen::sPhysicShape> sRigidBodyDesc::shapes() const
        {
            return Array<Ent::Gen::sPhysicShape>(node->at("shapes"));
        }
        inline Ent::Gen::Vector3 sRigidBodyDesc::translation() const
        {
            return Ent::Gen::Vector3(node->at("translation"));
        }
        // Transform3D
        inline Ent::Gen::String Transform3D::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Quat Transform3D::orientation() const
        {
            return Ent::Gen::Quat(node->at("orientation"));
        }
        inline Ent::Gen::Vector3 Transform3D::scale() const
        {
            return Ent::Gen::Vector3(node->at("scale"));
        }
        inline Ent::Gen::Vector3 Transform3D::translation() const
        {
            return Ent::Gen::Vector3(node->at("translation"));
        }
        // ProgressSoundEventData
        inline Ent::Gen::String ProgressSoundEventData::DecreaseEventName() const
        {
            return Ent::Gen::String(node->at("DecreaseEventName"));
        }
        inline Ent::Gen::Float ProgressSoundEventData::DecreaseStartThreshold() const
        {
            return Ent::Gen::Float(node->at("DecreaseStartThreshold"));
        }
        inline Ent::Gen::Float ProgressSoundEventData::DecreaseStopThreshold() const
        {
            return Ent::Gen::Float(node->at("DecreaseStopThreshold"));
        }
        inline Ent::Gen::String ProgressSoundEventData::EventBank() const
        {
            return Ent::Gen::String(node->at("EventBank"));
        }
        inline Ent::Gen::Bool ProgressSoundEventData::EventLooping() const
        {
            return Ent::Gen::Bool(node->at("EventLooping"));
        }
        inline Ent::Gen::String ProgressSoundEventData::IncreaseEventName() const
        {
            return Ent::Gen::String(node->at("IncreaseEventName"));
        }
        inline Ent::Gen::Float ProgressSoundEventData::IncreaseStartThreshold() const
        {
            return Ent::Gen::Float(node->at("IncreaseStartThreshold"));
        }
        inline Ent::Gen::Float ProgressSoundEventData::IncreaseStopThreshold() const
        {
            return Ent::Gen::Float(node->at("IncreaseStopThreshold"));
        }
        inline Ent::Gen::String ProgressSoundEventData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PrimitiveData
        inline Ent::Gen::Float PrimitiveData::Height() const
        {
            return Ent::Gen::Float(node->at("Height"));
        }
        inline Ent::Gen::Float PrimitiveData::Length() const
        {
            return Ent::Gen::Float(node->at("Length"));
        }
        inline Ent::Gen::Float PrimitiveData::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::Float PrimitiveData::Width() const
        {
            return Ent::Gen::Float(node->at("Width"));
        }
        inline Ent::Gen::String PrimitiveData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PredictionBehaviorDuration
        inline Ent::Gen::Float PredictionBehaviorDuration::Locked() const
        {
            return Ent::Gen::Float(node->at("Locked"));
        }
        inline Ent::Gen::Float PredictionBehaviorDuration::Step() const
        {
            return Ent::Gen::Float(node->at("Step"));
        }
        inline Ent::Gen::Float PredictionBehaviorDuration::Total() const
        {
            return Ent::Gen::Float(node->at("Total"));
        }
        inline Ent::Gen::String PredictionBehaviorDuration::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PredictionBehaviorData
        inline Ent::Gen::PredictionBehaviorDuration PredictionBehaviorData::Duration() const
        {
            return Ent::Gen::PredictionBehaviorDuration(node->at("Duration"));
        }
        inline Ent::Gen::String PredictionBehaviorData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // OutfitPiece
        inline Ent::Gen::EntityRef OutfitPiece::EntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("EntityRef"));
        }
        inline Ent::Gen::OutfitPieceType OutfitPiece::Slot() const
        {
            return Ent::Gen::OutfitPieceType(node->at("Slot"));
        }
        inline Ent::Gen::String OutfitPiece::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // Orientation
        inline Ent::Gen::String Orientation::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool Orientation::engaged() const
        {
            return Ent::Gen::Bool(node->at("engaged"));
        }
        inline Ent::Gen::Quat Orientation::val() const
        {
            return Ent::Gen::Quat(node->at("val"));
        }
        // NavmeshGenerationParameters
        inline Ent::Gen::Float NavmeshGenerationParameters::CreatureHeight() const
        {
            return Ent::Gen::Float(node->at("CreatureHeight"));
        }
        inline Ent::Gen::Float NavmeshGenerationParameters::CreatureRadius() const
        {
            return Ent::Gen::Float(node->at("CreatureRadius"));
        }
        inline Ent::Gen::Bool NavmeshGenerationParameters::MarkWaterAreas() const
        {
            return Ent::Gen::Bool(node->at("MarkWaterAreas"));
        }
        inline Ent::Gen::Float NavmeshGenerationParameters::MaxClimbHeight() const
        {
            return Ent::Gen::Float(node->at("MaxClimbHeight"));
        }
        inline Ent::Gen::Float NavmeshGenerationParameters::MaxWalkableSlopeAngle() const
        {
            return Ent::Gen::Float(node->at("MaxWalkableSlopeAngle"));
        }
        inline Ent::Gen::Float NavmeshGenerationParameters::MinWaterDepth() const
        {
            return Ent::Gen::Float(node->at("MinWaterDepth"));
        }
        inline PrimArray<Ent::Gen::String> NavmeshGenerationParameters::SizeLayerMask() const
        {
            return PrimArray<Ent::Gen::String>(node->at("SizeLayerMask"));
        }
        inline Ent::Gen::Float NavmeshGenerationParameters::TileWorldSize() const
        {
            return Ent::Gen::Float(node->at("TileWorldSize"));
        }
        inline Ent::Gen::String NavmeshGenerationParameters::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MoveCapacityData_OrientationSpeed
        inline Ent::Gen::String MoveCapacityData_OrientationSpeed::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Vector3 MoveCapacityData_OrientationSpeed::factor() const
        {
            return Ent::Gen::Vector3(node->at("factor"));
        }
        inline Ent::Gen::Vector3 MoveCapacityData_OrientationSpeed::rate() const
        {
            return Ent::Gen::Vector3(node->at("rate"));
        }
        inline Ent::Gen::ScaleConverter MoveCapacityData_OrientationSpeed::rotationRollFromAngularSpeed() const
        {
            return Ent::Gen::ScaleConverter(node->at("rotationRollFromAngularSpeed"));
        }
        inline Ent::Gen::ScaleConverter MoveCapacityData_OrientationSpeed::speedFactorFromSpeedSlow() const
        {
            return Ent::Gen::ScaleConverter(node->at("speedFactorFromSpeedSlow"));
        }
        inline Ent::Gen::Vector3 MoveCapacityData_OrientationSpeed::speedMax() const
        {
            return Ent::Gen::Vector3(node->at("speedMax"));
        }
        inline Ent::Gen::Vector3 MoveCapacityData_OrientationSpeed::steeringAngle() const
        {
            return Ent::Gen::Vector3(node->at("steeringAngle"));
        }
        // MountableSnapLine_ControlPoint
        inline Ent::Gen::String MountableSnapLine_ControlPoint::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Int MountableSnapLine_ControlPoint::boneId() const
        {
            return Ent::Gen::Int(node->at("boneId"));
        }
        inline Ent::Gen::Vector3 MountableSnapLine_ControlPoint::offset() const
        {
            return Ent::Gen::Vector3(node->at("offset"));
        }
        inline Ent::Gen::Float MountableSnapLine_ControlPoint::radius() const
        {
            return Ent::Gen::Float(node->at("radius"));
        }
        // MountData
        inline Ent::Gen::String MountData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float MountData::acrobaticJumpDistance() const
        {
            return Ent::Gen::Float(node->at("acrobaticJumpDistance"));
        }
        inline Ent::Gen::Float MountData::angle() const
        {
            return Ent::Gen::Float(node->at("angle"));
        }
        inline Ent::Gen::Float MountData::blindAngle() const
        {
            return Ent::Gen::Float(node->at("blindAngle"));
        }
        inline Ent::Gen::Float MountData::distance() const
        {
            return Ent::Gen::Float(node->at("distance"));
        }
        inline Ent::Gen::Float MountData::offset() const
        {
            return Ent::Gen::Float(node->at("offset"));
        }
        // MeshesItem
        inline Ent::Gen::String MeshesItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::String MeshesItem::mesh() const
        {
            return Ent::Gen::String(node->at("mesh"));
        }
        // RUNTIME_LODsItem
        inline Array<Ent::Gen::MeshesItem> RUNTIME_LODsItem::Meshes() const
        {
            return Array<Ent::Gen::MeshesItem>(node->at("Meshes"));
        }
        inline Ent::Gen::String RUNTIME_LODsItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MeshNavigationBehaviorData
        inline Ent::Gen::Bool MeshNavigationBehaviorData::EdgeTransitionConstraintAllowed() const
        {
            return Ent::Gen::Bool(node->at("EdgeTransitionConstraintAllowed"));
        }
        inline Ent::Gen::Float MeshNavigationBehaviorData::EdgeTransitionConstraintLedgeAngle() const
        {
            return Ent::Gen::Float(node->at("EdgeTransitionConstraintLedgeAngle"));
        }
        inline Ent::Gen::Float MeshNavigationBehaviorData::EdgeTransitionConstraintWallAngle() const
        {
            return Ent::Gen::Float(node->at("EdgeTransitionConstraintWallAngle"));
        }
        inline Ent::Gen::Float MeshNavigationBehaviorData::MaxNormalAngle() const
        {
            return Ent::Gen::Float(node->at("MaxNormalAngle"));
        }
        inline Ent::Gen::MeshNavigationAllowedMode MeshNavigationBehaviorData::MeshNavigationAllowedMode() const
        {
            return Ent::Gen::MeshNavigationAllowedMode(node->at("MeshNavigationAllowedMode"));
        }
        inline Ent::Gen::Float MeshNavigationBehaviorData::RayCastLengthLegFactor() const
        {
            return Ent::Gen::Float(node->at("RayCastLengthLegFactor"));
        }
        inline Ent::Gen::Float MeshNavigationBehaviorData::RayCastLengthSpeedFactor() const
        {
            return Ent::Gen::Float(node->at("RayCastLengthSpeedFactor"));
        }
        inline Ent::Gen::Bool MeshNavigationBehaviorData::RollAllowed() const
        {
            return Ent::Gen::Bool(node->at("RollAllowed"));
        }
        inline Ent::Gen::Bool MeshNavigationBehaviorData::StickToAnyNormalAllowed() const
        {
            return Ent::Gen::Bool(node->at("StickToAnyNormalAllowed"));
        }
        inline Ent::Gen::String MeshNavigationBehaviorData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // VolumeConstraintDataGD
        inline Ent::Gen::Matrix44 VolumeConstraintDataGD::Matrix() const
        {
            return Ent::Gen::Matrix44(node->at("Matrix"));
        }
        inline Ent::Gen::TransitionNeighborData VolumeConstraintDataGD::Neighbors() const
        {
            return Ent::Gen::TransitionNeighborData(node->at("Neighbors"));
        }
        inline Ent::Gen::Vector3 VolumeConstraintDataGD::Size() const
        {
            return Ent::Gen::Vector3(node->at("Size"));
        }
        inline PrimArray<Ent::Gen::String> VolumeConstraintDataGD::Tags() const
        {
            return PrimArray<Ent::Gen::String>(node->at("Tags"));
        }
        inline Ent::Gen::String VolumeConstraintDataGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MoveCapacityData_ReachSpeed
        inline Ent::Gen::String MoveCapacityData_ReachSpeed::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float MoveCapacityData_ReachSpeed::acceleration() const
        {
            return Ent::Gen::Float(node->at("acceleration"));
        }
        inline Ent::Gen::Float MoveCapacityData_ReachSpeed::deceleration() const
        {
            return Ent::Gen::Float(node->at("deceleration"));
        }
        inline Ent::Gen::LocomotionMode MoveCapacityData_ReachSpeed::name() const
        {
            return Ent::Gen::LocomotionMode(node->at("name"));
        }
        // ListItem
        inline Ent::Gen::String ListItem::EntityPath() const
        {
            return Ent::Gen::String(node->at("EntityPath"));
        }
        inline Ent::Gen::EntityRef ListItem::EntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("EntityRef"));
        }
        inline Ent::Gen::String ListItem::Tag() const
        {
            return Ent::Gen::String(node->at("Tag"));
        }
        inline Ent::Gen::String ListItem::Thumbnail() const
        {
            return Ent::Gen::String(node->at("Thumbnail"));
        }
        inline Ent::Gen::String ListItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // LifeAndDamageData
        inline Ent::Gen::String LifeAndDamageData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float LifeAndDamageData::attackCancelThreshold() const
        {
            return Ent::Gen::Float(node->at("attackCancelThreshold"));
        }
        inline Ent::Gen::Float LifeAndDamageData::damageThreshold() const
        {
            return Ent::Gen::Float(node->at("damageThreshold"));
        }
        inline Ent::Gen::Float LifeAndDamageData::dyingSolidity() const
        {
            return Ent::Gen::Float(node->at("dyingSolidity"));
        }
        inline Ent::Gen::Float LifeAndDamageData::energyMax() const
        {
            return Ent::Gen::Float(node->at("energyMax"));
        }
        inline Ent::Gen::Float LifeAndDamageData::energyRecoverSpeed() const
        {
            return Ent::Gen::Float(node->at("energyRecoverSpeed"));
        }
        inline PrimArray<Ent::Gen::Float> LifeAndDamageData::impactPercent() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("impactPercent"));
        }
        inline Ent::Gen::Float LifeAndDamageData::lifeInjuredCoeff() const
        {
            return Ent::Gen::Float(node->at("lifeInjuredCoeff"));
        }
        inline Ent::Gen::Float LifeAndDamageData::lifeMax() const
        {
            return Ent::Gen::Float(node->at("lifeMax"));
        }
        inline Ent::Gen::Float LifeAndDamageData::lifeRecoverSpeed() const
        {
            return Ent::Gen::Float(node->at("lifeRecoverSpeed"));
        }
        inline Ent::Gen::Float LifeAndDamageData::lifeStunCoeff() const
        {
            return Ent::Gen::Float(node->at("lifeStunCoeff"));
        }
        inline Ent::Gen::Float LifeAndDamageData::minLifeWhenSpending() const
        {
            return Ent::Gen::Float(node->at("minLifeWhenSpending"));
        }
        inline Ent::Gen::Bool LifeAndDamageData::shouldCrashWhenFlyingInjured() const
        {
            return Ent::Gen::Bool(node->at("shouldCrashWhenFlyingInjured"));
        }
        inline Ent::Gen::Float LifeAndDamageData::solidity() const
        {
            return Ent::Gen::Float(node->at("solidity"));
        }
        inline Ent::Gen::Bool LifeAndDamageData::unbreakable() const
        {
            return Ent::Gen::Bool(node->at("unbreakable"));
        }
        inline Ent::Gen::Float LifeAndDamageData::velocityDamageMax() const
        {
            return Ent::Gen::Float(node->at("velocityDamageMax"));
        }
        inline Ent::Gen::Float LifeAndDamageData::velocityImpactMax() const
        {
            return Ent::Gen::Float(node->at("velocityImpactMax"));
        }
        // LastAliveReviveSide
        inline Ent::Gen::String LastAliveReviveSide::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool LastAliveReviveSide::engaged() const
        {
            return Ent::Gen::Bool(node->at("engaged"));
        }
        inline Ent::Gen::ReviveSide LastAliveReviveSide::val() const
        {
            return Ent::Gen::ReviveSide(node->at("val"));
        }
        // InteractData
        inline Ent::Gen::String InteractData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float InteractData::distance() const
        {
            return Ent::Gen::Float(node->at("distance"));
        }
        // InputCollisionBehaviorData
        inline Ent::Gen::Float InputCollisionBehaviorData::AltitudeMax() const
        {
            return Ent::Gen::Float(node->at("AltitudeMax"));
        }
        inline Ent::Gen::Float InputCollisionBehaviorData::DepthMax() const
        {
            return Ent::Gen::Float(node->at("DepthMax"));
        }
        inline Ent::Gen::Float InputCollisionBehaviorData::FrontAngle() const
        {
            return Ent::Gen::Float(node->at("FrontAngle"));
        }
        inline Ent::Gen::Float InputCollisionBehaviorData::RadiusCoeff() const
        {
            return Ent::Gen::Float(node->at("RadiusCoeff"));
        }
        inline Ent::Gen::String InputCollisionBehaviorData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ImmersedBehaviorData
        inline Ent::Gen::String ImmersedBehaviorData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float ImmersedBehaviorData::depth() const
        {
            return Ent::Gen::Float(node->at("depth"));
        }
        inline Ent::Gen::Float ImmersedBehaviorData::depthHysteresisCoeff() const
        {
            return Ent::Gen::Float(node->at("depthHysteresisCoeff"));
        }
        inline Ent::Gen::ScaleConverter ImmersedBehaviorData::depthMaxRange() const
        {
            return Ent::Gen::ScaleConverter(node->at("depthMaxRange"));
        }
        inline Ent::Gen::Float ImmersedBehaviorData::flotation() const
        {
            return Ent::Gen::Float(node->at("flotation"));
        }
        inline Ent::Gen::Bool ImmersedBehaviorData::isAllowed() const
        {
            return Ent::Gen::Bool(node->at("isAllowed"));
        }
        inline Ent::Gen::Float ImmersedBehaviorData::minTooDeepPushSpeed() const
        {
            return Ent::Gen::Float(node->at("minTooDeepPushSpeed"));
        }
        inline Ent::Gen::Float ImmersedBehaviorData::reachSurfaceAccelerationCoeff() const
        {
            return Ent::Gen::Float(node->at("reachSurfaceAccelerationCoeff"));
        }
        // PickableDistributorComponentData
        inline Ent::Gen::EntityRef PickableDistributorComponentData::EntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("EntityRef"));
        }
        inline Ent::Gen::HotSpotType PickableDistributorComponentData::HotspotType() const
        {
            return Ent::Gen::HotSpotType(node->at("HotspotType"));
        }
        inline Ent::Gen::String PickableDistributorComponentData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HotspotData
        inline Ent::Gen::String HotspotData::Bone() const
        {
            return Ent::Gen::String(node->at("Bone"));
        }
        inline Ent::Gen::Vector3 HotspotData::Offset() const
        {
            return Ent::Gen::Vector3(node->at("Offset"));
        }
        inline Ent::Gen::Quat HotspotData::Orientation() const
        {
            return Ent::Gen::Quat(node->at("Orientation"));
        }
        inline Ent::Gen::Float HotspotData::Scale() const
        {
            return Ent::Gen::Float(node->at("Scale"));
        }
        inline Ent::Gen::PrimitiveSet<char const*> HotspotData::Tags() const
        {
            return Ent::Gen::PrimitiveSet<char const*>(node->at("Tags"));
        }
        inline Ent::Gen::EntityRef HotspotData::TargetEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("TargetEntityRef"));
        }
        inline Ent::Gen::HotSpotType HotspotData::Type_() const
        {
            return Ent::Gen::HotSpotType(node->at("Type_"));
        }
        inline Ent::Gen::String HotspotData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HeadCollisionBehaviorData
        inline Ent::Gen::String HeadCollisionBehaviorData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float HeadCollisionBehaviorData::disableDuration() const
        {
            return Ent::Gen::Float(node->at("disableDuration"));
        }
        inline Ent::Gen::Float HeadCollisionBehaviorData::enableDuration() const
        {
            return Ent::Gen::Float(node->at("enableDuration"));
        }
        inline Ent::Gen::Vector3 HeadCollisionBehaviorData::headOffset() const
        {
            return Ent::Gen::Vector3(node->at("headOffset"));
        }
        inline Ent::Gen::Bool HeadCollisionBehaviorData::isEnabled() const
        {
            return Ent::Gen::Bool(node->at("isEnabled"));
        }
        inline Ent::Gen::Float HeadCollisionBehaviorData::radiusCoeff() const
        {
            return Ent::Gen::Float(node->at("radiusCoeff"));
        }
        inline Ent::Gen::ScaleConverter HeadCollisionBehaviorData::slopeInfluence() const
        {
            return Ent::Gen::ScaleConverter(node->at("slopeInfluence"));
        }
        inline Ent::Gen::Float HeadCollisionBehaviorData::softCollisionRigidbodyCoeff() const
        {
            return Ent::Gen::Float(node->at("softCollisionRigidbodyCoeff"));
        }
        inline Ent::Gen::Float HeadCollisionBehaviorData::softCollisionVisualCoeff() const
        {
            return Ent::Gen::Float(node->at("softCollisionVisualCoeff"));
        }
        inline Ent::Gen::ScaleConverter HeadCollisionBehaviorData::speedInfluence() const
        {
            return Ent::Gen::ScaleConverter(node->at("speedInfluence"));
        }
        inline Ent::Gen::ScaleConverter HeadCollisionBehaviorData::visualSmoothOut() const
        {
            return Ent::Gen::ScaleConverter(node->at("visualSmoothOut"));
        }
        // FusionData
        inline Ent::Gen::Bool FusionData::IsSoul() const
        {
            return Ent::Gen::Bool(node->at("IsSoul"));
        }
        inline Ent::Gen::EntityRef FusionData::SoulEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("SoulEntityRef"));
        }
        inline Ent::Gen::Float FusionData::WarriorDamageFactor() const
        {
            return Ent::Gen::Float(node->at("WarriorDamageFactor"));
        }
        inline Ent::Gen::Float FusionData::WarriorImpactFactor() const
        {
            return Ent::Gen::Float(node->at("WarriorImpactFactor"));
        }
        inline Ent::Gen::String FusionData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FreezeData
        inline Ent::Gen::String FreezeData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float FreezeData::deltaTimeFactor() const
        {
            return Ent::Gen::Float(node->at("deltaTimeFactor"));
        }
        inline Ent::Gen::eventStringHash FreezeData::eventStringHash() const
        {
            return Ent::Gen::eventStringHash(node->at("eventStringHash"));
        }
        inline Ent::Gen::Float FreezeData::stateDuration() const
        {
            return Ent::Gen::Float(node->at("stateDuration"));
        }
        inline Ent::Gen::Float FreezeData::transitionInDuration() const
        {
            return Ent::Gen::Float(node->at("transitionInDuration"));
        }
        inline Ent::Gen::Float FreezeData::transitionOutDuration() const
        {
            return Ent::Gen::Float(node->at("transitionOutDuration"));
        }
        // ProjectileData
        inline Ent::Gen::String ProjectileData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool ProjectileData::canCollideWithOtherProjectiles() const
        {
            return Ent::Gen::Bool(node->at("canCollideWithOtherProjectiles"));
        }
        inline Ent::Gen::Float ProjectileData::damages() const
        {
            return Ent::Gen::Float(node->at("damages"));
        }
        inline Ent::Gen::Float ProjectileData::deleteAfterPlantTimer() const
        {
            return Ent::Gen::Float(node->at("deleteAfterPlantTimer"));
        }
        inline Ent::Gen::Bool ProjectileData::destroyOnHit() const
        {
            return Ent::Gen::Bool(node->at("destroyOnHit"));
        }
        inline Ent::Gen::Float ProjectileData::distanceFromBodyAtLaunch() const
        {
            return Ent::Gen::Float(node->at("distanceFromBodyAtLaunch"));
        }
        inline Ent::Gen::Bool ProjectileData::explodeOnFire() const
        {
            return Ent::Gen::Bool(node->at("explodeOnFire"));
        }
        inline Ent::Gen::Float ProjectileData::explosionShockForce() const
        {
            return Ent::Gen::Float(node->at("explosionShockForce"));
        }
        inline Ent::Gen::FreezeData ProjectileData::freezeData() const
        {
            return Ent::Gen::FreezeData(node->at("freezeData"));
        }
        inline PrimArray<Ent::Gen::String> ProjectileData::gameEffectOnHit() const
        {
            return PrimArray<Ent::Gen::String>(node->at("gameEffectOnHit"));
        }
        inline Ent::Gen::Float ProjectileData::gravity() const
        {
            return Ent::Gen::Float(node->at("gravity"));
        }
        inline Ent::Gen::Bool ProjectileData::hasNoCollision() const
        {
            return Ent::Gen::Bool(node->at("hasNoCollision"));
        }
        inline Ent::Gen::Vector3 ProjectileData::hitSourceOffset() const
        {
            return Ent::Gen::Vector3(node->at("hitSourceOffset"));
        }
        inline Ent::Gen::Float ProjectileData::homingInRangeAnticipationDist() const
        {
            return Ent::Gen::Float(node->at("homingInRangeAnticipationDist"));
        }
        inline Ent::Gen::Float ProjectileData::homingMaxAngle() const
        {
            return Ent::Gen::Float(node->at("homingMaxAngle"));
        }
        inline Ent::Gen::Float ProjectileData::homingMaxFlightTime() const
        {
            return Ent::Gen::Float(node->at("homingMaxFlightTime"));
        }
        inline Ent::Gen::Float ProjectileData::homingMaxInFrontAnticipationDist() const
        {
            return Ent::Gen::Float(node->at("homingMaxInFrontAnticipationDist"));
        }
        inline Ent::Gen::Float ProjectileData::homingMaxTotalAnticipationDist() const
        {
            return Ent::Gen::Float(node->at("homingMaxTotalAnticipationDist"));
        }
        inline PrimArray<Ent::Gen::Float> ProjectileData::homingTotalAnticipationRatioSpeeds() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("homingTotalAnticipationRatioSpeeds"));
        }
        inline Ent::Gen::Float ProjectileData::impact() const
        {
            return Ent::Gen::Float(node->at("impact"));
        }
        inline Ent::Gen::Bool ProjectileData::isRegenProjectile() const
        {
            return Ent::Gen::Bool(node->at("isRegenProjectile"));
        }
        inline Ent::Gen::Bool ProjectileData::isThrowable() const
        {
            return Ent::Gen::Bool(node->at("isThrowable"));
        }
        inline Ent::Gen::Vector3 ProjectileData::launchRotation() const
        {
            return Ent::Gen::Vector3(node->at("launchRotation"));
        }
        inline Ent::Gen::Float ProjectileData::launchSpeed() const
        {
            return Ent::Gen::Float(node->at("launchSpeed"));
        }
        inline Ent::Gen::Float ProjectileData::noiseLevelOnImpact() const
        {
            return Ent::Gen::Float(node->at("noiseLevelOnImpact"));
        }
        inline Ent::Gen::Bool ProjectileData::shouldBeVisibleBeforeShoot() const
        {
            return Ent::Gen::Bool(node->at("shouldBeVisibleBeforeShoot"));
        }
        inline Ent::Gen::Float ProjectileData::smoothTime() const
        {
            return Ent::Gen::Float(node->at("smoothTime"));
        }
        inline Ent::Gen::Bool ProjectileData::stopOnWater() const
        {
            return Ent::Gen::Bool(node->at("stopOnWater"));
        }
        inline Ent::Gen::Float ProjectileData::straightDistance() const
        {
            return Ent::Gen::Float(node->at("straightDistance"));
        }
        inline Ent::Gen::Bool ProjectileData::visibleInFlight() const
        {
            return Ent::Gen::Bool(node->at("visibleInFlight"));
        }
        // FluidVolumeComponentGD_SimulationParameters
        inline Ent::Gen::Float FluidVolumeComponentGD_SimulationParameters::Evaporation() const
        {
            return Ent::Gen::Float(node->at("Evaporation"));
        }
        inline Ent::Gen::Float FluidVolumeComponentGD_SimulationParameters::Momentum() const
        {
            return Ent::Gen::Float(node->at("Momentum"));
        }
        inline Ent::Gen::Float FluidVolumeComponentGD_SimulationParameters::Precision() const
        {
            return Ent::Gen::Float(node->at("Precision"));
        }
        inline Ent::Gen::Float FluidVolumeComponentGD_SimulationParameters::Viscosity() const
        {
            return Ent::Gen::Float(node->at("Viscosity"));
        }
        inline Ent::Gen::String FluidVolumeComponentGD_SimulationParameters::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FluidVolumeComponentGD_HeightMapData
        inline Ent::Gen::String FluidVolumeComponentGD_HeightMapData::Path() const
        {
            return Ent::Gen::String(node->at("Path"));
        }
        inline Ent::Gen::String FluidVolumeComponentGD_HeightMapData::TerrainName() const
        {
            return Ent::Gen::String(node->at("TerrainName"));
        }
        inline Ent::Gen::Vector2 FluidVolumeComponentGD_HeightMapData::WorldSize() const
        {
            return Ent::Gen::Vector2(node->at("WorldSize"));
        }
        inline Ent::Gen::String FluidVolumeComponentGD_HeightMapData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FluidVolumeComponentGD_FluidVolumeData
        inline Ent::Gen::FluidVolumeComponentGD_HeightMapData FluidVolumeComponentGD_FluidVolumeData::HeightMap() const
        {
            return Ent::Gen::FluidVolumeComponentGD_HeightMapData(node->at("HeightMap"));
        }
        inline Ent::Gen::Vector2 FluidVolumeComponentGD_FluidVolumeData::InHeightMapWorldSizeOffset() const
        {
            return Ent::Gen::Vector2(node->at("InHeightMapWorldSizeOffset"));
        }
        inline Ent::Gen::String FluidVolumeComponentGD_FluidVolumeData::Material() const
        {
            return Ent::Gen::String(node->at("Material"));
        }
        inline Ent::Gen::FluidVolumeComponentGD_SimulationParameters FluidVolumeComponentGD_FluidVolumeData::Simulation() const
        {
            return Ent::Gen::FluidVolumeComponentGD_SimulationParameters(node->at("Simulation"));
        }
        inline Ent::Gen::Vector2 FluidVolumeComponentGD_FluidVolumeData::WorldSize() const
        {
            return Ent::Gen::Vector2(node->at("WorldSize"));
        }
        inline Ent::Gen::String FluidVolumeComponentGD_FluidVolumeData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FloatRange
        inline Ent::Gen::Vector2 FloatRange::MinMax() const
        {
            return Ent::Gen::Vector2(node->at("MinMax"));
        }
        inline Ent::Gen::String FloatRange::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // VegetationPCloudData
        inline Ent::Gen::String VegetationPCloudData::PCloudPath() const
        {
            return Ent::Gen::String(node->at("PCloudPath"));
        }
        inline Ent::Gen::FloatRange VegetationPCloudData::RegenRange() const
        {
            return Ent::Gen::FloatRange(node->at("RegenRange"));
        }
        inline PrimArray<Ent::Gen::String> VegetationPCloudData::UsedVegetations() const
        {
            return PrimArray<Ent::Gen::String>(node->at("UsedVegetations"));
        }
        inline Ent::Gen::String VegetationPCloudData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EventCameraData
        inline Ent::Gen::Float EventCameraData::BlendCameraTime() const
        {
            return Ent::Gen::Float(node->at("BlendCameraTime"));
        }
        inline Ent::Gen::Bool EventCameraData::CameraAimTriggerActor() const
        {
            return Ent::Gen::Bool(node->at("CameraAimTriggerActor"));
        }
        inline Array<Ent::Gen::Vector3> EventCameraData::CameraOffsets() const
        {
            return Array<Ent::Gen::Vector3>(node->at("CameraOffsets"));
        }
        inline Ent::Gen::Float EventCameraData::DOFFarStart() const
        {
            return Ent::Gen::Float(node->at("DOFFarStart"));
        }
        inline Ent::Gen::Float EventCameraData::DOFFarStop() const
        {
            return Ent::Gen::Float(node->at("DOFFarStop"));
        }
        inline Ent::Gen::Float EventCameraData::DOFMultiplier() const
        {
            return Ent::Gen::Float(node->at("DOFMultiplier"));
        }
        inline Ent::Gen::Float EventCameraData::DOFNearStart() const
        {
            return Ent::Gen::Float(node->at("DOFNearStart"));
        }
        inline Ent::Gen::Float EventCameraData::DOFNearStop() const
        {
            return Ent::Gen::Float(node->at("DOFNearStop"));
        }
        inline Ent::Gen::Bool EventCameraData::DOFRelativeTarget() const
        {
            return Ent::Gen::Bool(node->at("DOFRelativeTarget"));
        }
        inline Ent::Gen::Float EventCameraData::EventCameraTime() const
        {
            return Ent::Gen::Float(node->at("EventCameraTime"));
        }
        inline Ent::Gen::Float EventCameraData::FOV() const
        {
            return Ent::Gen::Float(node->at("FOV"));
        }
        inline Ent::Gen::Bool EventCameraData::FixedCam() const
        {
            return Ent::Gen::Bool(node->at("FixedCam"));
        }
        inline Ent::Gen::Bool EventCameraData::FollowCam() const
        {
            return Ent::Gen::Bool(node->at("FollowCam"));
        }
        inline Ent::Gen::Bool EventCameraData::FollowTarget() const
        {
            return Ent::Gen::Bool(node->at("FollowTarget"));
        }
        inline Ent::Gen::Float EventCameraData::OffsetsBlendTime() const
        {
            return Ent::Gen::Float(node->at("OffsetsBlendTime"));
        }
        inline Ent::Gen::Bool EventCameraData::PositionsAngularBlend() const
        {
            return Ent::Gen::Bool(node->at("PositionsAngularBlend"));
        }
        inline Ent::Gen::Float EventCameraData::PositionsBlendTime() const
        {
            return Ent::Gen::Float(node->at("PositionsBlendTime"));
        }
        inline Array<Ent::Gen::Vector3> EventCameraData::TargetOffsets() const
        {
            return Array<Ent::Gen::Vector3>(node->at("TargetOffsets"));
        }
        inline Ent::Gen::Bool EventCameraData::UseDOF() const
        {
            return Ent::Gen::Bool(node->at("UseDOF"));
        }
        inline Ent::Gen::Bool EventCameraData::UseOffsetsSpline() const
        {
            return Ent::Gen::Bool(node->at("UseOffsetsSpline"));
        }
        inline Ent::Gen::Bool EventCameraData::UsePositionsSpline() const
        {
            return Ent::Gen::Bool(node->at("UsePositionsSpline"));
        }
        inline Ent::Gen::Bool EventCameraData::UseTriggerActorPosition() const
        {
            return Ent::Gen::Bool(node->at("UseTriggerActorPosition"));
        }
        inline Ent::Gen::Bool EventCameraData::UseTriggerActorSight() const
        {
            return Ent::Gen::Bool(node->at("UseTriggerActorSight"));
        }
        inline Ent::Gen::String EventCameraData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EntityLODData
        inline Ent::Gen::EntityRef EntityLODData::EntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("EntityRef"));
        }
        inline Ent::Gen::Float EntityLODData::MaxDist() const
        {
            return Ent::Gen::Float(node->at("MaxDist"));
        }
        inline Ent::Gen::String EntityLODData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // RegenData
        inline Array<Ent::Gen::EntityLODData> RegenData::LODData() const
        {
            return Array<Ent::Gen::EntityLODData>(node->at("LODData"));
        }
        inline Ent::Gen::FloatRange RegenData::RegenRange() const
        {
            return Ent::Gen::FloatRange(node->at("RegenRange"));
        }
        inline Ent::Gen::Float RegenData::RegenRangeHysteresis() const
        {
            return Ent::Gen::Float(node->at("RegenRangeHysteresis"));
        }
        inline Ent::Gen::String RegenData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EDITOR_Mesh
        inline Ent::Gen::String EDITOR_Mesh::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Int EDITOR_Mesh::id() const
        {
            return Ent::Gen::Int(node->at("id"));
        }
        inline Ent::Gen::String EDITOR_Mesh::path() const
        {
            return Ent::Gen::String(node->at("path"));
        }
        // EDITOR_LODsItem
        inline Ent::Gen::String EDITOR_LODsItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Int EDITOR_LODsItem::lod() const
        {
            return Ent::Gen::Int(node->at("lod"));
        }
        inline PrimArray<Ent::Gen::String> EDITOR_LODsItem::wvis() const
        {
            return PrimArray<Ent::Gen::String>(node->at("wvis"));
        }
        // DisplaceNoiseListItem
        inline Ent::Gen::Float DisplaceNoiseListItem::DisplaceDistance() const
        {
            return Ent::Gen::Float(node->at("DisplaceDistance"));
        }
        inline Ent::Gen::Float DisplaceNoiseListItem::LuminanceCenter() const
        {
            return Ent::Gen::Float(node->at("LuminanceCenter"));
        }
        inline Ent::Gen::Int DisplaceNoiseListItem::MapChannel() const
        {
            return Ent::Gen::Int(node->at("MapChannel"));
        }
        inline Ent::Gen::String DisplaceNoiseListItem::MotifName() const
        {
            return Ent::Gen::String(node->at("MotifName"));
        }
        inline Ent::Gen::Float DisplaceNoiseListItem::MotifOffsetX() const
        {
            return Ent::Gen::Float(node->at("MotifOffsetX"));
        }
        inline Ent::Gen::Float DisplaceNoiseListItem::MotifOffsetY() const
        {
            return Ent::Gen::Float(node->at("MotifOffsetY"));
        }
        inline Ent::Gen::Float DisplaceNoiseListItem::MotifRotationZ() const
        {
            return Ent::Gen::Float(node->at("MotifRotationZ"));
        }
        inline Ent::Gen::Float DisplaceNoiseListItem::MotifSizeX() const
        {
            return Ent::Gen::Float(node->at("MotifSizeX"));
        }
        inline Ent::Gen::Float DisplaceNoiseListItem::MotifSizeY() const
        {
            return Ent::Gen::Float(node->at("MotifSizeY"));
        }
        inline Ent::Gen::String DisplaceNoiseListItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CreatureDangerousness
        inline Ent::Gen::String CreatureDangerousness::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Int CreatureDangerousness::dangerousness() const
        {
            return Ent::Gen::Int(node->at("dangerousness"));
        }
        inline Ent::Gen::Float CreatureDangerousness::multiplierWhenInjured() const
        {
            return Ent::Gen::Float(node->at("multiplierWhenInjured"));
        }
        // ConditionalRigidityAttribute_RigidityParameter
        inline Ent::Gen::ScaleConverter ConditionalRigidityAttribute_RigidityParameter::Rigidity() const
        {
            return Ent::Gen::ScaleConverter(node->at("Rigidity"));
        }
        inline Ent::Gen::Float ConditionalRigidityAttribute_RigidityParameter::SpeedDown() const
        {
            return Ent::Gen::Float(node->at("SpeedDown"));
        }
        inline Ent::Gen::Float ConditionalRigidityAttribute_RigidityParameter::SpeedUp() const
        {
            return Ent::Gen::Float(node->at("SpeedUp"));
        }
        inline Ent::Gen::String ConditionalRigidityAttribute_RigidityParameter::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ConditionalRigidityAttribute_Conditions
        inline PrimArray<Ent::Gen::ActorCategory> ConditionalRigidityAttribute_Conditions::ActorCategories() const
        {
            return PrimArray<Ent::Gen::ActorCategory>(node->at("ActorCategories"));
        }
        inline PrimArray<Ent::Gen::String> ConditionalRigidityAttribute_Conditions::ActorStates() const
        {
            return PrimArray<Ent::Gen::String>(node->at("ActorStates"));
        }
        inline Ent::Gen::Vector2 ConditionalRigidityAttribute_Conditions::AngularVelocityFactorRange() const
        {
            return Ent::Gen::Vector2(node->at("AngularVelocityFactorRange"));
        }
        inline Ent::Gen::Vector2 ConditionalRigidityAttribute_Conditions::DirectionDotRange() const
        {
            return Ent::Gen::Vector2(node->at("DirectionDotRange"));
        }
        inline Ent::Gen::Vector2 ConditionalRigidityAttribute_Conditions::LinearVelocityFactorRange() const
        {
            return Ent::Gen::Vector2(node->at("LinearVelocityFactorRange"));
        }
        inline Ent::Gen::String ConditionalRigidityAttribute_Conditions::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ConditionalRigidityAttribute_Attributes
        inline Ent::Gen::ConditionalRigidityAttribute_RigidityParameter ConditionalRigidityAttribute_Attributes::DirectionAngular() const
        {
            return Ent::Gen::ConditionalRigidityAttribute_RigidityParameter(node->at("DirectionAngular"));
        }
        inline Ent::Gen::ConditionalRigidityAttribute_RigidityParameter ConditionalRigidityAttribute_Attributes::DirectionLinear() const
        {
            return Ent::Gen::ConditionalRigidityAttribute_RigidityParameter(node->at("DirectionLinear"));
        }
        inline Ent::Gen::ConditionalRigidityAttribute_RigidityParameter ConditionalRigidityAttribute_Attributes::OscillationAngular() const
        {
            return Ent::Gen::ConditionalRigidityAttribute_RigidityParameter(node->at("OscillationAngular"));
        }
        inline Ent::Gen::ConditionalRigidityAttribute_RigidityParameter ConditionalRigidityAttribute_Attributes::OscillationLinear() const
        {
            return Ent::Gen::ConditionalRigidityAttribute_RigidityParameter(node->at("OscillationLinear"));
        }
        inline Ent::Gen::String ConditionalRigidityAttribute_Attributes::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ConditionalRigidityAttribute
        inline Ent::Gen::ConditionalRigidityAttribute_Attributes ConditionalRigidityAttribute::Attributes() const
        {
            return Ent::Gen::ConditionalRigidityAttribute_Attributes(node->at("Attributes"));
        }
        inline Ent::Gen::ConditionalRigidityAttribute_Conditions ConditionalRigidityAttribute::Conditions() const
        {
            return Ent::Gen::ConditionalRigidityAttribute_Conditions(node->at("Conditions"));
        }
        inline Ent::Gen::Bool ConditionalRigidityAttribute::Default() const
        {
            return Ent::Gen::Bool(node->at("Default"));
        }
        inline Ent::Gen::String ConditionalRigidityAttribute::Name() const
        {
            return Ent::Gen::String(node->at("Name"));
        }
        inline Ent::Gen::String ConditionalRigidityAttribute::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ComponentGD
        // WorldScalePathFindGD
        inline Ent::Gen::String WorldScalePathFindGD::FilePath() const
        {
            return Ent::Gen::String(node->at("FilePath"));
        }
        inline Array<Ent::Gen::NavmeshGenerationParameters> WorldScalePathFindGD::GenerationParameters() const
        {
            return Array<Ent::Gen::NavmeshGenerationParameters>(node->at("GenerationParameters"));
        }
        inline Ent::Gen::ComponentGD WorldScalePathFindGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String WorldScalePathFindGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // WildObject
        inline Ent::Gen::String WildObject::GdPath() const
        {
            return Ent::Gen::String(node->at("GdPath"));
        }
        inline Ent::Gen::String WildObject::ObjectType() const
        {
            return Ent::Gen::String(node->at("ObjectType"));
        }
        inline Ent::Gen::ComponentGD WildObject::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String WildObject::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // VoxelSimulationGD
        inline Ent::Gen::String VoxelSimulationGD::FilePath() const
        {
            return Ent::Gen::String(node->at("FilePath"));
        }
        inline Ent::Gen::Float VoxelSimulationGD::LossBySecond() const
        {
            return Ent::Gen::Float(node->at("LossBySecond"));
        }
        inline Ent::Gen::Float VoxelSimulationGD::LostRatio() const
        {
            return Ent::Gen::Float(node->at("LostRatio"));
        }
        inline Ent::Gen::ComponentGD VoxelSimulationGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Float VoxelSimulationGD::TransmissionBySecond() const
        {
            return Ent::Gen::Float(node->at("TransmissionBySecond"));
        }
        inline Ent::Gen::Float VoxelSimulationGD::TransmittedRatio() const
        {
            return Ent::Gen::Float(node->at("TransmittedRatio"));
        }
        inline Ent::Gen::String VoxelSimulationGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // VolumeConstraintGD
        inline Array<Ent::Gen::VolumeConstraintDataGD> VolumeConstraintGD::Constraints() const
        {
            return Array<Ent::Gen::VolumeConstraintDataGD>(node->at("Constraints"));
        }
        inline Ent::Gen::ComponentGD VolumeConstraintGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String VolumeConstraintGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // VisualGD
        inline Ent::Gen::Bool VisualGD::AlwaysStatic() const
        {
            return Ent::Gen::Bool(node->at("AlwaysStatic"));
        }
        inline Ent::Gen::Bool VisualGD::EDITOR_GenerateFur() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_GenerateFur"));
        }
        inline Array<Ent::Gen::EDITOR_LODsItem> VisualGD::EDITOR_LODs() const
        {
            return Array<Ent::Gen::EDITOR_LODsItem>(node->at("EDITOR_LODs"));
        }
        inline Ent::Gen::Float VisualGD::RUNTIME_LODScale() const
        {
            return Ent::Gen::Float(node->at("RUNTIME_LODScale"));
        }
        inline Array<Ent::Gen::RUNTIME_LODsItem> VisualGD::RUNTIME_LODs() const
        {
            return Array<Ent::Gen::RUNTIME_LODsItem>(node->at("RUNTIME_LODs"));
        }
        inline Ent::Gen::ComponentGD VisualGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String VisualGD::VisualResourcePath() const
        {
            return Ent::Gen::String(node->at("VisualResourcePath"));
        }
        inline Ent::Gen::String VisualGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // VelocityObstacleGD
        inline Ent::Gen::Float VelocityObstacleGD::AccelerationAfterAvoidance() const
        {
            return Ent::Gen::Float(node->at("AccelerationAfterAvoidance"));
        }
        inline Ent::Gen::Float VelocityObstacleGD::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::ComponentGD VelocityObstacleGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String VelocityObstacleGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // UnifiedPhysicsDataGD
        inline Ent::Gen::ComponentGD UnifiedPhysicsDataGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String UnifiedPhysicsDataGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TriggerEventCameraGD
        inline Ent::Gen::EventCameraData TriggerEventCameraGD::EventCameraData() const
        {
            return Ent::Gen::EventCameraData(node->at("EventCameraData"));
        }
        inline Ent::Gen::String TriggerEventCameraGD::PlayAnimBeforeTrigger() const
        {
            return Ent::Gen::String(node->at("PlayAnimBeforeTrigger"));
        }
        inline PrimArray<Ent::Gen::String> TriggerEventCameraGD::PlayAnimsWhenTriggered() const
        {
            return PrimArray<Ent::Gen::String>(node->at("PlayAnimsWhenTriggered"));
        }
        inline Ent::Gen::Float TriggerEventCameraGD::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::ComponentGD TriggerEventCameraGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Bool TriggerEventCameraGD::UseDuration() const
        {
            return Ent::Gen::Bool(node->at("UseDuration"));
        }
        inline Ent::Gen::Bool TriggerEventCameraGD::UsePhysics() const
        {
            return Ent::Gen::Bool(node->at("UsePhysics"));
        }
        inline Ent::Gen::Bool TriggerEventCameraGD::UseRadius() const
        {
            return Ent::Gen::Bool(node->at("UseRadius"));
        }
        inline Ent::Gen::String TriggerEventCameraGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TransformGD
        inline Ent::Gen::Bool TransformGD::EDITOR_InheritScaleFromSubSceneHolder() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_InheritScaleFromSubSceneHolder"));
        }
        inline Ent::Gen::Bool TransformGD::EDITOR_PropagateScaleToSubScene() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_PropagateScaleToSubScene"));
        }
        inline Ent::Gen::Matrix33 TransformGD::Matrix() const
        {
            return Ent::Gen::Matrix33(node->at("Matrix"));
        }
        inline Ent::Gen::Quat TransformGD::Orientation() const
        {
            return Ent::Gen::Quat(node->at("Orientation"));
        }
        inline Ent::Gen::Vector3 TransformGD::Position() const
        {
            return Ent::Gen::Vector3(node->at("Position"));
        }
        inline Ent::Gen::Vector3 TransformGD::Scale() const
        {
            return Ent::Gen::Vector3(node->at("Scale"));
        }
        inline Ent::Gen::ComponentGD TransformGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String TransformGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TestUnion
        inline Ent::Gen::ComponentGD TestUnion::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ TestUnion::Union() const
        {
            return Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(node->at("Union"));
        }
        inline Array<Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_> TestUnion::UnionArray() const
        {
            return Array<Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_>(node->at("UnionArray"));
        }
        inline Array<Ent::Gen::UnionObjectArrayItem> TestUnion::UnionObjectArray() const
        {
            return Array<Ent::Gen::UnionObjectArrayItem>(node->at("UnionObjectArray"));
        }
        inline Ent::Gen::String TestUnion::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TestSetOfObject
        inline Ent::Gen::Map<char const*, Ent::Gen::MapOfObjectItem_A> TestSetOfObject::MapOfObject() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::MapOfObjectItem_A>(node->at("MapOfObject"));
        }
        inline Ent::Gen::ObjectSet<char const*, Ent::Gen::SetOfObjectItem> TestSetOfObject::SetOfObject() const
        {
            return Ent::Gen::ObjectSet<char const*, Ent::Gen::SetOfObjectItem>(node->at("SetOfObject"));
        }
        inline Ent::Gen::ComponentGD TestSetOfObject::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String TestSetOfObject::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TestEntityRef
        inline Ent::Gen::ComponentGD TestEntityRef::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::EntityRef TestEntityRef::TestRef() const
        {
            return Ent::Gen::EntityRef(node->at("TestRef"));
        }
        inline Ent::Gen::String TestEntityRef::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TestDefaultValues
        inline Ent::Gen::Matrix33 TestDefaultValues::Matrix() const
        {
            return Ent::Gen::Matrix33(node->at("Matrix"));
        }
        inline Ent::Gen::Matrix33 TestDefaultValues::Matrix2() const
        {
            return Ent::Gen::Matrix33(node->at("Matrix2"));
        }
        inline Ent::Gen::ComponentGD TestDefaultValues::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String TestDefaultValues::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::TestPropertyDefaultValues2 TestDefaultValues::propertyWithDefault() const
        {
            return Ent::Gen::TestPropertyDefaultValues2(node->at("propertyWithDefault"));
        }
        // TestCreature
        inline Ent::Gen::EntityRef TestCreature::FullCursed() const
        {
            return Ent::Gen::EntityRef(node->at("FullCursed"));
        }
        inline Ent::Gen::EntityRef TestCreature::FullLush() const
        {
            return Ent::Gen::EntityRef(node->at("FullLush"));
        }
        inline Ent::Gen::EntityRef TestCreature::SklCursed() const
        {
            return Ent::Gen::EntityRef(node->at("SklCursed"));
        }
        inline Ent::Gen::EntityRef TestCreature::SklLush() const
        {
            return Ent::Gen::EntityRef(node->at("SklLush"));
        }
        inline Ent::Gen::EntityRef TestCreature::SklNeutral() const
        {
            return Ent::Gen::EntityRef(node->at("SklNeutral"));
        }
        inline Ent::Gen::ComponentGD TestCreature::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String TestCreature::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TestArrays
        inline PrimArray<Ent::Gen::Float> TestArrays::DefaultValue() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("DefaultValue"));
        }
        inline PrimArray<Ent::Gen::Float> TestArrays::OverridedDefaultValue() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("OverridedDefaultValue"));
        }
        inline PrimArray<Ent::Gen::Float> TestArrays::OverridedPrefabValue() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("OverridedPrefabValue"));
        }
        inline PrimArray<Ent::Gen::Float> TestArrays::PrefabValue() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("PrefabValue"));
        }
        inline Ent::Gen::ComponentGD TestArrays::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ TestArrays::Variant() const
        {
            return Ent::Gen::variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(node->at("Variant"));
        }
        inline Ent::Gen::String TestArrays::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TerrainSurfaceObject
        inline Ent::Gen::String TerrainSurfaceObject::EDITOR_tso() const
        {
            return Ent::Gen::String(node->at("EDITOR_tso"));
        }
        inline Ent::Gen::ComponentGD TerrainSurfaceObject::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String TerrainSurfaceObject::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TerrainGD
        inline Ent::Gen::Int TerrainGD::EDITOR_AlbedoType() const
        {
            return Ent::Gen::Int(node->at("EDITOR_AlbedoType"));
        }
        inline Ent::Gen::Float TerrainGD::EDITOR_CavityAlbedoStrength() const
        {
            return Ent::Gen::Float(node->at("EDITOR_CavityAlbedoStrength"));
        }
        inline Ent::Gen::Float TerrainGD::EDITOR_CavityStrength() const
        {
            return Ent::Gen::Float(node->at("EDITOR_CavityStrength"));
        }
        inline Ent::Gen::Float TerrainGD::EDITOR_CollisionDecimateHmm() const
        {
            return Ent::Gen::Float(node->at("EDITOR_CollisionDecimateHmm"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_ComputeSurfaceObjectTerrain() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_ComputeSurfaceObjectTerrain"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_DebugMode() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_DebugMode"));
        }
        inline Ent::Gen::Int TerrainGD::EDITOR_DetailMapFalloff() const
        {
            return Ent::Gen::Int(node->at("EDITOR_DetailMapFalloff"));
        }
        inline Ent::Gen::Float TerrainGD::EDITOR_DetailScale() const
        {
            return Ent::Gen::Float(node->at("EDITOR_DetailScale"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_DisableSeedParams() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_DisableSeedParams"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_DisplayAlbedo() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_DisplayAlbedo"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_DisplayFinal() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_DisplayFinal"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_Distributed() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_Distributed"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_Erosion() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_Erosion"));
        }
        inline Ent::Gen::Int TerrainGD::EDITOR_ErosionType() const
        {
            return Ent::Gen::Int(node->at("EDITOR_ErosionType"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_ExportCollision() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_ExportCollision"));
        }
        inline Ent::Gen::Int TerrainGD::EDITOR_ExportQuality() const
        {
            return Ent::Gen::Int(node->at("EDITOR_ExportQuality"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_LocalSndbs() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_LocalSndbs"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_MergeTSOPreview() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_MergeTSOPreview"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_MultiLayerHeightmap() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_MultiLayerHeightmap"));
        }
        inline Ent::Gen::String TerrainGD::EDITOR_Path() const
        {
            return Ent::Gen::String(node->at("EDITOR_Path"));
        }
        inline Ent::Gen::Int TerrainGD::EDITOR_PreviewQuality() const
        {
            return Ent::Gen::Int(node->at("EDITOR_PreviewQuality"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_ProcessDetailMap() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_ProcessDetailMap"));
        }
        inline Ent::Gen::Int TerrainGD::EDITOR_SeedTextureSizeReduce() const
        {
            return Ent::Gen::Int(node->at("EDITOR_SeedTextureSizeReduce"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_SuperimposeSeeds() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_SuperimposeSeeds"));
        }
        inline Ent::Gen::Float TerrainGD::EDITOR_SurfaceObjectDecimate() const
        {
            return Ent::Gen::Float(node->at("EDITOR_SurfaceObjectDecimate"));
        }
        inline Ent::Gen::Float TerrainGD::EDITOR_SurfaceObjectDecimateHmm() const
        {
            return Ent::Gen::Float(node->at("EDITOR_SurfaceObjectDecimateHmm"));
        }
        inline Ent::Gen::String TerrainGD::EDITOR_TerrainWildMat() const
        {
            return Ent::Gen::String(node->at("EDITOR_TerrainWildMat"));
        }
        inline Ent::Gen::Int TerrainGD::EDITOR_TriPerMeter() const
        {
            return Ent::Gen::Int(node->at("EDITOR_TriPerMeter"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_WMErosionComputeDistant() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_WMErosionComputeDistant"));
        }
        inline Ent::Gen::Bool TerrainGD::EDITOR_WMErosionPreview() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_WMErosionPreview"));
        }
        inline Ent::Gen::ComponentGD TerrainGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Terrain_TerrainMeta TerrainGD::TerrainMeta() const
        {
            return Ent::Gen::Terrain_TerrainMeta(node->at("TerrainMeta"));
        }
        inline Ent::Gen::String TerrainGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // TeamGD
        inline Ent::Gen::ComponentGD TeamGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String TeamGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SystemicCreature
        inline PrimArray<Ent::Gen::String> SystemicCreature::BehaviorModifierTagList() const
        {
            return PrimArray<Ent::Gen::String>(node->at("BehaviorModifierTagList"));
        }
        inline Ent::Gen::String SystemicCreature::BehaviorPath() const
        {
            return Ent::Gen::String(node->at("BehaviorPath"));
        }
        inline Ent::Gen::String SystemicCreature::BehaviorState() const
        {
            return Ent::Gen::String(node->at("BehaviorState"));
        }
        inline Ent::Gen::Bool SystemicCreature::Burried() const
        {
            return Ent::Gen::Bool(node->at("Burried"));
        }
        inline Ent::Gen::Bool SystemicCreature::CameraTarget() const
        {
            return Ent::Gen::Bool(node->at("CameraTarget"));
        }
        inline Ent::Gen::Bool SystemicCreature::CanBeMaster() const
        {
            return Ent::Gen::Bool(node->at("CanBeMaster"));
        }
        inline Ent::Gen::String SystemicCreature::Faction() const
        {
            return Ent::Gen::String(node->at("Faction"));
        }
        inline Ent::Gen::String SystemicCreature::Inventory() const
        {
            return Ent::Gen::String(node->at("Inventory"));
        }
        inline Ent::Gen::Bool SystemicCreature::Invincible() const
        {
            return Ent::Gen::Bool(node->at("Invincible"));
        }
        inline Ent::Gen::Float SystemicCreature::Life() const
        {
            return Ent::Gen::Float(node->at("Life"));
        }
        inline Ent::Gen::String SystemicCreature::Name() const
        {
            return Ent::Gen::String(node->at("Name"));
        }
        inline Ent::Gen::Bool SystemicCreature::PlayerSpawn() const
        {
            return Ent::Gen::Bool(node->at("PlayerSpawn"));
        }
        inline PrimArray<Ent::Gen::String> SystemicCreature::ScriptList() const
        {
            return PrimArray<Ent::Gen::String>(node->at("ScriptList"));
        }
        inline Ent::Gen::String SystemicCreature::Spawner() const
        {
            return Ent::Gen::String(node->at("Spawner"));
        }
        inline Ent::Gen::ComponentGD SystemicCreature::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SystemicCreature::UniqueID() const
        {
            return Ent::Gen::String(node->at("UniqueID"));
        }
        inline Ent::Gen::Bool SystemicCreature::Warrior() const
        {
            return Ent::Gen::Bool(node->at("Warrior"));
        }
        inline Ent::Gen::String SystemicCreature::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SubScene
        inline Ent::Gen::ObjectSet<char const*, Ent::Gen::Entity> SubScene::Embedded() const
        {
            return Ent::Gen::ObjectSet<char const*, Ent::Gen::Entity>(node->at("Embedded"));
        }
        inline Ent::Gen::String SubScene::File() const
        {
            return Ent::Gen::String(node->at("File"));
        }
        inline Ent::Gen::ComponentGD SubScene::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SubScene::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool SubScene::isEmbedded() const
        {
            return Ent::Gen::Bool(node->at("isEmbedded"));
        }
        // StickToTerrain
        inline Ent::Gen::Float StickToTerrain::NormalRatio() const
        {
            return Ent::Gen::Float(node->at("NormalRatio"));
        }
        inline Ent::Gen::ComponentGD StickToTerrain::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Float StickToTerrain::ZOffset() const
        {
            return Ent::Gen::Float(node->at("ZOffset"));
        }
        inline Ent::Gen::String StickToTerrain::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float StickToTerrain::precisionRadius() const
        {
            return Ent::Gen::Float(node->at("precisionRadius"));
        }
        inline Ent::Gen::Bool StickToTerrain::useNormal() const
        {
            return Ent::Gen::Bool(node->at("useNormal"));
        }
        // StaticObjectGD
        inline Ent::Gen::Bool StaticObjectGD::EDITOR_IsCave() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_IsCave"));
        }
        inline Ent::Gen::Bool StaticObjectGD::EDITOR_UsedInMultiLayerHeightmap() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_UsedInMultiLayerHeightmap"));
        }
        inline Ent::Gen::ComponentGD StaticObjectGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Bool StaticObjectGD::Visual() const
        {
            return Ent::Gen::Bool(node->at("Visual"));
        }
        inline Ent::Gen::String StaticObjectGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // StaffVertebrasGD
        inline PrimArray<Ent::Gen::String> StaffVertebrasGD::HotspotNames() const
        {
            return PrimArray<Ent::Gen::String>(node->at("HotspotNames"));
        }
        inline Ent::Gen::Int StaffVertebrasGD::MaxVertebraCount() const
        {
            return Ent::Gen::Int(node->at("MaxVertebraCount"));
        }
        inline Ent::Gen::Int StaffVertebrasGD::OwnedVertebraStartCount() const
        {
            return Ent::Gen::Int(node->at("OwnedVertebraStartCount"));
        }
        inline Ent::Gen::ComponentGD StaffVertebrasGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String StaffVertebrasGD::VertebraGRCPath1() const
        {
            return Ent::Gen::String(node->at("VertebraGRCPath1"));
        }
        inline Ent::Gen::String StaffVertebrasGD::VertebraGRCPath2() const
        {
            return Ent::Gen::String(node->at("VertebraGRCPath2"));
        }
        inline Ent::Gen::String StaffVertebrasGD::VertebraGRCPath3() const
        {
            return Ent::Gen::String(node->at("VertebraGRCPath3"));
        }
        inline Ent::Gen::String StaffVertebrasGD::VertebraGRCPath4() const
        {
            return Ent::Gen::String(node->at("VertebraGRCPath4"));
        }
        inline Ent::Gen::VomitData StaffVertebrasGD::VomitData() const
        {
            return Ent::Gen::VomitData(node->at("VomitData"));
        }
        inline Ent::Gen::String StaffVertebrasGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SoundEmitterGD
        inline Ent::Gen::Float SoundEmitterGD::ActivationDistance() const
        {
            return Ent::Gen::Float(node->at("ActivationDistance"));
        }
        inline PrimArray<Ent::Gen::String> SoundEmitterGD::ActivationSound() const
        {
            return PrimArray<Ent::Gen::String>(node->at("ActivationSound"));
        }
        inline Ent::Gen::SyncTempoMode SoundEmitterGD::ActivationSync() const
        {
            return Ent::Gen::SyncTempoMode(node->at("ActivationSync"));
        }
        inline Ent::Gen::String SoundEmitterGD::AuxSend() const
        {
            return Ent::Gen::String(node->at("AuxSend"));
        }
        inline PrimArray<Ent::Gen::String> SoundEmitterGD::Bank() const
        {
            return PrimArray<Ent::Gen::String>(node->at("Bank"));
        }
        inline Ent::Gen::Float SoundEmitterGD::BoidRadius() const
        {
            return Ent::Gen::Float(node->at("BoidRadius"));
        }
        inline Ent::Gen::Float SoundEmitterGD::BoidRadiusToInnerEdgeRatio() const
        {
            return Ent::Gen::Float(node->at("BoidRadiusToInnerEdgeRatio"));
        }
        inline Ent::Gen::Float SoundEmitterGD::BoidRadiusToOuterEdgeRatio() const
        {
            return Ent::Gen::Float(node->at("BoidRadiusToOuterEdgeRatio"));
        }
        inline Ent::Gen::Bool SoundEmitterGD::BoidRealPositionComputation() const
        {
            return Ent::Gen::Bool(node->at("BoidRealPositionComputation"));
        }
        inline Ent::Gen::String SoundEmitterGD::CreatureType() const
        {
            return Ent::Gen::String(node->at("CreatureType"));
        }
        inline Ent::Gen::Bool SoundEmitterGD::Echoes() const
        {
            return Ent::Gen::Bool(node->at("Echoes"));
        }
        inline Ent::Gen::Float SoundEmitterGD::EchoesSend() const
        {
            return Ent::Gen::Float(node->at("EchoesSend"));
        }
        inline Ent::Gen::Float SoundEmitterGD::EventDistance() const
        {
            return Ent::Gen::Float(node->at("EventDistance"));
        }
        inline Ent::Gen::SoundEventMapping SoundEmitterGD::EventMapping() const
        {
            return Ent::Gen::SoundEventMapping(node->at("EventMapping"));
        }
        inline Ent::Gen::Map<char const*, Ent::Gen::String> SoundEmitterGD::ExplicitEventMapping() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::String>(node->at("ExplicitEventMapping"));
        }
        inline PrimArray<Ent::Gen::String> SoundEmitterGD::InEvents() const
        {
            return PrimArray<Ent::Gen::String>(node->at("InEvents"));
        }
        inline PrimArray<Ent::Gen::String> SoundEmitterGD::OutEvents() const
        {
            return PrimArray<Ent::Gen::String>(node->at("OutEvents"));
        }
        inline Ent::Gen::ComponentGD SoundEmitterGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline PrimArray<Ent::Gen::String> SoundEmitterGD::UnactivationSound() const
        {
            return PrimArray<Ent::Gen::String>(node->at("UnactivationSound"));
        }
        inline Ent::Gen::SyncTempoMode SoundEmitterGD::UnactivationSync() const
        {
            return Ent::Gen::SyncTempoMode(node->at("UnactivationSync"));
        }
        inline Ent::Gen::String SoundEmitterGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool SoundEmitterGD::dopplerActivated() const
        {
            return Ent::Gen::Bool(node->at("dopplerActivated"));
        }
        inline Ent::Gen::Int SoundEmitterGD::relativeHeightPriority() const
        {
            return Ent::Gen::Int(node->at("relativeHeightPriority"));
        }
        inline Ent::Gen::Bool SoundEmitterGD::sendSoundAreaEvents() const
        {
            return Ent::Gen::Bool(node->at("sendSoundAreaEvents"));
        }
        inline Ent::Gen::Float SoundEmitterGD::waterDeepAltitude() const
        {
            return Ent::Gen::Float(node->at("waterDeepAltitude"));
        }
        inline Ent::Gen::Float SoundEmitterGD::waterPuddleAltitude() const
        {
            return Ent::Gen::Float(node->at("waterPuddleAltitude"));
        }
        // SoundAreaGD
        inline Ent::Gen::String SoundAreaGD::EventEnter() const
        {
            return Ent::Gen::String(node->at("EventEnter"));
        }
        inline Ent::Gen::String SoundAreaGD::EventExit() const
        {
            return Ent::Gen::String(node->at("EventExit"));
        }
        inline Ent::Gen::ComponentGD SoundAreaGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SoundAreaGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SoulSpotGD
        inline Ent::Gen::ComponentGD SoulSpotGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline PrimArray<Ent::Gen::String> SoulSpotGD::Tags() const
        {
            return PrimArray<Ent::Gen::String>(node->at("Tags"));
        }
        inline Ent::Gen::String SoulSpotGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SoulRespawnOpportunityGD
        inline Ent::Gen::ReviveSide SoulRespawnOpportunityGD::ForceReviveSide() const
        {
            return Ent::Gen::ReviveSide(node->at("ForceReviveSide"));
        }
        inline Ent::Gen::Int SoulRespawnOpportunityGD::MaxDensityCount() const
        {
            return Ent::Gen::Int(node->at("MaxDensityCount"));
        }
        inline Ent::Gen::Float SoulRespawnOpportunityGD::MaxDensityRadius() const
        {
            return Ent::Gen::Float(node->at("MaxDensityRadius"));
        }
        inline Ent::Gen::Vector3 SoulRespawnOpportunityGD::Offset() const
        {
            return Ent::Gen::Vector3(node->at("Offset"));
        }
        inline Ent::Gen::Int SoulRespawnOpportunityGD::SlotCount() const
        {
            return Ent::Gen::Int(node->at("SlotCount"));
        }
        inline Ent::Gen::Specie SoulRespawnOpportunityGD::Specie() const
        {
            return Ent::Gen::Specie(node->at("Specie"));
        }
        inline Ent::Gen::ComponentGD SoulRespawnOpportunityGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SoulRespawnOpportunityGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SmoothScaleComponentGD
        inline Ent::Gen::ComponentGD SmoothScaleComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SmoothScaleComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SmallActorSpawnerGD
        inline Ent::Gen::ComponentGD SmallActorSpawnerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SmallActorSpawnerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SmallActorGD
        inline Ent::Gen::ComponentGD SmallActorGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SmallActorGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SideMapGateGD
        inline Ent::Gen::String SideMapGateGD::SideMapName() const
        {
            return Ent::Gen::String(node->at("SideMapName"));
        }
        inline Ent::Gen::ComponentGD SideMapGateGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SideMapGateGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ShapeshiftStatueGD
        inline Ent::Gen::EntityRef ShapeshiftStatueGD::AssociatedEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("AssociatedEntityRef"));
        }
        inline Ent::Gen::ComponentGD ShapeshiftStatueGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ShapeshiftStatueGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ShamanVisionGD
        inline Ent::Gen::ComponentGD ShamanVisionGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ShamanVisionGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ShamanItemGD
        inline PrimArray<Ent::Gen::String> ShamanItemGD::BoneNames() const
        {
            return PrimArray<Ent::Gen::String>(node->at("BoneNames"));
        }
        inline Ent::Gen::EntityRef ShamanItemGD::OppositeItemEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("OppositeItemEntityRef"));
        }
        inline Ent::Gen::ReviveSide ShamanItemGD::ReviveSide() const
        {
            return Ent::Gen::ReviveSide(node->at("ReviveSide"));
        }
        inline Ent::Gen::Int ShamanItemGD::StartPartCount() const
        {
            return Ent::Gen::Int(node->at("StartPartCount"));
        }
        inline Ent::Gen::ComponentGD ShamanItemGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ShamanItemGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SensorControllerGD
        inline Ent::Gen::ComponentGD SensorControllerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SensorControllerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SeedPatch
        inline Ent::Gen::Bool SeedPatch::AddVertexColor() const
        {
            return Ent::Gen::Bool(node->at("AddVertexColor"));
        }
        inline Ent::Gen::Matrix33 SeedPatch::LocalMatrix() const
        {
            return Ent::Gen::Matrix33(node->at("LocalMatrix"));
        }
        inline Ent::Gen::String SeedPatch::MeshFile() const
        {
            return Ent::Gen::String(node->at("MeshFile"));
        }
        inline Ent::Gen::String SeedPatch::NoiseName() const
        {
            return Ent::Gen::String(node->at("NoiseName"));
        }
        inline Ent::Gen::Float SeedPatch::NoiseOffsetX() const
        {
            return Ent::Gen::Float(node->at("NoiseOffsetX"));
        }
        inline Ent::Gen::Float SeedPatch::NoiseOffsetY() const
        {
            return Ent::Gen::Float(node->at("NoiseOffsetY"));
        }
        inline Ent::Gen::Float SeedPatch::NoiseSizeX() const
        {
            return Ent::Gen::Float(node->at("NoiseSizeX"));
        }
        inline Ent::Gen::Float SeedPatch::NoiseSizeY() const
        {
            return Ent::Gen::Float(node->at("NoiseSizeY"));
        }
        inline Ent::Gen::String SeedPatch::SeedName() const
        {
            return Ent::Gen::String(node->at("SeedName"));
        }
        inline Ent::Gen::Bool SeedPatch::SeedOverride() const
        {
            return Ent::Gen::Bool(node->at("SeedOverride"));
        }
        inline Ent::Gen::SeedPatchDataList SeedPatch::SeedPatchDataList() const
        {
            return Ent::Gen::SeedPatchDataList(node->at("SeedPatchDataList"));
        }
        inline Ent::Gen::Int SeedPatch::Subdivision() const
        {
            return Ent::Gen::Int(node->at("Subdivision"));
        }
        inline Ent::Gen::ComponentGD SeedPatch::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String SeedPatch::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ScriptComponentGD
        inline Ent::Gen::Map<char const*, Ent::Gen::TypedValue> ScriptComponentGD::CommonDataMap() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::TypedValue>(node->at("CommonDataMap"));
        }
        inline Ent::Gen::Map<char const*, Ent::Gen::ScriptPathAndDataSet> ScriptComponentGD::ScriptsMap() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::ScriptPathAndDataSet>(node->at("ScriptsMap"));
        }
        inline Ent::Gen::ComponentGD ScriptComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ScriptComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ReviveSideSwitcherGD
        inline Ent::Gen::EntityRef ReviveSideSwitcherGD::ReviveEnergyEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("ReviveEnergyEntityRef"));
        }
        inline Ent::Gen::Map<ReviveSideEnum, Ent::Gen::ReviveSideData> ReviveSideSwitcherGD::ReviveSideData() const
        {
            return Ent::Gen::Map<ReviveSideEnum, Ent::Gen::ReviveSideData>(node->at("ReviveSideData"));
        }
        inline Ent::Gen::ComponentGD ReviveSideSwitcherGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ReviveSideSwitcherGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ReviveEnergyGD
        inline Ent::Gen::Float ReviveEnergyGD::EnergyMinNeutral() const
        {
            return Ent::Gen::Float(node->at("EnergyMinNeutral"));
        }
        inline Ent::Gen::Float ReviveEnergyGD::HatchingEnergyMinHysteresis() const
        {
            return Ent::Gen::Float(node->at("HatchingEnergyMinHysteresis"));
        }
        inline Ent::Gen::Float ReviveEnergyGD::HatchingFightBackSpeedModifier() const
        {
            return Ent::Gen::Float(node->at("HatchingFightBackSpeedModifier"));
        }
        inline Ent::Gen::Float ReviveEnergyGD::HatchingMaxDuration() const
        {
            return Ent::Gen::Float(node->at("HatchingMaxDuration"));
        }
        inline Ent::Gen::Float ReviveEnergyGD::HatchingMinDuration() const
        {
            return Ent::Gen::Float(node->at("HatchingMinDuration"));
        }
        inline Ent::Gen::Float ReviveEnergyGD::InitEnergy() const
        {
            return Ent::Gen::Float(node->at("InitEnergy"));
        }
        inline Ent::Gen::ReviveSide ReviveEnergyGD::InitReviveSide() const
        {
            return Ent::Gen::ReviveSide(node->at("InitReviveSide"));
        }
        inline Ent::Gen::Float ReviveEnergyGD::MaxEnergy() const
        {
            return Ent::Gen::Float(node->at("MaxEnergy"));
        }
        inline Ent::Gen::Float ReviveEnergyGD::MaxWaitingTime() const
        {
            return Ent::Gen::Float(node->at("MaxWaitingTime"));
        }
        inline Ent::Gen::ComponentGD ReviveEnergyGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ReviveEnergyGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // RespawnPlaceGD
        inline Ent::Gen::Bool RespawnPlaceGD::AlwaysAvailable() const
        {
            return Ent::Gen::Bool(node->at("AlwaysAvailable"));
        }
        inline Ent::Gen::ComponentGD RespawnPlaceGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String RespawnPlaceGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // RegenerableVegetationGD
        inline Ent::Gen::String RegenerableVegetationGD::PCloudPath() const
        {
            return Ent::Gen::String(node->at("PCloudPath"));
        }
        inline Ent::Gen::FloatRange RegenerableVegetationGD::RegenRange() const
        {
            return Ent::Gen::FloatRange(node->at("RegenRange"));
        }
        inline Ent::Gen::ComponentGD RegenerableVegetationGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline PrimArray<Ent::Gen::String> RegenerableVegetationGD::UsedVegetations() const
        {
            return PrimArray<Ent::Gen::String>(node->at("UsedVegetations"));
        }
        inline Array<Ent::Gen::VegetationPCloudData> RegenerableVegetationGD::VegetationPClouds() const
        {
            return Array<Ent::Gen::VegetationPCloudData>(node->at("VegetationPClouds"));
        }
        inline Ent::Gen::String RegenerableVegetationGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // RegenSwitcherGD
        inline Ent::Gen::Bool RegenSwitcherGD::ParentTransforms() const
        {
            return Ent::Gen::Bool(node->at("ParentTransforms"));
        }
        inline Array<Ent::Gen::RegenData> RegenSwitcherGD::RegenData() const
        {
            return Array<Ent::Gen::RegenData>(node->at("RegenData"));
        }
        inline Ent::Gen::RegenSwitchBehavior RegenSwitcherGD::RegenSwitchBehavior() const
        {
            return Ent::Gen::RegenSwitchBehavior(node->at("RegenSwitchBehavior"));
        }
        inline Ent::Gen::ComponentGD RegenSwitcherGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String RegenSwitcherGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // RegenMeshGD
        inline Ent::Gen::String RegenMeshGD::FilePath() const
        {
            return Ent::Gen::String(node->at("FilePath"));
        }
        inline Ent::Gen::Float RegenMeshGD::FrontierHeightDetection() const
        {
            return Ent::Gen::Float(node->at("FrontierHeightDetection"));
        }
        inline Ent::Gen::Float RegenMeshGD::FrontierTolerance() const
        {
            return Ent::Gen::Float(node->at("FrontierTolerance"));
        }
        inline Ent::Gen::Float RegenMeshGD::LossBySecond() const
        {
            return Ent::Gen::Float(node->at("LossBySecond"));
        }
        inline Ent::Gen::Float RegenMeshGD::LostRatio() const
        {
            return Ent::Gen::Float(node->at("LostRatio"));
        }
        inline Ent::Gen::ComponentGD RegenMeshGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Float RegenMeshGD::TransmissionPerSecond() const
        {
            return Ent::Gen::Float(node->at("TransmissionPerSecond"));
        }
        inline Ent::Gen::Float RegenMeshGD::TransmissionRatio() const
        {
            return Ent::Gen::Float(node->at("TransmissionRatio"));
        }
        inline Ent::Gen::String RegenMeshGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // RegenFXGD
        inline Ent::Gen::ComponentGD RegenFXGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String RegenFXGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // RagdollGD
        inline Ent::Gen::String RagdollGD::RagdollType() const
        {
            return Ent::Gen::String(node->at("RagdollType"));
        }
        inline Ent::Gen::ComponentGD RagdollGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String RagdollGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // QuickCreatureSwitchGD
        inline PrimArray<Ent::Gen::EntityRef> QuickCreatureSwitchGD::CreatureEntityRefs() const
        {
            return PrimArray<Ent::Gen::EntityRef>(node->at("CreatureEntityRefs"));
        }
        inline Ent::Gen::ComponentGD QuickCreatureSwitchGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String QuickCreatureSwitchGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ProtoComponentGD
        inline Ent::Gen::ComponentGD ProtoComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ProtoComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ProjectileShooterGD
        inline Ent::Gen::Map<char const*, Ent::Gen::ProjectileShooterData> ProjectileShooterGD::ProjectileShooterData() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::ProjectileShooterData>(node->at("ProjectileShooterData"));
        }
        inline Ent::Gen::ComponentGD ProjectileShooterGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ProjectileShooterGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PossessableGPEGD
        inline Ent::Gen::String PossessableGPEGD::GPEActorStateName() const
        {
            return Ent::Gen::String(node->at("GPEActorStateName"));
        }
        inline Ent::Gen::GPEType PossessableGPEGD::GPEType() const
        {
            return Ent::Gen::GPEType(node->at("GPEType"));
        }
        inline Ent::Gen::String PossessableGPEGD::HotspotName() const
        {
            return Ent::Gen::String(node->at("HotspotName"));
        }
        inline Ent::Gen::ComponentGD PossessableGPEGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PossessableGPEGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PlayerComponentGD
        inline Ent::Gen::ComponentGD PlayerComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PlayerComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PickableDistributorComponentGD
        inline Ent::Gen::Float PickableDistributorComponentGD::PickableGrowingTime() const
        {
            return Ent::Gen::Float(node->at("PickableGrowingTime"));
        }
        inline Ent::Gen::Float PickableDistributorComponentGD::PickablePickedUpCooldownTime() const
        {
            return Ent::Gen::Float(node->at("PickablePickedUpCooldownTime"));
        }
        inline Array<Ent::Gen::PickableDistributorComponentData> PickableDistributorComponentGD::PickablesList() const
        {
            return Array<Ent::Gen::PickableDistributorComponentData>(node->at("PickablesList"));
        }
        inline Ent::Gen::ComponentGD PickableDistributorComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PickableDistributorComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PickableComponentGD
        inline Array<Ent::Gen::ResponsiblePointer_ActorState_> PickableComponentGD::StatesForPicker() const
        {
            return Array<Ent::Gen::ResponsiblePointer_ActorState_>(node->at("StatesForPicker"));
        }
        inline Ent::Gen::ComponentGD PickableComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PickableComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PhysicsTriggerGD
        inline PrimArray<Ent::Gen::String> PhysicsTriggerGD::RequiredComponents() const
        {
            return PrimArray<Ent::Gen::String>(node->at("RequiredComponents"));
        }
        inline Ent::Gen::ComponentGD PhysicsTriggerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PhysicsTriggerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PhysicsMeshProviderGD
        inline Ent::Gen::Bool PhysicsMeshProviderGD::EdgeTransitionConstraintAllowed() const
        {
            return Ent::Gen::Bool(node->at("EdgeTransitionConstraintAllowed"));
        }
        inline Ent::Gen::ComponentGD PhysicsMeshProviderGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PhysicsMeshProviderGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PhysicsMeshDeformerGD
        inline Ent::Gen::ComponentGD PhysicsMeshDeformerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PhysicsMeshDeformerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PhysicsGD
        inline Ent::Gen::Bool PhysicsGD::AffectByHit() const
        {
            return Ent::Gen::Bool(node->at("AffectByHit"));
        }
        inline Ent::Gen::Float PhysicsGD::AngularDamping() const
        {
            return Ent::Gen::Float(node->at("AngularDamping"));
        }
        inline Ent::Gen::Vector3 PhysicsGD::AxisRestriction() const
        {
            return Ent::Gen::Vector3(node->at("AxisRestriction"));
        }
        inline Ent::Gen::Bool PhysicsGD::CameraIgnored() const
        {
            return Ent::Gen::Bool(node->at("CameraIgnored"));
        }
        inline Ent::Gen::Bool PhysicsGD::Ccd() const
        {
            return Ent::Gen::Bool(node->at("Ccd"));
        }
        inline PrimArray<Ent::Gen::String> PhysicsGD::EDITOR_MeshColliders() const
        {
            return PrimArray<Ent::Gen::String>(node->at("EDITOR_MeshColliders"));
        }
        inline Ent::Gen::String PhysicsGD::EDITOR_MeshEdges() const
        {
            return Ent::Gen::String(node->at("EDITOR_MeshEdges"));
        }
        inline Ent::Gen::String PhysicsGD::EDITOR_NavMeshStamper() const
        {
            return Ent::Gen::String(node->at("EDITOR_NavMeshStamper"));
        }
        inline Ent::Gen::Float PhysicsGD::EnergyLoss() const
        {
            return Ent::Gen::Float(node->at("EnergyLoss"));
        }
        inline Ent::Gen::Float PhysicsGD::Friction() const
        {
            return Ent::Gen::Float(node->at("Friction"));
        }
        inline Ent::Gen::Bool PhysicsGD::HasGravity() const
        {
            return Ent::Gen::Bool(node->at("HasGravity"));
        }
        inline Ent::Gen::Float PhysicsGD::LinearDamping() const
        {
            return Ent::Gen::Float(node->at("LinearDamping"));
        }
        inline Ent::Gen::Float PhysicsGD::Mass() const
        {
            return Ent::Gen::Float(node->at("Mass"));
        }
        inline PrimArray<Ent::Gen::String> PhysicsGD::MeshColliders() const
        {
            return PrimArray<Ent::Gen::String>(node->at("MeshColliders"));
        }
        inline Ent::Gen::String PhysicsGD::MeshEdges() const
        {
            return Ent::Gen::String(node->at("MeshEdges"));
        }
        inline Ent::Gen::String PhysicsGD::MotionType() const
        {
            return Ent::Gen::String(node->at("MotionType"));
        }
        inline Ent::Gen::String PhysicsGD::NavMeshStamper() const
        {
            return Ent::Gen::String(node->at("NavMeshStamper"));
        }
        inline Ent::Gen::Vector3 PhysicsGD::Offset() const
        {
            return Ent::Gen::Vector3(node->at("Offset"));
        }
        inline Ent::Gen::Vector3 PhysicsGD::OffsetRotation() const
        {
            return Ent::Gen::Vector3(node->at("OffsetRotation"));
        }
        inline Ent::Gen::String PhysicsGD::PhysicsMaterial() const
        {
            return Ent::Gen::String(node->at("PhysicsMaterial"));
        }
        inline Ent::Gen::PrimitiveColliderType PhysicsGD::PrimitiveCollider() const
        {
            return Ent::Gen::PrimitiveColliderType(node->at("PrimitiveCollider"));
        }
        inline PrimArray<Ent::Gen::Size> PhysicsGD::PrimitiveColliderSizeLayerMask() const
        {
            return PrimArray<Ent::Gen::Size>(node->at("PrimitiveColliderSizeLayerMask"));
        }
        inline Ent::Gen::Float PhysicsGD::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::Float PhysicsGD::Restitution() const
        {
            return Ent::Gen::Float(node->at("Restitution"));
        }
        inline PrimArray<Ent::Gen::PhysicsLayer> PhysicsGD::SelfFilter() const
        {
            return PrimArray<Ent::Gen::PhysicsLayer>(node->at("SelfFilter"));
        }
        inline Ent::Gen::Vector3 PhysicsGD::Size() const
        {
            return Ent::Gen::Vector3(node->at("Size"));
        }
        inline Ent::Gen::Bool PhysicsGD::Sleep() const
        {
            return Ent::Gen::Bool(node->at("Sleep"));
        }
        inline Ent::Gen::ComponentGD PhysicsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline PrimArray<Ent::Gen::PhysicsLayer> PhysicsGD::TargetFilter() const
        {
            return PrimArray<Ent::Gen::PhysicsLayer>(node->at("TargetFilter"));
        }
        inline Ent::Gen::Bool PhysicsGD::Walkable() const
        {
            return Ent::Gen::Bool(node->at("Walkable"));
        }
        inline Ent::Gen::String PhysicsGD::WalkableSoundSwitch() const
        {
            return Ent::Gen::String(node->at("WalkableSoundSwitch"));
        }
        inline Ent::Gen::String PhysicsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PhysicsDataGD
        inline Array<Ent::Gen::EDITOR_Mesh> PhysicsDataGD::EDITOR_Shapes() const
        {
            return Array<Ent::Gen::EDITOR_Mesh>(node->at("EDITOR_Shapes"));
        }
        inline Ent::Gen::Bool PhysicsDataGD::EDITOR_isTrigger() const
        {
            return Ent::Gen::Bool(node->at("EDITOR_isTrigger"));
        }
        inline Ent::Gen::ComponentGD PhysicsDataGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PhysicsDataGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Array<Ent::Gen::sPhysicsJointDesc> PhysicsDataGD::joints() const
        {
            return Array<Ent::Gen::sPhysicsJointDesc>(node->at("joints"));
        }
        inline Array<Ent::Gen::sRigidBodyDesc> PhysicsDataGD::rigidBodies() const
        {
            return Array<Ent::Gen::sRigidBodyDesc>(node->at("rigidBodies"));
        }
        // PerceiverGD
        inline Ent::Gen::ComponentGD PerceiverGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PerceiverGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float PerceiverGD::m_coneAngle() const
        {
            return Ent::Gen::Float(node->at("m_coneAngle"));
        }
        inline Ent::Gen::Float PerceiverGD::m_farSoundDistance() const
        {
            return Ent::Gen::Float(node->at("m_farSoundDistance"));
        }
        inline Ent::Gen::Float PerceiverGD::m_longRangeDistance() const
        {
            return Ent::Gen::Float(node->at("m_longRangeDistance"));
        }
        inline Ent::Gen::Float PerceiverGD::m_lowRangeDistance() const
        {
            return Ent::Gen::Float(node->at("m_lowRangeDistance"));
        }
        inline Ent::Gen::Float PerceiverGD::m_middleRangeDistance() const
        {
            return Ent::Gen::Float(node->at("m_middleRangeDistance"));
        }
        inline Ent::Gen::Float PerceiverGD::m_middleSoundDistance() const
        {
            return Ent::Gen::Float(node->at("m_middleSoundDistance"));
        }
        inline Ent::Gen::Float PerceiverGD::m_nearSoundDistance() const
        {
            return Ent::Gen::Float(node->at("m_nearSoundDistance"));
        }
        inline Ent::Gen::Float PerceiverGD::m_perceptionHeightMultiplier() const
        {
            return Ent::Gen::Float(node->at("m_perceptionHeightMultiplier"));
        }
        inline Ent::Gen::Float PerceiverGD::m_perceptionHeightMultiplierHeightMax() const
        {
            return Ent::Gen::Float(node->at("m_perceptionHeightMultiplierHeightMax"));
        }
        inline Ent::Gen::Bool PerceiverGD::m_rayCastCheck() const
        {
            return Ent::Gen::Bool(node->at("m_rayCastCheck"));
        }
        // PerceivableGD
        inline Ent::Gen::ComponentGD PerceivableGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PerceivableGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float PerceivableGD::m_perceivedDistanceMultiplier() const
        {
            return Ent::Gen::Float(node->at("m_perceivedDistanceMultiplier"));
        }
        inline Ent::Gen::SoundEmissionStrength PerceivableGD::m_soundCrouch() const
        {
            return Ent::Gen::SoundEmissionStrength(node->at("m_soundCrouch"));
        }
        inline Ent::Gen::SoundEmissionStrength PerceivableGD::m_soundImmobile() const
        {
            return Ent::Gen::SoundEmissionStrength(node->at("m_soundImmobile"));
        }
        inline Ent::Gen::SoundEmissionStrength PerceivableGD::m_soundRun() const
        {
            return Ent::Gen::SoundEmissionStrength(node->at("m_soundRun"));
        }
        inline Ent::Gen::SoundEmissionStrength PerceivableGD::m_soundWalk() const
        {
            return Ent::Gen::SoundEmissionStrength(node->at("m_soundWalk"));
        }
        inline PrimArray<Ent::Gen::String> PerceivableGD::m_tags() const
        {
            return PrimArray<Ent::Gen::String>(node->at("m_tags"));
        }
        // PathNodeGD
        inline Ent::Gen::Float PathNodeGD::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::ComponentGD PathNodeGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::TagsList PathNodeGD::Tags() const
        {
            return Ent::Gen::TagsList(node->at("Tags"));
        }
        inline Ent::Gen::String PathNodeGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PathMotionControllerGD
        inline Ent::Gen::ComponentGD PathMotionControllerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PathMotionControllerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PathGD
        inline Ent::Gen::String PathGD::FilePath() const
        {
            return Ent::Gen::String(node->at("FilePath"));
        }
        inline Ent::Gen::ComponentGD PathGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PathGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PathBoneRigidBodyGD
        inline Ent::Gen::ComponentGD PathBoneRigidBodyGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PathBoneRigidBodyGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PathBoneInfluenceGD
        inline Array<Ent::Gen::sNodeBoneInfluenceDataTemplate> PathBoneInfluenceGD::Data() const
        {
            return Array<Ent::Gen::sNodeBoneInfluenceDataTemplate>(node->at("Data"));
        }
        inline Ent::Gen::ComponentGD PathBoneInfluenceGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PathBoneInfluenceGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // PathBoneAnimGD
        inline Ent::Gen::ComponentGD PathBoneAnimGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String PathBoneAnimGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // OutfitWearerGD
        inline Ent::Gen::EntityRef OutfitWearerGD::InventoryEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("InventoryEntityRef"));
        }
        inline Ent::Gen::Float OutfitWearerGD::OutfitFadeDelay() const
        {
            return Ent::Gen::Float(node->at("OutfitFadeDelay"));
        }
        inline Ent::Gen::Float OutfitWearerGD::OutfitFadeDuration() const
        {
            return Ent::Gen::Float(node->at("OutfitFadeDuration"));
        }
        inline Ent::Gen::ComponentGD OutfitWearerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String OutfitWearerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // OutfitGD
        inline Array<Ent::Gen::MountableSnapLine_ControlPoint> OutfitGD::SnapLine() const
        {
            return Array<Ent::Gen::MountableSnapLine_ControlPoint>(node->at("SnapLine"));
        }
        inline Ent::Gen::SoundEventMapping OutfitGD::SoundEventMappingRules() const
        {
            return Ent::Gen::SoundEventMapping(node->at("SoundEventMappingRules"));
        }
        inline Ent::Gen::ComponentGD OutfitGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String OutfitGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Array<Ent::Gen::OutfitPiece> OutfitGD::clothes() const
        {
            return Array<Ent::Gen::OutfitPiece>(node->at("clothes"));
        }
        inline Ent::Gen::String OutfitGD::faction() const
        {
            return Ent::Gen::String(node->at("faction"));
        }
        inline Ent::Gen::String OutfitGD::overrideSpeciesAudioCategory() const
        {
            return Ent::Gen::String(node->at("overrideSpeciesAudioCategory"));
        }
        inline PrimArray<Ent::Gen::String> OutfitGD::soundBank() const
        {
            return PrimArray<Ent::Gen::String>(node->at("soundBank"));
        }
        inline Ent::Gen::String OutfitGD::soundTag() const
        {
            return Ent::Gen::String(node->at("soundTag"));
        }
        inline Ent::Gen::StyleMode OutfitGD::specialOutfitStyle() const
        {
            return Ent::Gen::StyleMode(node->at("specialOutfitStyle"));
        }
        inline Ent::Gen::Bool OutfitGD::spirit() const
        {
            return Ent::Gen::Bool(node->at("spirit"));
        }
        // NotVisibleInSubscene
        inline Ent::Gen::ComponentGD NotVisibleInSubscene::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String NotVisibleInSubscene::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // NetworkNode
        inline Ent::Gen::ComponentGD NetworkNode::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String NetworkNode::Tag() const
        {
            return Ent::Gen::String(node->at("Tag"));
        }
        inline Ent::Gen::String NetworkNode::ThumbnailMesh() const
        {
            return Ent::Gen::String(node->at("ThumbnailMesh"));
        }
        inline Ent::Gen::String NetworkNode::Type_() const
        {
            return Ent::Gen::String(node->at("Type_"));
        }
        inline Ent::Gen::String NetworkNode::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // NetworkLink
        inline Ent::Gen::String NetworkLink::Source() const
        {
            return Ent::Gen::String(node->at("Source"));
        }
        inline Ent::Gen::EntityRef NetworkLink::SourceEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("SourceEntityRef"));
        }
        inline Ent::Gen::ComponentGD NetworkLink::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String NetworkLink::Target() const
        {
            return Ent::Gen::String(node->at("Target"));
        }
        inline Ent::Gen::EntityRef NetworkLink::TargetEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("TargetEntityRef"));
        }
        inline Ent::Gen::String NetworkLink::ThumbnailMesh() const
        {
            return Ent::Gen::String(node->at("ThumbnailMesh"));
        }
        inline Ent::Gen::String NetworkLink::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // NetGD
        inline Ent::Gen::ComponentGD NetGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String NetGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MultiThumbnail
        inline Array<Ent::Gen::ListItem> MultiThumbnail::List() const
        {
            return Array<Ent::Gen::ListItem>(node->at("List"));
        }
        inline Ent::Gen::ComponentGD MultiThumbnail::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String MultiThumbnail::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MounterGD
        inline Ent::Gen::String MounterGD::HotspotName() const
        {
            return Ent::Gen::String(node->at("HotspotName"));
        }
        inline Ent::Gen::ComponentGD MounterGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String MounterGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MountableGD
        inline PrimArray<Ent::Gen::String> MountableGD::HotspotNames() const
        {
            return PrimArray<Ent::Gen::String>(node->at("HotspotNames"));
        }
        inline Array<Ent::Gen::MountableSnapLine_ControlPoint> MountableGD::SnapLine() const
        {
            return Array<Ent::Gen::MountableSnapLine_ControlPoint>(node->at("SnapLine"));
        }
        inline Ent::Gen::ComponentGD MountableGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String MountableGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MountIKControllerGD
        inline Ent::Gen::ComponentGD MountIKControllerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String MountIKControllerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float MountIKControllerGD::horizontalSpineLeanFactor() const
        {
            return Ent::Gen::Float(node->at("horizontalSpineLeanFactor"));
        }
        // MissionHolderGD
        inline Ent::Gen::Bool MissionHolderGD::Private() const
        {
            return Ent::Gen::Bool(node->at("Private"));
        }
        inline Ent::Gen::ComponentGD MissionHolderGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String MissionHolderGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MeshNavigationInfosGD
        inline Ent::Gen::ComponentGD MeshNavigationInfosGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String MeshNavigationInfosGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // Mesh
        inline Ent::Gen::String Mesh::File() const
        {
            return Ent::Gen::String(node->at("File"));
        }
        inline Ent::Gen::ComponentGD Mesh::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String Mesh::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // LDPrimitive
        inline Ent::Gen::Bool LDPrimitive::NonDisuptive() const
        {
            return Ent::Gen::Bool(node->at("NonDisuptive"));
        }
        inline Ent::Gen::PrimitiveData LDPrimitive::PrimitiveData() const
        {
            return Ent::Gen::PrimitiveData(node->at("PrimitiveData"));
        }
        inline Ent::Gen::String LDPrimitive::PrimitiveType() const
        {
            return Ent::Gen::String(node->at("PrimitiveType"));
        }
        inline Ent::Gen::ComponentGD LDPrimitive::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String LDPrimitive::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ItemHolderGD
        inline Ent::Gen::String ItemHolderGD::HotspotDefault() const
        {
            return Ent::Gen::String(node->at("HotspotDefault"));
        }
        inline Ent::Gen::String ItemHolderGD::HotspotHandLeft() const
        {
            return Ent::Gen::String(node->at("HotspotHandLeft"));
        }
        inline Ent::Gen::String ItemHolderGD::HotspotHandRight() const
        {
            return Ent::Gen::String(node->at("HotspotHandRight"));
        }
        inline Ent::Gen::ComponentGD ItemHolderGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Bool ItemHolderGD::Visible() const
        {
            return Ent::Gen::Bool(node->at("Visible"));
        }
        inline Ent::Gen::String ItemHolderGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // InventoryGD
        inline Ent::Gen::ComponentGD InventoryGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Array<Ent::Gen::TaggedEntityRef> InventoryGD::TaggedEntityRefs() const
        {
            return Array<Ent::Gen::TaggedEntityRef>(node->at("TaggedEntityRefs"));
        }
        inline Ent::Gen::String InventoryGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // InfoboardRegistererGD
        inline Ent::Gen::String InfoboardRegistererGD::InfoboardName() const
        {
            return Ent::Gen::String(node->at("InfoboardName"));
        }
        inline Ent::Gen::ComponentGD InfoboardRegistererGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String InfoboardRegistererGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HotspotsGD
        inline Ent::Gen::Map<char const*, Ent::Gen::HotspotData> HotspotsGD::HotspotsMap() const
        {
            return Ent::Gen::Map<char const*, Ent::Gen::HotspotData>(node->at("HotspotsMap"));
        }
        inline Ent::Gen::ComponentGD HotspotsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String HotspotsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HitTriggerGD
        inline Ent::Gen::ComponentGD HitTriggerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String HitTriggerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HeightObj
        inline Array<Ent::Gen::DisplaceNoiseListItem> HeightObj::DisplaceNoiseList() const
        {
            return Array<Ent::Gen::DisplaceNoiseListItem>(node->at("DisplaceNoiseList"));
        }
        inline Ent::Gen::Int HeightObj::EditorSubdivision() const
        {
            return Ent::Gen::Int(node->at("EditorSubdivision"));
        }
        inline Ent::Gen::Matrix33 HeightObj::LocalMatrix() const
        {
            return Ent::Gen::Matrix33(node->at("LocalMatrix"));
        }
        inline Ent::Gen::String HeightObj::MeshFile() const
        {
            return Ent::Gen::String(node->at("MeshFile"));
        }
        inline Ent::Gen::String HeightObj::MeshName() const
        {
            return Ent::Gen::String(node->at("MeshName"));
        }
        inline Ent::Gen::Int HeightObj::Priority() const
        {
            return Ent::Gen::Int(node->at("Priority"));
        }
        inline Ent::Gen::Int HeightObj::Subdivision() const
        {
            return Ent::Gen::Int(node->at("Subdivision"));
        }
        inline Ent::Gen::ComponentGD HeightObj::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String HeightObj::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HeightMapComponentGD
        inline Ent::Gen::String HeightMapComponentGD::HeightMapArchivePath() const
        {
            return Ent::Gen::String(node->at("HeightMapArchivePath"));
        }
        inline PrimArray<Ent::Gen::String> HeightMapComponentGD::HeightMapPaths() const
        {
            return PrimArray<Ent::Gen::String>(node->at("HeightMapPaths"));
        }
        inline Ent::Gen::Float HeightMapComponentGD::HeightScale() const
        {
            return Ent::Gen::Float(node->at("HeightScale"));
        }
        inline Ent::Gen::ComponentGD HeightMapComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Bool HeightMapComponentGD::SwapX() const
        {
            return Ent::Gen::Bool(node->at("SwapX"));
        }
        inline Ent::Gen::Bool HeightMapComponentGD::SwapY() const
        {
            return Ent::Gen::Bool(node->at("SwapY"));
        }
        inline Ent::Gen::Vector2 HeightMapComponentGD::WorldSize() const
        {
            return Ent::Gen::Vector2(node->at("WorldSize"));
        }
        inline Ent::Gen::String HeightMapComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HealthAreaGD
        inline Ent::Gen::Float HealthAreaGD::EnergyRestorationRate() const
        {
            return Ent::Gen::Float(node->at("EnergyRestorationRate"));
        }
        inline Ent::Gen::ReviveSide HealthAreaGD::FactionSide() const
        {
            return Ent::Gen::ReviveSide(node->at("FactionSide"));
        }
        inline Ent::Gen::Float HealthAreaGD::LifeRestorationRate() const
        {
            return Ent::Gen::Float(node->at("LifeRestorationRate"));
        }
        inline Ent::Gen::Float HealthAreaGD::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::Float HealthAreaGD::ReviveRestorationRate() const
        {
            return Ent::Gen::Float(node->at("ReviveRestorationRate"));
        }
        inline Ent::Gen::ComponentGD HealthAreaGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String HealthAreaGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HealerGD
        inline Ent::Gen::ComponentGD HealerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String HealerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HealTriggerGD
        inline Ent::Gen::ComponentGD HealTriggerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String HealTriggerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // HealPumpGD
        inline Ent::Gen::Float HealPumpGD::AlliesLifeAgentPerSecond() const
        {
            return Ent::Gen::Float(node->at("AlliesLifeAgentPerSecond"));
        }
        inline Ent::Gen::Float HealPumpGD::EnemiesLifeAgentPerSecond() const
        {
            return Ent::Gen::Float(node->at("EnemiesLifeAgentPerSecond"));
        }
        inline Ent::Gen::Float HealPumpGD::LifeAmountRatio() const
        {
            return Ent::Gen::Float(node->at("LifeAmountRatio"));
        }
        inline Ent::Gen::Float HealPumpGD::Range() const
        {
            return Ent::Gen::Float(node->at("Range"));
        }
        inline Ent::Gen::ComponentGD HealPumpGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String HealPumpGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // GroundTypeSamplerGD
        inline Ent::Gen::String GroundTypeSamplerGD::GroundTypeMapPath() const
        {
            return Ent::Gen::String(node->at("GroundTypeMapPath"));
        }
        inline Ent::Gen::ComponentGD GroundTypeSamplerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String GroundTypeSamplerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // GameEffectSpawnerGD
        inline Ent::Gen::Vector3 GameEffectSpawnerGD::GameEffectOffset() const
        {
            return Ent::Gen::Vector3(node->at("GameEffectOffset"));
        }
        inline Array<Ent::Gen::sGameEffectTemplate> GameEffectSpawnerGD::StartGameEffects() const
        {
            return Array<Ent::Gen::sGameEffectTemplate>(node->at("StartGameEffects"));
        }
        inline Ent::Gen::ComponentGD GameEffectSpawnerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String GameEffectSpawnerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FluidVolumeComponentGD
        inline Ent::Gen::FluidVolumeComponentGD_FluidVolumeData FluidVolumeComponentGD::FluidVolume() const
        {
            return Ent::Gen::FluidVolumeComponentGD_FluidVolumeData(node->at("FluidVolume"));
        }
        inline Ent::Gen::ComponentGD FluidVolumeComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String FluidVolumeComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FluidViewGD
        inline Ent::Gen::ComponentGD FluidViewGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String FluidViewGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FluidToRegenInjectorGD
        inline Ent::Gen::Float FluidToRegenInjectorGD::EnergyPerSecond() const
        {
            return Ent::Gen::Float(node->at("EnergyPerSecond"));
        }
        inline Ent::Gen::Float FluidToRegenInjectorGD::MinDepth() const
        {
            return Ent::Gen::Float(node->at("MinDepth"));
        }
        inline Ent::Gen::ComponentGD FluidToRegenInjectorGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Float FluidToRegenInjectorGD::UpdatePeriod() const
        {
            return Ent::Gen::Float(node->at("UpdatePeriod"));
        }
        inline Ent::Gen::String FluidToRegenInjectorGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FluidNavMeshTaggerGD
        inline Ent::Gen::Float FluidNavMeshTaggerGD::MinDepth() const
        {
            return Ent::Gen::Float(node->at("MinDepth"));
        }
        inline Ent::Gen::Precision FluidNavMeshTaggerGD::SamplingPrecision() const
        {
            return Ent::Gen::Precision(node->at("SamplingPrecision"));
        }
        inline Ent::Gen::ComponentGD FluidNavMeshTaggerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Float FluidNavMeshTaggerGD::UpdatePeriod() const
        {
            return Ent::Gen::Float(node->at("UpdatePeriod"));
        }
        inline Ent::Gen::String FluidNavMeshTaggerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FluidGD
        inline Ent::Gen::ComponentGD FluidGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String FluidGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::FluidType FluidGD::type() const
        {
            return Ent::Gen::FluidType(node->at("type"));
        }
        inline Ent::Gen::Bool FluidGD::useHalfShape() const
        {
            return Ent::Gen::Bool(node->at("useHalfShape"));
        }
        // FluidFXEntitySpawnerGD
        inline Ent::Gen::Precision FluidFXEntitySpawnerGD::SamplingPrecision() const
        {
            return Ent::Gen::Precision(node->at("SamplingPrecision"));
        }
        inline Array<Ent::Gen::SpawningParameter> FluidFXEntitySpawnerGD::SpawningParameters() const
        {
            return Array<Ent::Gen::SpawningParameter>(node->at("SpawningParameters"));
        }
        inline Ent::Gen::ComponentGD FluidFXEntitySpawnerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Float FluidFXEntitySpawnerGD::UpdatePeriod() const
        {
            return Ent::Gen::Float(node->at("UpdatePeriod"));
        }
        inline Ent::Gen::String FluidFXEntitySpawnerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FireSensorGD
        inline Ent::Gen::ComponentGD FireSensorGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String FireSensorGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EventTriggerGD
        inline PrimArray<Ent::Gen::String> EventTriggerGD::Events() const
        {
            return PrimArray<Ent::Gen::String>(node->at("Events"));
        }
        inline Ent::Gen::ComponentGD EventTriggerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EventTriggerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EventHandlerGD
        inline Ent::Gen::ComponentGD EventHandlerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EventHandlerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EnvStampGD
        inline Ent::Gen::Float EnvStampGD::RegenStateChangeDuration() const
        {
            return Ent::Gen::Float(node->at("RegenStateChangeDuration"));
        }
        inline Ent::Gen::Map<RegenerationStateEnum, Array<Ent::Gen::sEnvStamp>> EnvStampGD::Stamps() const
        {
            return Ent::Gen::Map<RegenerationStateEnum, Array<Ent::Gen::sEnvStamp>>(node->at("Stamps"));
        }
        inline Ent::Gen::ComponentGD EnvStampGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EnvStampGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EnergySpoutGD
        inline Ent::Gen::Float EnergySpoutGD::EnergySpeed() const
        {
            return Ent::Gen::Float(node->at("EnergySpeed"));
        }
        inline Ent::Gen::EntityRef EnergySpoutGD::ListenerEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("ListenerEntityRef"));
        }
        inline Ent::Gen::Float EnergySpoutGD::MinDistanceBetweenRegen() const
        {
            return Ent::Gen::Float(node->at("MinDistanceBetweenRegen"));
        }
        inline Ent::Gen::Float EnergySpoutGD::MinTimeBetweenRegen() const
        {
            return Ent::Gen::Float(node->at("MinTimeBetweenRegen"));
        }
        inline Ent::Gen::Float EnergySpoutGD::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::String EnergySpoutGD::SplineRegenEffectName() const
        {
            return Ent::Gen::String(node->at("SplineRegenEffectName"));
        }
        inline Ent::Gen::ComponentGD EnergySpoutGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EnergySpoutGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EnergySourceGD
        inline Ent::Gen::Float EnergySourceGD::MaxBuffDuration() const
        {
            return Ent::Gen::Float(node->at("MaxBuffDuration"));
        }
        inline Ent::Gen::Float EnergySourceGD::NearbyReactionRadius() const
        {
            return Ent::Gen::Float(node->at("NearbyReactionRadius"));
        }
        inline Ent::Gen::Float EnergySourceGD::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::Float EnergySourceGD::RefreshFrequency() const
        {
            return Ent::Gen::Float(node->at("RefreshFrequency"));
        }
        inline Ent::Gen::ReviveSide EnergySourceGD::ReviveSide() const
        {
            return Ent::Gen::ReviveSide(node->at("ReviveSide"));
        }
        inline Ent::Gen::String EnergySourceGD::SourceRegenEffectName() const
        {
            return Ent::Gen::String(node->at("SourceRegenEffectName"));
        }
        inline Ent::Gen::ComponentGD EnergySourceGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EnergySourceGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EnergyProbeGD
        inline Ent::Gen::ComponentGD EnergyProbeGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EnergyProbeGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EnergyPoolGD
        inline Ent::Gen::Float EnergyPoolGD::DrainConnectionRadius() const
        {
            return Ent::Gen::Float(node->at("DrainConnectionRadius"));
        }
        inline Ent::Gen::Bool EnergyPoolGD::FactionOverride() const
        {
            return Ent::Gen::Bool(node->at("FactionOverride"));
        }
        inline Ent::Gen::Float EnergyPoolGD::ProbeDetectionRadius() const
        {
            return Ent::Gen::Float(node->at("ProbeDetectionRadius"));
        }
        inline PrimArray<Ent::Gen::String> EnergyPoolGD::RegenEffectsOnConversion() const
        {
            return PrimArray<Ent::Gen::String>(node->at("RegenEffectsOnConversion"));
        }
        inline Ent::Gen::ComponentGD EnergyPoolGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EnergyPoolGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EnergyNetworkListenerGD
        inline Ent::Gen::ComponentGD EnergyNetworkListenerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EnergyNetworkListenerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EnergyDrainGD
        inline Ent::Gen::EntityRef EnergyDrainGD::PoolEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("PoolEntityRef"));
        }
        inline Ent::Gen::ComponentGD EnergyDrainGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EnergyDrainGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EnergyCrookGD
        inline Ent::Gen::EntityRef EnergyCrookGD::FatherEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("FatherEntityRef"));
        }
        inline Ent::Gen::Float EnergyCrookGD::Radius() const
        {
            return Ent::Gen::Float(node->at("Radius"));
        }
        inline Ent::Gen::Float EnergyCrookGD::RegenScale() const
        {
            return Ent::Gen::Float(node->at("RegenScale"));
        }
        inline Ent::Gen::ComponentGD EnergyCrookGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String EnergyCrookGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // DummyComponentGD
        inline Ent::Gen::ComponentGD DummyComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String DummyComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // DistanceTriggerGD
        inline PrimArray<Ent::Gen::Float> DistanceTriggerGD::Distances() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("Distances"));
        }
        inline PrimArray<Ent::Gen::Float> DistanceTriggerGD::Hystereses() const
        {
            return PrimArray<Ent::Gen::Float>(node->at("Hystereses"));
        }
        inline Ent::Gen::ComponentGD DistanceTriggerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String DistanceTriggerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // FightDistanceTriggerGD
        inline Ent::Gen::DistanceTriggerGD FightDistanceTriggerGD::Super() const
        {
            return Ent::Gen::DistanceTriggerGD(node->at("Super"));
        }
        inline Ent::Gen::String FightDistanceTriggerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // DebugGridGD
        inline Ent::Gen::Int DebugGridGD::Height() const
        {
            return Ent::Gen::Int(node->at("Height"));
        }
        inline Ent::Gen::ComponentGD DebugGridGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Int DebugGridGD::Width() const
        {
            return Ent::Gen::Int(node->at("Width"));
        }
        inline Ent::Gen::String DebugGridGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CustomThumbnail
        inline Ent::Gen::ComponentGD CustomThumbnail::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::ThumbPath CustomThumbnail::Thumbnail() const
        {
            return Ent::Gen::ThumbPath(node->at("Thumbnail"));
        }
        inline Ent::Gen::String CustomThumbnail::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CreatureUIGD
        inline Ent::Gen::Float CreatureUIGD::LifeBarLength() const
        {
            return Ent::Gen::Float(node->at("LifeBarLength"));
        }
        inline Ent::Gen::Float CreatureUIGD::LifeBarWidth() const
        {
            return Ent::Gen::Float(node->at("LifeBarWidth"));
        }
        inline Ent::Gen::Float CreatureUIGD::LifeBarZOffset() const
        {
            return Ent::Gen::Float(node->at("LifeBarZOffset"));
        }
        inline Ent::Gen::Bool CreatureUIGD::ShowLifeBar() const
        {
            return Ent::Gen::Bool(node->at("ShowLifeBar"));
        }
        inline Ent::Gen::ComponentGD CreatureUIGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String CreatureUIGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ConnectorGD
        inline Ent::Gen::ComponentGD ConnectorGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ConnectorGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ComponentWithProtoCodeGD
        inline Ent::Gen::ComponentGD ComponentWithProtoCodeGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ComponentWithProtoCodeGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ClothAnimationGD
        inline Ent::Gen::String ClothAnimationGD::ClothSkeletonPath() const
        {
            return Ent::Gen::String(node->at("ClothSkeletonPath"));
        }
        inline Ent::Gen::Float ClothAnimationGD::PhysicsDamping() const
        {
            return Ent::Gen::Float(node->at("PhysicsDamping"));
        }
        inline Ent::Gen::Bool ClothAnimationGD::PhysicsFixedDt() const
        {
            return Ent::Gen::Bool(node->at("PhysicsFixedDt"));
        }
        inline Ent::Gen::Vector3 ClothAnimationGD::PhysicsGravity() const
        {
            return Ent::Gen::Vector3(node->at("PhysicsGravity"));
        }
        inline Ent::Gen::Float ClothAnimationGD::PhysicsMass() const
        {
            return Ent::Gen::Float(node->at("PhysicsMass"));
        }
        inline Ent::Gen::Float ClothAnimationGD::PhysicsSpeedInfluence() const
        {
            return Ent::Gen::Float(node->at("PhysicsSpeedInfluence"));
        }
        inline Ent::Gen::Bool ClothAnimationGD::PhysicsUseDefaultProperties() const
        {
            return Ent::Gen::Bool(node->at("PhysicsUseDefaultProperties"));
        }
        inline Ent::Gen::ComponentGD ClothAnimationGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ClothAnimationGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ChildEntityPoolComponentGD
        inline PrimArray<Ent::Gen::EntityRef> ChildEntityPoolComponentGD::EntityRefs() const
        {
            return PrimArray<Ent::Gen::EntityRef>(node->at("EntityRefs"));
        }
        inline Ent::Gen::ComponentGD ChildEntityPoolComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String ChildEntityPoolComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CharacterPlatformGD
        inline Ent::Gen::ComponentGD CharacterPlatformGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String CharacterPlatformGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CameraDataGD
        inline Ent::Gen::String CameraDataGD::CameraDataResourcePath() const
        {
            return Ent::Gen::String(node->at("CameraDataResourcePath"));
        }
        inline Ent::Gen::ComponentGD CameraDataGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String CameraDataGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // BreakableGD
        inline Ent::Gen::String BreakableGD::BreakSoundBank() const
        {
            return Ent::Gen::String(node->at("BreakSoundBank"));
        }
        inline Ent::Gen::String BreakableGD::BreakSoundEvent() const
        {
            return Ent::Gen::String(node->at("BreakSoundEvent"));
        }
        inline Ent::Gen::String BreakableGD::GameEffectOnBroken() const
        {
            return Ent::Gen::String(node->at("GameEffectOnBroken"));
        }
        inline Ent::Gen::String BreakableGD::GameEffectOnDestruction() const
        {
            return Ent::Gen::String(node->at("GameEffectOnDestruction"));
        }
        inline Ent::Gen::ComponentGD BreakableGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String BreakableGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool BreakableGD::isBreakableWithAttack() const
        {
            return Ent::Gen::Bool(node->at("isBreakableWithAttack"));
        }
        // BittenGD
        inline Ent::Gen::ComponentGD BittenGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String BittenGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // BeamGeneratorGD
        inline PrimArray<Ent::Gen::String> BeamGeneratorGD::BonesStartPoints() const
        {
            return PrimArray<Ent::Gen::String>(node->at("BonesStartPoints"));
        }
        inline Ent::Gen::Float BeamGeneratorGD::ExtraDistanceBeyondTarget() const
        {
            return Ent::Gen::Float(node->at("ExtraDistanceBeyondTarget"));
        }
        inline Ent::Gen::Float BeamGeneratorGD::LengthDuration() const
        {
            return Ent::Gen::Float(node->at("LengthDuration"));
        }
        inline Ent::Gen::String BeamGeneratorGD::PathBeamEffect() const
        {
            return Ent::Gen::String(node->at("PathBeamEffect"));
        }
        inline Ent::Gen::Int BeamGeneratorGD::PointsPerBeam() const
        {
            return Ent::Gen::Int(node->at("PointsPerBeam"));
        }
        inline Ent::Gen::ComponentGD BeamGeneratorGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String BeamGeneratorGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AttackTriggerGD
        inline Ent::Gen::ComponentGD AttackTriggerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AttackTriggerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AssemblyGD
        inline Ent::Gen::ComponentGD AssemblyGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AssemblyGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationRegenConstraintsGD
        inline Ent::Gen::Float AnimationRegenConstraintsGD::MaxDisplace() const
        {
            return Ent::Gen::Float(node->at("MaxDisplace"));
        }
        inline Ent::Gen::Float AnimationRegenConstraintsGD::MaxRegenSpeed() const
        {
            return Ent::Gen::Float(node->at("MaxRegenSpeed"));
        }
        inline Ent::Gen::Float AnimationRegenConstraintsGD::MinDisplace() const
        {
            return Ent::Gen::Float(node->at("MinDisplace"));
        }
        inline Ent::Gen::Float AnimationRegenConstraintsGD::RegenMultiplier() const
        {
            return Ent::Gen::Float(node->at("RegenMultiplier"));
        }
        inline Ent::Gen::String AnimationRegenConstraintsGD::RegenToDisplaceCurve() const
        {
            return Ent::Gen::String(node->at("RegenToDisplaceCurve"));
        }
        inline Ent::Gen::ComponentGD AnimationRegenConstraintsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AnimationRegenConstraintsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationPlaylistGD
        inline PrimArray<Ent::Gen::String> AnimationPlaylistGD::PlayAnim() const
        {
            return PrimArray<Ent::Gen::String>(node->at("PlayAnim"));
        }
        inline Ent::Gen::Int AnimationPlaylistGD::PlayAnimInputID() const
        {
            return Ent::Gen::Int(node->at("PlayAnimInputID"));
        }
        inline Ent::Gen::Bool AnimationPlaylistGD::RandomizeStartTime() const
        {
            return Ent::Gen::Bool(node->at("RandomizeStartTime"));
        }
        inline Ent::Gen::ComponentGD AnimationPlaylistGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AnimationPlaylistGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationPhysicsChainConstraintsGD
        inline Ent::Gen::String AnimationPhysicsChainConstraintsGD::BoneNamePrefix() const
        {
            return Ent::Gen::String(node->at("BoneNamePrefix"));
        }
        inline Ent::Gen::ComponentGD AnimationPhysicsChainConstraintsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AnimationPhysicsChainConstraintsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationModelGD
        inline Ent::Gen::ComponentGD AnimationModelGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AnimationModelGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool AnimationModelGD::isLandAnimDriven() const
        {
            return Ent::Gen::Bool(node->at("isLandAnimDriven"));
        }
        inline Ent::Gen::Bool AnimationModelGD::isTurnAllowed() const
        {
            return Ent::Gen::Bool(node->at("isTurnAllowed"));
        }
        inline Ent::Gen::Float AnimationModelGD::playRatioFactor() const
        {
            return Ent::Gen::Float(node->at("playRatioFactor"));
        }
        inline Ent::Gen::Float AnimationModelGD::scalePlayRatioCoeffInfluence() const
        {
            return Ent::Gen::Float(node->at("scalePlayRatioCoeffInfluence"));
        }
        inline Ent::Gen::Float AnimationModelGD::startRunPlayRatioFactor() const
        {
            return Ent::Gen::Float(node->at("startRunPlayRatioFactor"));
        }
        inline Ent::Gen::Float AnimationModelGD::turnPlayRatioFactor() const
        {
            return Ent::Gen::Float(node->at("turnPlayRatioFactor"));
        }
        // AnimationHitsConstraintsGD
        inline Ent::Gen::ComponentGD AnimationHitsConstraintsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AnimationHitsConstraintsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // Component
        inline char const* Component::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::StaticObjectGD> Component::StaticObjectGD() const
        {
            return strcmp(node->getUnionType(), "StaticObjectGD") != 0? std::optional<Ent::Gen::StaticObjectGD>{}: std::optional<Ent::Gen::StaticObjectGD>(node->getUnionData());
        }
        inline Ent::Gen::StaticObjectGD Component::setStaticObjectGD() const
        {
            return Ent::Gen::StaticObjectGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationControllerGD> Component::AnimationControllerGD() const
        {
            return strcmp(node->getUnionType(), "AnimationControllerGD") != 0? std::optional<Ent::Gen::AnimationControllerGD>{}: std::optional<Ent::Gen::AnimationControllerGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationControllerGD Component::setAnimationControllerGD() const
        {
            return Ent::Gen::AnimationControllerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PhysicsDataGD> Component::PhysicsDataGD() const
        {
            return strcmp(node->getUnionType(), "PhysicsDataGD") != 0? std::optional<Ent::Gen::PhysicsDataGD>{}: std::optional<Ent::Gen::PhysicsDataGD>(node->getUnionData());
        }
        inline Ent::Gen::PhysicsDataGD Component::setPhysicsDataGD() const
        {
            return Ent::Gen::PhysicsDataGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::VisualGD> Component::VisualGD() const
        {
            return strcmp(node->getUnionType(), "VisualGD") != 0? std::optional<Ent::Gen::VisualGD>{}: std::optional<Ent::Gen::VisualGD>(node->getUnionData());
        }
        inline Ent::Gen::VisualGD Component::setVisualGD() const
        {
            return Ent::Gen::VisualGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TransformGD> Component::TransformGD() const
        {
            return strcmp(node->getUnionType(), "TransformGD") != 0? std::optional<Ent::Gen::TransformGD>{}: std::optional<Ent::Gen::TransformGD>(node->getUnionData());
        }
        inline Ent::Gen::TransformGD Component::setTransformGD() const
        {
            return Ent::Gen::TransformGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TerrainGD> Component::TerrainGD() const
        {
            return strcmp(node->getUnionType(), "TerrainGD") != 0? std::optional<Ent::Gen::TerrainGD>{}: std::optional<Ent::Gen::TerrainGD>(node->getUnionData());
        }
        inline Ent::Gen::TerrainGD Component::setTerrainGD() const
        {
            return Ent::Gen::TerrainGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PhysicsGD> Component::PhysicsGD() const
        {
            return strcmp(node->getUnionType(), "PhysicsGD") != 0? std::optional<Ent::Gen::PhysicsGD>{}: std::optional<Ent::Gen::PhysicsGD>(node->getUnionData());
        }
        inline Ent::Gen::PhysicsGD Component::setPhysicsGD() const
        {
            return Ent::Gen::PhysicsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CustomThumbnail> Component::CustomThumbnail() const
        {
            return strcmp(node->getUnionType(), "CustomThumbnail") != 0? std::optional<Ent::Gen::CustomThumbnail>{}: std::optional<Ent::Gen::CustomThumbnail>(node->getUnionData());
        }
        inline Ent::Gen::CustomThumbnail Component::setCustomThumbnail() const
        {
            return Ent::Gen::CustomThumbnail(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::HeightObj> Component::HeightObj() const
        {
            return strcmp(node->getUnionType(), "HeightObj") != 0? std::optional<Ent::Gen::HeightObj>{}: std::optional<Ent::Gen::HeightObj>(node->getUnionData());
        }
        inline Ent::Gen::HeightObj Component::setHeightObj() const
        {
            return Ent::Gen::HeightObj(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::LDPrimitive> Component::LDPrimitive() const
        {
            return strcmp(node->getUnionType(), "LDPrimitive") != 0? std::optional<Ent::Gen::LDPrimitive>{}: std::optional<Ent::Gen::LDPrimitive>(node->getUnionData());
        }
        inline Ent::Gen::LDPrimitive Component::setLDPrimitive() const
        {
            return Ent::Gen::LDPrimitive(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::Mesh> Component::Mesh() const
        {
            return strcmp(node->getUnionType(), "Mesh") != 0? std::optional<Ent::Gen::Mesh>{}: std::optional<Ent::Gen::Mesh>(node->getUnionData());
        }
        inline Ent::Gen::Mesh Component::setMesh() const
        {
            return Ent::Gen::Mesh(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::MultiThumbnail> Component::MultiThumbnail() const
        {
            return strcmp(node->getUnionType(), "MultiThumbnail") != 0? std::optional<Ent::Gen::MultiThumbnail>{}: std::optional<Ent::Gen::MultiThumbnail>(node->getUnionData());
        }
        inline Ent::Gen::MultiThumbnail Component::setMultiThumbnail() const
        {
            return Ent::Gen::MultiThumbnail(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::NetworkLink> Component::NetworkLink() const
        {
            return strcmp(node->getUnionType(), "NetworkLink") != 0? std::optional<Ent::Gen::NetworkLink>{}: std::optional<Ent::Gen::NetworkLink>(node->getUnionData());
        }
        inline Ent::Gen::NetworkLink Component::setNetworkLink() const
        {
            return Ent::Gen::NetworkLink(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::NetworkNode> Component::NetworkNode() const
        {
            return strcmp(node->getUnionType(), "NetworkNode") != 0? std::optional<Ent::Gen::NetworkNode>{}: std::optional<Ent::Gen::NetworkNode>(node->getUnionData());
        }
        inline Ent::Gen::NetworkNode Component::setNetworkNode() const
        {
            return Ent::Gen::NetworkNode(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::NotVisibleInSubscene> Component::NotVisibleInSubscene() const
        {
            return strcmp(node->getUnionType(), "NotVisibleInSubscene") != 0? std::optional<Ent::Gen::NotVisibleInSubscene>{}: std::optional<Ent::Gen::NotVisibleInSubscene>(node->getUnionData());
        }
        inline Ent::Gen::NotVisibleInSubscene Component::setNotVisibleInSubscene() const
        {
            return Ent::Gen::NotVisibleInSubscene(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SeedPatch> Component::SeedPatch() const
        {
            return strcmp(node->getUnionType(), "SeedPatch") != 0? std::optional<Ent::Gen::SeedPatch>{}: std::optional<Ent::Gen::SeedPatch>(node->getUnionData());
        }
        inline Ent::Gen::SeedPatch Component::setSeedPatch() const
        {
            return Ent::Gen::SeedPatch(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::StickToTerrain> Component::StickToTerrain() const
        {
            return strcmp(node->getUnionType(), "StickToTerrain") != 0? std::optional<Ent::Gen::StickToTerrain>{}: std::optional<Ent::Gen::StickToTerrain>(node->getUnionData());
        }
        inline Ent::Gen::StickToTerrain Component::setStickToTerrain() const
        {
            return Ent::Gen::StickToTerrain(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SubScene> Component::SubScene() const
        {
            return strcmp(node->getUnionType(), "SubScene") != 0? std::optional<Ent::Gen::SubScene>{}: std::optional<Ent::Gen::SubScene>(node->getUnionData());
        }
        inline Ent::Gen::SubScene Component::setSubScene() const
        {
            return Ent::Gen::SubScene(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SystemicCreature> Component::SystemicCreature() const
        {
            return strcmp(node->getUnionType(), "SystemicCreature") != 0? std::optional<Ent::Gen::SystemicCreature>{}: std::optional<Ent::Gen::SystemicCreature>(node->getUnionData());
        }
        inline Ent::Gen::SystemicCreature Component::setSystemicCreature() const
        {
            return Ent::Gen::SystemicCreature(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TerrainSurfaceObject> Component::TerrainSurfaceObject() const
        {
            return strcmp(node->getUnionType(), "TerrainSurfaceObject") != 0? std::optional<Ent::Gen::TerrainSurfaceObject>{}: std::optional<Ent::Gen::TerrainSurfaceObject>(node->getUnionData());
        }
        inline Ent::Gen::TerrainSurfaceObject Component::setTerrainSurfaceObject() const
        {
            return Ent::Gen::TerrainSurfaceObject(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TestArrays> Component::TestArrays() const
        {
            return strcmp(node->getUnionType(), "TestArrays") != 0? std::optional<Ent::Gen::TestArrays>{}: std::optional<Ent::Gen::TestArrays>(node->getUnionData());
        }
        inline Ent::Gen::TestArrays Component::setTestArrays() const
        {
            return Ent::Gen::TestArrays(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TestCreature> Component::TestCreature() const
        {
            return strcmp(node->getUnionType(), "TestCreature") != 0? std::optional<Ent::Gen::TestCreature>{}: std::optional<Ent::Gen::TestCreature>(node->getUnionData());
        }
        inline Ent::Gen::TestCreature Component::setTestCreature() const
        {
            return Ent::Gen::TestCreature(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TestDefaultValues> Component::TestDefaultValues() const
        {
            return strcmp(node->getUnionType(), "TestDefaultValues") != 0? std::optional<Ent::Gen::TestDefaultValues>{}: std::optional<Ent::Gen::TestDefaultValues>(node->getUnionData());
        }
        inline Ent::Gen::TestDefaultValues Component::setTestDefaultValues() const
        {
            return Ent::Gen::TestDefaultValues(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TestEntityRef> Component::TestEntityRef() const
        {
            return strcmp(node->getUnionType(), "TestEntityRef") != 0? std::optional<Ent::Gen::TestEntityRef>{}: std::optional<Ent::Gen::TestEntityRef>(node->getUnionData());
        }
        inline Ent::Gen::TestEntityRef Component::setTestEntityRef() const
        {
            return Ent::Gen::TestEntityRef(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TestSetOfObject> Component::TestSetOfObject() const
        {
            return strcmp(node->getUnionType(), "TestSetOfObject") != 0? std::optional<Ent::Gen::TestSetOfObject>{}: std::optional<Ent::Gen::TestSetOfObject>(node->getUnionData());
        }
        inline Ent::Gen::TestSetOfObject Component::setTestSetOfObject() const
        {
            return Ent::Gen::TestSetOfObject(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TestUnion> Component::TestUnion() const
        {
            return strcmp(node->getUnionType(), "TestUnion") != 0? std::optional<Ent::Gen::TestUnion>{}: std::optional<Ent::Gen::TestUnion>(node->getUnionData());
        }
        inline Ent::Gen::TestUnion Component::setTestUnion() const
        {
            return Ent::Gen::TestUnion(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::UnitTestComponent> Component::UnitTestComponent() const
        {
            return strcmp(node->getUnionType(), "UnitTestComponent") != 0? std::optional<Ent::Gen::UnitTestComponent>{}: std::optional<Ent::Gen::UnitTestComponent>(node->getUnionData());
        }
        inline Ent::Gen::UnitTestComponent Component::setUnitTestComponent() const
        {
            return Ent::Gen::UnitTestComponent(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::WildObject> Component::WildObject() const
        {
            return strcmp(node->getUnionType(), "WildObject") != 0? std::optional<Ent::Gen::WildObject>{}: std::optional<Ent::Gen::WildObject>(node->getUnionData());
        }
        inline Ent::Gen::WildObject Component::setWildObject() const
        {
            return Ent::Gen::WildObject(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EnergyCrookGD> Component::EnergyCrookGD() const
        {
            return strcmp(node->getUnionType(), "EnergyCrookGD") != 0? std::optional<Ent::Gen::EnergyCrookGD>{}: std::optional<Ent::Gen::EnergyCrookGD>(node->getUnionData());
        }
        inline Ent::Gen::EnergyCrookGD Component::setEnergyCrookGD() const
        {
            return Ent::Gen::EnergyCrookGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AIContextGD> Component::AIContextGD() const
        {
            return strcmp(node->getUnionType(), "AIContextGD") != 0? std::optional<Ent::Gen::AIContextGD>{}: std::optional<Ent::Gen::AIContextGD>(node->getUnionData());
        }
        inline Ent::Gen::AIContextGD Component::setAIContextGD() const
        {
            return Ent::Gen::AIContextGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EventTriggerGD> Component::EventTriggerGD() const
        {
            return strcmp(node->getUnionType(), "EventTriggerGD") != 0? std::optional<Ent::Gen::EventTriggerGD>{}: std::optional<Ent::Gen::EventTriggerGD>(node->getUnionData());
        }
        inline Ent::Gen::EventTriggerGD Component::setEventTriggerGD() const
        {
            return Ent::Gen::EventTriggerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::BeamGeneratorGD> Component::BeamGeneratorGD() const
        {
            return strcmp(node->getUnionType(), "BeamGeneratorGD") != 0? std::optional<Ent::Gen::BeamGeneratorGD>{}: std::optional<Ent::Gen::BeamGeneratorGD>(node->getUnionData());
        }
        inline Ent::Gen::BeamGeneratorGD Component::setBeamGeneratorGD() const
        {
            return Ent::Gen::BeamGeneratorGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::WorldScalePathFindGD> Component::WorldScalePathFindGD() const
        {
            return strcmp(node->getUnionType(), "WorldScalePathFindGD") != 0? std::optional<Ent::Gen::WorldScalePathFindGD>{}: std::optional<Ent::Gen::WorldScalePathFindGD>(node->getUnionData());
        }
        inline Ent::Gen::WorldScalePathFindGD Component::setWorldScalePathFindGD() const
        {
            return Ent::Gen::WorldScalePathFindGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::NetGD> Component::NetGD() const
        {
            return strcmp(node->getUnionType(), "NetGD") != 0? std::optional<Ent::Gen::NetGD>{}: std::optional<Ent::Gen::NetGD>(node->getUnionData());
        }
        inline Ent::Gen::NetGD Component::setNetGD() const
        {
            return Ent::Gen::NetGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::BittenGD> Component::BittenGD() const
        {
            return strcmp(node->getUnionType(), "BittenGD") != 0? std::optional<Ent::Gen::BittenGD>{}: std::optional<Ent::Gen::BittenGD>(node->getUnionData());
        }
        inline Ent::Gen::BittenGD Component::setBittenGD() const
        {
            return Ent::Gen::BittenGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PathBoneAnimGD> Component::PathBoneAnimGD() const
        {
            return strcmp(node->getUnionType(), "PathBoneAnimGD") != 0? std::optional<Ent::Gen::PathBoneAnimGD>{}: std::optional<Ent::Gen::PathBoneAnimGD>(node->getUnionData());
        }
        inline Ent::Gen::PathBoneAnimGD Component::setPathBoneAnimGD() const
        {
            return Ent::Gen::PathBoneAnimGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationRegenConstraintsGD> Component::AnimationRegenConstraintsGD() const
        {
            return strcmp(node->getUnionType(), "AnimationRegenConstraintsGD") != 0? std::optional<Ent::Gen::AnimationRegenConstraintsGD>{}: std::optional<Ent::Gen::AnimationRegenConstraintsGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationRegenConstraintsGD Component::setAnimationRegenConstraintsGD() const
        {
            return Ent::Gen::AnimationRegenConstraintsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::HealPumpGD> Component::HealPumpGD() const
        {
            return strcmp(node->getUnionType(), "HealPumpGD") != 0? std::optional<Ent::Gen::HealPumpGD>{}: std::optional<Ent::Gen::HealPumpGD>(node->getUnionData());
        }
        inline Ent::Gen::HealPumpGD Component::setHealPumpGD() const
        {
            return Ent::Gen::HealPumpGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::GroundTypeSamplerGD> Component::GroundTypeSamplerGD() const
        {
            return strcmp(node->getUnionType(), "GroundTypeSamplerGD") != 0? std::optional<Ent::Gen::GroundTypeSamplerGD>{}: std::optional<Ent::Gen::GroundTypeSamplerGD>(node->getUnionData());
        }
        inline Ent::Gen::GroundTypeSamplerGD Component::setGroundTypeSamplerGD() const
        {
            return Ent::Gen::GroundTypeSamplerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::UnifiedPhysicsDataGD> Component::UnifiedPhysicsDataGD() const
        {
            return strcmp(node->getUnionType(), "UnifiedPhysicsDataGD") != 0? std::optional<Ent::Gen::UnifiedPhysicsDataGD>{}: std::optional<Ent::Gen::UnifiedPhysicsDataGD>(node->getUnionData());
        }
        inline Ent::Gen::UnifiedPhysicsDataGD Component::setUnifiedPhysicsDataGD() const
        {
            return Ent::Gen::UnifiedPhysicsDataGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::FluidGD> Component::FluidGD() const
        {
            return strcmp(node->getUnionType(), "FluidGD") != 0? std::optional<Ent::Gen::FluidGD>{}: std::optional<Ent::Gen::FluidGD>(node->getUnionData());
        }
        inline Ent::Gen::FluidGD Component::setFluidGD() const
        {
            return Ent::Gen::FluidGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ProjectileGD> Component::ProjectileGD() const
        {
            return strcmp(node->getUnionType(), "ProjectileGD") != 0? std::optional<Ent::Gen::ProjectileGD>{}: std::optional<Ent::Gen::ProjectileGD>(node->getUnionData());
        }
        inline Ent::Gen::ProjectileGD Component::setProjectileGD() const
        {
            return Ent::Gen::ProjectileGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CameraSetterGD> Component::CameraSetterGD() const
        {
            return strcmp(node->getUnionType(), "CameraSetterGD") != 0? std::optional<Ent::Gen::CameraSetterGD>{}: std::optional<Ent::Gen::CameraSetterGD>(node->getUnionData());
        }
        inline Ent::Gen::CameraSetterGD Component::setCameraSetterGD() const
        {
            return Ent::Gen::CameraSetterGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AssemblyGD> Component::AssemblyGD() const
        {
            return strcmp(node->getUnionType(), "AssemblyGD") != 0? std::optional<Ent::Gen::AssemblyGD>{}: std::optional<Ent::Gen::AssemblyGD>(node->getUnionData());
        }
        inline Ent::Gen::AssemblyGD Component::setAssemblyGD() const
        {
            return Ent::Gen::AssemblyGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SmoothScaleComponentGD> Component::SmoothScaleComponentGD() const
        {
            return strcmp(node->getUnionType(), "SmoothScaleComponentGD") != 0? std::optional<Ent::Gen::SmoothScaleComponentGD>{}: std::optional<Ent::Gen::SmoothScaleComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::SmoothScaleComponentGD Component::setSmoothScaleComponentGD() const
        {
            return Ent::Gen::SmoothScaleComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::FluidViewGD> Component::FluidViewGD() const
        {
            return strcmp(node->getUnionType(), "FluidViewGD") != 0? std::optional<Ent::Gen::FluidViewGD>{}: std::optional<Ent::Gen::FluidViewGD>(node->getUnionData());
        }
        inline Ent::Gen::FluidViewGD Component::setFluidViewGD() const
        {
            return Ent::Gen::FluidViewGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::RegenMeshGD> Component::RegenMeshGD() const
        {
            return strcmp(node->getUnionType(), "RegenMeshGD") != 0? std::optional<Ent::Gen::RegenMeshGD>{}: std::optional<Ent::Gen::RegenMeshGD>(node->getUnionData());
        }
        inline Ent::Gen::RegenMeshGD Component::setRegenMeshGD() const
        {
            return Ent::Gen::RegenMeshGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ReviveEnergyGD> Component::ReviveEnergyGD() const
        {
            return strcmp(node->getUnionType(), "ReviveEnergyGD") != 0? std::optional<Ent::Gen::ReviveEnergyGD>{}: std::optional<Ent::Gen::ReviveEnergyGD>(node->getUnionData());
        }
        inline Ent::Gen::ReviveEnergyGD Component::setReviveEnergyGD() const
        {
            return Ent::Gen::ReviveEnergyGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::DebugGridGD> Component::DebugGridGD() const
        {
            return strcmp(node->getUnionType(), "DebugGridGD") != 0? std::optional<Ent::Gen::DebugGridGD>{}: std::optional<Ent::Gen::DebugGridGD>(node->getUnionData());
        }
        inline Ent::Gen::DebugGridGD Component::setDebugGridGD() const
        {
            return Ent::Gen::DebugGridGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ChildEntityPoolComponentGD> Component::ChildEntityPoolComponentGD() const
        {
            return strcmp(node->getUnionType(), "ChildEntityPoolComponentGD") != 0? std::optional<Ent::Gen::ChildEntityPoolComponentGD>{}: std::optional<Ent::Gen::ChildEntityPoolComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::ChildEntityPoolComponentGD Component::setChildEntityPoolComponentGD() const
        {
            return Ent::Gen::ChildEntityPoolComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ProtoComponentGD> Component::ProtoComponentGD() const
        {
            return strcmp(node->getUnionType(), "ProtoComponentGD") != 0? std::optional<Ent::Gen::ProtoComponentGD>{}: std::optional<Ent::Gen::ProtoComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::ProtoComponentGD Component::setProtoComponentGD() const
        {
            return Ent::Gen::ProtoComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::GameEffectSpawnerGD> Component::GameEffectSpawnerGD() const
        {
            return strcmp(node->getUnionType(), "GameEffectSpawnerGD") != 0? std::optional<Ent::Gen::GameEffectSpawnerGD>{}: std::optional<Ent::Gen::GameEffectSpawnerGD>(node->getUnionData());
        }
        inline Ent::Gen::GameEffectSpawnerGD Component::setGameEffectSpawnerGD() const
        {
            return Ent::Gen::GameEffectSpawnerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ClothGD> Component::ClothGD() const
        {
            return strcmp(node->getUnionType(), "ClothGD") != 0? std::optional<Ent::Gen::ClothGD>{}: std::optional<Ent::Gen::ClothGD>(node->getUnionData());
        }
        inline Ent::Gen::ClothGD Component::setClothGD() const
        {
            return Ent::Gen::ClothGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::FireSensorGD> Component::FireSensorGD() const
        {
            return strcmp(node->getUnionType(), "FireSensorGD") != 0? std::optional<Ent::Gen::FireSensorGD>{}: std::optional<Ent::Gen::FireSensorGD>(node->getUnionData());
        }
        inline Ent::Gen::FireSensorGD Component::setFireSensorGD() const
        {
            return Ent::Gen::FireSensorGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::HealerGD> Component::HealerGD() const
        {
            return strcmp(node->getUnionType(), "HealerGD") != 0? std::optional<Ent::Gen::HealerGD>{}: std::optional<Ent::Gen::HealerGD>(node->getUnionData());
        }
        inline Ent::Gen::HealerGD Component::setHealerGD() const
        {
            return Ent::Gen::HealerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationLegsConstraintsGD> Component::AnimationLegsConstraintsGD() const
        {
            return strcmp(node->getUnionType(), "AnimationLegsConstraintsGD") != 0? std::optional<Ent::Gen::AnimationLegsConstraintsGD>{}: std::optional<Ent::Gen::AnimationLegsConstraintsGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationLegsConstraintsGD Component::setAnimationLegsConstraintsGD() const
        {
            return Ent::Gen::AnimationLegsConstraintsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PathBoneRigidBodyGD> Component::PathBoneRigidBodyGD() const
        {
            return strcmp(node->getUnionType(), "PathBoneRigidBodyGD") != 0? std::optional<Ent::Gen::PathBoneRigidBodyGD>{}: std::optional<Ent::Gen::PathBoneRigidBodyGD>(node->getUnionData());
        }
        inline Ent::Gen::PathBoneRigidBodyGD Component::setPathBoneRigidBodyGD() const
        {
            return Ent::Gen::PathBoneRigidBodyGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::FightDistanceTriggerGD> Component::FightDistanceTriggerGD() const
        {
            return strcmp(node->getUnionType(), "FightDistanceTriggerGD") != 0? std::optional<Ent::Gen::FightDistanceTriggerGD>{}: std::optional<Ent::Gen::FightDistanceTriggerGD>(node->getUnionData());
        }
        inline Ent::Gen::FightDistanceTriggerGD Component::setFightDistanceTriggerGD() const
        {
            return Ent::Gen::FightDistanceTriggerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SoulSpotGD> Component::SoulSpotGD() const
        {
            return strcmp(node->getUnionType(), "SoulSpotGD") != 0? std::optional<Ent::Gen::SoulSpotGD>{}: std::optional<Ent::Gen::SoulSpotGD>(node->getUnionData());
        }
        inline Ent::Gen::SoulSpotGD Component::setSoulSpotGD() const
        {
            return Ent::Gen::SoulSpotGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::HealTriggerGD> Component::HealTriggerGD() const
        {
            return strcmp(node->getUnionType(), "HealTriggerGD") != 0? std::optional<Ent::Gen::HealTriggerGD>{}: std::optional<Ent::Gen::HealTriggerGD>(node->getUnionData());
        }
        inline Ent::Gen::HealTriggerGD Component::setHealTriggerGD() const
        {
            return Ent::Gen::HealTriggerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationTailConstraintsGD> Component::AnimationTailConstraintsGD() const
        {
            return strcmp(node->getUnionType(), "AnimationTailConstraintsGD") != 0? std::optional<Ent::Gen::AnimationTailConstraintsGD>{}: std::optional<Ent::Gen::AnimationTailConstraintsGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationTailConstraintsGD Component::setAnimationTailConstraintsGD() const
        {
            return Ent::Gen::AnimationTailConstraintsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::VolumeConstraintGD> Component::VolumeConstraintGD() const
        {
            return strcmp(node->getUnionType(), "VolumeConstraintGD") != 0? std::optional<Ent::Gen::VolumeConstraintGD>{}: std::optional<Ent::Gen::VolumeConstraintGD>(node->getUnionData());
        }
        inline Ent::Gen::VolumeConstraintGD Component::setVolumeConstraintGD() const
        {
            return Ent::Gen::VolumeConstraintGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EnvStampGD> Component::EnvStampGD() const
        {
            return strcmp(node->getUnionType(), "EnvStampGD") != 0? std::optional<Ent::Gen::EnvStampGD>{}: std::optional<Ent::Gen::EnvStampGD>(node->getUnionData());
        }
        inline Ent::Gen::EnvStampGD Component::setEnvStampGD() const
        {
            return Ent::Gen::EnvStampGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::FluidFXEntitySpawnerGD> Component::FluidFXEntitySpawnerGD() const
        {
            return strcmp(node->getUnionType(), "FluidFXEntitySpawnerGD") != 0? std::optional<Ent::Gen::FluidFXEntitySpawnerGD>{}: std::optional<Ent::Gen::FluidFXEntitySpawnerGD>(node->getUnionData());
        }
        inline Ent::Gen::FluidFXEntitySpawnerGD Component::setFluidFXEntitySpawnerGD() const
        {
            return Ent::Gen::FluidFXEntitySpawnerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EnergyDrainGD> Component::EnergyDrainGD() const
        {
            return strcmp(node->getUnionType(), "EnergyDrainGD") != 0? std::optional<Ent::Gen::EnergyDrainGD>{}: std::optional<Ent::Gen::EnergyDrainGD>(node->getUnionData());
        }
        inline Ent::Gen::EnergyDrainGD Component::setEnergyDrainGD() const
        {
            return Ent::Gen::EnergyDrainGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationEventsGeneratorGD> Component::AnimationEventsGeneratorGD() const
        {
            return strcmp(node->getUnionType(), "AnimationEventsGeneratorGD") != 0? std::optional<Ent::Gen::AnimationEventsGeneratorGD>{}: std::optional<Ent::Gen::AnimationEventsGeneratorGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationEventsGeneratorGD Component::setAnimationEventsGeneratorGD() const
        {
            return Ent::Gen::AnimationEventsGeneratorGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::MountableGD> Component::MountableGD() const
        {
            return strcmp(node->getUnionType(), "MountableGD") != 0? std::optional<Ent::Gen::MountableGD>{}: std::optional<Ent::Gen::MountableGD>(node->getUnionData());
        }
        inline Ent::Gen::MountableGD Component::setMountableGD() const
        {
            return Ent::Gen::MountableGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::InfoboardRegistererGD> Component::InfoboardRegistererGD() const
        {
            return strcmp(node->getUnionType(), "InfoboardRegistererGD") != 0? std::optional<Ent::Gen::InfoboardRegistererGD>{}: std::optional<Ent::Gen::InfoboardRegistererGD>(node->getUnionData());
        }
        inline Ent::Gen::InfoboardRegistererGD Component::setInfoboardRegistererGD() const
        {
            return Ent::Gen::InfoboardRegistererGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EventHandlerGD> Component::EventHandlerGD() const
        {
            return strcmp(node->getUnionType(), "EventHandlerGD") != 0? std::optional<Ent::Gen::EventHandlerGD>{}: std::optional<Ent::Gen::EventHandlerGD>(node->getUnionData());
        }
        inline Ent::Gen::EventHandlerGD Component::setEventHandlerGD() const
        {
            return Ent::Gen::EventHandlerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SoulRespawnOpportunityGD> Component::SoulRespawnOpportunityGD() const
        {
            return strcmp(node->getUnionType(), "SoulRespawnOpportunityGD") != 0? std::optional<Ent::Gen::SoulRespawnOpportunityGD>{}: std::optional<Ent::Gen::SoulRespawnOpportunityGD>(node->getUnionData());
        }
        inline Ent::Gen::SoulRespawnOpportunityGD Component::setSoulRespawnOpportunityGD() const
        {
            return Ent::Gen::SoulRespawnOpportunityGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::HealthAreaGD> Component::HealthAreaGD() const
        {
            return strcmp(node->getUnionType(), "HealthAreaGD") != 0? std::optional<Ent::Gen::HealthAreaGD>{}: std::optional<Ent::Gen::HealthAreaGD>(node->getUnionData());
        }
        inline Ent::Gen::HealthAreaGD Component::setHealthAreaGD() const
        {
            return Ent::Gen::HealthAreaGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SoundAreaGD> Component::SoundAreaGD() const
        {
            return strcmp(node->getUnionType(), "SoundAreaGD") != 0? std::optional<Ent::Gen::SoundAreaGD>{}: std::optional<Ent::Gen::SoundAreaGD>(node->getUnionData());
        }
        inline Ent::Gen::SoundAreaGD Component::setSoundAreaGD() const
        {
            return Ent::Gen::SoundAreaGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PathBoneInfluenceGD> Component::PathBoneInfluenceGD() const
        {
            return strcmp(node->getUnionType(), "PathBoneInfluenceGD") != 0? std::optional<Ent::Gen::PathBoneInfluenceGD>{}: std::optional<Ent::Gen::PathBoneInfluenceGD>(node->getUnionData());
        }
        inline Ent::Gen::PathBoneInfluenceGD Component::setPathBoneInfluenceGD() const
        {
            return Ent::Gen::PathBoneInfluenceGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ComponentWithProtoCodeGD> Component::ComponentWithProtoCodeGD() const
        {
            return strcmp(node->getUnionType(), "ComponentWithProtoCodeGD") != 0? std::optional<Ent::Gen::ComponentWithProtoCodeGD>{}: std::optional<Ent::Gen::ComponentWithProtoCodeGD>(node->getUnionData());
        }
        inline Ent::Gen::ComponentWithProtoCodeGD Component::setComponentWithProtoCodeGD() const
        {
            return Ent::Gen::ComponentWithProtoCodeGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CharacterControllerGD> Component::CharacterControllerGD() const
        {
            return strcmp(node->getUnionType(), "CharacterControllerGD") != 0? std::optional<Ent::Gen::CharacterControllerGD>{}: std::optional<Ent::Gen::CharacterControllerGD>(node->getUnionData());
        }
        inline Ent::Gen::CharacterControllerGD Component::setCharacterControllerGD() const
        {
            return Ent::Gen::CharacterControllerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PickableComponentGD> Component::PickableComponentGD() const
        {
            return strcmp(node->getUnionType(), "PickableComponentGD") != 0? std::optional<Ent::Gen::PickableComponentGD>{}: std::optional<Ent::Gen::PickableComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::PickableComponentGD Component::setPickableComponentGD() const
        {
            return Ent::Gen::PickableComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CameraDataGD> Component::CameraDataGD() const
        {
            return strcmp(node->getUnionType(), "CameraDataGD") != 0? std::optional<Ent::Gen::CameraDataGD>{}: std::optional<Ent::Gen::CameraDataGD>(node->getUnionData());
        }
        inline Ent::Gen::CameraDataGD Component::setCameraDataGD() const
        {
            return Ent::Gen::CameraDataGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::RegenFXGD> Component::RegenFXGD() const
        {
            return strcmp(node->getUnionType(), "RegenFXGD") != 0? std::optional<Ent::Gen::RegenFXGD>{}: std::optional<Ent::Gen::RegenFXGD>(node->getUnionData());
        }
        inline Ent::Gen::RegenFXGD Component::setRegenFXGD() const
        {
            return Ent::Gen::RegenFXGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PhysicsMeshDeformerGD> Component::PhysicsMeshDeformerGD() const
        {
            return strcmp(node->getUnionType(), "PhysicsMeshDeformerGD") != 0? std::optional<Ent::Gen::PhysicsMeshDeformerGD>{}: std::optional<Ent::Gen::PhysicsMeshDeformerGD>(node->getUnionData());
        }
        inline Ent::Gen::PhysicsMeshDeformerGD Component::setPhysicsMeshDeformerGD() const
        {
            return Ent::Gen::PhysicsMeshDeformerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationHitsConstraintsGD> Component::AnimationHitsConstraintsGD() const
        {
            return strcmp(node->getUnionType(), "AnimationHitsConstraintsGD") != 0? std::optional<Ent::Gen::AnimationHitsConstraintsGD>{}: std::optional<Ent::Gen::AnimationHitsConstraintsGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationHitsConstraintsGD Component::setAnimationHitsConstraintsGD() const
        {
            return Ent::Gen::AnimationHitsConstraintsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::FluidVolumeComponentGD> Component::FluidVolumeComponentGD() const
        {
            return strcmp(node->getUnionType(), "FluidVolumeComponentGD") != 0? std::optional<Ent::Gen::FluidVolumeComponentGD>{}: std::optional<Ent::Gen::FluidVolumeComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::FluidVolumeComponentGD Component::setFluidVolumeComponentGD() const
        {
            return Ent::Gen::FluidVolumeComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::RegenerableVegetationGD> Component::RegenerableVegetationGD() const
        {
            return strcmp(node->getUnionType(), "RegenerableVegetationGD") != 0? std::optional<Ent::Gen::RegenerableVegetationGD>{}: std::optional<Ent::Gen::RegenerableVegetationGD>(node->getUnionData());
        }
        inline Ent::Gen::RegenerableVegetationGD Component::setRegenerableVegetationGD() const
        {
            return Ent::Gen::RegenerableVegetationGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ShamanVisionGD> Component::ShamanVisionGD() const
        {
            return strcmp(node->getUnionType(), "ShamanVisionGD") != 0? std::optional<Ent::Gen::ShamanVisionGD>{}: std::optional<Ent::Gen::ShamanVisionGD>(node->getUnionData());
        }
        inline Ent::Gen::ShamanVisionGD Component::setShamanVisionGD() const
        {
            return Ent::Gen::ShamanVisionGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CinematicGD> Component::CinematicGD() const
        {
            return strcmp(node->getUnionType(), "CinematicGD") != 0? std::optional<Ent::Gen::CinematicGD>{}: std::optional<Ent::Gen::CinematicGD>(node->getUnionData());
        }
        inline Ent::Gen::CinematicGD Component::setCinematicGD() const
        {
            return Ent::Gen::CinematicGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ConnectorGD> Component::ConnectorGD() const
        {
            return strcmp(node->getUnionType(), "ConnectorGD") != 0? std::optional<Ent::Gen::ConnectorGD>{}: std::optional<Ent::Gen::ConnectorGD>(node->getUnionData());
        }
        inline Ent::Gen::ConnectorGD Component::setConnectorGD() const
        {
            return Ent::Gen::ConnectorGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::BeamTargetGD> Component::BeamTargetGD() const
        {
            return strcmp(node->getUnionType(), "BeamTargetGD") != 0? std::optional<Ent::Gen::BeamTargetGD>{}: std::optional<Ent::Gen::BeamTargetGD>(node->getUnionData());
        }
        inline Ent::Gen::BeamTargetGD Component::setBeamTargetGD() const
        {
            return Ent::Gen::BeamTargetGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ActorGD> Component::ActorGD() const
        {
            return strcmp(node->getUnionType(), "ActorGD") != 0? std::optional<Ent::Gen::ActorGD>{}: std::optional<Ent::Gen::ActorGD>(node->getUnionData());
        }
        inline Ent::Gen::ActorGD Component::setActorGD() const
        {
            return Ent::Gen::ActorGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CharacterPlatformGD> Component::CharacterPlatformGD() const
        {
            return strcmp(node->getUnionType(), "CharacterPlatformGD") != 0? std::optional<Ent::Gen::CharacterPlatformGD>{}: std::optional<Ent::Gen::CharacterPlatformGD>(node->getUnionData());
        }
        inline Ent::Gen::CharacterPlatformGD Component::setCharacterPlatformGD() const
        {
            return Ent::Gen::CharacterPlatformGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ReviveSideSwitcherGD> Component::ReviveSideSwitcherGD() const
        {
            return strcmp(node->getUnionType(), "ReviveSideSwitcherGD") != 0? std::optional<Ent::Gen::ReviveSideSwitcherGD>{}: std::optional<Ent::Gen::ReviveSideSwitcherGD>(node->getUnionData());
        }
        inline Ent::Gen::ReviveSideSwitcherGD Component::setReviveSideSwitcherGD() const
        {
            return Ent::Gen::ReviveSideSwitcherGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EnergyPoolGD> Component::EnergyPoolGD() const
        {
            return strcmp(node->getUnionType(), "EnergyPoolGD") != 0? std::optional<Ent::Gen::EnergyPoolGD>{}: std::optional<Ent::Gen::EnergyPoolGD>(node->getUnionData());
        }
        inline Ent::Gen::EnergyPoolGD Component::setEnergyPoolGD() const
        {
            return Ent::Gen::EnergyPoolGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PlayerComponentGD> Component::PlayerComponentGD() const
        {
            return strcmp(node->getUnionType(), "PlayerComponentGD") != 0? std::optional<Ent::Gen::PlayerComponentGD>{}: std::optional<Ent::Gen::PlayerComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::PlayerComponentGD Component::setPlayerComponentGD() const
        {
            return Ent::Gen::PlayerComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::HotspotsGD> Component::HotspotsGD() const
        {
            return strcmp(node->getUnionType(), "HotspotsGD") != 0? std::optional<Ent::Gen::HotspotsGD>{}: std::optional<Ent::Gen::HotspotsGD>(node->getUnionData());
        }
        inline Ent::Gen::HotspotsGD Component::setHotspotsGD() const
        {
            return Ent::Gen::HotspotsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SmallActorSpawnerGD> Component::SmallActorSpawnerGD() const
        {
            return strcmp(node->getUnionType(), "SmallActorSpawnerGD") != 0? std::optional<Ent::Gen::SmallActorSpawnerGD>{}: std::optional<Ent::Gen::SmallActorSpawnerGD>(node->getUnionData());
        }
        inline Ent::Gen::SmallActorSpawnerGD Component::setSmallActorSpawnerGD() const
        {
            return Ent::Gen::SmallActorSpawnerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PathMotionControllerGD> Component::PathMotionControllerGD() const
        {
            return strcmp(node->getUnionType(), "PathMotionControllerGD") != 0? std::optional<Ent::Gen::PathMotionControllerGD>{}: std::optional<Ent::Gen::PathMotionControllerGD>(node->getUnionData());
        }
        inline Ent::Gen::PathMotionControllerGD Component::setPathMotionControllerGD() const
        {
            return Ent::Gen::PathMotionControllerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CreatureAIGD> Component::CreatureAIGD() const
        {
            return strcmp(node->getUnionType(), "CreatureAIGD") != 0? std::optional<Ent::Gen::CreatureAIGD>{}: std::optional<Ent::Gen::CreatureAIGD>(node->getUnionData());
        }
        inline Ent::Gen::CreatureAIGD Component::setCreatureAIGD() const
        {
            return Ent::Gen::CreatureAIGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CreatureUIGD> Component::CreatureUIGD() const
        {
            return strcmp(node->getUnionType(), "CreatureUIGD") != 0? std::optional<Ent::Gen::CreatureUIGD>{}: std::optional<Ent::Gen::CreatureUIGD>(node->getUnionData());
        }
        inline Ent::Gen::CreatureUIGD Component::setCreatureUIGD() const
        {
            return Ent::Gen::CreatureUIGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SoundEmitterGD> Component::SoundEmitterGD() const
        {
            return strcmp(node->getUnionType(), "SoundEmitterGD") != 0? std::optional<Ent::Gen::SoundEmitterGD>{}: std::optional<Ent::Gen::SoundEmitterGD>(node->getUnionData());
        }
        inline Ent::Gen::SoundEmitterGD Component::setSoundEmitterGD() const
        {
            return Ent::Gen::SoundEmitterGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EnergySourceGD> Component::EnergySourceGD() const
        {
            return strcmp(node->getUnionType(), "EnergySourceGD") != 0? std::optional<Ent::Gen::EnergySourceGD>{}: std::optional<Ent::Gen::EnergySourceGD>(node->getUnionData());
        }
        inline Ent::Gen::EnergySourceGD Component::setEnergySourceGD() const
        {
            return Ent::Gen::EnergySourceGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ClothAnimationGD> Component::ClothAnimationGD() const
        {
            return strcmp(node->getUnionType(), "ClothAnimationGD") != 0? std::optional<Ent::Gen::ClothAnimationGD>{}: std::optional<Ent::Gen::ClothAnimationGD>(node->getUnionData());
        }
        inline Ent::Gen::ClothAnimationGD Component::setClothAnimationGD() const
        {
            return Ent::Gen::ClothAnimationGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::CreatureGD> Component::CreatureGD() const
        {
            return strcmp(node->getUnionType(), "CreatureGD") != 0? std::optional<Ent::Gen::CreatureGD>{}: std::optional<Ent::Gen::CreatureGD>(node->getUnionData());
        }
        inline Ent::Gen::CreatureGD Component::setCreatureGD() const
        {
            return Ent::Gen::CreatureGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::HitTriggerGD> Component::HitTriggerGD() const
        {
            return strcmp(node->getUnionType(), "HitTriggerGD") != 0? std::optional<Ent::Gen::HitTriggerGD>{}: std::optional<Ent::Gen::HitTriggerGD>(node->getUnionData());
        }
        inline Ent::Gen::HitTriggerGD Component::setHitTriggerGD() const
        {
            return Ent::Gen::HitTriggerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ProjectileShooterGD> Component::ProjectileShooterGD() const
        {
            return strcmp(node->getUnionType(), "ProjectileShooterGD") != 0? std::optional<Ent::Gen::ProjectileShooterGD>{}: std::optional<Ent::Gen::ProjectileShooterGD>(node->getUnionData());
        }
        inline Ent::Gen::ProjectileShooterGD Component::setProjectileShooterGD() const
        {
            return Ent::Gen::ProjectileShooterGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::LightComponentGD> Component::LightComponentGD() const
        {
            return strcmp(node->getUnionType(), "LightComponentGD") != 0? std::optional<Ent::Gen::LightComponentGD>{}: std::optional<Ent::Gen::LightComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::LightComponentGD Component::setLightComponentGD() const
        {
            return Ent::Gen::LightComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::MounterGD> Component::MounterGD() const
        {
            return strcmp(node->getUnionType(), "MounterGD") != 0? std::optional<Ent::Gen::MounterGD>{}: std::optional<Ent::Gen::MounterGD>(node->getUnionData());
        }
        inline Ent::Gen::MounterGD Component::setMounterGD() const
        {
            return Ent::Gen::MounterGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AttackTriggerGD> Component::AttackTriggerGD() const
        {
            return strcmp(node->getUnionType(), "AttackTriggerGD") != 0? std::optional<Ent::Gen::AttackTriggerGD>{}: std::optional<Ent::Gen::AttackTriggerGD>(node->getUnionData());
        }
        inline Ent::Gen::AttackTriggerGD Component::setAttackTriggerGD() const
        {
            return Ent::Gen::AttackTriggerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PossessableGPEGD> Component::PossessableGPEGD() const
        {
            return strcmp(node->getUnionType(), "PossessableGPEGD") != 0? std::optional<Ent::Gen::PossessableGPEGD>{}: std::optional<Ent::Gen::PossessableGPEGD>(node->getUnionData());
        }
        inline Ent::Gen::PossessableGPEGD Component::setPossessableGPEGD() const
        {
            return Ent::Gen::PossessableGPEGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::OutfitGD> Component::OutfitGD() const
        {
            return strcmp(node->getUnionType(), "OutfitGD") != 0? std::optional<Ent::Gen::OutfitGD>{}: std::optional<Ent::Gen::OutfitGD>(node->getUnionData());
        }
        inline Ent::Gen::OutfitGD Component::setOutfitGD() const
        {
            return Ent::Gen::OutfitGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::BreakableGD> Component::BreakableGD() const
        {
            return strcmp(node->getUnionType(), "BreakableGD") != 0? std::optional<Ent::Gen::BreakableGD>{}: std::optional<Ent::Gen::BreakableGD>(node->getUnionData());
        }
        inline Ent::Gen::BreakableGD Component::setBreakableGD() const
        {
            return Ent::Gen::BreakableGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PathNodeGD> Component::PathNodeGD() const
        {
            return strcmp(node->getUnionType(), "PathNodeGD") != 0? std::optional<Ent::Gen::PathNodeGD>{}: std::optional<Ent::Gen::PathNodeGD>(node->getUnionData());
        }
        inline Ent::Gen::PathNodeGD Component::setPathNodeGD() const
        {
            return Ent::Gen::PathNodeGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::VelocityObstacleGD> Component::VelocityObstacleGD() const
        {
            return strcmp(node->getUnionType(), "VelocityObstacleGD") != 0? std::optional<Ent::Gen::VelocityObstacleGD>{}: std::optional<Ent::Gen::VelocityObstacleGD>(node->getUnionData());
        }
        inline Ent::Gen::VelocityObstacleGD Component::setVelocityObstacleGD() const
        {
            return Ent::Gen::VelocityObstacleGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ShapeshiftStatueGD> Component::ShapeshiftStatueGD() const
        {
            return strcmp(node->getUnionType(), "ShapeshiftStatueGD") != 0? std::optional<Ent::Gen::ShapeshiftStatueGD>{}: std::optional<Ent::Gen::ShapeshiftStatueGD>(node->getUnionData());
        }
        inline Ent::Gen::ShapeshiftStatueGD Component::setShapeshiftStatueGD() const
        {
            return Ent::Gen::ShapeshiftStatueGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::RagdollGD> Component::RagdollGD() const
        {
            return strcmp(node->getUnionType(), "RagdollGD") != 0? std::optional<Ent::Gen::RagdollGD>{}: std::optional<Ent::Gen::RagdollGD>(node->getUnionData());
        }
        inline Ent::Gen::RagdollGD Component::setRagdollGD() const
        {
            return Ent::Gen::RagdollGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD> Component::AnimationPhysicsChainConstraintsGD() const
        {
            return strcmp(node->getUnionType(), "AnimationPhysicsChainConstraintsGD") != 0? std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD>{}: std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationPhysicsChainConstraintsGD Component::setAnimationPhysicsChainConstraintsGD() const
        {
            return Ent::Gen::AnimationPhysicsChainConstraintsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ScriptComponentGD> Component::ScriptComponentGD() const
        {
            return strcmp(node->getUnionType(), "ScriptComponentGD") != 0? std::optional<Ent::Gen::ScriptComponentGD>{}: std::optional<Ent::Gen::ScriptComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::ScriptComponentGD Component::setScriptComponentGD() const
        {
            return Ent::Gen::ScriptComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::FluidToRegenInjectorGD> Component::FluidToRegenInjectorGD() const
        {
            return strcmp(node->getUnionType(), "FluidToRegenInjectorGD") != 0? std::optional<Ent::Gen::FluidToRegenInjectorGD>{}: std::optional<Ent::Gen::FluidToRegenInjectorGD>(node->getUnionData());
        }
        inline Ent::Gen::FluidToRegenInjectorGD Component::setFluidToRegenInjectorGD() const
        {
            return Ent::Gen::FluidToRegenInjectorGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PerceivableGD> Component::PerceivableGD() const
        {
            return strcmp(node->getUnionType(), "PerceivableGD") != 0? std::optional<Ent::Gen::PerceivableGD>{}: std::optional<Ent::Gen::PerceivableGD>(node->getUnionData());
        }
        inline Ent::Gen::PerceivableGD Component::setPerceivableGD() const
        {
            return Ent::Gen::PerceivableGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::InventoryGD> Component::InventoryGD() const
        {
            return strcmp(node->getUnionType(), "InventoryGD") != 0? std::optional<Ent::Gen::InventoryGD>{}: std::optional<Ent::Gen::InventoryGD>(node->getUnionData());
        }
        inline Ent::Gen::InventoryGD Component::setInventoryGD() const
        {
            return Ent::Gen::InventoryGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ItemHolderGD> Component::ItemHolderGD() const
        {
            return strcmp(node->getUnionType(), "ItemHolderGD") != 0? std::optional<Ent::Gen::ItemHolderGD>{}: std::optional<Ent::Gen::ItemHolderGD>(node->getUnionData());
        }
        inline Ent::Gen::ItemHolderGD Component::setItemHolderGD() const
        {
            return Ent::Gen::ItemHolderGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PathGD> Component::PathGD() const
        {
            return strcmp(node->getUnionType(), "PathGD") != 0? std::optional<Ent::Gen::PathGD>{}: std::optional<Ent::Gen::PathGD>(node->getUnionData());
        }
        inline Ent::Gen::PathGD Component::setPathGD() const
        {
            return Ent::Gen::PathGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PerceiverGD> Component::PerceiverGD() const
        {
            return strcmp(node->getUnionType(), "PerceiverGD") != 0? std::optional<Ent::Gen::PerceiverGD>{}: std::optional<Ent::Gen::PerceiverGD>(node->getUnionData());
        }
        inline Ent::Gen::PerceiverGD Component::setPerceiverGD() const
        {
            return Ent::Gen::PerceiverGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::DummyComponentGD> Component::DummyComponentGD() const
        {
            return strcmp(node->getUnionType(), "DummyComponentGD") != 0? std::optional<Ent::Gen::DummyComponentGD>{}: std::optional<Ent::Gen::DummyComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::DummyComponentGD Component::setDummyComponentGD() const
        {
            return Ent::Gen::DummyComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::FluidNavMeshTaggerGD> Component::FluidNavMeshTaggerGD() const
        {
            return strcmp(node->getUnionType(), "FluidNavMeshTaggerGD") != 0? std::optional<Ent::Gen::FluidNavMeshTaggerGD>{}: std::optional<Ent::Gen::FluidNavMeshTaggerGD>(node->getUnionData());
        }
        inline Ent::Gen::FluidNavMeshTaggerGD Component::setFluidNavMeshTaggerGD() const
        {
            return Ent::Gen::FluidNavMeshTaggerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EnergySpoutGD> Component::EnergySpoutGD() const
        {
            return strcmp(node->getUnionType(), "EnergySpoutGD") != 0? std::optional<Ent::Gen::EnergySpoutGD>{}: std::optional<Ent::Gen::EnergySpoutGD>(node->getUnionData());
        }
        inline Ent::Gen::EnergySpoutGD Component::setEnergySpoutGD() const
        {
            return Ent::Gen::EnergySpoutGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PickableDistributorComponentGD> Component::PickableDistributorComponentGD() const
        {
            return strcmp(node->getUnionType(), "PickableDistributorComponentGD") != 0? std::optional<Ent::Gen::PickableDistributorComponentGD>{}: std::optional<Ent::Gen::PickableDistributorComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::PickableDistributorComponentGD Component::setPickableDistributorComponentGD() const
        {
            return Ent::Gen::PickableDistributorComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::ShamanItemGD> Component::ShamanItemGD() const
        {
            return strcmp(node->getUnionType(), "ShamanItemGD") != 0? std::optional<Ent::Gen::ShamanItemGD>{}: std::optional<Ent::Gen::ShamanItemGD>(node->getUnionData());
        }
        inline Ent::Gen::ShamanItemGD Component::setShamanItemGD() const
        {
            return Ent::Gen::ShamanItemGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TeamGD> Component::TeamGD() const
        {
            return strcmp(node->getUnionType(), "TeamGD") != 0? std::optional<Ent::Gen::TeamGD>{}: std::optional<Ent::Gen::TeamGD>(node->getUnionData());
        }
        inline Ent::Gen::TeamGD Component::setTeamGD() const
        {
            return Ent::Gen::TeamGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SmallActorGD> Component::SmallActorGD() const
        {
            return strcmp(node->getUnionType(), "SmallActorGD") != 0? std::optional<Ent::Gen::SmallActorGD>{}: std::optional<Ent::Gen::SmallActorGD>(node->getUnionData());
        }
        inline Ent::Gen::SmallActorGD Component::setSmallActorGD() const
        {
            return Ent::Gen::SmallActorGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PhysicsMeshProviderGD> Component::PhysicsMeshProviderGD() const
        {
            return strcmp(node->getUnionType(), "PhysicsMeshProviderGD") != 0? std::optional<Ent::Gen::PhysicsMeshProviderGD>{}: std::optional<Ent::Gen::PhysicsMeshProviderGD>(node->getUnionData());
        }
        inline Ent::Gen::PhysicsMeshProviderGD Component::setPhysicsMeshProviderGD() const
        {
            return Ent::Gen::PhysicsMeshProviderGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SideMapGateGD> Component::SideMapGateGD() const
        {
            return strcmp(node->getUnionType(), "SideMapGateGD") != 0? std::optional<Ent::Gen::SideMapGateGD>{}: std::optional<Ent::Gen::SideMapGateGD>(node->getUnionData());
        }
        inline Ent::Gen::SideMapGateGD Component::setSideMapGateGD() const
        {
            return Ent::Gen::SideMapGateGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::HeightMapComponentGD> Component::HeightMapComponentGD() const
        {
            return strcmp(node->getUnionType(), "HeightMapComponentGD") != 0? std::optional<Ent::Gen::HeightMapComponentGD>{}: std::optional<Ent::Gen::HeightMapComponentGD>(node->getUnionData());
        }
        inline Ent::Gen::HeightMapComponentGD Component::setHeightMapComponentGD() const
        {
            return Ent::Gen::HeightMapComponentGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::MountIKControllerGD> Component::MountIKControllerGD() const
        {
            return strcmp(node->getUnionType(), "MountIKControllerGD") != 0? std::optional<Ent::Gen::MountIKControllerGD>{}: std::optional<Ent::Gen::MountIKControllerGD>(node->getUnionData());
        }
        inline Ent::Gen::MountIKControllerGD Component::setMountIKControllerGD() const
        {
            return Ent::Gen::MountIKControllerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::StaffVertebrasGD> Component::StaffVertebrasGD() const
        {
            return strcmp(node->getUnionType(), "StaffVertebrasGD") != 0? std::optional<Ent::Gen::StaffVertebrasGD>{}: std::optional<Ent::Gen::StaffVertebrasGD>(node->getUnionData());
        }
        inline Ent::Gen::StaffVertebrasGD Component::setStaffVertebrasGD() const
        {
            return Ent::Gen::StaffVertebrasGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::SensorControllerGD> Component::SensorControllerGD() const
        {
            return strcmp(node->getUnionType(), "SensorControllerGD") != 0? std::optional<Ent::Gen::SensorControllerGD>{}: std::optional<Ent::Gen::SensorControllerGD>(node->getUnionData());
        }
        inline Ent::Gen::SensorControllerGD Component::setSensorControllerGD() const
        {
            return Ent::Gen::SensorControllerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::BoidsGD> Component::BoidsGD() const
        {
            return strcmp(node->getUnionType(), "BoidsGD") != 0? std::optional<Ent::Gen::BoidsGD>{}: std::optional<Ent::Gen::BoidsGD>(node->getUnionData());
        }
        inline Ent::Gen::BoidsGD Component::setBoidsGD() const
        {
            return Ent::Gen::BoidsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationTreeConstraintsGD> Component::AnimationTreeConstraintsGD() const
        {
            return strcmp(node->getUnionType(), "AnimationTreeConstraintsGD") != 0? std::optional<Ent::Gen::AnimationTreeConstraintsGD>{}: std::optional<Ent::Gen::AnimationTreeConstraintsGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationTreeConstraintsGD Component::setAnimationTreeConstraintsGD() const
        {
            return Ent::Gen::AnimationTreeConstraintsGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::DistanceTriggerGD> Component::DistanceTriggerGD() const
        {
            return strcmp(node->getUnionType(), "DistanceTriggerGD") != 0? std::optional<Ent::Gen::DistanceTriggerGD>{}: std::optional<Ent::Gen::DistanceTriggerGD>(node->getUnionData());
        }
        inline Ent::Gen::DistanceTriggerGD Component::setDistanceTriggerGD() const
        {
            return Ent::Gen::DistanceTriggerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::QuickCreatureSwitchGD> Component::QuickCreatureSwitchGD() const
        {
            return strcmp(node->getUnionType(), "QuickCreatureSwitchGD") != 0? std::optional<Ent::Gen::QuickCreatureSwitchGD>{}: std::optional<Ent::Gen::QuickCreatureSwitchGD>(node->getUnionData());
        }
        inline Ent::Gen::QuickCreatureSwitchGD Component::setQuickCreatureSwitchGD() const
        {
            return Ent::Gen::QuickCreatureSwitchGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EnergyProbeGD> Component::EnergyProbeGD() const
        {
            return strcmp(node->getUnionType(), "EnergyProbeGD") != 0? std::optional<Ent::Gen::EnergyProbeGD>{}: std::optional<Ent::Gen::EnergyProbeGD>(node->getUnionData());
        }
        inline Ent::Gen::EnergyProbeGD Component::setEnergyProbeGD() const
        {
            return Ent::Gen::EnergyProbeGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::RespawnPlaceGD> Component::RespawnPlaceGD() const
        {
            return strcmp(node->getUnionType(), "RespawnPlaceGD") != 0? std::optional<Ent::Gen::RespawnPlaceGD>{}: std::optional<Ent::Gen::RespawnPlaceGD>(node->getUnionData());
        }
        inline Ent::Gen::RespawnPlaceGD Component::setRespawnPlaceGD() const
        {
            return Ent::Gen::RespawnPlaceGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::OutfitWearerGD> Component::OutfitWearerGD() const
        {
            return strcmp(node->getUnionType(), "OutfitWearerGD") != 0? std::optional<Ent::Gen::OutfitWearerGD>{}: std::optional<Ent::Gen::OutfitWearerGD>(node->getUnionData());
        }
        inline Ent::Gen::OutfitWearerGD Component::setOutfitWearerGD() const
        {
            return Ent::Gen::OutfitWearerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::VoxelSimulationGD> Component::VoxelSimulationGD() const
        {
            return strcmp(node->getUnionType(), "VoxelSimulationGD") != 0? std::optional<Ent::Gen::VoxelSimulationGD>{}: std::optional<Ent::Gen::VoxelSimulationGD>(node->getUnionData());
        }
        inline Ent::Gen::VoxelSimulationGD Component::setVoxelSimulationGD() const
        {
            return Ent::Gen::VoxelSimulationGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationModelGD> Component::AnimationModelGD() const
        {
            return strcmp(node->getUnionType(), "AnimationModelGD") != 0? std::optional<Ent::Gen::AnimationModelGD>{}: std::optional<Ent::Gen::AnimationModelGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationModelGD Component::setAnimationModelGD() const
        {
            return Ent::Gen::AnimationModelGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::TriggerEventCameraGD> Component::TriggerEventCameraGD() const
        {
            return strcmp(node->getUnionType(), "TriggerEventCameraGD") != 0? std::optional<Ent::Gen::TriggerEventCameraGD>{}: std::optional<Ent::Gen::TriggerEventCameraGD>(node->getUnionData());
        }
        inline Ent::Gen::TriggerEventCameraGD Component::setTriggerEventCameraGD() const
        {
            return Ent::Gen::TriggerEventCameraGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::AnimationPlaylistGD> Component::AnimationPlaylistGD() const
        {
            return strcmp(node->getUnionType(), "AnimationPlaylistGD") != 0? std::optional<Ent::Gen::AnimationPlaylistGD>{}: std::optional<Ent::Gen::AnimationPlaylistGD>(node->getUnionData());
        }
        inline Ent::Gen::AnimationPlaylistGD Component::setAnimationPlaylistGD() const
        {
            return Ent::Gen::AnimationPlaylistGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::MeshNavigationInfosGD> Component::MeshNavigationInfosGD() const
        {
            return strcmp(node->getUnionType(), "MeshNavigationInfosGD") != 0? std::optional<Ent::Gen::MeshNavigationInfosGD>{}: std::optional<Ent::Gen::MeshNavigationInfosGD>(node->getUnionData());
        }
        inline Ent::Gen::MeshNavigationInfosGD Component::setMeshNavigationInfosGD() const
        {
            return Ent::Gen::MeshNavigationInfosGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::PhysicsTriggerGD> Component::PhysicsTriggerGD() const
        {
            return strcmp(node->getUnionType(), "PhysicsTriggerGD") != 0? std::optional<Ent::Gen::PhysicsTriggerGD>{}: std::optional<Ent::Gen::PhysicsTriggerGD>(node->getUnionData());
        }
        inline Ent::Gen::PhysicsTriggerGD Component::setPhysicsTriggerGD() const
        {
            return Ent::Gen::PhysicsTriggerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::EnergyNetworkListenerGD> Component::EnergyNetworkListenerGD() const
        {
            return strcmp(node->getUnionType(), "EnergyNetworkListenerGD") != 0? std::optional<Ent::Gen::EnergyNetworkListenerGD>{}: std::optional<Ent::Gen::EnergyNetworkListenerGD>(node->getUnionData());
        }
        inline Ent::Gen::EnergyNetworkListenerGD Component::setEnergyNetworkListenerGD() const
        {
            return Ent::Gen::EnergyNetworkListenerGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::MissionHolderGD> Component::MissionHolderGD() const
        {
            return strcmp(node->getUnionType(), "MissionHolderGD") != 0? std::optional<Ent::Gen::MissionHolderGD>{}: std::optional<Ent::Gen::MissionHolderGD>(node->getUnionData());
        }
        inline Ent::Gen::MissionHolderGD Component::setMissionHolderGD() const
        {
            return Ent::Gen::MissionHolderGD(node->setUnionType("Component"));
        }
        inline std::optional<Ent::Gen::RegenSwitcherGD> Component::RegenSwitcherGD() const
        {
            return strcmp(node->getUnionType(), "RegenSwitcherGD") != 0? std::optional<Ent::Gen::RegenSwitcherGD>{}: std::optional<Ent::Gen::RegenSwitcherGD>(node->getUnionData());
        }
        inline Ent::Gen::RegenSwitcherGD Component::setRegenSwitcherGD() const
        {
            return Ent::Gen::RegenSwitcherGD(node->setUnionType("Component"));
        }
        // Object_Components
        inline char const* Object_Components::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::StaticObjectGD> Object_Components::StaticObjectGD() const
        {
            auto sub = getSubNode("StaticObjectGD");
            return sub == nullptr? std::optional<Ent::Gen::StaticObjectGD>{}: std::optional<Ent::Gen::StaticObjectGD>(getSubNode("StaticObjectGD"));
        }
        inline Ent::Gen::StaticObjectGD Object_Components::addStaticObjectGD() const
        {
            return Ent::Gen::StaticObjectGD(addSubNode("StaticObjectGD"));
        }
        inline std::optional<Ent::Gen::AnimationControllerGD> Object_Components::AnimationControllerGD() const
        {
            auto sub = getSubNode("AnimationControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationControllerGD>{}: std::optional<Ent::Gen::AnimationControllerGD>(getSubNode("AnimationControllerGD"));
        }
        inline Ent::Gen::AnimationControllerGD Object_Components::addAnimationControllerGD() const
        {
            return Ent::Gen::AnimationControllerGD(addSubNode("AnimationControllerGD"));
        }
        inline std::optional<Ent::Gen::PhysicsDataGD> Object_Components::PhysicsDataGD() const
        {
            auto sub = getSubNode("PhysicsDataGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsDataGD>{}: std::optional<Ent::Gen::PhysicsDataGD>(getSubNode("PhysicsDataGD"));
        }
        inline Ent::Gen::PhysicsDataGD Object_Components::addPhysicsDataGD() const
        {
            return Ent::Gen::PhysicsDataGD(addSubNode("PhysicsDataGD"));
        }
        inline std::optional<Ent::Gen::VisualGD> Object_Components::VisualGD() const
        {
            auto sub = getSubNode("VisualGD");
            return sub == nullptr? std::optional<Ent::Gen::VisualGD>{}: std::optional<Ent::Gen::VisualGD>(getSubNode("VisualGD"));
        }
        inline Ent::Gen::VisualGD Object_Components::addVisualGD() const
        {
            return Ent::Gen::VisualGD(addSubNode("VisualGD"));
        }
        inline std::optional<Ent::Gen::TransformGD> Object_Components::TransformGD() const
        {
            auto sub = getSubNode("TransformGD");
            return sub == nullptr? std::optional<Ent::Gen::TransformGD>{}: std::optional<Ent::Gen::TransformGD>(getSubNode("TransformGD"));
        }
        inline Ent::Gen::TransformGD Object_Components::addTransformGD() const
        {
            return Ent::Gen::TransformGD(addSubNode("TransformGD"));
        }
        inline std::optional<Ent::Gen::TerrainGD> Object_Components::TerrainGD() const
        {
            auto sub = getSubNode("TerrainGD");
            return sub == nullptr? std::optional<Ent::Gen::TerrainGD>{}: std::optional<Ent::Gen::TerrainGD>(getSubNode("TerrainGD"));
        }
        inline Ent::Gen::TerrainGD Object_Components::addTerrainGD() const
        {
            return Ent::Gen::TerrainGD(addSubNode("TerrainGD"));
        }
        inline std::optional<Ent::Gen::PhysicsGD> Object_Components::PhysicsGD() const
        {
            auto sub = getSubNode("PhysicsGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsGD>{}: std::optional<Ent::Gen::PhysicsGD>(getSubNode("PhysicsGD"));
        }
        inline Ent::Gen::PhysicsGD Object_Components::addPhysicsGD() const
        {
            return Ent::Gen::PhysicsGD(addSubNode("PhysicsGD"));
        }
        inline std::optional<Ent::Gen::CustomThumbnail> Object_Components::CustomThumbnail() const
        {
            auto sub = getSubNode("CustomThumbnail");
            return sub == nullptr? std::optional<Ent::Gen::CustomThumbnail>{}: std::optional<Ent::Gen::CustomThumbnail>(getSubNode("CustomThumbnail"));
        }
        inline Ent::Gen::CustomThumbnail Object_Components::addCustomThumbnail() const
        {
            return Ent::Gen::CustomThumbnail(addSubNode("CustomThumbnail"));
        }
        inline std::optional<Ent::Gen::HeightObj> Object_Components::HeightObj() const
        {
            auto sub = getSubNode("HeightObj");
            return sub == nullptr? std::optional<Ent::Gen::HeightObj>{}: std::optional<Ent::Gen::HeightObj>(getSubNode("HeightObj"));
        }
        inline Ent::Gen::HeightObj Object_Components::addHeightObj() const
        {
            return Ent::Gen::HeightObj(addSubNode("HeightObj"));
        }
        inline std::optional<Ent::Gen::LDPrimitive> Object_Components::LDPrimitive() const
        {
            auto sub = getSubNode("LDPrimitive");
            return sub == nullptr? std::optional<Ent::Gen::LDPrimitive>{}: std::optional<Ent::Gen::LDPrimitive>(getSubNode("LDPrimitive"));
        }
        inline Ent::Gen::LDPrimitive Object_Components::addLDPrimitive() const
        {
            return Ent::Gen::LDPrimitive(addSubNode("LDPrimitive"));
        }
        inline std::optional<Ent::Gen::Mesh> Object_Components::Mesh() const
        {
            auto sub = getSubNode("Mesh");
            return sub == nullptr? std::optional<Ent::Gen::Mesh>{}: std::optional<Ent::Gen::Mesh>(getSubNode("Mesh"));
        }
        inline Ent::Gen::Mesh Object_Components::addMesh() const
        {
            return Ent::Gen::Mesh(addSubNode("Mesh"));
        }
        inline std::optional<Ent::Gen::MultiThumbnail> Object_Components::MultiThumbnail() const
        {
            auto sub = getSubNode("MultiThumbnail");
            return sub == nullptr? std::optional<Ent::Gen::MultiThumbnail>{}: std::optional<Ent::Gen::MultiThumbnail>(getSubNode("MultiThumbnail"));
        }
        inline Ent::Gen::MultiThumbnail Object_Components::addMultiThumbnail() const
        {
            return Ent::Gen::MultiThumbnail(addSubNode("MultiThumbnail"));
        }
        inline std::optional<Ent::Gen::NetworkLink> Object_Components::NetworkLink() const
        {
            auto sub = getSubNode("NetworkLink");
            return sub == nullptr? std::optional<Ent::Gen::NetworkLink>{}: std::optional<Ent::Gen::NetworkLink>(getSubNode("NetworkLink"));
        }
        inline Ent::Gen::NetworkLink Object_Components::addNetworkLink() const
        {
            return Ent::Gen::NetworkLink(addSubNode("NetworkLink"));
        }
        inline std::optional<Ent::Gen::NetworkNode> Object_Components::NetworkNode() const
        {
            auto sub = getSubNode("NetworkNode");
            return sub == nullptr? std::optional<Ent::Gen::NetworkNode>{}: std::optional<Ent::Gen::NetworkNode>(getSubNode("NetworkNode"));
        }
        inline Ent::Gen::NetworkNode Object_Components::addNetworkNode() const
        {
            return Ent::Gen::NetworkNode(addSubNode("NetworkNode"));
        }
        inline std::optional<Ent::Gen::NotVisibleInSubscene> Object_Components::NotVisibleInSubscene() const
        {
            auto sub = getSubNode("NotVisibleInSubscene");
            return sub == nullptr? std::optional<Ent::Gen::NotVisibleInSubscene>{}: std::optional<Ent::Gen::NotVisibleInSubscene>(getSubNode("NotVisibleInSubscene"));
        }
        inline Ent::Gen::NotVisibleInSubscene Object_Components::addNotVisibleInSubscene() const
        {
            return Ent::Gen::NotVisibleInSubscene(addSubNode("NotVisibleInSubscene"));
        }
        inline std::optional<Ent::Gen::SeedPatch> Object_Components::SeedPatch() const
        {
            auto sub = getSubNode("SeedPatch");
            return sub == nullptr? std::optional<Ent::Gen::SeedPatch>{}: std::optional<Ent::Gen::SeedPatch>(getSubNode("SeedPatch"));
        }
        inline Ent::Gen::SeedPatch Object_Components::addSeedPatch() const
        {
            return Ent::Gen::SeedPatch(addSubNode("SeedPatch"));
        }
        inline std::optional<Ent::Gen::StickToTerrain> Object_Components::StickToTerrain() const
        {
            auto sub = getSubNode("StickToTerrain");
            return sub == nullptr? std::optional<Ent::Gen::StickToTerrain>{}: std::optional<Ent::Gen::StickToTerrain>(getSubNode("StickToTerrain"));
        }
        inline Ent::Gen::StickToTerrain Object_Components::addStickToTerrain() const
        {
            return Ent::Gen::StickToTerrain(addSubNode("StickToTerrain"));
        }
        inline std::optional<Ent::Gen::SubScene> Object_Components::SubScene() const
        {
            auto sub = getSubNode("SubScene");
            return sub == nullptr? std::optional<Ent::Gen::SubScene>{}: std::optional<Ent::Gen::SubScene>(getSubNode("SubScene"));
        }
        inline Ent::Gen::SubScene Object_Components::addSubScene() const
        {
            return Ent::Gen::SubScene(addSubNode("SubScene"));
        }
        inline std::optional<Ent::Gen::SystemicCreature> Object_Components::SystemicCreature() const
        {
            auto sub = getSubNode("SystemicCreature");
            return sub == nullptr? std::optional<Ent::Gen::SystemicCreature>{}: std::optional<Ent::Gen::SystemicCreature>(getSubNode("SystemicCreature"));
        }
        inline Ent::Gen::SystemicCreature Object_Components::addSystemicCreature() const
        {
            return Ent::Gen::SystemicCreature(addSubNode("SystemicCreature"));
        }
        inline std::optional<Ent::Gen::TerrainSurfaceObject> Object_Components::TerrainSurfaceObject() const
        {
            auto sub = getSubNode("TerrainSurfaceObject");
            return sub == nullptr? std::optional<Ent::Gen::TerrainSurfaceObject>{}: std::optional<Ent::Gen::TerrainSurfaceObject>(getSubNode("TerrainSurfaceObject"));
        }
        inline Ent::Gen::TerrainSurfaceObject Object_Components::addTerrainSurfaceObject() const
        {
            return Ent::Gen::TerrainSurfaceObject(addSubNode("TerrainSurfaceObject"));
        }
        inline std::optional<Ent::Gen::TestArrays> Object_Components::TestArrays() const
        {
            auto sub = getSubNode("TestArrays");
            return sub == nullptr? std::optional<Ent::Gen::TestArrays>{}: std::optional<Ent::Gen::TestArrays>(getSubNode("TestArrays"));
        }
        inline Ent::Gen::TestArrays Object_Components::addTestArrays() const
        {
            return Ent::Gen::TestArrays(addSubNode("TestArrays"));
        }
        inline std::optional<Ent::Gen::TestCreature> Object_Components::TestCreature() const
        {
            auto sub = getSubNode("TestCreature");
            return sub == nullptr? std::optional<Ent::Gen::TestCreature>{}: std::optional<Ent::Gen::TestCreature>(getSubNode("TestCreature"));
        }
        inline Ent::Gen::TestCreature Object_Components::addTestCreature() const
        {
            return Ent::Gen::TestCreature(addSubNode("TestCreature"));
        }
        inline std::optional<Ent::Gen::TestDefaultValues> Object_Components::TestDefaultValues() const
        {
            auto sub = getSubNode("TestDefaultValues");
            return sub == nullptr? std::optional<Ent::Gen::TestDefaultValues>{}: std::optional<Ent::Gen::TestDefaultValues>(getSubNode("TestDefaultValues"));
        }
        inline Ent::Gen::TestDefaultValues Object_Components::addTestDefaultValues() const
        {
            return Ent::Gen::TestDefaultValues(addSubNode("TestDefaultValues"));
        }
        inline std::optional<Ent::Gen::TestEntityRef> Object_Components::TestEntityRef() const
        {
            auto sub = getSubNode("TestEntityRef");
            return sub == nullptr? std::optional<Ent::Gen::TestEntityRef>{}: std::optional<Ent::Gen::TestEntityRef>(getSubNode("TestEntityRef"));
        }
        inline Ent::Gen::TestEntityRef Object_Components::addTestEntityRef() const
        {
            return Ent::Gen::TestEntityRef(addSubNode("TestEntityRef"));
        }
        inline std::optional<Ent::Gen::TestSetOfObject> Object_Components::TestSetOfObject() const
        {
            auto sub = getSubNode("TestSetOfObject");
            return sub == nullptr? std::optional<Ent::Gen::TestSetOfObject>{}: std::optional<Ent::Gen::TestSetOfObject>(getSubNode("TestSetOfObject"));
        }
        inline Ent::Gen::TestSetOfObject Object_Components::addTestSetOfObject() const
        {
            return Ent::Gen::TestSetOfObject(addSubNode("TestSetOfObject"));
        }
        inline std::optional<Ent::Gen::TestUnion> Object_Components::TestUnion() const
        {
            auto sub = getSubNode("TestUnion");
            return sub == nullptr? std::optional<Ent::Gen::TestUnion>{}: std::optional<Ent::Gen::TestUnion>(getSubNode("TestUnion"));
        }
        inline Ent::Gen::TestUnion Object_Components::addTestUnion() const
        {
            return Ent::Gen::TestUnion(addSubNode("TestUnion"));
        }
        inline std::optional<Ent::Gen::UnitTestComponent> Object_Components::UnitTestComponent() const
        {
            auto sub = getSubNode("UnitTestComponent");
            return sub == nullptr? std::optional<Ent::Gen::UnitTestComponent>{}: std::optional<Ent::Gen::UnitTestComponent>(getSubNode("UnitTestComponent"));
        }
        inline Ent::Gen::UnitTestComponent Object_Components::addUnitTestComponent() const
        {
            return Ent::Gen::UnitTestComponent(addSubNode("UnitTestComponent"));
        }
        inline std::optional<Ent::Gen::WildObject> Object_Components::WildObject() const
        {
            auto sub = getSubNode("WildObject");
            return sub == nullptr? std::optional<Ent::Gen::WildObject>{}: std::optional<Ent::Gen::WildObject>(getSubNode("WildObject"));
        }
        inline Ent::Gen::WildObject Object_Components::addWildObject() const
        {
            return Ent::Gen::WildObject(addSubNode("WildObject"));
        }
        inline std::optional<Ent::Gen::EnergyCrookGD> Object_Components::EnergyCrookGD() const
        {
            auto sub = getSubNode("EnergyCrookGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyCrookGD>{}: std::optional<Ent::Gen::EnergyCrookGD>(getSubNode("EnergyCrookGD"));
        }
        inline Ent::Gen::EnergyCrookGD Object_Components::addEnergyCrookGD() const
        {
            return Ent::Gen::EnergyCrookGD(addSubNode("EnergyCrookGD"));
        }
        inline std::optional<Ent::Gen::AIContextGD> Object_Components::AIContextGD() const
        {
            auto sub = getSubNode("AIContextGD");
            return sub == nullptr? std::optional<Ent::Gen::AIContextGD>{}: std::optional<Ent::Gen::AIContextGD>(getSubNode("AIContextGD"));
        }
        inline Ent::Gen::AIContextGD Object_Components::addAIContextGD() const
        {
            return Ent::Gen::AIContextGD(addSubNode("AIContextGD"));
        }
        inline std::optional<Ent::Gen::EventTriggerGD> Object_Components::EventTriggerGD() const
        {
            auto sub = getSubNode("EventTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::EventTriggerGD>{}: std::optional<Ent::Gen::EventTriggerGD>(getSubNode("EventTriggerGD"));
        }
        inline Ent::Gen::EventTriggerGD Object_Components::addEventTriggerGD() const
        {
            return Ent::Gen::EventTriggerGD(addSubNode("EventTriggerGD"));
        }
        inline std::optional<Ent::Gen::BeamGeneratorGD> Object_Components::BeamGeneratorGD() const
        {
            auto sub = getSubNode("BeamGeneratorGD");
            return sub == nullptr? std::optional<Ent::Gen::BeamGeneratorGD>{}: std::optional<Ent::Gen::BeamGeneratorGD>(getSubNode("BeamGeneratorGD"));
        }
        inline Ent::Gen::BeamGeneratorGD Object_Components::addBeamGeneratorGD() const
        {
            return Ent::Gen::BeamGeneratorGD(addSubNode("BeamGeneratorGD"));
        }
        inline std::optional<Ent::Gen::WorldScalePathFindGD> Object_Components::WorldScalePathFindGD() const
        {
            auto sub = getSubNode("WorldScalePathFindGD");
            return sub == nullptr? std::optional<Ent::Gen::WorldScalePathFindGD>{}: std::optional<Ent::Gen::WorldScalePathFindGD>(getSubNode("WorldScalePathFindGD"));
        }
        inline Ent::Gen::WorldScalePathFindGD Object_Components::addWorldScalePathFindGD() const
        {
            return Ent::Gen::WorldScalePathFindGD(addSubNode("WorldScalePathFindGD"));
        }
        inline std::optional<Ent::Gen::NetGD> Object_Components::NetGD() const
        {
            auto sub = getSubNode("NetGD");
            return sub == nullptr? std::optional<Ent::Gen::NetGD>{}: std::optional<Ent::Gen::NetGD>(getSubNode("NetGD"));
        }
        inline Ent::Gen::NetGD Object_Components::addNetGD() const
        {
            return Ent::Gen::NetGD(addSubNode("NetGD"));
        }
        inline std::optional<Ent::Gen::BittenGD> Object_Components::BittenGD() const
        {
            auto sub = getSubNode("BittenGD");
            return sub == nullptr? std::optional<Ent::Gen::BittenGD>{}: std::optional<Ent::Gen::BittenGD>(getSubNode("BittenGD"));
        }
        inline Ent::Gen::BittenGD Object_Components::addBittenGD() const
        {
            return Ent::Gen::BittenGD(addSubNode("BittenGD"));
        }
        inline std::optional<Ent::Gen::PathBoneAnimGD> Object_Components::PathBoneAnimGD() const
        {
            auto sub = getSubNode("PathBoneAnimGD");
            return sub == nullptr? std::optional<Ent::Gen::PathBoneAnimGD>{}: std::optional<Ent::Gen::PathBoneAnimGD>(getSubNode("PathBoneAnimGD"));
        }
        inline Ent::Gen::PathBoneAnimGD Object_Components::addPathBoneAnimGD() const
        {
            return Ent::Gen::PathBoneAnimGD(addSubNode("PathBoneAnimGD"));
        }
        inline std::optional<Ent::Gen::AnimationRegenConstraintsGD> Object_Components::AnimationRegenConstraintsGD() const
        {
            auto sub = getSubNode("AnimationRegenConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationRegenConstraintsGD>{}: std::optional<Ent::Gen::AnimationRegenConstraintsGD>(getSubNode("AnimationRegenConstraintsGD"));
        }
        inline Ent::Gen::AnimationRegenConstraintsGD Object_Components::addAnimationRegenConstraintsGD() const
        {
            return Ent::Gen::AnimationRegenConstraintsGD(addSubNode("AnimationRegenConstraintsGD"));
        }
        inline std::optional<Ent::Gen::HealPumpGD> Object_Components::HealPumpGD() const
        {
            auto sub = getSubNode("HealPumpGD");
            return sub == nullptr? std::optional<Ent::Gen::HealPumpGD>{}: std::optional<Ent::Gen::HealPumpGD>(getSubNode("HealPumpGD"));
        }
        inline Ent::Gen::HealPumpGD Object_Components::addHealPumpGD() const
        {
            return Ent::Gen::HealPumpGD(addSubNode("HealPumpGD"));
        }
        inline std::optional<Ent::Gen::GroundTypeSamplerGD> Object_Components::GroundTypeSamplerGD() const
        {
            auto sub = getSubNode("GroundTypeSamplerGD");
            return sub == nullptr? std::optional<Ent::Gen::GroundTypeSamplerGD>{}: std::optional<Ent::Gen::GroundTypeSamplerGD>(getSubNode("GroundTypeSamplerGD"));
        }
        inline Ent::Gen::GroundTypeSamplerGD Object_Components::addGroundTypeSamplerGD() const
        {
            return Ent::Gen::GroundTypeSamplerGD(addSubNode("GroundTypeSamplerGD"));
        }
        inline std::optional<Ent::Gen::UnifiedPhysicsDataGD> Object_Components::UnifiedPhysicsDataGD() const
        {
            auto sub = getSubNode("UnifiedPhysicsDataGD");
            return sub == nullptr? std::optional<Ent::Gen::UnifiedPhysicsDataGD>{}: std::optional<Ent::Gen::UnifiedPhysicsDataGD>(getSubNode("UnifiedPhysicsDataGD"));
        }
        inline Ent::Gen::UnifiedPhysicsDataGD Object_Components::addUnifiedPhysicsDataGD() const
        {
            return Ent::Gen::UnifiedPhysicsDataGD(addSubNode("UnifiedPhysicsDataGD"));
        }
        inline std::optional<Ent::Gen::FluidGD> Object_Components::FluidGD() const
        {
            auto sub = getSubNode("FluidGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidGD>{}: std::optional<Ent::Gen::FluidGD>(getSubNode("FluidGD"));
        }
        inline Ent::Gen::FluidGD Object_Components::addFluidGD() const
        {
            return Ent::Gen::FluidGD(addSubNode("FluidGD"));
        }
        inline std::optional<Ent::Gen::ProjectileGD> Object_Components::ProjectileGD() const
        {
            auto sub = getSubNode("ProjectileGD");
            return sub == nullptr? std::optional<Ent::Gen::ProjectileGD>{}: std::optional<Ent::Gen::ProjectileGD>(getSubNode("ProjectileGD"));
        }
        inline Ent::Gen::ProjectileGD Object_Components::addProjectileGD() const
        {
            return Ent::Gen::ProjectileGD(addSubNode("ProjectileGD"));
        }
        inline std::optional<Ent::Gen::CameraSetterGD> Object_Components::CameraSetterGD() const
        {
            auto sub = getSubNode("CameraSetterGD");
            return sub == nullptr? std::optional<Ent::Gen::CameraSetterGD>{}: std::optional<Ent::Gen::CameraSetterGD>(getSubNode("CameraSetterGD"));
        }
        inline Ent::Gen::CameraSetterGD Object_Components::addCameraSetterGD() const
        {
            return Ent::Gen::CameraSetterGD(addSubNode("CameraSetterGD"));
        }
        inline std::optional<Ent::Gen::AssemblyGD> Object_Components::AssemblyGD() const
        {
            auto sub = getSubNode("AssemblyGD");
            return sub == nullptr? std::optional<Ent::Gen::AssemblyGD>{}: std::optional<Ent::Gen::AssemblyGD>(getSubNode("AssemblyGD"));
        }
        inline Ent::Gen::AssemblyGD Object_Components::addAssemblyGD() const
        {
            return Ent::Gen::AssemblyGD(addSubNode("AssemblyGD"));
        }
        inline std::optional<Ent::Gen::SmoothScaleComponentGD> Object_Components::SmoothScaleComponentGD() const
        {
            auto sub = getSubNode("SmoothScaleComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::SmoothScaleComponentGD>{}: std::optional<Ent::Gen::SmoothScaleComponentGD>(getSubNode("SmoothScaleComponentGD"));
        }
        inline Ent::Gen::SmoothScaleComponentGD Object_Components::addSmoothScaleComponentGD() const
        {
            return Ent::Gen::SmoothScaleComponentGD(addSubNode("SmoothScaleComponentGD"));
        }
        inline std::optional<Ent::Gen::FluidViewGD> Object_Components::FluidViewGD() const
        {
            auto sub = getSubNode("FluidViewGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidViewGD>{}: std::optional<Ent::Gen::FluidViewGD>(getSubNode("FluidViewGD"));
        }
        inline Ent::Gen::FluidViewGD Object_Components::addFluidViewGD() const
        {
            return Ent::Gen::FluidViewGD(addSubNode("FluidViewGD"));
        }
        inline std::optional<Ent::Gen::RegenMeshGD> Object_Components::RegenMeshGD() const
        {
            auto sub = getSubNode("RegenMeshGD");
            return sub == nullptr? std::optional<Ent::Gen::RegenMeshGD>{}: std::optional<Ent::Gen::RegenMeshGD>(getSubNode("RegenMeshGD"));
        }
        inline Ent::Gen::RegenMeshGD Object_Components::addRegenMeshGD() const
        {
            return Ent::Gen::RegenMeshGD(addSubNode("RegenMeshGD"));
        }
        inline std::optional<Ent::Gen::ReviveEnergyGD> Object_Components::ReviveEnergyGD() const
        {
            auto sub = getSubNode("ReviveEnergyGD");
            return sub == nullptr? std::optional<Ent::Gen::ReviveEnergyGD>{}: std::optional<Ent::Gen::ReviveEnergyGD>(getSubNode("ReviveEnergyGD"));
        }
        inline Ent::Gen::ReviveEnergyGD Object_Components::addReviveEnergyGD() const
        {
            return Ent::Gen::ReviveEnergyGD(addSubNode("ReviveEnergyGD"));
        }
        inline std::optional<Ent::Gen::DebugGridGD> Object_Components::DebugGridGD() const
        {
            auto sub = getSubNode("DebugGridGD");
            return sub == nullptr? std::optional<Ent::Gen::DebugGridGD>{}: std::optional<Ent::Gen::DebugGridGD>(getSubNode("DebugGridGD"));
        }
        inline Ent::Gen::DebugGridGD Object_Components::addDebugGridGD() const
        {
            return Ent::Gen::DebugGridGD(addSubNode("DebugGridGD"));
        }
        inline std::optional<Ent::Gen::ChildEntityPoolComponentGD> Object_Components::ChildEntityPoolComponentGD() const
        {
            auto sub = getSubNode("ChildEntityPoolComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::ChildEntityPoolComponentGD>{}: std::optional<Ent::Gen::ChildEntityPoolComponentGD>(getSubNode("ChildEntityPoolComponentGD"));
        }
        inline Ent::Gen::ChildEntityPoolComponentGD Object_Components::addChildEntityPoolComponentGD() const
        {
            return Ent::Gen::ChildEntityPoolComponentGD(addSubNode("ChildEntityPoolComponentGD"));
        }
        inline std::optional<Ent::Gen::ProtoComponentGD> Object_Components::ProtoComponentGD() const
        {
            auto sub = getSubNode("ProtoComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::ProtoComponentGD>{}: std::optional<Ent::Gen::ProtoComponentGD>(getSubNode("ProtoComponentGD"));
        }
        inline Ent::Gen::ProtoComponentGD Object_Components::addProtoComponentGD() const
        {
            return Ent::Gen::ProtoComponentGD(addSubNode("ProtoComponentGD"));
        }
        inline std::optional<Ent::Gen::GameEffectSpawnerGD> Object_Components::GameEffectSpawnerGD() const
        {
            auto sub = getSubNode("GameEffectSpawnerGD");
            return sub == nullptr? std::optional<Ent::Gen::GameEffectSpawnerGD>{}: std::optional<Ent::Gen::GameEffectSpawnerGD>(getSubNode("GameEffectSpawnerGD"));
        }
        inline Ent::Gen::GameEffectSpawnerGD Object_Components::addGameEffectSpawnerGD() const
        {
            return Ent::Gen::GameEffectSpawnerGD(addSubNode("GameEffectSpawnerGD"));
        }
        inline std::optional<Ent::Gen::ClothGD> Object_Components::ClothGD() const
        {
            auto sub = getSubNode("ClothGD");
            return sub == nullptr? std::optional<Ent::Gen::ClothGD>{}: std::optional<Ent::Gen::ClothGD>(getSubNode("ClothGD"));
        }
        inline Ent::Gen::ClothGD Object_Components::addClothGD() const
        {
            return Ent::Gen::ClothGD(addSubNode("ClothGD"));
        }
        inline std::optional<Ent::Gen::FireSensorGD> Object_Components::FireSensorGD() const
        {
            auto sub = getSubNode("FireSensorGD");
            return sub == nullptr? std::optional<Ent::Gen::FireSensorGD>{}: std::optional<Ent::Gen::FireSensorGD>(getSubNode("FireSensorGD"));
        }
        inline Ent::Gen::FireSensorGD Object_Components::addFireSensorGD() const
        {
            return Ent::Gen::FireSensorGD(addSubNode("FireSensorGD"));
        }
        inline std::optional<Ent::Gen::HealerGD> Object_Components::HealerGD() const
        {
            auto sub = getSubNode("HealerGD");
            return sub == nullptr? std::optional<Ent::Gen::HealerGD>{}: std::optional<Ent::Gen::HealerGD>(getSubNode("HealerGD"));
        }
        inline Ent::Gen::HealerGD Object_Components::addHealerGD() const
        {
            return Ent::Gen::HealerGD(addSubNode("HealerGD"));
        }
        inline std::optional<Ent::Gen::AnimationLegsConstraintsGD> Object_Components::AnimationLegsConstraintsGD() const
        {
            auto sub = getSubNode("AnimationLegsConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationLegsConstraintsGD>{}: std::optional<Ent::Gen::AnimationLegsConstraintsGD>(getSubNode("AnimationLegsConstraintsGD"));
        }
        inline Ent::Gen::AnimationLegsConstraintsGD Object_Components::addAnimationLegsConstraintsGD() const
        {
            return Ent::Gen::AnimationLegsConstraintsGD(addSubNode("AnimationLegsConstraintsGD"));
        }
        inline std::optional<Ent::Gen::PathBoneRigidBodyGD> Object_Components::PathBoneRigidBodyGD() const
        {
            auto sub = getSubNode("PathBoneRigidBodyGD");
            return sub == nullptr? std::optional<Ent::Gen::PathBoneRigidBodyGD>{}: std::optional<Ent::Gen::PathBoneRigidBodyGD>(getSubNode("PathBoneRigidBodyGD"));
        }
        inline Ent::Gen::PathBoneRigidBodyGD Object_Components::addPathBoneRigidBodyGD() const
        {
            return Ent::Gen::PathBoneRigidBodyGD(addSubNode("PathBoneRigidBodyGD"));
        }
        inline std::optional<Ent::Gen::FightDistanceTriggerGD> Object_Components::FightDistanceTriggerGD() const
        {
            auto sub = getSubNode("FightDistanceTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::FightDistanceTriggerGD>{}: std::optional<Ent::Gen::FightDistanceTriggerGD>(getSubNode("FightDistanceTriggerGD"));
        }
        inline Ent::Gen::FightDistanceTriggerGD Object_Components::addFightDistanceTriggerGD() const
        {
            return Ent::Gen::FightDistanceTriggerGD(addSubNode("FightDistanceTriggerGD"));
        }
        inline std::optional<Ent::Gen::SoulSpotGD> Object_Components::SoulSpotGD() const
        {
            auto sub = getSubNode("SoulSpotGD");
            return sub == nullptr? std::optional<Ent::Gen::SoulSpotGD>{}: std::optional<Ent::Gen::SoulSpotGD>(getSubNode("SoulSpotGD"));
        }
        inline Ent::Gen::SoulSpotGD Object_Components::addSoulSpotGD() const
        {
            return Ent::Gen::SoulSpotGD(addSubNode("SoulSpotGD"));
        }
        inline std::optional<Ent::Gen::HealTriggerGD> Object_Components::HealTriggerGD() const
        {
            auto sub = getSubNode("HealTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::HealTriggerGD>{}: std::optional<Ent::Gen::HealTriggerGD>(getSubNode("HealTriggerGD"));
        }
        inline Ent::Gen::HealTriggerGD Object_Components::addHealTriggerGD() const
        {
            return Ent::Gen::HealTriggerGD(addSubNode("HealTriggerGD"));
        }
        inline std::optional<Ent::Gen::AnimationTailConstraintsGD> Object_Components::AnimationTailConstraintsGD() const
        {
            auto sub = getSubNode("AnimationTailConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationTailConstraintsGD>{}: std::optional<Ent::Gen::AnimationTailConstraintsGD>(getSubNode("AnimationTailConstraintsGD"));
        }
        inline Ent::Gen::AnimationTailConstraintsGD Object_Components::addAnimationTailConstraintsGD() const
        {
            return Ent::Gen::AnimationTailConstraintsGD(addSubNode("AnimationTailConstraintsGD"));
        }
        inline std::optional<Ent::Gen::VolumeConstraintGD> Object_Components::VolumeConstraintGD() const
        {
            auto sub = getSubNode("VolumeConstraintGD");
            return sub == nullptr? std::optional<Ent::Gen::VolumeConstraintGD>{}: std::optional<Ent::Gen::VolumeConstraintGD>(getSubNode("VolumeConstraintGD"));
        }
        inline Ent::Gen::VolumeConstraintGD Object_Components::addVolumeConstraintGD() const
        {
            return Ent::Gen::VolumeConstraintGD(addSubNode("VolumeConstraintGD"));
        }
        inline std::optional<Ent::Gen::EnvStampGD> Object_Components::EnvStampGD() const
        {
            auto sub = getSubNode("EnvStampGD");
            return sub == nullptr? std::optional<Ent::Gen::EnvStampGD>{}: std::optional<Ent::Gen::EnvStampGD>(getSubNode("EnvStampGD"));
        }
        inline Ent::Gen::EnvStampGD Object_Components::addEnvStampGD() const
        {
            return Ent::Gen::EnvStampGD(addSubNode("EnvStampGD"));
        }
        inline std::optional<Ent::Gen::FluidFXEntitySpawnerGD> Object_Components::FluidFXEntitySpawnerGD() const
        {
            auto sub = getSubNode("FluidFXEntitySpawnerGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidFXEntitySpawnerGD>{}: std::optional<Ent::Gen::FluidFXEntitySpawnerGD>(getSubNode("FluidFXEntitySpawnerGD"));
        }
        inline Ent::Gen::FluidFXEntitySpawnerGD Object_Components::addFluidFXEntitySpawnerGD() const
        {
            return Ent::Gen::FluidFXEntitySpawnerGD(addSubNode("FluidFXEntitySpawnerGD"));
        }
        inline std::optional<Ent::Gen::EnergyDrainGD> Object_Components::EnergyDrainGD() const
        {
            auto sub = getSubNode("EnergyDrainGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyDrainGD>{}: std::optional<Ent::Gen::EnergyDrainGD>(getSubNode("EnergyDrainGD"));
        }
        inline Ent::Gen::EnergyDrainGD Object_Components::addEnergyDrainGD() const
        {
            return Ent::Gen::EnergyDrainGD(addSubNode("EnergyDrainGD"));
        }
        inline std::optional<Ent::Gen::AnimationEventsGeneratorGD> Object_Components::AnimationEventsGeneratorGD() const
        {
            auto sub = getSubNode("AnimationEventsGeneratorGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationEventsGeneratorGD>{}: std::optional<Ent::Gen::AnimationEventsGeneratorGD>(getSubNode("AnimationEventsGeneratorGD"));
        }
        inline Ent::Gen::AnimationEventsGeneratorGD Object_Components::addAnimationEventsGeneratorGD() const
        {
            return Ent::Gen::AnimationEventsGeneratorGD(addSubNode("AnimationEventsGeneratorGD"));
        }
        inline std::optional<Ent::Gen::MountableGD> Object_Components::MountableGD() const
        {
            auto sub = getSubNode("MountableGD");
            return sub == nullptr? std::optional<Ent::Gen::MountableGD>{}: std::optional<Ent::Gen::MountableGD>(getSubNode("MountableGD"));
        }
        inline Ent::Gen::MountableGD Object_Components::addMountableGD() const
        {
            return Ent::Gen::MountableGD(addSubNode("MountableGD"));
        }
        inline std::optional<Ent::Gen::InfoboardRegistererGD> Object_Components::InfoboardRegistererGD() const
        {
            auto sub = getSubNode("InfoboardRegistererGD");
            return sub == nullptr? std::optional<Ent::Gen::InfoboardRegistererGD>{}: std::optional<Ent::Gen::InfoboardRegistererGD>(getSubNode("InfoboardRegistererGD"));
        }
        inline Ent::Gen::InfoboardRegistererGD Object_Components::addInfoboardRegistererGD() const
        {
            return Ent::Gen::InfoboardRegistererGD(addSubNode("InfoboardRegistererGD"));
        }
        inline std::optional<Ent::Gen::EventHandlerGD> Object_Components::EventHandlerGD() const
        {
            auto sub = getSubNode("EventHandlerGD");
            return sub == nullptr? std::optional<Ent::Gen::EventHandlerGD>{}: std::optional<Ent::Gen::EventHandlerGD>(getSubNode("EventHandlerGD"));
        }
        inline Ent::Gen::EventHandlerGD Object_Components::addEventHandlerGD() const
        {
            return Ent::Gen::EventHandlerGD(addSubNode("EventHandlerGD"));
        }
        inline std::optional<Ent::Gen::SoulRespawnOpportunityGD> Object_Components::SoulRespawnOpportunityGD() const
        {
            auto sub = getSubNode("SoulRespawnOpportunityGD");
            return sub == nullptr? std::optional<Ent::Gen::SoulRespawnOpportunityGD>{}: std::optional<Ent::Gen::SoulRespawnOpportunityGD>(getSubNode("SoulRespawnOpportunityGD"));
        }
        inline Ent::Gen::SoulRespawnOpportunityGD Object_Components::addSoulRespawnOpportunityGD() const
        {
            return Ent::Gen::SoulRespawnOpportunityGD(addSubNode("SoulRespawnOpportunityGD"));
        }
        inline std::optional<Ent::Gen::HealthAreaGD> Object_Components::HealthAreaGD() const
        {
            auto sub = getSubNode("HealthAreaGD");
            return sub == nullptr? std::optional<Ent::Gen::HealthAreaGD>{}: std::optional<Ent::Gen::HealthAreaGD>(getSubNode("HealthAreaGD"));
        }
        inline Ent::Gen::HealthAreaGD Object_Components::addHealthAreaGD() const
        {
            return Ent::Gen::HealthAreaGD(addSubNode("HealthAreaGD"));
        }
        inline std::optional<Ent::Gen::SoundAreaGD> Object_Components::SoundAreaGD() const
        {
            auto sub = getSubNode("SoundAreaGD");
            return sub == nullptr? std::optional<Ent::Gen::SoundAreaGD>{}: std::optional<Ent::Gen::SoundAreaGD>(getSubNode("SoundAreaGD"));
        }
        inline Ent::Gen::SoundAreaGD Object_Components::addSoundAreaGD() const
        {
            return Ent::Gen::SoundAreaGD(addSubNode("SoundAreaGD"));
        }
        inline std::optional<Ent::Gen::PathBoneInfluenceGD> Object_Components::PathBoneInfluenceGD() const
        {
            auto sub = getSubNode("PathBoneInfluenceGD");
            return sub == nullptr? std::optional<Ent::Gen::PathBoneInfluenceGD>{}: std::optional<Ent::Gen::PathBoneInfluenceGD>(getSubNode("PathBoneInfluenceGD"));
        }
        inline Ent::Gen::PathBoneInfluenceGD Object_Components::addPathBoneInfluenceGD() const
        {
            return Ent::Gen::PathBoneInfluenceGD(addSubNode("PathBoneInfluenceGD"));
        }
        inline std::optional<Ent::Gen::ComponentWithProtoCodeGD> Object_Components::ComponentWithProtoCodeGD() const
        {
            auto sub = getSubNode("ComponentWithProtoCodeGD");
            return sub == nullptr? std::optional<Ent::Gen::ComponentWithProtoCodeGD>{}: std::optional<Ent::Gen::ComponentWithProtoCodeGD>(getSubNode("ComponentWithProtoCodeGD"));
        }
        inline Ent::Gen::ComponentWithProtoCodeGD Object_Components::addComponentWithProtoCodeGD() const
        {
            return Ent::Gen::ComponentWithProtoCodeGD(addSubNode("ComponentWithProtoCodeGD"));
        }
        inline std::optional<Ent::Gen::CharacterControllerGD> Object_Components::CharacterControllerGD() const
        {
            auto sub = getSubNode("CharacterControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::CharacterControllerGD>{}: std::optional<Ent::Gen::CharacterControllerGD>(getSubNode("CharacterControllerGD"));
        }
        inline Ent::Gen::CharacterControllerGD Object_Components::addCharacterControllerGD() const
        {
            return Ent::Gen::CharacterControllerGD(addSubNode("CharacterControllerGD"));
        }
        inline std::optional<Ent::Gen::PickableComponentGD> Object_Components::PickableComponentGD() const
        {
            auto sub = getSubNode("PickableComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::PickableComponentGD>{}: std::optional<Ent::Gen::PickableComponentGD>(getSubNode("PickableComponentGD"));
        }
        inline Ent::Gen::PickableComponentGD Object_Components::addPickableComponentGD() const
        {
            return Ent::Gen::PickableComponentGD(addSubNode("PickableComponentGD"));
        }
        inline std::optional<Ent::Gen::CameraDataGD> Object_Components::CameraDataGD() const
        {
            auto sub = getSubNode("CameraDataGD");
            return sub == nullptr? std::optional<Ent::Gen::CameraDataGD>{}: std::optional<Ent::Gen::CameraDataGD>(getSubNode("CameraDataGD"));
        }
        inline Ent::Gen::CameraDataGD Object_Components::addCameraDataGD() const
        {
            return Ent::Gen::CameraDataGD(addSubNode("CameraDataGD"));
        }
        inline std::optional<Ent::Gen::RegenFXGD> Object_Components::RegenFXGD() const
        {
            auto sub = getSubNode("RegenFXGD");
            return sub == nullptr? std::optional<Ent::Gen::RegenFXGD>{}: std::optional<Ent::Gen::RegenFXGD>(getSubNode("RegenFXGD"));
        }
        inline Ent::Gen::RegenFXGD Object_Components::addRegenFXGD() const
        {
            return Ent::Gen::RegenFXGD(addSubNode("RegenFXGD"));
        }
        inline std::optional<Ent::Gen::PhysicsMeshDeformerGD> Object_Components::PhysicsMeshDeformerGD() const
        {
            auto sub = getSubNode("PhysicsMeshDeformerGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsMeshDeformerGD>{}: std::optional<Ent::Gen::PhysicsMeshDeformerGD>(getSubNode("PhysicsMeshDeformerGD"));
        }
        inline Ent::Gen::PhysicsMeshDeformerGD Object_Components::addPhysicsMeshDeformerGD() const
        {
            return Ent::Gen::PhysicsMeshDeformerGD(addSubNode("PhysicsMeshDeformerGD"));
        }
        inline std::optional<Ent::Gen::AnimationHitsConstraintsGD> Object_Components::AnimationHitsConstraintsGD() const
        {
            auto sub = getSubNode("AnimationHitsConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationHitsConstraintsGD>{}: std::optional<Ent::Gen::AnimationHitsConstraintsGD>(getSubNode("AnimationHitsConstraintsGD"));
        }
        inline Ent::Gen::AnimationHitsConstraintsGD Object_Components::addAnimationHitsConstraintsGD() const
        {
            return Ent::Gen::AnimationHitsConstraintsGD(addSubNode("AnimationHitsConstraintsGD"));
        }
        inline std::optional<Ent::Gen::FluidVolumeComponentGD> Object_Components::FluidVolumeComponentGD() const
        {
            auto sub = getSubNode("FluidVolumeComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidVolumeComponentGD>{}: std::optional<Ent::Gen::FluidVolumeComponentGD>(getSubNode("FluidVolumeComponentGD"));
        }
        inline Ent::Gen::FluidVolumeComponentGD Object_Components::addFluidVolumeComponentGD() const
        {
            return Ent::Gen::FluidVolumeComponentGD(addSubNode("FluidVolumeComponentGD"));
        }
        inline std::optional<Ent::Gen::RegenerableVegetationGD> Object_Components::RegenerableVegetationGD() const
        {
            auto sub = getSubNode("RegenerableVegetationGD");
            return sub == nullptr? std::optional<Ent::Gen::RegenerableVegetationGD>{}: std::optional<Ent::Gen::RegenerableVegetationGD>(getSubNode("RegenerableVegetationGD"));
        }
        inline Ent::Gen::RegenerableVegetationGD Object_Components::addRegenerableVegetationGD() const
        {
            return Ent::Gen::RegenerableVegetationGD(addSubNode("RegenerableVegetationGD"));
        }
        inline std::optional<Ent::Gen::ShamanVisionGD> Object_Components::ShamanVisionGD() const
        {
            auto sub = getSubNode("ShamanVisionGD");
            return sub == nullptr? std::optional<Ent::Gen::ShamanVisionGD>{}: std::optional<Ent::Gen::ShamanVisionGD>(getSubNode("ShamanVisionGD"));
        }
        inline Ent::Gen::ShamanVisionGD Object_Components::addShamanVisionGD() const
        {
            return Ent::Gen::ShamanVisionGD(addSubNode("ShamanVisionGD"));
        }
        inline std::optional<Ent::Gen::CinematicGD> Object_Components::CinematicGD() const
        {
            auto sub = getSubNode("CinematicGD");
            return sub == nullptr? std::optional<Ent::Gen::CinematicGD>{}: std::optional<Ent::Gen::CinematicGD>(getSubNode("CinematicGD"));
        }
        inline Ent::Gen::CinematicGD Object_Components::addCinematicGD() const
        {
            return Ent::Gen::CinematicGD(addSubNode("CinematicGD"));
        }
        inline std::optional<Ent::Gen::ConnectorGD> Object_Components::ConnectorGD() const
        {
            auto sub = getSubNode("ConnectorGD");
            return sub == nullptr? std::optional<Ent::Gen::ConnectorGD>{}: std::optional<Ent::Gen::ConnectorGD>(getSubNode("ConnectorGD"));
        }
        inline Ent::Gen::ConnectorGD Object_Components::addConnectorGD() const
        {
            return Ent::Gen::ConnectorGD(addSubNode("ConnectorGD"));
        }
        inline std::optional<Ent::Gen::BeamTargetGD> Object_Components::BeamTargetGD() const
        {
            auto sub = getSubNode("BeamTargetGD");
            return sub == nullptr? std::optional<Ent::Gen::BeamTargetGD>{}: std::optional<Ent::Gen::BeamTargetGD>(getSubNode("BeamTargetGD"));
        }
        inline Ent::Gen::BeamTargetGD Object_Components::addBeamTargetGD() const
        {
            return Ent::Gen::BeamTargetGD(addSubNode("BeamTargetGD"));
        }
        inline std::optional<Ent::Gen::ActorGD> Object_Components::ActorGD() const
        {
            auto sub = getSubNode("ActorGD");
            return sub == nullptr? std::optional<Ent::Gen::ActorGD>{}: std::optional<Ent::Gen::ActorGD>(getSubNode("ActorGD"));
        }
        inline Ent::Gen::ActorGD Object_Components::addActorGD() const
        {
            return Ent::Gen::ActorGD(addSubNode("ActorGD"));
        }
        inline std::optional<Ent::Gen::CharacterPlatformGD> Object_Components::CharacterPlatformGD() const
        {
            auto sub = getSubNode("CharacterPlatformGD");
            return sub == nullptr? std::optional<Ent::Gen::CharacterPlatformGD>{}: std::optional<Ent::Gen::CharacterPlatformGD>(getSubNode("CharacterPlatformGD"));
        }
        inline Ent::Gen::CharacterPlatformGD Object_Components::addCharacterPlatformGD() const
        {
            return Ent::Gen::CharacterPlatformGD(addSubNode("CharacterPlatformGD"));
        }
        inline std::optional<Ent::Gen::ReviveSideSwitcherGD> Object_Components::ReviveSideSwitcherGD() const
        {
            auto sub = getSubNode("ReviveSideSwitcherGD");
            return sub == nullptr? std::optional<Ent::Gen::ReviveSideSwitcherGD>{}: std::optional<Ent::Gen::ReviveSideSwitcherGD>(getSubNode("ReviveSideSwitcherGD"));
        }
        inline Ent::Gen::ReviveSideSwitcherGD Object_Components::addReviveSideSwitcherGD() const
        {
            return Ent::Gen::ReviveSideSwitcherGD(addSubNode("ReviveSideSwitcherGD"));
        }
        inline std::optional<Ent::Gen::EnergyPoolGD> Object_Components::EnergyPoolGD() const
        {
            auto sub = getSubNode("EnergyPoolGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyPoolGD>{}: std::optional<Ent::Gen::EnergyPoolGD>(getSubNode("EnergyPoolGD"));
        }
        inline Ent::Gen::EnergyPoolGD Object_Components::addEnergyPoolGD() const
        {
            return Ent::Gen::EnergyPoolGD(addSubNode("EnergyPoolGD"));
        }
        inline std::optional<Ent::Gen::PlayerComponentGD> Object_Components::PlayerComponentGD() const
        {
            auto sub = getSubNode("PlayerComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::PlayerComponentGD>{}: std::optional<Ent::Gen::PlayerComponentGD>(getSubNode("PlayerComponentGD"));
        }
        inline Ent::Gen::PlayerComponentGD Object_Components::addPlayerComponentGD() const
        {
            return Ent::Gen::PlayerComponentGD(addSubNode("PlayerComponentGD"));
        }
        inline std::optional<Ent::Gen::HotspotsGD> Object_Components::HotspotsGD() const
        {
            auto sub = getSubNode("HotspotsGD");
            return sub == nullptr? std::optional<Ent::Gen::HotspotsGD>{}: std::optional<Ent::Gen::HotspotsGD>(getSubNode("HotspotsGD"));
        }
        inline Ent::Gen::HotspotsGD Object_Components::addHotspotsGD() const
        {
            return Ent::Gen::HotspotsGD(addSubNode("HotspotsGD"));
        }
        inline std::optional<Ent::Gen::SmallActorSpawnerGD> Object_Components::SmallActorSpawnerGD() const
        {
            auto sub = getSubNode("SmallActorSpawnerGD");
            return sub == nullptr? std::optional<Ent::Gen::SmallActorSpawnerGD>{}: std::optional<Ent::Gen::SmallActorSpawnerGD>(getSubNode("SmallActorSpawnerGD"));
        }
        inline Ent::Gen::SmallActorSpawnerGD Object_Components::addSmallActorSpawnerGD() const
        {
            return Ent::Gen::SmallActorSpawnerGD(addSubNode("SmallActorSpawnerGD"));
        }
        inline std::optional<Ent::Gen::PathMotionControllerGD> Object_Components::PathMotionControllerGD() const
        {
            auto sub = getSubNode("PathMotionControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::PathMotionControllerGD>{}: std::optional<Ent::Gen::PathMotionControllerGD>(getSubNode("PathMotionControllerGD"));
        }
        inline Ent::Gen::PathMotionControllerGD Object_Components::addPathMotionControllerGD() const
        {
            return Ent::Gen::PathMotionControllerGD(addSubNode("PathMotionControllerGD"));
        }
        inline std::optional<Ent::Gen::CreatureAIGD> Object_Components::CreatureAIGD() const
        {
            auto sub = getSubNode("CreatureAIGD");
            return sub == nullptr? std::optional<Ent::Gen::CreatureAIGD>{}: std::optional<Ent::Gen::CreatureAIGD>(getSubNode("CreatureAIGD"));
        }
        inline Ent::Gen::CreatureAIGD Object_Components::addCreatureAIGD() const
        {
            return Ent::Gen::CreatureAIGD(addSubNode("CreatureAIGD"));
        }
        inline std::optional<Ent::Gen::CreatureUIGD> Object_Components::CreatureUIGD() const
        {
            auto sub = getSubNode("CreatureUIGD");
            return sub == nullptr? std::optional<Ent::Gen::CreatureUIGD>{}: std::optional<Ent::Gen::CreatureUIGD>(getSubNode("CreatureUIGD"));
        }
        inline Ent::Gen::CreatureUIGD Object_Components::addCreatureUIGD() const
        {
            return Ent::Gen::CreatureUIGD(addSubNode("CreatureUIGD"));
        }
        inline std::optional<Ent::Gen::SoundEmitterGD> Object_Components::SoundEmitterGD() const
        {
            auto sub = getSubNode("SoundEmitterGD");
            return sub == nullptr? std::optional<Ent::Gen::SoundEmitterGD>{}: std::optional<Ent::Gen::SoundEmitterGD>(getSubNode("SoundEmitterGD"));
        }
        inline Ent::Gen::SoundEmitterGD Object_Components::addSoundEmitterGD() const
        {
            return Ent::Gen::SoundEmitterGD(addSubNode("SoundEmitterGD"));
        }
        inline std::optional<Ent::Gen::EnergySourceGD> Object_Components::EnergySourceGD() const
        {
            auto sub = getSubNode("EnergySourceGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergySourceGD>{}: std::optional<Ent::Gen::EnergySourceGD>(getSubNode("EnergySourceGD"));
        }
        inline Ent::Gen::EnergySourceGD Object_Components::addEnergySourceGD() const
        {
            return Ent::Gen::EnergySourceGD(addSubNode("EnergySourceGD"));
        }
        inline std::optional<Ent::Gen::ClothAnimationGD> Object_Components::ClothAnimationGD() const
        {
            auto sub = getSubNode("ClothAnimationGD");
            return sub == nullptr? std::optional<Ent::Gen::ClothAnimationGD>{}: std::optional<Ent::Gen::ClothAnimationGD>(getSubNode("ClothAnimationGD"));
        }
        inline Ent::Gen::ClothAnimationGD Object_Components::addClothAnimationGD() const
        {
            return Ent::Gen::ClothAnimationGD(addSubNode("ClothAnimationGD"));
        }
        inline std::optional<Ent::Gen::CreatureGD> Object_Components::CreatureGD() const
        {
            auto sub = getSubNode("CreatureGD");
            return sub == nullptr? std::optional<Ent::Gen::CreatureGD>{}: std::optional<Ent::Gen::CreatureGD>(getSubNode("CreatureGD"));
        }
        inline Ent::Gen::CreatureGD Object_Components::addCreatureGD() const
        {
            return Ent::Gen::CreatureGD(addSubNode("CreatureGD"));
        }
        inline std::optional<Ent::Gen::HitTriggerGD> Object_Components::HitTriggerGD() const
        {
            auto sub = getSubNode("HitTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::HitTriggerGD>{}: std::optional<Ent::Gen::HitTriggerGD>(getSubNode("HitTriggerGD"));
        }
        inline Ent::Gen::HitTriggerGD Object_Components::addHitTriggerGD() const
        {
            return Ent::Gen::HitTriggerGD(addSubNode("HitTriggerGD"));
        }
        inline std::optional<Ent::Gen::ProjectileShooterGD> Object_Components::ProjectileShooterGD() const
        {
            auto sub = getSubNode("ProjectileShooterGD");
            return sub == nullptr? std::optional<Ent::Gen::ProjectileShooterGD>{}: std::optional<Ent::Gen::ProjectileShooterGD>(getSubNode("ProjectileShooterGD"));
        }
        inline Ent::Gen::ProjectileShooterGD Object_Components::addProjectileShooterGD() const
        {
            return Ent::Gen::ProjectileShooterGD(addSubNode("ProjectileShooterGD"));
        }
        inline std::optional<Ent::Gen::LightComponentGD> Object_Components::LightComponentGD() const
        {
            auto sub = getSubNode("LightComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::LightComponentGD>{}: std::optional<Ent::Gen::LightComponentGD>(getSubNode("LightComponentGD"));
        }
        inline Ent::Gen::LightComponentGD Object_Components::addLightComponentGD() const
        {
            return Ent::Gen::LightComponentGD(addSubNode("LightComponentGD"));
        }
        inline std::optional<Ent::Gen::MounterGD> Object_Components::MounterGD() const
        {
            auto sub = getSubNode("MounterGD");
            return sub == nullptr? std::optional<Ent::Gen::MounterGD>{}: std::optional<Ent::Gen::MounterGD>(getSubNode("MounterGD"));
        }
        inline Ent::Gen::MounterGD Object_Components::addMounterGD() const
        {
            return Ent::Gen::MounterGD(addSubNode("MounterGD"));
        }
        inline std::optional<Ent::Gen::AttackTriggerGD> Object_Components::AttackTriggerGD() const
        {
            auto sub = getSubNode("AttackTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::AttackTriggerGD>{}: std::optional<Ent::Gen::AttackTriggerGD>(getSubNode("AttackTriggerGD"));
        }
        inline Ent::Gen::AttackTriggerGD Object_Components::addAttackTriggerGD() const
        {
            return Ent::Gen::AttackTriggerGD(addSubNode("AttackTriggerGD"));
        }
        inline std::optional<Ent::Gen::PossessableGPEGD> Object_Components::PossessableGPEGD() const
        {
            auto sub = getSubNode("PossessableGPEGD");
            return sub == nullptr? std::optional<Ent::Gen::PossessableGPEGD>{}: std::optional<Ent::Gen::PossessableGPEGD>(getSubNode("PossessableGPEGD"));
        }
        inline Ent::Gen::PossessableGPEGD Object_Components::addPossessableGPEGD() const
        {
            return Ent::Gen::PossessableGPEGD(addSubNode("PossessableGPEGD"));
        }
        inline std::optional<Ent::Gen::OutfitGD> Object_Components::OutfitGD() const
        {
            auto sub = getSubNode("OutfitGD");
            return sub == nullptr? std::optional<Ent::Gen::OutfitGD>{}: std::optional<Ent::Gen::OutfitGD>(getSubNode("OutfitGD"));
        }
        inline Ent::Gen::OutfitGD Object_Components::addOutfitGD() const
        {
            return Ent::Gen::OutfitGD(addSubNode("OutfitGD"));
        }
        inline std::optional<Ent::Gen::BreakableGD> Object_Components::BreakableGD() const
        {
            auto sub = getSubNode("BreakableGD");
            return sub == nullptr? std::optional<Ent::Gen::BreakableGD>{}: std::optional<Ent::Gen::BreakableGD>(getSubNode("BreakableGD"));
        }
        inline Ent::Gen::BreakableGD Object_Components::addBreakableGD() const
        {
            return Ent::Gen::BreakableGD(addSubNode("BreakableGD"));
        }
        inline std::optional<Ent::Gen::PathNodeGD> Object_Components::PathNodeGD() const
        {
            auto sub = getSubNode("PathNodeGD");
            return sub == nullptr? std::optional<Ent::Gen::PathNodeGD>{}: std::optional<Ent::Gen::PathNodeGD>(getSubNode("PathNodeGD"));
        }
        inline Ent::Gen::PathNodeGD Object_Components::addPathNodeGD() const
        {
            return Ent::Gen::PathNodeGD(addSubNode("PathNodeGD"));
        }
        inline std::optional<Ent::Gen::VelocityObstacleGD> Object_Components::VelocityObstacleGD() const
        {
            auto sub = getSubNode("VelocityObstacleGD");
            return sub == nullptr? std::optional<Ent::Gen::VelocityObstacleGD>{}: std::optional<Ent::Gen::VelocityObstacleGD>(getSubNode("VelocityObstacleGD"));
        }
        inline Ent::Gen::VelocityObstacleGD Object_Components::addVelocityObstacleGD() const
        {
            return Ent::Gen::VelocityObstacleGD(addSubNode("VelocityObstacleGD"));
        }
        inline std::optional<Ent::Gen::ShapeshiftStatueGD> Object_Components::ShapeshiftStatueGD() const
        {
            auto sub = getSubNode("ShapeshiftStatueGD");
            return sub == nullptr? std::optional<Ent::Gen::ShapeshiftStatueGD>{}: std::optional<Ent::Gen::ShapeshiftStatueGD>(getSubNode("ShapeshiftStatueGD"));
        }
        inline Ent::Gen::ShapeshiftStatueGD Object_Components::addShapeshiftStatueGD() const
        {
            return Ent::Gen::ShapeshiftStatueGD(addSubNode("ShapeshiftStatueGD"));
        }
        inline std::optional<Ent::Gen::RagdollGD> Object_Components::RagdollGD() const
        {
            auto sub = getSubNode("RagdollGD");
            return sub == nullptr? std::optional<Ent::Gen::RagdollGD>{}: std::optional<Ent::Gen::RagdollGD>(getSubNode("RagdollGD"));
        }
        inline Ent::Gen::RagdollGD Object_Components::addRagdollGD() const
        {
            return Ent::Gen::RagdollGD(addSubNode("RagdollGD"));
        }
        inline std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD> Object_Components::AnimationPhysicsChainConstraintsGD() const
        {
            auto sub = getSubNode("AnimationPhysicsChainConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD>{}: std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD>(getSubNode("AnimationPhysicsChainConstraintsGD"));
        }
        inline Ent::Gen::AnimationPhysicsChainConstraintsGD Object_Components::addAnimationPhysicsChainConstraintsGD() const
        {
            return Ent::Gen::AnimationPhysicsChainConstraintsGD(addSubNode("AnimationPhysicsChainConstraintsGD"));
        }
        inline std::optional<Ent::Gen::ScriptComponentGD> Object_Components::ScriptComponentGD() const
        {
            auto sub = getSubNode("ScriptComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::ScriptComponentGD>{}: std::optional<Ent::Gen::ScriptComponentGD>(getSubNode("ScriptComponentGD"));
        }
        inline Ent::Gen::ScriptComponentGD Object_Components::addScriptComponentGD() const
        {
            return Ent::Gen::ScriptComponentGD(addSubNode("ScriptComponentGD"));
        }
        inline std::optional<Ent::Gen::FluidToRegenInjectorGD> Object_Components::FluidToRegenInjectorGD() const
        {
            auto sub = getSubNode("FluidToRegenInjectorGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidToRegenInjectorGD>{}: std::optional<Ent::Gen::FluidToRegenInjectorGD>(getSubNode("FluidToRegenInjectorGD"));
        }
        inline Ent::Gen::FluidToRegenInjectorGD Object_Components::addFluidToRegenInjectorGD() const
        {
            return Ent::Gen::FluidToRegenInjectorGD(addSubNode("FluidToRegenInjectorGD"));
        }
        inline std::optional<Ent::Gen::PerceivableGD> Object_Components::PerceivableGD() const
        {
            auto sub = getSubNode("PerceivableGD");
            return sub == nullptr? std::optional<Ent::Gen::PerceivableGD>{}: std::optional<Ent::Gen::PerceivableGD>(getSubNode("PerceivableGD"));
        }
        inline Ent::Gen::PerceivableGD Object_Components::addPerceivableGD() const
        {
            return Ent::Gen::PerceivableGD(addSubNode("PerceivableGD"));
        }
        inline std::optional<Ent::Gen::InventoryGD> Object_Components::InventoryGD() const
        {
            auto sub = getSubNode("InventoryGD");
            return sub == nullptr? std::optional<Ent::Gen::InventoryGD>{}: std::optional<Ent::Gen::InventoryGD>(getSubNode("InventoryGD"));
        }
        inline Ent::Gen::InventoryGD Object_Components::addInventoryGD() const
        {
            return Ent::Gen::InventoryGD(addSubNode("InventoryGD"));
        }
        inline std::optional<Ent::Gen::ItemHolderGD> Object_Components::ItemHolderGD() const
        {
            auto sub = getSubNode("ItemHolderGD");
            return sub == nullptr? std::optional<Ent::Gen::ItemHolderGD>{}: std::optional<Ent::Gen::ItemHolderGD>(getSubNode("ItemHolderGD"));
        }
        inline Ent::Gen::ItemHolderGD Object_Components::addItemHolderGD() const
        {
            return Ent::Gen::ItemHolderGD(addSubNode("ItemHolderGD"));
        }
        inline std::optional<Ent::Gen::PathGD> Object_Components::PathGD() const
        {
            auto sub = getSubNode("PathGD");
            return sub == nullptr? std::optional<Ent::Gen::PathGD>{}: std::optional<Ent::Gen::PathGD>(getSubNode("PathGD"));
        }
        inline Ent::Gen::PathGD Object_Components::addPathGD() const
        {
            return Ent::Gen::PathGD(addSubNode("PathGD"));
        }
        inline std::optional<Ent::Gen::PerceiverGD> Object_Components::PerceiverGD() const
        {
            auto sub = getSubNode("PerceiverGD");
            return sub == nullptr? std::optional<Ent::Gen::PerceiverGD>{}: std::optional<Ent::Gen::PerceiverGD>(getSubNode("PerceiverGD"));
        }
        inline Ent::Gen::PerceiverGD Object_Components::addPerceiverGD() const
        {
            return Ent::Gen::PerceiverGD(addSubNode("PerceiverGD"));
        }
        inline std::optional<Ent::Gen::DummyComponentGD> Object_Components::DummyComponentGD() const
        {
            auto sub = getSubNode("DummyComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::DummyComponentGD>{}: std::optional<Ent::Gen::DummyComponentGD>(getSubNode("DummyComponentGD"));
        }
        inline Ent::Gen::DummyComponentGD Object_Components::addDummyComponentGD() const
        {
            return Ent::Gen::DummyComponentGD(addSubNode("DummyComponentGD"));
        }
        inline std::optional<Ent::Gen::FluidNavMeshTaggerGD> Object_Components::FluidNavMeshTaggerGD() const
        {
            auto sub = getSubNode("FluidNavMeshTaggerGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidNavMeshTaggerGD>{}: std::optional<Ent::Gen::FluidNavMeshTaggerGD>(getSubNode("FluidNavMeshTaggerGD"));
        }
        inline Ent::Gen::FluidNavMeshTaggerGD Object_Components::addFluidNavMeshTaggerGD() const
        {
            return Ent::Gen::FluidNavMeshTaggerGD(addSubNode("FluidNavMeshTaggerGD"));
        }
        inline std::optional<Ent::Gen::EnergySpoutGD> Object_Components::EnergySpoutGD() const
        {
            auto sub = getSubNode("EnergySpoutGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergySpoutGD>{}: std::optional<Ent::Gen::EnergySpoutGD>(getSubNode("EnergySpoutGD"));
        }
        inline Ent::Gen::EnergySpoutGD Object_Components::addEnergySpoutGD() const
        {
            return Ent::Gen::EnergySpoutGD(addSubNode("EnergySpoutGD"));
        }
        inline std::optional<Ent::Gen::PickableDistributorComponentGD> Object_Components::PickableDistributorComponentGD() const
        {
            auto sub = getSubNode("PickableDistributorComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::PickableDistributorComponentGD>{}: std::optional<Ent::Gen::PickableDistributorComponentGD>(getSubNode("PickableDistributorComponentGD"));
        }
        inline Ent::Gen::PickableDistributorComponentGD Object_Components::addPickableDistributorComponentGD() const
        {
            return Ent::Gen::PickableDistributorComponentGD(addSubNode("PickableDistributorComponentGD"));
        }
        inline std::optional<Ent::Gen::ShamanItemGD> Object_Components::ShamanItemGD() const
        {
            auto sub = getSubNode("ShamanItemGD");
            return sub == nullptr? std::optional<Ent::Gen::ShamanItemGD>{}: std::optional<Ent::Gen::ShamanItemGD>(getSubNode("ShamanItemGD"));
        }
        inline Ent::Gen::ShamanItemGD Object_Components::addShamanItemGD() const
        {
            return Ent::Gen::ShamanItemGD(addSubNode("ShamanItemGD"));
        }
        inline std::optional<Ent::Gen::TeamGD> Object_Components::TeamGD() const
        {
            auto sub = getSubNode("TeamGD");
            return sub == nullptr? std::optional<Ent::Gen::TeamGD>{}: std::optional<Ent::Gen::TeamGD>(getSubNode("TeamGD"));
        }
        inline Ent::Gen::TeamGD Object_Components::addTeamGD() const
        {
            return Ent::Gen::TeamGD(addSubNode("TeamGD"));
        }
        inline std::optional<Ent::Gen::SmallActorGD> Object_Components::SmallActorGD() const
        {
            auto sub = getSubNode("SmallActorGD");
            return sub == nullptr? std::optional<Ent::Gen::SmallActorGD>{}: std::optional<Ent::Gen::SmallActorGD>(getSubNode("SmallActorGD"));
        }
        inline Ent::Gen::SmallActorGD Object_Components::addSmallActorGD() const
        {
            return Ent::Gen::SmallActorGD(addSubNode("SmallActorGD"));
        }
        inline std::optional<Ent::Gen::PhysicsMeshProviderGD> Object_Components::PhysicsMeshProviderGD() const
        {
            auto sub = getSubNode("PhysicsMeshProviderGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsMeshProviderGD>{}: std::optional<Ent::Gen::PhysicsMeshProviderGD>(getSubNode("PhysicsMeshProviderGD"));
        }
        inline Ent::Gen::PhysicsMeshProviderGD Object_Components::addPhysicsMeshProviderGD() const
        {
            return Ent::Gen::PhysicsMeshProviderGD(addSubNode("PhysicsMeshProviderGD"));
        }
        inline std::optional<Ent::Gen::SideMapGateGD> Object_Components::SideMapGateGD() const
        {
            auto sub = getSubNode("SideMapGateGD");
            return sub == nullptr? std::optional<Ent::Gen::SideMapGateGD>{}: std::optional<Ent::Gen::SideMapGateGD>(getSubNode("SideMapGateGD"));
        }
        inline Ent::Gen::SideMapGateGD Object_Components::addSideMapGateGD() const
        {
            return Ent::Gen::SideMapGateGD(addSubNode("SideMapGateGD"));
        }
        inline std::optional<Ent::Gen::HeightMapComponentGD> Object_Components::HeightMapComponentGD() const
        {
            auto sub = getSubNode("HeightMapComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::HeightMapComponentGD>{}: std::optional<Ent::Gen::HeightMapComponentGD>(getSubNode("HeightMapComponentGD"));
        }
        inline Ent::Gen::HeightMapComponentGD Object_Components::addHeightMapComponentGD() const
        {
            return Ent::Gen::HeightMapComponentGD(addSubNode("HeightMapComponentGD"));
        }
        inline std::optional<Ent::Gen::MountIKControllerGD> Object_Components::MountIKControllerGD() const
        {
            auto sub = getSubNode("MountIKControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::MountIKControllerGD>{}: std::optional<Ent::Gen::MountIKControllerGD>(getSubNode("MountIKControllerGD"));
        }
        inline Ent::Gen::MountIKControllerGD Object_Components::addMountIKControllerGD() const
        {
            return Ent::Gen::MountIKControllerGD(addSubNode("MountIKControllerGD"));
        }
        inline std::optional<Ent::Gen::StaffVertebrasGD> Object_Components::StaffVertebrasGD() const
        {
            auto sub = getSubNode("StaffVertebrasGD");
            return sub == nullptr? std::optional<Ent::Gen::StaffVertebrasGD>{}: std::optional<Ent::Gen::StaffVertebrasGD>(getSubNode("StaffVertebrasGD"));
        }
        inline Ent::Gen::StaffVertebrasGD Object_Components::addStaffVertebrasGD() const
        {
            return Ent::Gen::StaffVertebrasGD(addSubNode("StaffVertebrasGD"));
        }
        inline std::optional<Ent::Gen::SensorControllerGD> Object_Components::SensorControllerGD() const
        {
            auto sub = getSubNode("SensorControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::SensorControllerGD>{}: std::optional<Ent::Gen::SensorControllerGD>(getSubNode("SensorControllerGD"));
        }
        inline Ent::Gen::SensorControllerGD Object_Components::addSensorControllerGD() const
        {
            return Ent::Gen::SensorControllerGD(addSubNode("SensorControllerGD"));
        }
        inline std::optional<Ent::Gen::BoidsGD> Object_Components::BoidsGD() const
        {
            auto sub = getSubNode("BoidsGD");
            return sub == nullptr? std::optional<Ent::Gen::BoidsGD>{}: std::optional<Ent::Gen::BoidsGD>(getSubNode("BoidsGD"));
        }
        inline Ent::Gen::BoidsGD Object_Components::addBoidsGD() const
        {
            return Ent::Gen::BoidsGD(addSubNode("BoidsGD"));
        }
        inline std::optional<Ent::Gen::AnimationTreeConstraintsGD> Object_Components::AnimationTreeConstraintsGD() const
        {
            auto sub = getSubNode("AnimationTreeConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationTreeConstraintsGD>{}: std::optional<Ent::Gen::AnimationTreeConstraintsGD>(getSubNode("AnimationTreeConstraintsGD"));
        }
        inline Ent::Gen::AnimationTreeConstraintsGD Object_Components::addAnimationTreeConstraintsGD() const
        {
            return Ent::Gen::AnimationTreeConstraintsGD(addSubNode("AnimationTreeConstraintsGD"));
        }
        inline std::optional<Ent::Gen::DistanceTriggerGD> Object_Components::DistanceTriggerGD() const
        {
            auto sub = getSubNode("DistanceTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::DistanceTriggerGD>{}: std::optional<Ent::Gen::DistanceTriggerGD>(getSubNode("DistanceTriggerGD"));
        }
        inline Ent::Gen::DistanceTriggerGD Object_Components::addDistanceTriggerGD() const
        {
            return Ent::Gen::DistanceTriggerGD(addSubNode("DistanceTriggerGD"));
        }
        inline std::optional<Ent::Gen::QuickCreatureSwitchGD> Object_Components::QuickCreatureSwitchGD() const
        {
            auto sub = getSubNode("QuickCreatureSwitchGD");
            return sub == nullptr? std::optional<Ent::Gen::QuickCreatureSwitchGD>{}: std::optional<Ent::Gen::QuickCreatureSwitchGD>(getSubNode("QuickCreatureSwitchGD"));
        }
        inline Ent::Gen::QuickCreatureSwitchGD Object_Components::addQuickCreatureSwitchGD() const
        {
            return Ent::Gen::QuickCreatureSwitchGD(addSubNode("QuickCreatureSwitchGD"));
        }
        inline std::optional<Ent::Gen::EnergyProbeGD> Object_Components::EnergyProbeGD() const
        {
            auto sub = getSubNode("EnergyProbeGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyProbeGD>{}: std::optional<Ent::Gen::EnergyProbeGD>(getSubNode("EnergyProbeGD"));
        }
        inline Ent::Gen::EnergyProbeGD Object_Components::addEnergyProbeGD() const
        {
            return Ent::Gen::EnergyProbeGD(addSubNode("EnergyProbeGD"));
        }
        inline std::optional<Ent::Gen::RespawnPlaceGD> Object_Components::RespawnPlaceGD() const
        {
            auto sub = getSubNode("RespawnPlaceGD");
            return sub == nullptr? std::optional<Ent::Gen::RespawnPlaceGD>{}: std::optional<Ent::Gen::RespawnPlaceGD>(getSubNode("RespawnPlaceGD"));
        }
        inline Ent::Gen::RespawnPlaceGD Object_Components::addRespawnPlaceGD() const
        {
            return Ent::Gen::RespawnPlaceGD(addSubNode("RespawnPlaceGD"));
        }
        inline std::optional<Ent::Gen::OutfitWearerGD> Object_Components::OutfitWearerGD() const
        {
            auto sub = getSubNode("OutfitWearerGD");
            return sub == nullptr? std::optional<Ent::Gen::OutfitWearerGD>{}: std::optional<Ent::Gen::OutfitWearerGD>(getSubNode("OutfitWearerGD"));
        }
        inline Ent::Gen::OutfitWearerGD Object_Components::addOutfitWearerGD() const
        {
            return Ent::Gen::OutfitWearerGD(addSubNode("OutfitWearerGD"));
        }
        inline std::optional<Ent::Gen::VoxelSimulationGD> Object_Components::VoxelSimulationGD() const
        {
            auto sub = getSubNode("VoxelSimulationGD");
            return sub == nullptr? std::optional<Ent::Gen::VoxelSimulationGD>{}: std::optional<Ent::Gen::VoxelSimulationGD>(getSubNode("VoxelSimulationGD"));
        }
        inline Ent::Gen::VoxelSimulationGD Object_Components::addVoxelSimulationGD() const
        {
            return Ent::Gen::VoxelSimulationGD(addSubNode("VoxelSimulationGD"));
        }
        inline std::optional<Ent::Gen::AnimationModelGD> Object_Components::AnimationModelGD() const
        {
            auto sub = getSubNode("AnimationModelGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationModelGD>{}: std::optional<Ent::Gen::AnimationModelGD>(getSubNode("AnimationModelGD"));
        }
        inline Ent::Gen::AnimationModelGD Object_Components::addAnimationModelGD() const
        {
            return Ent::Gen::AnimationModelGD(addSubNode("AnimationModelGD"));
        }
        inline std::optional<Ent::Gen::TriggerEventCameraGD> Object_Components::TriggerEventCameraGD() const
        {
            auto sub = getSubNode("TriggerEventCameraGD");
            return sub == nullptr? std::optional<Ent::Gen::TriggerEventCameraGD>{}: std::optional<Ent::Gen::TriggerEventCameraGD>(getSubNode("TriggerEventCameraGD"));
        }
        inline Ent::Gen::TriggerEventCameraGD Object_Components::addTriggerEventCameraGD() const
        {
            return Ent::Gen::TriggerEventCameraGD(addSubNode("TriggerEventCameraGD"));
        }
        inline std::optional<Ent::Gen::AnimationPlaylistGD> Object_Components::AnimationPlaylistGD() const
        {
            auto sub = getSubNode("AnimationPlaylistGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationPlaylistGD>{}: std::optional<Ent::Gen::AnimationPlaylistGD>(getSubNode("AnimationPlaylistGD"));
        }
        inline Ent::Gen::AnimationPlaylistGD Object_Components::addAnimationPlaylistGD() const
        {
            return Ent::Gen::AnimationPlaylistGD(addSubNode("AnimationPlaylistGD"));
        }
        inline std::optional<Ent::Gen::MeshNavigationInfosGD> Object_Components::MeshNavigationInfosGD() const
        {
            auto sub = getSubNode("MeshNavigationInfosGD");
            return sub == nullptr? std::optional<Ent::Gen::MeshNavigationInfosGD>{}: std::optional<Ent::Gen::MeshNavigationInfosGD>(getSubNode("MeshNavigationInfosGD"));
        }
        inline Ent::Gen::MeshNavigationInfosGD Object_Components::addMeshNavigationInfosGD() const
        {
            return Ent::Gen::MeshNavigationInfosGD(addSubNode("MeshNavigationInfosGD"));
        }
        inline std::optional<Ent::Gen::PhysicsTriggerGD> Object_Components::PhysicsTriggerGD() const
        {
            auto sub = getSubNode("PhysicsTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsTriggerGD>{}: std::optional<Ent::Gen::PhysicsTriggerGD>(getSubNode("PhysicsTriggerGD"));
        }
        inline Ent::Gen::PhysicsTriggerGD Object_Components::addPhysicsTriggerGD() const
        {
            return Ent::Gen::PhysicsTriggerGD(addSubNode("PhysicsTriggerGD"));
        }
        inline std::optional<Ent::Gen::EnergyNetworkListenerGD> Object_Components::EnergyNetworkListenerGD() const
        {
            auto sub = getSubNode("EnergyNetworkListenerGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyNetworkListenerGD>{}: std::optional<Ent::Gen::EnergyNetworkListenerGD>(getSubNode("EnergyNetworkListenerGD"));
        }
        inline Ent::Gen::EnergyNetworkListenerGD Object_Components::addEnergyNetworkListenerGD() const
        {
            return Ent::Gen::EnergyNetworkListenerGD(addSubNode("EnergyNetworkListenerGD"));
        }
        inline std::optional<Ent::Gen::MissionHolderGD> Object_Components::MissionHolderGD() const
        {
            auto sub = getSubNode("MissionHolderGD");
            return sub == nullptr? std::optional<Ent::Gen::MissionHolderGD>{}: std::optional<Ent::Gen::MissionHolderGD>(getSubNode("MissionHolderGD"));
        }
        inline Ent::Gen::MissionHolderGD Object_Components::addMissionHolderGD() const
        {
            return Ent::Gen::MissionHolderGD(addSubNode("MissionHolderGD"));
        }
        inline std::optional<Ent::Gen::RegenSwitcherGD> Object_Components::RegenSwitcherGD() const
        {
            auto sub = getSubNode("RegenSwitcherGD");
            return sub == nullptr? std::optional<Ent::Gen::RegenSwitcherGD>{}: std::optional<Ent::Gen::RegenSwitcherGD>(getSubNode("RegenSwitcherGD"));
        }
        inline Ent::Gen::RegenSwitcherGD Object_Components::addRegenSwitcherGD() const
        {
            return Ent::Gen::RegenSwitcherGD(addSubNode("RegenSwitcherGD"));
        }
        // Components
        inline char const* Components::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::StaticObjectGD> Components::StaticObjectGD() const
        {
            auto sub = getSubNode("StaticObjectGD");
            return sub == nullptr? std::optional<Ent::Gen::StaticObjectGD>{}: std::optional<Ent::Gen::StaticObjectGD>(getSubNode("StaticObjectGD"));
        }
        inline Ent::Gen::StaticObjectGD Components::addStaticObjectGD() const
        {
            return Ent::Gen::StaticObjectGD(addSubNode("StaticObjectGD"));
        }
        inline std::optional<Ent::Gen::AnimationControllerGD> Components::AnimationControllerGD() const
        {
            auto sub = getSubNode("AnimationControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationControllerGD>{}: std::optional<Ent::Gen::AnimationControllerGD>(getSubNode("AnimationControllerGD"));
        }
        inline Ent::Gen::AnimationControllerGD Components::addAnimationControllerGD() const
        {
            return Ent::Gen::AnimationControllerGD(addSubNode("AnimationControllerGD"));
        }
        inline std::optional<Ent::Gen::PhysicsDataGD> Components::PhysicsDataGD() const
        {
            auto sub = getSubNode("PhysicsDataGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsDataGD>{}: std::optional<Ent::Gen::PhysicsDataGD>(getSubNode("PhysicsDataGD"));
        }
        inline Ent::Gen::PhysicsDataGD Components::addPhysicsDataGD() const
        {
            return Ent::Gen::PhysicsDataGD(addSubNode("PhysicsDataGD"));
        }
        inline std::optional<Ent::Gen::VisualGD> Components::VisualGD() const
        {
            auto sub = getSubNode("VisualGD");
            return sub == nullptr? std::optional<Ent::Gen::VisualGD>{}: std::optional<Ent::Gen::VisualGD>(getSubNode("VisualGD"));
        }
        inline Ent::Gen::VisualGD Components::addVisualGD() const
        {
            return Ent::Gen::VisualGD(addSubNode("VisualGD"));
        }
        inline std::optional<Ent::Gen::TransformGD> Components::TransformGD() const
        {
            auto sub = getSubNode("TransformGD");
            return sub == nullptr? std::optional<Ent::Gen::TransformGD>{}: std::optional<Ent::Gen::TransformGD>(getSubNode("TransformGD"));
        }
        inline Ent::Gen::TransformGD Components::addTransformGD() const
        {
            return Ent::Gen::TransformGD(addSubNode("TransformGD"));
        }
        inline std::optional<Ent::Gen::TerrainGD> Components::TerrainGD() const
        {
            auto sub = getSubNode("TerrainGD");
            return sub == nullptr? std::optional<Ent::Gen::TerrainGD>{}: std::optional<Ent::Gen::TerrainGD>(getSubNode("TerrainGD"));
        }
        inline Ent::Gen::TerrainGD Components::addTerrainGD() const
        {
            return Ent::Gen::TerrainGD(addSubNode("TerrainGD"));
        }
        inline std::optional<Ent::Gen::PhysicsGD> Components::PhysicsGD() const
        {
            auto sub = getSubNode("PhysicsGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsGD>{}: std::optional<Ent::Gen::PhysicsGD>(getSubNode("PhysicsGD"));
        }
        inline Ent::Gen::PhysicsGD Components::addPhysicsGD() const
        {
            return Ent::Gen::PhysicsGD(addSubNode("PhysicsGD"));
        }
        inline std::optional<Ent::Gen::CustomThumbnail> Components::CustomThumbnail() const
        {
            auto sub = getSubNode("CustomThumbnail");
            return sub == nullptr? std::optional<Ent::Gen::CustomThumbnail>{}: std::optional<Ent::Gen::CustomThumbnail>(getSubNode("CustomThumbnail"));
        }
        inline Ent::Gen::CustomThumbnail Components::addCustomThumbnail() const
        {
            return Ent::Gen::CustomThumbnail(addSubNode("CustomThumbnail"));
        }
        inline std::optional<Ent::Gen::HeightObj> Components::HeightObj() const
        {
            auto sub = getSubNode("HeightObj");
            return sub == nullptr? std::optional<Ent::Gen::HeightObj>{}: std::optional<Ent::Gen::HeightObj>(getSubNode("HeightObj"));
        }
        inline Ent::Gen::HeightObj Components::addHeightObj() const
        {
            return Ent::Gen::HeightObj(addSubNode("HeightObj"));
        }
        inline std::optional<Ent::Gen::LDPrimitive> Components::LDPrimitive() const
        {
            auto sub = getSubNode("LDPrimitive");
            return sub == nullptr? std::optional<Ent::Gen::LDPrimitive>{}: std::optional<Ent::Gen::LDPrimitive>(getSubNode("LDPrimitive"));
        }
        inline Ent::Gen::LDPrimitive Components::addLDPrimitive() const
        {
            return Ent::Gen::LDPrimitive(addSubNode("LDPrimitive"));
        }
        inline std::optional<Ent::Gen::Mesh> Components::Mesh() const
        {
            auto sub = getSubNode("Mesh");
            return sub == nullptr? std::optional<Ent::Gen::Mesh>{}: std::optional<Ent::Gen::Mesh>(getSubNode("Mesh"));
        }
        inline Ent::Gen::Mesh Components::addMesh() const
        {
            return Ent::Gen::Mesh(addSubNode("Mesh"));
        }
        inline std::optional<Ent::Gen::MultiThumbnail> Components::MultiThumbnail() const
        {
            auto sub = getSubNode("MultiThumbnail");
            return sub == nullptr? std::optional<Ent::Gen::MultiThumbnail>{}: std::optional<Ent::Gen::MultiThumbnail>(getSubNode("MultiThumbnail"));
        }
        inline Ent::Gen::MultiThumbnail Components::addMultiThumbnail() const
        {
            return Ent::Gen::MultiThumbnail(addSubNode("MultiThumbnail"));
        }
        inline std::optional<Ent::Gen::NetworkLink> Components::NetworkLink() const
        {
            auto sub = getSubNode("NetworkLink");
            return sub == nullptr? std::optional<Ent::Gen::NetworkLink>{}: std::optional<Ent::Gen::NetworkLink>(getSubNode("NetworkLink"));
        }
        inline Ent::Gen::NetworkLink Components::addNetworkLink() const
        {
            return Ent::Gen::NetworkLink(addSubNode("NetworkLink"));
        }
        inline std::optional<Ent::Gen::NetworkNode> Components::NetworkNode() const
        {
            auto sub = getSubNode("NetworkNode");
            return sub == nullptr? std::optional<Ent::Gen::NetworkNode>{}: std::optional<Ent::Gen::NetworkNode>(getSubNode("NetworkNode"));
        }
        inline Ent::Gen::NetworkNode Components::addNetworkNode() const
        {
            return Ent::Gen::NetworkNode(addSubNode("NetworkNode"));
        }
        inline std::optional<Ent::Gen::NotVisibleInSubscene> Components::NotVisibleInSubscene() const
        {
            auto sub = getSubNode("NotVisibleInSubscene");
            return sub == nullptr? std::optional<Ent::Gen::NotVisibleInSubscene>{}: std::optional<Ent::Gen::NotVisibleInSubscene>(getSubNode("NotVisibleInSubscene"));
        }
        inline Ent::Gen::NotVisibleInSubscene Components::addNotVisibleInSubscene() const
        {
            return Ent::Gen::NotVisibleInSubscene(addSubNode("NotVisibleInSubscene"));
        }
        inline std::optional<Ent::Gen::SeedPatch> Components::SeedPatch() const
        {
            auto sub = getSubNode("SeedPatch");
            return sub == nullptr? std::optional<Ent::Gen::SeedPatch>{}: std::optional<Ent::Gen::SeedPatch>(getSubNode("SeedPatch"));
        }
        inline Ent::Gen::SeedPatch Components::addSeedPatch() const
        {
            return Ent::Gen::SeedPatch(addSubNode("SeedPatch"));
        }
        inline std::optional<Ent::Gen::StickToTerrain> Components::StickToTerrain() const
        {
            auto sub = getSubNode("StickToTerrain");
            return sub == nullptr? std::optional<Ent::Gen::StickToTerrain>{}: std::optional<Ent::Gen::StickToTerrain>(getSubNode("StickToTerrain"));
        }
        inline Ent::Gen::StickToTerrain Components::addStickToTerrain() const
        {
            return Ent::Gen::StickToTerrain(addSubNode("StickToTerrain"));
        }
        inline std::optional<Ent::Gen::SubScene> Components::SubScene() const
        {
            auto sub = getSubNode("SubScene");
            return sub == nullptr? std::optional<Ent::Gen::SubScene>{}: std::optional<Ent::Gen::SubScene>(getSubNode("SubScene"));
        }
        inline Ent::Gen::SubScene Components::addSubScene() const
        {
            return Ent::Gen::SubScene(addSubNode("SubScene"));
        }
        inline std::optional<Ent::Gen::SystemicCreature> Components::SystemicCreature() const
        {
            auto sub = getSubNode("SystemicCreature");
            return sub == nullptr? std::optional<Ent::Gen::SystemicCreature>{}: std::optional<Ent::Gen::SystemicCreature>(getSubNode("SystemicCreature"));
        }
        inline Ent::Gen::SystemicCreature Components::addSystemicCreature() const
        {
            return Ent::Gen::SystemicCreature(addSubNode("SystemicCreature"));
        }
        inline std::optional<Ent::Gen::TerrainSurfaceObject> Components::TerrainSurfaceObject() const
        {
            auto sub = getSubNode("TerrainSurfaceObject");
            return sub == nullptr? std::optional<Ent::Gen::TerrainSurfaceObject>{}: std::optional<Ent::Gen::TerrainSurfaceObject>(getSubNode("TerrainSurfaceObject"));
        }
        inline Ent::Gen::TerrainSurfaceObject Components::addTerrainSurfaceObject() const
        {
            return Ent::Gen::TerrainSurfaceObject(addSubNode("TerrainSurfaceObject"));
        }
        inline std::optional<Ent::Gen::TestArrays> Components::TestArrays() const
        {
            auto sub = getSubNode("TestArrays");
            return sub == nullptr? std::optional<Ent::Gen::TestArrays>{}: std::optional<Ent::Gen::TestArrays>(getSubNode("TestArrays"));
        }
        inline Ent::Gen::TestArrays Components::addTestArrays() const
        {
            return Ent::Gen::TestArrays(addSubNode("TestArrays"));
        }
        inline std::optional<Ent::Gen::TestCreature> Components::TestCreature() const
        {
            auto sub = getSubNode("TestCreature");
            return sub == nullptr? std::optional<Ent::Gen::TestCreature>{}: std::optional<Ent::Gen::TestCreature>(getSubNode("TestCreature"));
        }
        inline Ent::Gen::TestCreature Components::addTestCreature() const
        {
            return Ent::Gen::TestCreature(addSubNode("TestCreature"));
        }
        inline std::optional<Ent::Gen::TestDefaultValues> Components::TestDefaultValues() const
        {
            auto sub = getSubNode("TestDefaultValues");
            return sub == nullptr? std::optional<Ent::Gen::TestDefaultValues>{}: std::optional<Ent::Gen::TestDefaultValues>(getSubNode("TestDefaultValues"));
        }
        inline Ent::Gen::TestDefaultValues Components::addTestDefaultValues() const
        {
            return Ent::Gen::TestDefaultValues(addSubNode("TestDefaultValues"));
        }
        inline std::optional<Ent::Gen::TestEntityRef> Components::TestEntityRef() const
        {
            auto sub = getSubNode("TestEntityRef");
            return sub == nullptr? std::optional<Ent::Gen::TestEntityRef>{}: std::optional<Ent::Gen::TestEntityRef>(getSubNode("TestEntityRef"));
        }
        inline Ent::Gen::TestEntityRef Components::addTestEntityRef() const
        {
            return Ent::Gen::TestEntityRef(addSubNode("TestEntityRef"));
        }
        inline std::optional<Ent::Gen::TestSetOfObject> Components::TestSetOfObject() const
        {
            auto sub = getSubNode("TestSetOfObject");
            return sub == nullptr? std::optional<Ent::Gen::TestSetOfObject>{}: std::optional<Ent::Gen::TestSetOfObject>(getSubNode("TestSetOfObject"));
        }
        inline Ent::Gen::TestSetOfObject Components::addTestSetOfObject() const
        {
            return Ent::Gen::TestSetOfObject(addSubNode("TestSetOfObject"));
        }
        inline std::optional<Ent::Gen::TestUnion> Components::TestUnion() const
        {
            auto sub = getSubNode("TestUnion");
            return sub == nullptr? std::optional<Ent::Gen::TestUnion>{}: std::optional<Ent::Gen::TestUnion>(getSubNode("TestUnion"));
        }
        inline Ent::Gen::TestUnion Components::addTestUnion() const
        {
            return Ent::Gen::TestUnion(addSubNode("TestUnion"));
        }
        inline std::optional<Ent::Gen::UnitTestComponent> Components::UnitTestComponent() const
        {
            auto sub = getSubNode("UnitTestComponent");
            return sub == nullptr? std::optional<Ent::Gen::UnitTestComponent>{}: std::optional<Ent::Gen::UnitTestComponent>(getSubNode("UnitTestComponent"));
        }
        inline Ent::Gen::UnitTestComponent Components::addUnitTestComponent() const
        {
            return Ent::Gen::UnitTestComponent(addSubNode("UnitTestComponent"));
        }
        inline std::optional<Ent::Gen::WildObject> Components::WildObject() const
        {
            auto sub = getSubNode("WildObject");
            return sub == nullptr? std::optional<Ent::Gen::WildObject>{}: std::optional<Ent::Gen::WildObject>(getSubNode("WildObject"));
        }
        inline Ent::Gen::WildObject Components::addWildObject() const
        {
            return Ent::Gen::WildObject(addSubNode("WildObject"));
        }
        inline std::optional<Ent::Gen::EnergyCrookGD> Components::EnergyCrookGD() const
        {
            auto sub = getSubNode("EnergyCrookGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyCrookGD>{}: std::optional<Ent::Gen::EnergyCrookGD>(getSubNode("EnergyCrookGD"));
        }
        inline Ent::Gen::EnergyCrookGD Components::addEnergyCrookGD() const
        {
            return Ent::Gen::EnergyCrookGD(addSubNode("EnergyCrookGD"));
        }
        inline std::optional<Ent::Gen::AIContextGD> Components::AIContextGD() const
        {
            auto sub = getSubNode("AIContextGD");
            return sub == nullptr? std::optional<Ent::Gen::AIContextGD>{}: std::optional<Ent::Gen::AIContextGD>(getSubNode("AIContextGD"));
        }
        inline Ent::Gen::AIContextGD Components::addAIContextGD() const
        {
            return Ent::Gen::AIContextGD(addSubNode("AIContextGD"));
        }
        inline std::optional<Ent::Gen::EventTriggerGD> Components::EventTriggerGD() const
        {
            auto sub = getSubNode("EventTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::EventTriggerGD>{}: std::optional<Ent::Gen::EventTriggerGD>(getSubNode("EventTriggerGD"));
        }
        inline Ent::Gen::EventTriggerGD Components::addEventTriggerGD() const
        {
            return Ent::Gen::EventTriggerGD(addSubNode("EventTriggerGD"));
        }
        inline std::optional<Ent::Gen::BeamGeneratorGD> Components::BeamGeneratorGD() const
        {
            auto sub = getSubNode("BeamGeneratorGD");
            return sub == nullptr? std::optional<Ent::Gen::BeamGeneratorGD>{}: std::optional<Ent::Gen::BeamGeneratorGD>(getSubNode("BeamGeneratorGD"));
        }
        inline Ent::Gen::BeamGeneratorGD Components::addBeamGeneratorGD() const
        {
            return Ent::Gen::BeamGeneratorGD(addSubNode("BeamGeneratorGD"));
        }
        inline std::optional<Ent::Gen::WorldScalePathFindGD> Components::WorldScalePathFindGD() const
        {
            auto sub = getSubNode("WorldScalePathFindGD");
            return sub == nullptr? std::optional<Ent::Gen::WorldScalePathFindGD>{}: std::optional<Ent::Gen::WorldScalePathFindGD>(getSubNode("WorldScalePathFindGD"));
        }
        inline Ent::Gen::WorldScalePathFindGD Components::addWorldScalePathFindGD() const
        {
            return Ent::Gen::WorldScalePathFindGD(addSubNode("WorldScalePathFindGD"));
        }
        inline std::optional<Ent::Gen::NetGD> Components::NetGD() const
        {
            auto sub = getSubNode("NetGD");
            return sub == nullptr? std::optional<Ent::Gen::NetGD>{}: std::optional<Ent::Gen::NetGD>(getSubNode("NetGD"));
        }
        inline Ent::Gen::NetGD Components::addNetGD() const
        {
            return Ent::Gen::NetGD(addSubNode("NetGD"));
        }
        inline std::optional<Ent::Gen::BittenGD> Components::BittenGD() const
        {
            auto sub = getSubNode("BittenGD");
            return sub == nullptr? std::optional<Ent::Gen::BittenGD>{}: std::optional<Ent::Gen::BittenGD>(getSubNode("BittenGD"));
        }
        inline Ent::Gen::BittenGD Components::addBittenGD() const
        {
            return Ent::Gen::BittenGD(addSubNode("BittenGD"));
        }
        inline std::optional<Ent::Gen::PathBoneAnimGD> Components::PathBoneAnimGD() const
        {
            auto sub = getSubNode("PathBoneAnimGD");
            return sub == nullptr? std::optional<Ent::Gen::PathBoneAnimGD>{}: std::optional<Ent::Gen::PathBoneAnimGD>(getSubNode("PathBoneAnimGD"));
        }
        inline Ent::Gen::PathBoneAnimGD Components::addPathBoneAnimGD() const
        {
            return Ent::Gen::PathBoneAnimGD(addSubNode("PathBoneAnimGD"));
        }
        inline std::optional<Ent::Gen::AnimationRegenConstraintsGD> Components::AnimationRegenConstraintsGD() const
        {
            auto sub = getSubNode("AnimationRegenConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationRegenConstraintsGD>{}: std::optional<Ent::Gen::AnimationRegenConstraintsGD>(getSubNode("AnimationRegenConstraintsGD"));
        }
        inline Ent::Gen::AnimationRegenConstraintsGD Components::addAnimationRegenConstraintsGD() const
        {
            return Ent::Gen::AnimationRegenConstraintsGD(addSubNode("AnimationRegenConstraintsGD"));
        }
        inline std::optional<Ent::Gen::HealPumpGD> Components::HealPumpGD() const
        {
            auto sub = getSubNode("HealPumpGD");
            return sub == nullptr? std::optional<Ent::Gen::HealPumpGD>{}: std::optional<Ent::Gen::HealPumpGD>(getSubNode("HealPumpGD"));
        }
        inline Ent::Gen::HealPumpGD Components::addHealPumpGD() const
        {
            return Ent::Gen::HealPumpGD(addSubNode("HealPumpGD"));
        }
        inline std::optional<Ent::Gen::GroundTypeSamplerGD> Components::GroundTypeSamplerGD() const
        {
            auto sub = getSubNode("GroundTypeSamplerGD");
            return sub == nullptr? std::optional<Ent::Gen::GroundTypeSamplerGD>{}: std::optional<Ent::Gen::GroundTypeSamplerGD>(getSubNode("GroundTypeSamplerGD"));
        }
        inline Ent::Gen::GroundTypeSamplerGD Components::addGroundTypeSamplerGD() const
        {
            return Ent::Gen::GroundTypeSamplerGD(addSubNode("GroundTypeSamplerGD"));
        }
        inline std::optional<Ent::Gen::UnifiedPhysicsDataGD> Components::UnifiedPhysicsDataGD() const
        {
            auto sub = getSubNode("UnifiedPhysicsDataGD");
            return sub == nullptr? std::optional<Ent::Gen::UnifiedPhysicsDataGD>{}: std::optional<Ent::Gen::UnifiedPhysicsDataGD>(getSubNode("UnifiedPhysicsDataGD"));
        }
        inline Ent::Gen::UnifiedPhysicsDataGD Components::addUnifiedPhysicsDataGD() const
        {
            return Ent::Gen::UnifiedPhysicsDataGD(addSubNode("UnifiedPhysicsDataGD"));
        }
        inline std::optional<Ent::Gen::FluidGD> Components::FluidGD() const
        {
            auto sub = getSubNode("FluidGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidGD>{}: std::optional<Ent::Gen::FluidGD>(getSubNode("FluidGD"));
        }
        inline Ent::Gen::FluidGD Components::addFluidGD() const
        {
            return Ent::Gen::FluidGD(addSubNode("FluidGD"));
        }
        inline std::optional<Ent::Gen::ProjectileGD> Components::ProjectileGD() const
        {
            auto sub = getSubNode("ProjectileGD");
            return sub == nullptr? std::optional<Ent::Gen::ProjectileGD>{}: std::optional<Ent::Gen::ProjectileGD>(getSubNode("ProjectileGD"));
        }
        inline Ent::Gen::ProjectileGD Components::addProjectileGD() const
        {
            return Ent::Gen::ProjectileGD(addSubNode("ProjectileGD"));
        }
        inline std::optional<Ent::Gen::CameraSetterGD> Components::CameraSetterGD() const
        {
            auto sub = getSubNode("CameraSetterGD");
            return sub == nullptr? std::optional<Ent::Gen::CameraSetterGD>{}: std::optional<Ent::Gen::CameraSetterGD>(getSubNode("CameraSetterGD"));
        }
        inline Ent::Gen::CameraSetterGD Components::addCameraSetterGD() const
        {
            return Ent::Gen::CameraSetterGD(addSubNode("CameraSetterGD"));
        }
        inline std::optional<Ent::Gen::AssemblyGD> Components::AssemblyGD() const
        {
            auto sub = getSubNode("AssemblyGD");
            return sub == nullptr? std::optional<Ent::Gen::AssemblyGD>{}: std::optional<Ent::Gen::AssemblyGD>(getSubNode("AssemblyGD"));
        }
        inline Ent::Gen::AssemblyGD Components::addAssemblyGD() const
        {
            return Ent::Gen::AssemblyGD(addSubNode("AssemblyGD"));
        }
        inline std::optional<Ent::Gen::SmoothScaleComponentGD> Components::SmoothScaleComponentGD() const
        {
            auto sub = getSubNode("SmoothScaleComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::SmoothScaleComponentGD>{}: std::optional<Ent::Gen::SmoothScaleComponentGD>(getSubNode("SmoothScaleComponentGD"));
        }
        inline Ent::Gen::SmoothScaleComponentGD Components::addSmoothScaleComponentGD() const
        {
            return Ent::Gen::SmoothScaleComponentGD(addSubNode("SmoothScaleComponentGD"));
        }
        inline std::optional<Ent::Gen::FluidViewGD> Components::FluidViewGD() const
        {
            auto sub = getSubNode("FluidViewGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidViewGD>{}: std::optional<Ent::Gen::FluidViewGD>(getSubNode("FluidViewGD"));
        }
        inline Ent::Gen::FluidViewGD Components::addFluidViewGD() const
        {
            return Ent::Gen::FluidViewGD(addSubNode("FluidViewGD"));
        }
        inline std::optional<Ent::Gen::RegenMeshGD> Components::RegenMeshGD() const
        {
            auto sub = getSubNode("RegenMeshGD");
            return sub == nullptr? std::optional<Ent::Gen::RegenMeshGD>{}: std::optional<Ent::Gen::RegenMeshGD>(getSubNode("RegenMeshGD"));
        }
        inline Ent::Gen::RegenMeshGD Components::addRegenMeshGD() const
        {
            return Ent::Gen::RegenMeshGD(addSubNode("RegenMeshGD"));
        }
        inline std::optional<Ent::Gen::ReviveEnergyGD> Components::ReviveEnergyGD() const
        {
            auto sub = getSubNode("ReviveEnergyGD");
            return sub == nullptr? std::optional<Ent::Gen::ReviveEnergyGD>{}: std::optional<Ent::Gen::ReviveEnergyGD>(getSubNode("ReviveEnergyGD"));
        }
        inline Ent::Gen::ReviveEnergyGD Components::addReviveEnergyGD() const
        {
            return Ent::Gen::ReviveEnergyGD(addSubNode("ReviveEnergyGD"));
        }
        inline std::optional<Ent::Gen::DebugGridGD> Components::DebugGridGD() const
        {
            auto sub = getSubNode("DebugGridGD");
            return sub == nullptr? std::optional<Ent::Gen::DebugGridGD>{}: std::optional<Ent::Gen::DebugGridGD>(getSubNode("DebugGridGD"));
        }
        inline Ent::Gen::DebugGridGD Components::addDebugGridGD() const
        {
            return Ent::Gen::DebugGridGD(addSubNode("DebugGridGD"));
        }
        inline std::optional<Ent::Gen::ChildEntityPoolComponentGD> Components::ChildEntityPoolComponentGD() const
        {
            auto sub = getSubNode("ChildEntityPoolComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::ChildEntityPoolComponentGD>{}: std::optional<Ent::Gen::ChildEntityPoolComponentGD>(getSubNode("ChildEntityPoolComponentGD"));
        }
        inline Ent::Gen::ChildEntityPoolComponentGD Components::addChildEntityPoolComponentGD() const
        {
            return Ent::Gen::ChildEntityPoolComponentGD(addSubNode("ChildEntityPoolComponentGD"));
        }
        inline std::optional<Ent::Gen::ProtoComponentGD> Components::ProtoComponentGD() const
        {
            auto sub = getSubNode("ProtoComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::ProtoComponentGD>{}: std::optional<Ent::Gen::ProtoComponentGD>(getSubNode("ProtoComponentGD"));
        }
        inline Ent::Gen::ProtoComponentGD Components::addProtoComponentGD() const
        {
            return Ent::Gen::ProtoComponentGD(addSubNode("ProtoComponentGD"));
        }
        inline std::optional<Ent::Gen::GameEffectSpawnerGD> Components::GameEffectSpawnerGD() const
        {
            auto sub = getSubNode("GameEffectSpawnerGD");
            return sub == nullptr? std::optional<Ent::Gen::GameEffectSpawnerGD>{}: std::optional<Ent::Gen::GameEffectSpawnerGD>(getSubNode("GameEffectSpawnerGD"));
        }
        inline Ent::Gen::GameEffectSpawnerGD Components::addGameEffectSpawnerGD() const
        {
            return Ent::Gen::GameEffectSpawnerGD(addSubNode("GameEffectSpawnerGD"));
        }
        inline std::optional<Ent::Gen::ClothGD> Components::ClothGD() const
        {
            auto sub = getSubNode("ClothGD");
            return sub == nullptr? std::optional<Ent::Gen::ClothGD>{}: std::optional<Ent::Gen::ClothGD>(getSubNode("ClothGD"));
        }
        inline Ent::Gen::ClothGD Components::addClothGD() const
        {
            return Ent::Gen::ClothGD(addSubNode("ClothGD"));
        }
        inline std::optional<Ent::Gen::FireSensorGD> Components::FireSensorGD() const
        {
            auto sub = getSubNode("FireSensorGD");
            return sub == nullptr? std::optional<Ent::Gen::FireSensorGD>{}: std::optional<Ent::Gen::FireSensorGD>(getSubNode("FireSensorGD"));
        }
        inline Ent::Gen::FireSensorGD Components::addFireSensorGD() const
        {
            return Ent::Gen::FireSensorGD(addSubNode("FireSensorGD"));
        }
        inline std::optional<Ent::Gen::HealerGD> Components::HealerGD() const
        {
            auto sub = getSubNode("HealerGD");
            return sub == nullptr? std::optional<Ent::Gen::HealerGD>{}: std::optional<Ent::Gen::HealerGD>(getSubNode("HealerGD"));
        }
        inline Ent::Gen::HealerGD Components::addHealerGD() const
        {
            return Ent::Gen::HealerGD(addSubNode("HealerGD"));
        }
        inline std::optional<Ent::Gen::AnimationLegsConstraintsGD> Components::AnimationLegsConstraintsGD() const
        {
            auto sub = getSubNode("AnimationLegsConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationLegsConstraintsGD>{}: std::optional<Ent::Gen::AnimationLegsConstraintsGD>(getSubNode("AnimationLegsConstraintsGD"));
        }
        inline Ent::Gen::AnimationLegsConstraintsGD Components::addAnimationLegsConstraintsGD() const
        {
            return Ent::Gen::AnimationLegsConstraintsGD(addSubNode("AnimationLegsConstraintsGD"));
        }
        inline std::optional<Ent::Gen::PathBoneRigidBodyGD> Components::PathBoneRigidBodyGD() const
        {
            auto sub = getSubNode("PathBoneRigidBodyGD");
            return sub == nullptr? std::optional<Ent::Gen::PathBoneRigidBodyGD>{}: std::optional<Ent::Gen::PathBoneRigidBodyGD>(getSubNode("PathBoneRigidBodyGD"));
        }
        inline Ent::Gen::PathBoneRigidBodyGD Components::addPathBoneRigidBodyGD() const
        {
            return Ent::Gen::PathBoneRigidBodyGD(addSubNode("PathBoneRigidBodyGD"));
        }
        inline std::optional<Ent::Gen::FightDistanceTriggerGD> Components::FightDistanceTriggerGD() const
        {
            auto sub = getSubNode("FightDistanceTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::FightDistanceTriggerGD>{}: std::optional<Ent::Gen::FightDistanceTriggerGD>(getSubNode("FightDistanceTriggerGD"));
        }
        inline Ent::Gen::FightDistanceTriggerGD Components::addFightDistanceTriggerGD() const
        {
            return Ent::Gen::FightDistanceTriggerGD(addSubNode("FightDistanceTriggerGD"));
        }
        inline std::optional<Ent::Gen::SoulSpotGD> Components::SoulSpotGD() const
        {
            auto sub = getSubNode("SoulSpotGD");
            return sub == nullptr? std::optional<Ent::Gen::SoulSpotGD>{}: std::optional<Ent::Gen::SoulSpotGD>(getSubNode("SoulSpotGD"));
        }
        inline Ent::Gen::SoulSpotGD Components::addSoulSpotGD() const
        {
            return Ent::Gen::SoulSpotGD(addSubNode("SoulSpotGD"));
        }
        inline std::optional<Ent::Gen::HealTriggerGD> Components::HealTriggerGD() const
        {
            auto sub = getSubNode("HealTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::HealTriggerGD>{}: std::optional<Ent::Gen::HealTriggerGD>(getSubNode("HealTriggerGD"));
        }
        inline Ent::Gen::HealTriggerGD Components::addHealTriggerGD() const
        {
            return Ent::Gen::HealTriggerGD(addSubNode("HealTriggerGD"));
        }
        inline std::optional<Ent::Gen::AnimationTailConstraintsGD> Components::AnimationTailConstraintsGD() const
        {
            auto sub = getSubNode("AnimationTailConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationTailConstraintsGD>{}: std::optional<Ent::Gen::AnimationTailConstraintsGD>(getSubNode("AnimationTailConstraintsGD"));
        }
        inline Ent::Gen::AnimationTailConstraintsGD Components::addAnimationTailConstraintsGD() const
        {
            return Ent::Gen::AnimationTailConstraintsGD(addSubNode("AnimationTailConstraintsGD"));
        }
        inline std::optional<Ent::Gen::VolumeConstraintGD> Components::VolumeConstraintGD() const
        {
            auto sub = getSubNode("VolumeConstraintGD");
            return sub == nullptr? std::optional<Ent::Gen::VolumeConstraintGD>{}: std::optional<Ent::Gen::VolumeConstraintGD>(getSubNode("VolumeConstraintGD"));
        }
        inline Ent::Gen::VolumeConstraintGD Components::addVolumeConstraintGD() const
        {
            return Ent::Gen::VolumeConstraintGD(addSubNode("VolumeConstraintGD"));
        }
        inline std::optional<Ent::Gen::EnvStampGD> Components::EnvStampGD() const
        {
            auto sub = getSubNode("EnvStampGD");
            return sub == nullptr? std::optional<Ent::Gen::EnvStampGD>{}: std::optional<Ent::Gen::EnvStampGD>(getSubNode("EnvStampGD"));
        }
        inline Ent::Gen::EnvStampGD Components::addEnvStampGD() const
        {
            return Ent::Gen::EnvStampGD(addSubNode("EnvStampGD"));
        }
        inline std::optional<Ent::Gen::FluidFXEntitySpawnerGD> Components::FluidFXEntitySpawnerGD() const
        {
            auto sub = getSubNode("FluidFXEntitySpawnerGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidFXEntitySpawnerGD>{}: std::optional<Ent::Gen::FluidFXEntitySpawnerGD>(getSubNode("FluidFXEntitySpawnerGD"));
        }
        inline Ent::Gen::FluidFXEntitySpawnerGD Components::addFluidFXEntitySpawnerGD() const
        {
            return Ent::Gen::FluidFXEntitySpawnerGD(addSubNode("FluidFXEntitySpawnerGD"));
        }
        inline std::optional<Ent::Gen::EnergyDrainGD> Components::EnergyDrainGD() const
        {
            auto sub = getSubNode("EnergyDrainGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyDrainGD>{}: std::optional<Ent::Gen::EnergyDrainGD>(getSubNode("EnergyDrainGD"));
        }
        inline Ent::Gen::EnergyDrainGD Components::addEnergyDrainGD() const
        {
            return Ent::Gen::EnergyDrainGD(addSubNode("EnergyDrainGD"));
        }
        inline std::optional<Ent::Gen::AnimationEventsGeneratorGD> Components::AnimationEventsGeneratorGD() const
        {
            auto sub = getSubNode("AnimationEventsGeneratorGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationEventsGeneratorGD>{}: std::optional<Ent::Gen::AnimationEventsGeneratorGD>(getSubNode("AnimationEventsGeneratorGD"));
        }
        inline Ent::Gen::AnimationEventsGeneratorGD Components::addAnimationEventsGeneratorGD() const
        {
            return Ent::Gen::AnimationEventsGeneratorGD(addSubNode("AnimationEventsGeneratorGD"));
        }
        inline std::optional<Ent::Gen::MountableGD> Components::MountableGD() const
        {
            auto sub = getSubNode("MountableGD");
            return sub == nullptr? std::optional<Ent::Gen::MountableGD>{}: std::optional<Ent::Gen::MountableGD>(getSubNode("MountableGD"));
        }
        inline Ent::Gen::MountableGD Components::addMountableGD() const
        {
            return Ent::Gen::MountableGD(addSubNode("MountableGD"));
        }
        inline std::optional<Ent::Gen::InfoboardRegistererGD> Components::InfoboardRegistererGD() const
        {
            auto sub = getSubNode("InfoboardRegistererGD");
            return sub == nullptr? std::optional<Ent::Gen::InfoboardRegistererGD>{}: std::optional<Ent::Gen::InfoboardRegistererGD>(getSubNode("InfoboardRegistererGD"));
        }
        inline Ent::Gen::InfoboardRegistererGD Components::addInfoboardRegistererGD() const
        {
            return Ent::Gen::InfoboardRegistererGD(addSubNode("InfoboardRegistererGD"));
        }
        inline std::optional<Ent::Gen::EventHandlerGD> Components::EventHandlerGD() const
        {
            auto sub = getSubNode("EventHandlerGD");
            return sub == nullptr? std::optional<Ent::Gen::EventHandlerGD>{}: std::optional<Ent::Gen::EventHandlerGD>(getSubNode("EventHandlerGD"));
        }
        inline Ent::Gen::EventHandlerGD Components::addEventHandlerGD() const
        {
            return Ent::Gen::EventHandlerGD(addSubNode("EventHandlerGD"));
        }
        inline std::optional<Ent::Gen::SoulRespawnOpportunityGD> Components::SoulRespawnOpportunityGD() const
        {
            auto sub = getSubNode("SoulRespawnOpportunityGD");
            return sub == nullptr? std::optional<Ent::Gen::SoulRespawnOpportunityGD>{}: std::optional<Ent::Gen::SoulRespawnOpportunityGD>(getSubNode("SoulRespawnOpportunityGD"));
        }
        inline Ent::Gen::SoulRespawnOpportunityGD Components::addSoulRespawnOpportunityGD() const
        {
            return Ent::Gen::SoulRespawnOpportunityGD(addSubNode("SoulRespawnOpportunityGD"));
        }
        inline std::optional<Ent::Gen::HealthAreaGD> Components::HealthAreaGD() const
        {
            auto sub = getSubNode("HealthAreaGD");
            return sub == nullptr? std::optional<Ent::Gen::HealthAreaGD>{}: std::optional<Ent::Gen::HealthAreaGD>(getSubNode("HealthAreaGD"));
        }
        inline Ent::Gen::HealthAreaGD Components::addHealthAreaGD() const
        {
            return Ent::Gen::HealthAreaGD(addSubNode("HealthAreaGD"));
        }
        inline std::optional<Ent::Gen::SoundAreaGD> Components::SoundAreaGD() const
        {
            auto sub = getSubNode("SoundAreaGD");
            return sub == nullptr? std::optional<Ent::Gen::SoundAreaGD>{}: std::optional<Ent::Gen::SoundAreaGD>(getSubNode("SoundAreaGD"));
        }
        inline Ent::Gen::SoundAreaGD Components::addSoundAreaGD() const
        {
            return Ent::Gen::SoundAreaGD(addSubNode("SoundAreaGD"));
        }
        inline std::optional<Ent::Gen::PathBoneInfluenceGD> Components::PathBoneInfluenceGD() const
        {
            auto sub = getSubNode("PathBoneInfluenceGD");
            return sub == nullptr? std::optional<Ent::Gen::PathBoneInfluenceGD>{}: std::optional<Ent::Gen::PathBoneInfluenceGD>(getSubNode("PathBoneInfluenceGD"));
        }
        inline Ent::Gen::PathBoneInfluenceGD Components::addPathBoneInfluenceGD() const
        {
            return Ent::Gen::PathBoneInfluenceGD(addSubNode("PathBoneInfluenceGD"));
        }
        inline std::optional<Ent::Gen::ComponentWithProtoCodeGD> Components::ComponentWithProtoCodeGD() const
        {
            auto sub = getSubNode("ComponentWithProtoCodeGD");
            return sub == nullptr? std::optional<Ent::Gen::ComponentWithProtoCodeGD>{}: std::optional<Ent::Gen::ComponentWithProtoCodeGD>(getSubNode("ComponentWithProtoCodeGD"));
        }
        inline Ent::Gen::ComponentWithProtoCodeGD Components::addComponentWithProtoCodeGD() const
        {
            return Ent::Gen::ComponentWithProtoCodeGD(addSubNode("ComponentWithProtoCodeGD"));
        }
        inline std::optional<Ent::Gen::CharacterControllerGD> Components::CharacterControllerGD() const
        {
            auto sub = getSubNode("CharacterControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::CharacterControllerGD>{}: std::optional<Ent::Gen::CharacterControllerGD>(getSubNode("CharacterControllerGD"));
        }
        inline Ent::Gen::CharacterControllerGD Components::addCharacterControllerGD() const
        {
            return Ent::Gen::CharacterControllerGD(addSubNode("CharacterControllerGD"));
        }
        inline std::optional<Ent::Gen::PickableComponentGD> Components::PickableComponentGD() const
        {
            auto sub = getSubNode("PickableComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::PickableComponentGD>{}: std::optional<Ent::Gen::PickableComponentGD>(getSubNode("PickableComponentGD"));
        }
        inline Ent::Gen::PickableComponentGD Components::addPickableComponentGD() const
        {
            return Ent::Gen::PickableComponentGD(addSubNode("PickableComponentGD"));
        }
        inline std::optional<Ent::Gen::CameraDataGD> Components::CameraDataGD() const
        {
            auto sub = getSubNode("CameraDataGD");
            return sub == nullptr? std::optional<Ent::Gen::CameraDataGD>{}: std::optional<Ent::Gen::CameraDataGD>(getSubNode("CameraDataGD"));
        }
        inline Ent::Gen::CameraDataGD Components::addCameraDataGD() const
        {
            return Ent::Gen::CameraDataGD(addSubNode("CameraDataGD"));
        }
        inline std::optional<Ent::Gen::RegenFXGD> Components::RegenFXGD() const
        {
            auto sub = getSubNode("RegenFXGD");
            return sub == nullptr? std::optional<Ent::Gen::RegenFXGD>{}: std::optional<Ent::Gen::RegenFXGD>(getSubNode("RegenFXGD"));
        }
        inline Ent::Gen::RegenFXGD Components::addRegenFXGD() const
        {
            return Ent::Gen::RegenFXGD(addSubNode("RegenFXGD"));
        }
        inline std::optional<Ent::Gen::PhysicsMeshDeformerGD> Components::PhysicsMeshDeformerGD() const
        {
            auto sub = getSubNode("PhysicsMeshDeformerGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsMeshDeformerGD>{}: std::optional<Ent::Gen::PhysicsMeshDeformerGD>(getSubNode("PhysicsMeshDeformerGD"));
        }
        inline Ent::Gen::PhysicsMeshDeformerGD Components::addPhysicsMeshDeformerGD() const
        {
            return Ent::Gen::PhysicsMeshDeformerGD(addSubNode("PhysicsMeshDeformerGD"));
        }
        inline std::optional<Ent::Gen::AnimationHitsConstraintsGD> Components::AnimationHitsConstraintsGD() const
        {
            auto sub = getSubNode("AnimationHitsConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationHitsConstraintsGD>{}: std::optional<Ent::Gen::AnimationHitsConstraintsGD>(getSubNode("AnimationHitsConstraintsGD"));
        }
        inline Ent::Gen::AnimationHitsConstraintsGD Components::addAnimationHitsConstraintsGD() const
        {
            return Ent::Gen::AnimationHitsConstraintsGD(addSubNode("AnimationHitsConstraintsGD"));
        }
        inline std::optional<Ent::Gen::FluidVolumeComponentGD> Components::FluidVolumeComponentGD() const
        {
            auto sub = getSubNode("FluidVolumeComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidVolumeComponentGD>{}: std::optional<Ent::Gen::FluidVolumeComponentGD>(getSubNode("FluidVolumeComponentGD"));
        }
        inline Ent::Gen::FluidVolumeComponentGD Components::addFluidVolumeComponentGD() const
        {
            return Ent::Gen::FluidVolumeComponentGD(addSubNode("FluidVolumeComponentGD"));
        }
        inline std::optional<Ent::Gen::RegenerableVegetationGD> Components::RegenerableVegetationGD() const
        {
            auto sub = getSubNode("RegenerableVegetationGD");
            return sub == nullptr? std::optional<Ent::Gen::RegenerableVegetationGD>{}: std::optional<Ent::Gen::RegenerableVegetationGD>(getSubNode("RegenerableVegetationGD"));
        }
        inline Ent::Gen::RegenerableVegetationGD Components::addRegenerableVegetationGD() const
        {
            return Ent::Gen::RegenerableVegetationGD(addSubNode("RegenerableVegetationGD"));
        }
        inline std::optional<Ent::Gen::ShamanVisionGD> Components::ShamanVisionGD() const
        {
            auto sub = getSubNode("ShamanVisionGD");
            return sub == nullptr? std::optional<Ent::Gen::ShamanVisionGD>{}: std::optional<Ent::Gen::ShamanVisionGD>(getSubNode("ShamanVisionGD"));
        }
        inline Ent::Gen::ShamanVisionGD Components::addShamanVisionGD() const
        {
            return Ent::Gen::ShamanVisionGD(addSubNode("ShamanVisionGD"));
        }
        inline std::optional<Ent::Gen::CinematicGD> Components::CinematicGD() const
        {
            auto sub = getSubNode("CinematicGD");
            return sub == nullptr? std::optional<Ent::Gen::CinematicGD>{}: std::optional<Ent::Gen::CinematicGD>(getSubNode("CinematicGD"));
        }
        inline Ent::Gen::CinematicGD Components::addCinematicGD() const
        {
            return Ent::Gen::CinematicGD(addSubNode("CinematicGD"));
        }
        inline std::optional<Ent::Gen::ConnectorGD> Components::ConnectorGD() const
        {
            auto sub = getSubNode("ConnectorGD");
            return sub == nullptr? std::optional<Ent::Gen::ConnectorGD>{}: std::optional<Ent::Gen::ConnectorGD>(getSubNode("ConnectorGD"));
        }
        inline Ent::Gen::ConnectorGD Components::addConnectorGD() const
        {
            return Ent::Gen::ConnectorGD(addSubNode("ConnectorGD"));
        }
        inline std::optional<Ent::Gen::BeamTargetGD> Components::BeamTargetGD() const
        {
            auto sub = getSubNode("BeamTargetGD");
            return sub == nullptr? std::optional<Ent::Gen::BeamTargetGD>{}: std::optional<Ent::Gen::BeamTargetGD>(getSubNode("BeamTargetGD"));
        }
        inline Ent::Gen::BeamTargetGD Components::addBeamTargetGD() const
        {
            return Ent::Gen::BeamTargetGD(addSubNode("BeamTargetGD"));
        }
        inline std::optional<Ent::Gen::ActorGD> Components::ActorGD() const
        {
            auto sub = getSubNode("ActorGD");
            return sub == nullptr? std::optional<Ent::Gen::ActorGD>{}: std::optional<Ent::Gen::ActorGD>(getSubNode("ActorGD"));
        }
        inline Ent::Gen::ActorGD Components::addActorGD() const
        {
            return Ent::Gen::ActorGD(addSubNode("ActorGD"));
        }
        inline std::optional<Ent::Gen::CharacterPlatformGD> Components::CharacterPlatformGD() const
        {
            auto sub = getSubNode("CharacterPlatformGD");
            return sub == nullptr? std::optional<Ent::Gen::CharacterPlatformGD>{}: std::optional<Ent::Gen::CharacterPlatformGD>(getSubNode("CharacterPlatformGD"));
        }
        inline Ent::Gen::CharacterPlatformGD Components::addCharacterPlatformGD() const
        {
            return Ent::Gen::CharacterPlatformGD(addSubNode("CharacterPlatformGD"));
        }
        inline std::optional<Ent::Gen::ReviveSideSwitcherGD> Components::ReviveSideSwitcherGD() const
        {
            auto sub = getSubNode("ReviveSideSwitcherGD");
            return sub == nullptr? std::optional<Ent::Gen::ReviveSideSwitcherGD>{}: std::optional<Ent::Gen::ReviveSideSwitcherGD>(getSubNode("ReviveSideSwitcherGD"));
        }
        inline Ent::Gen::ReviveSideSwitcherGD Components::addReviveSideSwitcherGD() const
        {
            return Ent::Gen::ReviveSideSwitcherGD(addSubNode("ReviveSideSwitcherGD"));
        }
        inline std::optional<Ent::Gen::EnergyPoolGD> Components::EnergyPoolGD() const
        {
            auto sub = getSubNode("EnergyPoolGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyPoolGD>{}: std::optional<Ent::Gen::EnergyPoolGD>(getSubNode("EnergyPoolGD"));
        }
        inline Ent::Gen::EnergyPoolGD Components::addEnergyPoolGD() const
        {
            return Ent::Gen::EnergyPoolGD(addSubNode("EnergyPoolGD"));
        }
        inline std::optional<Ent::Gen::PlayerComponentGD> Components::PlayerComponentGD() const
        {
            auto sub = getSubNode("PlayerComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::PlayerComponentGD>{}: std::optional<Ent::Gen::PlayerComponentGD>(getSubNode("PlayerComponentGD"));
        }
        inline Ent::Gen::PlayerComponentGD Components::addPlayerComponentGD() const
        {
            return Ent::Gen::PlayerComponentGD(addSubNode("PlayerComponentGD"));
        }
        inline std::optional<Ent::Gen::HotspotsGD> Components::HotspotsGD() const
        {
            auto sub = getSubNode("HotspotsGD");
            return sub == nullptr? std::optional<Ent::Gen::HotspotsGD>{}: std::optional<Ent::Gen::HotspotsGD>(getSubNode("HotspotsGD"));
        }
        inline Ent::Gen::HotspotsGD Components::addHotspotsGD() const
        {
            return Ent::Gen::HotspotsGD(addSubNode("HotspotsGD"));
        }
        inline std::optional<Ent::Gen::SmallActorSpawnerGD> Components::SmallActorSpawnerGD() const
        {
            auto sub = getSubNode("SmallActorSpawnerGD");
            return sub == nullptr? std::optional<Ent::Gen::SmallActorSpawnerGD>{}: std::optional<Ent::Gen::SmallActorSpawnerGD>(getSubNode("SmallActorSpawnerGD"));
        }
        inline Ent::Gen::SmallActorSpawnerGD Components::addSmallActorSpawnerGD() const
        {
            return Ent::Gen::SmallActorSpawnerGD(addSubNode("SmallActorSpawnerGD"));
        }
        inline std::optional<Ent::Gen::PathMotionControllerGD> Components::PathMotionControllerGD() const
        {
            auto sub = getSubNode("PathMotionControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::PathMotionControllerGD>{}: std::optional<Ent::Gen::PathMotionControllerGD>(getSubNode("PathMotionControllerGD"));
        }
        inline Ent::Gen::PathMotionControllerGD Components::addPathMotionControllerGD() const
        {
            return Ent::Gen::PathMotionControllerGD(addSubNode("PathMotionControllerGD"));
        }
        inline std::optional<Ent::Gen::CreatureAIGD> Components::CreatureAIGD() const
        {
            auto sub = getSubNode("CreatureAIGD");
            return sub == nullptr? std::optional<Ent::Gen::CreatureAIGD>{}: std::optional<Ent::Gen::CreatureAIGD>(getSubNode("CreatureAIGD"));
        }
        inline Ent::Gen::CreatureAIGD Components::addCreatureAIGD() const
        {
            return Ent::Gen::CreatureAIGD(addSubNode("CreatureAIGD"));
        }
        inline std::optional<Ent::Gen::CreatureUIGD> Components::CreatureUIGD() const
        {
            auto sub = getSubNode("CreatureUIGD");
            return sub == nullptr? std::optional<Ent::Gen::CreatureUIGD>{}: std::optional<Ent::Gen::CreatureUIGD>(getSubNode("CreatureUIGD"));
        }
        inline Ent::Gen::CreatureUIGD Components::addCreatureUIGD() const
        {
            return Ent::Gen::CreatureUIGD(addSubNode("CreatureUIGD"));
        }
        inline std::optional<Ent::Gen::SoundEmitterGD> Components::SoundEmitterGD() const
        {
            auto sub = getSubNode("SoundEmitterGD");
            return sub == nullptr? std::optional<Ent::Gen::SoundEmitterGD>{}: std::optional<Ent::Gen::SoundEmitterGD>(getSubNode("SoundEmitterGD"));
        }
        inline Ent::Gen::SoundEmitterGD Components::addSoundEmitterGD() const
        {
            return Ent::Gen::SoundEmitterGD(addSubNode("SoundEmitterGD"));
        }
        inline std::optional<Ent::Gen::EnergySourceGD> Components::EnergySourceGD() const
        {
            auto sub = getSubNode("EnergySourceGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergySourceGD>{}: std::optional<Ent::Gen::EnergySourceGD>(getSubNode("EnergySourceGD"));
        }
        inline Ent::Gen::EnergySourceGD Components::addEnergySourceGD() const
        {
            return Ent::Gen::EnergySourceGD(addSubNode("EnergySourceGD"));
        }
        inline std::optional<Ent::Gen::ClothAnimationGD> Components::ClothAnimationGD() const
        {
            auto sub = getSubNode("ClothAnimationGD");
            return sub == nullptr? std::optional<Ent::Gen::ClothAnimationGD>{}: std::optional<Ent::Gen::ClothAnimationGD>(getSubNode("ClothAnimationGD"));
        }
        inline Ent::Gen::ClothAnimationGD Components::addClothAnimationGD() const
        {
            return Ent::Gen::ClothAnimationGD(addSubNode("ClothAnimationGD"));
        }
        inline std::optional<Ent::Gen::CreatureGD> Components::CreatureGD() const
        {
            auto sub = getSubNode("CreatureGD");
            return sub == nullptr? std::optional<Ent::Gen::CreatureGD>{}: std::optional<Ent::Gen::CreatureGD>(getSubNode("CreatureGD"));
        }
        inline Ent::Gen::CreatureGD Components::addCreatureGD() const
        {
            return Ent::Gen::CreatureGD(addSubNode("CreatureGD"));
        }
        inline std::optional<Ent::Gen::HitTriggerGD> Components::HitTriggerGD() const
        {
            auto sub = getSubNode("HitTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::HitTriggerGD>{}: std::optional<Ent::Gen::HitTriggerGD>(getSubNode("HitTriggerGD"));
        }
        inline Ent::Gen::HitTriggerGD Components::addHitTriggerGD() const
        {
            return Ent::Gen::HitTriggerGD(addSubNode("HitTriggerGD"));
        }
        inline std::optional<Ent::Gen::ProjectileShooterGD> Components::ProjectileShooterGD() const
        {
            auto sub = getSubNode("ProjectileShooterGD");
            return sub == nullptr? std::optional<Ent::Gen::ProjectileShooterGD>{}: std::optional<Ent::Gen::ProjectileShooterGD>(getSubNode("ProjectileShooterGD"));
        }
        inline Ent::Gen::ProjectileShooterGD Components::addProjectileShooterGD() const
        {
            return Ent::Gen::ProjectileShooterGD(addSubNode("ProjectileShooterGD"));
        }
        inline std::optional<Ent::Gen::LightComponentGD> Components::LightComponentGD() const
        {
            auto sub = getSubNode("LightComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::LightComponentGD>{}: std::optional<Ent::Gen::LightComponentGD>(getSubNode("LightComponentGD"));
        }
        inline Ent::Gen::LightComponentGD Components::addLightComponentGD() const
        {
            return Ent::Gen::LightComponentGD(addSubNode("LightComponentGD"));
        }
        inline std::optional<Ent::Gen::MounterGD> Components::MounterGD() const
        {
            auto sub = getSubNode("MounterGD");
            return sub == nullptr? std::optional<Ent::Gen::MounterGD>{}: std::optional<Ent::Gen::MounterGD>(getSubNode("MounterGD"));
        }
        inline Ent::Gen::MounterGD Components::addMounterGD() const
        {
            return Ent::Gen::MounterGD(addSubNode("MounterGD"));
        }
        inline std::optional<Ent::Gen::AttackTriggerGD> Components::AttackTriggerGD() const
        {
            auto sub = getSubNode("AttackTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::AttackTriggerGD>{}: std::optional<Ent::Gen::AttackTriggerGD>(getSubNode("AttackTriggerGD"));
        }
        inline Ent::Gen::AttackTriggerGD Components::addAttackTriggerGD() const
        {
            return Ent::Gen::AttackTriggerGD(addSubNode("AttackTriggerGD"));
        }
        inline std::optional<Ent::Gen::PossessableGPEGD> Components::PossessableGPEGD() const
        {
            auto sub = getSubNode("PossessableGPEGD");
            return sub == nullptr? std::optional<Ent::Gen::PossessableGPEGD>{}: std::optional<Ent::Gen::PossessableGPEGD>(getSubNode("PossessableGPEGD"));
        }
        inline Ent::Gen::PossessableGPEGD Components::addPossessableGPEGD() const
        {
            return Ent::Gen::PossessableGPEGD(addSubNode("PossessableGPEGD"));
        }
        inline std::optional<Ent::Gen::OutfitGD> Components::OutfitGD() const
        {
            auto sub = getSubNode("OutfitGD");
            return sub == nullptr? std::optional<Ent::Gen::OutfitGD>{}: std::optional<Ent::Gen::OutfitGD>(getSubNode("OutfitGD"));
        }
        inline Ent::Gen::OutfitGD Components::addOutfitGD() const
        {
            return Ent::Gen::OutfitGD(addSubNode("OutfitGD"));
        }
        inline std::optional<Ent::Gen::BreakableGD> Components::BreakableGD() const
        {
            auto sub = getSubNode("BreakableGD");
            return sub == nullptr? std::optional<Ent::Gen::BreakableGD>{}: std::optional<Ent::Gen::BreakableGD>(getSubNode("BreakableGD"));
        }
        inline Ent::Gen::BreakableGD Components::addBreakableGD() const
        {
            return Ent::Gen::BreakableGD(addSubNode("BreakableGD"));
        }
        inline std::optional<Ent::Gen::PathNodeGD> Components::PathNodeGD() const
        {
            auto sub = getSubNode("PathNodeGD");
            return sub == nullptr? std::optional<Ent::Gen::PathNodeGD>{}: std::optional<Ent::Gen::PathNodeGD>(getSubNode("PathNodeGD"));
        }
        inline Ent::Gen::PathNodeGD Components::addPathNodeGD() const
        {
            return Ent::Gen::PathNodeGD(addSubNode("PathNodeGD"));
        }
        inline std::optional<Ent::Gen::VelocityObstacleGD> Components::VelocityObstacleGD() const
        {
            auto sub = getSubNode("VelocityObstacleGD");
            return sub == nullptr? std::optional<Ent::Gen::VelocityObstacleGD>{}: std::optional<Ent::Gen::VelocityObstacleGD>(getSubNode("VelocityObstacleGD"));
        }
        inline Ent::Gen::VelocityObstacleGD Components::addVelocityObstacleGD() const
        {
            return Ent::Gen::VelocityObstacleGD(addSubNode("VelocityObstacleGD"));
        }
        inline std::optional<Ent::Gen::ShapeshiftStatueGD> Components::ShapeshiftStatueGD() const
        {
            auto sub = getSubNode("ShapeshiftStatueGD");
            return sub == nullptr? std::optional<Ent::Gen::ShapeshiftStatueGD>{}: std::optional<Ent::Gen::ShapeshiftStatueGD>(getSubNode("ShapeshiftStatueGD"));
        }
        inline Ent::Gen::ShapeshiftStatueGD Components::addShapeshiftStatueGD() const
        {
            return Ent::Gen::ShapeshiftStatueGD(addSubNode("ShapeshiftStatueGD"));
        }
        inline std::optional<Ent::Gen::RagdollGD> Components::RagdollGD() const
        {
            auto sub = getSubNode("RagdollGD");
            return sub == nullptr? std::optional<Ent::Gen::RagdollGD>{}: std::optional<Ent::Gen::RagdollGD>(getSubNode("RagdollGD"));
        }
        inline Ent::Gen::RagdollGD Components::addRagdollGD() const
        {
            return Ent::Gen::RagdollGD(addSubNode("RagdollGD"));
        }
        inline std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD> Components::AnimationPhysicsChainConstraintsGD() const
        {
            auto sub = getSubNode("AnimationPhysicsChainConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD>{}: std::optional<Ent::Gen::AnimationPhysicsChainConstraintsGD>(getSubNode("AnimationPhysicsChainConstraintsGD"));
        }
        inline Ent::Gen::AnimationPhysicsChainConstraintsGD Components::addAnimationPhysicsChainConstraintsGD() const
        {
            return Ent::Gen::AnimationPhysicsChainConstraintsGD(addSubNode("AnimationPhysicsChainConstraintsGD"));
        }
        inline std::optional<Ent::Gen::ScriptComponentGD> Components::ScriptComponentGD() const
        {
            auto sub = getSubNode("ScriptComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::ScriptComponentGD>{}: std::optional<Ent::Gen::ScriptComponentGD>(getSubNode("ScriptComponentGD"));
        }
        inline Ent::Gen::ScriptComponentGD Components::addScriptComponentGD() const
        {
            return Ent::Gen::ScriptComponentGD(addSubNode("ScriptComponentGD"));
        }
        inline std::optional<Ent::Gen::FluidToRegenInjectorGD> Components::FluidToRegenInjectorGD() const
        {
            auto sub = getSubNode("FluidToRegenInjectorGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidToRegenInjectorGD>{}: std::optional<Ent::Gen::FluidToRegenInjectorGD>(getSubNode("FluidToRegenInjectorGD"));
        }
        inline Ent::Gen::FluidToRegenInjectorGD Components::addFluidToRegenInjectorGD() const
        {
            return Ent::Gen::FluidToRegenInjectorGD(addSubNode("FluidToRegenInjectorGD"));
        }
        inline std::optional<Ent::Gen::PerceivableGD> Components::PerceivableGD() const
        {
            auto sub = getSubNode("PerceivableGD");
            return sub == nullptr? std::optional<Ent::Gen::PerceivableGD>{}: std::optional<Ent::Gen::PerceivableGD>(getSubNode("PerceivableGD"));
        }
        inline Ent::Gen::PerceivableGD Components::addPerceivableGD() const
        {
            return Ent::Gen::PerceivableGD(addSubNode("PerceivableGD"));
        }
        inline std::optional<Ent::Gen::InventoryGD> Components::InventoryGD() const
        {
            auto sub = getSubNode("InventoryGD");
            return sub == nullptr? std::optional<Ent::Gen::InventoryGD>{}: std::optional<Ent::Gen::InventoryGD>(getSubNode("InventoryGD"));
        }
        inline Ent::Gen::InventoryGD Components::addInventoryGD() const
        {
            return Ent::Gen::InventoryGD(addSubNode("InventoryGD"));
        }
        inline std::optional<Ent::Gen::ItemHolderGD> Components::ItemHolderGD() const
        {
            auto sub = getSubNode("ItemHolderGD");
            return sub == nullptr? std::optional<Ent::Gen::ItemHolderGD>{}: std::optional<Ent::Gen::ItemHolderGD>(getSubNode("ItemHolderGD"));
        }
        inline Ent::Gen::ItemHolderGD Components::addItemHolderGD() const
        {
            return Ent::Gen::ItemHolderGD(addSubNode("ItemHolderGD"));
        }
        inline std::optional<Ent::Gen::PathGD> Components::PathGD() const
        {
            auto sub = getSubNode("PathGD");
            return sub == nullptr? std::optional<Ent::Gen::PathGD>{}: std::optional<Ent::Gen::PathGD>(getSubNode("PathGD"));
        }
        inline Ent::Gen::PathGD Components::addPathGD() const
        {
            return Ent::Gen::PathGD(addSubNode("PathGD"));
        }
        inline std::optional<Ent::Gen::PerceiverGD> Components::PerceiverGD() const
        {
            auto sub = getSubNode("PerceiverGD");
            return sub == nullptr? std::optional<Ent::Gen::PerceiverGD>{}: std::optional<Ent::Gen::PerceiverGD>(getSubNode("PerceiverGD"));
        }
        inline Ent::Gen::PerceiverGD Components::addPerceiverGD() const
        {
            return Ent::Gen::PerceiverGD(addSubNode("PerceiverGD"));
        }
        inline std::optional<Ent::Gen::DummyComponentGD> Components::DummyComponentGD() const
        {
            auto sub = getSubNode("DummyComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::DummyComponentGD>{}: std::optional<Ent::Gen::DummyComponentGD>(getSubNode("DummyComponentGD"));
        }
        inline Ent::Gen::DummyComponentGD Components::addDummyComponentGD() const
        {
            return Ent::Gen::DummyComponentGD(addSubNode("DummyComponentGD"));
        }
        inline std::optional<Ent::Gen::FluidNavMeshTaggerGD> Components::FluidNavMeshTaggerGD() const
        {
            auto sub = getSubNode("FluidNavMeshTaggerGD");
            return sub == nullptr? std::optional<Ent::Gen::FluidNavMeshTaggerGD>{}: std::optional<Ent::Gen::FluidNavMeshTaggerGD>(getSubNode("FluidNavMeshTaggerGD"));
        }
        inline Ent::Gen::FluidNavMeshTaggerGD Components::addFluidNavMeshTaggerGD() const
        {
            return Ent::Gen::FluidNavMeshTaggerGD(addSubNode("FluidNavMeshTaggerGD"));
        }
        inline std::optional<Ent::Gen::EnergySpoutGD> Components::EnergySpoutGD() const
        {
            auto sub = getSubNode("EnergySpoutGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergySpoutGD>{}: std::optional<Ent::Gen::EnergySpoutGD>(getSubNode("EnergySpoutGD"));
        }
        inline Ent::Gen::EnergySpoutGD Components::addEnergySpoutGD() const
        {
            return Ent::Gen::EnergySpoutGD(addSubNode("EnergySpoutGD"));
        }
        inline std::optional<Ent::Gen::PickableDistributorComponentGD> Components::PickableDistributorComponentGD() const
        {
            auto sub = getSubNode("PickableDistributorComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::PickableDistributorComponentGD>{}: std::optional<Ent::Gen::PickableDistributorComponentGD>(getSubNode("PickableDistributorComponentGD"));
        }
        inline Ent::Gen::PickableDistributorComponentGD Components::addPickableDistributorComponentGD() const
        {
            return Ent::Gen::PickableDistributorComponentGD(addSubNode("PickableDistributorComponentGD"));
        }
        inline std::optional<Ent::Gen::ShamanItemGD> Components::ShamanItemGD() const
        {
            auto sub = getSubNode("ShamanItemGD");
            return sub == nullptr? std::optional<Ent::Gen::ShamanItemGD>{}: std::optional<Ent::Gen::ShamanItemGD>(getSubNode("ShamanItemGD"));
        }
        inline Ent::Gen::ShamanItemGD Components::addShamanItemGD() const
        {
            return Ent::Gen::ShamanItemGD(addSubNode("ShamanItemGD"));
        }
        inline std::optional<Ent::Gen::TeamGD> Components::TeamGD() const
        {
            auto sub = getSubNode("TeamGD");
            return sub == nullptr? std::optional<Ent::Gen::TeamGD>{}: std::optional<Ent::Gen::TeamGD>(getSubNode("TeamGD"));
        }
        inline Ent::Gen::TeamGD Components::addTeamGD() const
        {
            return Ent::Gen::TeamGD(addSubNode("TeamGD"));
        }
        inline std::optional<Ent::Gen::SmallActorGD> Components::SmallActorGD() const
        {
            auto sub = getSubNode("SmallActorGD");
            return sub == nullptr? std::optional<Ent::Gen::SmallActorGD>{}: std::optional<Ent::Gen::SmallActorGD>(getSubNode("SmallActorGD"));
        }
        inline Ent::Gen::SmallActorGD Components::addSmallActorGD() const
        {
            return Ent::Gen::SmallActorGD(addSubNode("SmallActorGD"));
        }
        inline std::optional<Ent::Gen::PhysicsMeshProviderGD> Components::PhysicsMeshProviderGD() const
        {
            auto sub = getSubNode("PhysicsMeshProviderGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsMeshProviderGD>{}: std::optional<Ent::Gen::PhysicsMeshProviderGD>(getSubNode("PhysicsMeshProviderGD"));
        }
        inline Ent::Gen::PhysicsMeshProviderGD Components::addPhysicsMeshProviderGD() const
        {
            return Ent::Gen::PhysicsMeshProviderGD(addSubNode("PhysicsMeshProviderGD"));
        }
        inline std::optional<Ent::Gen::SideMapGateGD> Components::SideMapGateGD() const
        {
            auto sub = getSubNode("SideMapGateGD");
            return sub == nullptr? std::optional<Ent::Gen::SideMapGateGD>{}: std::optional<Ent::Gen::SideMapGateGD>(getSubNode("SideMapGateGD"));
        }
        inline Ent::Gen::SideMapGateGD Components::addSideMapGateGD() const
        {
            return Ent::Gen::SideMapGateGD(addSubNode("SideMapGateGD"));
        }
        inline std::optional<Ent::Gen::HeightMapComponentGD> Components::HeightMapComponentGD() const
        {
            auto sub = getSubNode("HeightMapComponentGD");
            return sub == nullptr? std::optional<Ent::Gen::HeightMapComponentGD>{}: std::optional<Ent::Gen::HeightMapComponentGD>(getSubNode("HeightMapComponentGD"));
        }
        inline Ent::Gen::HeightMapComponentGD Components::addHeightMapComponentGD() const
        {
            return Ent::Gen::HeightMapComponentGD(addSubNode("HeightMapComponentGD"));
        }
        inline std::optional<Ent::Gen::MountIKControllerGD> Components::MountIKControllerGD() const
        {
            auto sub = getSubNode("MountIKControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::MountIKControllerGD>{}: std::optional<Ent::Gen::MountIKControllerGD>(getSubNode("MountIKControllerGD"));
        }
        inline Ent::Gen::MountIKControllerGD Components::addMountIKControllerGD() const
        {
            return Ent::Gen::MountIKControllerGD(addSubNode("MountIKControllerGD"));
        }
        inline std::optional<Ent::Gen::StaffVertebrasGD> Components::StaffVertebrasGD() const
        {
            auto sub = getSubNode("StaffVertebrasGD");
            return sub == nullptr? std::optional<Ent::Gen::StaffVertebrasGD>{}: std::optional<Ent::Gen::StaffVertebrasGD>(getSubNode("StaffVertebrasGD"));
        }
        inline Ent::Gen::StaffVertebrasGD Components::addStaffVertebrasGD() const
        {
            return Ent::Gen::StaffVertebrasGD(addSubNode("StaffVertebrasGD"));
        }
        inline std::optional<Ent::Gen::SensorControllerGD> Components::SensorControllerGD() const
        {
            auto sub = getSubNode("SensorControllerGD");
            return sub == nullptr? std::optional<Ent::Gen::SensorControllerGD>{}: std::optional<Ent::Gen::SensorControllerGD>(getSubNode("SensorControllerGD"));
        }
        inline Ent::Gen::SensorControllerGD Components::addSensorControllerGD() const
        {
            return Ent::Gen::SensorControllerGD(addSubNode("SensorControllerGD"));
        }
        inline std::optional<Ent::Gen::BoidsGD> Components::BoidsGD() const
        {
            auto sub = getSubNode("BoidsGD");
            return sub == nullptr? std::optional<Ent::Gen::BoidsGD>{}: std::optional<Ent::Gen::BoidsGD>(getSubNode("BoidsGD"));
        }
        inline Ent::Gen::BoidsGD Components::addBoidsGD() const
        {
            return Ent::Gen::BoidsGD(addSubNode("BoidsGD"));
        }
        inline std::optional<Ent::Gen::AnimationTreeConstraintsGD> Components::AnimationTreeConstraintsGD() const
        {
            auto sub = getSubNode("AnimationTreeConstraintsGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationTreeConstraintsGD>{}: std::optional<Ent::Gen::AnimationTreeConstraintsGD>(getSubNode("AnimationTreeConstraintsGD"));
        }
        inline Ent::Gen::AnimationTreeConstraintsGD Components::addAnimationTreeConstraintsGD() const
        {
            return Ent::Gen::AnimationTreeConstraintsGD(addSubNode("AnimationTreeConstraintsGD"));
        }
        inline std::optional<Ent::Gen::DistanceTriggerGD> Components::DistanceTriggerGD() const
        {
            auto sub = getSubNode("DistanceTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::DistanceTriggerGD>{}: std::optional<Ent::Gen::DistanceTriggerGD>(getSubNode("DistanceTriggerGD"));
        }
        inline Ent::Gen::DistanceTriggerGD Components::addDistanceTriggerGD() const
        {
            return Ent::Gen::DistanceTriggerGD(addSubNode("DistanceTriggerGD"));
        }
        inline std::optional<Ent::Gen::QuickCreatureSwitchGD> Components::QuickCreatureSwitchGD() const
        {
            auto sub = getSubNode("QuickCreatureSwitchGD");
            return sub == nullptr? std::optional<Ent::Gen::QuickCreatureSwitchGD>{}: std::optional<Ent::Gen::QuickCreatureSwitchGD>(getSubNode("QuickCreatureSwitchGD"));
        }
        inline Ent::Gen::QuickCreatureSwitchGD Components::addQuickCreatureSwitchGD() const
        {
            return Ent::Gen::QuickCreatureSwitchGD(addSubNode("QuickCreatureSwitchGD"));
        }
        inline std::optional<Ent::Gen::EnergyProbeGD> Components::EnergyProbeGD() const
        {
            auto sub = getSubNode("EnergyProbeGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyProbeGD>{}: std::optional<Ent::Gen::EnergyProbeGD>(getSubNode("EnergyProbeGD"));
        }
        inline Ent::Gen::EnergyProbeGD Components::addEnergyProbeGD() const
        {
            return Ent::Gen::EnergyProbeGD(addSubNode("EnergyProbeGD"));
        }
        inline std::optional<Ent::Gen::RespawnPlaceGD> Components::RespawnPlaceGD() const
        {
            auto sub = getSubNode("RespawnPlaceGD");
            return sub == nullptr? std::optional<Ent::Gen::RespawnPlaceGD>{}: std::optional<Ent::Gen::RespawnPlaceGD>(getSubNode("RespawnPlaceGD"));
        }
        inline Ent::Gen::RespawnPlaceGD Components::addRespawnPlaceGD() const
        {
            return Ent::Gen::RespawnPlaceGD(addSubNode("RespawnPlaceGD"));
        }
        inline std::optional<Ent::Gen::OutfitWearerGD> Components::OutfitWearerGD() const
        {
            auto sub = getSubNode("OutfitWearerGD");
            return sub == nullptr? std::optional<Ent::Gen::OutfitWearerGD>{}: std::optional<Ent::Gen::OutfitWearerGD>(getSubNode("OutfitWearerGD"));
        }
        inline Ent::Gen::OutfitWearerGD Components::addOutfitWearerGD() const
        {
            return Ent::Gen::OutfitWearerGD(addSubNode("OutfitWearerGD"));
        }
        inline std::optional<Ent::Gen::VoxelSimulationGD> Components::VoxelSimulationGD() const
        {
            auto sub = getSubNode("VoxelSimulationGD");
            return sub == nullptr? std::optional<Ent::Gen::VoxelSimulationGD>{}: std::optional<Ent::Gen::VoxelSimulationGD>(getSubNode("VoxelSimulationGD"));
        }
        inline Ent::Gen::VoxelSimulationGD Components::addVoxelSimulationGD() const
        {
            return Ent::Gen::VoxelSimulationGD(addSubNode("VoxelSimulationGD"));
        }
        inline std::optional<Ent::Gen::AnimationModelGD> Components::AnimationModelGD() const
        {
            auto sub = getSubNode("AnimationModelGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationModelGD>{}: std::optional<Ent::Gen::AnimationModelGD>(getSubNode("AnimationModelGD"));
        }
        inline Ent::Gen::AnimationModelGD Components::addAnimationModelGD() const
        {
            return Ent::Gen::AnimationModelGD(addSubNode("AnimationModelGD"));
        }
        inline std::optional<Ent::Gen::TriggerEventCameraGD> Components::TriggerEventCameraGD() const
        {
            auto sub = getSubNode("TriggerEventCameraGD");
            return sub == nullptr? std::optional<Ent::Gen::TriggerEventCameraGD>{}: std::optional<Ent::Gen::TriggerEventCameraGD>(getSubNode("TriggerEventCameraGD"));
        }
        inline Ent::Gen::TriggerEventCameraGD Components::addTriggerEventCameraGD() const
        {
            return Ent::Gen::TriggerEventCameraGD(addSubNode("TriggerEventCameraGD"));
        }
        inline std::optional<Ent::Gen::AnimationPlaylistGD> Components::AnimationPlaylistGD() const
        {
            auto sub = getSubNode("AnimationPlaylistGD");
            return sub == nullptr? std::optional<Ent::Gen::AnimationPlaylistGD>{}: std::optional<Ent::Gen::AnimationPlaylistGD>(getSubNode("AnimationPlaylistGD"));
        }
        inline Ent::Gen::AnimationPlaylistGD Components::addAnimationPlaylistGD() const
        {
            return Ent::Gen::AnimationPlaylistGD(addSubNode("AnimationPlaylistGD"));
        }
        inline std::optional<Ent::Gen::MeshNavigationInfosGD> Components::MeshNavigationInfosGD() const
        {
            auto sub = getSubNode("MeshNavigationInfosGD");
            return sub == nullptr? std::optional<Ent::Gen::MeshNavigationInfosGD>{}: std::optional<Ent::Gen::MeshNavigationInfosGD>(getSubNode("MeshNavigationInfosGD"));
        }
        inline Ent::Gen::MeshNavigationInfosGD Components::addMeshNavigationInfosGD() const
        {
            return Ent::Gen::MeshNavigationInfosGD(addSubNode("MeshNavigationInfosGD"));
        }
        inline std::optional<Ent::Gen::PhysicsTriggerGD> Components::PhysicsTriggerGD() const
        {
            auto sub = getSubNode("PhysicsTriggerGD");
            return sub == nullptr? std::optional<Ent::Gen::PhysicsTriggerGD>{}: std::optional<Ent::Gen::PhysicsTriggerGD>(getSubNode("PhysicsTriggerGD"));
        }
        inline Ent::Gen::PhysicsTriggerGD Components::addPhysicsTriggerGD() const
        {
            return Ent::Gen::PhysicsTriggerGD(addSubNode("PhysicsTriggerGD"));
        }
        inline std::optional<Ent::Gen::EnergyNetworkListenerGD> Components::EnergyNetworkListenerGD() const
        {
            auto sub = getSubNode("EnergyNetworkListenerGD");
            return sub == nullptr? std::optional<Ent::Gen::EnergyNetworkListenerGD>{}: std::optional<Ent::Gen::EnergyNetworkListenerGD>(getSubNode("EnergyNetworkListenerGD"));
        }
        inline Ent::Gen::EnergyNetworkListenerGD Components::addEnergyNetworkListenerGD() const
        {
            return Ent::Gen::EnergyNetworkListenerGD(addSubNode("EnergyNetworkListenerGD"));
        }
        inline std::optional<Ent::Gen::MissionHolderGD> Components::MissionHolderGD() const
        {
            auto sub = getSubNode("MissionHolderGD");
            return sub == nullptr? std::optional<Ent::Gen::MissionHolderGD>{}: std::optional<Ent::Gen::MissionHolderGD>(getSubNode("MissionHolderGD"));
        }
        inline Ent::Gen::MissionHolderGD Components::addMissionHolderGD() const
        {
            return Ent::Gen::MissionHolderGD(addSubNode("MissionHolderGD"));
        }
        inline std::optional<Ent::Gen::RegenSwitcherGD> Components::RegenSwitcherGD() const
        {
            auto sub = getSubNode("RegenSwitcherGD");
            return sub == nullptr? std::optional<Ent::Gen::RegenSwitcherGD>{}: std::optional<Ent::Gen::RegenSwitcherGD>(getSubNode("RegenSwitcherGD"));
        }
        inline Ent::Gen::RegenSwitcherGD Components::addRegenSwitcherGD() const
        {
            return Ent::Gen::RegenSwitcherGD(addSubNode("RegenSwitcherGD"));
        }
        // LightComponentGD
        inline Ent::Gen::Vector3 LightComponentGD::AngleOffset() const
        {
            return Ent::Gen::Vector3(node->at("AngleOffset"));
        }
        inline Ent::Gen::Float LightComponentGD::Brightness() const
        {
            return Ent::Gen::Float(node->at("Brightness"));
        }
        inline Ent::Gen::Bool LightComponentGD::CastShadow() const
        {
            return Ent::Gen::Bool(node->at("CastShadow"));
        }
        inline Ent::Gen::Color LightComponentGD::Color() const
        {
            return Ent::Gen::Color(node->at("Color"));
        }
        inline Ent::Gen::Vector3 LightComponentGD::Direction() const
        {
            return Ent::Gen::Vector3(node->at("Direction"));
        }
        inline Ent::Gen::Bool LightComponentGD::Enabled() const
        {
            return Ent::Gen::Bool(node->at("Enabled"));
        }
        inline Ent::Gen::Float LightComponentGD::LinearAttenuationStart() const
        {
            return Ent::Gen::Float(node->at("LinearAttenuationStart"));
        }
        inline Ent::Gen::Float LightComponentGD::LinearAttenuationStop() const
        {
            return Ent::Gen::Float(node->at("LinearAttenuationStop"));
        }
        inline Ent::Gen::Vector3 LightComponentGD::Offset() const
        {
            return Ent::Gen::Vector3(node->at("Offset"));
        }
        inline Ent::Gen::Float LightComponentGD::RadialAttenuationStart() const
        {
            return Ent::Gen::Float(node->at("RadialAttenuationStart"));
        }
        inline Ent::Gen::Float LightComponentGD::RadialAttenuationStop() const
        {
            return Ent::Gen::Float(node->at("RadialAttenuationStop"));
        }
        inline Ent::Gen::ComponentGD LightComponentGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::LightType LightComponentGD::Type_() const
        {
            return Ent::Gen::LightType(node->at("Type_"));
        }
        inline Ent::Gen::Bool LightComponentGD::VolumetricFog() const
        {
            return Ent::Gen::Bool(node->at("VolumetricFog"));
        }
        inline Ent::Gen::String LightComponentGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // BoidsGD
        inline Ent::Gen::Bool BoidsGD::AffectedByFluid() const
        {
            return Ent::Gen::Bool(node->at("AffectedByFluid"));
        }
        inline Ent::Gen::Bool BoidsGD::AllowMerge() const
        {
            return Ent::Gen::Bool(node->at("AllowMerge"));
        }
        inline Ent::Gen::Bool BoidsGD::AutoMoveRoot() const
        {
            return Ent::Gen::Bool(node->at("AutoMoveRoot"));
        }
        inline Ent::Gen::EntityRef BoidsGD::BudEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("BudEntityRef"));
        }
        inline Ent::Gen::Float BoidsGD::BudVisualScaleMax() const
        {
            return Ent::Gen::Float(node->at("BudVisualScaleMax"));
        }
        inline Ent::Gen::Float BoidsGD::BudVisualScaleMin() const
        {
            return Ent::Gen::Float(node->at("BudVisualScaleMin"));
        }
        inline Ent::Gen::Bool BoidsGD::DisplayMaster() const
        {
            return Ent::Gen::Bool(node->at("DisplayMaster"));
        }
        inline Ent::Gen::Float BoidsGD::FlockingAttackDamages() const
        {
            return Ent::Gen::Float(node->at("FlockingAttackDamages"));
        }
        inline Ent::Gen::Float BoidsGD::FluidSurfaceHeightOffset() const
        {
            return Ent::Gen::Float(node->at("FluidSurfaceHeightOffset"));
        }
        inline Ent::Gen::Bool BoidsGD::ForceOutsideWater() const
        {
            return Ent::Gen::Bool(node->at("ForceOutsideWater"));
        }
        inline Ent::Gen::EntityRef BoidsGD::FullEntityPoolRef() const
        {
            return Ent::Gen::EntityRef(node->at("FullEntityPoolRef"));
        }
        inline Ent::Gen::Float BoidsGD::GetBackToFlockingDuration() const
        {
            return Ent::Gen::Float(node->at("GetBackToFlockingDuration"));
        }
        inline Ent::Gen::Float BoidsGD::GhostDuration() const
        {
            return Ent::Gen::Float(node->at("GhostDuration"));
        }
        inline Ent::Gen::Float BoidsGD::HierarchyDistanceMultiplier() const
        {
            return Ent::Gen::Float(node->at("HierarchyDistanceMultiplier"));
        }
        inline Ent::Gen::Float BoidsGD::InitialRadius() const
        {
            return Ent::Gen::Float(node->at("InitialRadius"));
        }
        inline Ent::Gen::Float BoidsGD::LightBrightness() const
        {
            return Ent::Gen::Float(node->at("LightBrightness"));
        }
        inline Ent::Gen::Color BoidsGD::LightColor() const
        {
            return Ent::Gen::Color(node->at("LightColor"));
        }
        inline Ent::Gen::Float BoidsGD::MainTargetHeight() const
        {
            return Ent::Gen::Float(node->at("MainTargetHeight"));
        }
        inline Ent::Gen::Float BoidsGD::MainTargetRotateDistance() const
        {
            return Ent::Gen::Float(node->at("MainTargetRotateDistance"));
        }
        inline Ent::Gen::Float BoidsGD::MainTargetSpeedMultiplier() const
        {
            return Ent::Gen::Float(node->at("MainTargetSpeedMultiplier"));
        }
        inline Ent::Gen::Float BoidsGD::MinRegenToWakeUp() const
        {
            return Ent::Gen::Float(node->at("MinRegenToWakeUp"));
        }
        inline Ent::Gen::Int BoidsGD::NbAgents() const
        {
            return Ent::Gen::Int(node->at("NbAgents"));
        }
        inline Ent::Gen::Int BoidsGD::NbAgentsPerZone() const
        {
            return Ent::Gen::Int(node->at("NbAgentsPerZone"));
        }
        inline Ent::Gen::String BoidsGD::ParamBlock() const
        {
            return Ent::Gen::String(node->at("ParamBlock"));
        }
        inline Ent::Gen::String BoidsGD::ParamBudAppear() const
        {
            return Ent::Gen::String(node->at("ParamBudAppear"));
        }
        inline Ent::Gen::String BoidsGD::ParamBudOpen() const
        {
            return Ent::Gen::String(node->at("ParamBudOpen"));
        }
        inline Ent::Gen::String BoidsGD::ParamHome() const
        {
            return Ent::Gen::String(node->at("ParamHome"));
        }
        inline Ent::Gen::String BoidsGD::ParamMove() const
        {
            return Ent::Gen::String(node->at("ParamMove"));
        }
        inline Ent::Gen::String BoidsGD::ParamSwim() const
        {
            return Ent::Gen::String(node->at("ParamSwim"));
        }
        inline Ent::Gen::String BoidsGD::ParamWakeUp() const
        {
            return Ent::Gen::String(node->at("ParamWakeUp"));
        }
        inline Ent::Gen::Float BoidsGD::PointCloudSearchRadius() const
        {
            return Ent::Gen::Float(node->at("PointCloudSearchRadius"));
        }
        inline Ent::Gen::String BoidsGD::PointCloudTag() const
        {
            return Ent::Gen::String(node->at("PointCloudTag"));
        }
        inline Ent::Gen::String BoidsGD::PresetName() const
        {
            return Ent::Gen::String(node->at("PresetName"));
        }
        inline Ent::Gen::String BoidsGD::PresetNameBud() const
        {
            return Ent::Gen::String(node->at("PresetNameBud"));
        }
        inline Ent::Gen::Float BoidsGD::RegenMaxThreshold() const
        {
            return Ent::Gen::Float(node->at("RegenMaxThreshold"));
        }
        inline Ent::Gen::ComponentGD BoidsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Float BoidsGD::VisualScaleMax() const
        {
            return Ent::Gen::Float(node->at("VisualScaleMax"));
        }
        inline Ent::Gen::Float BoidsGD::VisualScaleMin() const
        {
            return Ent::Gen::Float(node->at("VisualScaleMin"));
        }
        inline Ent::Gen::Float BoidsGD::WakeUpDuration() const
        {
            return Ent::Gen::Float(node->at("WakeUpDuration"));
        }
        inline Ent::Gen::String BoidsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // Collider
        inline Ent::Gen::String Collider::BoneName() const
        {
            return Ent::Gen::String(node->at("BoneName"));
        }
        inline Ent::Gen::Float Collider::RadiusFactor() const
        {
            return Ent::Gen::Float(node->at("RadiusFactor"));
        }
        inline Ent::Gen::String Collider::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationTailConstraintsGD
        inline Ent::Gen::Float AnimationTailConstraintsGD::AngularSpeedMaxForSpeedModeFurious() const
        {
            return Ent::Gen::Float(node->at("AngularSpeedMaxForSpeedModeFurious"));
        }
        inline Ent::Gen::Float AnimationTailConstraintsGD::AngularSpeedMaxForSpeedModeNone() const
        {
            return Ent::Gen::Float(node->at("AngularSpeedMaxForSpeedModeNone"));
        }
        inline Ent::Gen::Bool AnimationTailConstraintsGD::BoneInjectDirectionFromUseAmplitudeFactor() const
        {
            return Ent::Gen::Bool(node->at("BoneInjectDirectionFromUseAmplitudeFactor"));
        }
        inline Ent::Gen::String AnimationTailConstraintsGD::BoneNameEnd() const
        {
            return Ent::Gen::String(node->at("BoneNameEnd"));
        }
        inline Ent::Gen::String AnimationTailConstraintsGD::BoneNameInjectDirectionFrom() const
        {
            return Ent::Gen::String(node->at("BoneNameInjectDirectionFrom"));
        }
        inline Ent::Gen::String AnimationTailConstraintsGD::BoneNameStart() const
        {
            return Ent::Gen::String(node->at("BoneNameStart"));
        }
        inline Array<Ent::Gen::Collider> AnimationTailConstraintsGD::Colliders() const
        {
            return Array<Ent::Gen::Collider>(node->at("Colliders"));
        }
        inline Ent::Gen::Float AnimationTailConstraintsGD::CollidersRadiusFactorGrounded() const
        {
            return Ent::Gen::Float(node->at("CollidersRadiusFactorGrounded"));
        }
        inline Ent::Gen::Float AnimationTailConstraintsGD::CompensateSegmentStretchFactor() const
        {
            return Ent::Gen::Float(node->at("CompensateSegmentStretchFactor"));
        }
        inline Array<Ent::Gen::ConditionalRigidityAttribute> AnimationTailConstraintsGD::ConditionalRigidityAttributes() const
        {
            return Array<Ent::Gen::ConditionalRigidityAttribute>(node->at("ConditionalRigidityAttributes"));
        }
        inline Array<Ent::Gen::StickToGround> AnimationTailConstraintsGD::StickToGrounds() const
        {
            return Array<Ent::Gen::StickToGround>(node->at("StickToGrounds"));
        }
        inline Ent::Gen::Float AnimationTailConstraintsGD::StickToGroundsGravity() const
        {
            return Ent::Gen::Float(node->at("StickToGroundsGravity"));
        }
        inline Ent::Gen::Float AnimationTailConstraintsGD::StickToGroundsGravityUnderwater() const
        {
            return Ent::Gen::Float(node->at("StickToGroundsGravityUnderwater"));
        }
        inline Ent::Gen::Float AnimationTailConstraintsGD::StickToGroundsRadiusFactorDead() const
        {
            return Ent::Gen::Float(node->at("StickToGroundsRadiusFactorDead"));
        }
        inline Ent::Gen::ComponentGD AnimationTailConstraintsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AnimationTailConstraintsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CinematicSlot
        inline Ent::Gen::String CinematicSlot::ActorBone() const
        {
            return Ent::Gen::String(node->at("ActorBone"));
        }
        inline Ent::Gen::String CinematicSlot::Anim() const
        {
            return Ent::Gen::String(node->at("Anim"));
        }
        inline Ent::Gen::Bool CinematicSlot::CameraHolder() const
        {
            return Ent::Gen::Bool(node->at("CameraHolder"));
        }
        inline Ent::Gen::Bool CinematicSlot::CanBeInstanciated() const
        {
            return Ent::Gen::Bool(node->at("CanBeInstanciated"));
        }
        inline Ent::Gen::Bool CinematicSlot::DestroyAfter() const
        {
            return Ent::Gen::Bool(node->at("DestroyAfter"));
        }
        inline Ent::Gen::EntityRef CinematicSlot::EntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("EntityRef"));
        }
        inline Ent::Gen::Bool CinematicSlot::EventCameraHolder() const
        {
            return Ent::Gen::Bool(node->at("EventCameraHolder"));
        }
        inline Ent::Gen::Float CinematicSlot::FOV() const
        {
            return Ent::Gen::Float(node->at("FOV"));
        }
        inline Ent::Gen::Float CinematicSlot::FadeInDelay() const
        {
            return Ent::Gen::Float(node->at("FadeInDelay"));
        }
        inline Ent::Gen::Float CinematicSlot::FadeOutDelay() const
        {
            return Ent::Gen::Float(node->at("FadeOutDelay"));
        }
        inline Ent::Gen::Transform3D CinematicSlot::InitTransform() const
        {
            return Ent::Gen::Transform3D(node->at("InitTransform"));
        }
        inline Ent::Gen::Bool CinematicSlot::MainRole() const
        {
            return Ent::Gen::Bool(node->at("MainRole"));
        }
        inline Ent::Gen::Bool CinematicSlot::Mandatory() const
        {
            return Ent::Gen::Bool(node->at("Mandatory"));
        }
        inline Ent::Gen::String CinematicSlot::Role() const
        {
            return Ent::Gen::String(node->at("Role"));
        }
        inline Ent::Gen::String CinematicSlot::RoleInNextSequence() const
        {
            return Ent::Gen::String(node->at("RoleInNextSequence"));
        }
        inline Ent::Gen::Bool CinematicSlot::Visible() const
        {
            return Ent::Gen::Bool(node->at("Visible"));
        }
        inline Ent::Gen::String CinematicSlot::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // Sequence
        inline Ent::Gen::Float Sequence::ActivationDelay() const
        {
            return Ent::Gen::Float(node->at("ActivationDelay"));
        }
        inline Ent::Gen::Bool Sequence::AutoSwitchToNextSequence() const
        {
            return Ent::Gen::Bool(node->at("AutoSwitchToNextSequence"));
        }
        inline Ent::Gen::String Sequence::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Array<Ent::Gen::CinematicSlot> Sequence::actors() const
        {
            return Array<Ent::Gen::CinematicSlot>(node->at("actors"));
        }
        inline Ent::Gen::Bool Sequence::loop() const
        {
            return Ent::Gen::Bool(node->at("loop"));
        }
        inline Ent::Gen::String Sequence::name() const
        {
            return Ent::Gen::String(node->at("name"));
        }
        // CinematicGD
        inline Ent::Gen::Float CinematicGD::ActivationDistance() const
        {
            return Ent::Gen::Float(node->at("ActivationDistance"));
        }
        inline Array<Ent::Gen::ResponsiblePointer_CineEvent_> CinematicGD::ScriptEvents() const
        {
            return Array<Ent::Gen::ResponsiblePointer_CineEvent_>(node->at("ScriptEvents"));
        }
        inline Array<Ent::Gen::Sequence> CinematicGD::Sequences() const
        {
            return Array<Ent::Gen::Sequence>(node->at("Sequences"));
        }
        inline Ent::Gen::Bool CinematicGD::Skippable() const
        {
            return Ent::Gen::Bool(node->at("Skippable"));
        }
        inline Ent::Gen::ComponentGD CinematicGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::CinematicUpdateType CinematicGD::UpdateType() const
        {
            return Ent::Gen::CinematicUpdateType(node->at("UpdateType"));
        }
        inline Ent::Gen::String CinematicGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEvent
        inline Ent::Gen::Bool CineEvent::Active() const
        {
            return Ent::Gen::Bool(node->at("Active"));
        }
        inline Ent::Gen::String CineEvent::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTrigger
        inline Ent::Gen::CineEvent CineEventTrigger::Super() const
        {
            return Ent::Gen::CineEvent(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTrigger::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTriggerPlaySound
        inline Ent::Gen::String CineEventTriggerPlaySound::SoundEventName() const
        {
            return Ent::Gen::String(node->at("SoundEventName"));
        }
        inline Ent::Gen::CineEventTrigger CineEventTriggerPlaySound::Super() const
        {
            return Ent::Gen::CineEventTrigger(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTriggerPlaySound::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTriggerPlaySequence
        inline Ent::Gen::Int CineEventTriggerPlaySequence::SequenceID() const
        {
            return Ent::Gen::Int(node->at("SequenceID"));
        }
        inline Ent::Gen::CineEventTrigger CineEventTriggerPlaySequence::Super() const
        {
            return Ent::Gen::CineEventTrigger(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTriggerPlaySequence::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTriggerGameStateChange
        inline Ent::Gen::String CineEventTriggerGameStateChange::GameStateName() const
        {
            return Ent::Gen::String(node->at("GameStateName"));
        }
        inline Ent::Gen::CineEventTrigger CineEventTriggerGameStateChange::Super() const
        {
            return Ent::Gen::CineEventTrigger(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTriggerGameStateChange::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTriggerEventHandlerPost
        inline Ent::Gen::String CineEventTriggerEventHandlerPost::EventCategory() const
        {
            return Ent::Gen::String(node->at("EventCategory"));
        }
        inline Ent::Gen::String CineEventTriggerEventHandlerPost::EventName() const
        {
            return Ent::Gen::String(node->at("EventName"));
        }
        inline Ent::Gen::CineEventTrigger CineEventTriggerEventHandlerPost::Super() const
        {
            return Ent::Gen::CineEventTrigger(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTriggerEventHandlerPost::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTest
        inline Ent::Gen::Bool CineEventTest::InvertTest() const
        {
            return Ent::Gen::Bool(node->at("InvertTest"));
        }
        inline Ent::Gen::CineEvent CineEventTest::Super() const
        {
            return Ent::Gen::CineEvent(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTest::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTestWait
        inline Ent::Gen::Float CineEventTestWait::Duration() const
        {
            return Ent::Gen::Float(node->at("Duration"));
        }
        inline Ent::Gen::CineEventTest CineEventTestWait::Super() const
        {
            return Ent::Gen::CineEventTest(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTestWait::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTestIsCanceled
        inline Ent::Gen::CineEventTest CineEventTestIsCanceled::Super() const
        {
            return Ent::Gen::CineEventTest(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTestIsCanceled::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTestInput
        inline Ent::Gen::Bool CineEventTestInput::AnyButtonInput() const
        {
            return Ent::Gen::Bool(node->at("AnyButtonInput"));
        }
        inline Ent::Gen::Bool CineEventTestInput::AnyJoyInput() const
        {
            return Ent::Gen::Bool(node->at("AnyJoyInput"));
        }
        inline Ent::Gen::CineEventTest CineEventTestInput::Super() const
        {
            return Ent::Gen::CineEventTest(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTestInput::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTestEndCurrentSequence
        inline Ent::Gen::CineEventTest CineEventTestEndCurrentSequence::Super() const
        {
            return Ent::Gen::CineEventTest(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTestEndCurrentSequence::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CineEventTestCurrentGameState
        inline Ent::Gen::String CineEventTestCurrentGameState::GameStateName() const
        {
            return Ent::Gen::String(node->at("GameStateName"));
        }
        inline Ent::Gen::CineEventTest CineEventTestCurrentGameState::Super() const
        {
            return Ent::Gen::CineEventTest(node->at("Super"));
        }
        inline Ent::Gen::String CineEventTestCurrentGameState::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CharacterControllerSlideData
        inline Ent::Gen::String CharacterControllerSlideData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::ScaleConverter CharacterControllerSlideData::adherenceRecoverSpeedDependingOnTheSlope() const
        {
            return Ent::Gen::ScaleConverter(node->at("adherenceRecoverSpeedDependingOnTheSlope"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::adherenceThresholdHysteresis() const
        {
            return Ent::Gen::Float(node->at("adherenceThresholdHysteresis"));
        }
        inline Ent::Gen::ScaleConverter CharacterControllerSlideData::adherenceThresholdRequiredToKeepControl() const
        {
            return Ent::Gen::ScaleConverter(node->at("adherenceThresholdRequiredToKeepControl"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::adherenceUsingDownwardSlopeDirection() const
        {
            return Ent::Gen::Float(node->at("adherenceUsingDownwardSlopeDirection"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::adherenceUsingSideSlopeDirection() const
        {
            return Ent::Gen::Float(node->at("adherenceUsingSideSlopeDirection"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::adherenceUsingUpwardSlopeDirection() const
        {
            return Ent::Gen::Float(node->at("adherenceUsingUpwardSlopeDirection"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::animblendInTime() const
        {
            return Ent::Gen::Float(node->at("animblendInTime"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::friction() const
        {
            return Ent::Gen::Float(node->at("friction"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::maxSlopeAngle() const
        {
            return Ent::Gen::Float(node->at("maxSlopeAngle"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::speedMediumCoeffHysteresis() const
        {
            return Ent::Gen::Float(node->at("speedMediumCoeffHysteresis"));
        }
        inline Ent::Gen::ScaleConverter CharacterControllerSlideData::speedMediumCoeffIn() const
        {
            return Ent::Gen::ScaleConverter(node->at("speedMediumCoeffIn"));
        }
        inline Ent::Gen::Float CharacterControllerSlideData::speedMediumCoeffMin() const
        {
            return Ent::Gen::Float(node->at("speedMediumCoeffMin"));
        }
        // CharacterControllerGroundNormalData
        inline Ent::Gen::Bool CharacterControllerGroundNormalData::AllowOtherCreatureCast() const
        {
            return Ent::Gen::Bool(node->at("AllowOtherCreatureCast"));
        }
        inline Ent::Gen::Float CharacterControllerGroundNormalData::PercentageEdgeTolerance() const
        {
            return Ent::Gen::Float(node->at("PercentageEdgeTolerance"));
        }
        inline Ent::Gen::Float CharacterControllerGroundNormalData::PercentageExtirpate() const
        {
            return Ent::Gen::Float(node->at("PercentageExtirpate"));
        }
        inline Ent::Gen::String CharacterControllerGroundNormalData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CharacterControllerFallData
        inline Ent::Gen::ScaleConverter CharacterControllerFallData::DamagesPerHeightFall() const
        {
            return Ent::Gen::ScaleConverter(node->at("DamagesPerHeightFall"));
        }
        inline Ent::Gen::Float CharacterControllerFallData::MinHeightForDamageFall() const
        {
            return Ent::Gen::Float(node->at("MinHeightForDamageFall"));
        }
        inline Ent::Gen::Float CharacterControllerFallData::MinHeightForDeathFall() const
        {
            return Ent::Gen::Float(node->at("MinHeightForDeathFall"));
        }
        inline Ent::Gen::Float CharacterControllerFallData::MinHeightForRecoveryFall() const
        {
            return Ent::Gen::Float(node->at("MinHeightForRecoveryFall"));
        }
        inline Ent::Gen::String CharacterControllerFallData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CharacterControllerClamberData
        inline Ent::Gen::Float CharacterControllerClamberData::DropOffAngle() const
        {
            return Ent::Gen::Float(node->at("DropOffAngle"));
        }
        inline Ent::Gen::Float CharacterControllerClamberData::EnterAngle() const
        {
            return Ent::Gen::Float(node->at("EnterAngle"));
        }
        inline Ent::Gen::Float CharacterControllerClamberData::ExitAngle() const
        {
            return Ent::Gen::Float(node->at("ExitAngle"));
        }
        inline Ent::Gen::Bool CharacterControllerClamberData::IsAllowed() const
        {
            return Ent::Gen::Bool(node->at("IsAllowed"));
        }
        inline Ent::Gen::ScaleConverter CharacterControllerClamberData::VerticalOrientationRatio() const
        {
            return Ent::Gen::ScaleConverter(node->at("VerticalOrientationRatio"));
        }
        inline Ent::Gen::String CharacterControllerClamberData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CameraSetterGD
        inline Ent::Gen::Bool CameraSetterGD::SetPositionToHotspot() const
        {
            return Ent::Gen::Bool(node->at("SetPositionToHotspot"));
        }
        inline Ent::Gen::ComponentGD CameraSetterGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Bool CameraSetterGD::SwitchToType() const
        {
            return Ent::Gen::Bool(node->at("SwitchToType"));
        }
        inline Ent::Gen::CameraType CameraSetterGD::Type_() const
        {
            return Ent::Gen::CameraType(node->at("Type_"));
        }
        inline Ent::Gen::String CameraSetterGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CameraShakeData
        inline Ent::Gen::String CameraShakeData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float CameraShakeData::shakeDuration() const
        {
            return Ent::Gen::Float(node->at("shakeDuration"));
        }
        inline Ent::Gen::Float CameraShakeData::shakeFrequency() const
        {
            return Ent::Gen::Float(node->at("shakeFrequency"));
        }
        inline Ent::Gen::Float CameraShakeData::shakeIntensity() const
        {
            return Ent::Gen::Float(node->at("shakeIntensity"));
        }
        inline Ent::Gen::Vector3 CameraShakeData::shakeRotation() const
        {
            return Ent::Gen::Vector3(node->at("shakeRotation"));
        }
        // BiteData
        inline Ent::Gen::Bool BiteData::CanBiteBiped() const
        {
            return Ent::Gen::Bool(node->at("CanBiteBiped"));
        }
        inline Ent::Gen::Bool BiteData::CanBiteFriends() const
        {
            return Ent::Gen::Bool(node->at("CanBiteFriends"));
        }
        inline Ent::Gen::Bool BiteData::CheckHotspotOrientation() const
        {
            return Ent::Gen::Bool(node->at("CheckHotspotOrientation"));
        }
        inline Ent::Gen::String BiteData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Bool BiteData::bezierMove() const
        {
            return Ent::Gen::Bool(node->at("bezierMove"));
        }
        inline Ent::Gen::Float BiteData::biteDamagePerSec() const
        {
            return Ent::Gen::Float(node->at("biteDamagePerSec"));
        }
        inline Ent::Gen::Float BiteData::biteDefenseDamages() const
        {
            return Ent::Gen::Float(node->at("biteDefenseDamages"));
        }
        inline Ent::Gen::Float BiteData::biteDuration() const
        {
            return Ent::Gen::Float(node->at("biteDuration"));
        }
        inline Ent::Gen::Float BiteData::biteMaxRange() const
        {
            return Ent::Gen::Float(node->at("biteMaxRange"));
        }
        // BehaviorScriptData
        inline Ent::Gen::String BehaviorScriptData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float BehaviorScriptData::additionalDangerousnessDiffToFlee() const
        {
            return Ent::Gen::Float(node->at("additionalDangerousnessDiffToFlee"));
        }
        inline Ent::Gen::Float BehaviorScriptData::aimingDuration() const
        {
            return Ent::Gen::Float(node->at("aimingDuration"));
        }
        inline Ent::Gen::Int BehaviorScriptData::answerAttackRunSpeed() const
        {
            return Ent::Gen::Int(node->at("answerAttackRunSpeed"));
        }
        inline Ent::Gen::Float BehaviorScriptData::artificialArenaRadius() const
        {
            return Ent::Gen::Float(node->at("artificialArenaRadius"));
        }
        inline Ent::Gen::Int BehaviorScriptData::attackAggressivityDecrease() const
        {
            return Ent::Gen::Int(node->at("attackAggressivityDecrease"));
        }
        inline Ent::Gen::Float BehaviorScriptData::attackIfEnemyHasBeenSeenSince() const
        {
            return Ent::Gen::Float(node->at("attackIfEnemyHasBeenSeenSince"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::attackInPack() const
        {
            return Ent::Gen::Bool(node->at("attackInPack"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::attackOrderCanFlee() const
        {
            return Ent::Gen::Bool(node->at("attackOrderCanFlee"));
        }
        inline Ent::Gen::Int BehaviorScriptData::attackRunSpeed() const
        {
            return Ent::Gen::Int(node->at("attackRunSpeed"));
        }
        inline Ent::Gen::Float BehaviorScriptData::attackWaitCircle_Offset_Z() const
        {
            return Ent::Gen::Float(node->at("attackWaitCircle_Offset_Z"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::avoidGroundMovements() const
        {
            return Ent::Gen::Bool(node->at("avoidGroundMovements"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::avoidWaterMovements() const
        {
            return Ent::Gen::Bool(node->at("avoidWaterMovements"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::blockedByScaryWeather() const
        {
            return Ent::Gen::Bool(node->at("blockedByScaryWeather"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::canBite() const
        {
            return Ent::Gen::Bool(node->at("canBite"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::canFlee() const
        {
            return Ent::Gen::Bool(node->at("canFlee"));
        }
        inline Ent::Gen::Float BehaviorScriptData::closeAttack_Offset_Z() const
        {
            return Ent::Gen::Float(node->at("closeAttack_Offset_Z"));
        }
        inline Ent::Gen::Float BehaviorScriptData::closeCombatDistance() const
        {
            return Ent::Gen::Float(node->at("closeCombatDistance"));
        }
        inline Ent::Gen::Float BehaviorScriptData::combatFlyingHeightOffset() const
        {
            return Ent::Gen::Float(node->at("combatFlyingHeightOffset"));
        }
        inline Ent::Gen::Int BehaviorScriptData::combatSpeedModeOnNodes() const
        {
            return Ent::Gen::Int(node->at("combatSpeedModeOnNodes"));
        }
        inline Ent::Gen::Float BehaviorScriptData::combatStopOnNodeCoolDown() const
        {
            return Ent::Gen::Float(node->at("combatStopOnNodeCoolDown"));
        }
        inline Ent::Gen::Float BehaviorScriptData::combatStopOnNodeMaxTime() const
        {
            return Ent::Gen::Float(node->at("combatStopOnNodeMaxTime"));
        }
        inline Ent::Gen::Float BehaviorScriptData::combatTooCloseDistance() const
        {
            return Ent::Gen::Float(node->at("combatTooCloseDistance"));
        }
        inline Ent::Gen::Float BehaviorScriptData::combatTriggerStopOnNodeTimerDistance() const
        {
            return Ent::Gen::Float(node->at("combatTriggerStopOnNodeTimerDistance"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::considersRunnerAsAMenace() const
        {
            return Ent::Gen::Bool(node->at("considersRunnerAsAMenace"));
        }
        inline Ent::Gen::Float BehaviorScriptData::coolDownBetweenProjectileDodge() const
        {
            return Ent::Gen::Float(node->at("coolDownBetweenProjectileDodge"));
        }
        inline Ent::Gen::Float BehaviorScriptData::drivingAimAngle() const
        {
            return Ent::Gen::Float(node->at("drivingAimAngle"));
        }
        inline Ent::Gen::Float BehaviorScriptData::drivingAimSpeed() const
        {
            return Ent::Gen::Float(node->at("drivingAimSpeed"));
        }
        inline Ent::Gen::Int BehaviorScriptData::enemyAggressivity() const
        {
            return Ent::Gen::Int(node->at("enemyAggressivity"));
        }
        inline Ent::Gen::Float BehaviorScriptData::energyAttackProbability() const
        {
            return Ent::Gen::Float(node->at("energyAttackProbability"));
        }
        inline Ent::Gen::Float BehaviorScriptData::engageInCombatDistance() const
        {
            return Ent::Gen::Float(node->at("engageInCombatDistance"));
        }
        inline Ent::Gen::Float BehaviorScriptData::farCombatDistance() const
        {
            return Ent::Gen::Float(node->at("farCombatDistance"));
        }
        inline Ent::Gen::Float BehaviorScriptData::feelsSafeWhenDangerIsThisFar() const
        {
            return Ent::Gen::Float(node->at("feelsSafeWhenDangerIsThisFar"));
        }
        inline Ent::Gen::Float BehaviorScriptData::fleeDistToEnemy() const
        {
            return Ent::Gen::Float(node->at("fleeDistToEnemy"));
        }
        inline Ent::Gen::Float BehaviorScriptData::fleeMaxDist() const
        {
            return Ent::Gen::Float(node->at("fleeMaxDist"));
        }
        inline Ent::Gen::Float BehaviorScriptData::fleeTime() const
        {
            return Ent::Gen::Float(node->at("fleeTime"));
        }
        inline Ent::Gen::Float BehaviorScriptData::flockingArenaRadius() const
        {
            return Ent::Gen::Float(node->at("flockingArenaRadius"));
        }
        inline Ent::Gen::Int BehaviorScriptData::friendAggressivity() const
        {
            return Ent::Gen::Int(node->at("friendAggressivity"));
        }
        inline Ent::Gen::Float BehaviorScriptData::goToTargetCheckDistance() const
        {
            return Ent::Gen::Float(node->at("goToTargetCheckDistance"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideFollowMalusScorePerSec() const
        {
            return Ent::Gen::Float(node->at("guideFollowMalusScorePerSec"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideFollowMaxBonusScorePerSec() const
        {
            return Ent::Gen::Float(node->at("guideFollowMaxBonusScorePerSec"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideFollowMaxDistToScore() const
        {
            return Ent::Gen::Float(node->at("guideFollowMaxDistToScore"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideFollowMaxDistanceToTrail() const
        {
            return Ent::Gen::Float(node->at("guideFollowMaxDistanceToTrail"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideFollowMinBonusScorePerSec() const
        {
            return Ent::Gen::Float(node->at("guideFollowMinBonusScorePerSec"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideFollowMinDistToScore() const
        {
            return Ent::Gen::Float(node->at("guideFollowMinDistToScore"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideFollowScoreThreshold() const
        {
            return Ent::Gen::Float(node->at("guideFollowScoreThreshold"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideFollowTimeBetweenTeleport() const
        {
            return Ent::Gen::Float(node->at("guideFollowTimeBetweenTeleport"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideMinSpeed() const
        {
            return Ent::Gen::Float(node->at("guideMinSpeed"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideRepulsiveDistIn() const
        {
            return Ent::Gen::Float(node->at("guideRepulsiveDistIn"));
        }
        inline Ent::Gen::Float BehaviorScriptData::guideRepulsiveDistOut() const
        {
            return Ent::Gen::Float(node->at("guideRepulsiveDistOut"));
        }
        inline Ent::Gen::Int BehaviorScriptData::hardFeelingsFriendlyHitCount() const
        {
            return Ent::Gen::Int(node->at("hardFeelingsFriendlyHitCount"));
        }
        inline Ent::Gen::Int BehaviorScriptData::hardFeelingsNotFriendlyHitCount() const
        {
            return Ent::Gen::Int(node->at("hardFeelingsNotFriendlyHitCount"));
        }
        inline Ent::Gen::Float BehaviorScriptData::helpOtherDoneIfLifeAboveThreshold() const
        {
            return Ent::Gen::Float(node->at("helpOtherDoneIfLifeAboveThreshold"));
        }
        inline Ent::Gen::Float BehaviorScriptData::helpOtherIfLifeBelowThreshold() const
        {
            return Ent::Gen::Float(node->at("helpOtherIfLifeBelowThreshold"));
        }
        inline Ent::Gen::Float BehaviorScriptData::innerArenaRatio() const
        {
            return Ent::Gen::Float(node->at("innerArenaRatio"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::isAffectedByStench() const
        {
            return Ent::Gen::Bool(node->at("isAffectedByStench"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::isCourageous() const
        {
            return Ent::Gen::Bool(node->at("isCourageous"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::isScaredBySoundEffect() const
        {
            return Ent::Gen::Bool(node->at("isScaredBySoundEffect"));
        }
        inline Ent::Gen::Float BehaviorScriptData::jumpAttackProbability() const
        {
            return Ent::Gen::Float(node->at("jumpAttackProbability"));
        }
        inline Ent::Gen::Float BehaviorScriptData::lifeInDangerThreshold() const
        {
            return Ent::Gen::Float(node->at("lifeInDangerThreshold"));
        }
        inline Ent::Gen::Float BehaviorScriptData::lifeInNoMoreDangerThreshold() const
        {
            return Ent::Gen::Float(node->at("lifeInNoMoreDangerThreshold"));
        }
        inline Ent::Gen::Float BehaviorScriptData::lockEnemyFollowMaxDistFromGuide() const
        {
            return Ent::Gen::Float(node->at("lockEnemyFollowMaxDistFromGuide"));
        }
        inline Ent::Gen::Float BehaviorScriptData::maxDistanceToFollowBeam() const
        {
            return Ent::Gen::Float(node->at("maxDistanceToFollowBeam"));
        }
        inline Ent::Gen::Int BehaviorScriptData::maxFollowerCount() const
        {
            return Ent::Gen::Int(node->at("maxFollowerCount"));
        }
        inline Ent::Gen::Float BehaviorScriptData::maxLookOutModeTimer() const
        {
            return Ent::Gen::Float(node->at("maxLookOutModeTimer"));
        }
        inline Ent::Gen::Float BehaviorScriptData::maxTimeBeforeStoppingToWaitForBeam() const
        {
            return Ent::Gen::Float(node->at("maxTimeBeforeStoppingToWaitForBeam"));
        }
        inline Ent::Gen::MenaceSelection BehaviorScriptData::menaceSelection() const
        {
            return Ent::Gen::MenaceSelection(node->at("menaceSelection"));
        }
        inline Ent::Gen::Float BehaviorScriptData::middleCombatDistance() const
        {
            return Ent::Gen::Float(node->at("middleCombatDistance"));
        }
        inline Ent::Gen::Float BehaviorScriptData::minAbsoluteDistanceToTeleportToMaster() const
        {
            return Ent::Gen::Float(node->at("minAbsoluteDistanceToTeleportToMaster"));
        }
        inline Ent::Gen::Float BehaviorScriptData::minDistanceToBeamPosition() const
        {
            return Ent::Gen::Float(node->at("minDistanceToBeamPosition"));
        }
        inline Ent::Gen::Float BehaviorScriptData::minDistanceToFollowBeam() const
        {
            return Ent::Gen::Float(node->at("minDistanceToFollowBeam"));
        }
        inline Ent::Gen::Float BehaviorScriptData::minNavmeshDistanceToTeleportToMaster() const
        {
            return Ent::Gen::Float(node->at("minNavmeshDistanceToTeleportToMaster"));
        }
        inline Ent::Gen::Float BehaviorScriptData::minTimeBeforeStoppingToWaitForBeam() const
        {
            return Ent::Gen::Float(node->at("minTimeBeforeStoppingToWaitForBeam"));
        }
        inline Ent::Gen::Float BehaviorScriptData::noAttackTimeAfterAttack() const
        {
            return Ent::Gen::Float(node->at("noAttackTimeAfterAttack"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::offerAGiftWhenChosen() const
        {
            return Ent::Gen::Bool(node->at("offerAGiftWhenChosen"));
        }
        inline Ent::Gen::Int BehaviorScriptData::panicAggressivityDecrease() const
        {
            return Ent::Gen::Int(node->at("panicAggressivityDecrease"));
        }
        inline Ent::Gen::Int BehaviorScriptData::panicsWhenGameEffect() const
        {
            return Ent::Gen::Int(node->at("panicsWhenGameEffect"));
        }
        inline Ent::Gen::Int BehaviorScriptData::returnOnCircleAfterMaxAttacks() const
        {
            return Ent::Gen::Int(node->at("returnOnCircleAfterMaxAttacks"));
        }
        inline Ent::Gen::Int BehaviorScriptData::roamSpeedModeOnNodes() const
        {
            return Ent::Gen::Int(node->at("roamSpeedModeOnNodes"));
        }
        inline Ent::Gen::Float BehaviorScriptData::runsForDistancesSuperiorTo() const
        {
            return Ent::Gen::Float(node->at("runsForDistancesSuperiorTo"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::searchSoulOpportunity() const
        {
            return Ent::Gen::Bool(node->at("searchSoulOpportunity"));
        }
        inline Ent::Gen::Float BehaviorScriptData::shootPreferedEnemyDistance() const
        {
            return Ent::Gen::Float(node->at("shootPreferedEnemyDistance"));
        }
        inline Array<Ent::Gen::ShootSequenceData> BehaviorScriptData::shootSequence() const
        {
            return Array<Ent::Gen::ShootSequenceData>(node->at("shootSequence"));
        }
        inline Ent::Gen::Float BehaviorScriptData::shootingMistakeMaxDelta() const
        {
            return Ent::Gen::Float(node->at("shootingMistakeMaxDelta"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::shouldConquer() const
        {
            return Ent::Gen::Bool(node->at("shouldConquer"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::shouldDodgeAfterAttack() const
        {
            return Ent::Gen::Bool(node->at("shouldDodgeAfterAttack"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::shouldHealPools() const
        {
            return Ent::Gen::Bool(node->at("shouldHealPools"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::shouldJumpInArena() const
        {
            return Ent::Gen::Bool(node->at("shouldJumpInArena"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::shouldStrafe() const
        {
            return Ent::Gen::Bool(node->at("shouldStrafe"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::shouldTranshumance() const
        {
            return Ent::Gen::Bool(node->at("shouldTranshumance"));
        }
        inline Ent::Gen::Float BehaviorScriptData::staffAngleFullHint() const
        {
            return Ent::Gen::Float(node->at("staffAngleFullHint"));
        }
        inline Ent::Gen::Float BehaviorScriptData::staffMaxTimeInAlert() const
        {
            return Ent::Gen::Float(node->at("staffMaxTimeInAlert"));
        }
        inline Ent::Gen::Int BehaviorScriptData::staffMinScoreToAlert() const
        {
            return Ent::Gen::Int(node->at("staffMinScoreToAlert"));
        }
        inline Ent::Gen::Float BehaviorScriptData::staffTimeBeforeAlertAgain() const
        {
            return Ent::Gen::Float(node->at("staffTimeBeforeAlertAgain"));
        }
        inline Ent::Gen::Bool BehaviorScriptData::usesWarningShot() const
        {
            return Ent::Gen::Bool(node->at("usesWarningShot"));
        }
        // CreatureAIGD
        inline PrimArray<Ent::Gen::String> CreatureAIGD::BehaviorModifiersTags() const
        {
            return PrimArray<Ent::Gen::String>(node->at("BehaviorModifiersTags"));
        }
        inline Ent::Gen::String CreatureAIGD::BehaviorPath() const
        {
            return Ent::Gen::String(node->at("BehaviorPath"));
        }
        inline Ent::Gen::String CreatureAIGD::BehaviorState() const
        {
            return Ent::Gen::String(node->at("BehaviorState"));
        }
        inline Ent::Gen::Bool CreatureAIGD::CanBeMaster() const
        {
            return Ent::Gen::Bool(node->at("CanBeMaster"));
        }
        inline Ent::Gen::ComponentGD CreatureAIGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String CreatureAIGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::BehaviorScriptData CreatureAIGD::behaviorScriptData() const
        {
            return Ent::Gen::BehaviorScriptData(node->at("behaviorScriptData"));
        }
        inline Ent::Gen::Float CreatureAIGD::m_oblivionTimerAfterSuspicious() const
        {
            return Ent::Gen::Float(node->at("m_oblivionTimerAfterSuspicious"));
        }
        inline Ent::Gen::Float CreatureAIGD::m_oblivionTimerBeforeSuspicious() const
        {
            return Ent::Gen::Float(node->at("m_oblivionTimerBeforeSuspicious"));
        }
        inline Ent::Gen::Float CreatureAIGD::m_timerBeforeCertain() const
        {
            return Ent::Gen::Float(node->at("m_timerBeforeCertain"));
        }
        inline Ent::Gen::Float CreatureAIGD::m_timerBeforeSuspicious() const
        {
            return Ent::Gen::Float(node->at("m_timerBeforeSuspicious"));
        }
        // BeamTargetGD
        inline Ent::Gen::Bool BeamTargetGD::CheckHotspotOrientation() const
        {
            return Ent::Gen::Bool(node->at("CheckHotspotOrientation"));
        }
        inline Ent::Gen::String BeamTargetGD::EventTriggered() const
        {
            return Ent::Gen::String(node->at("EventTriggered"));
        }
        inline Ent::Gen::HotSpotType BeamTargetGD::HotspotType() const
        {
            return Ent::Gen::HotSpotType(node->at("HotspotType"));
        }
        inline Ent::Gen::Bool BeamTargetGD::IsCollectable() const
        {
            return Ent::Gen::Bool(node->at("IsCollectable"));
        }
        inline Ent::Gen::Bool BeamTargetGD::Levitate() const
        {
            return Ent::Gen::Bool(node->at("Levitate"));
        }
        inline Ent::Gen::Float BeamTargetGD::MaxTargetableDistance() const
        {
            return Ent::Gen::Float(node->at("MaxTargetableDistance"));
        }
        inline Ent::Gen::BeamStaffMode BeamTargetGD::Mode() const
        {
            return Ent::Gen::BeamStaffMode(node->at("Mode"));
        }
        inline Ent::Gen::Bool BeamTargetGD::SpendEnergy() const
        {
            return Ent::Gen::Bool(node->at("SpendEnergy"));
        }
        inline Ent::Gen::ComponentGD BeamTargetGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String BeamTargetGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AttackAbility
        inline Ent::Gen::Float AttackAbility::Damage() const
        {
            return Ent::Gen::Float(node->at("Damage"));
        }
        inline Ent::Gen::Float AttackAbility::DistanceMax() const
        {
            return Ent::Gen::Float(node->at("DistanceMax"));
        }
        inline Ent::Gen::Float AttackAbility::DistanceMin() const
        {
            return Ent::Gen::Float(node->at("DistanceMin"));
        }
        inline Ent::Gen::Float AttackAbility::Duration() const
        {
            return Ent::Gen::Float(node->at("Duration"));
        }
        inline Ent::Gen::Float AttackAbility::EnergyCost() const
        {
            return Ent::Gen::Float(node->at("EnergyCost"));
        }
        inline Ent::Gen::FreezeData AttackAbility::FreezeData() const
        {
            return Ent::Gen::FreezeData(node->at("FreezeData"));
        }
        inline Ent::Gen::Float AttackAbility::Impact() const
        {
            return Ent::Gen::Float(node->at("Impact"));
        }
        inline Ent::Gen::CameraShakeData AttackAbility::ShakeData() const
        {
            return Ent::Gen::CameraShakeData(node->at("ShakeData"));
        }
        inline Ent::Gen::String AttackAbility::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AttackWeaponAbility
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Backward() const
        {
            return Ent::Gen::AttackAbility(node->at("Backward"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Bite() const
        {
            return Ent::Gen::AttackAbility(node->at("Bite"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Charged() const
        {
            return Ent::Gen::AttackAbility(node->at("Charged"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Dash() const
        {
            return Ent::Gen::AttackAbility(node->at("Dash"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Distant() const
        {
            return Ent::Gen::AttackAbility(node->at("Distant"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Dodge() const
        {
            return Ent::Gen::AttackAbility(node->at("Dodge"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::JumpOnto() const
        {
            return Ent::Gen::AttackAbility(node->at("JumpOnto"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Landing() const
        {
            return Ent::Gen::AttackAbility(node->at("Landing"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Long() const
        {
            return Ent::Gen::AttackAbility(node->at("Long"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Push() const
        {
            return Ent::Gen::AttackAbility(node->at("Push"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Short() const
        {
            return Ent::Gen::AttackAbility(node->at("Short"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Stomp() const
        {
            return Ent::Gen::AttackAbility(node->at("Stomp"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Unmount() const
        {
            return Ent::Gen::AttackAbility(node->at("Unmount"));
        }
        inline Ent::Gen::AttackAbility AttackWeaponAbility::Uppercut() const
        {
            return Ent::Gen::AttackAbility(node->at("Uppercut"));
        }
        inline Ent::Gen::String AttackWeaponAbility::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AttackData
        inline Ent::Gen::AttackType AttackData::DefaultAttackType() const
        {
            return Ent::Gen::AttackType(node->at("DefaultAttackType"));
        }
        inline Ent::Gen::AttackWeaponAbility AttackData::Hammer() const
        {
            return Ent::Gen::AttackWeaponAbility(node->at("Hammer"));
        }
        inline Ent::Gen::AttackWeaponAbility AttackData::Knife() const
        {
            return Ent::Gen::AttackWeaponAbility(node->at("Knife"));
        }
        inline Ent::Gen::AttackWeaponAbility AttackData::None_() const
        {
            return Ent::Gen::AttackWeaponAbility(node->at("None_"));
        }
        inline Ent::Gen::AttackWeaponAbility AttackData::Stick() const
        {
            return Ent::Gen::AttackWeaponAbility(node->at("Stick"));
        }
        inline Ent::Gen::AttackWeaponAbility AttackData::Sword() const
        {
            return Ent::Gen::AttackWeaponAbility(node->at("Sword"));
        }
        inline Ent::Gen::String AttackData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationTreeConstraintsGD_GrowData
        inline Ent::Gen::Float AnimationTreeConstraintsGD_GrowData::DegrowShakeForce() const
        {
            return Ent::Gen::Float(node->at("DegrowShakeForce"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_GrowData::GrowShakeForce() const
        {
            return Ent::Gen::Float(node->at("GrowShakeForce"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_GrowData::GrowSpeed() const
        {
            return Ent::Gen::Float(node->at("GrowSpeed"));
        }
        inline Ent::Gen::GrowingState AnimationTreeConstraintsGD_GrowData::GrowingState() const
        {
            return Ent::Gen::GrowingState(node->at("GrowingState"));
        }
        inline Ent::Gen::ProgressSoundEventData AnimationTreeConstraintsGD_GrowData::ProgressSoundEventData() const
        {
            return Ent::Gen::ProgressSoundEventData(node->at("ProgressSoundEventData"));
        }
        inline Ent::Gen::String AnimationTreeConstraintsGD_GrowData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationTreeConstraintsGD_ForceData
        inline Ent::Gen::Bool AnimationTreeConstraintsGD_ForceData::AutoSetupForceInfluence() const
        {
            return Ent::Gen::Bool(node->at("AutoSetupForceInfluence"));
        }
        inline Ent::Gen::Int AnimationTreeConstraintsGD_ForceData::AutoSetupForceInfluenceLevelStart() const
        {
            return Ent::Gen::Int(node->at("AutoSetupForceInfluenceLevelStart"));
        }
        inline Ent::Gen::Int AnimationTreeConstraintsGD_ForceData::AutoSetupForceInfluenceLevelStop() const
        {
            return Ent::Gen::Int(node->at("AutoSetupForceInfluenceLevelStop"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_ForceData::AutoSetupForceInfluenceValueAfterStop() const
        {
            return Ent::Gen::Float(node->at("AutoSetupForceInfluenceValueAfterStop"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_ForceData::AutoSetupForceInfluenceValueBeforeStart() const
        {
            return Ent::Gen::Float(node->at("AutoSetupForceInfluenceValueBeforeStart"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_ForceData::AutoSetupForceInfluenceValueStart() const
        {
            return Ent::Gen::Float(node->at("AutoSetupForceInfluenceValueStart"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_ForceData::AutoSetupForceInfluenceValueStop() const
        {
            return Ent::Gen::Float(node->at("AutoSetupForceInfluenceValueStop"));
        }
        inline Ent::Gen::String AnimationTreeConstraintsGD_ForceData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationTreeConstraintsGD_BendData
        inline Ent::Gen::Bool AnimationTreeConstraintsGD_BendData::AcceptDrag() const
        {
            return Ent::Gen::Bool(node->at("AcceptDrag"));
        }
        inline Ent::Gen::Bool AnimationTreeConstraintsGD_BendData::AcceptDragOnBaseBone() const
        {
            return Ent::Gen::Bool(node->at("AcceptDragOnBaseBone"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_BendData::AttractDuration() const
        {
            return Ent::Gen::Float(node->at("AttractDuration"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_BendData::DragOnBaseBoneAttractionStartFactor() const
        {
            return Ent::Gen::Float(node->at("DragOnBaseBoneAttractionStartFactor"));
        }
        inline Ent::Gen::Int AnimationTreeConstraintsGD_BendData::MaxBendAngleFirstBone() const
        {
            return Ent::Gen::Int(node->at("MaxBendAngleFirstBone"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_BendData::MaxBendAngleValueAtFirstBone() const
        {
            return Ent::Gen::Float(node->at("MaxBendAngleValueAtFirstBone"));
        }
        inline Ent::Gen::Float AnimationTreeConstraintsGD_BendData::MaxBendAngleValueAtLastBone() const
        {
            return Ent::Gen::Float(node->at("MaxBendAngleValueAtLastBone"));
        }
        inline Ent::Gen::String AnimationTreeConstraintsGD_BendData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationTreeConstraintsGD
        inline Ent::Gen::AnimationTreeConstraintsGD_BendData AnimationTreeConstraintsGD::BendData() const
        {
            return Ent::Gen::AnimationTreeConstraintsGD_BendData(node->at("BendData"));
        }
        inline Ent::Gen::AnimationTreeConstraintsGD_ForceData AnimationTreeConstraintsGD::ForceData() const
        {
            return Ent::Gen::AnimationTreeConstraintsGD_ForceData(node->at("ForceData"));
        }
        inline Ent::Gen::AnimationTreeConstraintsGD_GrowData AnimationTreeConstraintsGD::GrowData() const
        {
            return Ent::Gen::AnimationTreeConstraintsGD_GrowData(node->at("GrowData"));
        }
        inline Ent::Gen::ComponentGD AnimationTreeConstraintsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AnimationTreeConstraintsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationLegsConstraints_SlopeOffsetInfo
        inline Ent::Gen::Float AnimationLegsConstraints_SlopeOffsetInfo::MaxSlopeAngle() const
        {
            return Ent::Gen::Float(node->at("MaxSlopeAngle"));
        }
        inline Ent::Gen::Vector3 AnimationLegsConstraints_SlopeOffsetInfo::RotationOffset() const
        {
            return Ent::Gen::Vector3(node->at("RotationOffset"));
        }
        inline Ent::Gen::Vector3 AnimationLegsConstraints_SlopeOffsetInfo::TranslationOffset() const
        {
            return Ent::Gen::Vector3(node->at("TranslationOffset"));
        }
        inline Ent::Gen::String AnimationLegsConstraints_SlopeOffsetInfo::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationLegsConstraintsGD
        inline Ent::Gen::Bool AnimationLegsConstraintsGD::AllowHeightMapCastFallback() const
        {
            return Ent::Gen::Bool(node->at("AllowHeightMapCastFallback"));
        }
        inline Ent::Gen::AnimationLegsConstraints_SlopeOffsetInfo AnimationLegsConstraintsGD::AscendingSlopeOffsetInfo() const
        {
            return Ent::Gen::AnimationLegsConstraints_SlopeOffsetInfo(node->at("AscendingSlopeOffsetInfo"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::BackLegsCompensateExtensionThreshold() const
        {
            return Ent::Gen::Float(node->at("BackLegsCompensateExtensionThreshold"));
        }
        inline Ent::Gen::Vector2 AnimationLegsConstraintsGD::BackLegsHeightRangeForIKInfluence() const
        {
            return Ent::Gen::Vector2(node->at("BackLegsHeightRangeForIKInfluence"));
        }
        inline Ent::Gen::Bool AnimationLegsConstraintsGD::BoneBending() const
        {
            return Ent::Gen::Bool(node->at("BoneBending"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::BoneBendingAnticipation() const
        {
            return Ent::Gen::Float(node->at("BoneBendingAnticipation"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::BoneBendingAnticipationBackward() const
        {
            return Ent::Gen::Float(node->at("BoneBendingAnticipationBackward"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::BoneBendingLocomotionInfluenceSpeed() const
        {
            return Ent::Gen::Float(node->at("BoneBendingLocomotionInfluenceSpeed"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::CastDeltaDistToTriggerSmooth() const
        {
            return Ent::Gen::Float(node->at("CastDeltaDistToTriggerSmooth"));
        }
        inline Ent::Gen::AnimationLegsConstraints_SlopeOffsetInfo AnimationLegsConstraintsGD::DescendingSlopeOffsetInfo() const
        {
            return Ent::Gen::AnimationLegsConstraints_SlopeOffsetInfo(node->at("DescendingSlopeOffsetInfo"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::FeetInfluence() const
        {
            return Ent::Gen::Float(node->at("FeetInfluence"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::FrontLegsCompensateExtensionThreshold() const
        {
            return Ent::Gen::Float(node->at("FrontLegsCompensateExtensionThreshold"));
        }
        inline Ent::Gen::Vector2 AnimationLegsConstraintsGD::FrontLegsHeightRangeForIKInfluence() const
        {
            return Ent::Gen::Vector2(node->at("FrontLegsHeightRangeForIKInfluence"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::GlobalInfluence() const
        {
            return Ent::Gen::Float(node->at("GlobalInfluence"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::LegInfluence() const
        {
            return Ent::Gen::Float(node->at("LegInfluence"));
        }
        inline Ent::Gen::Bool AnimationLegsConstraintsGD::LegLock() const
        {
            return Ent::Gen::Bool(node->at("LegLock"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::MaxHeightForFootInfluence() const
        {
            return Ent::Gen::Float(node->at("MaxHeightForFootInfluence"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::ObstructionCastHitPosMarginOffsetFactor() const
        {
            return Ent::Gen::Float(node->at("ObstructionCastHitPosMarginOffsetFactor"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::ObstructionCastOffsetFactor() const
        {
            return Ent::Gen::Float(node->at("ObstructionCastOffsetFactor"));
        }
        inline Ent::Gen::Float AnimationLegsConstraintsGD::ObstructionCastSafeRadiusFactor() const
        {
            return Ent::Gen::Float(node->at("ObstructionCastSafeRadiusFactor"));
        }
        inline Ent::Gen::ScaleConverter AnimationLegsConstraintsGD::SpeedFactorFromLockedRootDistance() const
        {
            return Ent::Gen::ScaleConverter(node->at("SpeedFactorFromLockedRootDistance"));
        }
        inline Ent::Gen::ComponentGD AnimationLegsConstraintsGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Bool AnimationLegsConstraintsGD::UseObstructionCast() const
        {
            return Ent::Gen::Bool(node->at("UseObstructionCast"));
        }
        inline Ent::Gen::String AnimationLegsConstraintsGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationEventsGeneratorGD_TrackedBone
        inline Ent::Gen::String AnimationEventsGeneratorGD_TrackedBone::Name() const
        {
            return Ent::Gen::String(node->at("Name"));
        }
        inline Ent::Gen::Int AnimationEventsGeneratorGD_TrackedBone::OffsetFrameCountStart() const
        {
            return Ent::Gen::Int(node->at("OffsetFrameCountStart"));
        }
        inline Ent::Gen::Int AnimationEventsGeneratorGD_TrackedBone::OffsetFrameCountStop() const
        {
            return Ent::Gen::Int(node->at("OffsetFrameCountStop"));
        }
        inline Ent::Gen::String AnimationEventsGeneratorGD_TrackedBone::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AnimationEventsGeneratorGD
        inline Ent::Gen::ComponentGD AnimationEventsGeneratorGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Array<Ent::Gen::AnimationEventsGeneratorGD_TrackedBone> AnimationEventsGeneratorGD::TrackedBones() const
        {
            return Array<Ent::Gen::AnimationEventsGeneratorGD_TrackedBone>(node->at("TrackedBones"));
        }
        inline Ent::Gen::String AnimationEventsGeneratorGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // MoveCapacityData_AnimTagTimelineTransitionItem
        inline Ent::Gen::String MoveCapacityData_AnimTagTimelineTransitionItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::AnimTag MoveCapacityData_AnimTagTimelineTransitionItem::to() const
        {
            return Ent::Gen::AnimTag(node->at("to"));
        }
        inline Ent::Gen::AnimTagTimelineTransition MoveCapacityData_AnimTagTimelineTransitionItem::type() const
        {
            return Ent::Gen::AnimTagTimelineTransition(node->at("type"));
        }
        // MoveCapacityData_AnimTagTimelineTransitionTable
        inline Ent::Gen::String MoveCapacityData_AnimTagTimelineTransitionTable::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::AnimTag MoveCapacityData_AnimTagTimelineTransitionTable::from_() const
        {
            return Ent::Gen::AnimTag(node->at("from_"));
        }
        inline Array<Ent::Gen::MoveCapacityData_AnimTagTimelineTransitionItem> MoveCapacityData_AnimTagTimelineTransitionTable::transitions() const
        {
            return Array<Ent::Gen::MoveCapacityData_AnimTagTimelineTransitionItem>(node->at("transitions"));
        }
        // MoveCapacityData
        inline Ent::Gen::String MoveCapacityData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float MoveCapacityData::airControlFactor() const
        {
            return Ent::Gen::Float(node->at("airControlFactor"));
        }
        inline Ent::Gen::Bool MoveCapacityData::allowClampSpeedBiggerThanLocomotionDuringBlend() const
        {
            return Ent::Gen::Bool(node->at("allowClampSpeedBiggerThanLocomotionDuringBlend"));
        }
        inline Ent::Gen::Bool MoveCapacityData::allowKeepAnimationPlayRatioUnclamped() const
        {
            return Ent::Gen::Bool(node->at("allowKeepAnimationPlayRatioUnclamped"));
        }
        inline Ent::Gen::Float MoveCapacityData::angularSpeedMaxFlyDumpFactor() const
        {
            return Ent::Gen::Float(node->at("angularSpeedMaxFlyDumpFactor"));
        }
        inline Ent::Gen::Float MoveCapacityData::angularSpeedMaxGroundDumpFactor() const
        {
            return Ent::Gen::Float(node->at("angularSpeedMaxGroundDumpFactor"));
        }
        inline Ent::Gen::Float MoveCapacityData::angularSpeedMaxRiderDumpFactor() const
        {
            return Ent::Gen::Float(node->at("angularSpeedMaxRiderDumpFactor"));
        }
        inline Ent::Gen::Float MoveCapacityData::angularSpeedMaxWaterDumpFactor() const
        {
            return Ent::Gen::Float(node->at("angularSpeedMaxWaterDumpFactor"));
        }
        inline Ent::Gen::MoveCapacityData_AnimTagTimelineTransitionTable MoveCapacityData::animTagTimelineTransitionTable() const
        {
            return Ent::Gen::MoveCapacityData_AnimTagTimelineTransitionTable(node->at("animTagTimelineTransitionTable"));
        }
        inline Ent::Gen::Float MoveCapacityData::brakeDeceleration() const
        {
            return Ent::Gen::Float(node->at("brakeDeceleration"));
        }
        inline Ent::Gen::Float MoveCapacityData::capsuleBigRadius() const
        {
            return Ent::Gen::Float(node->at("capsuleBigRadius"));
        }
        inline Ent::Gen::Float MoveCapacityData::capsuleEnormousRadius() const
        {
            return Ent::Gen::Float(node->at("capsuleEnormousRadius"));
        }
        inline Ent::Gen::Float MoveCapacityData::capsuleMediumRadius() const
        {
            return Ent::Gen::Float(node->at("capsuleMediumRadius"));
        }
        inline Ent::Gen::Float MoveCapacityData::capsuleSmallRadius() const
        {
            return Ent::Gen::Float(node->at("capsuleSmallRadius"));
        }
        inline Ent::Gen::Float MoveCapacityData::capsuleTinyRadius() const
        {
            return Ent::Gen::Float(node->at("capsuleTinyRadius"));
        }
        inline Ent::Gen::ScaleConverter MoveCapacityData::constraintDetectionAnticipation() const
        {
            return Ent::Gen::ScaleConverter(node->at("constraintDetectionAnticipation"));
        }
        inline Ent::Gen::Vector3 MoveCapacityData::constraintDetectionOffset() const
        {
            return Ent::Gen::Vector3(node->at("constraintDetectionOffset"));
        }
        inline Ent::Gen::ScaleConverter MoveCapacityData::constraintDetectionRadius() const
        {
            return Ent::Gen::ScaleConverter(node->at("constraintDetectionRadius"));
        }
        inline Ent::Gen::Float MoveCapacityData::coyoteJumpMaxTime() const
        {
            return Ent::Gen::Float(node->at("coyoteJumpMaxTime"));
        }
        inline Ent::Gen::Float MoveCapacityData::crashPreventionSafeguardFactor() const
        {
            return Ent::Gen::Float(node->at("crashPreventionSafeguardFactor"));
        }
        inline Ent::Gen::Bool MoveCapacityData::doubleJump() const
        {
            return Ent::Gen::Bool(node->at("doubleJump"));
        }
        inline Ent::Gen::ScaleConverter MoveCapacityData::dropPlaneLegLenFactor() const
        {
            return Ent::Gen::ScaleConverter(node->at("dropPlaneLegLenFactor"));
        }
        inline Ent::Gen::Bool MoveCapacityData::dropSyncTrajectoryAndVisual() const
        {
            return Ent::Gen::Bool(node->at("dropSyncTrajectoryAndVisual"));
        }
        inline Ent::Gen::Float MoveCapacityData::ellipseCoeff() const
        {
            return Ent::Gen::Float(node->at("ellipseCoeff"));
        }
        inline Ent::Gen::ScaleConverter MoveCapacityData::extirpateObstacleAcceleration() const
        {
            return Ent::Gen::ScaleConverter(node->at("extirpateObstacleAcceleration"));
        }
        inline Ent::Gen::Float MoveCapacityData::extirpateObstacleDuration() const
        {
            return Ent::Gen::Float(node->at("extirpateObstacleDuration"));
        }
        inline Ent::Gen::ScaleConverter MoveCapacityData::flyCentrifugalCoeff() const
        {
            return Ent::Gen::ScaleConverter(node->at("flyCentrifugalCoeff"));
        }
        inline Ent::Gen::Float MoveCapacityData::flyCentrifugalRate() const
        {
            return Ent::Gen::Float(node->at("flyCentrifugalRate"));
        }
        inline Ent::Gen::Float MoveCapacityData::jumpAnalogScale() const
        {
            return Ent::Gen::Float(node->at("jumpAnalogScale"));
        }
        inline Ent::Gen::Bool MoveCapacityData::jumpOntoPosition() const
        {
            return Ent::Gen::Bool(node->at("jumpOntoPosition"));
        }
        inline Ent::Gen::Float MoveCapacityData::ledgeApproachSpeedMaxZ() const
        {
            return Ent::Gen::Float(node->at("ledgeApproachSpeedMaxZ"));
        }
        inline Ent::Gen::Float MoveCapacityData::ledgeDepthRadiusCoeff() const
        {
            return Ent::Gen::Float(node->at("ledgeDepthRadiusCoeff"));
        }
        inline Ent::Gen::Float MoveCapacityData::ledgeMaxDistance() const
        {
            return Ent::Gen::Float(node->at("ledgeMaxDistance"));
        }
        inline Ent::Gen::Float MoveCapacityData::ledgeMaxHeightEpsilon() const
        {
            return Ent::Gen::Float(node->at("ledgeMaxHeightEpsilon"));
        }
        inline Ent::Gen::Float MoveCapacityData::ledgeMinDepthEpsilon() const
        {
            return Ent::Gen::Float(node->at("ledgeMinDepthEpsilon"));
        }
        inline Ent::Gen::Float MoveCapacityData::ledgeMinWidthEpsilon() const
        {
            return Ent::Gen::Float(node->at("ledgeMinWidthEpsilon"));
        }
        inline Ent::Gen::Float MoveCapacityData::legLength() const
        {
            return Ent::Gen::Float(node->at("legLength"));
        }
        inline Ent::Gen::Float MoveCapacityData::mass() const
        {
            return Ent::Gen::Float(node->at("mass"));
        }
        inline Ent::Gen::Float MoveCapacityData::maxAverageSpeedDuringJumpOnto() const
        {
            return Ent::Gen::Float(node->at("maxAverageSpeedDuringJumpOnto"));
        }
        inline Ent::Gen::Float MoveCapacityData::maxFlapTime() const
        {
            return Ent::Gen::Float(node->at("maxFlapTime"));
        }
        inline Ent::Gen::Float MoveCapacityData::maxTimeBetweenFlaps() const
        {
            return Ent::Gen::Float(node->at("maxTimeBetweenFlaps"));
        }
        inline Ent::Gen::Float MoveCapacityData::minFlapTime() const
        {
            return Ent::Gen::Float(node->at("minFlapTime"));
        }
        inline Ent::Gen::Float MoveCapacityData::minSpeedToSteerPitch() const
        {
            return Ent::Gen::Float(node->at("minSpeedToSteerPitch"));
        }
        inline Ent::Gen::Float MoveCapacityData::minTimeBetweenFlaps() const
        {
            return Ent::Gen::Float(node->at("minTimeBetweenFlaps"));
        }
        inline Ent::Gen::MoveCapacityData_OrientationSpeed MoveCapacityData::orientationSpeedFly() const
        {
            return Ent::Gen::MoveCapacityData_OrientationSpeed(node->at("orientationSpeedFly"));
        }
        inline Ent::Gen::MoveCapacityData_OrientationSpeed MoveCapacityData::orientationSpeedGround() const
        {
            return Ent::Gen::MoveCapacityData_OrientationSpeed(node->at("orientationSpeedGround"));
        }
        inline Ent::Gen::MoveCapacityData_OrientationSpeed MoveCapacityData::orientationSpeedWater() const
        {
            return Ent::Gen::MoveCapacityData_OrientationSpeed(node->at("orientationSpeedWater"));
        }
        inline Ent::Gen::Float MoveCapacityData::patinateSpeedMinEnter() const
        {
            return Ent::Gen::Float(node->at("patinateSpeedMinEnter"));
        }
        inline Ent::Gen::Float MoveCapacityData::patinateSpeedMinExit() const
        {
            return Ent::Gen::Float(node->at("patinateSpeedMinExit"));
        }
        inline Ent::Gen::Float MoveCapacityData::reachSpeedAcceleration() const
        {
            return Ent::Gen::Float(node->at("reachSpeedAcceleration"));
        }
        inline Array<Ent::Gen::MoveCapacityData_ReachSpeed> MoveCapacityData::reachSpeedByLocomotion() const
        {
            return Array<Ent::Gen::MoveCapacityData_ReachSpeed>(node->at("reachSpeedByLocomotion"));
        }
        inline Ent::Gen::Float MoveCapacityData::reachSpeedDeceleration() const
        {
            return Ent::Gen::Float(node->at("reachSpeedDeceleration"));
        }
        inline Ent::Gen::Bool MoveCapacityData::reactToOtherCharacterBodyCollision() const
        {
            return Ent::Gen::Bool(node->at("reactToOtherCharacterBodyCollision"));
        }
        inline Ent::Gen::Float MoveCapacityData::sphereCastRadiusRatio() const
        {
            return Ent::Gen::Float(node->at("sphereCastRadiusRatio"));
        }
        inline Ent::Gen::Float MoveCapacityData::sphereOverrideRadius() const
        {
            return Ent::Gen::Float(node->at("sphereOverrideRadius"));
        }
        inline Ent::Gen::Float MoveCapacityData::strafeBlendIn() const
        {
            return Ent::Gen::Float(node->at("strafeBlendIn"));
        }
        inline Ent::Gen::Float MoveCapacityData::strafeBlendWeightMinToChangeAnim() const
        {
            return Ent::Gen::Float(node->at("strafeBlendWeightMinToChangeAnim"));
        }
        inline Ent::Gen::Float MoveCapacityData::strafeOrientationRateFactor() const
        {
            return Ent::Gen::Float(node->at("strafeOrientationRateFactor"));
        }
        inline Ent::Gen::SpeedMode MoveCapacityData::strafeSpeedModeMax() const
        {
            return Ent::Gen::SpeedMode(node->at("strafeSpeedModeMax"));
        }
        inline Ent::Gen::Float MoveCapacityData::strafeStopOrientationRateFactor() const
        {
            return Ent::Gen::Float(node->at("strafeStopOrientationRateFactor"));
        }
        inline Ent::Gen::Float MoveCapacityData::strafeTurnAngleMin() const
        {
            return Ent::Gen::Float(node->at("strafeTurnAngleMin"));
        }
        inline Ent::Gen::Float MoveCapacityData::trajectoryRateFactorDuringLateralLand() const
        {
            return Ent::Gen::Float(node->at("trajectoryRateFactorDuringLateralLand"));
        }
        inline Ent::Gen::Float MoveCapacityData::turnAroundInputDirectionAngleDeltaMin() const
        {
            return Ent::Gen::Float(node->at("turnAroundInputDirectionAngleDeltaMin"));
        }
        // CharacterControllerGD
        inline Ent::Gen::Bool CharacterControllerGD::AllowHeightMapFallback() const
        {
            return Ent::Gen::Bool(node->at("AllowHeightMapFallback"));
        }
        inline Ent::Gen::CharacterControllerClamberData CharacterControllerGD::ClamberData() const
        {
            return Ent::Gen::CharacterControllerClamberData(node->at("ClamberData"));
        }
        inline Ent::Gen::CharacterControllerFallData CharacterControllerGD::FallData() const
        {
            return Ent::Gen::CharacterControllerFallData(node->at("FallData"));
        }
        inline Ent::Gen::CharacterControllerGroundNormalData CharacterControllerGD::GroundNormalData() const
        {
            return Ent::Gen::CharacterControllerGroundNormalData(node->at("GroundNormalData"));
        }
        inline Ent::Gen::HeadCollisionBehaviorData CharacterControllerGD::HeadCollisionData() const
        {
            return Ent::Gen::HeadCollisionBehaviorData(node->at("HeadCollisionData"));
        }
        inline Ent::Gen::ImmersedBehaviorData CharacterControllerGD::ImmersedData() const
        {
            return Ent::Gen::ImmersedBehaviorData(node->at("ImmersedData"));
        }
        inline Ent::Gen::InputCollisionBehaviorData CharacterControllerGD::InputCollisionData() const
        {
            return Ent::Gen::InputCollisionBehaviorData(node->at("InputCollisionData"));
        }
        inline Ent::Gen::MeshNavigationBehaviorData CharacterControllerGD::MeshNavigationData() const
        {
            return Ent::Gen::MeshNavigationBehaviorData(node->at("MeshNavigationData"));
        }
        inline Ent::Gen::PredictionBehaviorData CharacterControllerGD::PredictionData() const
        {
            return Ent::Gen::PredictionBehaviorData(node->at("PredictionData"));
        }
        inline Ent::Gen::Vector3 CharacterControllerGD::RotationSmooth() const
        {
            return Ent::Gen::Vector3(node->at("RotationSmooth"));
        }
        inline Ent::Gen::CharacterControllerSlideData CharacterControllerGD::SlideData() const
        {
            return Ent::Gen::CharacterControllerSlideData(node->at("SlideData"));
        }
        inline Ent::Gen::ComponentGD CharacterControllerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String CharacterControllerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::MoveCapacityData CharacterControllerGD::moveCapacityData() const
        {
            return Ent::Gen::MoveCapacityData(node->at("moveCapacityData"));
        }
        // AnimMirroringSpecData
        inline Ent::Gen::String AnimMirroringSpecData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::String AnimMirroringSpecData::name() const
        {
            return Ent::Gen::String(node->at("name"));
        }
        inline Ent::Gen::String AnimMirroringSpecData::name2() const
        {
            return Ent::Gen::String(node->at("name2"));
        }
        inline Ent::Gen::String AnimMirroringSpecData::spec() const
        {
            return Ent::Gen::String(node->at("spec"));
        }
        // AnimMirroringData
        inline Ent::Gen::String AnimMirroringData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Array<Ent::Gen::AnimMirroringSpecData> AnimMirroringData::specs() const
        {
            return Array<Ent::Gen::AnimMirroringSpecData>(node->at("specs"));
        }
        // AnimationControllerGD
        inline Ent::Gen::String AnimationControllerGD::EDITOR_skeleton() const
        {
            return Ent::Gen::String(node->at("EDITOR_skeleton"));
        }
        inline Ent::Gen::ComponentGD AnimationControllerGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AnimationControllerGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::String AnimationControllerGD::animDatabase() const
        {
            return Ent::Gen::String(node->at("animDatabase"));
        }
        inline Ent::Gen::AnimMirroringData AnimationControllerGD::mirroringData() const
        {
            return Ent::Gen::AnimMirroringData(node->at("mirroringData"));
        }
        inline Ent::Gen::Float AnimationControllerGD::romLookAtInfluence() const
        {
            return Ent::Gen::Float(node->at("romLookAtInfluence"));
        }
        inline Ent::Gen::String AnimationControllerGD::skeleton() const
        {
            return Ent::Gen::String(node->at("skeleton"));
        }
        inline Ent::Gen::String AnimationControllerGD::syncDataName() const
        {
            return Ent::Gen::String(node->at("syncDataName"));
        }
        // ActorStates
        inline char const* ActorStates::getType() const
        {
            return node->getUnionType();
        }
        inline std::optional<Ent::Gen::ActorStateAlive> ActorStates::ActorStateAlive() const
        {
            auto sub = getSubNode("ActorStateAlive");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateAlive>{}: std::optional<Ent::Gen::ActorStateAlive>(getSubNode("ActorStateAlive"));
        }
        inline Ent::Gen::ActorStateAlive ActorStates::addActorStateAlive() const
        {
            return Ent::Gen::ActorStateAlive(addSubNode("ActorStateAlive"));
        }
        inline std::optional<Ent::Gen::ActorStateBeingImmersed> ActorStates::ActorStateBeingImmersed() const
        {
            auto sub = getSubNode("ActorStateBeingImmersed");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateBeingImmersed>{}: std::optional<Ent::Gen::ActorStateBeingImmersed>(getSubNode("ActorStateBeingImmersed"));
        }
        inline Ent::Gen::ActorStateBeingImmersed ActorStates::addActorStateBeingImmersed() const
        {
            return Ent::Gen::ActorStateBeingImmersed(addSubNode("ActorStateBeingImmersed"));
        }
        inline std::optional<Ent::Gen::ActorStateBeingInAir> ActorStates::ActorStateBeingInAir() const
        {
            auto sub = getSubNode("ActorStateBeingInAir");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateBeingInAir>{}: std::optional<Ent::Gen::ActorStateBeingInAir>(getSubNode("ActorStateBeingInAir"));
        }
        inline Ent::Gen::ActorStateBeingInAir ActorStates::addActorStateBeingInAir() const
        {
            return Ent::Gen::ActorStateBeingInAir(addSubNode("ActorStateBeingInAir"));
        }
        inline std::optional<Ent::Gen::ActorStateBeingOnGround> ActorStates::ActorStateBeingOnGround() const
        {
            auto sub = getSubNode("ActorStateBeingOnGround");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateBeingOnGround>{}: std::optional<Ent::Gen::ActorStateBeingOnGround>(getSubNode("ActorStateBeingOnGround"));
        }
        inline Ent::Gen::ActorStateBeingOnGround ActorStates::addActorStateBeingOnGround() const
        {
            return Ent::Gen::ActorStateBeingOnGround(addSubNode("ActorStateBeingOnGround"));
        }
        inline std::optional<Ent::Gen::ActorStateBuried> ActorStates::ActorStateBuried() const
        {
            auto sub = getSubNode("ActorStateBuried");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateBuried>{}: std::optional<Ent::Gen::ActorStateBuried>(getSubNode("ActorStateBuried"));
        }
        inline Ent::Gen::ActorStateBuried ActorStates::addActorStateBuried() const
        {
            return Ent::Gen::ActorStateBuried(addSubNode("ActorStateBuried"));
        }
        inline std::optional<Ent::Gen::ActorStateDead> ActorStates::ActorStateDead() const
        {
            auto sub = getSubNode("ActorStateDead");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateDead>{}: std::optional<Ent::Gen::ActorStateDead>(getSubNode("ActorStateDead"));
        }
        inline Ent::Gen::ActorStateDead ActorStates::addActorStateDead() const
        {
            return Ent::Gen::ActorStateDead(addSubNode("ActorStateDead"));
        }
        inline std::optional<Ent::Gen::ActorStateHasNoBody> ActorStates::ActorStateHasNoBody() const
        {
            auto sub = getSubNode("ActorStateHasNoBody");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateHasNoBody>{}: std::optional<Ent::Gen::ActorStateHasNoBody>(getSubNode("ActorStateHasNoBody"));
        }
        inline Ent::Gen::ActorStateHasNoBody ActorStates::addActorStateHasNoBody() const
        {
            return Ent::Gen::ActorStateHasNoBody(addSubNode("ActorStateHasNoBody"));
        }
        inline std::optional<Ent::Gen::ActorStateHoldingItem> ActorStates::ActorStateHoldingItem() const
        {
            auto sub = getSubNode("ActorStateHoldingItem");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateHoldingItem>{}: std::optional<Ent::Gen::ActorStateHoldingItem>(getSubNode("ActorStateHoldingItem"));
        }
        inline Ent::Gen::ActorStateHoldingItem ActorStates::addActorStateHoldingItem() const
        {
            return Ent::Gen::ActorStateHoldingItem(addSubNode("ActorStateHoldingItem"));
        }
        inline std::optional<Ent::Gen::ActorStateInvincible> ActorStates::ActorStateInvincible() const
        {
            auto sub = getSubNode("ActorStateInvincible");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateInvincible>{}: std::optional<Ent::Gen::ActorStateInvincible>(getSubNode("ActorStateInvincible"));
        }
        inline Ent::Gen::ActorStateInvincible ActorStates::addActorStateInvincible() const
        {
            return Ent::Gen::ActorStateInvincible(addSubNode("ActorStateInvincible"));
        }
        inline std::optional<Ent::Gen::ActorStateRegenerationFull> ActorStates::ActorStateRegenerationFull() const
        {
            auto sub = getSubNode("ActorStateRegenerationFull");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateRegenerationFull>{}: std::optional<Ent::Gen::ActorStateRegenerationFull>(getSubNode("ActorStateRegenerationFull"));
        }
        inline Ent::Gen::ActorStateRegenerationFull ActorStates::addActorStateRegenerationFull() const
        {
            return Ent::Gen::ActorStateRegenerationFull(addSubNode("ActorStateRegenerationFull"));
        }
        inline std::optional<Ent::Gen::ActorStateRegenerationLow> ActorStates::ActorStateRegenerationLow() const
        {
            auto sub = getSubNode("ActorStateRegenerationLow");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateRegenerationLow>{}: std::optional<Ent::Gen::ActorStateRegenerationLow>(getSubNode("ActorStateRegenerationLow"));
        }
        inline Ent::Gen::ActorStateRegenerationLow ActorStates::addActorStateRegenerationLow() const
        {
            return Ent::Gen::ActorStateRegenerationLow(addSubNode("ActorStateRegenerationLow"));
        }
        inline std::optional<Ent::Gen::ActorStateTeleport> ActorStates::ActorStateTeleport() const
        {
            auto sub = getSubNode("ActorStateTeleport");
            return sub == nullptr? std::optional<Ent::Gen::ActorStateTeleport>{}: std::optional<Ent::Gen::ActorStateTeleport>(getSubNode("ActorStateTeleport"));
        }
        inline Ent::Gen::ActorStateTeleport ActorStates::addActorStateTeleport() const
        {
            return Ent::Gen::ActorStateTeleport(addSubNode("ActorStateTeleport"));
        }
        inline std::optional<Ent::Gen::EntityStateBoidsHomePos> ActorStates::EntityStateBoidsHomePos() const
        {
            auto sub = getSubNode("EntityStateBoidsHomePos");
            return sub == nullptr? std::optional<Ent::Gen::EntityStateBoidsHomePos>{}: std::optional<Ent::Gen::EntityStateBoidsHomePos>(getSubNode("EntityStateBoidsHomePos"));
        }
        inline Ent::Gen::EntityStateBoidsHomePos ActorStates::addEntityStateBoidsHomePos() const
        {
            return Ent::Gen::EntityStateBoidsHomePos(addSubNode("EntityStateBoidsHomePos"));
        }
        inline std::optional<Ent::Gen::EntityStateEnergyRootState> ActorStates::EntityStateEnergyRootState() const
        {
            auto sub = getSubNode("EntityStateEnergyRootState");
            return sub == nullptr? std::optional<Ent::Gen::EntityStateEnergyRootState>{}: std::optional<Ent::Gen::EntityStateEnergyRootState>(getSubNode("EntityStateEnergyRootState"));
        }
        inline Ent::Gen::EntityStateEnergyRootState ActorStates::addEntityStateEnergyRootState() const
        {
            return Ent::Gen::EntityStateEnergyRootState(addSubNode("EntityStateEnergyRootState"));
        }
        inline std::optional<Ent::Gen::EntityStateEnergySpoutState> ActorStates::EntityStateEnergySpoutState() const
        {
            auto sub = getSubNode("EntityStateEnergySpoutState");
            return sub == nullptr? std::optional<Ent::Gen::EntityStateEnergySpoutState>{}: std::optional<Ent::Gen::EntityStateEnergySpoutState>(getSubNode("EntityStateEnergySpoutState"));
        }
        inline Ent::Gen::EntityStateEnergySpoutState ActorStates::addEntityStateEnergySpoutState() const
        {
            return Ent::Gen::EntityStateEnergySpoutState(addSubNode("EntityStateEnergySpoutState"));
        }
        inline std::optional<Ent::Gen::EntityStateForceCanBeTargeted> ActorStates::EntityStateForceCanBeTargeted() const
        {
            auto sub = getSubNode("EntityStateForceCanBeTargeted");
            return sub == nullptr? std::optional<Ent::Gen::EntityStateForceCanBeTargeted>{}: std::optional<Ent::Gen::EntityStateForceCanBeTargeted>(getSubNode("EntityStateForceCanBeTargeted"));
        }
        inline Ent::Gen::EntityStateForceCanBeTargeted ActorStates::addEntityStateForceCanBeTargeted() const
        {
            return Ent::Gen::EntityStateForceCanBeTargeted(addSubNode("EntityStateForceCanBeTargeted"));
        }
        inline std::optional<Ent::Gen::EntityStateMask> ActorStates::EntityStateMask() const
        {
            auto sub = getSubNode("EntityStateMask");
            return sub == nullptr? std::optional<Ent::Gen::EntityStateMask>{}: std::optional<Ent::Gen::EntityStateMask>(getSubNode("EntityStateMask"));
        }
        inline Ent::Gen::EntityStateMask ActorStates::addEntityStateMask() const
        {
            return Ent::Gen::EntityStateMask(addSubNode("EntityStateMask"));
        }
        inline std::optional<Ent::Gen::EntityStatePlayer> ActorStates::EntityStatePlayer() const
        {
            auto sub = getSubNode("EntityStatePlayer");
            return sub == nullptr? std::optional<Ent::Gen::EntityStatePlayer>{}: std::optional<Ent::Gen::EntityStatePlayer>(getSubNode("EntityStatePlayer"));
        }
        inline Ent::Gen::EntityStatePlayer ActorStates::addEntityStatePlayer() const
        {
            return Ent::Gen::EntityStatePlayer(addSubNode("EntityStatePlayer"));
        }
        inline std::optional<Ent::Gen::EntityStateVoxelsVolume> ActorStates::EntityStateVoxelsVolume() const
        {
            auto sub = getSubNode("EntityStateVoxelsVolume");
            return sub == nullptr? std::optional<Ent::Gen::EntityStateVoxelsVolume>{}: std::optional<Ent::Gen::EntityStateVoxelsVolume>(getSubNode("EntityStateVoxelsVolume"));
        }
        inline Ent::Gen::EntityStateVoxelsVolume ActorStates::addEntityStateVoxelsVolume() const
        {
            return Ent::Gen::EntityStateVoxelsVolume(addSubNode("EntityStateVoxelsVolume"));
        }
        // Object
        inline Ent::Gen::ActorStates Object::ActorStates() const
        {
            return Ent::Gen::ActorStates(node->at("ActorStates"));
        }
        inline Ent::Gen::Color Object::Color() const
        {
            return Ent::Gen::Color(node->at("Color"));
        }
        inline Ent::Gen::Object_Components Object::Components() const
        {
            return Ent::Gen::Object_Components(node->at("Components"));
        }
        inline Ent::Gen::String Object::InstanceOf() const
        {
            return Ent::Gen::String(node->at("InstanceOf"));
        }
        inline Ent::Gen::Object_MaxActivationLevel Object::MaxActivationLevel() const
        {
            return Ent::Gen::Object_MaxActivationLevel(node->at("MaxActivationLevel"));
        }
        inline Ent::Gen::String Object::Name() const
        {
            return Ent::Gen::String(node->at("Name"));
        }
        inline Ent::Gen::String Object::Thumbnail() const
        {
            return Ent::Gen::String(node->at("Thumbnail"));
        }
        inline Ent::Gen::Bool Object::__removed__() const
        {
            return Ent::Gen::Bool(node->at("__removed__"));
        }
        inline Ent::Gen::String Object::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // UnitTestComponent
        inline Ent::Gen::Object UnitTestComponent::Entity() const
        {
            return Ent::Gen::Object(node->at("Entity"));
        }
        inline Ent::Gen::PrimitiveSet<ReviveSideEnum> UnitTestComponent::EnumSet() const
        {
            return Ent::Gen::PrimitiveSet<ReviveSideEnum>(node->at("EnumSet"));
        }
        inline Ent::Gen::Position UnitTestComponent::Position() const
        {
            return Ent::Gen::Position(node->at("Position"));
        }
        inline Ent::Gen::ComponentGD UnitTestComponent::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String UnitTestComponent::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // Entity
        inline Ent::Gen::ActorStates Entity::ActorStates() const
        {
            return Ent::Gen::ActorStates(node->at("ActorStates"));
        }
        inline Ent::Gen::Color Entity::Color() const
        {
            return Ent::Gen::Color(node->at("Color"));
        }
        inline Ent::Gen::Components Entity::Components() const
        {
            return Ent::Gen::Components(node->at("Components"));
        }
        inline Ent::Gen::String Entity::InstanceOf() const
        {
            return Ent::Gen::String(node->at("InstanceOf"));
        }
        inline Ent::Gen::MaxActivationLevel Entity::MaxActivationLevel() const
        {
            return Ent::Gen::MaxActivationLevel(node->at("MaxActivationLevel"));
        }
        inline Ent::Gen::String Entity::Name() const
        {
            return Ent::Gen::String(node->at("Name"));
        }
        inline Ent::Gen::String Entity::Thumbnail() const
        {
            return Ent::Gen::String(node->at("Thumbnail"));
        }
        inline Ent::Gen::String Entity::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateTeleport_Inputs
        inline Ent::Gen::Orientation ActorStateTeleport_Inputs::Orientation() const
        {
            return Ent::Gen::Orientation(node->at("Orientation"));
        }
        inline Ent::Gen::Position ActorStateTeleport_Inputs::Position() const
        {
            return Ent::Gen::Position(node->at("Position"));
        }
        inline Ent::Gen::Bool ActorStateTeleport_Inputs::ResetCamera() const
        {
            return Ent::Gen::Bool(node->at("ResetCamera"));
        }
        inline Ent::Gen::Bool ActorStateTeleport_Inputs::TouchGround() const
        {
            return Ent::Gen::Bool(node->at("TouchGround"));
        }
        inline Ent::Gen::String ActorStateTeleport_Inputs::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorState
        // EntityStateVoxelsVolume
        inline Ent::Gen::ActorState EntityStateVoxelsVolume::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String EntityStateVoxelsVolume::VoxelsState() const
        {
            return Ent::Gen::String(node->at("VoxelsState"));
        }
        inline Ent::Gen::String EntityStateVoxelsVolume::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EntityStatePlayer
        inline Ent::Gen::ActorState EntityStatePlayer::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String EntityStatePlayer::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EntityStateMask
        inline Ent::Gen::String EntityStateMask::MaskMeshPath() const
        {
            return Ent::Gen::String(node->at("MaskMeshPath"));
        }
        inline Ent::Gen::ActorState EntityStateMask::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String EntityStateMask::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EntityStateForceCanBeTargeted
        inline Ent::Gen::Bool EntityStateForceCanBeTargeted::CanBeTargeted() const
        {
            return Ent::Gen::Bool(node->at("CanBeTargeted"));
        }
        inline Ent::Gen::ActorState EntityStateForceCanBeTargeted::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String EntityStateForceCanBeTargeted::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EntityStateEnergySpoutState
        inline Ent::Gen::ReviveSide EntityStateEnergySpoutState::ReviveSide() const
        {
            return Ent::Gen::ReviveSide(node->at("ReviveSide"));
        }
        inline Array<Ent::Gen::ReviveSideEvent> EntityStateEnergySpoutState::ReviveSideEvents() const
        {
            return Array<Ent::Gen::ReviveSideEvent>(node->at("ReviveSideEvents"));
        }
        inline Ent::Gen::ActorState EntityStateEnergySpoutState::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String EntityStateEnergySpoutState::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EntityStateEnergyRootState
        inline Ent::Gen::Float EntityStateEnergyRootState::Energy() const
        {
            return Ent::Gen::Float(node->at("Energy"));
        }
        inline Ent::Gen::ReviveSide EntityStateEnergyRootState::ReviveSide() const
        {
            return Ent::Gen::ReviveSide(node->at("ReviveSide"));
        }
        inline Ent::Gen::ActorState EntityStateEnergyRootState::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String EntityStateEnergyRootState::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // EntityStateBoidsHomePos
        inline Ent::Gen::Position EntityStateBoidsHomePos::HomePosition() const
        {
            return Ent::Gen::Position(node->at("HomePosition"));
        }
        inline Ent::Gen::ActorState EntityStateBoidsHomePos::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String EntityStateBoidsHomePos::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateTeleport
        inline Ent::Gen::ActorStateTeleport_Inputs ActorStateTeleport::Inputs() const
        {
            return Ent::Gen::ActorStateTeleport_Inputs(node->at("Inputs"));
        }
        inline Ent::Gen::ActorState ActorStateTeleport::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateTeleport::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateRegenerationLow
        inline Ent::Gen::Bool ActorStateRegenerationLow::NeedToBeFreed() const
        {
            return Ent::Gen::Bool(node->at("NeedToBeFreed"));
        }
        inline Ent::Gen::ActorState ActorStateRegenerationLow::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateRegenerationLow::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateRegenerationFull
        inline Ent::Gen::ActorState ActorStateRegenerationFull::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateRegenerationFull::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateInvincible
        inline Ent::Gen::ActorState ActorStateInvincible::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateInvincible::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateHoldingItem
        inline Ent::Gen::EntityRef ActorStateHoldingItem::InventoryEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("InventoryEntityRef"));
        }
        inline Ent::Gen::EntityRef ActorStateHoldingItem::ItemEntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("ItemEntityRef"));
        }
        inline Ent::Gen::ActorState ActorStateHoldingItem::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateHoldingItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateHasNoBody
        inline Ent::Gen::ActorState ActorStateHasNoBody::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateHasNoBody::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateDead
        inline Ent::Gen::LastAliveReviveSide ActorStateDead::LastAliveReviveSide() const
        {
            return Ent::Gen::LastAliveReviveSide(node->at("LastAliveReviveSide"));
        }
        inline Ent::Gen::Float ActorStateDead::ReviveLifeSigned() const
        {
            return Ent::Gen::Float(node->at("ReviveLifeSigned"));
        }
        inline Ent::Gen::ActorState ActorStateDead::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateDead::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateBuried
        inline Ent::Gen::ActorState ActorStateBuried::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateBuried::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateBeingOnGround
        inline Ent::Gen::ActorState ActorStateBeingOnGround::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateBeingOnGround::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateBeingInAir
        inline Ent::Gen::ActorState ActorStateBeingInAir::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateBeingInAir::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateBeingImmersed
        inline Ent::Gen::ActorState ActorStateBeingImmersed::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateBeingImmersed::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ActorStateAlive
        inline Ent::Gen::Float ActorStateAlive::Life() const
        {
            return Ent::Gen::Float(node->at("Life"));
        }
        inline Ent::Gen::ReviveSide ActorStateAlive::ReviveSide() const
        {
            return Ent::Gen::ReviveSide(node->at("ReviveSide"));
        }
        inline Ent::Gen::StunGauge ActorStateAlive::StunGauge() const
        {
            return Ent::Gen::StunGauge(node->at("StunGauge"));
        }
        inline Ent::Gen::ActorState ActorStateAlive::Super() const
        {
            return Ent::Gen::ActorState(node->at("Super"));
        }
        inline Ent::Gen::String ActorStateAlive::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AbilityData
        inline Ent::Gen::String AbilityData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline PrimArray<Ent::Gen::ActorAbility> AbilityData::abilities() const
        {
            return PrimArray<Ent::Gen::ActorAbility>(node->at("abilities"));
        }
        // ActorGD
        inline Ent::Gen::Archetype ActorGD::Archetype() const
        {
            return Ent::Gen::Archetype(node->at("Archetype"));
        }
        inline Ent::Gen::StyleMode ActorGD::ClassStyleTag() const
        {
            return Ent::Gen::StyleMode(node->at("ClassStyleTag"));
        }
        inline Ent::Gen::String ActorGD::FactionName() const
        {
            return Ent::Gen::String(node->at("FactionName"));
        }
        inline Ent::Gen::String ActorGD::Icon() const
        {
            return Ent::Gen::String(node->at("Icon"));
        }
        inline Ent::Gen::Bool ActorGD::InSpiritWorld() const
        {
            return Ent::Gen::Bool(node->at("InSpiritWorld"));
        }
        inline Ent::Gen::Specie ActorGD::Specie() const
        {
            return Ent::Gen::Specie(node->at("Specie"));
        }
        inline Ent::Gen::ComponentGD ActorGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::Bool ActorGD::Weapon() const
        {
            return Ent::Gen::Bool(node->at("Weapon"));
        }
        inline Ent::Gen::String ActorGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::AbilityData ActorGD::abilityData() const
        {
            return Ent::Gen::AbilityData(node->at("abilityData"));
        }
        inline Ent::Gen::AttackData ActorGD::attackData() const
        {
            return Ent::Gen::AttackData(node->at("attackData"));
        }
        inline Ent::Gen::LifeAndDamageData ActorGD::lifeAndDamageData() const
        {
            return Ent::Gen::LifeAndDamageData(node->at("lifeAndDamageData"));
        }
        inline Ent::Gen::ProjectileData ActorGD::projectileData() const
        {
            return Ent::Gen::ProjectileData(node->at("projectileData"));
        }
        inline Ent::Gen::Float ActorGD::radius() const
        {
            return Ent::Gen::Float(node->at("radius"));
        }
        inline Ent::Gen::ShootData ActorGD::shootData() const
        {
            return Ent::Gen::ShootData(node->at("shootData"));
        }
        inline Ent::Gen::StunData ActorGD::stunData() const
        {
            return Ent::Gen::StunData(node->at("stunData"));
        }
        inline Ent::Gen::Float ActorGD::volume() const
        {
            return Ent::Gen::Float(node->at("volume"));
        }
        // ProjectileGD
        inline Ent::Gen::ActorGD ProjectileGD::Super() const
        {
            return Ent::Gen::ActorGD(node->at("Super"));
        }
        inline Ent::Gen::String ProjectileGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // CreatureGD
        inline Ent::Gen::Bool CreatureGD::DisableLookAt() const
        {
            return Ent::Gen::Bool(node->at("DisableLookAt"));
        }
        inline Ent::Gen::Float CreatureGD::DivePitchAngleMax() const
        {
            return Ent::Gen::Float(node->at("DivePitchAngleMax"));
        }
        inline Ent::Gen::Float CreatureGD::DivePitchAngleMin() const
        {
            return Ent::Gen::Float(node->at("DivePitchAngleMin"));
        }
        inline Ent::Gen::Float CreatureGD::FlyPitchAngleMax() const
        {
            return Ent::Gen::Float(node->at("FlyPitchAngleMax"));
        }
        inline Ent::Gen::Float CreatureGD::FlyPitchAngleMin() const
        {
            return Ent::Gen::Float(node->at("FlyPitchAngleMin"));
        }
        inline Ent::Gen::Bool CreatureGD::IsBig() const
        {
            return Ent::Gen::Bool(node->at("IsBig"));
        }
        inline Ent::Gen::Bool CreatureGD::IsDivinity() const
        {
            return Ent::Gen::Bool(node->at("IsDivinity"));
        }
        inline Ent::Gen::Bool CreatureGD::IsGuardian() const
        {
            return Ent::Gen::Bool(node->at("IsGuardian"));
        }
        inline Ent::Gen::Bool CreatureGD::IsStaff() const
        {
            return Ent::Gen::Bool(node->at("IsStaff"));
        }
        inline Ent::Gen::Bool CreatureGD::SpawnSoulIfNoEnemy() const
        {
            return Ent::Gen::Bool(node->at("SpawnSoulIfNoEnemy"));
        }
        inline Ent::Gen::SpeedFastMinDuration CreatureGD::SpeedFastMinDuration() const
        {
            return Ent::Gen::SpeedFastMinDuration(node->at("SpeedFastMinDuration"));
        }
        inline Ent::Gen::ActorGD CreatureGD::Super() const
        {
            return Ent::Gen::ActorGD(node->at("Super"));
        }
        inline Ent::Gen::String CreatureGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::BiteData CreatureGD::biteData() const
        {
            return Ent::Gen::BiteData(node->at("biteData"));
        }
        inline Ent::Gen::CreatureDangerousness CreatureGD::dangerousnessData() const
        {
            return Ent::Gen::CreatureDangerousness(node->at("dangerousnessData"));
        }
        inline Ent::Gen::FusionData CreatureGD::fusionData() const
        {
            return Ent::Gen::FusionData(node->at("fusionData"));
        }
        inline Ent::Gen::InteractData CreatureGD::interactData() const
        {
            return Ent::Gen::InteractData(node->at("interactData"));
        }
        inline Ent::Gen::MountData CreatureGD::mountData() const
        {
            return Ent::Gen::MountData(node->at("mountData"));
        }
        inline Ent::Gen::RevivedData CreatureGD::revivedData() const
        {
            return Ent::Gen::RevivedData(node->at("revivedData"));
        }
        // ClothGD
        inline Ent::Gen::String ClothGD::BodyEventsPath() const
        {
            return Ent::Gen::String(node->at("BodyEventsPath"));
        }
        inline Ent::Gen::String ClothGD::BodyNamePath() const
        {
            return Ent::Gen::String(node->at("BodyNamePath"));
        }
        inline PrimArray<Ent::Gen::String> ClothGD::SoundBanks() const
        {
            return PrimArray<Ent::Gen::String>(node->at("SoundBanks"));
        }
        inline Ent::Gen::SoundEventMapping ClothGD::SoundEventMappingRules() const
        {
            return Ent::Gen::SoundEventMapping(node->at("SoundEventMappingRules"));
        }
        inline Ent::Gen::ActorGD ClothGD::Super() const
        {
            return Ent::Gen::ActorGD(node->at("Super"));
        }
        inline Ent::Gen::String ClothGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AIContextSlot
        inline Ent::Gen::Int AIContextSlot::Count() const
        {
            return Ent::Gen::Int(node->at("Count"));
        }
        inline Ent::Gen::String AIContextSlot::Name() const
        {
            return Ent::Gen::String(node->at("Name"));
        }
        inline Ent::Gen::String AIContextSlot::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // AIContextGD
        inline Ent::Gen::Float AIContextGD::FollowAccelerationCoeff() const
        {
            return Ent::Gen::Float(node->at("FollowAccelerationCoeff"));
        }
        inline Ent::Gen::Float AIContextGD::FollowCanStopMaxStateDuration() const
        {
            return Ent::Gen::Float(node->at("FollowCanStopMaxStateDuration"));
        }
        inline Ent::Gen::Float AIContextGD::FollowCanStopMaxTimeInExpandedZone() const
        {
            return Ent::Gen::Float(node->at("FollowCanStopMaxTimeInExpandedZone"));
        }
        inline Ent::Gen::Float AIContextGD::FollowDecelerationCoeff() const
        {
            return Ent::Gen::Float(node->at("FollowDecelerationCoeff"));
        }
        inline Ent::Gen::Float AIContextGD::FollowDeltaAngleTarget() const
        {
            return Ent::Gen::Float(node->at("FollowDeltaAngleTarget"));
        }
        inline Ent::Gen::Float AIContextGD::FollowHotspotRadius() const
        {
            return Ent::Gen::Float(node->at("FollowHotspotRadius"));
        }
        inline Ent::Gen::Float AIContextGD::FollowHotspotSpace() const
        {
            return Ent::Gen::Float(node->at("FollowHotspotSpace"));
        }
        inline Ent::Gen::Float AIContextGD::FollowRandomSpeedZoneInBeginCoeffMax() const
        {
            return Ent::Gen::Float(node->at("FollowRandomSpeedZoneInBeginCoeffMax"));
        }
        inline Ent::Gen::Float AIContextGD::FollowRandomSpeedZoneInBeginCoeffMin() const
        {
            return Ent::Gen::Float(node->at("FollowRandomSpeedZoneInBeginCoeffMin"));
        }
        inline Ent::Gen::Float AIContextGD::FollowRandomSpeedZoneInEndCoeffMax() const
        {
            return Ent::Gen::Float(node->at("FollowRandomSpeedZoneInEndCoeffMax"));
        }
        inline Ent::Gen::Float AIContextGD::FollowRandomSpeedZoneInEndCoeffMin() const
        {
            return Ent::Gen::Float(node->at("FollowRandomSpeedZoneInEndCoeffMin"));
        }
        inline Ent::Gen::Float AIContextGD::FollowRandomSynchroDelayMax() const
        {
            return Ent::Gen::Float(node->at("FollowRandomSynchroDelayMax"));
        }
        inline Ent::Gen::Float AIContextGD::FollowRandomSynchroDelayMin() const
        {
            return Ent::Gen::Float(node->at("FollowRandomSynchroDelayMin"));
        }
        inline Ent::Gen::Float AIContextGD::FollowSpeedChangeThreshold() const
        {
            return Ent::Gen::Float(node->at("FollowSpeedChangeThreshold"));
        }
        inline Ent::Gen::Float AIContextGD::FollowSpeedZoneInBegin() const
        {
            return Ent::Gen::Float(node->at("FollowSpeedZoneInBegin"));
        }
        inline Ent::Gen::Float AIContextGD::FollowSpeedZoneInEnd() const
        {
            return Ent::Gen::Float(node->at("FollowSpeedZoneInEnd"));
        }
        inline Ent::Gen::Float AIContextGD::FollowSpeedZoneOutEnd() const
        {
            return Ent::Gen::Float(node->at("FollowSpeedZoneOutEnd"));
        }
        inline Ent::Gen::Float AIContextGD::FollowTargetDistRadiusFactor() const
        {
            return Ent::Gen::Float(node->at("FollowTargetDistRadiusFactor"));
        }
        inline Ent::Gen::ComponentGD AIContextGD::Super() const
        {
            return Ent::Gen::ComponentGD(node->at("Super"));
        }
        inline Ent::Gen::String AIContextGD::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        inline Ent::Gen::Float AIContextGD::attackCircleRadius() const
        {
            return Ent::Gen::Float(node->at("attackCircleRadius"));
        }
        inline Ent::Gen::Float AIContextGD::distanceBetweenCreatures() const
        {
            return Ent::Gen::Float(node->at("distanceBetweenCreatures"));
        }
        inline Ent::Gen::Float AIContextGD::distantReachCircleRadius() const
        {
            return Ent::Gen::Float(node->at("distantReachCircleRadius"));
        }
        inline Ent::Gen::Float AIContextGD::followCircleRadius() const
        {
            return Ent::Gen::Float(node->at("followCircleRadius"));
        }
        inline Ent::Gen::Float AIContextGD::lockTargetCircleRadius() const
        {
            return Ent::Gen::Float(node->at("lockTargetCircleRadius"));
        }
        inline Array<Ent::Gen::AIContextSlot> AIContextGD::slots() const
        {
            return Array<Ent::Gen::AIContextSlot>(node->at("slots"));
        }
        // MapOfObjectItem_A
        inline Ent::Gen::String MapOfObjectItem_A::Value() const
        {
            return Ent::Gen::String(node->at("Value"));
        }
        inline Ent::Gen::String MapOfObjectItem_A::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ProjectileShooterData
        inline Ent::Gen::EntityRef ProjectileShooterData::SubEntity() const
        {
            return Ent::Gen::EntityRef(node->at("SubEntity"));
        }
        inline Ent::Gen::String ProjectileShooterData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // ReviveSideData
        inline Ent::Gen::EntityRef ReviveSideData::EntityRef() const
        {
            return Ent::Gen::EntityRef(node->at("EntityRef"));
        }
        inline Ent::Gen::String ReviveSideData::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // Scene
        inline Ent::Gen::ObjectSet<char const*, Ent::Gen::Entity> Scene::Objects() const
        {
            return Ent::Gen::ObjectSet<char const*, Ent::Gen::Entity>(node->at("Objects"));
        }
        inline Ent::Gen::Int Scene::Version() const
        {
            return Ent::Gen::Int(node->at("Version"));
        }
        inline Ent::Gen::String Scene::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
        // SetOfObjectItem
        inline Ent::Gen::String SetOfObjectItem::Name() const
        {
            return Ent::Gen::String(node->at("Name"));
        }
        inline Ent::Gen::String SetOfObjectItem::Value() const
        {
            return Ent::Gen::String(node->at("Value"));
        }
        inline Ent::Gen::String SetOfObjectItem::_comment() const
        {
            return Ent::Gen::String(node->at("_comment"));
        }
    } // Gen
} // Ent
