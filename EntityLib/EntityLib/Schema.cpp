#include "include/Schema.h"

#include <algorithm>
#include <ciso646>
#include "Tools.h"

namespace Ent
{
    std::pair<Subschema const*, size_t> Subschema::getUnionTypeWrapper(char const* _subtype) const
    {
        if (type != DataType::oneOf)
        {
            throw BadType();
        }
        if (not std::holds_alternative<UnionMeta>(meta))
        {
            throw MissingMetadata(name.c_str());
        }
        if (auto const iter = unionTypeMap.find(_subtype); iter != unionTypeMap.end())
        {
            return {iter->second.wrapperSchema, iter->second.index};
        }
        throw BadUnionType(_subtype);
    }
    /// @endcond

    Subschema const* Subschema::getUnionType(char const* _subtype) const
    {
        auto const& un = std::get<UnionMeta>(meta);
        auto [schema, index] = getUnionTypeWrapper(_subtype);
        return &AT(schema->properties, un.dataField).get();
    }

    char const* Subschema::getUnionNameField() const
    {
        if (type != DataType::oneOf)
        {
            throw BadType();
        }
        if (not std::holds_alternative<UnionMeta>(meta))
        {
            throw MissingMetadata(name.c_str());
        }

        auto const& unionData = std::get<UnionMeta>(meta);
        return unionData.typeField.c_str();
    }

    char const* Subschema::getUnionDataField() const
    {
        if (type != DataType::oneOf)
        {
            throw BadType();
        }
        if (not std::holds_alternative<UnionMeta>(meta))
        {
            throw MissingMetadata(name.c_str());
        }

        auto const& unionData = std::get<UnionMeta>(meta);
        return unionData.dataField.c_str();
    }

    std::map<std::string, Subschema const*> Subschema::getUnionTypesMap() const
    {
        if (type != DataType::oneOf)
        {
            throw BadType();
        }
        if (not std::holds_alternative<UnionMeta>(meta))
        {
            throw MissingMetadata(name.c_str());
        }

        std::map<std::string, Subschema const*> result;

        auto const& unionData = std::get<UnionMeta>(meta);

        for (SubschemaRef const& ref : *oneOf)
        {
            auto acceptedType =
                AT(ref.get().properties, unionData.typeField)->constValue->get<std::string>();
            Subschema const& schema = AT(ref.get().properties, unionData.dataField).get();
            result.emplace(std::move(acceptedType), &schema);
        }

        return result;
    }

    char const* Subschema::getUnionDefaultTypeName() const
    {
        auto const fieldName = getUnionNameField();
        auto& typeSchema = oneOf->front()->properties.at(fieldName);
        return typeSchema->constValue->get_ptr<nlohmann::json::string_t const*>()->c_str();
    }

    DataKind Subschema::getDataKind() const
    {
        switch (type)
        {
        case DataType::string: return DataKind::string;
        case DataType::number: return DataKind::number;
        case DataType::integer: return DataKind::integer;
        case DataType::object: return DataKind::object;
        case DataType::boolean: return DataKind::boolean;
        case DataType::entityRef: return DataKind::entityRef;
        case DataType::oneOf: return DataKind::union_;
        case DataType::array:
            switch (hash(std::get<ArrayMeta>(meta).overridePolicy))
            {
            case "map"_hash: return DataKind::map;
            case "set"_hash:
                switch (singularItems->get().type)
                {
                case DataType::integer: [[fallthrough]];
                case DataType::string: return DataKind::primitiveSet;
                case DataType::oneOf: return DataKind::unionSet;
                case DataType::object: return DataKind::objectSet;
                default: break;
                }
                ENTLIB_LOGIC_ERROR("Unexpected DataType in singularItems of set !");
            case ""_hash: return DataKind::array;
            }
            ENTLIB_LOGIC_ERROR("Unexpected overridePolicy !");
        case DataType::COUNT: break;
        case DataType::null: break;
        }
        ENTLIB_LOGIC_ERROR("Unexpected DataType !");
    }
} // namespace Ent
