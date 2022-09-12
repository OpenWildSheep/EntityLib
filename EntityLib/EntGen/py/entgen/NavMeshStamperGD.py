
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.VolumeConstraintStamper import *
from entgen.MeshStamper import *
from entgen.OffMeshLink import *
from entgen.ZoneStamper import *

from EntityLibPy import Node

class NavMeshStamperGD(HelperObject):
    schema_name = "NavMeshStamperGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NavMeshStamperGD
        return NavMeshStamperGD(entlib.load_node_file(sourcefile, entlib.get_schema(NavMeshStamperGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NavMeshStamperGD
        return NavMeshStamperGD(entlib.make_node(NavMeshStamperGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def IsActive(self):  # type: ()->Bool
        return Bool(self._node.at("IsActive"))
    @IsActive.setter
    def IsActive(self, val): self.IsActive.set(val)
    @property
    def MeshStampers(self):  # type: ()->Array[MeshStamper]
        return (lambda n: Array(MeshStamper, n))(self._node.at("MeshStampers"))
    @property
    def OffMeshLinks(self):  # type: ()->Array[OffMeshLink]
        return (lambda n: Array(OffMeshLink, n))(self._node.at("OffMeshLinks"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UseSkinnedMeshStamper(self):  # type: ()->Bool
        return Bool(self._node.at("UseSkinnedMeshStamper"))
    @UseSkinnedMeshStamper.setter
    def UseSkinnedMeshStamper(self, val): self.UseSkinnedMeshStamper.set(val)
    @property
    def VolumeConstraintStamper(self):  # type: ()->VolumeConstraintStamper
        return VolumeConstraintStamper(self._node.at("VolumeConstraintStamper"))
    @property
    def ZoneStampers(self):  # type: ()->Array[ZoneStamper]
        return (lambda n: Array(ZoneStamper, n))(self._node.at("ZoneStampers"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




