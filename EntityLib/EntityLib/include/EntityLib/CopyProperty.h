#pragma once

#include <vector>

#include "Visitor.h"
#include "Property.h"

namespace Ent
{
    /// Deep copy from a Node to an empty Node
    class CopyProperty : public RecursiveVisitor
    {
        std::vector<Property> m_dest;
        OverrideValueSource m_overrideValueSource = {};
        bool m_copyRootInstanceOf = false;
        bool m_isKeyField = false;

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

        bool doNeedCopy(Property const& _source) const
        {
            auto checkOVS = [this, &_source]
            {
                switch (m_overrideValueSource)
                {
                case OverrideValueSource::OverrideOrPrefab: return not _source.isDefault();
                case OverrideValueSource::Override: return _source.isSet();
                case OverrideValueSource::Any: return true;
                }
                throw ContextException("Wrong OverrideValueSource given to CopyToEmptyNode");
            };
            return !m_isKeyField && checkOVS();
        }

    public:
        CopyProperty(
            Property _dest, OverrideValueSource _overrideValueSource, bool _copyRootInstanceOf = true)
            : m_dest({std::move(_dest)})
            , m_overrideValueSource(_overrideValueSource)
            , m_copyRootInstanceOf(_copyRootInstanceOf)
        {
        }
        void inObject(Property& m_source) override
        {
            if (m_overrideValueSource == OverrideValueSource::Override
                and (m_copyRootInstanceOf or m_dest.size() > 1))
            {
                if (auto const instanceOf = m_source.getInstanceOf())
                {
                    _back().resetInstanceOf(instanceOf);
                }
            }
        }
        bool inObjectField([[maybe_unused]] Property& m_source, char const* _key) override
        {
            if (Property const parentProp = m_source.getParent(); parentProp.hasValue())
            {
                if (Property const grandParentProp = parentProp.getParent();
                    grandParentProp.hasValue())
                {
                    auto const grandParentKind = grandParentProp.getDataKind();
                    if (grandParentKind == DataKind::objectSet)
                    {
                        auto const& meta =
                            std::get<Subschema::ArrayMeta>(grandParentProp.getSchema()->meta);
                        if (meta.keyField.has_value() and *meta.keyField == _key)
                        {
                            m_isKeyField = true;
                        }
                    }
                }
            }

            _push(_back().getObjectField(_key));
            return true;
        }
        void outObjectField([[maybe_unused]] Property& m_source, [[maybe_unused]] char const* _key) override
        {
            _pop();
            m_isKeyField = false;
        }
        void inUnion(Property& m_source, char const* _type) override
        {
            if (doNeedCopy(m_source))
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
            if (doNeedCopy(m_source))
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
            ENTLIB_ASSERT(_back().getDataKind() == DataKind::objectSet);
            _push(_back().getObjectSetItem(_key));
        }
        void inObjectSetElement([[maybe_unused]] Property& m_source, int64_t _key) override
        {
            ENTLIB_ASSERT(_back().getDataKind() == DataKind::objectSet);
            _push(_back().getObjectSetItem(_key));
        }
        void outObjectSetElement([[maybe_unused]] Property& m_source) override
        {
            _pop();
        }
        void inArray(Property& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setSize(m_source.size());
            }
        }
        void outMap([[maybe_unused]] Property& m_source) override
        {
            if (m_overrideValueSource == OverrideValueSource::Override)
            {
                switch (m_source.getMapKeyType())
                {
                case DataType::integer:
                    for (auto& removed : m_source.getMapRemovedKeysInt())
                    {
                        _back().eraseMapItem(removed);
                    }
                    break;
                case DataType::string: [[fallthrough]];
                case DataType::entityRef:
                    for (auto& removed : m_source.getMapRemovedKeysString())
                    {
                        _back().eraseMapItem(removed);
                    }
                    break;
                default: ENTLIB_LOGIC_ERROR("Unexpected OverrideValueSource");
                }
            }
        }
        void outObjectSet([[maybe_unused]] Property& m_source) override
        {
            if (m_overrideValueSource == OverrideValueSource::Override)
            {
                switch (m_source.getObjectSetKeyType())
                {
                case DataType::integer:
                    for (auto& removed : m_source.getObjectSetRemovedKeysInt())
                    {
                        _back().eraseObjectSetItem(removed);
                    }
                    break;
                case DataType::string: [[fallthrough]];
                case DataType::entityRef:
                    for (auto& removed : m_source.getObjectSetRemovedKeysString())
                    {
                        _back().eraseObjectSetItem(removed);
                    }
                    break;
                default: ENTLIB_LOGIC_ERROR("Unexpected OverrideValueSource");
                }
            }
        }
        void outUnionSet([[maybe_unused]] Property& m_source) override
        {
            if (m_overrideValueSource == OverrideValueSource::Override)
            {
                for (auto&& [removed, schema] : m_source.getUnionSetRemovedKeysString())
                {
                    _back().eraseUnionSetItem(removed);
                }
            }
        }
        void boolProperty(Property& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setBool(m_source.getBool());
            }
        }
        void intProperty(Property& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setInt(m_source.getInt());
            }
        }
        void floatProperty(Property& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setFloat(m_source.getFloat());
            }
        }
        void stringProperty(Property& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setString(m_source.getString());
            }
        }
        void entityRefProperty(Property& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setEntityRef(m_source.getEntityRef());
            }
        }
    };
} // namespace Ent
