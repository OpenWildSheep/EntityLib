#include "include/EntityLib/Visitor.h"

namespace Ent
{
    RecursiveVisitor::RecursiveVisitor() = default;
    RecursiveVisitor ::~RecursiveVisitor() = default;

    void visitRecursive(HandlerRW& _expl, RecursiveVisitor& _visitor)
    {
        switch (_expl.getDataType())
        {
        case Ent::DataType::object:
        {
            _visitor.inObject(_expl);
            for (auto&& [name, schemaref] : _expl.getSchema()->properties)
            {
                auto field = _expl.enterObjectField(name.c_str(), &schemaref);
                if (_visitor.inObjectField(field, name.c_str()))
                {
                    visitRecursive(field, _visitor);
                    _visitor.outObjectField(field, name.c_str());
                }
            }
            _visitor.outObject(_expl);
            break;
        }
        case Ent::DataType::oneOf:
        {
            _visitor.inUnion(_expl, _expl.getUnionType());
            auto data = _expl.enterUnionData();
            visitRecursive(data, _visitor);
            _visitor.outUnion(_expl);
            break;
        }
        case Ent::DataType::array:
        {
            auto meta = std::get<Ent::Subschema::ArrayMeta>(_expl.getSchema()->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                _visitor.inMap(_expl);
                switch (_expl.getMapKeyType())
                {
                case Ent::DataType::string:
                    for (char const* key : _expl.getMapKeysString())
                    {
                        auto value = _expl.enterMapItem(key);
                        _visitor.inMapElement(value, key);
                        visitRecursive(value, _visitor);
                        _visitor.outMapElement(value);
                    }
                    break;
                case Ent::DataType::integer:
                    for (int64_t key : _expl.getMapKeysInt())
                    {
                        auto value = _expl.enterMapItem(key);
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
                case Ent::DataType::integer:
                    _visitor.inPrimSet(_expl, itemType.type);
                    for (int64_t key : _expl.getPrimSetKeysInt())
                    {
                        _visitor.key(_expl, key);
                    }
                    _visitor.outPrimSet(_expl);
                    break;
                case Ent::DataType::string:
                    _visitor.inPrimSet(_expl, itemType.type);
                    for (char const* key : _expl.getPrimSetKeysString())
                    {
                        _visitor.key(_expl, key);
                    }
                    _visitor.outPrimSet(_expl);
                    break;
                case Ent::DataType::oneOf:
                    _visitor.inUnionSet(_expl);
                    for (auto&& [name, schema] : _expl.getUnionSetKeysString())
                    {
                        auto data = _expl.enterUnionSetItem(name, schema);
                        _visitor.inUnionSetElement(_expl, name);
                        visitRecursive(data, _visitor);
                        _visitor.outUnionSetElement(_expl);
                    }
                    _visitor.outUnionSet(_expl);
                    break;
                case Ent::DataType::object:
                    _visitor.inObjectSet(_expl);
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case Ent::DataType::string:
                        for (auto&& key : _expl.getObjectSetKeysString())
                        {
                            auto data = _expl.enterObjectSetItem(key);
                            _visitor.inObjectSetElement(data, key);
                            visitRecursive(data, _visitor);
                            _visitor.outObjectSetElement(data);
                        }
                        break;
                    case Ent::DataType::integer:
                        for (auto&& key : _expl.getObjectSetKeysInt())
                        {
                            auto data = _expl.enterObjectSetItem(key);
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
                    auto data = _expl.enterArrayItem(i);
                    _visitor.inArrayElement(data, i);
                    visitRecursive(data, _visitor);
                    _visitor.outArrayElement(data);
                }
                _visitor.outArray(_expl);
                break;
            }
        }
        break;
        case Ent::DataType::null: _visitor.nullNode(_expl); break;
        case Ent::DataType::boolean: _visitor.boolNode(_expl); break;
        case Ent::DataType::integer: _visitor.intNode(_expl); break;
        case Ent::DataType::number: _visitor.floatNode(_expl); break;
        case Ent::DataType::string: _visitor.stringNode(_expl); break;
        case Ent::DataType::entityRef: _visitor.entityRefNode(_expl); break;
        case Ent::DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
    }

    Visitor::Visitor() = default;
    Visitor::~Visitor() = default;

    void visit(HandlerRW& _expl, Visitor& _visitor)
    {
        switch (_expl.getDataType())
        {
        case Ent::DataType::object: _visitor.inObject(); break;
        case Ent::DataType::oneOf: _visitor.inUnion(_expl.getUnionType()); break;
        case Ent::DataType::array:
        {
            auto meta = std::get<Ent::Subschema::ArrayMeta>(_expl.getSchema()->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash: _visitor.inMap(); break;
            case "set"_hash:
            {
                auto& itemType = _expl.getSchema()->singularItems->get();
                switch (itemType.type)
                {
                case Ent::DataType::integer:
                case Ent::DataType::string: _visitor.inPrimSet(itemType.type); break;
                case Ent::DataType::oneOf: _visitor.inUnionSet(); break;
                case Ent::DataType::object: _visitor.inObjectSet(); break;
                }
            }
            break;
            case ""_hash: _visitor.inArray(); break;
            }
        }
        break;
        case Ent::DataType::null: _visitor.nullNode(); break;
        case Ent::DataType::boolean: _visitor.boolNode(); break;
        case Ent::DataType::integer: _visitor.intNode(); break;
        case Ent::DataType::number: _visitor.floatNode(); break;
        case Ent::DataType::string: _visitor.stringNode(); break;
        case Ent::DataType::entityRef: _visitor.entityRefNode(); break;
        case Ent::DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
    }
} // namespace Ent
