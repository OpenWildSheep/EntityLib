
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class SideMapGateGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SideMapGateGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SideMapGateGD.schema_name))
    @property
    def SideMapName(self): return String(self._node.at("SideMapName"))
    @SideMapName.setter
    def SideMapName(self, val): self.SideMapName.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




