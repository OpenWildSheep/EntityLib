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
            return ref->properties.at(un.typeField).get().constValue->get<std::string>() == subtype;
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
        return &getUnionTypeWrapper(_subtype)->properties.at(un.dataField).get();
    }

} // namespace Ent
