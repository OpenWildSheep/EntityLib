
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ID import *
from entgen.Position import *
from entgen.Quat import *
from entgen.Vector3 import *

from EntityLibPy import Node

class PhysicsReplicateData(HelperObject):
    schema_name = "PhysicsReplicateData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsReplicateData
        return PhysicsReplicateData(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsReplicateData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsReplicateData
        return PhysicsReplicateData(entlib.make_node(PhysicsReplicateData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngularV(self):  # type: ()->Vector3
        return Vector3(self._node.at("AngularV"))
    @AngularV.setter
    def AngularV(self, val): self.AngularV.set(val)
    @property
    def ID(self):  # type: ()->ID
        return ID(self._node.at("ID"))
    @property
    def LinearV(self):  # type: ()->Vector3
        return Vector3(self._node.at("LinearV"))
    @LinearV.setter
    def LinearV(self, val): self.LinearV.set(val)
    @property
    def Position(self):  # type: ()->Position
        return Position(self._node.at("Position"))
    @property
    def Rotation(self):  # type: ()->Quat
        return Quat(self._node.at("Rotation"))
    @Rotation.setter
    def Rotation(self, val): self.Rotation.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




