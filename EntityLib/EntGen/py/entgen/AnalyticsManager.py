
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnalyticsManager_MongoDBConnection import *
from entgen.Bool import *
from entgen.Manager import *
from entgen.ResponsiblePointer_AnalyticsObserverInterface_ import *

from EntityLibPy import Node

class AnalyticsManager(HelperObject):
    schema_name = "AnalyticsManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnalyticsManager
        return AnalyticsManager(entlib.load_node_file(sourcefile, entlib.get_schema(AnalyticsManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnalyticsManager
        return AnalyticsManager(entlib.make_node(AnalyticsManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnableAnalyticsTeleportation(self):  # type: ()->Bool
        return Bool(self._node.at("EnableAnalyticsTeleportation"))
    @EnableAnalyticsTeleportation.setter
    def EnableAnalyticsTeleportation(self, val): self.EnableAnalyticsTeleportation.set(val)
    @property
    def EnableEventLogger(self):  # type: ()->Bool
        return Bool(self._node.at("EnableEventLogger"))
    @EnableEventLogger.setter
    def EnableEventLogger(self, val): self.EnableEventLogger.set(val)
    @property
    def MongoDBConnection(self):  # type: ()->AnalyticsManager_MongoDBConnection
        return AnalyticsManager_MongoDBConnection(self._node.at("MongoDBConnection"))
    @property
    def Plugins(self):  # type: ()->Array[ResponsiblePointer_AnalyticsObserverInterface_]
        return (lambda n: Array(ResponsiblePointer_AnalyticsObserverInterface_, n))(self._node.at("Plugins"))
    @property
    def StartPaused(self):  # type: ()->Bool
        return Bool(self._node.at("StartPaused"))
    @StartPaused.setter
    def StartPaused(self, val): self.StartPaused.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




