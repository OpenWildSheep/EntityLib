
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class CameraDataGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CameraDataGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraDataGD
        return CameraDataGD(entlib.load_node_file(sourcefile, entlib.get_schema(CameraDataGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraDataGD
        return CameraDataGD(entlib.make_node(CameraDataGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CameraDataResourcePath(self):  # type: ()->String
        return String(self._node.at("CameraDataResourcePath"))
    @CameraDataResourcePath.setter
    def CameraDataResourcePath(self, val): self.CameraDataResourcePath.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




