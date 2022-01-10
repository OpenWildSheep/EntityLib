#include "Schema.h"

#include <algorithm>
#include <ciso646>

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
        if (auto iter = unionTypeMap.find(_subtype); iter != unionTypeMap.end())
        {
            return {iter->second.wrapperSchema, iter->second.index};
        }
        else
        {
            throw BadUnionType(_subtype);
        }
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
        auto fieldName = getUnionNameField();
        auto& typeSchema = oneOf->front()->properties.at(fieldName);
        return typeSchema->constValue->get_ptr<nlohmann::json::string_t const*>()->c_str();
    }

} // namespace Ent
