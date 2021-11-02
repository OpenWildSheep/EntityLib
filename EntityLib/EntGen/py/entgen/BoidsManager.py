
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *

from EntityLibPy import Node

class BoidsManager(HelperObject):
    schema_name = "BoidsManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BoidsManager
        return BoidsManager(entlib.load_node_file(sourcefile, entlib.get_schema(BoidsManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BoidsManager
        return BoidsManager(entlib.make_node(BoidsManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FirstRootSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("FirstRootSpeedFactor"))
    @FirstRootSpeedFactor.setter
    def FirstRootSpeedFactor(self, val): self.FirstRootSpeedFactor.set(val)
    @property
    def MergeEntityDistanceMultiplier(self):  # type: ()->Float
        return Float(self._node.at("MergeEntityDistanceMultiplier"))
    @MergeEntityDistanceMultiplier.setter
    def MergeEntityDistanceMultiplier(self, val): self.MergeEntityDistanceMultiplier.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def boidPresets(self):  # type: ()->String
        return String(self._node.at("boidPresets"))
    @boidPresets.setter
    def boidPresets(self, val): self.boidPresets.set(val)
    pass




