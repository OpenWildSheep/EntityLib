
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class MissionHolderGD(HelperObject):
    schema_name = "MissionHolderGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MissionHolderGD
        return MissionHolderGD(entlib.load_node_file(sourcefile, entlib.get_schema(MissionHolderGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MissionHolderGD
        return MissionHolderGD(entlib.make_node(MissionHolderGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Private(self):  # type: ()->Bool
        return Bool(self._node.at("Private"))
    @Private.setter
    def Private(self, val): self.Private.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




