#include "Vector.h"

#include <ciso646>

#include "include/EntityLib.h"
#include "include/Schema.h"
#include "Tools.h"

using namespace nlohmann;

Ent::Vector::Vector(EntityLib const* _entlib, Subschema const* _schema)
    : m_entlib(_entlib)
    , m_schema(_schema)
{
}

Ent::Vector::Vector(Vector const& _other)
    : m_entlib(_other.m_entlib)
    , m_schema(_other.m_schema)
    // , m_data(_other.m_data)
    , m_arraySize(_other.m_arraySize)

{
    m_data.reserve(_other.m_data.size());
    for (auto& data : _other.m_data)
    {
        m_data.push_back(data->clone());
    }
}
Ent::Vector& Ent::Vector::operator=(Vector const& _other)
{
    if (this != &_other)
    {
        Vector tmp(_other);
        std::swap(tmp, *this);
    }
    return *this;
}

void Ent::Vector::setSize(Override<size_t> _size)
{
    m_arraySize = _size;
}

bool Ent::Vector::hasOverride() const
{
    return m_arraySize.isSet()
           || std::any_of(begin(m_data), end(m_data), std::mem_fn(&Ent::Node::hasOverride));
}

bool Ent::Vector::hasPrefabValue() const
{
    return m_arraySize.hasPrefabValue()
           || std::any_of(begin(m_data), end(m_data), std::mem_fn(&Ent::Node::hasPrefabValue));
}

Ent::Node* Ent::Vector::at(uint64_t _index)
{
    if (_index < m_data.size())
    {
        return m_data[_index].get();
    }
    else
    {
        return nullptr;
    }
}
Ent::Node const* Ent::Vector::at(uint64_t _index) const
{
    if (_index < m_data.size())
    {
        return m_data[_index].get();
    }
    else
    {
        return nullptr;
    }
}

bool Ent::Vector::isTuple() const
{
    return m_schema->linearItems.has_value();
}

std::vector<Ent::Node const*> Ent::Vector::getItems() const
{
    checkInvariants();
    std::vector<Node const*> result(m_data.size());
    std::transform(begin(m_data), end(m_data), begin(result), [](auto& n) { return n.get(); });
    return result;
}

std::vector<Ent::Node*> Ent::Vector::getItems()
{
    checkInvariants();
    std::vector<Node*> result(m_data.size());
    std::transform(begin(m_data), end(m_data), begin(result), [](auto& n) { return n.get(); });
    return result;
}

void Ent::Vector::checkInvariants() const
{
    ENTLIB_ASSERT(m_schema != nullptr);
    ENTLIB_ASSERT(m_data.size() == m_arraySize.get());
    if (m_schema->singularItems != nullptr)
    {
        auto singItem = &m_schema->singularItems->get();
        for (auto& itm : m_data)
        {
            ENTLIB_ASSERT(singItem == itm->getSchema());
        }
    }
    else
    {
        ENTLIB_ASSERT(m_data.size() == m_schema->linearItems->size());
    }
}

bool Ent::Vector::hasDefaultValue() const
{
    return std::all_of(begin(m_data), end(m_data), std::mem_fn(&Node::hasDefaultValue));
}

void Ent::Vector::pop()
{
    ENTLIB_ASSERT(not isTuple());
    ENTLIB_ASSERT(not m_data.empty());
    m_data.pop_back();
    m_arraySize.set(m_arraySize.get() - 1);
}

void Ent::Vector::clear()
{
    ENTLIB_ASSERT(not isTuple());
    m_data.clear();
    m_arraySize.set(0);
    checkInvariants();
}

Ent::Vector Ent::Vector::detach() const
{
    Vector result{getEntityLib(), m_schema};
    for (auto const& elt : m_data)
    {
        result.m_data.emplace_back(elt->detach());
    }
    result.m_arraySize = m_arraySize.detach();
    result.checkInvariants();
    return result;
}

Ent::Vector Ent::Vector::makeInstanceOf() const
{
    Vector result{getEntityLib(), m_schema};
    for (auto const& elt : m_data)
    {
        result.m_data.emplace_back(elt->makeInstanceOf());
    }
    result.m_arraySize = m_arraySize.makeInstanceOf();
    return result;
}

void Ent::Vector::computeMemory(MemoryProfiler& prof) const
{
    prof.addMem("Array::data", m_data.capacity() * sizeof(m_data.front()));
    for (auto&& item : m_data)
    {
        item->computeMemory(prof);
        prof.addMem("Array::data::value_ptr", sizeof(Ent::Node));
    }
    prof.addNodes(m_data.size());
}

tl::optional<size_t> Ent::Vector::getRawSize(OverrideValueLocation _location) const
{
    return m_arraySize.getRaw(_location);
}

Ent::Node* Ent::Vector::initPush(NodeUniquePtr _node, bool _addedInInstance)
{
    ENTLIB_ASSERT(
        m_schema->singularItems == nullptr
        || (&m_schema->singularItems->get() == _node->getSchema()));
    m_data.emplace_back(std::move(_node));
    m_arraySize.set(m_arraySize.get() + 1);
    auto node = m_data.back().get();
    node->setAddedInInsance(_addedInInstance);
    return node;
}

Ent::Node* Ent::Vector::push()
{
    SubschemaRef const* itemSchema = m_schema->singularItems.get();
    return initPush(m_entlib->loadNode(itemSchema->get(), json(), nullptr), true);
}

size_t Ent::Vector::size() const
{
    return m_arraySize.get();
}

size_t Ent::Vector::getDefaultSize() const
{
    return m_arraySize.getDefault();
}

size_t Ent::Vector::getPrefabSize() const
{
    return m_arraySize.getPrefab();
}

void Ent::Vector::unset()
{
    for (auto& elt : m_data)
    {
        elt->unset();
    }
    m_arraySize.unset();
    m_data.resize(m_arraySize.get());
}

void Ent::Vector::applyAllValues(Vector& _dest, CopyMode _copyMode) const
{
    while (_dest.size() > size())
    {
        _dest.pop();
    }
    while (size() > _dest.size())
    {
        _dest.push();
    }
    for (size_t i = 0; i < size(); ++i)
    {
        m_data[i]->applyAllValues(*_dest.m_data[i], _copyMode);
    }
}

void Ent::Vector::setParentNode(Node* _parentNode)
{
    for (auto& elt : m_data)
    {
        elt->setParentNode(_parentNode);
    }
}

void Ent::Vector::checkParent(Node const* _parentNode) const
{
    for (auto& elt : m_data)
    {
        elt->checkParent(_parentNode);
    }
}

Ent::EntityLib const* Ent::Vector::getEntityLib() const
{
    return m_entlib;
}

std::vector<Ent::NodeUniquePtr> Ent::Vector::releaseAllElements()
{
    std::vector<NodeUniquePtr> releasedElts;
    for (auto& elt : m_data)
    {
        releasedElts.push_back(std::move(elt));
    }
    clear();
    return releasedElts;
}

Ent::NodeRef Ent::Vector::computeNodeRefToChild(Node const* child) const
{
    size_t i = 0;
    for (auto& subnode : this->getItems())
    {
        if (child == subnode)
        {
            return format("%llu", i);
        }
        ++i;
    }
    ENTLIB_LOGIC_ERROR("child is not a child of this Vector");
}
