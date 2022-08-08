
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.enableSynchronization import *
from entgen.tryGrasp import *

from EntityLibPy import Node

class GrasperComponentInput(HelperObject):
    schema_name = "GrasperComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GrasperComponentInput
        return GrasperComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(GrasperComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GrasperComponentInput
        return GrasperComponentInput(entlib.make_node(GrasperComponentInput.schema_name))
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
    def enableSynchronization(self):  # type: ()->enableSynchronization
        return enableSynchronization(self._node.at("enableSynchronization"))
    @property
    def tryGrasp(self):  # type: ()->tryGrasp
        return tryGrasp(self._node.at("tryGrasp"))
    pass



