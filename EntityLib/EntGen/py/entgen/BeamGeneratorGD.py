
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.BoneStartPoint import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *

from EntityLibPy import Node

class BeamGeneratorGD(HelperObject):
    schema_name = "BeamGeneratorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamGeneratorGD
        return BeamGeneratorGD(entlib.load_node_file(sourcefile, entlib.get_schema(BeamGeneratorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamGeneratorGD
        return BeamGeneratorGD(entlib.make_node(BeamGeneratorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BeamEffectsNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("BeamEffectsNames"))
    @BeamEffectsNames.setter
    def BeamEffectsNames(self, val): self.BeamEffectsNames.set(val)
    @property
    def BoneStartPoint(self):  # type: ()->BoneStartPoint
        return BoneStartPoint(self._node.at("BoneStartPoint"))
    @property
    def MaxBeamRange(self):  # type: ()->Float
        return Float(self._node.at("MaxBeamRange"))
    @MaxBeamRange.setter
    def MaxBeamRange(self, val): self.MaxBeamRange.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




