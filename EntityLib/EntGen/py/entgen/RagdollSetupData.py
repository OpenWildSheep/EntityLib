
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class RagdollSetupData(HelperObject):
    schema_name = "RagdollSetupData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RagdollSetupData
        return RagdollSetupData(entlib.load_node_file(sourcefile, entlib.get_schema(RagdollSetupData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RagdollSetupData
        return RagdollSetupData(entlib.make_node(RagdollSetupData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def blend(self):  # type: ()->Float
        return Float(self._node.at("blend"))
    @blend.setter
    def blend(self, val): self.blend.set(val)
    @property
    def inertiaFactor(self):  # type: ()->Float
        return Float(self._node.at("inertiaFactor"))
    @inertiaFactor.setter
    def inertiaFactor(self, val): self.inertiaFactor.set(val)
    @property
    def jointsRigidity(self):  # type: ()->Float
        return Float(self._node.at("jointsRigidity"))
    @jointsRigidity.setter
    def jointsRigidity(self, val): self.jointsRigidity.set(val)
    pass




