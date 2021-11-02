
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class AnalyticsObserverInterface(HelperObject):
    schema_name = "AnalyticsObserverInterface"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnalyticsObserverInterface
        return AnalyticsObserverInterface(entlib.load_node_file(sourcefile, entlib.get_schema(AnalyticsObserverInterface.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnalyticsObserverInterface
        return AnalyticsObserverInterface(entlib.make_node(AnalyticsObserverInterface.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




