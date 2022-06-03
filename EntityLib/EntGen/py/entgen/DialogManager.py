
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class DialogManager(HelperObject):
    schema_name = "DialogManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DialogManager
        return DialogManager(entlib.load_node_file(sourcefile, entlib.get_schema(DialogManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DialogManager
        return DialogManager(entlib.make_node(DialogManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DialogFileExtension(self):  # type: ()->String
        return String(self._node.at("DialogFileExtension"))
    @DialogFileExtension.setter
    def DialogFileExtension(self, val): self.DialogFileExtension.set(val)
    @property
    def DialogsRootPath(self):  # type: ()->String
        return String(self._node.at("DialogsRootPath"))
    @DialogsRootPath.setter
    def DialogsRootPath(self, val): self.DialogsRootPath.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




