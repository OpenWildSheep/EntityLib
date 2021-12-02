#include "include/EntVisitor.h"

namespace Ent
{
    void visit(Cursor& expl, size_t tab, NodeVisitor& visitor)
    {
        auto getTab = [&] {
            return std::string(tab * 4, ' ');
        };
        switch (expl.getDataType())
        {
        case Ent::DataType::object:
            visitor.inObject();
            for (auto&& [name, schemaref] : expl.getSchema()->properties)
            {
                expl.checkInvariants();
                expl.enterObjectField(name.c_str(), &schemaref);
                visitor.inObjectField(name.c_str(), expl);
                expl.checkInvariants();
                visit(expl, tab + 1, visitor);
                expl.checkInvariants();
                visitor.outObjectField();
                expl.exit();
                expl.checkInvariants();
            }
            visitor.outObject();
            break;
        case Ent::DataType::oneOf:
            visitor.inUnion(expl.getUnionType());
            expl.enterUnionData();
            visit(expl, tab + 1, visitor);
            visitor.outUnion();
            expl.exit();
            break;
        case Ent::DataType::array:
        {
            auto meta = std::get<Ent::Subschema::ArrayMeta>(expl.getSchema()->meta);
            switch (hash(meta.overridePolicy))
            {
            case "map"_hash:
                visitor.inMap();
                switch (expl.getMapKeyType())
                {
                case Ent::DataType::string:
                    for (char const* key : expl.getMapKeysString())
                    {
                        expl.enterMapItem(key);
                        visitor.inMapElement(key);
                        visit(expl, tab + 1, visitor);
                        visitor.outMapElement();
                        expl.exit();
                    }
                    break;
                case Ent::DataType::integer:
                    for (int64_t key : expl.getMapKeysInt())
                    {
                        expl.enterMapItem(key);
                        visitor.inMapElement(key);
                        visit(expl, tab + 1, visitor);
                        visitor.outMapElement();
                        expl.exit();
                    }
                    break;
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                visitor.outMap();
                break;
            case "set"_hash:
            {
                auto& itemType = expl.getSchema()->singularItems.get()->get();
                switch (itemType.type)
                {
                case Ent::DataType::integer:
                    visitor.inPrimSet(itemType.type);
                    for (int64_t key : expl.getPrimSetKeysInt())
                    {
                        visitor.key(key);
                    }
                    visitor.outPrimSet();
                    break;
                case Ent::DataType::string:
                    visitor.inPrimSet(itemType.type);
                    for (char const* key : expl.getPrimSetKeysString())
                    {
                        visitor.key(key);
                    }
                    visitor.outPrimSet();
                    break;
                case Ent::DataType::oneOf:
                    visitor.inUnionSet();
                    for (auto&& [name, schema] : expl.getUnionSetKeysString())
                    {
                        expl.enterUnionSetItem(name, schema);
                        visitor.inUnionSetElement(name);
                        visit(expl, tab + 1, visitor);
                        visitor.outUnionSetElement();
                        expl.exit();
                    }
                    visitor.outUnionSet();
                    break;
                case Ent::DataType::object:
                    visitor.inObjectSet();
                    auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                    switch (keyFieldSchema.type)
                    {
                    case Ent::DataType::string:
                        for (auto&& key : expl.getObjectSetKeysString())
                        {
                            expl.enterObjectSetItem(key);
                            visitor.inObjectSetElement(key);
                            visit(expl, tab + 1, visitor);
                            visitor.outObjectSetElement();
                            expl.exit();
                        }
                        break;
                    case Ent::DataType::integer:
                        for (auto&& key : expl.getObjectSetKeysInt())
                        {
                            expl.enterObjectSetItem(key);
                            visitor.inObjectSetElement(key);
                            visit(expl, tab + 1, visitor);
                            visitor.outObjectSetElement();
                            expl.exit();
                        }
                        break;
                    default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                    }
                    visitor.outObjectSet();
                    break;
                }
            }
            break;
            case ""_hash:
                visitor.inArray();
                for (size_t i = 0; i < expl.size(); ++i)
                {
                    expl.enterArrayItem(i);
                    visitor.inArrayElement(i);
                    visit(expl, tab + 1, visitor);
                    visitor.outArrayElement();
                    expl.exit();
                }
                visitor.outArray();
                break;
            }
        }
        break;
        case Ent::DataType::null: visitor.nullNode(); break;
        case Ent::DataType::boolean: visitor.boolNode(); break;
        case Ent::DataType::integer: visitor.intNode(); break;
        case Ent::DataType::number: visitor.floatNode(); break;
        case Ent::DataType::string: visitor.stringNode(); break;
        case Ent::DataType::entityRef: visitor.entityRefNode(); break;
        case Ent::DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Unexpected DataType!");
        }
    }
} // namespace Ent
