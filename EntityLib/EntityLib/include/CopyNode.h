#pragma once

#include "EntVisitor.h"

namespace Ent
{

    class CopyNode : public NodeVisitor
    {
        Cursor& source;
        Cursor& dest;

    public:
        CopyNode(Cursor& _source, Cursor& _dest)
            : source(_source)
            , dest(_dest)
        {
        }
        virtual void inObject()
        {
            // ENTLIB_ASSERT(nodes.back()->getFieldNames().size() == expl.get);
        }
        virtual void inObjectField(char const* key, Cursor const&)
        {
            dest.enterObjectField(key);
        }
        virtual void outObjectField()
        {
            dest.exit();
        }
        virtual void outObject()
        {
        }
        virtual void inUnion(char const* type)
        {
            if (source.isSet())
                dest.setUnionType(type);
            dest.enterUnionData(type);
        }
        virtual void outUnion()
        {
            dest.exit();
        }
        virtual void inMap()
        {
        }
        virtual void outMap()
        {
        }
        virtual void inMapElement(char const* key)
        {
            dest.enterMapItem(key);
        }
        virtual void inMapElement(int64_t key)
        {
            dest.enterMapItem(key);
        }
        virtual void outMapElement()
        {
            dest.exit();
        }
        virtual void inPrimSet(Ent::DataType)
        {
        }
        virtual void inArrayElement(size_t i)
        {
            dest.enterArrayItem(i);
        }
        virtual void outArrayElement()
        {
            dest.exit();
        }
        virtual void key([[maybe_unused]] char const* key)
        {
            dest.insertPrimSetKey(key);
        }
        virtual void key([[maybe_unused]] int64_t key)
        {
            dest.insertPrimSetKey(key);
        }
        virtual void outPrimSet()
        {
        }
        virtual void inUnionSet()
        {
        }
        virtual void inUnionSetElement(char const* type)
        {
            dest.enterUnionSetItem(type);
        }
        virtual void outUnionSetElement()
        {
            dest.exit();
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
        virtual void inObjectSetElement(char const* key)
        {
            dest.enterObjectSetItem(key);
        }
        virtual void inObjectSetElement(int64_t key)
        {
            dest.enterObjectSetItem(key);
        }
        virtual void outObjectSetElement()
        {
            dest.exit();
        }
        virtual void inArray()
        {
            if (source.isSet())
                dest.setSize(source.size());
        }
        virtual void outArray()
        {
        }
        virtual void nullNode()
        {
        }
        virtual void boolNode()
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
        virtual void intNode()
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
        virtual void floatNode()
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
        virtual void stringNode()
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
        virtual void entityRefNode()
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
