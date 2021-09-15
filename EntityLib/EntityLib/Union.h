#pragma once

#include "Override.h"
#include "include/Schema.h"

namespace Ent
{
    struct Node;
    struct MemoryProfiler;

    struct Union
    {
        Union(EntityLib const* _entityLib, Subschema const* _schema, Node&& _wrapper, size_t _typeIndex);

        EntityLib const* entityLib = nullptr;
        Subschema const* schema = nullptr; ///< The schema of the object containing the oneOf field
        size_t typeIndex = 0; ///< Index of the type
        value_ptr<Node> wrapper; ///< Node containing the className/classData
        Ent::Subschema::UnionMeta const* metaData = nullptr;

        bool typeOverriden = false;

        bool hasOverride() const; ///< Recursively check if there is an override inside.
        bool hasDefaultValue() const;
        Node* getUnionData(); ///< return the underlying data (The type is given by getUnionType)
        Node const* getUnionData() const; ///< return the underlying data (The type is given by getUnionType)
        char const* getUnionType() const; ///< Get the type inside the union
        /// @brief Change the type inside the union
        /// @pre type match with a type declared inside the json "oneOf"
        Node* setUnionType(char const* _type);

        void computeMemory(MemoryProfiler& prof) const;

        void unset();

        void applyAllValues(Union& _dest, CopyMode _copyMode) const;

        Union detach() const;

        Union makeInstanceOf() const;

        bool hasPrefabValue() const;

        void setParentNode(Node* _parentNode);
        void checkParent(Node const* _parentNode) const;

    private:
        Node* resetUnionTypeWithoutOverride(char const* _type);
    };
} // namespace Ent
