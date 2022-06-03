
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class RevivedData(HelperObject):
    schema_name = "RevivedData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RevivedData
        return RevivedData(entlib.load_node_file(sourcefile, entlib.get_schema(RevivedData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RevivedData
        return RevivedData(entlib.make_node(RevivedData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NonCreatureConvertRatio(self):  # type: ()->Float
        return Float(self._node.at("NonCreatureConvertRatio"))
    @NonCreatureConvertRatio.setter
    def NonCreatureConvertRatio(self, val): self.NonCreatureConvertRatio.set(val)
    @property
    def ReviveSinAmplitude(self):  # type: ()->Float
        return Float(self._node.at("ReviveSinAmplitude"))
    @ReviveSinAmplitude.setter
    def ReviveSinAmplitude(self, val): self.ReviveSinAmplitude.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




