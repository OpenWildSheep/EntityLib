
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *


class CharacterControllerGroundNormalData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerGroundNormalData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerGroundNormalData.schema_name))
    @property
    def AllowOtherCreatureCast(self): return Bool(self._node.at("AllowOtherCreatureCast"))
    @AllowOtherCreatureCast.setter
    def AllowOtherCreatureCast(self, val): self.AllowOtherCreatureCast.set(val)
    @property
    def PercentageEdgeTolerance(self): return Float(self._node.at("PercentageEdgeTolerance"))
    @PercentageEdgeTolerance.setter
    def PercentageEdgeTolerance(self, val): self.PercentageEdgeTolerance.set(val)
    @property
    def PercentageExtirpate(self): return Float(self._node.at("PercentageExtirpate"))
    @PercentageExtirpate.setter
    def PercentageExtirpate(self, val): self.PercentageExtirpate.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




