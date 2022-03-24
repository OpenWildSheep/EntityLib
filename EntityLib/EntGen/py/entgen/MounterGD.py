
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class MounterGD(HelperObject):
    schema_name = "MounterGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MounterGD
        return MounterGD(entlib.load_node_file(sourcefile, entlib.get_schema(MounterGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MounterGD
        return MounterGD(entlib.make_node(MounterGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotName(self):  # type: ()->String
        return String(self._node.at("HotspotName"))
    @HotspotName.setter
    def HotspotName(self, val): self.HotspotName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




