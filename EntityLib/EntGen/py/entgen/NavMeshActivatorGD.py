
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *

from EntityLibPy import Node

class NavMeshActivatorGD(HelperObject):
    schema_name = "NavMeshActivatorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NavMeshActivatorGD
        return NavMeshActivatorGD(entlib.load_node_file(sourcefile, entlib.get_schema(NavMeshActivatorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NavMeshActivatorGD
        return NavMeshActivatorGD(entlib.make_node(NavMeshActivatorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActivationZoneSize(self):  # type: ()->Float
        return Float(self._node.at("ActivationZoneSize"))
    @ActivationZoneSize.setter
    def ActivationZoneSize(self, val): self.ActivationZoneSize.set(val)
    @property
    def SizeLayerMask(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("SizeLayerMask"))
    @SizeLayerMask.setter
    def SizeLayerMask(self, val): self.SizeLayerMask.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




