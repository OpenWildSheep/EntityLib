
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class TrailRenderingAttributeEnum(Enum):
    Horizontal = "Horizontal"
    Vertical = "Vertical"
    Frontal = "Frontal"
    TrailRenderingAttribute_COUNT = "TrailRenderingAttribute_COUNT"


class TrailRenderingAttribute(Primitive[TrailRenderingAttributeEnum]):  # Enum
    def __init__(self, node):
        super(TrailRenderingAttribute, self).__init__(TrailRenderingAttributeEnum, node)
    schema_name = "TrailRenderingAttribute"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> TrailRenderingAttribute
        return TrailRenderingAttribute(node)
    def set(self, val):  # type: (TrailRenderingAttributeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




