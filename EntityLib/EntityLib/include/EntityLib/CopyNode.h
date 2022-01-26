#pragma once

#include "Visitor.h"

namespace Ent
{
    /// Deep copy from a Node to an empty Node
    class CopyToEmptyNode : public RecursiveVisitor
    {
        Cursor& m_source;
        Cursor& m_dest;

    public:
        CopyToEmptyNode(Cursor& _source, Cursor& _dest)
            : m_source(_source)
            , m_dest(_dest)
        {
        }
        void inObject() override
        {
            m_dest.setInstanceOf(m_source.getInstanceOf());
        }
        bool inObjectField(char const* _key) override
        {
            m_dest.enterObjectField(_key);
            return true;
        }
        void outObjectField([[maybe_unused]] char const* _key) override
        {
            m_dest.exit();
        }
        void inUnion(char const* _type) override
        {
            if (m_source.isSet())
            {
                m_dest.setUnionType(_type);
            }
            m_dest.enterUnionData(_type);
        }
        void outUnion() override
        {
            m_dest.exit();
        }
        void inMapElement(char const* _key) override
        {
            m_dest.enterMapItem(_key);
        }
        void inMapElement(int64_t _key) override
        {
            m_dest.enterMapItem(_key);
        }
        void outMapElement() override
        {
            m_dest.exit();
        }
        void inArrayElement(size_t _index) override
        {
            m_dest.enterArrayItem(_index);
        }
        void outArrayElement() override
        {
            m_dest.exit();
        }
        void key(char const* _key) override
        {
            m_dest.insertPrimSetKey(_key);
        }
        void key(int64_t _key) override
        {
            m_dest.insertPrimSetKey(_key);
        }
        void inUnionSetElement(char const* _type) override
        {
            m_dest.enterUnionSetItem(_type);
            if (m_source.isSet())
            {
                m_dest.buildPath(); // Force it to set
            }
        }
        void outUnionSetElement() override
        {
            m_dest.exit();
        }
        void inObjectSetElement(char const* _key) override
        {
            m_dest.enterObjectSetItem(_key);
        }
        void inObjectSetElement(int64_t _key) override
        {
            m_dest.enterObjectSetItem(_key);
        }
        void outObjectSetElement() override
        {
            m_dest.exit();
        }
        void inArray() override
        {
            if (m_source.isSet())
            {
                m_dest.setSize(m_source.size());
            }
        }
        void boolNode() override
        {
            if (m_source.isSet())
            {
                m_dest.setBool(m_source.getBool());
            }
        }
        void intNode() override
        {
            if (m_source.isSet())
            {
                m_dest.setInt(m_source.getInt());
            }
        }
        void floatNode() override
        {
            if (m_source.isSet())
            {
                m_dest.setFloat(m_source.getFloat());
            }
        }
        void stringNode() override
        {
            if (m_source.isSet())
            {
                m_dest.setString(m_source.getString());
            }
        }
        void entityRefNode() override
        {
            if (m_source.isSet())
            {
                m_dest.setEntityRef(m_source.getEntityRef());
            }
        }
    };
} // namespace Ent
