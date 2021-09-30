
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.sEnvStamp import *
from entgen.RegenerationState import *


class EnvStampGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnvStampGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EnvStampGD.schema_name))
    @property
    def RegenStateChangeDuration(self): return Float(self._node.at("RegenStateChangeDuration"))
    @RegenStateChangeDuration.setter
    def RegenStateChangeDuration(self, val): self.RegenStateChangeDuration.set(val)
    @property
    def Stamps(self): return (lambda n: Map(RegenerationStateEnum, (lambda n: Array(sEnvStamp, n)), n))(self._node.at("Stamps"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




