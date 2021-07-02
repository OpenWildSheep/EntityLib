#pragma once

#pragma warning(push, 0)
#include "../external/optional.hpp"
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

    enum class CopyMode
    {
        CopyOverride, ///< Always override in dest when there is override in source
        MinimalOverride ///< Do not override when values are identicals
    };

    template <typename V>
    struct Override
    {
        Override()
            : hasPrefab(false)
            , hasOverride(false)
        {
        }
        Override(V _defaultValue, tl::optional<V> _prefabValue, tl::optional<V> _overrideValue)
            : defaultValue(std::move(_defaultValue))
        {
            hasPrefab = _prefabValue.has_value();
            hasOverride = _overrideValue.has_value();
            if (hasPrefab)
                prefabValue = std::move(*_prefabValue);
            if (hasOverride)
                overrideValue = std::move(*_overrideValue);
        }
        Override(V _defaultValue, V _prefabValue, V _overrideValue, bool _hasPrefab, bool _hasOverride)
            : defaultValue(std::move(_defaultValue))
            , prefabValue(std::move(_prefabValue))
            , overrideValue(std::move(_overrideValue))
            , hasPrefab(_hasPrefab)
            , hasOverride(_hasOverride)
        {
        }
        Override(V _defaultValue, V const* _prefabValue, V const* _overrideValue)
            : defaultValue(std::move(_defaultValue))
            , hasPrefab(_prefabValue != nullptr)
            , hasOverride(_overrideValue != nullptr)
        {
            if (hasPrefab)
                prefabValue = *_prefabValue;
            if (hasOverride)
                overrideValue = *_overrideValue;
        }
        Override(V _defaultVal)
            : defaultValue(_defaultVal)
            , hasPrefab(false)
            , hasOverride(false)
        {
        }

        V const& get() const;

        void set(V _newVal);

        bool isSet() const;

        void unset();

        Override<V> detach() const;

        Override<V> makeInstanceOf() const;

        /// makeInstanceOf, then set a value
        Override<V> makeOverridedInstanceOf(tl::optional<V> _overrideValue) const
        {
            Override<V> result = makeInstanceOf();
            result.hasOverride = _overrideValue.has_value();
            if (result.hasOverride)
                result.overrideValue = *_overrideValue;
            else
                result.overrideValue = {};
            return result;
        }

        /// True if no value was set in template or in instance
        bool isDefault() const
        {
            return !(hasPrefab || hasOverride);
        }

        void computeMemory(MemoryProfiler& prof) const;

        // bool hasOverride() const;

        tl::optional<V&> getRaw(OverrideValueLocation _location)
        {
            switch (_location)
            {
            case OverrideValueLocation::Default: return defaultValue;
            case OverrideValueLocation::Prefab:
                return hasPrefab ? tl::optional<V&>{prefabValue} : tl::nullopt;
            case OverrideValueLocation::Override:
                return hasOverride ? tl::optional<V&>{overrideValue} : tl::nullopt;
            default: return tl::nullopt;
            }
        }

        tl::optional<V const&> getRaw(OverrideValueLocation _location) const
        {
            switch (_location)
            {
            case OverrideValueLocation::Default: return defaultValue;
            case OverrideValueLocation::Prefab:
                return hasPrefab ? tl::optional<V const&>{prefabValue} : tl::nullopt;
            case OverrideValueLocation::Override:
                return hasOverride ? tl::optional<V const&>{overrideValue} : tl::nullopt;
            default: return tl::nullopt;
            }
        }

        V& getPrefab()
        {
            return hasPrefab ? prefabValue : defaultValue;
        }
        V const& getPrefab() const
        {
            return hasPrefab ? prefabValue : defaultValue;
        }

        void applyAllValues(Override& _dest, CopyMode _copyMode) const
        {
            switch (_copyMode)
            {
            case CopyMode::CopyOverride:
                if (isSet())
                {
                    _dest.set(get());
                }
                else if (!(get() == _dest.get()))
                    _dest.set(get());
                break;
            case CopyMode::MinimalOverride:
                _dest.unset();
                if (!(get() == _dest.get()))
                    _dest.set(get());
                break;
            }
        }

    public:
        V defaultValue{};
        V prefabValue{};
        V overrideValue{};
        bool hasPrefab : 1; // No default init for bitfield until c++20
        bool hasOverride : 1;
        // DeleteCheck deleteCheck;
    };

    template <typename V>
    V const& Override<V>::get() const
    {
        if (hasOverride)
        {
            return overrideValue;
        }
        if (hasPrefab)
        {
            return prefabValue;
        }
        return defaultValue;
    }

    template <typename V>
    void Override<V>::set(V _newVal)
    {
        overrideValue = std::move(_newVal);
        hasOverride = true;
    }

    template <typename V>
    bool Override<V>::isSet() const
    {
        return hasOverride;
    }

    template <typename V>
    void Override<V>::unset()
    {
        hasOverride = false;
        overrideValue = {};
    }

    template <typename V>
    Override<V> Override<V>::detach() const
    {
        if (hasOverride)
            return Override<V>(defaultValue, V{}, overrideValue, false, hasOverride);
        else
            return Override<V>(defaultValue, V{}, prefabValue, false, hasPrefab);
    }

    template <typename V>
    Override<V> Override<V>::makeInstanceOf() const
    {
        if (hasOverride)
            return Override<V>(defaultValue, overrideValue, V{}, hasOverride, false);
        else
            return Override<V>(defaultValue, prefabValue, V{}, hasPrefab, false);
    }
} // namespace Ent
