#include "include/EntityLib/Visitor.h"

namespace Ent
{
    RecursiveVisitor::RecursiveVisitor() = default;
    RecursiveVisitor ::~RecursiveVisitor() = default;

    void visitRecursive(Property const& _expl, RecursiveVisitor& _visitor)
    {
        switch (_expl.getDataType())
        {
        case DataType::object:
        {
            _visitor.inObject(_expl);
            for (auto&& [name, schemaref] : _expl.getSchema()->properties)
            {
                auto field = _expl.getObjectField(name.c_str(), &schemaref);
                if (_visitor.inObjectField(field, name.c_str()))
                {
                    visitRecursive(field, _visitor);
                    _visitor.outObjectField(field, name.c_str());
                }
            }
            _visitor.outObject(_expl);
            break;
        }
        case DataType::oneOf:
        {
            _visitor.inUnion(_expl, _expl.getUnionType());
            auto data = _expl.getUnionData();
            visitRecursive(data, _visitor);
            _visitor.outUnion(_expl);
            break;
        }
        case DataType::array:
        {
            auto meta = std::get<Subschema::ArrayMeta>(_expl.getSchema()->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                _visitor.inMap(_expl);
                switch (_expl.getMapKeyType())
                {
                case DataType::entityRef: [[fallthrough]];
                case DataType::string:
                    for (char const* key : _expl.getMapKeysString())
                    {
                        auto value = _expl.getMapItem(key);
                        ENTLIB_ASSERT(value.has_value());
                        _visitor.inMapElement(*value, key);
                        visitRecursive(*value, _visitor);
                        _visitor.outMapElement(*value);
                    }
                    break;
                case DataType::integer:
                    for (int64_t const key : _expl.getMapKeysInt())
                    {
                        auto value = *_expl.getMapItem(key);
                        _visitor.inMapElement(value, key);
                        visitRecursive(value, _visitor);
                        _visitor.outMapElement(value);
                    }
                    break;
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                _visitor.outMap(_expl);
                break;
            case "set"_hash:
            {
                auto& itemType = _expl.getSchema()->singularItems->get();
                switch (itemType.type)
                {
                case DataType::integer:
                    _visitor.inPrimSet(_expl, itemType.type);
                    for (int64_t const key : _expl.getPrimSetKeysInt())
                    {
                        _visitor.key(_expl, key);
                    }
                    _visitor.outPrimSet(_expl);
                    break;
                case DataType::entityRef: [[fallthrough]];
                case DataType::string:
                    _visitor.inPrimSet(_expl, itemType.type);
                    for (char const* key : _expl.getPrimSetKeysString())
                    {
                        _visitor.key(_expl, key);
                    }
                    _visitor.outPrimSet(_expl);
                    break;
                case DataType::oneOf:
                    _visitor.inUnionSet(_expl);
                    for (auto&& [name, schema] : _expl.getUnionSetKeysString())
                    {
                        auto data = _expl.getUnionSetItem(name, schema);
                        _visitor.inUnionSetElement(*data, name);
                        visitRecursive(*data, _visitor);
                        _visitor.outUnionSetElement(*data);
                    }
                    _visitor.outUnionSet(_expl);
                    break;
                case DataType::object:
                    _visitor.inObjectSet(_expl);
                    auto const& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case DataType::entityRef: [[fallthrough]];
                    case DataType::string:
                        for (auto&& key : _expl.getObjectSetKeysString())
                        {
                            auto data = *_expl.getObjectSetItem(key);
                            _visitor.inObjectSetElement(data, key);
                            visitRecursive(data, _visitor);
                            _visitor.outObjectSetElement(data);
                        }
                        break;
                    case DataType::integer:
                        for (auto&& key : _expl.getObjectSetKeysInt())
                        {
                            auto data = *_expl.getObjectSetItem(key);
                            _visitor.inObjectSetElement(data, key);
                            visitRecursive(data, _visitor);
                            _visitor.outObjectSetElement(data);
                        }
                        break;
                    default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                    }
                    _visitor.outObjectSet(_expl);
                    break;
                }
            }
            break;
            case ""_hash:
                _visitor.inArray(_expl);
                for (size_t i = 0; i < _expl.size(); ++i)
                {
                    auto data = _expl.getArrayItem(i);
                    _visitor.inArrayElement(data, i);
                    visitRecursive(data, _visitor);
                    _visitor.outArrayElement(data);
                }
                _visitor.outArray(_expl);
                break;
            }
        }
        break;
        case DataType::null: _visitor.nullProperty(_expl); break;
        case DataType::boolean: _visitor.boolProperty(_expl); break;
        case DataType::integer: _visitor.intProperty(_expl); break;
        case DataType::number: _visitor.floatProperty(_expl); break;
        case DataType::string: _visitor.stringProperty(_expl); break;
        case DataType::entityRef: _visitor.entityRefProperty(_expl); break;
        case DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
    }

    Visitor::Visitor() = default;
    Visitor::~Visitor() = default;

    void visit(Property const& _expl, Visitor& _visitor)
    {
        switch (_expl.getDataType())
        {
        case DataType::object: _visitor.inObject(); break;
        case DataType::oneOf: _visitor.inUnion(_expl.getUnionType()); break;
        case DataType::array:
        {
            auto meta = std::get<Subschema::ArrayMeta>(_expl.getSchema()->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash: _visitor.inMap(); break;
            case "set"_hash:
            {
                auto const& itemType = _expl.getSchema()->singularItems->get();
                switch (itemType.type)
                {
                case DataType::integer:
                case DataType::entityRef: [[fallthrough]];
                case DataType::string: _visitor.inPrimSet(itemType.type); break;
                case DataType::oneOf: _visitor.inUnionSet(); break;
                case DataType::object: _visitor.inObjectSet(); break;
                }
            }
            break;
            case ""_hash: _visitor.inArray(); break;
            }
        }
        break;
        case DataType::null: _visitor.nullProperty(); break;
        case DataType::boolean: _visitor.boolProperty(); break;
        case DataType::integer: _visitor.intProperty(); break;
        case DataType::number: _visitor.floatProperty(); break;
        case DataType::string: _visitor.stringProperty(); break;
        case DataType::entityRef: _visitor.entityRefProperty(); break;
        case DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
    }
} // namespace Ent
