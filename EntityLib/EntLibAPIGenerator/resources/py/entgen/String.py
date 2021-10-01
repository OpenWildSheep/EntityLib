

from entgen_helpers import *

class String(Primitive[str]):
    def __init__(self, node):
        super(String, self).__init__(str, node)

    def set(self, val):  # type: (str) -> None
        return self._node.set_string(val)

    def __str__(self):
        return self._node.value

