#include "include/EntityLib/Visitor.h"

namespace Ent
{
    RecursiveVisitor::RecursiveVisitor() = default;
    RecursiveVisitor ::~RecursiveVisitor() = default;

    void visitRecursive(Cursor& _expl, RecursiveVisitor& _visitor, bool sortFields)
    {
        switch (_expl.getDataType())
        {
        case Ent::DataType::object:
        {
            _visitor.inObject();
            for (auto&& [name, schemaref] : _expl.getSchema()->properties)
            {
                _expl.enterObjectField(name.c_str(), &schemaref);
                if (_visitor.inObjectField(name.c_str()))
                {
                    visitRecursive(_expl, _visitor, sortFields);
                    _visitor.outObjectField(name.c_str());
                }
                _expl.exit();
            }
            _visitor.outObject();
            break;
        }
        case Ent::DataType::oneOf:
            _visitor.inUnion(_expl.getUnionType());
            _expl.enterUnionData();
            visitRecursive(_expl, _visitor, sortFields);
            _visitor.outUnion();
            _expl.exit();
            break;
        case Ent::DataType::array:
        {
            auto meta = std::get<Ent::Subschema::ArrayMeta>(_expl.getSchema()->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                _visitor.inMap();
                switch (_expl.getMapKeyType())
                {
                case Ent::DataType::string:
                    for (char const* key : _expl.getMapKeysString())
                    {
                        _expl.enterMapItem(key);
                        _visitor.inMapElement(key);
                        visitRecursive(_expl, _visitor, sortFields);
                        _visitor.outMapElement();
                        _expl.exit();
                    }
                    break;
                case Ent::DataType::integer:
                    for (int64_t key : _expl.getMapKeysInt())
                    {
                        _expl.enterMapItem(key);
                        _visitor.inMapElement(key);
                        visitRecursive(_expl, _visitor, sortFields);
                        _visitor.outMapElement();
                        _expl.exit();
                    }
                    break;
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                _visitor.outMap();
                break;
            case "set"_hash:
            {
                auto& itemType = _expl.getSchema()->singularItems->get();
                switch (itemType.type)
                {
                case Ent::DataType::integer:
                    _visitor.inPrimSet(itemType.type);
                    for (int64_t key : _expl.getPrimSetKeysInt())
                    {
                        _visitor.key(key);
                    }
                    _visitor.outPrimSet();
                    break;
                case Ent::DataType::string:
                    _visitor.inPrimSet(itemType.type);
                    for (char const* key : _expl.getPrimSetKeysString())
                    {
                        _visitor.key(key);
                    }
                    _visitor.outPrimSet();
                    break;
                case Ent::DataType::oneOf:
                    _visitor.inUnionSet();
                    for (auto&& [name, schema] : _expl.getUnionSetKeysString())
                    {
                        _expl.enterUnionSetItem(name, schema);
                        _visitor.inUnionSetElement(name);
                        visitRecursive(_expl, _visitor, sortFields);
                        _visitor.outUnionSetElement();
                        _expl.exit();
                    }
                    _visitor.outUnionSet();
                    break;
                case Ent::DataType::object:
                    _visitor.inObjectSet();
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case Ent::DataType::string:
                        for (auto&& key : _expl.getObjectSetKeysString())
                        {
                            _expl.enterObjectSetItem(key);
                            _visitor.inObjectSetElement(key);
                            visitRecursive(_expl, _visitor, sortFields);
                            _visitor.outObjectSetElement();
                            _expl.exit();
                        }
                        break;
                    case Ent::DataType::integer:
                        for (auto&& key : _expl.getObjectSetKeysInt())
                        {
                            _expl.enterObjectSetItem(key);
                            _visitor.inObjectSetElement(key);
                            visitRecursive(_expl, _visitor, sortFields);
                            _visitor.outObjectSetElement();
                            _expl.exit();
                        }
                        break;
                    default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                    }
                    _visitor.outObjectSet();
                    break;
                }
            }
            break;
            case ""_hash:
                _visitor.inArray();
                for (size_t i = 0; i < _expl.size(); ++i)
                {
                    _expl.enterArrayItem(i);
                    _visitor.inArrayElement(i);
                    visitRecursive(_expl, _visitor, sortFields);
                    _visitor.outArrayElement();
                    _expl.exit();
                }
                _visitor.outArray();
                break;
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

    Visitor::Visitor() = default;
    Visitor::~Visitor() = default;

    void visit(Cursor& _expl, Visitor& _visitor)
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
