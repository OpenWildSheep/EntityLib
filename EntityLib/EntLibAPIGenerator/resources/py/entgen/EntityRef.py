
import EntityLibPy
from entgen_helpers import *

class EntityRef(Primitive[EntityLibPy.EntityRef]):
    def __init__(self, node):
        super(EntityRef, self).__init__(EntityLibPy.EntityRef, node)

    def set(self, val):  # type: (EntityLibPy.EntityRef) -> None
        return self._node.set_entityref(val)
