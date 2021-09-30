

from entgen_helpers import *


class Int(Primitive[int]):
    def __init__(self, node):
        super(Int, self).__init__(int, node)

    def set(self, val):  # type: (int) -> None
        return self._node.set_int(val)
