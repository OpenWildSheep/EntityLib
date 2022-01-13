#pragma once

#include "Visitor.h"

namespace Ent
{
    /// Deep copy from a Node to an empty Node
    class CopyToEmptyNode : public RecursiveVisitor
    {
        Cursor& source;
        Cursor& dest;

    public:
        CopyToEmptyNode(Cursor& _source, Cursor& _dest)
            : source(_source)
            , dest(_dest)
        {
        }
        bool inObjectField(char const* _key) override
        {
            dest.enterObjectField(_key);
            return true;
        }
        void outObjectField([[maybe_unused]] char const* _key) override
        {
            dest.exit();
        }
        void inUnion(char const* _type) override
        {
            if (source.isSet())
            {
                dest.setUnionType(_type);
            }
            dest.enterUnionData(_type);
        }
        void outUnion() override
        {
            dest.exit();
        }
        void inMapElement(char const* _key) override
        {
            dest.enterMapItem(_key);
        }
        void inMapElement(int64_t _key) override
        {
            dest.enterMapItem(_key);
        }
        void outMapElement() override
        {
            dest.exit();
        }
        void inArrayElement(size_t _index) override
        {
            dest.enterArrayItem(_index);
        }
        void outArrayElement() override
        {
            dest.exit();
        }
        void key(char const* _key) override
        {
            dest.insertPrimSetKey(_key);
        }
        void key(int64_t _key) override
        {
            dest.insertPrimSetKey(_key);
        }
        void inUnionSetElement(char const* _type) override
        {
            dest.enterUnionSetItem(_type);
        }
        void outUnionSetElement() override
        {
            dest.exit();
        }
        void inObjectSetElement(char const* _key) override
        {
            dest.enterObjectSetItem(_key);
        }
        void inObjectSetElement(int64_t _key) override
        {
            dest.enterObjectSetItem(_key);
        }
        void outObjectSetElement() override
        {
            dest.exit();
        }
        void inArray() override
        {
            if (source.isSet())
            {
                dest.setSize(source.size());
            }
        }
        void boolNode() override
        {
            if (source.isSet())
            {
                dest.setBool(source.getBool());
            }
        }
        void intNode() override
        {
            if (source.isSet())
            {
                dest.setInt(source.getInt());
            }
        }
        void floatNode() override
        {
            if (source.isSet())
            {
                dest.setFloat(source.getFloat());
            }
        }
        void stringNode() override
        {
            if (source.isSet())
            {
                dest.setString(source.getString());
            }
        }
        void entityRefNode() override
        {
            if (source.isSet())
            {
                dest.setEntityRef(source.getEntityRef());
            }
        }
    };
} // namespace Ent
