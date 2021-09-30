
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *


class EnergyCrookGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyCrookGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EnergyCrookGD.schema_name))
    @property
    def FatherEntityRef(self): return EntityRef(self._node.at("FatherEntityRef"))
    @FatherEntityRef.setter
    def FatherEntityRef(self, val): self.FatherEntityRef.set(val)
    @property
    def Radius(self): return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def RegenScale(self): return Float(self._node.at("RegenScale"))
    @RegenScale.setter
    def RegenScale(self, val): self.RegenScale.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




