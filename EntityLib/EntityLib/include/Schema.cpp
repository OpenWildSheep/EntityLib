#include "Schema.h"

#include <algorithm>
#include <ciso646>

namespace Ent
{
    std::pair<Subschema const*, size_t> Subschema::getUnionTypeWrapper(char const* _subtype) const
    {
        if (type != Ent::DataType::oneOf)
        {
            throw BadType();
        }
        std::string const subtype(_subtype);
        if (not std::holds_alternative<UnionMeta>(meta))
        {
            throw MissingMetadata(name.c_str());
        }
        auto const& un = std::get<UnionMeta>(meta);
        auto iter = std::find_if(begin(*oneOf), end(*oneOf), [&](SubschemaRef const& ref) {
            return AT(ref->properties, un.typeField).get().constValue->get<std::string>() == subtype;
        });
        if (iter == end(*oneOf))
        {
            throw BadUnionType(_subtype);
        }
        else
        {
            return {&iter->get(), iter - begin(*oneOf)};
        }
    }
    /// @endcond

    Subschema const* Subschema::getUnionType(char const* _subtype) const
    {
        auto const& un = std::get<UnionMeta>(meta);
        auto schema = getUnionTypeWrapper(_subtype).first;
        return &AT(schema->properties, un.dataField).get();
    }

    char const* Subschema::getUnionNameField() const
    {
        if (type != Ent::DataType::oneOf)
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
        if (type != Ent::DataType::oneOf)
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
        if (type != Ent::DataType::oneOf)
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
