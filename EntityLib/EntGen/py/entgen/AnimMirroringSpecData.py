
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *


class AnimMirroringSpecData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimMirroringSpecData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimMirroringSpecData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def name(self): return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    @property
    def name2(self): return String(self._node.at("name2"))
    @name2.setter
    def name2(self, val): self.name2.set(val)
    @property
    def spec(self): return String(self._node.at("spec"))
    @spec.setter
    def spec(self, val): self.spec.set(val)
    pass




