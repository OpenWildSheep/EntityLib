
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ResponsiblePointer_ActorState_ import *

from EntityLibPy import Node

class EntityStateSet(HelperObject):
    schema_name = "EntityStateSet"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateSet
        return EntityStateSet(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateSet.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateSet
        return EntityStateSet(entlib.make_node(EntityStateSet.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityStates(self):  # type: ()->Array[ResponsiblePointer_ActorState_]
        return (lambda n: Array(ResponsiblePointer_ActorState_, n))(self._node.at("EntityStates"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




