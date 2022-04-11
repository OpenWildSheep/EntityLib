
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ResponsiblePointer_GameEffect_ import *
from entgen.Vector3 import *

from EntityLibPy import Node

class sGameEffectTemplate(HelperObject):
    schema_name = "sGameEffectTemplate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sGameEffectTemplate
        return sGameEffectTemplate(entlib.load_node_file(sourcefile, entlib.get_schema(sGameEffectTemplate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sGameEffectTemplate
        return sGameEffectTemplate(entlib.make_node(sGameEffectTemplate.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def Effect(self):  # type: ()->ResponsiblePointer_GameEffect_
        return ResponsiblePointer_GameEffect_(self._node.at("Effect"))
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




