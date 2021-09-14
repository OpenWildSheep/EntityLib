from typing import TypeVar, Generic, Tuple, Type, Callable, Any
from enum import Enum
import EntityLibPy
import inspect

MYPY = False

TODO_None = None
TODO_Tuple = None
TODO_UnknownArray = None


T = TypeVar("T")


class Base(object):
    def __init__(self, node):
        self._node = node  # type: EntityLibPy.Node

    def __bool__(self):
        return self._node is not Node

    def __nonzero__(self):
        return self._node is not Node
    
    @property
    def node(self):
        return self._node

    @property
    def is_null(self):
        return self._node is None

    @property
    def is_set(self):
        return self._node.is_set()

    def unset(self):
        return self._node.unset()

    @property
    def is_default(self):
        return self._node.is_default()

    @property
    def has_default_value(self):
        return self._node.has_default_value()


class Primitive(Base, Generic[T]):
    def __init__(self, item_type, node=None):  # type: (Type[T], EntityLibPy.Node) -> None
        super(Primitive, self).__init__(node)
        self._item_type = item_type

    @property
    def value(self):  # type: () -> T
        return self.get()

    @value.setter
    def value(self, val):  # type: (T) -> None
        self.set(val)

    def get(self):  # type: () -> T
        return self._item_type(self._node.value)

    def is_set(self):  # type: (...) -> bool
        return self._node.is_set()

    def unset(self):
        return self._node.unset()


class Float(Primitive[float]):
    def __init__(self, node):
        super(Float, self).__init__(float, node)

    def set(self, val):  # type: (float) -> None
        return self._node.set_float(val)


class Int(Primitive[int]):
    def __init__(self, node):
        super(Int, self).__init__(int, node)

    def set(self, val):  # type: (int) -> None
        return self._node.set_int(val)


class Bool(Primitive[bool]):
    def __init__(self, node):
        super(Bool, self).__init__(bool, node)

    def set(self, val):  # type: (bool) -> None
        return self._node.set_bool(val)


class String(Primitive[str]):
    def __init__(self, node):
        super(String, self).__init__(str, node)

    def set(self, val):  # type: (str) -> None
        return self._node.set_string(val)

    def __str__(self):
        return self._node.value


class EntityRef(Primitive[EntityLibPy.EntityRef]):
    def __init__(self, node):
        super(EntityRef, self).__init__(EntityLibPy.EntityRef, node)

    def set(self, val):  # type: (EntityLibPy.EntityRef) -> None
        return self._node.set_entityref(val)


TComponent = TypeVar("TComponent")


class UnionSet(Base):
    def get(self, key_type):  # type: (Type[TComponent]) -> TComponent
        typename = key_type.__name__
        union = self._node.map_get(typename)
        if union is None:
            return None
        else:
            return key_type(union.get_union_data())

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
    def __init__(self, item_ctor, node=None):  # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super(Array, self).__init__(node)
        self._item_ctor = item_ctor

    def __getitem__(self, idx):  # type: (int) -> T
        return self._item_ctor(self._node.at(idx))

    def __len__(self):
        return self._node.size()

    def push(self):
        return self._item_ctor(self._node.push())

    def pop(self):
        return self._node.pop()

    def clean(self):
        return self._node.clean()


class PrimArray(Array[T], Generic[T]):
    def set(self, values):  # type: (List[T]) -> None
        for i in range(self._node.size()):
            self._node.at(i).value = values[i]

    @property
    def value(self):  # type: (...) -> List[T]
        return [self._node.at(i).value for i in range(self._node.size())]

    @value.setter
    def value(self, values):  # type: (List[T]) -> None
        self.set(values)

    def __setitem__(self, idx, value):  # type: (int, ...) -> None
        self._node.at(idx).value = value


class ObjectSet(Base, Generic[T]):
    def __init__(self, item_ctor, node=None):  # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super(ObjectSet, self).__init__(node)
        self._item_ctor = item_ctor

    def get(self, key):  # type: (...) -> T
        return self._item_ctor(self._node.map_get(key))

    def add(self, key):  # type: (...) -> T
        return self._item_ctor(self._node.map_insert(key))

    def remove(self, key):
        self._node.map_erase(key)

    def clean(self):
        return self._node.clean()

    def __getitem__(self, key):  # type: (...) -> T
        return self._item_ctor(self._node.map_get(key))

    def __len__(self):
        return self._node.size()

    def __iter__(self):
        for item in self._node.get_items():
            yield self._item_ctor(item)


K = TypeVar("K")
V = TypeVar("V")


class Map(Base, Generic[K, V]):
    def __init__(self, key_type, item_ctor, node=None):  # type: (Type[K], Callable[[Any], V], EntityLibPy.Node) -> None
        super(Map, self).__init__(node)
        self._key_type = key_type
        self._item_ctor = item_ctor

    @staticmethod
    def to_internal(key):  # type : (T) -> T
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

    def clean(self):
        return self._node.clean()

    def __getitem__(self, key):     # type: (K) -> V
        return self._item_ctor(self._node.map_get(self.to_internal(key)))

    def __len__(self):
        return self._node.size()

    def get_keys(self):  # type: () -> [K]
        return self._node.get_keys()

    def __iter__(self):
        for key in self._node.get_keys():
            yield (key, self.get(key))


class PrimitiveSet(Base, Generic[T]):
    def __init__(self, item_ctor, node=None):  # type: (Callable[[Any], T], EntityLibPy.Node) -> None
        super(PrimitiveSet, self).__init__(node)
        self._item_ctor = item_ctor

    @staticmethod
    def to_internal(key):  # type : (T) -> T
        if issubclass(type(key), Enum):
            return key.value
        else:
            return key

    def add(self, key):  # type: (T) -> None
        assert type(key) == self._item_ctor
        self._node.map_insert(self.to_internal(key))

    def count(self, key):  # type: (T) -> bool
        return self._node.map_get(self.to_internal(key)) is not None

    def __iter__(self):
        for item in self._node.get_items():
            yield self._item_ctor(item.value)

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
    def __init__(self, typelist, node=None):  # type: (TTuple, EntityLibPy.Node) -> None
        super(TupleNode, self).__init__(node)
        self.typelist = typelist

    def __getitem__(self, key):
        return self.typelist[key](self._node.at(key))

    def __setitem__(self, key, value):
        self._node.at(key).value = value

    def __len__(self):
        return self._node.size()


class HelperObject(Base):
    def save(self, dest_file):
        self._node.save_node(dest_file)
