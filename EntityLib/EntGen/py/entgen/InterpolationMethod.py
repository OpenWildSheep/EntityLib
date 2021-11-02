
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class InterpolationMethodEnum(Enum):
    Spline = "Spline"
    BSpline = "BSpline"
    InterpolationMethod_COUNT = "InterpolationMethod_COUNT"


class InterpolationMethod(Primitive[InterpolationMethodEnum]):  # Enum
    def __init__(self, node):
        super(InterpolationMethod, self).__init__(InterpolationMethodEnum, node)
    schema_name = "InterpolationMethod"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> InterpolationMethod
        return InterpolationMethod(node)
    def set(self, val):  # type: (InterpolationMethodEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




