
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.InGameCameraParams import *

from EntityLibPy import Node

class InGameCameraObservationParams(HelperObject):
    schema_name = "InGameCameraObservationParams"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InGameCameraObservationParams
        return InGameCameraObservationParams(entlib.load_node_file(sourcefile, entlib.get_schema(InGameCameraObservationParams.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InGameCameraObservationParams
        return InGameCameraObservationParams(entlib.make_node(InGameCameraObservationParams.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def aim(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("aim"))
    @property
    def fps(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("fps"))
    @property
    def lock(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("lock"))
    @property
    def motionconstraint(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("motionconstraint"))
    @property
    def purgatory(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("purgatory"))
    @property
    def shoulder(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("shoulder"))
    @property
    def strongattack(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("strongattack"))
    @property
    def thirdperson(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("thirdperson"))
    @property
    def zoom(self):  # type: ()->InGameCameraParams
        return InGameCameraParams(self._node.at("zoom"))
    pass




