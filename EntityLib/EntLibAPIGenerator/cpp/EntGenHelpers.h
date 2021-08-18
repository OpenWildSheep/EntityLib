#pragma once

#include <string>
#include <optional>

#include <EntityLib.h>

namespace Ent
{
    namespace Gen
    {
        struct Base
        {
            Ent::Node* node{};

            Base(Ent::Node* _node)
                : node(_node)
            {
            }

            bool hasValue() const
            {
                return node != nullptr;
            }

            bool isSet() const
            {
                return node->isSet();
            }
            void unset() const
            {
                node->unset();
            }

            bool isDefault() const
            {
                return node->isDefault();
            }

            bool hasDefaultValue() const
            {
                return node->hasDefaultValue();
            }
        };

        template <typename T>
        struct Array : Base
        {
            struct iterator
            {
                Ent::Node* node;
                size_t index;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                iterator& operator--()
                {
                    --index;
                    return *this;
                }

                bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node == rho.node);
                    return index == rho.index;
                }

                bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                T operator*() const
                {
                    return T(node->at(index));
                }

                std::optional<T> operator->() const
                {
                    return T(node->at(index));
                }
            };

            iterator begin() const
            {
                return iterator{node, 0};
            }

            iterator end() const
            {
                return iterator{node, node->size()};
            }

            Array(Ent::Node* _node)
                : Base(_node)
            {
            }
            T operator[](size_t i)
            {
                return T(node->at(i));
            }
            size_t size() const
            {
                return node->size();
            }
            T push()
            {
                return T(node->push(i));
            }
            void pop_back()
            {
                node->pop();
            }

