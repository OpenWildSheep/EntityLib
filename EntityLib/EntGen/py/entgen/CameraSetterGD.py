
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.CameraType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class CameraSetterGD(HelperObject):
    schema_name = "CameraSetterGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraSetterGD
        return CameraSetterGD(entlib.load_node_file(sourcefile, entlib.get_schema(CameraSetterGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraSetterGD
        return CameraSetterGD(entlib.make_node(CameraSetterGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SetPositionToHotspot(self):  # type: ()->Bool
        return Bool(self._node.at("SetPositionToHotspot"))
    @SetPositionToHotspot.setter
    def SetPositionToHotspot(self, val): self.SetPositionToHotspot.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def SwitchToType(self):  # type: ()->Bool
        return Bool(self._node.at("SwitchToType"))
    @SwitchToType.setter
    def SwitchToType(self, val): self.SwitchToType.set(val)
    @property
    def Type_(self):  # type: ()->CameraType
        return CameraType(self._node.at("Type"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




