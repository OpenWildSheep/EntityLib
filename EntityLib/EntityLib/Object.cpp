#include "Object.h"

#include <ciso646>

#include "external/json.hpp"

#include "Tools.h"
#include "include/EntityLib.h"

using namespace nlohmann;

namespace Ent
{
    bool Object::hasDefaultValue() const
    {
        return std::all_of(nodes.begin(), nodes.end(), [](ObjField const& field) {
            return field.node->hasDefaultValue();
        });
    }

    // ************************************* Object ***********************************************

    Ent::ObjField::ObjField(ObjField const& _other)
        : name(_other.name)
        , node(_other.node->clone())
        , fieldIdx(_other.fieldIdx)

    {
    }

    ObjField& Ent::ObjField::operator=(ObjField const& _other)
    {
        if (&_other != this)
        {
            ObjField tmp(_other);
            std::swap(tmp, *this);
        }
        return *this;
    }

    void Ent::Object::unset()
    {
        for (ObjField& field : nodes)
        {
            field.node->unset();
        }
    }

    void Ent::Object::applyAllValues(Object& _dest, CopyMode _copyMode) const
    {
        applyInstanceOfField(*this, _dest, _copyMode);
        applyAllValuesButPrefab(_dest, _copyMode);
    }

    void Ent::Object::applyAllValuesButPrefab(Object& _dest, CopyMode _copyMode) const
    {
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            nodes[i].node->applyAllValues(*_dest.nodes[i].node, _copyMode);
        }
    }

    Ent::Object Ent::Object::makeInstanceOf() const
    {
        Object out(schema);
        out.hasASuper = true;
        out.instanceOf = instanceOf.makeInstanceOf();
        out.nodes.reserve(size());
        for (auto&& [name, node, fieldIdx] : *this)
        {
            out.nodes.push_back(ObjField{name, node->makeInstanceOf(), fieldIdx});
        }
        std::sort(begin(out), end(out), CompObject());
        return out;
    }

    Object Ent::Object::detach() const
    {
        Object out(schema);
        out.nodes.reserve(size());
        for (auto&& [name, node, fieldIdx] : *this)
        {
            out.nodes.emplace_back(ObjField{name, node->detach(), fieldIdx});
        }
        std::sort(begin(out), end(out), CompObject());
        return out;
    }

    void Ent::Object::resetInstanceOf(char const* _prefabNodePath)
    {
        auto const* entlib = schema->rootSchema->entityLib;
        if (_prefabNodePath == nullptr or strlen(_prefabNodePath) == 0)
        {
            auto prefabNode = entlib->loadNode(*schema, json{}, nullptr);
            (*this) = std::get<Object>(prefabNode->GetRawValue()).makeInstanceOf();
            instanceOf.set("");
        }
        else
        {
            auto relPath = entlib->getRelativePath(_prefabNodePath).generic_u8string();
            json nodeData = loadJsonFile(entlib->rawdataPath, _prefabNodePath);
            auto prefabNode = entlib->loadNode(*schema, nodeData, nullptr);
            // Get the keyfield
            NodeUniquePtr keyField;
            for (ObjField& objfield : nodes)
            {
                auto&& field = objfield.node;
                if (field->getSchema()->isKeyField)
                {
                    if (keyField != nullptr)
                    {
                        throw IllFormedSchema(
                            R"(An Object is used in two set with different keyField)");
                    }
                    keyField = field->clone();
                }
            }
            (*this) = std::get<Object>(prefabNode->GetRawValue()).makeInstanceOf();
            // Set the keyField
            if (keyField != nullptr and keyField->isSet()) // Only report the previus ID if it is set
            {
                for (ObjField& objfield : nodes)
                {
                    auto&& field = objfield.node;
                    if (field->getSchema()->isKeyField)
                    {
                        keyField->applyAllValues(*field, CopyMode::MinimalOverride);
                    }
                }
            }
            instanceOf.set(relPath);
        }
    }

    bool Object::hasOverride() const
    {
        if (instanceOf.hasOverride())
        {
            return true;
        }
        for (ObjField const& field : nodes)
        {
            if (field.node->hasOverride())
            {
                return true;
            }
        }
        return false;
    }

    bool Object::hasPrefabValue() const
    {
        if (instanceOf.hasPrefabValue())
        {
            return true;
        }
        for (ObjField const& field : nodes)
        {
            if (field.node->hasPrefabValue())
            {
                return true;
            }
        }
        return false;
    }

    void Ent::Object::setParentNode(Node* _parentNode)
    {
        for (auto&& [name, node, fieldIndex] : nodes)
        {
            node->setParentNode(_parentNode);
        }
    }

    void Ent::Object::checkParent(Node const* _parentNode) const
    {
        for (auto&& [name, node, fieldIndex] : nodes)
        {
            node->checkParent(_parentNode);
        }
    }

    void Object::computeMemory(MemoryProfiler& prof) const
    {
        prof.addMem("Object", nodes.capacity() * sizeof(front()));
        instanceOf.computeMemory(prof);
        for (ObjField const& field : nodes)
        {
            field.node->computeMemory(prof);
            prof.addMem("Object::value_ptr", sizeof(Ent::Node));
        }
        prof.addNodes(size());
    }

    NodeRef Object::computeNodeRefToChild(Node const* child) const
    {
        for (auto& field : nodes)
        {
            if (child == field.node.get())
            {
                return field.name;
            }
        }
        ENTLIB_LOGIC_ERROR("child is not a child of this Object");
    }

    size_t count(Object const& obj, char const* key)
    {
        auto range = std::equal_range(begin(obj), end(obj), ObjField{key, nullptr, 0}, CompObject());
        return (size_t)std::distance(range.first, range.second);
    }
    void emplace(Object& obj, ObjField const& value)
    {
        auto range = std::equal_range(begin(obj), end(obj), value, CompObject());
        if (range.first == range.second)
        {
            obj.nodes.insert(range.first, value);
        }
    }
    Node const& at(Object const& obj, char const* key)
    {
        return *obj.at(key).node;
    }
    Node& at(Object& obj, char const* key)
    {
        return *obj.at(key).node;
    }
} // namespace Ent
