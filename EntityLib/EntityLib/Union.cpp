#include "Union.h"

#include <ciso646>

#include "external/json.hpp"

#include "include/EntityLib.h"
#include "Tools.h"

using namespace nlohmann;

namespace Ent
{
    Union::Union(
        EntityLib const* _entityLib,
        Subschema const* _schema,
        NodeUniquePtr _wrapper,
        size_t _typeIndex,
        Override<String> _instanceOf)
        : entityLib(_entityLib)
        , schema(_schema)
        , typeIndex(_typeIndex)
        , wrapper(std::move(_wrapper))
        , metaData(&(std::get<Subschema::UnionMeta>(schema->meta)))
        , instanceOf(std::move(_instanceOf))
    {
        auto const* typeNode = wrapper->at(metaData->typeField.c_str());
        typeOverriden = typeNode->hasOverride();
    }

    Union::Union(Union const& _other)
        : entityLib(_other.entityLib)
        , schema(_other.schema)
        , typeIndex(_other.typeIndex)
        , wrapper(_other.wrapper->clone())
        , metaData(_other.metaData)
        , instanceOf(_other.instanceOf)
    {
    }

    Union& Union::operator=(Union const& _other)
    {
        Union tmp(_other);
        std::swap(*this, tmp);
        return *this;
    }

    bool Union::hasOverride() const
    {
        return typeOverriden or wrapper->hasOverride() or instanceOf.hasOverride();
    }

    bool Union::hasDefaultValue() const
    {
        return wrapper->hasDefaultValue() and instanceOf.hasDefaultValue();
    }

    Node* Union::getUnionData()
    {
        return wrapper->at(metaData->dataField.c_str());
    }

    Node const* Union::getUnionData() const
    {
        if (wrapper != nullptr)
        {
            return wrapper->at(metaData->dataField.c_str());
        }
        return nullptr;
    }

    char const* Union::getUnionType() const
    {
        if (wrapper != nullptr)
        {
            ENTLIB_ASSERT_MSG(
                wrapper->count(metaData->typeField.c_str()),
                "Field %s not found in union",
                metaData->typeField.c_str());
            auto* const typeNode = wrapper->at(metaData->typeField.c_str());
            ENTLIB_ASSERT(typeNode);
            return typeNode->getString();
        }
        return nullptr;
    }

    Node* Union::resetUnionTypeWithoutOverride(char const* _type)
    {
        Subschema const* subTypeSchema{};
        std::tie(subTypeSchema, typeIndex) = schema->getUnionTypeWrapper(_type);
        // TODO(lolo): Loïc - low prio - Find a way to get the super.
        //   It could be hard because we are no more in the loading phase, so the super is
        //   now delete.
        Node* unionNode = wrapper->getParentNode();
        if (unionNode != nullptr)
        {
            Node* parrentNode = unionNode->getParentNode();
            if (parrentNode != nullptr and parrentNode->getSchema()->type == DataType::array)
            {
                auto const& meta = std::get<Subschema::ArrayMeta>(parrentNode->getSchema()->meta);
                if (meta.overridePolicy == "set")
                {
                    throw BadType("Can't change union type inside a set of union");
                }
            }
        }
        wrapper = entityLib->loadNode(*subTypeSchema, json(), nullptr);
        wrapper->setParentNode(unionNode);
        typeOverriden = false;
        return getUnionData();
    }

    Node* Union::setUnionType(char const* _type)
    {
        if (_type == nullptr)
        {
            throw NullPointerArgument("_type", "Union::setUnionType");
        }
        auto const* const unionType = getUnionType();
        if (unionType == nullptr or strcmp(_type, unionType) != 0)
        {
            auto* unionData = resetUnionTypeWithoutOverride(_type);
            typeOverriden = true;
            wrapper->at(schema->getUnionNameField())->setString(_type);
            return unionData;
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
        Union detUnion{entityLib, schema, wrapper->detach(), typeIndex, {}};
        detUnion.typeOverriden = true;
        return detUnion;
    }

    Union Union::makeInstanceOf() const
    {
        ENTLIB_ASSERT(schema != nullptr);
        ENTLIB_ASSERT(wrapper != nullptr);
        Union detUnion{
            entityLib, schema, wrapper->makeInstanceOf(), typeIndex, instanceOf.makeInstanceOf()};
        detUnion.typeOverriden = false;
        return detUnion;
    }

    bool Union::hasPrefabValue() const
    {
        return wrapper->hasPrefabValue() or instanceOf.hasPrefabValue();
    }

    void Union::setParentNode(Node* _parentNode) const
    {
        wrapper->setParentNode(_parentNode);
    }

    void Union::checkParent(Node const* _parentNode) const
    {
        wrapper->checkParent(_parentNode);
    }

    std::unique_ptr<Union> Union::clone() const
    {
        return std::make_unique<Union>(entityLib, schema, wrapper->clone(), typeIndex, instanceOf);
    }

    NodeRef Union::computeNodeRefToChild(Node const* _child) const
    {
        ENTLIB_ASSERT(getUnionData() == _child);
        return getUnionType();
    }

    void Union::resetInstanceOf(char const* _prefabNodePath)
    {
        auto const* entlib = schema->rootSchema->entityLib;
        if (_prefabNodePath == nullptr or strlen(_prefabNodePath) == 0)
        {
            auto const prefabNode = entlib->loadNode(*schema, json{}, nullptr);
            (*this) = std::get<UnionPtr>(prefabNode->GetRawValue())->makeInstanceOf();
            instanceOf.set("");
        }
        else
        {
            auto const relPath = entlib->getRelativePath(_prefabNodePath).generic_u8string();
            json const nodeData = loadJsonFile(entlib->rawdataPath, _prefabNodePath);
            auto const prefabNode = entlib->loadNode(*schema, nodeData, nullptr);
            (*this) = std::get<UnionPtr>(prefabNode->GetRawValue())->makeInstanceOf();
            instanceOf.set(relPath);
        }
    }
} // namespace Ent
