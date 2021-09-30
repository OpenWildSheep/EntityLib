
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *


class TestCreature(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestCreature"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TestCreature.schema_name))
    @property
    def FullCursed(self): return EntityRef(self._node.at("FullCursed"))
    @FullCursed.setter
    def FullCursed(self, val): self.FullCursed.set(val)
    @property
    def FullLush(self): return EntityRef(self._node.at("FullLush"))
    @FullLush.setter
    def FullLush(self, val): self.FullLush.set(val)
    @property
    def SklCursed(self): return EntityRef(self._node.at("SklCursed"))
    @SklCursed.setter
    def SklCursed(self, val): self.SklCursed.set(val)
    @property
    def SklLush(self): return EntityRef(self._node.at("SklLush"))
    @SklLush.setter
    def SklLush(self, val): self.SklLush.set(val)
    @property
    def SklNeutral(self): return EntityRef(self._node.at("SklNeutral"))
    @SklNeutral.setter
    def SklNeutral(self, val): self.SklNeutral.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




