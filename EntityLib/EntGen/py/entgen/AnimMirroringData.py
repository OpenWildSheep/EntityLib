
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnimMirroringSpecData import *

from EntityLibPy import Node

class AnimMirroringData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimMirroringData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimMirroringData
        return AnimMirroringData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimMirroringData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimMirroringData
        return AnimMirroringData(entlib.make_node(AnimMirroringData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def specs(self):  # type: ()->Array[AnimMirroringSpecData]
        return (lambda n: Array(AnimMirroringSpecData, n))(self._node.at("specs"))
    pass




