
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class ActorCategoryEnum(Enum):
    CATEGORY_All = "CATEGORY_All"
    CATEGORY_Action = "CATEGORY_Action"
    CATEGORY_AnimationLegConstraint = "CATEGORY_AnimationLegConstraint"
    CATEGORY_ActionAttack = "CATEGORY_ActionAttack"
    CATEGORY_Attitude = "CATEGORY_Attitude"
    CATEGORY_Context = "CATEGORY_Context"
    CATEGORY_Control = "CATEGORY_Control"
    CATEGORY_ActionCosmetic = "CATEGORY_ActionCosmetic"
    CATEGORY_ActionDamage = "CATEGORY_ActionDamage"
    CATEGORY_ActionDefault = "CATEGORY_ActionDefault"
    CATEGORY_ActionDie = "CATEGORY_ActionDie"
    CATEGORY_Environment = "CATEGORY_Environment"
    CATEGORY_Fall = "CATEGORY_Fall"
    CATEGORY_ActionGrab = "CATEGORY_ActionGrab"
    CATEGORY_Hint = "CATEGORY_Hint"
    CATEGORY_LookAt = "CATEGORY_LookAt"
    CATEGORY_ActionJump = "CATEGORY_ActionJump"
    CATEGORY_ActionLand = "CATEGORY_ActionLand"
    CATEGORY_Life = "CATEGORY_Life"
    CATEGORY_Locomotion = "CATEGORY_Locomotion"
    CATEGORY_ActionMove = "CATEGORY_ActionMove"
    CATEGORY_Persistent = "CATEGORY_Persistent"
    CATEGORY_Purgatory = "CATEGORY_Purgatory"
    CATEGORY_ActionSlide = "CATEGORY_ActionSlide"
    CATEGORY_ActionStop = "CATEGORY_ActionStop"
    CATEGORY_ActionStrafe = "CATEGORY_ActionStrafe"
    CATEGORY_Transition = "CATEGORY_Transition"
    CATEGORY_Trigger = "CATEGORY_Trigger"
    CATEGORY_ActionWingFlutter = "CATEGORY_ActionWingFlutter"
    CATEGORY_Health = "CATEGORY_Health"
    CATEGORY_HealthAlive = "CATEGORY_HealthAlive"
    CATEGORY_HealthDead = "CATEGORY_HealthDead"
    CATEGORY_EntitySwitchTransition = "CATEGORY_EntitySwitchTransition"
    CATEGORY_EnergyRoot = "CATEGORY_EnergyRoot"
    CATEGORY_EnergySpout = "CATEGORY_EnergySpout"
    CATEGORY_Energy = "CATEGORY_Energy"
    CATEGORY_GPE = "CATEGORY_GPE"
    CATEGORY_SpiritAnimal = "CATEGORY_SpiritAnimal"
    CATEGORY_Hatching = "CATEGORY_Hatching"
    CATEGORY_Respawn = "CATEGORY_Respawn"
    CATEGORY_Save = "CATEGORY_Save"
    CATEGORY_Cinematic = "CATEGORY_Cinematic"
    CATEGORY_Loading = "CATEGORY_Loading"
    ActorCategory_COUNT = "ActorCategory_COUNT"


class ActorCategory(Primitive[ActorCategoryEnum]):  # Enum
    def __init__(self, node):
        super(ActorCategory, self).__init__(ActorCategoryEnum, node)
    schema_name = "ActorCategory"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ActorCategory
        return ActorCategory(node)
    def set(self, val):  # type: (ActorCategoryEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




