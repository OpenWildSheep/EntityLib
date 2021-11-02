
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ResponsiblePointer_AnalyticsObserverInterface_(HelperObject):
    schema_name = "ResponsiblePointer&lt;AnalyticsObserverInterface&gt;"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ResponsiblePointer_AnalyticsObserverInterface_
        return ResponsiblePointer_AnalyticsObserverInterface_(entlib.load_node_file(sourcefile, entlib.get_schema(ResponsiblePointer_AnalyticsObserverInterface_.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ResponsiblePointer_AnalyticsObserverInterface_
        return ResponsiblePointer_AnalyticsObserverInterface_(entlib.make_node(ResponsiblePointer_AnalyticsObserverInterface_.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




