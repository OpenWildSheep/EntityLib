
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.String import *


class EventTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EventTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EventTriggerGD.schema_name))
    @property
    def Events(self): return (lambda n: PrimArray(String, n))(self._node.at("Events"))
    @Events.setter
    def Events(self, val): self.Events.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




