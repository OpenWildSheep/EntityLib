
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class AnimMirroringSpecData(HelperObject):
    schema_name = "AnimMirroringSpecData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimMirroringSpecData
        return AnimMirroringSpecData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimMirroringSpecData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimMirroringSpecData
        return AnimMirroringSpecData(entlib.make_node(AnimMirroringSpecData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    @property
    def name2(self):  # type: ()->String
        return String(self._node.at("name2"))
    @name2.setter
    def name2(self, val): self.name2.set(val)
    @property
    def spec(self):  # type: ()->String
        return String(self._node.at("spec"))
    @spec.setter
    def spec(self, val): self.spec.set(val)
    pass




