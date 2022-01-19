
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class AnalyticsManager_MongoDBConnection(HelperObject):
    schema_name = "AnalyticsManager::MongoDBConnection"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnalyticsManager_MongoDBConnection
        return AnalyticsManager_MongoDBConnection(entlib.load_node_file(sourcefile, entlib.get_schema(AnalyticsManager_MongoDBConnection.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnalyticsManager_MongoDBConnection
        return AnalyticsManager_MongoDBConnection(entlib.make_node(AnalyticsManager_MongoDBConnection.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def collection(self):  # type: ()->String
        return String(self._node.at("collection"))
    @collection.setter
    def collection(self, val): self.collection.set(val)
    @property
    def database(self):  # type: ()->String
        return String(self._node.at("database"))
    @database.setter
    def database(self, val): self.database.set(val)
    @property
    def uri(self):  # type: ()->String
        return String(self._node.at("uri"))
    @uri.setter
    def uri(self, val): self.uri.set(val)
    pass




