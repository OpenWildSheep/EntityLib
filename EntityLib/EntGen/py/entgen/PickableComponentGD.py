
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ResponsiblePointer_ActorState_ import *

from EntityLibPy import Node

class PickableComponentGD(HelperObject):
    schema_name = "PickableComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PickableComponentGD
        return PickableComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(PickableComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PickableComponentGD
        return PickableComponentGD(entlib.make_node(PickableComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def StatesForPicker(self):  # type: ()->Array[ResponsiblePointer_ActorState_]
        return (lambda n: Array(ResponsiblePointer_ActorState_, n))(self._node.at("StatesForPicker"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