            /*std::vector<T> getItems()
            {
                std::vector<T> items;
                for (size_t i = 0; i < node->size(); ++i)
                {
                    items.emplace_back(node->at(i));
                }
                return items;
            }*/
        };

        template <typename T>
        auto begin(Array<T> arr)
        {
            return arr.begin();
        }

        template <typename T>
        auto end(Array<T> arr)
        {
            return arr.end();
        }

        template <typename T>
        struct UnionSetBase : Base
        {
            UnionSetBase(Ent::Node* _node)
                : Base(_node)
            {
            }
            Ent::Node* operator[](size_t i) const
            {
                return node->mapGet(i);
            }
            Ent::Node* operator[](char const* str) const
            {
                return node->mapGet(str);
            }
            template <typename T>
            static char const* getTypeName()
            {
                std::string_view name = typeid(T).name();
                auto colon = name.find_last_of(':');
                if (colon == std::string_view::npos)
                    return name.data();
                else
                    return name.data() + colon + 1;
            }
            Ent::Node* get(char const* str) const
            {
                return node->mapGet(str)->getUnionData();
            }
            template <typename T>
            T get() const
            {
                return get(getTypeName<T>());
            }
            Ent::Node* add(char const* str) const
            {
                return node->mapInsert(str)->getUnionData();
            }
            template <typename T>
            T add() const
            {
                return add(getTypeName<T>());
            }
            void remove(char const* str) const
            {
                return node->mapErase(str);
            }
            template <typename T>
            void remove() const
            {
                return remove(getTypeName<T>());
            }
            Ent::Node* operator[](std::string const& str) const
            {
                return node->mapGet(str.c_str());
            }
            size_t size() const
            {
                return node->size();
            }

            std::vector<Ent::Node*> getItems() const
            {
                std::vector<Ent::Node*> items;
                for (size_t i = 0; i < node->size(); ++i)
                {
                    items.emplace_back(node->at(i));
                }
                return items;
            }
        };

        template <typename T>
        struct PrimitiveSet : Base
        {
            PrimitiveSet(Ent::Node* _node)
                : Base(_node)
            {
            }
            T operator[](size_t i) const
            {
                return get(i);
            }
            T operator[](char const* str) const
            {
                return get(str);
            }
            T operator[](std::string const& str) const
            {
                return get(str);
            }
            T get(size_t i) const
            {
                return node->mapGet(i);
            }
            T get(char const* str) const
            {
                return node->mapGet(str);
            }
            T get(std::string const& str) const
            {
                return node->mapGet(str.c_str());
            }
            T add(size_t i) const
            {
                return node->mapInsert(i);
            }
            T add(char const* str) const
            {
                return node->mapInsert(str);
            }
            T add(std::string const& str) const
            {
                return node->mapInsert(str.c_str());
            }
            size_t size() const
            {
                return node->size();
            }

            std::vector<T> getItems()
            {
                std::vector<T> items;
                for (size_t i = 0; i < node->size(); ++i)
                {
                    items.emplace_back(node->at(i));
                }
                return items;
            }
        };

        template <typename T>
        struct ObjectSet : Base
        {
            ObjectSet(Ent::Node* _node)
                : Base(_node)
            {
            }
            T operator[](size_t key)
            {
                return node->mapGet(key);
            }
            T operator[](char const* key) const
            {
                return node->mapGet(key);
            }
            T operator[](std::string const& key) const
            {
                return node->mapGet(key);
            }
            T get(size_t key)
            {
                return node->mapGet(key);
            }
            T get(char const* key) const
            {
                return node->mapGet(key);
            }
            T get(std::string const& key) const
            {
                return node->mapGet(key);
            }
            T add(size_t key) const
            {
                return node->mapInsert(key);
            }
            T add(char const* key) const
            {
                return node->mapInsert(key);
            }
            T add(std::string const& key) const
            {
                return node->mapInsert(key.c_str());
            }
            void remove(size_t key) const
            {
                node->mapErase(key);
            }
            void remove(char const* key) const
            {
                node->mapErase(key);
            }
            void remove(std::string const& key) const
            {
                node->mapErase(key.c_str());
            }
            size_t size() const
            {
                return node->size();
            }

            std::vector<T> getItems()
            {
                std::vector<T> items;
                for (size_t i = 0; i < node->size(); ++i)
                {
                    items.emplace_back(node->at(i));
                }
                return items;
            }
        };

        template <typename... Args>
        struct Tuple : Base
        {
            Tuple(Ent::Node* _node)
                : Base(_node)
            {
            }

            template <auto I>
            typename std::tuple_element_t<I, std::tuple<Args...>> get()
            {
                return node->at(size_t(I));
            }

            constexpr size_t size()
            {
                return std::tuple_size_v<std::tuple<Args...>>;
            }
        };

        template <typename K, typename V>
        struct Map : Base
        {
            struct iterator
            {
                Ent::Node* node;
                size_t index;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                iterator& operator--()
                {
                    --index;
                    return *this;
                }

                bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node == rho.node);
                    return index == rho.index;
                }

                bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                Tuple<K, V> operator*() const
                {
                    return Tuple<K, V>(node->at(index));
                }

                std::optional<Tuple<K, V>> operator->() const
                {
                    return Tuple<K, V>(node->at(index));
                }
            };

            iterator begin() const
            {
                return iterator{node, 0};
            }

            iterator end() const
            {
                return iterator{node, node->size()};
            }

            Map(Ent::Node* _node)
                : Base(_node)
            {
            }
            V get(K key)
            {
                return node->mapGet(key);
            }
            V operator[](K key)
            {
                return node->mapGet(key);
            }
            V add(K key)
            {
                return node->mapInsert(key);
            }
            void remove(K key)
            {
                node->mapErase(key);
            }
            size_t size() const
            {
                return node->size();
            }
        };

        template <typename K, typename V>
        auto begin(Map<K, V> arr)
        {
            return arr.begin();
        }

        template <typename K, typename V>
        auto end(Map<K, V> arr)
        {
            return arr.end();
        }

        template <typename P, typename T>
        struct PropHelper : Base
        {
            PropHelper(Ent::Node* _node)
                : Base(_node)
            {
            }

            PropHelper& operator=(T value)
            {
                ((P const*)this)->set(value);
                return *this;
            }

            operator T() const
            {
                return ((P const*)this)->get();
            }
        };

        struct Bool : PropHelper<Bool, bool>
        {
            Bool(Ent::Node* _node)
                : PropHelper<Bool, bool>(_node)
            {
            }
            using PropHelper<Bool, bool>::operator=;
            void set(bool value) const
            {
                node->setBool(value);
            }
            bool get() const
            {
                return node->getBool();
            }
        };

        struct Int : PropHelper<Int, int64_t>
        {
            Int(Ent::Node* _node)
                : PropHelper<Int, int64_t>(_node)
            {
            }
            using PropHelper<Int, int64_t>::operator=;
            void set(int64_t value) const
            {
                node->setInt(value);
            }
            int64_t get() const
            {
                return node->getInt();
            }
        };

        struct Float : PropHelper<Float, double>
        {
            Float(Ent::Node* _node)
                : PropHelper<Float, double>(_node)
            {
            }
            using PropHelper<Float, double>::operator=;
            void set(double value) const
            {
                node->setFloat(value);
            }
            double get() const
            {
                return node->getFloat();
            }
        };

        struct String : PropHelper<String, char const*>
        {
            String(Ent::Node* _node)
                : PropHelper<String, char const*>(_node)
            {
            }
            using PropHelper<String, char const*>::operator=;
            void set(char const* value) const
            {
                node->setString(value);
            }
            void set(std::string const& value) const
            {
                node->setString(value.c_str());
            }
            char const* get() const
            {
                return node->getString();
            }

            String const& operator=(std::string const& value) const
            {
                set(value);
                return *this;
            }
        };

        struct EntityRef : PropHelper<EntityRef, Ent::EntityRef>
        {
            EntityRef(Ent::Node* _node)
                : PropHelper<EntityRef, Ent::EntityRef>(_node)
            {
            }
            using PropHelper<EntityRef, Ent::EntityRef>::operator=;
            void set(Ent::EntityRef value) const
            {
                node->setEntityRef(value);
            }
            Ent::EntityRef get() const
            {
                return node->getEntityRef();
            }
        };

        struct Object;
        using Entity = ::Ent::Gen::Object;
    } // namespace Gen
} // namespace Ent
