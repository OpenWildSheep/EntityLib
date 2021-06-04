#include "Vector.h"

#include <ciso646>

#include "include/EntityLib.h"
#include "include/Schema.h"
#include "Tools.h"

using namespace nlohmann;

bool Ent::Vector::hasOverride() const
{
    return arraySize.isSet()
           || std::any_of(begin(data), end(data), std::mem_fn(&Ent::Node::hasOverride));
}

bool Ent::Vector::hasPrefabValue() const
{
    return arraySize.hasPrefab
           || std::any_of(begin(data), end(data), std::mem_fn(&Ent::Node::hasPrefabValue));
}

Ent::Node* Ent::Vector::at(uint64_t _index)
{
    if (_index < data.size())
    {
        return data[_index].get();
    }
    else
    {
        return nullptr;
    }
}
Ent::Node const* Ent::Vector::at(uint64_t _index) const
{
    if (_index < data.size())
    {
        return data[_index].get();
    }
    else
    {
        return nullptr;
    }
}

bool Ent::Vector::isTuple() const
{
    return schema->linearItems.has_value();
}

std::vector<Ent::Node const*> Ent::Vector::getItems() const
{
    checkInvariants();
    std::vector<Node const*> result;
    result.reserve(data.size());
    for (auto&& node : data)
    {
        result.emplace_back(node.get());
    }
    return result;
}

void Ent::Vector::checkInvariants() const
{
    ENTLIB_ASSERT(schema != nullptr);
    ENTLIB_ASSERT(data.size() == arraySize.get());
    if (schema->singularItems != nullptr)
    {
        auto singItem = &schema->singularItems->get();
        for (auto& itm : data)
        {
            ENTLIB_ASSERT(singItem == itm->getSchema());
        }
    }
    else
    {
        ENTLIB_ASSERT(data.size() == schema->linearItems->size());
    }
}

bool Ent::Vector::hasDefaultValue() const
{
    return std::all_of(begin(data), end(data), std::mem_fn(&Node::hasDefaultValue));
}

void Ent::Vector::pop()
{
    ENTLIB_ASSERT(not isTuple());
    ENTLIB_ASSERT(not data.empty());
    data.pop_back();
    arraySize.set(arraySize.get() - 1);
}

void Ent::Vector::clear()
{
    ENTLIB_ASSERT(not isTuple());
    data.clear();
    arraySize.set(0);
    checkInvariants();
}

Ent::Vector Ent::Vector::detach() const
{
    Vector result{nullptr, schema};
    for (auto const elt : data)
    {
        result.data.emplace_back(elt->detach());
    }
    result.arraySize = arraySize.detach();
    result.checkInvariants();
    return result;
}

Ent::Vector Ent::Vector::makeInstanceOf() const
{
    Vector result{nullptr, schema};
    for (auto const elt : data)
    {
        result.data.emplace_back(elt->makeInstanceOf());
    }
    result.arraySize = arraySize.makeInstanceOf();
    return result;
}

void Ent::Vector::computeMemory(MemoryProfiler& prof) const
{
    prof.addMem("Array::data", data.capacity() * sizeof(data.front()));
    for (auto&& item : data)
    {
        item->computeMemory(prof);
        prof.addMem("Array::data::value_ptr", sizeof(Ent::Node));
    }
    prof.addNodes(data.size());
}

tl::optional<size_t> Ent::Vector::getRawSize(OverrideValueLocation _location) const
{
    return arraySize.getRaw(_location);
}

Ent::Node* Ent::Vector::initPush(Node _node)
{
    ENTLIB_ASSERT(
        schema->singularItems == nullptr || (&schema->singularItems->get() == _node.getSchema()));
    data.emplace_back(Ent::make_value<Node>(std::move(_node)));
    arraySize.set(arraySize.get() + 1);
    return data.back().get();
}

Ent::Node* Ent::Vector::push()
{
    SubschemaRef const* itemSchema = schema->singularItems.get();
    return initPush(entlib->loadNode(itemSchema->get(), json(), nullptr));
}
