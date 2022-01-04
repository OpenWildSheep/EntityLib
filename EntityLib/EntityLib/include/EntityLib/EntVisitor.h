#pragma once

#include "Cursor.h"

namespace Ent
{
    class RecursiveVisitor
    {
    public:
        RecursiveVisitor() = default;
        virtual ~RecursiveVisitor() = default;
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
        virtual void inUnion(char const*)
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
        virtual void inMapElement(char const*)
        {
        }
        virtual void inMapElement(int64_t)
        {
        }
        virtual void outMapElement()
        {
        }
        virtual void inPrimSet(Ent::DataType)
        {
        }
        virtual void inArrayElement(size_t)
        {
        }
        virtual void outArrayElement()
        {
        }
        virtual void key(char const*)
        {
        }
        virtual void key(int64_t)
        {
        }
        virtual void outPrimSet()
        {
        }
        virtual void inUnionSet()
        {
        }
        virtual void inUnionSetElement(char const*)
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
        virtual void inObjectSetElement(char const*)
        {
        }
        virtual void inObjectSetElement(int64_t)
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

    void visitRecursive(Cursor& expl, RecursiveVisitor& visitor, bool sortFields);
} // namespace Ent
