
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class AnimationTreeConstraintsGD_ForceData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::ForceData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTreeConstraintsGD_ForceData
        return AnimationTreeConstraintsGD_ForceData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_ForceData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTreeConstraintsGD_ForceData
        return AnimationTreeConstraintsGD_ForceData(entlib.make_node(AnimationTreeConstraintsGD_ForceData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AutoSetupForceInfluence(self):  # type: ()->Bool
        return Bool(self._node.at("AutoSetupForceInfluence"))
    @AutoSetupForceInfluence.setter
    def AutoSetupForceInfluence(self, val): self.AutoSetupForceInfluence.set(val)
    @property
    def AutoSetupForceInfluenceLevelStart(self):  # type: ()->Int
        return Int(self._node.at("AutoSetupForceInfluenceLevelStart"))
    @AutoSetupForceInfluenceLevelStart.setter
    def AutoSetupForceInfluenceLevelStart(self, val): self.AutoSetupForceInfluenceLevelStart.set(val)
    @property
    def AutoSetupForceInfluenceLevelStop(self):  # type: ()->Int
        return Int(self._node.at("AutoSetupForceInfluenceLevelStop"))
    @AutoSetupForceInfluenceLevelStop.setter
    def AutoSetupForceInfluenceLevelStop(self, val): self.AutoSetupForceInfluenceLevelStop.set(val)
    @property
    def AutoSetupForceInfluenceValueAfterStop(self):  # type: ()->Float
        return Float(self._node.at("AutoSetupForceInfluenceValueAfterStop"))
    @AutoSetupForceInfluenceValueAfterStop.setter
    def AutoSetupForceInfluenceValueAfterStop(self, val): self.AutoSetupForceInfluenceValueAfterStop.set(val)
    @property
    def AutoSetupForceInfluenceValueBeforeStart(self):  # type: ()->Float
        return Float(self._node.at("AutoSetupForceInfluenceValueBeforeStart"))
    @AutoSetupForceInfluenceValueBeforeStart.setter
    def AutoSetupForceInfluenceValueBeforeStart(self, val): self.AutoSetupForceInfluenceValueBeforeStart.set(val)
    @property
    def AutoSetupForceInfluenceValueStart(self):  # type: ()->Float
        return Float(self._node.at("AutoSetupForceInfluenceValueStart"))
    @AutoSetupForceInfluenceValueStart.setter
    def AutoSetupForceInfluenceValueStart(self, val): self.AutoSetupForceInfluenceValueStart.set(val)
    @property
    def AutoSetupForceInfluenceValueStop(self):  # type: ()->Float
        return Float(self._node.at("AutoSetupForceInfluenceValueStop"))
    @AutoSetupForceInfluenceValueStop.setter
    def AutoSetupForceInfluenceValueStop(self, val): self.AutoSetupForceInfluenceValueStop.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




