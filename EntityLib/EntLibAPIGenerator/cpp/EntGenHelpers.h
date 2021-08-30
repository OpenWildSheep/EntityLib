#pragma once

#include <string>
#include <tuple>
#include <string_view>
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
                using iterator_category = std::forward_iterator_tag;
                using value_type = T;
                using difference_type = size_t;
                using pointer = std::optional<T>;
                using reference = T;

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
        struct PrimArray : Array<T>
        {
            PrimArray(Ent::Node* _node)
                : Array(_node)
            {
            }

            template <typename T, std::size_t... Is>
            void copyFromTuple(T const& rho, std::index_sequence<Is...>)
            {
                (operator[](Is).set(std::get<Is>(rho)), ...);
            }

            template <typename T>
            Array& operator=(T const& rho)
            {
                ENT_IF_COMPILE(T, arr, std::get<0>(arr)) // tuple, c-style array and std::array
                {
                    if (std::tuple_size_v<T> != size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    copyFromTuple(rho, std::make_index_sequence<std::tuple_size_v<T>>{});
                }
                else ENT_IF_COMPILE(T, arr, std::size(arr)) // All other dynamic containers
                {
                    if (std::size(rho) != size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    std::copy(std::begin(rho), std::end(rho), begin());
                }
                else static_assert(false, "Unknown array type");
                return *this;
            }

            template <typename T, std::size_t... Is>
            void copyToTuple(T& point, std::index_sequence<Is...>)
            {
                ((std::get<Is>(point) = operator[](Is).get()), ...);
            }

            template <typename T>
            operator T()
            {
                T result;
                ENT_IF_COMPILE(T, arr, std::get<0>(arr)) // tuple, c-style array and std::array
                {
                    if (std::tuple_size_v<T> != size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    copyToTuple(result, std::make_index_sequence<std::tuple_size_v<T>>{});
                }
                else ENT_IF_COMPILE(T, arr, std::size(arr)) // All other dynamic containers
                {
                    std::copy(begin(), end(), std::back_inserter(result));
                }
                else static_assert(false, "Unknown array type");
                return result;
            }
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

        template <typename V>
        V toInternal(V value)
        {
            return value;
        }

        template <typename T>
        struct PrimitiveSet : Base
        {
            PrimitiveSet(Ent::Node* _node)
                : Base(_node)
            {
            }
            void add(T key) const
            {
                node->mapInsert(toInternal(key));
            }
            bool count(T key) const
            {
                return node->mapGet(toInternal(key)) != nullptr;
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

        template <typename K, typename O>
        struct ObjectSet : Base
        {
            ObjectSet(Ent::Node* _node)
                : Base(_node)
            {
            }
            O operator[](K key)
            {
                return node->mapGet(toInternal(key));
            }
            O get(K key)
            {
                return node->mapGet(toInternal(key));
            }
            O add(K key) const
            {
                return node->mapInsert(toInternal(key));
            }
            void remove(K key) const
            {
                node->mapErase(toInternal(key));
            }
            size_t size() const
            {
                return node->size();
            }

            std::vector<O> getItems()
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
                return node->mapGet(toInternal(key));
            }
            V operator[](K key)
            {
                return node->mapGet(toInternal(key));
            }
            V add(K key)
            {
                return node->mapInsert(toInternal(key));
            }
            void remove(K key)
            {
                node->mapErase(toInternal(key));
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
            using InternalType = T;
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

        template <typename Child, typename E>
        struct EnumPropHelper : PropHelper<Child, E>
        {
            using Enum = E;
            EnumPropHelper(Ent::Node* _node)
                : PropHelper<Child, Enum>(_node)
            {
            }
            void set(Enum value) const
            {
                node->setString(toInternal(value));
            }
            Enum get() const
            {
                char const* str = node->getString();
                auto iter = std::find(
                    std::begin(Child::enumToString),
                    std::end(Child::enumToString),
                    std::string_view(str));
                if (iter == std::end(Child::enumToString))
                    throw std::runtime_error(std::string("Unkown enum string '") + str + "'");
                return Enum(std::distance(std::begin(Child::enumToString), iter));
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
