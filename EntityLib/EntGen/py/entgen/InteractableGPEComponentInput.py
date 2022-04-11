
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.Interactor import *

from EntityLibPy import Node

class InteractableGPEComponentInput(HelperObject):
    schema_name = "InteractableGPEComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InteractableGPEComponentInput
        return InteractableGPEComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(InteractableGPEComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InteractableGPEComponentInput
        return InteractableGPEComponentInput(entlib.make_node(InteractableGPEComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Interactor(self):  # type: ()->Interactor
        return Interactor(self._node.at("Interactor"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




