
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class FadeEffect(HelperObject):
    schema_name = "FadeEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FadeEffect
        return FadeEffect(entlib.load_node_file(sourcefile, entlib.get_schema(FadeEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FadeEffect
        return FadeEffect(entlib.make_node(FadeEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def affectVisibilityProperty(self):  # type: ()->Bool
        return Bool(self._node.at("affectVisibilityProperty"))
    @affectVisibilityProperty.setter
    def affectVisibilityProperty(self, val): self.affectVisibilityProperty.set(val)
    @property
    def delay(self):  # type: ()->Float
        return Float(self._node.at("delay"))
    @delay.setter
    def delay(self, val): self.delay.set(val)
    @property
    def destinationAlpha(self):  # type: ()->Float
        return Float(self._node.at("destinationAlpha"))
    @destinationAlpha.setter
    def destinationAlpha(self, val): self.destinationAlpha.set(val)
    @property
    def duration(self):  # type: ()->Float
        return Float(self._node.at("duration"))
    @duration.setter
    def duration(self, val): self.duration.set(val)
    @property
    def infiniteDuration(self):  # type: ()->Bool
        return Bool(self._node.at("infiniteDuration"))
    @infiniteDuration.setter
    def infiniteDuration(self, val): self.infiniteDuration.set(val)
    @property
    def sourceAlpha(self):  # type: ()->Float
        return Float(self._node.at("sourceAlpha"))
    @sourceAlpha.setter
    def sourceAlpha(self, val): self.sourceAlpha.set(val)
    pass




