
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class SceneConverter_StreamingOptions(HelperObject):
    schema_name = "SceneConverter::StreamingOptions"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SceneConverter_StreamingOptions
        return SceneConverter_StreamingOptions(entlib.load_node_file(sourcefile, entlib.get_schema(SceneConverter_StreamingOptions.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SceneConverter_StreamingOptions
        return SceneConverter_StreamingOptions(entlib.make_node(SceneConverter_StreamingOptions.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ExportStreamingEntities(self):  # type: ()->Bool
        return Bool(self._node.at("ExportStreamingEntities"))
    @ExportStreamingEntities.setter
    def ExportStreamingEntities(self, val): self.ExportStreamingEntities.set(val)
    @property
    def StreamingUnitMaxLength(self):  # type: ()->Float
        return Float(self._node.at("StreamingUnitMaxLength"))
    @StreamingUnitMaxLength.setter
    def StreamingUnitMaxLength(self, val): self.StreamingUnitMaxLength.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




