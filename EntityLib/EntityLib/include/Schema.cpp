#include "Schema.h"

#include <algorithm>
#include <ciso646>

namespace Ent
{
    BadType::BadType()
        : std::runtime_error("Bad node type")
    {
    }

    MissingMetadata::MissingMetadata(char const* _schemaName)
        : std::runtime_error(std::string("Metadata missing : ") + _schemaName)
    {
    }

    BadUnionType::BadUnionType(char const* _type)
        : std::runtime_error(std::string("Bad union type : ") + _type)
    {
    }

    IllFormedSchema::IllFormedSchema(char const* _type)
        : std::runtime_error(std::string("Ill-formed schema : ") + _type)
    {
    }

    /// @cond PRIVATE
    Subschema const* Subschema::getUnionTypeWrapper(char const* _subtype) const
    {
        if (type != Ent::DataType::oneOf)
        {
            throw BadType();
        }
        std::string const subtype(_subtype);
        if (not meta.is<UnionMeta>())
        {
            throw MissingMetadata(name.c_str());
        }
        auto const& un = meta.get<UnionMeta>();
        auto iter = std::find_if(begin(*oneOf), end(*oneOf), [&](SubschemaRef const& ref) {
            return AT(ref->properties, un.typeField).get().constValue->get<std::string>() == subtype;
        });
        if (iter == end(*oneOf))
        {
            throw BadUnionType(_subtype);
        }
        else
        {
            return &iter->get();
        }
    }
    /// @endcond

    Subschema const* Subschema::getUnionType(char const* _subtype) const
    {
        auto const& un = meta.get<UnionMeta>();
        return &AT(getUnionTypeWrapper(_subtype)->properties, un.dataField).get();
    }

    char const* Subschema::getUnionNameField() const
    {
        if (type != Ent::DataType::oneOf)
        {
            throw BadType();
        }
        if (not meta.is<UnionMeta>())
        {
            throw MissingMetadata(name.c_str());
        }

        auto const& unionData = meta.get<UnionMeta>();
        return unionData.typeField.c_str();
    }

    char const* Subschema::getUnionDataField() const
    {
        if (type != Ent::DataType::oneOf)
        {
            throw BadType();
        }
        if (not meta.is<UnionMeta>())
        {
            throw MissingMetadata(name.c_str());
        }

        auto const& unionData = meta.get<UnionMeta>();
        return unionData.dataField.c_str();
    }

    std::map<std::string, Subschema const*> Subschema::getUnionTypesMap() const
    {
        if (type != Ent::DataType::oneOf)
        {
            throw BadType();
        }
        if (not meta.is<UnionMeta>())
        {
            throw MissingMetadata(name.c_str());
        }

        std::map<std::string, Subschema const*> result;

        auto const& unionData = meta.get<UnionMeta>();

        for (SubschemaRef const& ref : *oneOf)
        {
            std::string acceptedType =
                AT(ref.get().properties, unionData.typeField)->constValue->get<std::string>();
            Subschema const& schema = AT(ref.get().properties, unionData.dataField).get();
            result.emplace(std::move(acceptedType), &schema);
        }

        return result;
    }

} // namespace Ent
