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
                _back().changeInstanceOf(instanceOf);
            }
        }
        bool inObjectField([[maybe_unused]] Property& m_source, char const* _key) override
        {
            _push(_back().getObjectField(_key));
            return true;
        }
        void outObjectField([[maybe_unused]] Property& m_source, [[maybe_unused]] char const* _key) override
        {
            _pop();
        }
        void inUnion(Property& m_source, char const* _type) override
        {
            if (m_source.isSet())
            {
                _back().setUnionType(_type);
            }
            _push(_back().getUnionData(_type));
        }
        void outUnion([[maybe_unused]] Property& m_source) override
        {
            _pop();
        }
        void inMapElement([[maybe_unused]] Property& m_source, char const* _key) override
        {
            _push(_back().getMapItem(_key));
        }
        void inMapElement([[maybe_unused]] Property& m_source, int64_t _key) override
        {
            _push(_back().getMapItem(_key));
        }
        void outMapElement([[maybe_unused]] Property& m_source) override
        {
            _pop();
        }
        void inArrayElement([[maybe_unused]] Property& m_source, size_t _index) override
        {
            _push(_back().getArrayItem(_index));
        }
        void outArrayElement([[maybe_unused]] Property& m_source) override
        {
            _pop();
        }
        void key([[maybe_unused]] Property& m_source, char const* _key) override
        {
            _back().insertPrimSetKey(_key);
        }
        void key([[maybe_unused]] Property& m_source, int64_t _key) override
        {
            _back().insertPrimSetKey(_key);
        }
        void inUnionSetElement(Property& m_source, char const* _type) override
        {
            _push(_back().getUnionSetItem(_type));
            if (m_source.isSet())
            {
                _back().buildPath(); // Force it to set
            }
        }
        void outUnionSetElement([[maybe_unused]] Property& m_source) override
        {
            _pop();
        }
        void inObjectSetElement([[maybe_unused]] Property& m_source, char const* _key) override
        {
            _push(_back().getObjectSetItem(_key));
        }
        void inObjectSetElement([[maybe_unused]] Property& m_source, int64_t _key) override
        {
            _push(_back().getObjectSetItem(_key));
        }
        void outObjectSetElement([[maybe_unused]] Property& m_source) override
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
