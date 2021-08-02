#include "Union.h"

#include <ciso646>

#include "external/json.hpp"

#include "include/EntityLib.h"

using namespace nlohmann;

namespace Ent
{

    bool Union::hasOverride() const
    {
        return wrapper->hasOverride();
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
            ENTLIB_ASSERT_MSG(
                not typeNode->hasDefaultValue(),
                "In Union, the type-field (%s) is expected to be set",
                metaData->typeField.c_str());
            return typeNode->getString();
        }
        else
        {
            return nullptr;
        }
    }

    Node* Union::setUnionType(EntityLib const& _entlib, char const* _type)
    {
        if (getUnionType() != _type)
        {
            Subschema const* subTypeSchema{};
            std::tie(subTypeSchema, typeIndex) = schema->getUnionTypeWrapper(_type);
            // TODO : Loïc - low prio - Find a way to get the super.
            //   It could be hard because we are no more in the loading phase, so the super is
            //   now delete.
            wrapper = _entlib.loadNode(*subTypeSchema, json(), nullptr);
            wrapper->at(metaData->typeField.c_str())->setString(_type);
        }
        return getUnionData();
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
        wrapper->unset();
        Subschema const* subTypeSchema{};
        std::tie(subTypeSchema, typeIndex) = schema->getUnionTypeWrapper(getUnionType());
    }

    void Union::applyAllValues(Union& _dest, CopyMode _copyMode) const
    {
        if (typeIndex != _dest.typeIndex)
        {
            _dest.setUnionType(*wrapper->getEntityLib(), getUnionType());
        }
        wrapper->applyAllValues(*_dest.wrapper, _copyMode);
    }

    Union Union::detach() const
    {
        Union detUnion{};
        detUnion.schema = schema;
        detUnion.wrapper = wrapper->detach();
        detUnion.metaData = metaData;
        detUnion.typeIndex = typeIndex;
        return detUnion;
    }

    Union Union::makeInstanceOf() const
    {
        Union detUnion{};
        ENTLIB_ASSERT(schema != nullptr);
        detUnion.schema = schema;
        if (wrapper != nullptr)
        {
            detUnion.wrapper = wrapper->makeInstanceOf();
        }
        detUnion.metaData = metaData;
        detUnion.typeIndex = typeIndex;
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
