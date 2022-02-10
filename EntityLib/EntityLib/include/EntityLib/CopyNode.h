#pragma once

#include "Visitor.h"

#include <deque>

namespace Ent
{
    /// Deep copy from a Node to an empty Node
    class CopyToEmptyNode : public RecursiveVisitor
    {
        std::deque<Layer> m_dest;

    public:
        CopyToEmptyNode(Layer _dest)
            : m_dest({std::move(_dest)})
        {
        }
        void inObject([[maybe_unused]] Layer& m_source) override
        {
            if (auto instanceOf = m_source.getInstanceOf())
            {
                m_dest.back().setInstanceOf(instanceOf);
            }
        }
        bool inObjectField([[maybe_unused]] Layer& m_source, char const* _key) override
        {
            m_dest.push_back(m_dest.back().enterObjectField(_key));
            return true;
        }
        void outObjectField([[maybe_unused]] Layer& m_source, [[maybe_unused]] char const* _key) override
        {
            m_dest.pop_back();
        }
        void inUnion([[maybe_unused]] Layer& m_source, char const* _type) override
        {
            if (m_source.isSet())
            {
                m_dest.back().setUnionType(_type);
            }
            m_dest.push_back(m_dest.back().enterUnionData(_type));
        }
        void outUnion([[maybe_unused]] Layer& m_source) override
        {
            m_dest.pop_back();
        }
        void inMapElement([[maybe_unused]] Layer& m_source, char const* _key) override
        {
            m_dest.push_back(m_dest.back().enterMapItem(_key));
        }
        void inMapElement([[maybe_unused]] Layer& m_source, int64_t _key) override
        {
            m_dest.push_back(m_dest.back().enterMapItem(_key));
        }
        void outMapElement([[maybe_unused]] Layer& m_source) override
        {
            m_dest.pop_back();
        }
        void inArrayElement([[maybe_unused]] Layer& m_source, size_t _index) override
        {
            m_dest.push_back(m_dest.back().enterArrayItem(_index));
        }
        void outArrayElement([[maybe_unused]] Layer& m_source) override
        {
            m_dest.pop_back();
        }
        void key([[maybe_unused]] Layer& m_source, char const* _key) override
        {
            m_dest.back().insertPrimSetKey(_key);
        }
        void key([[maybe_unused]] Layer& m_source, int64_t _key) override
        {
            m_dest.back().insertPrimSetKey(_key);
        }
        void inUnionSetElement([[maybe_unused]] Layer& m_source, char const* _type) override
        {
            m_dest.push_back(m_dest.back().enterUnionSetItem(_type));
            if (m_source.isSet())
            {
                m_dest.back().buildPath(); // Force it to set
            }
        }
        void outUnionSetElement([[maybe_unused]] Layer& m_source) override
        {
            m_dest.pop_back();
        }
        void inObjectSetElement([[maybe_unused]] Layer& m_source, char const* _key) override
        {
            m_dest.push_back(m_dest.back().enterObjectSetItem(_key));
        }
        void inObjectSetElement([[maybe_unused]] Layer& m_source, int64_t _key) override
        {
            m_dest.push_back(m_dest.back().enterObjectSetItem(_key));
        }
        void outObjectSetElement([[maybe_unused]] Layer& m_source) override
        {
            m_dest.pop_back();
        }
        void inArray([[maybe_unused]] Layer& m_source) override
        {
            if (m_source.isSet())
            {
                m_dest.back().setSize(m_source.size());
            }
        }
        void boolNode([[maybe_unused]] Layer& m_source) override
        {
            if (m_source.isSet())
            {
                m_dest.back().setBool(m_source.getBool());
            }
        }
        void intNode([[maybe_unused]] Layer& m_source) override
        {
            if (m_source.isSet())
            {
                m_dest.back().setInt(m_source.getInt());
            }
        }
        void floatNode([[maybe_unused]] Layer& m_source) override
        {
            if (m_source.isSet())
            {
                m_dest.back().setFloat(m_source.getFloat());
            }
        }
        void stringNode([[maybe_unused]] Layer& m_source) override
        {
            if (m_source.isSet())
            {
                m_dest.back().setString(m_source.getString());
            }
        }
        void entityRefNode([[maybe_unused]] Layer& m_source) override
        {
            if (m_source.isSet())
            {
                m_dest.back().setEntityRef(m_source.getEntityRef());
            }
        }
    };
} // namespace Ent
