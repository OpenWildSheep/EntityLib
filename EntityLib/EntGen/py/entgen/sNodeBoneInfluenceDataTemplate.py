
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.sBoneInfluenceDataTemplate import *


class sNodeBoneInfluenceDataTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sNodeBoneInfluenceDataTemplate"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sNodeBoneInfluenceDataTemplate.schema_name))
    @property
    def Data(self): return (lambda n: Array(sBoneInfluenceDataTemplate, n))(self._node.at("Data"))
    @property
    def NodeName(self): return String(self._node.at("NodeName"))
    @NodeName.setter
    def NodeName(self, val): self.NodeName.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




