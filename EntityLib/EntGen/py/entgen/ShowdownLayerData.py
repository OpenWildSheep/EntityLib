
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ShowdownLayerInfo import *

from EntityLibPy import Node

class ShowdownLayerData(HelperObject):
    schema_name = "ShowdownLayerData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShowdownLayerData
        return ShowdownLayerData(entlib.load_node_file(sourcefile, entlib.get_schema(ShowdownLayerData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShowdownLayerData
        return ShowdownLayerData(entlib.make_node(ShowdownLayerData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Attacked(self):  # type: ()->ShowdownLayerInfo
        return ShowdownLayerInfo(self._node.at("Attacked"))
    @property
    def Danger(self):  # type: ()->ShowdownLayerInfo
        return ShowdownLayerInfo(self._node.at("Danger"))
    @property
    def Detected(self):  # type: ()->ShowdownLayerInfo
        return ShowdownLayerInfo(self._node.at("Detected"))
    @property
    def Suspected(self):  # type: ()->ShowdownLayerInfo
        return ShowdownLayerInfo(self._node.at("Suspected"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




