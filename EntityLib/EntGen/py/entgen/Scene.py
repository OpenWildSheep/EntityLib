
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Entity import *


class Scene(HelperObject):
    schema_name = "./Scene-schema.json#/definitions/Scene"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(Scene.schema_name))
    @property
    def Objects(self): return (lambda n: ObjectSet(Entity, n))(self._node.at("Objects"))
    @property
    def Version(self): return Int(self._node.at("Version"))
    @Version.setter
    def Version(self, val): self.Version.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




