#pragma once

#include <memory>

#include "Override.h"
#include "MemoryProfiler.h"
#include "include/EntityLibCore.h"

namespace Ent
{
    // For now, used only for Entities, but could be used for Components and in Ent::Map
    template <typename Key, typename Value>
    struct RemovableMap
    {
        struct Removable
        {
            std::unique_ptr<Value> value{};
            Override<bool> isPresent{};
            size_t index = 0; // Keep order

            // Removable() = default;

            Removable makeInstanceOf() const
            {
                return Removable{value->makeInstanceOf(), isPresent.makeInstanceOf()};
            }
            Removable clone() const
            {
                return Removable{value->clone(), isPresent.clone(), index};
            }

            [[nodiscard]] bool hasOverride() const
            {
                return value->hasOverride() || isPresent.hasOverride();
            }

            [[nodiscard]] bool hasPrefabValue() const
            {
                return value->hasPrefabValue() || isPresent.hasPrefabValue();
            }
            Removable resetInstanceOf() const
            {
                return Removable{value->resetInstanceOf(), isPresent.resetInstanceOf(), index};
            }

            void computeMemory(MemoryProfiler& prof) const
            {
                value->computeMemory(prof);
            }
        };
        RemovableMap() = default;
        RemovableMap(RemovableMap&&) noexcept = default;
        RemovableMap& operator=(RemovableMap&&) noexcept = default;
        std::map<Key, Removable> map;
        using value_type = typename std::map<Key, Removable>::value_type;

        Value* emplace(Key _key, std::unique_ptr<Value> _value, OverrideValueLocation _loc);

        void erase(Key const& _key);

        Value const* at(Key const& key) const;

        Value* at(Key const& key);

        [[nodiscard]] size_t size() const;

        void clear();

        void computeMemory(MemoryProfiler& prof) const;
    };

    template <typename Key, typename Value>
    Value* RemovableMap<Key, Value>::emplace(
        Key _key, std::unique_ptr<Value> _value, OverrideValueLocation _loc)
    {
        Override<bool> isPresent;
        switch (_loc)
        {
        case OverrideValueLocation::Default: isPresent.setDefault(true); break;
        case OverrideValueLocation::Prefab: isPresent.setPrefab(true); break;
        case OverrideValueLocation::Override: isPresent.set(true); break;
        }
        Removable rem{std::move(_value), std::move(isPresent), map.size()};

        return map.insert_or_assign(std::move(_key), std::move(rem)).first->second.value.get();
    }

    template <typename Key, typename Value>
    void RemovableMap<Key, Value>::erase(Key const& _key)
    {
        auto iter = map.find(_key);
        if (iter != map.end())
        {
            iter->second.isPresent.set(false);
        }
    }

    template <typename Key, typename Value>
    Value const* RemovableMap<Key, Value>::at(Key const& key) const
    {
        auto iter = map.find(key);
        if (iter != map.end() && iter->second.isPresent.get())
        {
            return iter->second.value.get();
        }
        return nullptr;
    }

    template <typename Key, typename Value>
    Value* RemovableMap<Key, Value>::at(Key const& key)
    {
        return const_cast<Value*>(std::as_const(*this).at(key));
    }

    template <typename Key, typename Value>
    size_t RemovableMap<Key, Value>::size() const
    {
        return static_cast<size_t>(std::count_if(
            begin(map),
            end(map),
            [](auto&& name_removable) { return name_removable.second.isPresent.get(); }));
    }

    template <typename Key, typename Value>
    void RemovableMap<Key, Value>::clear()
    {
        map.clear();
    }

    template <typename Key, typename Value>
    auto begin(RemovableMap<Key, Value>& _map)
    {
        return _map.map.begin();
    }

    template <typename Key, typename Value>
    auto end(RemovableMap<Key, Value>& _map)
    {
        return _map.map.end();
    }

    template <typename Key, typename Value>
    auto begin(RemovableMap<Key, Value> const& _map)
    {
        return _map.map.begin();
    }

    template <typename Key, typename Value>
    auto end(RemovableMap<Key, Value> const& _map)
    {
        return _map.map.end();
    }

    template <typename Key, typename Value>
    void RemovableMap<Key, Value>::computeMemory(MemoryProfiler& prof) const
    {
        for (auto&& [key, value] : map)
        {
            prof.addMem("RemovableMap_pair", sizeof(decltype(map)::value_type));
            prof.addMem("RemovableMap_key", key.capacity());
            value.computeMemory(prof);
        }
    }

} // namespace Ent
