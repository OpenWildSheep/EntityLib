#pragma once

#pragma warning(push, 0)
#include <map>
#include <memory>
#include <vector>

#include "../../../external/mapbox/variant.hpp"
#include "../external/optional.hpp"
#include "../external/json.hpp"
#pragma warning(pop)

#include "EntityLibCore.h"

/// EntityLib namespace
namespace Ent
{
    /// Internal type of a property Node
    enum class DataType
    {
        null,
        string, ///< Contains a string
        number, ///< Contains a number (real)
        integer, ///< Contains an integer
        object, ///< Contains a json object (it has properties)
        array, ///< Contains an array . It can be singular (one type for all) or linear (one type per element)
        boolean, ///< Contains a boolean value
        entityRef, ///< Contains a string which is a path to an Entity
        oneOf, ///< It is actually a union type, but union is a C keyword
        COUNT
    };

    /// @cond PRIVATE
    using Null = std::nullptr_t;
    /// @endcond

    // *************************************** Subschema ******************************************

    struct SubschemaRef;
    class Schema;

    /// Definition of a json Node
    struct ENTLIB_DLLEXPORT Subschema
    {
        /// @cond PRIVATE
        Subschema() = default;
        Subschema(Subschema const&) = delete;
        Subschema& operator=(Subschema const&) = delete;
        Subschema(Subschema&&) = default;
        Subschema& operator=(Subschema&&) = default;
        DeleteCheck deleteCheck;

        /// @brief Get the Subschema related to the given \p _subtype (className)
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        /// @throw BadUnionType if \p _subtype is not listed in the oneOf field
        Subschema const* getUnionTypeWrapper(char const* _subtype) const;
        /// @endcond

        Schema* rootSchema{};
        DataType type = DataType::null; ///< type of this Subschema. @see Ent::DataType
        bool required = false; ///< Is this property required?
        std::map<std::string, SubschemaRef> properties; ///< If type == Ent::DataType::object, child properties
        size_t maxItems = size_t(-1); ///< Maximum size of the array. (inclusive) [min, max]
        size_t minItems = 0; ///< @brief Minimum size of an array
        tl::optional<std::vector<SubschemaRef>> oneOf; ///< This object have to match with one of thos schema (union)
        std::string name; ///< This is not a constraint. Just the name of the definition
        nlohmann::json userMeta;

        // Meta informations
        /// Store metadata for any type
        struct BaseMeta
        {
            bool usedInEditor = true; ///< Does this Subschema exists in edition context ?
            bool usedInRuntime = true; ///< Does this Subschema exists in runtime context ?
            bool deprecated = false; ///< Is this Subschema deprecated ?
        };
        /// Store metadata for numeric type
        struct NumberMeta : BaseMeta
        {
            uint32_t bitDepth = 32; ///< Bit depth of this number, either 8, 16, 32 or 64
            bool isSigned = true; ///< is this number signed ?
        };
        /// Store metadata for union type (oneOf in json schema)
        struct UnionMeta : BaseMeta
        {
            std::string dataField; ///< Name of the field containing the data (ex : classData)
            std::string typeField; ///< Name of the field containing the type of the data (ex : className)
        };
        /// Store metadata for array type
        struct ArrayMeta : BaseMeta
        {
            std::string overridePolicy; ///< Policy used to override the array from the prefab
            bool ordered = true;
            bool isMapItem = false; ///< Can't be discarded at write (neither null)
        };
        /// Store metadata for all schema which doesn't have specific field
        struct GenericMeta : BaseMeta
        {
        };
        /// Meta data for any type of Node
        using Meta = mapbox::util::variant<GenericMeta, NumberMeta, UnionMeta, ArrayMeta>;
        Meta meta; ///< Contains meta data for any type of Node

        // helper methods
        bool IsDeprecated() const; ///< Is this node deprecated? (access to meta data)
        bool IsUsedInEditor() const; ///< Is this node used in editor? (access to meta data)
        bool IsUsedInRuntime() const; ///< Is this node used in runtime? (access to meta data)
        bool IsRuntimeOnly() const /// Is this node used in runtime only? (access to meta data)
        {
            return IsUsedInRuntime() && !IsUsedInEditor();
        }
        bool IsEditorOnly() const /// Is this node used in editor only? (access to meta data)
        {
            return !IsUsedInRuntime() && IsUsedInEditor();
        }

        /// @brief Get all types acceptable in the union, with their names
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        std::map<std::string, Subschema const*> getUnionTypesMap() const;

        /// @brief Get the Subschema related to the given \p _type (className)
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        /// @throw BadUnionType if \p _type is not listed in the oneOf field
        Subschema const* getUnionType(char const* _subtype) const;

        /// @brief Get the name of the json field containing the type name
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        char const* getUnionNameField() const;

        /// @brief Get the name of the json field containing the data
        /// @throw BadType if the schema is not a oneOf
        /// @throw MissingMetadata if the schema doesn't have a meta className and classData
        char const* getUnionDataField() const;

        /// Contains the simple value of one of the possible Ent::DataType
        using DefaultValue = nlohmann::json;
        DefaultValue defaultValue; ///< @brief Contains the data according to the type
        tl::optional<DefaultValue> constValue; ///< This property can only have this value

