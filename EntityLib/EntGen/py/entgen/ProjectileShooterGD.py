
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ProjectileShooterData import *
from entgen.String import *

from EntityLibPy import Node

class ProjectileShooterGD(HelperObject):
    schema_name = "ProjectileShooterGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileShooterGD
        return ProjectileShooterGD(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileShooterGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileShooterGD
        return ProjectileShooterGD(entlib.make_node(ProjectileShooterGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ProjectileShooterData(self):  # type: ()->Map[str, ProjectileShooterData]
        return (lambda n: Map(str, ProjectileShooterData, n))(self._node.at("ProjectileShooterData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




