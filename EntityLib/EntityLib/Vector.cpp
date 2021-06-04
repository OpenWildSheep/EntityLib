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
    return m_arraySize.hasPrefab
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
    std::vector<Node const*> result;
    result.reserve(m_data.size());
    for (auto&& node : m_data)
    {
        result.emplace_back(node.get());
    }
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
    Vector result{nullptr, m_schema};
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
    Vector result{nullptr, m_schema};
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

Ent::Node* Ent::Vector::initPush(Node _node)
{
    ENTLIB_ASSERT(
        m_schema->singularItems == nullptr || (&m_schema->singularItems->get() == _node.getSchema()));
    m_data.emplace_back(Ent::make_value<Node>(std::move(_node)));
    m_arraySize.set(m_arraySize.get() + 1);
    return m_data.back().get();
}

Ent::Node* Ent::Vector::push()
{
    SubschemaRef const* itemSchema = m_schema->singularItems.get();
    return initPush(m_entlib->loadNode(itemSchema->get(), json(), nullptr));
}

size_t Ent::Vector::size() const
{
    return m_arraySize.get();
}

size_t Ent::Vector::getDefaultSize() const
{
    return m_arraySize.defaultValue;
}

size_t Ent::Vector::getPrefabSize() const
{
    return m_arraySize.getPrefab();
}
