
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.EventCameraData import *
from entgen.Float import *
from entgen.String import *


class TriggerEventCameraGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TriggerEventCameraGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TriggerEventCameraGD.schema_name))
    @property
    def EventCameraData(self): return EventCameraData(self._node.at("EventCameraData"))
    @property
    def PlayAnimBeforeTrigger(self): return String(self._node.at("PlayAnimBeforeTrigger"))
    @PlayAnimBeforeTrigger.setter
    def PlayAnimBeforeTrigger(self, val): self.PlayAnimBeforeTrigger.set(val)
    @property
    def PlayAnimsWhenTriggered(self): return (lambda n: PrimArray(String, n))(self._node.at("PlayAnimsWhenTriggered"))
    @PlayAnimsWhenTriggered.setter
    def PlayAnimsWhenTriggered(self, val): self.PlayAnimsWhenTriggered.set(val)
    @property
    def Radius(self): return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def UseDuration(self): return Bool(self._node.at("UseDuration"))
    @UseDuration.setter
    def UseDuration(self, val): self.UseDuration.set(val)
    @property
    def UsePhysics(self): return Bool(self._node.at("UsePhysics"))
    @UsePhysics.setter
    def UsePhysics(self, val): self.UsePhysics.set(val)
    @property
    def UseRadius(self): return Bool(self._node.at("UseRadius"))
    @UseRadius.setter
    def UseRadius(self, val): self.UseRadius.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




