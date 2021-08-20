MYPY = False
from typing import TypeVar, Generic, Tuple, Type, Callable, Any
from enum import Enum
import EntityLibPy
import inspect

TODO_None = None
TODO_Tuple = None
TODO_UnknownArray = None


T = TypeVar("T")


class Base(object):
    def __init__(self, node):
        self._node = node  # type: EntityLibPy.Node

    @property
    def node(self):
        return self._node


class Primitive(Base, Generic[T]):
    def __init__(self, item_type, node = None):  # type: (Type[T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_type = item_type

    def __call__(self, node):  # type: (EntityLibPy.Node) -> Primitive[T]
        return Primitive(self._item_type, node)

    @property
    def value(self):  # type: () -> T
        return self.get()

    @value.setter
    def value(self, val):  # type: (T) -> None
        self.set(val)

    def get(self):  # type: () -> T
        return self._item_type(self._node.value)

    def is_set(self): # type: (...) -> bool
        return self._node.is_set()

    def unset(self):
        return self._node.unset()


class Float(Primitive[float]):
    def __init__(self, node):
        super().__init__(float, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Float
        return Float(node)
    def set(self, val):  # type: (float) -> None
        return self._node.set_float(val)


class Int(Primitive[int]):
    def __init__(self, node):
        super().__init__(int, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Int
        return Int(node)
    def set(self, val):  # type: (int) -> None
        return self._node.set_int(val)


class Bool(Primitive[bool]):
    def __init__(self, node):
        super().__init__(bool, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Bool
        return Bool(node)
    def set(self, val):  # type: (bool) -> None
        return self._node.set_bool(val)


class String(Primitive[str]):
    def __init__(self, node):
        super().__init__(str, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> String
        return String(node)
    def set(self, val):  # type: (str) -> None
        return self._node.set_string(val)


class EntityRef(Primitive[EntityLibPy.EntityRef]):
    def __init__(self, node):
        super().__init__(EntityLibPy.EntityRef, node)
    def __call__(self, node):  # type: (EntityLibPy.Node) -> EntityRef
        return EntityRef(node)
    def set(self, val):  # type: (EntityLibPy.EntityRef) -> None
        return self._node.set_entityref(val)


TComponent = TypeVar("TComponent")

class UnionSet(Base):
    def get(self, key_type):  # type: (Type[TComponent]) -> TComponent
        typename = key_type.__name__
        return key_type(self._node.map_get(typename).get_union_data())

    def add(self, key_type):  # type: (Type[TComponent]) -> TComponent
        typename = key_type.__name__
        return key_type(self._node.map_insert(typename).get_union_data())


class Union(Base):
    @property
    def type(self):
        return self._node.get_union_type()

    @property
    def data(self):
        return self._node.get_union_data()


class Array(Base, Generic[T]):
    def __init__(self, item_ctor, node = None):  # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_ctor = item_ctor

    def __call__(self, node):  # type: (...) -> ArrayClass[T]
       return  ArrayClass(self._item_ctor, node)

    def __getitem__(self, idx: int):
        return self._item_ctor(self._node.at(idx))

    def __len__(self):
        return self._node.size()


class ObjectSet(Base, Generic[T]):
    def __init__(self, item_ctor, node = None): # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_ctor = item_ctor

    def __call__(self, node):  # type: (...) -> ObjectSetClass[T]
       return  ObjectSet(self._item_ctor, node)

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


K = TypeVar("K")
V = TypeVar("V")

class Map(Base, Generic[K, V]):
    def __init__(self, key_type, item_ctor, node = None):  # type: (Type[K], Callable[[Any], V], EntityLibPy.Node) -> None
        super().__init__(node)
        self._key_type = key_type
        self._item_ctor = item_ctor

    def __call__(self, node):       # type: (...) -> MapClass[K, V]
       return  Map(self._item_ctor, node)

    def to_internal(self, key):  # type : (T) -> T
        if issubclass(type(key), Enum):
            return key.value
        else:
            return key

    def get(self, key):             # type: (K) -> V
        return self._item_ctor(self._node.map_get(self.to_internal(key)))

    def add(self, key):
        assert type(key) == self._key_type
        return self._item_ctor(self._node.map_insert(self.to_internal(key)))

    def remove(self, key):          # type: (K) -> None
        self._node.map_erase(self.to_internal(key))

    def __getitem__(self, key):     # type: (K) -> V
        return self._item_ctor(self._node.map_get(self.to_internal(key)))

    def __len__(self):
        return self._node.size()


class PrimitiveSet(Base, Generic[T]):
    def __init__(self, item_ctor, node = None):  # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super().__init__(node)
        self._item_ctor = item_ctor

    def __call__(self, node):  # type: (...) -> PrimitiveSetClass[T]
       return  PrimitiveSet(self._item_ctor, node)

    def to_internal(self, key):  # type : (T) -> T
        if issubclass(type(key), Enum):
            return key.value
        else:
            return key

    def add(self, key):  # type: (T) -> None
        assert type(key) == self._item_ctor
        self._node.map_insert(self.to_internal(key))

    def count(self, key):  # type: (T) -> bool
        return self._node.map_get(self.to_internal(key)) is not None

    # def remove(self, key):
    #    self._node.map_erase(key)

    def __len__(self):
        return self._node.size()

    # def erase(self, key):
    #     self._node.map_erase(key)

    # def __del__(self, key):
    #     self._node.map_erase(key)


TTuple = TypeVar("TTuple", bound=Tuple)
class TupleNode(Base, Generic[TTuple]):
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
