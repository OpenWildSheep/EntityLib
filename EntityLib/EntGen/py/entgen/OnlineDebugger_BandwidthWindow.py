
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.OnlineDebugger_BandwidthWindow_BandwithLimit import *

from EntityLibPy import Node

class OnlineDebugger_BandwidthWindow(HelperObject):
    schema_name = "OnlineDebugger::BandwidthWindow"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OnlineDebugger_BandwidthWindow
        return OnlineDebugger_BandwidthWindow(entlib.load_node_file(sourcefile, entlib.get_schema(OnlineDebugger_BandwidthWindow.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OnlineDebugger_BandwidthWindow
        return OnlineDebugger_BandwidthWindow(entlib.make_node(OnlineDebugger_BandwidthWindow.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DownColor(self):  # type: ()->Array[OnlineDebugger_BandwidthWindow_BandwithLimit]
        return (lambda n: Array(OnlineDebugger_BandwidthWindow_BandwithLimit, n))(self._node.at("DownColor"))
    @property
    def Enabled(self):  # type: ()->Bool
        return Bool(self._node.at("Enabled"))
    @Enabled.setter
    def Enabled(self, val): self.Enabled.set(val)
    @property
    def UpColor(self):  # type: ()->Array[OnlineDebugger_BandwidthWindow_BandwithLimit]
        return (lambda n: Array(OnlineDebugger_BandwidthWindow_BandwithLimit, n))(self._node.at("UpColor"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




