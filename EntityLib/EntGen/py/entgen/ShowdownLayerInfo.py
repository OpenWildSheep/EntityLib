
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class ShowdownLayerInfo(HelperObject):
    schema_name = "ShowdownLayerInfo"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShowdownLayerInfo
        return ShowdownLayerInfo(entlib.load_node_file(sourcefile, entlib.get_schema(ShowdownLayerInfo.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShowdownLayerInfo
        return ShowdownLayerInfo(entlib.make_node(ShowdownLayerInfo.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CoolDown(self):  # type: ()->Float
        return Float(self._node.at("CoolDown"))
    @CoolDown.setter
    def CoolDown(self, val): self.CoolDown.set(val)
    @property
    def DistanceRTPC(self):  # type: ()->String
        return String(self._node.at("DistanceRTPC"))
    @DistanceRTPC.setter
    def DistanceRTPC(self, val): self.DistanceRTPC.set(val)
    @property
    def Loop(self):  # type: ()->Bool
        return Bool(self._node.at("Loop"))
    @Loop.setter
    def Loop(self, val): self.Loop.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Priority(self):  # type: ()->String
        return String(self._node.at("Priority"))
    @Priority.setter
    def Priority(self, val): self.Priority.set(val)
    @property
    def UninvolvedDistanceRTPC(self):  # type: ()->String
        return String(self._node.at("UninvolvedDistanceRTPC"))
    @UninvolvedDistanceRTPC.setter
    def UninvolvedDistanceRTPC(self, val): self.UninvolvedDistanceRTPC.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




