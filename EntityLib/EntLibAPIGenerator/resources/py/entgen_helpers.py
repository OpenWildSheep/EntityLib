from typing import TypeVar, Generic, Tuple, Type, Callable, Any, Iterable
from enum import Enum
import EntityLibPy
import inspect

MYPY = False

TODO_None = None
TODO_Tuple = None
TODO_UnknownArray = None

T = TypeVar("T")


class Base(object):
    def __init__(self, node):  # type: (EntityLibPy.Node) -> None
        assert isinstance(node, EntityLibPy.Node)
        self._node = node  # type: EntityLibPy.Node

    @property
    def node(self):
        return self._node

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

    @property
    def has_override(self):
        return self._node.has_override()


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


TComponent = TypeVar("TComponent")


class UnionSet(Base, Generic[T]):
    def __init__(self, union_type, node=None):  # type: (Type[T], EntityLibPy.Node) -> None
        super(UnionSet, self).__init__(node)
        self._union_type = union_type

    def get_by_name(self, key_type):  # type: (str) -> EntityLibPy.Node
        union = self._node.map_get(key_type)
        if union is None:
            return None
        else:
            return union.get_union_data()

    def get(self, key_type):  # type: (Type[TComponent]) -> TComponent
        typename = key_type.__name__
        union = self._node.map_get(typename)
        if union is None:
            return None
        else:
            return key_type(union.get_union_data())

    def erase(self, key_type):  # type: (Type[TComponent]) -> None
        typename = key_type.__name__
        self._node.map_erase(typename)

    def add(self, key_type):  # type: (Type[TComponent]) -> TComponent
        typename = key_type.__name__
        return key_type(self._node.map_insert(typename).get_union_data())

    def clear(self):
        return self._node.clear()

    def empty(self):
        return self._node.empty()

    def __len__(self):
        return self._node.size()

    def size(self):
        return self._node.size()

    def keys(self):
        return self._node.get_keys()

    def __iter__(self):   # type: () -> Iterator[EntityLibPy.Node]
        for item in self._node.get_items():
            yield item.get_union_data()


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

    def empty(self):
        return self._node.empty()

    def __len__(self):
        return self._node.size()

    def size(self):
        return self._node.size()

    def push(self):
        return self._item_ctor(self._node.push())

    def pop(self):
        return self._node.pop()

    def clear(self):
        return self._node.clear()

    def __iter__(self):  # type: () -> Iterator[T]
        for item in self._node.get_items():
            yield self._item_ctor(item)		


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

    def clear(self):
        return self._node.clear()

    def __getitem__(self, key):  # type: (...) -> T
        return self._item_ctor(self._node.map_get(key))

    def empty(self):
        return self._node.empty()

    def __len__(self):
        return self._node.size()

    def size(self):
        return self._node.size()

    def __iter__(self):
        for item in self._node.get_items():
            yield self._item_ctor(item)

    def insert_instanceof(self, instance_path):
        return self._item_ctor(self._node.map_insert_instanceof(instance_path))

    def keys(self):
        return self._node.get_keys()


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

    def get(self, key):  # type: (K) -> V
        node = self._node.map_get(self.to_internal(key))
        return None if node is None else self._item_ctor(node)

    def add(self, key):
        assert type(key) == self._key_type
        return self._item_ctor(self._node.map_insert(self.to_internal(key)))

    def remove(self, key):  # type: (K) -> None
        self._node.map_erase(self.to_internal(key))

    def clear(self):
        return self._node.clear()

    def __getitem__(self, key):  # type: (K) -> V
        node = self._node.map_get(self.to_internal(key))
        return None if node is None else self._item_ctor(node)

    def empty(self):
        return self._node.empty()

    def __len__(self):
        return self._node.size()

    def size(self):
        return self._node.size()

    def keys(self):  # type: () -> Array[K]
        return [self._key_type(kv.at(0).value) for kv in self._node.get_items()]

    def __iter__(self):  # type: () -> Iterator[Tuple[K, V]]
        for key_value_node in self._node.get_items():
            yield (self._key_type(key_value_node.at(0).value), self._item_ctor(key_value_node.at(1)))  # (K, V)


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

    def empty(self):
        return self._node.empty()

    def __len__(self):
        return self._node.size()

    def size(self):
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

    def size(self):
        return self._node.size()



class HelperObject(Base):
    def save(self, dest_file):
        self._node.save_node(dest_file)

    def get_instance_of(self):  # type: () -> str
        return self._node.get_instance_of()

    def reset_instance_of(self, path):  # type: (str) -> None
        self._node.reset_instance_of(path)

    def change_instance_of(self, path):  # type: (str) -> None
        self._node.change_instance_of(path)

    def make_instance_of(self):
        return self.__class__(self._node.make_instance_of())

    def has_override(self):
        return self._node.has_override()
