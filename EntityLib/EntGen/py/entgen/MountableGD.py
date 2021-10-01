
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.String import *
from entgen.MountableSnapLine_ControlPoint import *

from EntityLibPy import Node

class MountableGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountableGD
        return MountableGD(entlib.load_node_file(sourcefile, entlib.get_schema(MountableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountableGD
        return MountableGD(entlib.make_node(MountableGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("HotspotNames"))
    @HotspotNames.setter
    def HotspotNames(self, val): self.HotspotNames.set(val)
    @property
    def SnapLine(self):  # type: ()->Array[MountableSnapLine_ControlPoint]
        return (lambda n: Array(MountableSnapLine_ControlPoint, n))(self._node.at("SnapLine"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




