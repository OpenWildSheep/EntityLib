#include "include/EntityLib/Visitor.h"

namespace Ent
{
    RecursiveVisitor::RecursiveVisitor() = default;
    RecursiveVisitor ::~RecursiveVisitor() = default;

    void visitRecursive(Property const& _expl, RecursiveVisitor& _visitor)
    {
        switch (_expl.getDataKind())
        {
        case DataKind::object:
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
        case DataKind::union_:
        {
            _visitor.inUnion(_expl, _expl.getUnionType());
            auto data = _expl.getUnionData();
            visitRecursive(data, _visitor);
            _visitor.outUnion(_expl);
            break;
        }
        case DataKind::array:
        {
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
        case DataKind::unionSet:
        {
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
        }
        case DataKind::objectSet:
        {
            auto meta = std::get<Subschema::ArrayMeta>(_expl.getSchema()->meta);
            auto& itemType = _expl.getSchema()->singularItems->get();

            _visitor.inObjectSet(_expl);
            auto const& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
            switch (keyFieldSchema.getDataKind())
            {
            case DataKind::entityRef: [[fallthrough]];
            case DataKind::string:
                for (auto&& key : _expl.getObjectSetKeysString())
                {
                    auto data = *_expl.getObjectSetItem(key);
                    _visitor.inObjectSetElement(data, key);
                    visitRecursive(data, _visitor);
                    _visitor.outObjectSetElement(data);
                }
                break;
            case DataKind::integer:
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
        case DataKind::map:
        {
            _visitor.inMap(_expl);
            switch (_expl.getMapKeyKind())
            {
            case DataKind::entityRef: [[fallthrough]];
            case DataKind::string:
                for (char const* key : _expl.getMapKeysString())
                {
                    auto value = _expl.getMapItem(key);
                    ENTLIB_ASSERT(value.has_value());
                    _visitor.inMapElement(*value, key);
                    visitRecursive(*value, _visitor);
                    _visitor.outMapElement(*value);
                }
                break;
            case DataKind::integer:
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
        }
        case DataKind::primitiveSet:
        {
            auto& itemType = _expl.getSchema()->singularItems->get();
            switch (itemType.getDataKind())
            {
            case DataKind::integer:
                _visitor.inPrimSet(_expl, itemType.getDataKind());
                for (int64_t const key : _expl.getPrimSetKeysInt())
                {
                    _visitor.key(_expl, key);
                }
                _visitor.outPrimSet(_expl);
                break;
            case DataKind::entityRef: [[fallthrough]];
            case DataKind::string:
                _visitor.inPrimSet(_expl, itemType.getDataKind());
                for (char const* key : _expl.getPrimSetKeysString())
                {
                    _visitor.key(_expl, key);
                }
                _visitor.outPrimSet(_expl);
                break;
            default: ENTLIB_LOGIC_ERROR("Unexpected DataKind!");
            }
            break;
        }
        case DataKind::boolean: _visitor.boolProperty(_expl); break;
        case DataKind::integer: _visitor.intProperty(_expl); break;
        case DataKind::number: _visitor.floatProperty(_expl); break;
        case DataKind::string: _visitor.stringProperty(_expl); break;
        case DataKind::entityRef: _visitor.entityRefProperty(_expl); break;
        case DataKind::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataKind!");
        }
    }

    Visitor::Visitor() = default;
    Visitor::~Visitor() = default;

    void visit(Property const& _expl, Visitor& _visitor)
    {
        switch (_expl.getDataKind())
        {
        case DataKind::object: _visitor.inObject(); break;
        case DataKind::union_: _visitor.inUnion(_expl.getUnionType()); break;
        case DataKind::array: _visitor.inArray(); break;
        case DataKind::unionSet: _visitor.inUnionSet(); break;
        case DataKind::objectSet: _visitor.inObjectSet(); break;
        case DataKind::map: _visitor.inMap(); break;
        case DataKind::primitiveSet:
        {
            auto const& itemType = _expl.getSchema()->singularItems->get();
            _visitor.inPrimSet(itemType.getDataKind());
        }
        break;
        case DataKind::boolean: _visitor.boolProperty(); break;
        case DataKind::integer: _visitor.intProperty(); break;
        case DataKind::number: _visitor.floatProperty(); break;
        case DataKind::string: _visitor.stringProperty(); break;
        case DataKind::entityRef: _visitor.entityRefProperty(); break;
        case DataKind::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataKind!");
        }
    }
} // namespace Ent
