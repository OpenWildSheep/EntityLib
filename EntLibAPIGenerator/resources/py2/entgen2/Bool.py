

from entgen2_helpers import *

class Bool(Primitive[bool]):
    def __init__(self, node):
        super(Bool, self).__init__(bool, node)

    def set(self, val):  # type: (bool) -> None
        return self._node.set_bool(val)
