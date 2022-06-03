
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ import *
from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class GameInfoDB(HelperObject):
    schema_name = "GameInfoDB"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameInfoDB
        return GameInfoDB(entlib.load_node_file(sourcefile, entlib.get_schema(GameInfoDB.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameInfoDB
        return GameInfoDB(entlib.make_node(GameInfoDB.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Store(self):  # type: ()->Map[str, Map[str, variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_]]
        return (lambda n: Map(str, (lambda n: Map(str, variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_, n)), n))(self._node.at("Store"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




