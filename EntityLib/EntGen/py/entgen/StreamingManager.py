
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Manager import *

from EntityLibPy import Node

class StreamingManager(HelperObject):
    schema_name = "StreamingManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StreamingManager
        return StreamingManager(entlib.load_node_file(sourcefile, entlib.get_schema(StreamingManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StreamingManager
        return StreamingManager(entlib.make_node(StreamingManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DisableStreaming(self):  # type: ()->Bool
        return Bool(self._node.at("DisableStreaming"))
    @DisableStreaming.setter
    def DisableStreaming(self, val): self.DisableStreaming.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




