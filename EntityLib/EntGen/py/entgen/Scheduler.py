
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class Scheduler(HelperObject):
    schema_name = "Scheduler"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Scheduler
        return Scheduler(entlib.load_node_file(sourcefile, entlib.get_schema(Scheduler.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Scheduler
        return Scheduler(entlib.make_node(Scheduler.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




