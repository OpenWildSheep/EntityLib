
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


class PrimitiveColliderTypeEnum(Enum):
    Undefined = "Undefined"
    Sphere = "Sphere"
    Box = "Box"
    Capsule = "Capsule"
    Cylinder = "Cylinder"
    Mesh = "Mesh"
    PrimitiveColliderType_COUNT = "PrimitiveColliderType_COUNT"


class PrimitiveColliderType(Primitive[PrimitiveColliderTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(PrimitiveColliderTypeEnum, node)
    schema_name = "PrimitiveColliderType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> PrimitiveColliderType
        return PrimitiveColliderType(node)
    def set(self, val):  # type: (PrimitiveColliderTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




