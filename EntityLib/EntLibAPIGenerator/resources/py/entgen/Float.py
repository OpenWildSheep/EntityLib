

from entgen_helpers import *

class Float(Primitive[float]):
    def __init__(self, node):
        super(Float, self).__init__(float, node)

    def set(self, val):  # type: (float) -> None
        return self._node.set_float(val)
