
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class CustomStreamingBehavior(HelperObject):
    schema_name = "CustomStreamingBehavior"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CustomStreamingBehavior
        return CustomStreamingBehavior(entlib.load_node_file(sourcefile, entlib.get_schema(CustomStreamingBehavior.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CustomStreamingBehavior
        return CustomStreamingBehavior(entlib.make_node(CustomStreamingBehavior.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Ignore(self):  # type: ()->Bool
        return Bool(self._node.at("Ignore"))
    @Ignore.setter
    def Ignore(self, val): self.Ignore.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




