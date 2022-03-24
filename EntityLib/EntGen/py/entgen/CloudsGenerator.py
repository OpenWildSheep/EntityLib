
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class CloudsGenerator(HelperObject):
    schema_name = "CloudsGenerator"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CloudsGenerator
        return CloudsGenerator(entlib.load_node_file(sourcefile, entlib.get_schema(CloudsGenerator.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CloudsGenerator
        return CloudsGenerator(entlib.make_node(CloudsGenerator.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ApearanceDuration(self):  # type: ()->Float
        return Float(self._node.at("ApearanceDuration"))
    @ApearanceDuration.setter
    def ApearanceDuration(self, val): self.ApearanceDuration.set(val)
    @property
    def ApearanceDurationRandom(self):  # type: ()->Float
        return Float(self._node.at("ApearanceDurationRandom"))
    @ApearanceDurationRandom.setter
    def ApearanceDurationRandom(self, val): self.ApearanceDurationRandom.set(val)
    @property
    def CloudSize(self):  # type: ()->Float
        return Float(self._node.at("CloudSize"))
    @CloudSize.setter
    def CloudSize(self, val): self.CloudSize.set(val)
    @property
    def CloudSizeRandom(self):  # type: ()->Float
        return Float(self._node.at("CloudSizeRandom"))
    @CloudSizeRandom.setter
    def CloudSizeRandom(self, val): self.CloudSizeRandom.set(val)
    @property
    def CloudSpeedMultiplier(self):  # type: ()->Float
        return Float(self._node.at("CloudSpeedMultiplier"))
    @CloudSpeedMultiplier.setter
    def CloudSpeedMultiplier(self, val): self.CloudSpeedMultiplier.set(val)
    @property
    def CloudStrength(self):  # type: ()->Float
        return Float(self._node.at("CloudStrength"))
    @CloudStrength.setter
    def CloudStrength(self, val): self.CloudStrength.set(val)
    @property
    def CloudsCoverageDensity(self):  # type: ()->Float
        return Float(self._node.at("CloudsCoverageDensity"))
    @CloudsCoverageDensity.setter
    def CloudsCoverageDensity(self, val): self.CloudsCoverageDensity.set(val)
    @property
    def DisapearanceDuration(self):  # type: ()->Float
        return Float(self._node.at("DisapearanceDuration"))
    @DisapearanceDuration.setter
    def DisapearanceDuration(self, val): self.DisapearanceDuration.set(val)
    @property
    def DisapearanceDurationRandom(self):  # type: ()->Float
        return Float(self._node.at("DisapearanceDurationRandom"))
    @DisapearanceDurationRandom.setter
    def DisapearanceDurationRandom(self, val): self.DisapearanceDurationRandom.set(val)
    @property
    def LifeDuration(self):  # type: ()->Float
        return Float(self._node.at("LifeDuration"))
    @LifeDuration.setter
    def LifeDuration(self, val): self.LifeDuration.set(val)
    @property
    def LifeDurationRandom(self):  # type: ()->Float
        return Float(self._node.at("LifeDurationRandom"))
    @LifeDurationRandom.setter
    def LifeDurationRandom(self, val): self.LifeDurationRandom.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




