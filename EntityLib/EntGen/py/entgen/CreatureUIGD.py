
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class CreatureUIGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureUIGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureUIGD
        return CreatureUIGD(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureUIGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureUIGD
        return CreatureUIGD(entlib.make_node(CreatureUIGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def LifeBarLength(self):  # type: ()->Float
        return Float(self._node.at("LifeBarLength"))
    @LifeBarLength.setter
    def LifeBarLength(self, val): self.LifeBarLength.set(val)
    @property
    def LifeBarWidth(self):  # type: ()->Float
        return Float(self._node.at("LifeBarWidth"))
    @LifeBarWidth.setter
    def LifeBarWidth(self, val): self.LifeBarWidth.set(val)
    @property
    def LifeBarZOffset(self):  # type: ()->Float
        return Float(self._node.at("LifeBarZOffset"))
    @LifeBarZOffset.setter
    def LifeBarZOffset(self, val): self.LifeBarZOffset.set(val)
    @property
    def ShowLifeBar(self):  # type: ()->Bool
        return Bool(self._node.at("ShowLifeBar"))
    @ShowLifeBar.setter
    def ShowLifeBar(self, val): self.ShowLifeBar.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




