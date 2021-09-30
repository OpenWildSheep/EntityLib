
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.PickableDistributorComponentData import *


class PickableDistributorComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PickableDistributorComponentGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PickableDistributorComponentGD.schema_name))
    @property
    def PickableGrowingTime(self): return Float(self._node.at("PickableGrowingTime"))
    @PickableGrowingTime.setter
    def PickableGrowingTime(self, val): self.PickableGrowingTime.set(val)
    @property
    def PickablePickedUpCooldownTime(self): return Float(self._node.at("PickablePickedUpCooldownTime"))
    @PickablePickedUpCooldownTime.setter
    def PickablePickedUpCooldownTime(self, val): self.PickablePickedUpCooldownTime.set(val)
    @property
    def PickablesList(self): return (lambda n: Array(PickableDistributorComponentData, n))(self._node.at("PickablesList"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




