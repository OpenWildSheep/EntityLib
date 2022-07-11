
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class StreamingLocatorGD(HelperObject):
    schema_name = "StreamingLocatorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StreamingLocatorGD
        return StreamingLocatorGD(entlib.load_node_file(sourcefile, entlib.get_schema(StreamingLocatorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StreamingLocatorGD
        return StreamingLocatorGD(entlib.make_node(StreamingLocatorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CenterOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("CenterOffset"))
    @CenterOffset.setter
    def CenterOffset(self, val): self.CenterOffset.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




