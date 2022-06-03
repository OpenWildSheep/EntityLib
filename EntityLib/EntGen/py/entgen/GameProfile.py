
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class GameProfile(HelperObject):
    schema_name = "GameProfile"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameProfile
        return GameProfile(entlib.load_node_file(sourcefile, entlib.get_schema(GameProfile.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameProfile
        return GameProfile(entlib.make_node(GameProfile.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def TypedScoreOverTimeList(self):  # type: ()->Map[str, Array[Array[TupleNode[Type[GameTimeInMs], Type[Float]]]]]
        return (lambda n: Map(str, (lambda n: Array((lambda n: Array(TupleNode, n)), n)), n))(self._node.at("TypedScoreOverTimeList"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




