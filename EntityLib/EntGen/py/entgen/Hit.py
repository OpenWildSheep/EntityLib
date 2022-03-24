
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.BaseParameters import *
from entgen.DamagesInstant import *
from entgen.TargetCollision import *

from EntityLibPy import Node

class Hit(HelperObject):
    schema_name = "Hit"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Hit
        return Hit(entlib.load_node_file(sourcefile, entlib.get_schema(Hit.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Hit
        return Hit(entlib.make_node(Hit.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BaseParameters(self):  # type: ()->BaseParameters
        return BaseParameters(self._node.at("BaseParameters"))
    @property
    def DamageInstantParameters(self):  # type: ()->DamagesInstant
        return DamagesInstant(self._node.at("DamageInstantParameters"))
    @property
    def TargetCollision(self):  # type: ()->TargetCollision
        return TargetCollision(self._node.at("TargetCollision"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




