#pragma once

#include "Cursor.h"

namespace Ent
{
    class RecursiveVisitor
    {
    public:
        RecursiveVisitor();
        virtual ~RecursiveVisitor();
        RecursiveVisitor(RecursiveVisitor const&) = delete;
        RecursiveVisitor(RecursiveVisitor&&) = delete;
        RecursiveVisitor& operator=(RecursiveVisitor const&) = delete;
        RecursiveVisitor& operator=(RecursiveVisitor&&) = delete;

        virtual void inObject()
        {
        }
        virtual bool inObjectField([[maybe_unused]] char const* _key)
        {
            return true;
        }
        virtual void outObjectField([[maybe_unused]] char const* _key)
        {
        }
        virtual void outObject()
        {
        }
        virtual void inUnion([[maybe_unused]] char const* _type)
        {
        }
        virtual void outUnion()
        {
        }
        virtual void inMap()
        {
        }
        virtual void outMap()
        {
        }
        virtual void inMapElement([[maybe_unused]] char const* _key)
        {
        }
        virtual void inMapElement([[maybe_unused]] int64_t _key)
        {
        }
        virtual void outMapElement()
        {
        }
        virtual void inPrimSet([[maybe_unused]] Ent::DataType _dataType)
        {
        }
        virtual void inArrayElement([[maybe_unused]] size_t _key)
        {
        }
        virtual void outArrayElement()
        {
        }
        virtual void key([[maybe_unused]] char const* _key)
        {
        }
        virtual void key([[maybe_unused]] int64_t _key)
        {
        }
        virtual void outPrimSet()
        {
        }
        virtual void inUnionSet()
        {
        }
        virtual void inUnionSetElement([[maybe_unused]] char const* _type)
        {
        }
        virtual void outUnionSetElement()
        {
        }
        virtual void outUnionSet()
        {
        }
        virtual void inObjectSet()
        {
        }
        virtual void outObjectSet()
        {
        }
        virtual void inObjectSetElement([[maybe_unused]] char const* _key)
        {
        }
        virtual void inObjectSetElement([[maybe_unused]] int64_t _key)
        {
        }
        virtual void outObjectSetElement()
        {
        }
        virtual void inArray()
        {
        }
        virtual void outArray()
        {
        }
        virtual void nullNode()
        {
        }
        virtual void boolNode()
        {
        }
        virtual void intNode()
        {
        }
        virtual void floatNode()
        {
        }
        virtual void stringNode()
        {
        }
        virtual void entityRefNode()
        {
        }
    };

    void visitRecursive(Cursor& _expl, RecursiveVisitor& _visitor, bool _sortFields);

    class Visitor
    {
    public:
        Visitor();
        virtual ~Visitor();
        Visitor(Visitor const&) = delete;
        Visitor(Visitor&&) = delete;
        Visitor& operator=(Visitor const&) = delete;
        Visitor& operator=(Visitor&&) = delete;

        virtual void inObject()
        {
        }
        virtual void inUnion([[maybe_unused]] char const* _type)
        {
        }
        virtual void inMap()
        {
        }
        virtual void inPrimSet([[maybe_unused]] Ent::DataType _dataType)
        {
        }
        virtual void inUnionSet()
        {
        }
        virtual void inObjectSet()
        {
        }
        virtual void inArray()
        {
        }
        virtual void nullNode()
        {
        }
        virtual void boolNode()
        {
        }
        virtual void intNode()
        {
        }
        virtual void floatNode()
        {
        }
        virtual void stringNode()
        {
        }
        virtual void entityRefNode()
        {
        }
    };

    void visit(Cursor& _expl, Visitor& _visitor);
} // namespace Ent
