
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.CameraType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *


class CameraSetterGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CameraSetterGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CameraSetterGD.schema_name))
    @property
    def SetPositionToHotspot(self): return Bool(self._node.at("SetPositionToHotspot"))
    @SetPositionToHotspot.setter
    def SetPositionToHotspot(self, val): self.SetPositionToHotspot.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def SwitchToType(self): return Bool(self._node.at("SwitchToType"))
    @SwitchToType.setter
    def SwitchToType(self, val): self.SwitchToType.set(val)
    @property
    def Type_(self): return CameraType(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




