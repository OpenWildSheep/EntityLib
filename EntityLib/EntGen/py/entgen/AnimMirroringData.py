
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnimMirroringSpecData import *


class AnimMirroringData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimMirroringData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimMirroringData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def specs(self): return (lambda n: Array(AnimMirroringSpecData, n))(self._node.at("specs"))
    pass




