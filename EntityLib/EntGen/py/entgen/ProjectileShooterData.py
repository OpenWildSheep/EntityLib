
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *

from EntityLibPy import Node

class ProjectileShooterData(HelperObject):
    schema_name = "ProjectileShooterData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileShooterData
        return ProjectileShooterData(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileShooterData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileShooterData
        return ProjectileShooterData(entlib.make_node(ProjectileShooterData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SubEntity(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SubEntity"))
    @SubEntity.setter
    def SubEntity(self, val): self.SubEntity.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




