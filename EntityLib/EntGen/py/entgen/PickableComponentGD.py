
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ResponsiblePointer_ActorState_ import *


class PickableComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PickableComponentGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PickableComponentGD.schema_name))
    @property
    def StatesForPicker(self): return (lambda n: Array(ResponsiblePointer_ActorState_, n))(self._node.at("StatesForPicker"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