        /// @brief Subschema of the unique type of item
        ///
        /// If type == Ent::DataType::array,
        ///   If all items have the same type (SingularItem),
        ///     This is the description of the items
        std::unique_ptr<SubschemaRef> singularItems;
        /// @brief Subschema of each items
        ///
        /// If type == Ent::DataType::array,
        ///   If all items have a different type (LinearItem),
        ///     This is the description of each items
        tl::optional<std::vector<SubschemaRef>> linearItems;
        std::vector<std::string> enumValues; ///< List of all posible values for enum
    };

    class Schema;

    /// Can hold a Subschema OR a reference to a Subschema
    struct SubschemaRef
    {
        /// @cond PRIVATE
        SubschemaRef() = default;
        SubschemaRef(SubschemaRef const&) = delete;
        SubschemaRef& operator=(SubschemaRef const&) = delete;
        SubschemaRef(SubschemaRef&&) = default;
        SubschemaRef& operator=(SubschemaRef&&) = default;
        /// @endcond

        using DefaultValue = nlohmann::json;

        /// @cond PRIVATE
        /// Make this private
        struct Ref
        {
            Schema* schema; //!< Schema of the referenced object
            std::string ref; //!< Name of the referenced object
            DefaultValue defaultValue; ///< Additional default values (beside a "$ref")
        };

        mapbox::util::variant<Null, Ref, Subschema> subSchemaOrRef;
        DeleteCheck deleteCheck;
        /// @endcond

        Subschema const& get() const; //!< Get the referenced subschema
        Subschema& get(); //!< Get the referenced subschema

        Subschema const& operator*() const; //!< Get the referenced subschema
        Subschema& operator*(); //!< Get the referenced subschema
        Subschema const* operator->() const; //!< Get the referenced subschema
        Subschema* operator->(); //!< Get the referenced subschema

        /// Get the default values beside a "$ref", or nullptr
        DefaultValue const* getRefDefaultValues() const
        {
            if (subSchemaOrRef.is<Ref>() && !subSchemaOrRef.get<Ref>().defaultValue.is_null())
            {
                return &subSchemaOrRef.get<Ref>().defaultValue;
            }
            else
            {
                return nullptr;
            }
        }
    };

    class EntityLib;

    /// Definition of everything
    class Schema
    {
    public:
        Schema() = default;
        Schema(Schema const&) = delete;
        Schema& operator=(Schema const&) = delete;
        SubschemaRef root; ///< Root Schema : Schema of the scene
        std::map<std::string, Subschema> allDefinitions; ///< Definition of everything, by type name
        EntityLib* entityLib = nullptr;

        /// @cond PRIVATE
        DeleteCheck deleteCheck;
        /// @endcond
    };

#pragma warning(push)
#pragma warning(disable : 4702)
    /// @cond PRIVATE

    /// variant visitor to get a specifique field in a Subschema::BaseMeta
    struct BasicFieldGetter
    {
        std::function<bool(const Subschema::BaseMeta*)> _fieldSelector;

        template <class MetaT>
        bool operator()(const MetaT& _meta)
        {
            return _fieldSelector(&_meta);
        }
    };

    inline bool Subschema::IsDeprecated() const
    {
        return mapbox::util::apply_visitor(
            BasicFieldGetter{[](const Subschema::BaseMeta* _meta) {
                return _meta->deprecated;
            }},
            meta);
    }

    inline bool Subschema::IsUsedInEditor() const
    {
        return mapbox::util::apply_visitor(
            BasicFieldGetter{[](const Subschema::BaseMeta* _meta) {
                return _meta->usedInEditor;
            }},
            meta);
    }

    inline bool Subschema::IsUsedInRuntime() const
    {
        return mapbox::util::apply_visitor(
            BasicFieldGetter{[](const Subschema::BaseMeta* _meta) {
                return _meta->usedInRuntime;
            }},
            meta);
    }

    inline Subschema const& SubschemaRef::get() const
    {
        if (subSchemaOrRef.is<Ref>())
        {
            Ref const& ref = subSchemaOrRef.get<Ref>();
            return AT(ref.schema->allDefinitions, ref.ref);
        }
        else if (subSchemaOrRef.is<Subschema>())
            return subSchemaOrRef.get<Subschema>();
        else
        {
            ENTLIB_LOGIC_ERROR("Uninitialized SubschemaRef!");
            return subSchemaOrRef.get<Subschema>();
        }
    }

    inline Subschema& SubschemaRef::get()
    {
        if (subSchemaOrRef.is<Ref>())
        {
            Ref const& ref = subSchemaOrRef.get<Ref>();
            return AT(ref.schema->allDefinitions, ref.ref);
        }
        else if (subSchemaOrRef.is<Subschema>())
            return subSchemaOrRef.get<Subschema>();
        else
        {
            ENTLIB_LOGIC_ERROR("Uninitialized SubschemaRef!");
            return subSchemaOrRef.get<Subschema>();
        }
    }

    inline Subschema const& SubschemaRef::operator*() const
    {
        return get();
    }
    inline Subschema& SubschemaRef::operator*()
    {
        return get();
    }
    inline Subschema const* SubschemaRef::operator->() const
    {
        return &get();
    }
    inline Subschema* SubschemaRef::operator->()
    {
        return &get();
    }

    /// @endcond

#pragma warning(pop)

} // namespace Ent
