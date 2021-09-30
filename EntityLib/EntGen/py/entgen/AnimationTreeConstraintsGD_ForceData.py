
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *


class AnimationTreeConstraintsGD_ForceData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::ForceData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_ForceData.schema_name))
    @property
    def AutoSetupForceInfluence(self): return Bool(self._node.at("AutoSetupForceInfluence"))
    @AutoSetupForceInfluence.setter
    def AutoSetupForceInfluence(self, val): self.AutoSetupForceInfluence.set(val)
    @property
    def AutoSetupForceInfluenceLevelStart(self): return Int(self._node.at("AutoSetupForceInfluenceLevelStart"))
    @AutoSetupForceInfluenceLevelStart.setter
    def AutoSetupForceInfluenceLevelStart(self, val): self.AutoSetupForceInfluenceLevelStart.set(val)
    @property
    def AutoSetupForceInfluenceLevelStop(self): return Int(self._node.at("AutoSetupForceInfluenceLevelStop"))
    @AutoSetupForceInfluenceLevelStop.setter
    def AutoSetupForceInfluenceLevelStop(self, val): self.AutoSetupForceInfluenceLevelStop.set(val)
    @property
    def AutoSetupForceInfluenceValueAfterStop(self): return Float(self._node.at("AutoSetupForceInfluenceValueAfterStop"))
    @AutoSetupForceInfluenceValueAfterStop.setter
    def AutoSetupForceInfluenceValueAfterStop(self, val): self.AutoSetupForceInfluenceValueAfterStop.set(val)
    @property
    def AutoSetupForceInfluenceValueBeforeStart(self): return Float(self._node.at("AutoSetupForceInfluenceValueBeforeStart"))
    @AutoSetupForceInfluenceValueBeforeStart.setter
    def AutoSetupForceInfluenceValueBeforeStart(self, val): self.AutoSetupForceInfluenceValueBeforeStart.set(val)
    @property
    def AutoSetupForceInfluenceValueStart(self): return Float(self._node.at("AutoSetupForceInfluenceValueStart"))
    @AutoSetupForceInfluenceValueStart.setter
    def AutoSetupForceInfluenceValueStart(self, val): self.AutoSetupForceInfluenceValueStart.set(val)
    @property
    def AutoSetupForceInfluenceValueStop(self): return Float(self._node.at("AutoSetupForceInfluenceValueStop"))
    @AutoSetupForceInfluenceValueStop.setter
    def AutoSetupForceInfluenceValueStop(self, val): self.AutoSetupForceInfluenceValueStop.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




