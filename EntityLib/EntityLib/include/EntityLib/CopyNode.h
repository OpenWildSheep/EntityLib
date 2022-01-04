#pragma once

#include "EntVisitor.h"

namespace Ent
{

    class CopyNode : public RecursiveVisitor
    {
        Cursor& source;
        Cursor& dest;

    public:
        CopyNode(Cursor& _source, Cursor& _dest)
            : source(_source)
            , dest(_dest)
        {
        }
        void inObject() override
        {
            // ENTLIB_ASSERT(nodes.back()->getFieldNames().size() == expl.get);
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
        void outObject() override
        {
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
        void inMap() override
        {
        }
        void outMap() override
        {
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
        void inPrimSet([[maybe_unused]] Ent::DataType _dataType) override
        {
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
        void outPrimSet() override
        {
        }
        void inUnionSet() override
        {
        }
        void inUnionSetElement(char const* _type) override
        {
            dest.enterUnionSetItem(_type);
        }
        void outUnionSetElement() override
        {
            dest.exit();
        }
        void outUnionSet() override
        {
        }
        void inObjectSet() override
        {
        }
        void outObjectSet() override
        {
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
        void outArray() override
        {
        }
        void nullNode() override
        {
        }
        void boolNode() override
        {
            if (source.isSet())
            {
                dest.setBool(source.getBool());
            }
            else
            {
                if (dest.isSet())
                {
                    // TODO : unset
                    // dest.unset();
                }
            }
        }
        void intNode() override
        {
            if (source.isSet())
            {
                dest.setInt(source.getInt());
            }
            else
            {
                if (dest.isSet())
                {
                    // TODO : unset
                    // dest.unset();
                }
            }
        }
        void floatNode() override
        {
            if (source.isSet())
            {
                dest.setFloat(source.getFloat());
            }
            else
            {
                if (dest.isSet())
                {
                    // TODO : unset
                    // dest.unset();
                }
            }
        }
        void stringNode() override
        {
            if (source.isSet())
            {
                dest.setString(source.getString());
            }
            else
            {
                if (dest.isSet())
                {
                    // TODO : unset
                    // dest.unset();
                }
            }
        }
        void entityRefNode() override
        {
            if (source.isSet())
            {
                dest.setEntityRef(source.getEntityRef());
            }
            else
            {
                if (dest.isSet())
                {
                    // TODO : unset
                    // dest.unset();
                }
            }
        }
    };
} // namespace Ent
