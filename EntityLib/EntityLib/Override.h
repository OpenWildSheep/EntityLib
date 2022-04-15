#pragma once

#include <optional>
#include <string>

#pragma warning(push, 0)
#include "MemoryProfiler.h"
#include "include/EntityLibCore.h"
#pragma warning(pop)

namespace Ent
{
    struct MemoryProfiler;

    /// @brief Value location inside an \e Override<T>
    enum class OverrideValueLocation
    {
        /// Override value comes from default value.
        Default,
        /// Override value comes from the prefab.
        Prefab,
        /// Override value comes from the instance.
        Override
    };

    template <typename V>
    struct Override
    {
        Override()
            : m_hasPrefab(false)
            , m_hasOverride(false)
        {
        }
        Override(V _defaultValue, std::optional<V> _prefabValue, std::optional<V> _overrideValue)
            : m_defaultValue(std::move(_defaultValue))
        {
            m_hasPrefab = _prefabValue.has_value();
            m_hasOverride = _overrideValue.has_value();
            if (m_hasPrefab)
            {
                m_prefabValue = std::move(*_prefabValue);
            }
            if (m_hasOverride)
            {
                m_overrideValue = std::move(*_overrideValue);
            }
        }
        Override(V _defaultValue, V _prefabValue, V _overrideValue, bool _hasPrefab, bool _hasOverride)
            : m_defaultValue(std::move(_defaultValue))
            , m_prefabValue(std::move(_prefabValue))
            , m_overrideValue(std::move(_overrideValue))
            , m_hasPrefab(_hasPrefab)
            , m_hasOverride(_hasOverride)
        {
        }
        Override(V _defaultValue, V const* _prefabValue, V const* _overrideValue)
            : m_defaultValue(std::move(_defaultValue))
            , m_hasPrefab(_prefabValue != nullptr)
            , m_hasOverride(_overrideValue != nullptr)
        {
            if (m_hasPrefab)
            {
                m_prefabValue = *_prefabValue;
            }
            if (m_hasOverride)
            {
                m_overrideValue = *_overrideValue;
            }
        }
        Override(V _defaultVal)
            : m_defaultValue(_defaultVal)
            , m_hasPrefab(false)
            , m_hasOverride(false)
        {
        }

        V const& get() const;

        void set(V _newVal);

        bool isSet() const;

        void unset();

        Override<V> detach() const;

        Override<V> makeInstanceOf() const;

        Override<V> clone() const
        {
            return *this;
        }

        /// makeInstanceOf, then set a value
        Override<V> makeOverridedInstanceOf(std::optional<V> _overrideValue) const
        {
            Override<V> result = makeInstanceOf();
            result.m_hasOverride = _overrideValue.has_value();
            if (result.m_hasOverride)
            {
                result.m_overrideValue = *_overrideValue;
            }
            else
            {
                result.m_overrideValue = {};
            }
            return result;
        }

        /// True if no value was set in template or in instance
        bool isDefault() const
        {
            return !(m_hasPrefab || m_hasOverride);
        }

        void computeMemory(MemoryProfiler& prof) const;

        // bool hasOverride() const;

        std::optional<std::reference_wrapper<V>> getRaw(OverrideValueLocation _location)
        {
            switch (_location)
            {
            case OverrideValueLocation::Default: return m_defaultValue;
            case OverrideValueLocation::Prefab:
                return m_hasPrefab ? std::optional<std::reference_wrapper<V>>{m_prefabValue} :
                                     std::nullopt;
            case OverrideValueLocation::Override:
                return m_hasOverride ? std::optional<std::reference_wrapper<V>>{m_overrideValue} :
                                       std::nullopt;
            default: return std::nullopt;
            }
        }

