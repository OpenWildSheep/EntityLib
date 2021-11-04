
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.PickableDistributorComponentData import *

from EntityLibPy import Node

class PickableDistributorComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PickableDistributorComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PickableDistributorComponentGD
        return PickableDistributorComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(PickableDistributorComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PickableDistributorComponentGD
        return PickableDistributorComponentGD(entlib.make_node(PickableDistributorComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PickableGrowingTime(self):  # type: ()->Float
        return Float(self._node.at("PickableGrowingTime"))
    @PickableGrowingTime.setter
    def PickableGrowingTime(self, val): self.PickableGrowingTime.set(val)
    @property
    def PickablePickedUpCooldownTime(self):  # type: ()->Float
        return Float(self._node.at("PickablePickedUpCooldownTime"))
    @PickablePickedUpCooldownTime.setter
    def PickablePickedUpCooldownTime(self, val): self.PickablePickedUpCooldownTime.set(val)
    @property
    def PickablesList(self):  # type: ()->Array[PickableDistributorComponentData]
        return (lambda n: Array(PickableDistributorComponentData, n))(self._node.at("PickablesList"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




