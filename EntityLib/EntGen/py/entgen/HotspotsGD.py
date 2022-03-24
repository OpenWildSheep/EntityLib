
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.HotspotData import *
from entgen.String import *

from EntityLibPy import Node

class HotspotsGD(HelperObject):
    schema_name = "HotspotsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HotspotsGD
        return HotspotsGD(entlib.load_node_file(sourcefile, entlib.get_schema(HotspotsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HotspotsGD
        return HotspotsGD(entlib.make_node(HotspotsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotsMap(self):  # type: ()->Map[str, HotspotData]
        return (lambda n: Map(str, HotspotData, n))(self._node.at("HotspotsMap"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




