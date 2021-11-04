
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *

from EntityLibPy import Node

class EnergyCrookGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyCrookGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyCrookGD
        return EnergyCrookGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyCrookGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyCrookGD
        return EnergyCrookGD(entlib.make_node(EnergyCrookGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FatherEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("FatherEntityRef"))
    @FatherEntityRef.setter
    def FatherEntityRef(self, val): self.FatherEntityRef.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def RegenScale(self):  # type: ()->Float
        return Float(self._node.at("RegenScale"))
    @RegenScale.setter
    def RegenScale(self, val): self.RegenScale.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




