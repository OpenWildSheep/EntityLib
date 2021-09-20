#include "Union.h"

#include <ciso646>

#include "external/json.hpp"

#include "include/EntityLib.h"

using namespace nlohmann;

namespace Ent
{
    Union::Union(EntityLib const* _entityLib, Subschema const* _schema, Node&& _wrapper, size_t _typeIndex)
        : entityLib(_entityLib)
        , schema(_schema)
        , typeIndex(_typeIndex)
        , wrapper(make_value<Node>(_wrapper))
        , metaData(&(schema->meta.get<Subschema::UnionMeta>()))
    {
        auto* typeNode = wrapper->at(metaData->typeField.c_str());
        typeOverriden = typeNode->hasOverride();
    }

    bool Union::hasOverride() const
    {
        return typeOverriden or wrapper->hasOverride();
    }

    bool Union::hasDefaultValue() const
    {
        return wrapper->hasDefaultValue();
    }

    Node* Union::getUnionData()
    {
        return wrapper->at(metaData->dataField.c_str());
    }

    Node const* Union::getUnionData() const
    {
        if (wrapper.has_value())
        {
            return wrapper->at(metaData->dataField.c_str());
        }
        else
        {
            return nullptr;
        }
    }

    char const* Union::getUnionType() const
    {
        if (wrapper.has_value())
        {
            ENTLIB_ASSERT_MSG(
                wrapper->count(metaData->typeField.c_str()),
                "Field %s not found in union",
                metaData->typeField.c_str());
            auto typeNode = wrapper->at(metaData->typeField.c_str());
            ENTLIB_ASSERT(typeNode);
            return typeNode->getString();
        }
        else
        {
            return nullptr;
        }
    }

    Node* Union::resetUnionTypeWithoutOverride(char const* _type)
    {
        Subschema const* subTypeSchema{};
        std::tie(subTypeSchema, typeIndex) = schema->getUnionTypeWrapper(_type);
        // TODO : Loïc - low prio - Find a way to get the super.
        //   It could be hard because we are no more in the loading phase, so the super is
        //   now delete.
        wrapper = entityLib->loadNode(*subTypeSchema, json(), nullptr);
        typeOverriden = false;
        return getUnionData();
    }

    Node* Union::setUnionType(char const* _type)
    {
        if (_type == nullptr)
        {
            throw NullPointerArgument("_type", "Union::setUnionType");
        }
        auto unionType = getUnionType();
        if (unionType == nullptr or strcmp(_type, unionType) != 0)
        {
            auto* unionData = resetUnionTypeWithoutOverride(_type);
            typeOverriden = true;
            wrapper->at(schema->getUnionNameField())->setString(_type);
            return unionData;
        }
        else
        {
            return getUnionData();
        }
    }

    void Union::computeMemory(MemoryProfiler& prof) const
    {
        prof.currentComp.push_back(getUnionType());
        if (wrapper)
        {
            wrapper->computeMemory(prof);
            prof.addMem("Union::wrapper", sizeof(Node));
        }
        prof.currentComp.pop_back();
    }

    void Union::unset()
    {
        resetUnionTypeWithoutOverride(schema->getUnionDefaultTypeName());
    }

    void Union::applyAllValues(Union& _dest, CopyMode _copyMode) const
    {
        if (typeIndex != _dest.typeIndex)
        {
            _dest.setUnionType(getUnionType());
        }
        wrapper->applyAllValues(*_dest.wrapper, _copyMode);
    }

    Union Union::detach() const
    {
        Union detUnion{entityLib, schema, wrapper->detach(), typeIndex};
        detUnion.typeOverriden = true;
        return detUnion;
    }

    Union Union::makeInstanceOf() const
    {
        ENTLIB_ASSERT(schema != nullptr);
        ENTLIB_ASSERT(wrapper != nullptr);
        Union detUnion{entityLib, schema, wrapper->makeInstanceOf(), typeIndex};
        detUnion.typeOverriden = false;
        return detUnion;
    }

    bool Union::hasPrefabValue() const
    {
        return wrapper->hasPrefabValue();
    }

    void Ent::Union::setParentNode(Node* _parentNode)
    {
        wrapper->setParentNode(_parentNode);
    }

    void Ent::Union::checkParent(Node const* _parentNode) const
    {
        wrapper->checkParent(_parentNode);
    }

} // namespace Ent
