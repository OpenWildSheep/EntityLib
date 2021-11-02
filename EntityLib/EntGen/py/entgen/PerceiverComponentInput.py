
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.PerceiverComponentInput_usePerception import *

from EntityLibPy import Node

class PerceiverComponentInput(HelperObject):
    schema_name = "PerceiverComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PerceiverComponentInput
        return PerceiverComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(PerceiverComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PerceiverComponentInput
        return PerceiverComponentInput(entlib.make_node(PerceiverComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def usePerception(self):  # type: ()->PerceiverComponentInput_usePerception
        return PerceiverComponentInput_usePerception(self._node.at("usePerception"))
    pass




