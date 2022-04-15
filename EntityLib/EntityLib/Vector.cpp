#include "Vector.h"

#include <ciso646>

#include "include/EntityLib.h"
#include "include/Schema.h"
#include "Tools.h"

using namespace nlohmann;

namespace Ent
{

    Vector::Vector(EntityLib const* _entlib, Subschema const* _schema)
        : m_entlib(_entlib)
        , m_schema(_schema)
    {
    }

    Vector::Vector(Vector const& _other)
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
    Vector& Vector::operator=(Vector const& _other)
    {
        if (this != &_other)
        {
            Vector tmp(_other);
            std::swap(tmp, *this);
        }
        return *this;
    }

    void Vector::setSize(Override<size_t> _size)
    {
        m_arraySize = _size;
    }

    bool Vector::hasOverride() const
    {
        return m_arraySize.isSet()
               || std::any_of(begin(m_data), end(m_data), std::mem_fn(&Node::hasOverride));
    }

    bool Vector::hasPrefabValue() const
    {
        return m_arraySize.hasPrefabValue()
               || std::any_of(begin(m_data), end(m_data), std::mem_fn(&Node::hasPrefabValue));
    }

    Node* Vector::at(uint64_t _index)
    {
        if (_index < m_data.size())
        {
            return m_data[_index].get();
        }
        return nullptr;
    }
    Node const* Vector::at(uint64_t _index) const
    {
        if (_index < m_data.size())
        {
            return m_data[_index].get();
        }
        return nullptr;
    }

    bool Vector::isTuple() const
    {
        return m_schema->linearItems.has_value();
    }

    std::vector<Node const*> Vector::getItems() const
    {
        checkInvariants();
        std::vector<Node const*> result(m_data.size());
        std::transform(begin(m_data), end(m_data), begin(result), [](auto& n) { return n.get(); });
        return result;
    }

    std::vector<Node*> Vector::getItems()
    {
        checkInvariants();
        std::vector<Node*> result(m_data.size());
        std::transform(begin(m_data), end(m_data), begin(result), [](auto& n) { return n.get(); });
        return result;
    }

    void Vector::checkInvariants() const
    {
        ENTLIB_ASSERT(m_schema != nullptr);
        ENTLIB_ASSERT(m_data.size() == m_arraySize.get());
        if (m_schema->singularItems != nullptr)
        {
            auto const singItem = &m_schema->singularItems->get();
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

    bool Vector::hasDefaultValue() const
    {
        return std::all_of(begin(m_data), end(m_data), std::mem_fn(&Node::hasDefaultValue));
    }

    void Vector::pop()
    {
        ENTLIB_ASSERT(not isTuple());
        ENTLIB_ASSERT(not m_data.empty());
        m_data.pop_back();
        m_arraySize.set(m_arraySize.get() - 1);
    }

    void Vector::clear()
    {
        ENTLIB_ASSERT(not isTuple());
        m_data.clear();
        m_arraySize.set(0);
        checkInvariants();
    }

    Vector Vector::detach() const
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

    Vector Vector::makeInstanceOf() const
    {
        Vector result{getEntityLib(), m_schema};
        for (auto const& elt : m_data)
        {
            result.m_data.emplace_back(elt->makeInstanceOf());
        }
        result.m_arraySize = m_arraySize.makeInstanceOf();
        return result;
    }

    void Vector::computeMemory(MemoryProfiler& prof) const
    {
        prof.addMem("Array::data", m_data.capacity() * sizeof(m_data.front()));
        for (auto&& item : m_data)
        {
            item->computeMemory(prof);
            prof.addMem("Array::data::value_ptr", sizeof(Node));
        }
        prof.addNodes(m_data.size());
    }

    std::optional<size_t> Vector::getRawSize(OverrideValueLocation _location) const
    {
        return m_arraySize.getRaw(_location);
    }

    Node* Vector::initPush(NodeUniquePtr _node, bool _addedInInstance)
    {
        ENTLIB_ASSERT(
            m_schema->singularItems == nullptr
            || (&m_schema->singularItems->get() == _node->getSchema()));
        m_data.emplace_back(std::move(_node));
        m_arraySize.set(m_arraySize.get() + 1);
        auto const node = m_data.back().get();
        node->setAddedInInsance(_addedInInstance);
        return node;
    }

    Node* Vector::push()
    {
        SubschemaRef const* itemSchema = m_schema->singularItems.get();
        return initPush(m_entlib->loadNode(itemSchema->get(), json(), nullptr), true);
    }

    size_t Vector::size() const
    {
        return m_arraySize.get();
    }

    size_t Vector::getDefaultSize() const
    {
        return m_arraySize.getDefault();
    }

    size_t Vector::getPrefabSize() const
    {
        return m_arraySize.getPrefab();
    }

    void Vector::unset()
    {
        for (auto const& elt : m_data)
        {
            elt->unset();
        }
        m_arraySize.unset();
        m_data.resize(m_arraySize.get());
    }

    void Vector::applyAllValues(Vector& _dest, CopyMode _copyMode) const
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

    void Vector::setParentNode(Node* _parentNode) const
    {
        for (auto const& elt : m_data)
        {
            elt->setParentNode(_parentNode);
        }
    }

    void Vector::checkParent(Node const* _parentNode) const
    {
        for (auto& elt : m_data)
        {
            elt->checkParent(_parentNode);
        }
    }

    EntityLib const* Vector::getEntityLib() const
    {
        return m_entlib;
    }

    std::vector<NodeUniquePtr> Vector::releaseAllElements()
    {
        std::vector<NodeUniquePtr> releasedElts;
        for (auto& elt : m_data)
        {
            releasedElts.push_back(std::move(elt));
        }
        clear();
        return releasedElts;
    }

    NodeRef Vector::computeNodeRefToChild(Node const* _child) const
    {
        size_t i = 0;
        for (auto const& subnode : this->getItems())
        {
            if (_child == subnode)
            {
                return format("%llu", i);
            }
            ++i;
        }
        ENTLIB_LOGIC_ERROR("_child is not a child of this Vector");
    }

} // namespace Ent
