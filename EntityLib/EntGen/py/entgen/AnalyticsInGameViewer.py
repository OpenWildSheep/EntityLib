
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class AnalyticsInGameViewer(HelperObject):
    schema_name = "AnalyticsInGameViewer"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnalyticsInGameViewer
        return AnalyticsInGameViewer(entlib.load_node_file(sourcefile, entlib.get_schema(AnalyticsInGameViewer.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnalyticsInGameViewer
        return AnalyticsInGameViewer(entlib.make_node(AnalyticsInGameViewer.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




