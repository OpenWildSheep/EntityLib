
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityRef import *


class ProjectileShooterData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProjectileShooterData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileShooterData.schema_name))
    @property
    def SubEntity(self): return EntityRef(self._node.at("SubEntity"))
    @SubEntity.setter
    def SubEntity(self, val): self.SubEntity.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




