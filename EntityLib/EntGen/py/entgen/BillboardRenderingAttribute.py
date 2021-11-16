
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class BillboardRenderingAttributeEnum(Enum):
    Horizontal = "Horizontal"
    Vertical = "Vertical"
    Frontal = "Frontal"
    BillboardRenderingAttribute_COUNT = "BillboardRenderingAttribute_COUNT"


class BillboardRenderingAttribute(Primitive[BillboardRenderingAttributeEnum]):  # Enum
    def __init__(self, node):
        super(BillboardRenderingAttribute, self).__init__(BillboardRenderingAttributeEnum, node)
    schema_name = "BillboardRenderingAttribute"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> BillboardRenderingAttribute
        return BillboardRenderingAttribute(node)
    def set(self, val):  # type: (BillboardRenderingAttributeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