        std::optional<std::reference_wrapper<V const>> getRaw(OverrideValueLocation _location) const
        {
            switch (_location)
            {
            case OverrideValueLocation::Default: return m_defaultValue;
            case OverrideValueLocation::Prefab:
                return m_hasPrefab ? std::optional<std::reference_wrapper<V const>>{m_prefabValue} :
                                     std::nullopt;
            case OverrideValueLocation::Override:
                return m_hasOverride ?
                           std::optional<std::reference_wrapper<V const>>{m_overrideValue} :
                           std::nullopt;
            default: return std::nullopt;
            }
        }

        V& getPrefab()
        {
            return m_hasPrefab ? m_prefabValue : m_defaultValue;
        }
        V const& getPrefab() const
        {
            return m_hasPrefab ? m_prefabValue : m_defaultValue;
        }

        V& getDefault()
        {
            return m_defaultValue;
        }
        V const& getDefault() const
        {
            return m_defaultValue;
        }

        void applyAllValues(Override& _dest, CopyMode _copyMode) const
        {
            switch (_copyMode)
            {
            case CopyMode::CopyOverride:
                if (isSet())
                { // Report the override when there is one
                    _dest.set(get());
                }
                else if (get() != _dest.get())
                {
                    _dest.set(get()); // If no override, minimize modification in _dest
                }
                break;
            case CopyMode::MinimalOverride:
                // Try to set a minimum of values
                _dest.unset();
                if (get() != _dest.get())
                {
                    _dest.set(get());
                }
                break;
            }
        }

        bool hasPrefabValue() const
        {
            return m_hasPrefab;
        }

        bool hasOverride() const
        {
            return m_hasOverride;
        }

        bool hasDefaultValue() const
        {
            return !hasPrefabValue() && !hasOverride();
        }

        void setPrefab(V _newVal)
        {
            m_hasPrefab = true;
            m_prefabValue = std::move(_newVal);
        }

        void setDefault(V _newVal)
        {
            m_defaultValue = std::move(_newVal);
        }

    private:
        V m_defaultValue{};
        V m_prefabValue{};
        V m_overrideValue{};
        bool m_hasPrefab : 1; // No default init for bitfield until c++20
        bool m_hasOverride : 1;
    };

    template <typename V>
    V const& Override<V>::get() const
    {
        if (m_hasOverride)
        {
            return m_overrideValue;
        }
        if (m_hasPrefab)
        {
            return m_prefabValue;
        }
        return m_defaultValue;
    }

    template <typename V>
    void Override<V>::set(V _newVal)
    {
        m_overrideValue = std::move(_newVal);
        m_hasOverride = true;
    }

    template <typename V>
    bool Override<V>::isSet() const
    {
        return m_hasOverride;
    }

    template <typename V>
    void Override<V>::unset()
    {
        m_hasOverride = false;
        m_overrideValue = {};
    }

    template <typename V>
    Override<V> Override<V>::detach() const
    {
        if (m_hasOverride)
        {
            return Override<V>(m_defaultValue, V{}, m_overrideValue, false, m_hasOverride);
        }
        return Override<V>(m_defaultValue, V{}, m_prefabValue, false, m_hasPrefab);
    }

    template <typename V>
    Override<V> Override<V>::makeInstanceOf() const
    {
        if (m_hasOverride)
        {
            return Override<V>(m_defaultValue, m_overrideValue, V{}, m_hasOverride, false);
        }
        return Override<V>(m_defaultValue, m_prefabValue, V{}, m_hasPrefab, false);
    }

    struct Memory
    {
        MemoryProfiler* prof;

        template <typename T>
        void operator()(T) const
        {
        }

        void operator()(std::string const& str) const
        {
            prof->addMem("Override<string>", str.capacity());
        }
    };

    template <typename V>
    void Override<V>::computeMemory(MemoryProfiler& prof) const
    {
        Memory compute{&prof};
        compute(m_defaultValue);
        if (hasPrefabValue())
        {
            compute(m_prefabValue);
        }
        if (hasOverride())
        {
            compute(m_overrideValue);
        }
    }
} // namespace Ent
