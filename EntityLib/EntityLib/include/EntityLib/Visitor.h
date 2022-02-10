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
        virtual void inObject([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in an object's field
        virtual bool inObjectField([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _key)
        {
            return true;
        }
        /// Called when exiting an object's field
        virtual void outObjectField([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _key)
        {
        }
        /// Called when exiting an object
        virtual void outObject([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in a union
        virtual void inUnion([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _type)
        {
        }
        /// Called when exiting a union
        virtual void outUnion([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in a Map
        virtual void inMap([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when exiting a Map
        virtual void outMap([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in a Map's element (string key)
        virtual void inMapElement([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _key)
        {
        }
        /// Called when entering in a Map's element (integer key)
        virtual void inMapElement([[maybe_unused]] Layer& expl, [[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting a Map's element (Get back to Map)
        virtual void outMapElement([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in a Set of primitive
        virtual void inPrimSet([[maybe_unused]] Layer& expl, [[maybe_unused]] Ent::DataType _dataType)
        {
        }
        /// Called when entering in the element of an array
        virtual void inArrayElement([[maybe_unused]] Layer& expl, [[maybe_unused]] size_t _index)
        {
        }
        /// Called when exiting the element of an array
        virtual void outArrayElement([[maybe_unused]] Layer& expl)
        {
        }
        /// Called for each values in a set of primitive
        virtual void key([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _key)
        {
        }
        /// Called for each values in a set of primitive
        virtual void key([[maybe_unused]] Layer& expl, [[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting a set of primitive
        virtual void outPrimSet([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in a set of union
        virtual void inUnionSet([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in the element of a set of union
        virtual void inUnionSetElement([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _type)
        {
        }
        /// Called when exiting the element of a set of union
        virtual void outUnionSetElement([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when exiting a set of union
        virtual void outUnionSet([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in a set of object
        virtual void inObjectSet([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when exiting a set of object
        virtual void outObjectSet([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in the child of a set of object
        virtual void inObjectSetElement([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _key)
        {
        }
        /// Called when entering in the child of a set of object
        virtual void inObjectSetElement([[maybe_unused]] Layer& expl, [[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting the child of a set of object
        virtual void outObjectSetElement([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entering in a simple array
        virtual void inArray([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when exiting in a simple array
        virtual void outArray([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entered in a null Node
        virtual void nullNode([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entered in a bool Node
        virtual void boolNode([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entered in a integer Node
        virtual void intNode([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entered in a float Node
        virtual void floatNode([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entered in a string Node
        virtual void stringNode([[maybe_unused]] Layer& expl)
        {
        }
        /// Called when entered in a entityref Node
        virtual void entityRefNode([[maybe_unused]] Layer& expl)
        {
        }
    };

    /// Visit all the given _expl Cursor in depth, calling _visitor at each step
    void visitRecursive(
        Layer& _expl, ///< Cursor to visit
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
        Layer& _expl, ///< Cursor to visit
        Visitor& _visitor ///< The right method in _visitor will be called (according the the type in _expl)
    );
} // namespace Ent
