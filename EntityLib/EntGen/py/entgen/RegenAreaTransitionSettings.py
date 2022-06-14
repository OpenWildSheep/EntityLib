
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class RegenAreaTransitionSettings(HelperObject):
    schema_name = "RegenAreaTransitionSettings"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenAreaTransitionSettings
        return RegenAreaTransitionSettings(entlib.load_node_file(sourcefile, entlib.get_schema(RegenAreaTransitionSettings.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenAreaTransitionSettings
        return RegenAreaTransitionSettings(entlib.make_node(RegenAreaTransitionSettings.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def TransitionWaveRadialSpeed(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("TransitionWaveRadialSpeed"))
    @property
    def TransitionWaveWidth(self):  # type: ()->Float
        return Float(self._node.at("TransitionWaveWidth"))
    @TransitionWaveWidth.setter
    def TransitionWaveWidth(self, val): self.TransitionWaveWidth.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




