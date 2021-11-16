
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AnimTag import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class DirectionSync(HelperObject):
    schema_name = "DirectionSync"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DirectionSync
        return DirectionSync(entlib.load_node_file(sourcefile, entlib.get_schema(DirectionSync.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DirectionSync
        return DirectionSync(entlib.make_node(DirectionSync.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def isOpposite(self):  # type: ()->Bool
        return Bool(self._node.at("isOpposite"))
    @isOpposite.setter
    def isOpposite(self, val): self.isOpposite.set(val)
    @property
    def mirrorKey(self):  # type: ()->Bool
        return Bool(self._node.at("mirrorKey"))
    @mirrorKey.setter
    def mirrorKey(self, val): self.mirrorKey.set(val)
    @property
    def syncCoeff(self):  # type: ()->Float
        return Float(self._node.at("syncCoeff"))
    @syncCoeff.setter
    def syncCoeff(self, val): self.syncCoeff.set(val)
    @property
    def tag1(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("tag1"))
    @tag1.setter
    def tag1(self, val): self.tag1.set(val)
    @property
    def tag2(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("tag2"))
    @tag2.setter
    def tag2(self, val): self.tag2.set(val)
    pass




