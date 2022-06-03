
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class Pasta_Easing_CurveEnum(Enum):
    Linear = "Linear"
    EaseInSin = "EaseInSin"
    EaseInQuad = "EaseInQuad"
    EaseInCubic = "EaseInCubic"
    EaseInQuart = "EaseInQuart"
    EaseInQuint = "EaseInQuint"
    EaseInExp = "EaseInExp"
    EaseOutSin = "EaseOutSin"
    EaseOutQuad = "EaseOutQuad"
    EaseOutCubic = "EaseOutCubic"
    EaseOutQuart = "EaseOutQuart"
    EaseOutQuint = "EaseOutQuint"
    EaseOutExp = "EaseOutExp"
    EaseInoutSin = "EaseInoutSin"
    EaseInoutQuad = "EaseInoutQuad"
    EaseInoutCubic = "EaseInoutCubic"
    EaseInoutQuart = "EaseInoutQuart"
    EaseInoutQuint = "EaseInoutQuint"
    EaseInoutExp = "EaseInoutExp"
    EaseInCirc = "EaseInCirc"
    EaseOutCirc = "EaseOutCirc"
    EaseInoutCirc = "EaseInoutCirc"
    EaseOutElastic = "EaseOutElastic"
    Count = "Count"


class Pasta_Easing_Curve(Primitive[Pasta_Easing_CurveEnum]):  # Enum
    def __init__(self, node):
        super(Pasta_Easing_Curve, self).__init__(Pasta_Easing_CurveEnum, node)
    schema_name = "Pasta::Easing::Curve"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Pasta_Easing_Curve
        return Pasta_Easing_Curve(node)
    def set(self, val):  # type: (Pasta_Easing_CurveEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




