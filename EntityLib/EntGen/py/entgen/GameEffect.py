
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Component import *
from entgen.Float import *

from EntityLibPy import Node

class GameEffect(HelperObject):
    schema_name = "GameEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameEffect
        return GameEffect(entlib.load_node_file(sourcefile, entlib.get_schema(GameEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameEffect
        return GameEffect(entlib.make_node(GameEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def PerceptionDistance(self):  # type: ()->Float
        return Float(self._node.at("PerceptionDistance"))
    @PerceptionDistance.setter
    def PerceptionDistance(self, val): self.PerceptionDistance.set(val)
    @property
    def RadiusChangeDuration(self):  # type: ()->Float
        return Float(self._node.at("RadiusChangeDuration"))
    @RadiusChangeDuration.setter
    def RadiusChangeDuration(self, val): self.RadiusChangeDuration.set(val)
    @property
    def RadiusStart(self):  # type: ()->Float
        return Float(self._node.at("RadiusStart"))
    @RadiusStart.setter
    def RadiusStart(self, val): self.RadiusStart.set(val)
    @property
    def RadiusStop(self):  # type: ()->Float
        return Float(self._node.at("RadiusStop"))
    @RadiusStop.setter
    def RadiusStop(self, val): self.RadiusStop.set(val)
    @property
    def Super(self):  # type: ()->Component
        return Component(self._node.at("Super"))
    @property
    def TimeBeforeStart(self):  # type: ()->Float
        return Float(self._node.at("TimeBeforeStart"))
    @TimeBeforeStart.setter
    def TimeBeforeStart(self, val): self.TimeBeforeStart.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




