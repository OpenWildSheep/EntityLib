
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.InGameCameraObservationParams import *
from entgen.CameraSoundEvent import *

from EntityLibPy import Node

class InGameCameraData(HelperObject):
    schema_name = "InGameCameraData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InGameCameraData
        return InGameCameraData(entlib.load_node_file(sourcefile, entlib.get_schema(InGameCameraData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InGameCameraData
        return InGameCameraData(entlib.make_node(InGameCameraData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def cinematic(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("cinematic"))
    @property
    def clamber(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("clamber"))
    @property
    def crouch(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("crouch"))
    @property
    def dive(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("dive"))
    @property
    def fall(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("fall"))
    @property
    def fight(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("fight"))
    @property
    def fly(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("fly"))
    @property
    def prone(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("prone"))
    @property
    def ridden(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("ridden"))
    @property
    def riddenfly(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("riddenfly"))
    @property
    def ride(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("ride"))
    @property
    def soundEvents(self):  # type: ()->Array[CameraSoundEvent]
        return (lambda n: Array(CameraSoundEvent, n))(self._node.at("soundEvents"))
    @property
    def standup(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("standup"))
    @property
    def swim(self):  # type: ()->InGameCameraObservationParams
        return InGameCameraObservationParams(self._node.at("swim"))
    pass




