#pragma once

#pragma warning(push, 0)
#include "../external/optional.hpp"
#pragma warning(pop)

namespace Ent
{
    struct MemoryProfiler;

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

        V const& getDefaultValue() const
        {
            return defaultValue;
        }

        V& getDefaultValue()
        {
            return defaultValue;
        }

    public:
        V defaultValue{};
        V prefabValue{};
        V overrideValue{};
        bool hasPrefab : 1; // No default init for bitfield until c++20
        bool hasOverride : 1;
        // DeleteCheck deleteCheck;
    };

} // namespace Ent
