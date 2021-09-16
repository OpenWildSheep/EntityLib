#pragma once

#include <string>
#include <tuple>
#include <string_view>
#include <optional>
#include <type_traits>

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

            bool isNull() const
            {
                return node == nullptr;
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
            void clean()
            {
                node->clean();
            }
        };

        template <typename T>
        struct PrimArray : Array<T>
        {
            PrimArray(Ent::Node* _node)
                : Array<T>(_node)
            {
            }

            template <typename T, std::size_t... Is>
            void copyFromTuple(T const& rho, std::index_sequence<Is...>)
            {
                (operator[](Is).set(std::get<Is>(rho)), ...);
            }

            template <typename T>
            struct What;

            template <typename V>
            Array<T>& operator=(V const& rho)
            {
                ENT_IF_COMPILE(V, arr, std::get<0>(arr)) // tuple, c-style array and std::array
                {
                    if (std::tuple_size_v<V> != size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    copyFromTuple(rho, std::make_index_sequence<std::tuple_size_v<V>>{});
                }
                else ENT_IF_COMPILE(V, arr, std::size(arr)) // All other dynamic containers
                {
                    if (std::size(rho) != size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    std::copy(std::begin(rho), std::end(rho), begin());
                }
                else static_assert(sizeof(V) == 0, "Unknown array type");
                return *this;
            }

            template <typename V, std::size_t... Is>
            void copyToTuple(V& point, std::index_sequence<Is...>)
            {
                ((std::get<Is>(point) = operator[](Is).get()), ...);
            }

            template <typename V>
            operator V()
            {
                V result;
                ENT_IF_COMPILE(V, arr, std::get<0>(arr)) // tuple, c-style array and std::array
                {
                    if (std::tuple_size_v<V> != size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    copyToTuple(result, std::make_index_sequence<std::tuple_size_v<V>>{});
                }
                else ENT_IF_COMPILE(V, arr, std::size(arr)) // All other dynamic containers
                {
                    std::copy(begin(), end(), std::back_inserter(result));
                }
                else static_assert(sizeof(V) == 0, "Unknown array type");
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

        namespace details
        {
            template <typename K>
            auto getKeys(Ent::Node* node)
            {
                if constexpr (std::is_enum_v<K>)
                {
                    std::vector<K> keys;
                    for (auto&& k : node->getKeysString())
                    {
                        keys.push_back(strToEnum<K>(k.c_str()));
                    }
                    return keys;
                }
                else if constexpr (std::is_arithmetic_v<K>)
                {
                    return node->getKeysInt();
                }
                else
                {
                    return node->getKeysString();
                }
            }

            template <typename A>
            size_t indexInEnum(char const* value, A&& arr)
            {
                for (size_t idx = 0; idx < std::size(arr); ++idx)
                {
                    if (strcmp(arr[idx], value) == 0)
                    {
                        return idx;
                    }
                }
                throw std::runtime_error("Wrong enum value");
            }
        } // namespace details

        template <typename U>
        struct UnionSetBase : Base
        {
            using Union = U;
            UnionSetBase(Ent::Node* _node)
                : Base(_node)
            {
            }
            Union operator[](char const* str) const
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
            Ent::Node* getSubNode(char const* str) const
            {
                return node->mapGet(str)->getUnionData();
            }
            template <typename T>
            T get() const
            {
                return getSubNode(getTypeName<T>());
            }
            Union get(char const* str) const
            {
                return node->mapGet(str);
            }
            Ent::Node* addSubNode(char const* str) const
            {
                return node->mapInsert(str)->getUnionData();
            }
            template <typename T>
            T add() const
            {
                return addSubNode(getTypeName<T>());
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

            auto getKeys() const
            {
                return details::getKeys<char const*>(node);
            }

            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using value_type = Union;
                using difference_type = size_t;
                using pointer = std::optional<Union>;
                using reference = Union;

                Ent::Node* node = nullptr;
                std::vector<Ent::String> keys;
                size_t index = 0;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node != nullptr);
                    ENTLIB_ASSERT(rho.node == nullptr);
                    return index == rho.index;
                }

                bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                reference operator*() const
                {
                    return Union(node->mapGet(keys[index].c_str()));
                }

                pointer operator->() const
                {
                    return *(*this);
                }
            };

            iterator begin() const
            {
                return iterator{node, node->getKeysString(), 0};
            }

            iterator end() const
            {
                return iterator{nullptr, {}, size()};
            }
        };

        template <typename U>
        auto begin(UnionSetBase<U> arr)
        {
            return arr.begin();
        }

        template <typename U>
        auto end(UnionSetBase<U> arr)
        {
            return arr.end();
        }

        template <typename V>
        V toInternal(V value)
        {
            return value;
        }

        char const* toInternal(Ent::String const& value)
        {
            return value.c_str();
        }

        template <typename E>
        E strToEnum(char const* in);

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

            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using value_type = T;
                using difference_type = size_t;
                using pointer = T const*;
                using reference = T const&;

                Ent::Node* node = nullptr;
                std::vector<T> keys;
                size_t index = 0;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node != nullptr);
                    ENTLIB_ASSERT(rho.node == nullptr);
                    return index == rho.index;
                }

                bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                reference operator*() const
                {
                    return keys[index];
                }

                pointer operator->() const
                {
                    return *(*this);
                }
            };

            iterator begin() const
            {
                return iterator{node, details::getKeys<T>(node), 0};
            }

            iterator end() const
            {
                return iterator{nullptr, {}, size()};
            }
        };

        template <typename U>
        auto begin(PrimitiveSet<U> arr)
        {
            return arr.begin();
        }

        template <typename U>
        auto end(PrimitiveSet<U> arr)
        {
            return arr.end();
        }

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

            auto getKeys() const
            {
                return details::getKeys<K>(node);
            }

            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using value_type = O;
                using difference_type = size_t;
                using pointer = std::optional<O>;
                using reference = O;

                Ent::Node* node = nullptr;
                std::vector<Ent::Node*> items;
                size_t index = 0;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node != nullptr);
                    ENTLIB_ASSERT(rho.node == nullptr);
                    return index == rho.index;
                }

                bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                reference operator*() const
                {
                    return items[index];
                }

                pointer operator->() const
                {
                    return *(*this);
                }
            };

            iterator begin() const
            {
                return iterator{node, node->getItems(), 0};
            }

            iterator end() const
            {
                return iterator{nullptr, {}, size()};
            }

            O insertInstanceOf(char const* _prefabPath)
            {
                return node->mapInsertInstanceOf(_prefabPath);
            }
        };

        template <typename K, typename O>
        auto begin(ObjectSet<K, O> const& arr)
        {
            return arr.begin();
        }

        template <typename K, typename O>
        auto end(ObjectSet<K, O> const& arr)
        {
            return arr.end();
        }

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

            auto getKeys() const
            {
                return details::getKeys<K>(node);
            }

            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using value_type = std::pair<K, V>;
                using difference_type = size_t;
                using pointer = std::optional<value_type>;
                using reference = value_type;

                Ent::Node* node = nullptr;
                std::vector<Ent::Node*> items;
                size_t index = 0;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node != nullptr);
                    ENTLIB_ASSERT(rho.node == nullptr);
                    return index == rho.index;
                }

                bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                reference operator*() const
                {
                    auto keyToView = [](Ent::Node* keynode) {
                        if constexpr (std::is_enum_v<K>)
                        {
                            return strToEnum<K>(keynode->getString());
                        }
                        else if constexpr (std::is_same_v<K, char const*>)
                        {
                            return keynode->getString();
                        }
                        else
                        {
                            return keynode->getInt();
                        }
                    };
                    return std::pair(keyToView(items[index]->at(0llu)), V(items[index]->at(1llu)));
                }

                pointer operator->() const
                {
                    return *(*this);
                }
            };

            iterator begin() const
            {
                return iterator{node, node->getItems(), 0};
            }

            iterator end() const
            {
                return iterator{nullptr, {}, size()};
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

        struct HelperObject : Base
        {
            HelperObject(Ent::Node* _node)
                : Base(_node)
            {
            }

            /// path to the prefab Node
            char const* getInstanceOf() const
            {
                return node->getInstanceOf();
            }

            /// Create a Node which is an "instance of" this one. With no override.
            Node makeInstanceOf() const
            {
                return node->makeInstanceOf();
            }

            /// Reset the Node to be an instance of the given \b _prefabNodePath
            ///
            /// @warning All sub-nodes into \b _node will be invalidated
            /// @param _prefabNodePath path to the prefab Node (relative to RawData)
            void resetInstanceOf(char const* _prefabNodePath)
            {
                node->resetInstanceOf(_prefabNodePath);
            }

            void resetInstanceOf()
            {
                node->resetInstanceOf();
            }

            /// @brief Change this Entity to be an instance of the given \b _newPrefab, keeping
            /// all internal values the same.
            /// @param _newPrefab path to the new prefab
            void changeInstanceOf(char const* _newPrefab)
            {
                node->changeInstanceOf(_newPrefab);
            }

            void save(std::filesystem::path const& _destFile)
            {
                node->saveNode(_destFile);
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
