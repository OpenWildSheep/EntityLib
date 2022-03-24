
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Float import *

from EntityLibPy import Node

class ImpactAndSolidityData(HelperObject):
    schema_name = "ImpactAndSolidityData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ImpactAndSolidityData
        return ImpactAndSolidityData(entlib.load_node_file(sourcefile, entlib.get_schema(ImpactAndSolidityData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ImpactAndSolidityData
        return ImpactAndSolidityData(entlib.make_node(ImpactAndSolidityData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def impactPercent(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("impactPercent"))
    @impactPercent.setter
    def impactPercent(self, val): self.impactPercent.set(val)
    @property
    def solidity(self):  # type: ()->Float
        return Float(self._node.at("solidity"))
    @solidity.setter
    def solidity(self, val): self.solidity.set(val)
    @property
    def unbreakable(self):  # type: ()->Bool
        return Bool(self._node.at("unbreakable"))
    @unbreakable.setter
    def unbreakable(self, val): self.unbreakable.set(val)
    @property
    def velocityImpactMax(self):  # type: ()->Float
        return Float(self._node.at("velocityImpactMax"))
    @velocityImpactMax.setter
    def velocityImpactMax(self, val): self.velocityImpactMax.set(val)
    pass




