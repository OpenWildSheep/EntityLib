
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ProjectileShooterData import *
from entgen.String import *


class ProjectileShooterGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProjectileShooterGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileShooterGD.schema_name))
    @property
    def ProjectileShooterData(self): return (lambda n: Map(str, ProjectileShooterData, n))(self._node.at("ProjectileShooterData"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




