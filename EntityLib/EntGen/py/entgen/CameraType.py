
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class CameraTypeEnum(Enum):
    NONE = "NONE"
    Death = "Death"
    Editor = "Editor"
    Event = "Event"
    Free = "Free"
    ThirdPerson = "ThirdPerson"
    ThirdPersonFollow = "ThirdPersonFollow"
    ThirdPersonAim = "ThirdPersonAim"
    ThirdPersonClamber = "ThirdPersonClamber"
    MotionConstraint = "MotionConstraint"
    OnSpline = "OnSpline"
    OnBones = "OnBones"
    TopView = "TopView"
    EntitySwap = "EntitySwap"
    Locked = "Locked"
    Pan = "Pan"
    CameraType_COUNT = "CameraType_COUNT"


class CameraType(Primitive[CameraTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(CameraTypeEnum, node)
    schema_name = "CameraType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> CameraType
        return CameraType(node)
    def set(self, val):  # type: (CameraTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




