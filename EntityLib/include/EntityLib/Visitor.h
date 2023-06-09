#pragma once

#include "Property.h"

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
        virtual void inObject([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in an object's field
        virtual bool
        inObjectField([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _key)
        {
            return true;
        }
        /// Called when exiting an object's field
        virtual void
        outObjectField([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _key)
        {
        }
        /// Called when exiting an object
        virtual void outObject([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in a union
        virtual void inUnion([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _type)
        {
        }
        /// Called when exiting a union
        virtual void outUnion([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in a Map
        virtual void inMap([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when exiting a Map
        virtual void outMap([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in a Map's element (string key)
        virtual void
        inMapElement([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _key)
        {
        }
        /// Called when entering in a Map's element (integer key)
        virtual void inMapElement([[maybe_unused]] Property const& _prop, [[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting a Map's element (Get back to Map)
        virtual void outMapElement([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in a Set of primitive
        virtual void inPrimSet([[maybe_unused]] Property const& _prop, [[maybe_unused]] DataKind _dataKind)
        {
        }
        /// Called when entering in the element of an array
        virtual void inArrayElement([[maybe_unused]] Property const& _prop, [[maybe_unused]] size_t _index)
        {
        }
        /// Called when exiting the element of an array
        virtual void outArrayElement([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called for each values in a set of primitive
        virtual void key([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _key)
        {
        }
        /// Called for each values in a set of primitive
        virtual void key([[maybe_unused]] Property const& _prop, [[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting a set of primitive
        virtual void outPrimSet([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in a set of union
        virtual void inUnionSet([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in the element of a set of union
        virtual void
        inUnionSetElement([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _type)
        {
        }
        /// Called when exiting the element of a set of union
        virtual void outUnionSetElement([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when exiting a set of union
        virtual void outUnionSet([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in a set of object
        virtual void inObjectSet([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when exiting a set of object
        virtual void outObjectSet([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in the child of a set of object
        virtual void
        inObjectSetElement([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _key)
        {
        }
        /// Called when entering in the child of a set of object
        virtual void
        inObjectSetElement([[maybe_unused]] Property const& _prop, [[maybe_unused]] int64_t _key)
        {
        }
        /// Called when exiting the child of a set of object
        virtual void outObjectSetElement([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entering in a simple array
        virtual void inArray([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when exiting in a simple array
        virtual void outArray([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entered in a bool Node
        virtual void boolProperty([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entered in a integer Node
        virtual void intProperty([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entered in a float Node
        virtual void floatProperty([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entered in a string Node
        virtual void stringProperty([[maybe_unused]] Property const& _prop)
        {
        }
        /// Called when entered in a entityref Node
        virtual void entityRefProperty([[maybe_unused]] Property const& _prop)
        {
        }
    };

    /// Visit all the given _expl Property in depth, calling _visitor at each step
    void visitRecursive(
        Property const& _expl, ///< Property to visit
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
        virtual void inPrimSet([[maybe_unused]] DataKind _dataKind)
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
        /// The node has the type bool
        virtual void boolProperty()
        {
        }
        /// The node has the type integer
        virtual void intProperty()
        {
        }
        /// The node has the type number
        virtual void floatProperty()
        {
        }
        /// The node has the type string
        virtual void stringProperty()
        {
        }
        /// The node has the type entityref
        virtual void entityRefProperty()
        {
        }
    };

    /// Visit all the given _expl Property in a shallow way
    void visit(
        Property const& _expl, ///< Property to visit
        Visitor& _visitor ///< The right method in _visitor will be called (according the the type in _expl)
    );
} // namespace Ent
