
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.Float import *
from entgen.EnergyValue import *
from entgen.String import *

from EntityLibPy import Node

class TaggingVegetation(HelperObject):
    schema_name = "TaggingVegetation"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TaggingVegetation
        return TaggingVegetation(entlib.load_node_file(sourcefile, entlib.get_schema(TaggingVegetation.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TaggingVegetation
        return TaggingVegetation(entlib.make_node(TaggingVegetation.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyValues(self):  # type: ()->PrimArray[EnergyValue]
        return (lambda n: PrimArray(EnergyValue, n))(self._node.at("EnergyValues"))
    @EnergyValues.setter
    def EnergyValues(self, val): self.EnergyValues.set(val)
    @property
    def RequiredRatio(self):  # type: ()->Float
        return Float(self._node.at("RequiredRatio"))
    @RequiredRatio.setter
    def RequiredRatio(self, val): self.RequiredRatio.set(val)
    @property
    def TaggedState(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("TaggedState"))
    @TaggedState.setter
    def TaggedState(self, val): self.TaggedState.set(val)
    @property
    def VegetationTags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("VegetationTags"))
    @VegetationTags.setter
    def VegetationTags(self, val): self.VegetationTags.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




