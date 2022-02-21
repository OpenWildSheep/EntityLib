#pragma once

#include <deque>

#include "Visitor.h"
#include "Handler.h"

namespace Ent
{
    /// Deep copy from a Node to an empty Node
    class CopyToEmptyNode : public RecursiveVisitor
    {
        Handler* m_root = nullptr;
        std::deque<Handler> m_dest;

        Handler& back()
        {
            if (m_dest.empty())
            {
                return *m_root;
            }
            else
            {
                return m_dest.back();
            }
        }

    public:
        CopyToEmptyNode(Handler& _dest)
            : m_root(&_dest)
        {
        }
        void inObject([[maybe_unused]] Handler& m_source) override
        {
            if (auto instanceOf = m_source.getInstanceOf())
            {
                back().setInstanceOf(instanceOf);
            }
        }
        bool inObjectField([[maybe_unused]] Handler& m_source, char const* _key) override
        {
            m_dest.push_back(back().enterObjectField(_key));
            return true;
        }
        void outObjectField([[maybe_unused]] Handler& m_source, [[maybe_unused]] char const* _key) override
        {
            m_dest.pop_back();
        }
        void inUnion([[maybe_unused]] Handler& m_source, char const* _type) override
        {
            if (m_source.isSet())
            {
                back().setUnionType(_type);
            }
            m_dest.push_back(back().enterUnionData(_type));
        }
        void outUnion([[maybe_unused]] Handler& m_source) override
        {
            m_dest.pop_back();
        }
        void inMapElement([[maybe_unused]] Handler& m_source, char const* _key) override
        {
            m_dest.push_back(back().enterMapItem(_key));
        }
        void inMapElement([[maybe_unused]] Handler& m_source, int64_t _key) override
        {
            m_dest.push_back(back().enterMapItem(_key));
        }
        void outMapElement([[maybe_unused]] Handler& m_source) override
        {
            m_dest.pop_back();
        }
        void inArrayElement([[maybe_unused]] Handler& m_source, size_t _index) override
        {
            m_dest.push_back(back().enterArrayItem(_index));
        }
        void outArrayElement([[maybe_unused]] Handler& m_source) override
        {
            m_dest.pop_back();
        }
        void key([[maybe_unused]] Handler& m_source, char const* _key) override
        {
            back().insertPrimSetKey(_key);
        }
        void key([[maybe_unused]] Handler& m_source, int64_t _key) override
        {
            back().insertPrimSetKey(_key);
        }
        void inUnionSetElement([[maybe_unused]] Handler& m_source, char const* _type) override
        {
            m_dest.push_back(back().enterUnionSetItem(_type));
            if (m_source.isSet())
            {
                back().buildPath(); // Force it to set
            }
        }
        void outUnionSetElement([[maybe_unused]] Handler& m_source) override
        {
            m_dest.pop_back();
        }
        void inObjectSetElement([[maybe_unused]] Handler& m_source, char const* _key) override
        {
            m_dest.push_back(back().enterObjectSetItem(_key));
        }
        void inObjectSetElement([[maybe_unused]] Handler& m_source, int64_t _key) override
        {
            m_dest.push_back(back().enterObjectSetItem(_key));
        }
        void outObjectSetElement([[maybe_unused]] Handler& m_source) override
        {
            m_dest.pop_back();
        }
        void inArray([[maybe_unused]] Handler& m_source) override
        {
            if (m_source.isSet())
            {
                back().setSize(m_source.size());
            }
        }
        void boolNode([[maybe_unused]] Handler& m_source) override
        {
            if (m_source.isSet())
            {
                back().setBool(m_source.getBool());
            }
        }
        void intNode([[maybe_unused]] Handler& m_source) override
        {
            if (m_source.isSet())
            {
                back().setInt(m_source.getInt());
            }
        }
        void floatNode([[maybe_unused]] Handler& m_source) override
        {
            if (m_source.isSet())
            {
                back().setFloat(m_source.getFloat());
            }
        }
        void stringNode([[maybe_unused]] Handler& m_source) override
        {
            if (m_source.isSet())
            {
                back().setString(m_source.getString());
            }
        }
        void entityRefNode([[maybe_unused]] Handler& m_source) override
        {
            if (m_source.isSet())
            {
                back().setEntityRef(m_source.getEntityRef());
            }
        }
    };
} // namespace Ent
