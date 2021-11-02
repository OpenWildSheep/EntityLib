
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node
class Position(TupleNode[Tuple[Type[Int], Type[Int], Type[Float], Type[Float], Type[Float]]]):
    def __init__(self, node=None):  # type: (EntityLibPy.Node) -> None
        super(Position, self).__init__((Int, Int, Float, Float, Float), node)
    schema_name = "Position"

    def get_0(self):  # type: () -> Int
        return Int(self._node.at(0))
    def get_1(self):  # type: () -> Int
        return Int(self._node.at(1))
    def get_2(self):  # type: () -> Float
        return Float(self._node.at(2))
    def get_3(self):  # type: () -> Float
        return Float(self._node.at(3))
    def get_4(self):  # type: () -> Float
        return Float(self._node.at(4))



