
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *


class CreatureUIGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureUIGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CreatureUIGD.schema_name))
    @property
    def LifeBarLength(self): return Float(self._node.at("LifeBarLength"))
    @LifeBarLength.setter
    def LifeBarLength(self, val): self.LifeBarLength.set(val)
    @property
    def LifeBarWidth(self): return Float(self._node.at("LifeBarWidth"))
    @LifeBarWidth.setter
    def LifeBarWidth(self, val): self.LifeBarWidth.set(val)
    @property
    def LifeBarZOffset(self): return Float(self._node.at("LifeBarZOffset"))
    @LifeBarZOffset.setter
    def LifeBarZOffset(self, val): self.LifeBarZOffset.set(val)
    @property
    def ShowLifeBar(self): return Bool(self._node.at("ShowLifeBar"))
    @ShowLifeBar.setter
    def ShowLifeBar(self, val): self.ShowLifeBar.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




