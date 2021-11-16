
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Color import *
from entgen.Float import *

from EntityLibPy import Node

class OnlineDebugger_BandwidthWindow_BandwithLimit(HelperObject):
    schema_name = "OnlineDebugger::BandwidthWindow::BandwithLimit"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OnlineDebugger_BandwidthWindow_BandwithLimit
        return OnlineDebugger_BandwidthWindow_BandwithLimit(entlib.load_node_file(sourcefile, entlib.get_schema(OnlineDebugger_BandwidthWindow_BandwithLimit.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OnlineDebugger_BandwidthWindow_BandwithLimit
        return OnlineDebugger_BandwidthWindow_BandwithLimit(entlib.make_node(OnlineDebugger_BandwidthWindow_BandwithLimit.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def color(self):  # type: ()->Color
        return Color(self._node.at("color"))
    @color.setter
    def color(self, val): self.color.set(val)
    @property
    def limit(self):  # type: ()->Float
        return Float(self._node.at("limit"))
    @limit.setter
    def limit(self, val): self.limit.set(val)
    pass




