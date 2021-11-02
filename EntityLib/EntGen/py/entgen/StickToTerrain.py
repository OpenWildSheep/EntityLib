
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class StickToTerrain(HelperObject):
    schema_name = "StickToTerrain"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StickToTerrain
        return StickToTerrain(entlib.load_node_file(sourcefile, entlib.get_schema(StickToTerrain.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StickToTerrain
        return StickToTerrain(entlib.make_node(StickToTerrain.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NormalRatio(self):  # type: ()->Float
        return Float(self._node.at("NormalRatio"))
    @NormalRatio.setter
    def NormalRatio(self, val): self.NormalRatio.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def ZOffset(self):  # type: ()->Float
        return Float(self._node.at("ZOffset"))
    @ZOffset.setter
    def ZOffset(self, val): self.ZOffset.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def precisionRadius(self):  # type: ()->Float
        return Float(self._node.at("precisionRadius"))
    @precisionRadius.setter
    def precisionRadius(self, val): self.precisionRadius.set(val)
    @property
    def useNormal(self):  # type: ()->Bool
        return Bool(self._node.at("useNormal"))
    @useNormal.setter
    def useNormal(self, val): self.useNormal.set(val)
    pass




