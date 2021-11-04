
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTest import *

from EntityLibPy import Node

class CineEventTestIsCanceled(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestIsCanceled"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestIsCanceled
        return CineEventTestIsCanceled(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestIsCanceled.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestIsCanceled
        return CineEventTestIsCanceled(entlib.make_node(CineEventTestIsCanceled.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




