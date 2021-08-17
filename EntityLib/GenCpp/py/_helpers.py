MYPY = False
from typing import TypeVar, Generic, Tuple, Type, Callable, Any
import EntityLibPy
import inspect

TODO_None = None
TODO_Tuple = None
TODO_UnknownArray = None


T = TypeVar("T")

class Field(Generic[T]):
    def __init__(self, node_ctor, node_name):  # type: (Callable[[Any], T], str) -> None
        self.node_name = node_name
        self.node_ctor = node_ctor

    def get_node(self, obj):  # type: (EntityLibClass) -> EntityLibPy.Node
        return obj._node.at(self.node_name)

    def __get__(self, obj, cls):  # type: (...) -> T
        # if not obj: return None  # quering the class field itself -> bypass the getter
        return self.node_ctor(self.get_node(obj))


class EntityLibClass(object):
    def __init__(self, node):
        self._node = node  # type: EntityLibPy.Node


class Primitive(EntityLibClass, Generic[T]):
    def __init__(self, item_type, node = None):  # type: (Type[T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_type = item_type

    def __call__(self, node):  # type: (EntityLibPy.Node) -> Primitive[T]
        return Primitive(self._item_type, node)

    @property
    def value(self):  # type: () -> T
        return self._item_type(self._node.value)

    def is_set(self): # type: (...) -> bool
        return self._node.is_set()

    def unset(self):
        return self._node.unset()

"""
Float = Primitive[float]
make_Float = lambda n: Primitive(float, n)
Int = Primitive[int]
make_Int = lambda n: Primitive(int, n)
Bool = Primitive[bool]
make_Bool = lambda n: Primitive(bool, n)
String = Primitive[str]
make_String = lambda n: Primitive(str, n)
EntityRef = Primitive[EntityLibPy.EntityRef]
make_EntityRef = lambda n: Primitive(EntityLibPy.EntityRef, n)
"""



class Float(Primitive[float]):
    def __init__(self, node):
        super().__init__(float, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Float
        return Float(node)


class Int(Primitive[int]):
    def __init__(self, node):
        super().__init__(int, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Int
        return Int(node)


class Bool(Primitive[bool]):
    def __init__(self, node):
        super().__init__(bool, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Bool
        return Bool(node)


class String(Primitive[str]):
    def __init__(self, node):
        super().__init__(str, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> String
        return String(node)


class EntityRef(Primitive[EntityLibPy.EntityRef]):
    def __init__(self, node):
        super().__init__(EntityLibPy.EntityRef, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> EntityRef
        return EntityRef(node)


TComponent = TypeVar("TComponent")

class UnionSetClass(EntityLibClass):
    def get(self, key_type):  # type: (Type[TComponent]) -> TComponent
        typename = key_type.__name__
        return key_type(self._node.map_get(typename).get_union_data())

    def add(self, key_type):  # type: (Type[TComponent]) -> TComponent
        typename = key_type.__name__
        return key_type(self._node.map_insert(typename).get_union_data())


class UnionClass(EntityLibClass):
    @property
    def type(self):
        return self._node.get_union_type()

    @property
    def data(self):
        return self._node.get_union_data()


class ArrayClass(EntityLibClass, Generic[T]):
    def __init__(self, item_ctor, node = None):  # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_ctor = item_ctor

    def __call__(self, node):  # type: (...) -> ArrayClass[T]
       return  ArrayClass(self._item_ctor, node)

    def __getitem__(self, idx: int):
        return self._item_ctor(self._node.at(idx))

    def __len__(self):
        return self._node.size()


class ObjectSetClass(EntityLibClass, Generic[T]):
    def __init__(self, item_ctor, node = None): # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_ctor = item_ctor

    def __call__(self, node):  # type: (...) -> ObjectSetClass[T]
       return  ObjectSetClass(self._item_ctor, node)

    def get(self, key): # type: (...) -> T
        return self._item_ctor(self._node.map_get(key))

    def add(self, key): # type: (...) -> T
        return self._item_ctor(self._node.map_insert(key))

    def remove(self, key):
        self._node.map_erase(key)

    def __getitem__(self, key): # type: (...) -> T
        return self._item_ctor(self._node.map_get(key))

    def __len__(self):
        return self._node.size()


class MapClass(EntityLibClass, Generic[T]):
    def __init__(self, item_ctor, node = None):  # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_ctor = item_ctor

    def __call__(self, node):  # type: (...) -> MapClass[T]
       return  MapClass(self._item_ctor, node)

    def get(self, key):
        return self._item_ctor(self._node.map_get(key))

    def add(self, key):
        return self._item_ctor(self._node.map_insert(key))

    def remove(self, key):
        self._node.map_erase(key)

    def __getitem__(self, key):
        return self._item_ctor(self._node.map_get(key))

    def __len__(self):
        return self._node.size()


class PrimitiveSetClass(EntityLibClass, Generic[T]):
    def __init__(self, item_ctor, node = None):  # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_ctor = item_ctor

    def __call__(self, node):  # type: (...) -> PrimitiveSetClass[T]
       return  PrimitiveSetClass(self._item_ctor, node)

    def get(self, key):  # type: (...) -> T
        return self._item_ctor(self._node.map_get(key))

    def add(self, key):  # type: (...) -> T
        return self._item_ctor(self._node.map_insert(key))

    # def remove(self, key):
    #    self._node.map_erase(key)

    def __getitem__(self, key):  # type: (...) -> T
        return self._item_ctor(self._node.map_get(key))

    def __len__(self):
        return self._node.size()

    # def erase(self, key):
    #     self._node.map_erase(key)

    # def __del__(self, key):
    #     self._node.map_erase(key)


TTuple = TypeVar("TTuple", bound=Tuple)
class TupleClass(EntityLibClass, Generic[TTuple]):
    def __init__(self, typelist, node = None): # type: (TTuple, EntityLibPy.Node) -> None
        super().__init__(node)
        self.typelist = typelist
    """
    def __call__(self, node):  # type: (EntityLibPy.Node) -> TupleClass[TTuple]
       return  TupleClass(self.typelist, node)
    """
    def __getitem__(self, key):
        return self.typelist[key](self._node.at(key))

    def __len__(self):
        return self._node.size()
