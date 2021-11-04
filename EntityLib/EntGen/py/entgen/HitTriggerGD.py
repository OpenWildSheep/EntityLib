
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class HitTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HitTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HitTriggerGD
        return HitTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(HitTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HitTriggerGD
        return HitTriggerGD(entlib.make_node(HitTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




