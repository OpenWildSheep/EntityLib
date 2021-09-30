
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class CameraDataGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CameraDataGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CameraDataGD.schema_name))
    @property
    def CameraDataResourcePath(self): return String(self._node.at("CameraDataResourcePath"))
    @CameraDataResourcePath.setter
    def CameraDataResourcePath(self, val): self.CameraDataResourcePath.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




