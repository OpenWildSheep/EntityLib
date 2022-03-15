#pragma once

#include <vector>

#include "Visitor.h"
#include "Property.h"

namespace Ent
{
    /// Deep copy from a Node to an empty Node
    class CopyToEmptyNode : public RecursiveVisitor
    {
        std::vector<Property> m_dest;

        [[nodiscard]] Property& _back()
        {
            return m_dest.back();
        }

        void _push(Property _prop)
        {
            m_dest.push_back(std::move(_prop));
        }

        void _pop()
        {
            m_dest.pop_back();
        }

    public:
        CopyToEmptyNode(Property _dest)
            : m_dest({std::move(_dest)})
        {
        }
        void inObject(Property& m_source) override
        {
            if (auto instanceOf = m_source.getInstanceOf())
            {
                _back().setInstanceOf(instanceOf);
            }
        }
        bool inObjectField(Property& m_source, char const* _key) override
        {
            _push(_back().enterObjectField(_key));
            return true;
        }
        void outObjectField(Property& m_source, char const* _key) override
        {
            _pop();
        }
        void inUnion(Property& m_source, char const* _type) override
        {
            if (m_source.isSet())
            {
                _back().setUnionType(_type);
            }
            _push(_back().enterUnionData(_type));
        }
        void outUnion(Property& m_source) override
        {
            _pop();
        }
        void inMapElement(Property& m_source, char const* _key) override
        {
            _push(_back().enterMapItem(_key));
        }
        void inMapElement(Property& m_source, int64_t _key) override
        {
            _push(_back().enterMapItem(_key));
        }
        void outMapElement(Property& m_source) override
        {
            _pop();
        }
        void inArrayElement(Property& m_source, size_t _index) override
        {
            _push(_back().enterArrayItem(_index));
        }
        void outArrayElement(Property& m_source) override
        {
            _pop();
        }
        void key(Property& m_source, char const* _key) override
        {
            _back().insertPrimSetKey(_key);
        }
        void key(Property& m_source, int64_t _key) override
        {
            _back().insertPrimSetKey(_key);
        }
        void inUnionSetElement(Property& m_source, char const* _type) override
        {
            _push(_back().enterUnionSetItem(_type));
            if (m_source.isSet())
            {
                _back().buildPath(); // Force it to set
            }
        }
        void outUnionSetElement(Property& m_source) override
        {
            _pop();
        }
        void inObjectSetElement(Property& m_source, char const* _key) override
        {
            _push(_back().enterObjectSetItem(_key));
        }
        void inObjectSetElement(Property& m_source, int64_t _key) override
        {
            _push(_back().enterObjectSetItem(_key));
        }
        void outObjectSetElement(Property& m_source) override
        {
            _pop();
        }
        void inArray(Property& m_source) override
        {
            if (m_source.isSet())
            {
                _back().setSize(m_source.size());
            }
        }
        void boolProperty(Property& m_source) override
        {
            if (m_source.isSet())
            {
                _back().setBool(m_source.getBool());
            }
        }
        void intProperty(Property& m_source) override
        {
            if (m_source.isSet())
            {
                _back().setInt(m_source.getInt());
            }
        }
        void floatProperty(Property& m_source) override
        {
            if (m_source.isSet())
            {
                _back().setFloat(m_source.getFloat());
            }
        }
        void stringProperty(Property& m_source) override
        {
            if (m_source.isSet())
            {
                _back().setString(m_source.getString());
            }
        }
        void entityRefProperty(Property& m_source) override
        {
            if (m_source.isSet())
            {
                _back().setEntityRef(m_source.getEntityRef());
            }
        }
    };
} // namespace Ent
