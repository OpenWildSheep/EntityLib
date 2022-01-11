
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.sEnvStamp import *
from entgen.EnergySide import *

from EntityLibPy import Node

class EnvStampGD(HelperObject):
    schema_name = "EnvStampGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnvStampGD
        return EnvStampGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnvStampGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnvStampGD
        return EnvStampGD(entlib.make_node(EnvStampGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RegenStateChangeDuration(self):  # type: ()->Float
        return Float(self._node.at("RegenStateChangeDuration"))
    @RegenStateChangeDuration.setter
    def RegenStateChangeDuration(self, val): self.RegenStateChangeDuration.set(val)
    @property
    def Stamps(self):  # type: ()->Map[EnergySideEnum, Array[sEnvStamp]]
        return (lambda n: Map(EnergySideEnum, (lambda n: Array(sEnvStamp, n)), n))(self._node.at("Stamps"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




