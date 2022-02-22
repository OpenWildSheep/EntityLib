
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.GameEffect import *

from EntityLibPy import Node

class CallForHelpEffect(HelperObject):
    schema_name = "CallForHelpEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CallForHelpEffect
        return CallForHelpEffect(entlib.load_node_file(sourcefile, entlib.get_schema(CallForHelpEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CallForHelpEffect
        return CallForHelpEffect(entlib.make_node(CallForHelpEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CallType(self):  # type: ()->String
        return String(self._node.at("CallType"))
    @CallType.setter
    def CallType(self, val): self.CallType.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




