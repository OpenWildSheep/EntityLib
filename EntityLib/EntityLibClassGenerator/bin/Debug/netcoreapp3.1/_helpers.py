MYPY = False
from typing import *
import EntityLibPy

TODO_None = None
TODO_Tuple = None
TODO_UnknownArray = None


class Field(object):
	# hack for Python 2 to get fields in declaration order (which is the default in Python > 3.5)
	_declaration_count = 0
	def __init__(self):
		self._declaration_index = Field._declaration_count
		Field._declaration_count += 1

	def setup(self, cls_chain, field_name):  # type: (List[Type], str) -> None
		self.cls_chain = cls_chain
		self.field_name = field_name


# the metaclass for EntityLibClass...
class EntityLibClassMeta(type):
	def __init__(cls, name, bases, attributes):
		def walk_tree(fields, cls_chain, cls):  # type: (List[Field], List[Type], Type) -> None
			cls_chain = list(cls_chain) # copy
			cls_chain.append(cls)

			for base in cls.__bases__:
				walk_tree(fields, cls_chain, base)

			for attr in cls.__dict__:
				field = getattr(cls, attr)
				if isinstance(field, Field):
					fields.append(field)
					field.setup(cls_chain, attr)

		fields = []  # type: List[Field]
		cls_chain = []  # type: List[Type]
		walk_tree(fields, cls_chain, cls)
		fields.sort(key=lambda f: f._declaration_index)
		cls.__fields__ = fields


T = TypeVar("T")

class BaseNode(Field, Generic[T]):
	def __init__(self, node_type, node_name):  # type: (Type[T], str) -> None
		Field.__init__(self)
		self.node_type = node_type
		self.node_name = node_name

	def get_node(self, obj):  # type: (EntityLibClass, Type) -> EntityLibPy.Node
		node = obj._node
		for cls in self.cls_chain[1:]:
			node = node.at(cls.__name__)
		node = node.at(self.node_name)
		return node


class ValueNode(BaseNode, Generic[T]):
	def __get__(self, obj, cls):  # type: (EntityLibClass, Type) -> T
		if not obj: return self  # quering the class field itself -> bypass the getter
		node = self.get_node(obj)
		return node.value

	def __set__(self, obj, value):  # type: (EntityLibClass, T) -> None
		node = self.get_node(obj)
		node.value = self.node_type(value)


class ValueArrayNode(BaseNode, Generic[T]):
	def __get__(self, obj, cls):  # type: (EntityLibClass, Type) -> Iterable[T]
		if not obj: return self  # quering the class field itself -> bypass the getter
		node = self.get_node(obj)
		return tuple(e.value for e in node.get_items())

	def __set__(self, obj, values):  # type: (EntityLibClass, Iterable[T]) -> None
		node = self.get_node(obj)
		node.clear()
		for value in values:
			item = node.push()
			item.value = value


# TupleNode is a special case of ValueArrayNode: functionaly identical,
# but for type hinting purposes we want to declare them with their typedef alias
#	eg: TupleNode(Vector3) instead of ValueArrayNode(float)
if MYPY:
	TTuple = TypeVar("TTuple", bound=Tuple)
	class TupleNode(BaseNode, Generic[TTuple]):
		def __get__(self, obj, cls):  # type: (EntityLibClass, Type) -> TTuple
			pass
		def __set__(self, obj, values):  # type: (EntityLibClass, TTuple) -> None
			pass
else:
	TupleNode = ValueArrayNode


class RefNode(BaseNode, Generic[T]):
	def __get__(self, obj, cls):  # type: (EntityLibClass, Type) -> T
		if not obj: return self  # quering the class field itself -> bypass the getter
		node = self.get_node(obj)
		return self.node_type(node)


class RefArrayNode(BaseNode, Generic[T]):
	if MYPY: # reclare __init__ to massage the type hinting system...
		def __init__(self, node_type, node_name):  # type: (Type[T], str) -> None
			pass

	def __get__(self, obj, cls):  # type: (EntityLibClass, Type) -> Instance[T]
		if not obj: return self  # quering the class field itself -> bypass the getter
		node = self.get_node(obj)
		return RefArrayNode.Instance(self.node_type, node)

	class Instance(Generic[T]):
		def __init__(self, node_type, node):  # type: (Type[T], EntityLibPy.Node) -> None
			self.node_type = node_type
			self.node = node

		def clear(self):  # type: () -> None
			self.node.clear()

		def push(self):  # type: () -> T
			item = self.node.push()
			return self.node_type(item)

		def __getitem__(self, index):  # type: (int) -> T
			item = self.node.get_items()[index]
			return self.node_type(item)



class EntityLibClass(object):
	__metaclass__ = EntityLibClassMeta
	__fields__ = None  # type: List[BaseNode]

	def __init__(self,
		node_or_component_or_entity # type: Union[EntityLibPy.Node, EntityLibPy.Component, EntityLibPy.Entity]
	):
		if isinstance(node_or_component_or_entity, EntityLibPy.Entity):
			node = node_or_component_or_entity.get_component("<#= type.name #>").root
		elif isinstance(node_or_component_or_entity, EntityLibPy.Component):
			node = node_or_component_or_entity.root
		else:
			node = node_or_component_or_entity
		self._node = node  # type: EntityLibPy.Node
