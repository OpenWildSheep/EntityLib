#pragma once

#include <vector>
#include <ciso646>

#include "Visitor.h"
#include "Property.h"

namespace Ent
{
    /// Deep copy from a Node to an empty Node
    class CopyProperty : public RecursiveVisitor
    {
        std::vector<Property> m_dest;
        OverrideValueSource m_overrideValueSource = {};
        CopyMode m_copyMode = {};
        bool m_copyRootInstanceOf = false;

        [[nodiscard]] Property const& _back()
        {
            return m_dest.back();
        }

        [[nodiscard]] Property const& _back() const
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

        [[nodiscard]] bool doNeedCopy(Property const& _source) const
        {
            auto checkOVS = [this, &_source]
            {
                switch (m_overrideValueSource)
                {
                case OverrideValueSource::OverrideOrPrefab: return not _source.isDefault();
                case OverrideValueSource::Override: return _source.isSet();
                case OverrideValueSource::Any: return true;
                }
                ENTLIB_LOGIC_ERROR("Wrong OverrideValueSource given to CopyProperty");
            };
            auto checkCopyMode = [this, &_source]
            {
                if (not _source.getSchema()->isPrimitive())
                {
                    return true;
                }
                switch (m_copyMode)
                {
                case CopyMode::CopyOverride:
                    return _source.hasOverride() or not _source.sameValue(_back());
                case CopyMode::MinimalOverride: return not _source.sameValue(_back());
                }
                ENTLIB_LOGIC_ERROR("Wrong CopyMode given to CopyProperty");
            };
            return checkOVS() && checkCopyMode();
        }

    public:
        CopyProperty(
            Property _dest,
            OverrideValueSource _overrideValueSource,
            CopyMode _copyMode,
            bool _copyRootInstanceOf = true)
            : m_dest({std::move(_dest)})
            , m_overrideValueSource(_overrideValueSource)
            , m_copyMode(_copyMode)
            , m_copyRootInstanceOf(_copyRootInstanceOf)
        {
        }
        void inObject(Property const& m_source) override
        {
            if (m_overrideValueSource == OverrideValueSource::Override
                and (m_copyRootInstanceOf or m_dest.size() > 1))
            {
                if (auto const* const instanceOf = m_source.getInstanceOf())
                {
                    _back().resetInstanceOf(instanceOf);
                }
            }
        }
        bool inObjectField([[maybe_unused]] Property const& m_source, char const* _key) override
        {
            _push(_back().getObjectField(_key));
            if (doNeedCopy(m_source))
            {
                return true;
            }
            // If no need to copy, no need to iterate
            _pop();
            return false;
        }
        void outObjectField(
            [[maybe_unused]] Property const& m_source, [[maybe_unused]] char const* _key) override
        {
            _pop();
        }
        void inUnion(Property const& m_source, char const* _type) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setUnionType(_type);
            }
            _push(_back().forceGetUnionData(_type).first);
        }
        void outUnion([[maybe_unused]] Property const& m_source) override
        {
            _pop();
        }
        void inMapElement([[maybe_unused]] Property const& m_source, char const* _key) override
        {
            _push(_back().forceGetMapItem(_key).first);
            if (doNeedCopy(m_source))
            {
                _back().buildPath(); // Force it to set
            }
        }
        void inMapElement([[maybe_unused]] Property const& m_source, int64_t _key) override
        {
            _push(_back().forceGetMapItem(_key).first);
        }
        void outMapElement([[maybe_unused]] Property const& m_source) override
        {
            _pop();
        }
        void inArrayElement([[maybe_unused]] Property const& m_source, size_t _index) override
        {
            _push(_back().getArrayItem(_index));
        }
        void outArrayElement([[maybe_unused]] Property const& m_source) override
        {
            _pop();
        }
        void key([[maybe_unused]] Property const& m_source, char const* _key) override
        {
            _back().insertPrimSetKey(_key);
            if (doNeedCopy(m_source))
            {
                _back().buildPath(); // Force it to set
            }
        }
        void key([[maybe_unused]] Property const& m_source, int64_t _key) override
        {
            _back().insertPrimSetKey(_key);
        }
        void inUnionSetElement(Property const& m_source, char const* _type) override
        {
            _push(_back().forceGetUnionSetItem(_type).first);
            if (doNeedCopy(m_source))
            {
                _back().buildPath(); // Force it to set
            }
        }
        void outUnionSetElement([[maybe_unused]] Property const& m_source) override
        {
            _pop();
        }
        void inObjectSetElement([[maybe_unused]] Property const& m_source, char const* _key) override
        {
            ENTLIB_ASSERT(_back().getDataKind() == DataKind::objectSet);
            _push(_back().forceGetObjectSetItem(_key).first);
            if (doNeedCopy(m_source))
            {
                _back().buildPath(); // Force it to set
            }
        }
        void inObjectSetElement([[maybe_unused]] Property const& m_source, int64_t _key) override
        {
            ENTLIB_ASSERT(_back().getDataKind() == DataKind::objectSet);
            _push(_back().forceGetObjectSetItem(_key).first);
            if (doNeedCopy(m_source))
            {
                _back().buildPath(); // Force it to set
            }
        }
        void outObjectSetElement([[maybe_unused]] Property const& m_source) override
        {
            _pop();
        }
        void inArray(Property const& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setSize(m_source.size());
            }
        }
        void outMap([[maybe_unused]] Property const& m_source) override
        {
            if (m_overrideValueSource == OverrideValueSource::Override)
            {
                switch (m_source.getMapKeyKind())
                {
                case DataKind::integer:
                    for (auto const& removed : m_source.getMapRemovedKeysInt())
                    {
                        _back().eraseMapItem(removed);
                    }
                    break;
                case DataKind::string: [[fallthrough]];
                case DataKind::entityRef:
                    for (auto const& removed : m_source.getMapRemovedKeysString())
                    {
                        _back().eraseMapItem(removed);
                    }
                    break;
                default: ENTLIB_LOGIC_ERROR("Unexpected OverrideValueSource");
                }
            }
        }
        void outObjectSet([[maybe_unused]] Property const& m_source) override
        {
            if (m_overrideValueSource == OverrideValueSource::Override)
            {
                switch (m_source.getObjectSetKeyKind())
                {
                case DataKind::integer:
                    for (auto const& removed : m_source.getObjectSetRemovedKeysInt())
                    {
                        _back().eraseObjectSetItem(removed);
                    }
                    break;
                case DataKind::string: [[fallthrough]];
                case DataKind::entityRef:
                    for (auto const& removed : m_source.getObjectSetRemovedKeysString())
                    {
                        _back().eraseObjectSetItem(removed);
                    }
                    break;
                default: ENTLIB_LOGIC_ERROR("Unexpected OverrideValueSource");
                }
            }
        }
        void outUnionSet([[maybe_unused]] Property const& m_source) override
        {
            if (m_overrideValueSource == OverrideValueSource::Override)
            {
                for (auto&& [removed, schema] : m_source.getUnionSetRemovedKeysString())
                {
                    _back().eraseUnionSetItem(removed);
                }
            }
        }
        void boolProperty(Property const& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setBool(m_source.getBool());
            }
        }
        void intProperty(Property const& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setInt(m_source.getInt());
            }
        }
        void floatProperty(Property const& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setFloat(m_source.getFloat());
            }
        }
        void stringProperty(Property const& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setString(m_source.getString());
            }
        }
        void entityRefProperty(Property const& m_source) override
        {
            if (doNeedCopy(m_source))
            {
                _back().setEntityRef(m_source.getEntityRef());
            }
        }
    };
} // namespace Ent
