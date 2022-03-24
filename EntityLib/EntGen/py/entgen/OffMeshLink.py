
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.NavMeshActionType import *
from entgen.String import *
from entgen.Bool import *
from entgen.EntityRef import *

from EntityLibPy import Node

class OffMeshLink(HelperObject):
    schema_name = "OffMeshLink"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OffMeshLink
        return OffMeshLink(entlib.load_node_file(sourcefile, entlib.get_schema(OffMeshLink.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OffMeshLink
        return OffMeshLink(entlib.make_node(OffMeshLink.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def action(self):  # type: ()->NavMeshActionType
        return NavMeshActionType(self._node.at("action"))
    @action.setter
    def action(self, val): self.action.set(val)
    @property
    def bidirectional(self):  # type: ()->Bool
        return Bool(self._node.at("bidirectional"))
    @bidirectional.setter
    def bidirectional(self, val): self.bidirectional.set(val)
    @property
    def destination(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("destination"))
    @destination.setter
    def destination(self, val): self.destination.set(val)
    pass




