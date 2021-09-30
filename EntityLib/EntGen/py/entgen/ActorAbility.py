
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class ActorAbilityEnum(Enum):
    landing = "landing"
    crouch = "crouch"
    fly = "fly"
    ride = "ride"
    dive = "dive"
    stinky = "stinky"
    ActorAbility_COUNT = "ActorAbility_COUNT"


class ActorAbility(Primitive[ActorAbilityEnum]):  # Enum
    def __init__(self, node):
        super().__init__(ActorAbilityEnum, node)
    schema_name = "ActorAbility"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ActorAbility
        return ActorAbility(node)
    def set(self, val):  # type: (ActorAbilityEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




