
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Color import *
from entgen.Float import *
from entgen.Vector2 import *

from EntityLibPy import Node

class UIMessage(HelperObject):
    schema_name = "UIMessage"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->UIMessage
        return UIMessage(entlib.load_node_file(sourcefile, entlib.get_schema(UIMessage.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->UIMessage
        return UIMessage(entlib.make_node(UIMessage.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Color(self):  # type: ()->Color
        return Color(self._node.at("Color"))
    @Color.setter
    def Color(self, val): self.Color.set(val)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def Icon(self):  # type: ()->String
        return String(self._node.at("Icon"))
    @Icon.setter
    def Icon(self, val): self.Icon.set(val)
    @property
    def ScreenPosition(self):  # type: ()->Vector2
        return Vector2(self._node.at("ScreenPosition"))
    @ScreenPosition.setter
    def ScreenPosition(self, val): self.ScreenPosition.set(val)
    @property
    def Text(self):  # type: ()->String
        return String(self._node.at("Text"))
    @Text.setter
    def Text(self, val): self.Text.set(val)
    @property
    def TextScale(self):  # type: ()->Float
        return Float(self._node.at("TextScale"))
    @TextScale.setter
    def TextScale(self, val): self.TextScale.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




