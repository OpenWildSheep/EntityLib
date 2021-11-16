
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *

from EntityLibPy import Node

class QuickCreatureSwitchGD(HelperObject):
    schema_name = "QuickCreatureSwitchGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->QuickCreatureSwitchGD
        return QuickCreatureSwitchGD(entlib.load_node_file(sourcefile, entlib.get_schema(QuickCreatureSwitchGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->QuickCreatureSwitchGD
        return QuickCreatureSwitchGD(entlib.make_node(QuickCreatureSwitchGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CreatureEntityRefs(self):  # type: ()->PrimArray[EntityRef]
        return (lambda n: PrimArray(EntityRef, n))(self._node.at("CreatureEntityRefs"))
    @CreatureEntityRefs.setter
    def CreatureEntityRefs(self, val): self.CreatureEntityRefs.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




