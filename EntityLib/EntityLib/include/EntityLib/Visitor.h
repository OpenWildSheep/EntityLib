#pragma once

#include "Cursor.h"

namespace Ent
{
    /// Inherit from RecursiveVisitor to visit a Node in depth
    class RecursiveVisitor
    {
    public:
        RecursiveVisitor();
        virtual ~RecursiveVisitor();
        RecursiveVisitor(RecursiveVisitor const&) = delete;
        RecursiveVisitor(RecursiveVisitor&&) = delete;
        RecursiveVisitor& operator=(RecursiveVisitor const&) = delete;
        RecursiveVisitor& operator=(RecursiveVisitor&&) = delete;

        /// Called when entering in object
        virtual void inObject()
        {
        }
        /// Called when entering in an object's field
        virtual bool inObjectField([[maybe_unused]] char const* _key)
        {
            return true;
        }
        /// Called when exiting an object's field
        virtual void outObjectField([[maybe_unused]] char const* _key)
        {
        }
        /// Called when exiting an object
        virtual void outObject()
        {
        }
        /// Called when entering in a union
        virtual void inUnion([[maybe_unused]] char const* _type)
        {
        }
        /// Called when exiting a union
        virtual void outUnion()
        {
        }
        /// Called when entering in a Map
        virtual void inMap()
        {
        }
        /// Called when exiting a Map
        virtual void outMap()
        {
        }
        /// Called when entering in a Map's element (string key)
        virtual void inMapElement([[maybe_unused]] char const* _key)
        {
        }
        /// Called when entering in a Map's element (integer key)
        virtual void inMapElement([[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting a Map's element (Get back to Map)
        virtual void outMapElement()
        {
        }
        /// Called when entering in a Set of primitive
        virtual void inPrimSet([[maybe_unused]] Ent::DataType _dataType)
        {
        }
        /// Called when entering in the element of an array
        virtual void inArrayElement([[maybe_unused]] size_t _index)
        {
        }
        /// Called when exiting the element of an array
        virtual void outArrayElement()
        {
        }
        /// Called for each values in a set of primitive
        virtual void key([[maybe_unused]] char const* _key)
        {
        }
        /// Called for each values in a set of primitive
        virtual void key([[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting a set of primitive
        virtual void outPrimSet()
        {
        }
        /// Called when entering in a set of union
        virtual void inUnionSet()
        {
        }
        /// Called when entering in the element of a set of union
        virtual void inUnionSetElement([[maybe_unused]] char const* _type)
        {
        }
        /// Called when exiting the element of a set of union
        virtual void outUnionSetElement()
        {
        }
        /// Called when exiting a set of union
        virtual void outUnionSet()
        {
        }
        /// Called when entering in a set of object
        virtual void inObjectSet()
        {
        }
        /// Called when exiting a set of object
        virtual void outObjectSet()
        {
        }
        /// Called when entering in the child of a set of object
        virtual void inObjectSetElement([[maybe_unused]] char const* _key)
        {
        }
        /// Called when entering in the child of a set of object
        virtual void inObjectSetElement([[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting the child of a set of object
        virtual void outObjectSetElement()
        {
        }
        /// Called when entering in a simple array
        virtual void inArray()
        {
        }
        /// Called when exiting in a simple array
        virtual void outArray()
        {
        }
        /// Called when entered in a null Node
        virtual void nullNode()
        {
        }
        /// Called when entered in a bool Node
        virtual void boolNode()
        {
        }
        /// Called when entered in a integer Node
        virtual void intNode()
        {
        }
        /// Called when entered in a float Node
        virtual void floatNode()
        {
        }
        /// Called when entered in a string Node
        virtual void stringNode()
        {
        }
        /// Called when entered in a entityref Node
        virtual void entityRefNode()
        {
        }
    };

    /// Visit all the given _expl Cursor in depth, calling _visitor at each step
    void visitRecursive(
        Cursor& _expl, ///< Cursor to visit
        RecursiveVisitor& _visitor ///< RecursiveVisitor to call at each step
    );

    class Visitor
    {
    public:
        Visitor();
        virtual ~Visitor();
        Visitor(Visitor const&) = delete;
        Visitor(Visitor&&) = delete;
        Visitor& operator=(Visitor const&) = delete;
        Visitor& operator=(Visitor&&) = delete;

        /// The node is an object
        virtual void inObject()
        {
        }
        /// The node is a union
        virtual void inUnion([[maybe_unused]] char const* _type)
        {
        }
        /// The node is a map
        virtual void inMap()
        {
        }
        /// The node is a set of primitive
        virtual void inPrimSet([[maybe_unused]] Ent::DataType _dataType)
        {
        }
        /// The node is a set of union
        virtual void inUnionSet()
        {
        }
        /// The node is a set of object
        virtual void inObjectSet()
        {
        }
        /// The node is an array
        virtual void inArray()
        {
        }
        /// The node has the type null
        virtual void nullNode()
        {
        }
        /// The node has the type bool
        virtual void boolNode()
        {
        }
        /// The node has the type integer
        virtual void intNode()
        {
        }
        /// The node has the type number
        virtual void floatNode()
        {
        }
        /// The node has the type string
        virtual void stringNode()
        {
        }
        /// The node has the type entityref
        virtual void entityRefNode()
        {
        }
    };

    /// Visit all the given _expl Cursor in a shallow way
    void visit(
        Cursor& _expl, ///< Cursor to visit
        Visitor& _visitor ///< The right method in _visitor will be called (according the the type in _expl)
    );
} // namespace Ent
