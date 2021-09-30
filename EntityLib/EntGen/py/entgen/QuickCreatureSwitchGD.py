
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *


class QuickCreatureSwitchGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/QuickCreatureSwitchGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(QuickCreatureSwitchGD.schema_name))
    @property
    def CreatureEntityRefs(self): return (lambda n: PrimArray(EntityRef, n))(self._node.at("CreatureEntityRefs"))
    @CreatureEntityRefs.setter
    def CreatureEntityRefs(self, val): self.CreatureEntityRefs.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




