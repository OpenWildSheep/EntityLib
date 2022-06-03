
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.Bool import *
from entgen.MinReviveRatio import *

from EntityLibPy import Node

class EntityStateCreatureHatching_Inputs(HelperObject):
    schema_name = "EntityStateCreatureHatching::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateCreatureHatching_Inputs
        return EntityStateCreatureHatching_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateCreatureHatching_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateCreatureHatching_Inputs
        return EntityStateCreatureHatching_Inputs(entlib.make_node(EntityStateCreatureHatching_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergySide(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("EnergySide"))
    @EnergySide.setter
    def EnergySide(self, val): self.EnergySide.set(val)
    @property
    def ForceSuccess(self):  # type: ()->Bool
        return Bool(self._node.at("ForceSuccess"))
    @ForceSuccess.setter
    def ForceSuccess(self, val): self.ForceSuccess.set(val)
    @property
    def MinReviveRatio(self):  # type: ()->MinReviveRatio
        return MinReviveRatio(self._node.at("MinReviveRatio"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




