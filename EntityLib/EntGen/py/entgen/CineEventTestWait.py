
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTest import *
from entgen.Float import *

from EntityLibPy import Node

class CineEventTestWait(HelperObject):
    schema_name = "CineEventTestWait"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestWait
        return CineEventTestWait(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestWait.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestWait
        return CineEventTestWait(entlib.make_node(CineEventTestWait.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




