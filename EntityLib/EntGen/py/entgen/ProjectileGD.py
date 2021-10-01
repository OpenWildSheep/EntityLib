
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorGD import *

from EntityLibPy import Node

class ProjectileGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProjectileGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileGD
        return ProjectileGD(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileGD
        return ProjectileGD(entlib.make_node(ProjectileGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorGD
        return ActorGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




