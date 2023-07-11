#pragma once

#include <string>
#include <tuple>
#include <string_view>
#include <optional>
#include <type_traits>
#include <filesystem>

#include <EntityLib/EntityLib.h>
#include <EntityLib/Property.h>

namespace Ent
{
    namespace Gen2
    {
        struct Base
        {
        private:
            Property m_property;

        public:
            Base(Property _prop)
                : m_property(_prop)
            {
            }

            [[nodiscard]] Property& getProperty()
            {
                return m_property;
            }

            [[nodiscard]] Property const& getProperty() const
            {
                return m_property;
            }

            void unset()
            {
                getProperty().unset();
            }

            [[nodiscard]] bool isDefault() const
            {
                return getProperty().isDefault();
            }

            [[nodiscard]] bool isSet() const
            {
                return getProperty().isSet();
            }

            [[nodiscard]] bool hasOverride() const
            {
                return getProperty().isSet();
            }

            [[nodiscard]] bool hasDefaultValue() const
            {
                return getProperty().isDefault();
            }

            [[nodiscard]] bool hasPrefabValue() const
            {
                return getProperty().hasPrefabValue();
            }

            [[nodiscard]] bool IsUsedInRuntime() const
            {
                return getProperty().getSchema()->IsUsedInRuntime();
            }

            [[nodiscard]] Subschema const* getSchema() const
            {
                return getProperty().getSchema();
            }

            [[nodiscard]] DataKind getDataKind() const
            {
                return getProperty().getSchema()->getDataKind();
            }

            void applyToPrefab()
            {
                getProperty().applyToPrefab();
            }

            [[nodiscard]] nlohmann::json const* getRawJson() const
            {
                return getProperty().getRawJson();
            }

            [[nodiscard]] EntityLib* getEntityLib() const
            {
                return getProperty().getEntityLib();
            }

            [[nodiscard]] Property getRootNode() const
            {
                return getProperty().getRootNode();
            }

            [[nodiscard]] std::optional<Property> getPrefab() const
            {
                return getProperty().getPrefab();
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

                Property m_property;
                size_t index;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                [[nodiscard]] bool operator==(iterator const& rho) const
                {
                    // ENTLIB_ASSERT(m_property.getNodeRef() == rho.m_property.getNodeRef());
                    return index == rho.index;
                }

                [[nodiscard]] bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                [[nodiscard]] T operator*() const
                {
                    return T(m_property.getArrayItem(index));
                }

                [[nodiscard]] std::optional<T> operator->() const
                {
                    return T(m_property.getArrayItem(index));
                }
            };

            [[nodiscard]] iterator begin()
            {
                return iterator{getProperty(), 0};
            }

            [[nodiscard]] iterator end()
            {
                return iterator{getProperty(), getProperty().size()};
            }

            Array(Property _node)
                : Base(std::move(_node))
            {
            }
            [[nodiscard]] T operator[](size_t i)
            {
                return T(getProperty().getArrayItem(i));
            }
            [[nodiscard]] size_t size()
            {
                return getProperty().size();
            }
            T push()
            {
                return T(getProperty().pushBack());
            }
            void pop_back()
            {
                getProperty().pop();
            }
            void clear()
            {
                getProperty().clear();
            }
            [[nodiscard]] bool empty() const
            {
                return getProperty().empty();
            }
        };

        template <typename T>
        struct PrimArray : Array<T>
        {
            PrimArray(Property _node)
                : Array<T>(std::move(_node))
            {
            }

            template <typename T, std::size_t... Is>
            void copyFromTuple(T const& rho, std::index_sequence<Is...>)
            {
                ((*this)[Is].set(std::get<Is>(rho)), ...);
            }

            template <typename T>
            struct What;

            template <typename V>
            PrimArray<T>& operator=(V const& rho)
            {
                ENT_IF_COMPILE(V, arr, std::get<0>(arr)) // tuple, c-style array and std::array
                {
                    if (std::tuple_size_v<V> != this->size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    copyFromTuple(rho, std::make_index_sequence<std::tuple_size_v<V>>{});
                }
                else ENT_IF_COMPILE(V, arr, std::size(arr)) // All other dynamic containers
                {
                    if (std::size(rho) != this->size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    std::copy(std::begin(rho), std::end(rho), this->begin());
                }
                else static_assert(sizeof(V) == 0, "Unknown array type");
                return *this;
            }

            template <typename V, std::size_t... Is>
            void copyToTuple(V& point, std::index_sequence<Is...>)
            {
                ((std::get<Is>(point) = static_cast<std::tuple_element_t<Is, V>>((*this)[Is].get())),
                 ...);
            }

            template <typename V>
            operator V()
            {
                V result;
                ENT_IF_COMPILE(V, arr, std::get<0>(arr)) // tuple, c-style array and std::array
                {
                    if (std::tuple_size_v<V> != this->size())
                        throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                    copyToTuple(result, std::make_index_sequence<std::tuple_size_v<V>>{});
                }
                else ENT_IF_COMPILE(V, arr, std::size(arr)) // All other dynamic containers
                {
                    std::copy(this->begin(), this->end(), std::back_inserter(result));
                }
                else static_assert(sizeof(V) == 0, "Unknown array type");
                return result;
            }
        };

        template <typename T>
        [[nodiscard]] auto begin(Array<T> arr)
        {
            return arr.begin();
        }

        template <typename T>
        [[nodiscard]] auto end(Array<T> arr)
        {
            return arr.end();
        }

        template <typename E>
        [[nodiscard]] E strToEnum(char const* in);

        namespace details
        {
            template <typename A>
            [[nodiscard]] size_t indexInEnum(char const* value, A&& arr)
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

        template <typename Uni>
        struct UnionSetBase : Base
        {
            // using Union = U;
            UnionSetBase(Property _node)
                : Base(std::move(_node))
            {
            }
            [[nodiscard]] std::optional<Property> operator[](char const* str) const
            {
                if (auto sub = getProperty().getUnionSetItem(str))
                {
                    return sub;
                }
                else
                {
                    return std::nullopt;
                }
            }
            template <typename T>
            [[nodiscard]] static char const* getTypeName()
            {
                std::string_view name = typeid(T).name();
                auto colon = name.find_last_of(':');
                if (colon == std::string_view::npos)
                    return name.data();
                else
                    return name.data() + colon + 1;
            }
            [[nodiscard]] bool count(char const* str) const
            {
                return getProperty().unionSetContains(str);
            }
            [[nodiscard]] std::optional<Property> getSubNode(char const* _typeName) const
            {
                return getProperty().getUnionSetItem(_typeName);
            }
            template <typename T>
            [[nodiscard]] std::optional<T> get() const
            {
                if (auto optProp = getSubNode(getTypeName<T>()))
                {
                    return std::optional<T>(*optProp);
                }
                else
                {
                    return std::nullopt;
                }
            }
            [[nodiscard]] std::optional<Property> get(char const* _typeName) const
            {
                return getProperty().getUnionSetItem(_typeName);
            }
            Property addSubNode(char const* str) const
            {
                return getProperty().insertUnionSetItem(str);
            }
            template <typename T>
            T add() const
            {
                return T(addSubNode(getTypeName<T>()));
            }
            bool remove(char const* str) const
            {
                return getProperty().eraseUnionSetItem(str);
            }
            template <typename T>
            bool remove() const
            {
                return remove(getTypeName<T>());
            }
            [[nodiscard]] std::optional<Property> operator[](std::string const& str) const
            {
                return get(str.c_str());
            }
            [[nodiscard]] size_t size() const
            {
                return getProperty().size();
            }

            [[nodiscard]] bool empty() const
            {
                return getProperty().empty();
            }
            void clear() const
            {
                getProperty().clear();
            }

            [[nodiscard]] std::set<char const*> getKeys() const
            {
                std::set<char const*> keys;
                for (auto [key, schema] : getProperty().getUnionSetKeysString())
                {
                    keys.insert(key);
                }
                return keys;
            }

            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using value_type = Property;
                using difference_type = size_t;
                using pointer = std::optional<Property>;
                using reference = Property;

                mutable Property m_property;
                std::vector<char const*> keys;
                size_t index = 0;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                [[nodiscard]] bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(m_property.hasValue());
                    ENTLIB_ASSERT(rho.m_property.hasValue());
                    return index == rho.index;
                }

                [[nodiscard]] bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                [[nodiscard]] reference operator*() const
                {
                    return *m_property.getUnionSetItem(keys[index]);
                }

                [[nodiscard]] pointer operator->() const
                {
                    return *(*this);
                }
            };

            [[nodiscard]] iterator begin()
            {
                std::vector<char const*> keys;
                for (auto&& [key, type] : getProperty().getUnionSetKeysString())
                {
                    keys.push_back(key);
                }
                return iterator{getProperty(), std::move(keys), 0};
            }

            [[nodiscard]] iterator end()
            {
                return iterator{getProperty(), {}, size()};
            }
        };

        template <typename U>
        [[nodiscard]] auto begin(UnionSetBase<U> arr)
        {
            return arr.begin();
        }

        template <typename U>
        [[nodiscard]] auto end(UnionSetBase<U> arr)
        {
            return arr.end();
        }

        template <typename V>
        [[nodiscard]] V toInternal(V value)
        {
            return value;
        }

        [[nodiscard]] inline char const* toInternal(std::string const& value)
        {
            return value.c_str();
        }

        template <typename T>
        struct PrimitiveSet : Base
        {
            PrimitiveSet(Property _node)
                : Base(std::move(_node))
            {
            }
            void add(T key)
            {
                getProperty().insertPrimSetKey(toInternal(key));
            }
            void remove(T key)
            {
                getProperty().erasePrimSetKey(toInternal(key));
            }
            [[nodiscard]] bool count(T key)
            {
                return getProperty().primSetContains(toInternal(key));
            }
            [[nodiscard]] size_t size()
            {
                return getProperty().size();
            }

            [[nodiscard]] bool empty() const
            {
                return getProperty().empty();
            }

            void clear()
            {
                getProperty().clear();
            }

            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using value_type = T;
                using difference_type = size_t;
                using pointer = T const*;
                using reference = T const&;

                Property node;
                std::vector<T> keys;
                size_t index = 0;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                [[nodiscard]] bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node.hasValue());
                    ENTLIB_ASSERT(rho.node.hasValue());
                    return index == rho.index;
                }

                [[nodiscard]] bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                [[nodiscard]] reference operator*() const
                {
                    return keys[index];
                }

                [[nodiscard]] pointer operator->() const
                {
                    return *(*this);
                }
            };

            [[nodiscard]] iterator begin()
            {
                if constexpr (std::is_enum_v<T>)
                {
                    std::vector<T> enums;
                    for (auto&& str : getProperty().getPrimSetKeysString())
                    {
                        enums.push_back(strToEnum<T>(str));
                    }
                    return iterator{getProperty(), std::move(enums), 0};
                }
                else if constexpr (std::is_same_v<T, char const*>)
                {
                    std::vector<T> strings;
                    for (auto&& str : getProperty().getPrimSetKeysString())
                    {
                        strings.push_back(str);
                    }
                    return iterator{getProperty(), std::move(strings), 0};
                }
                else
                {
                    return iterator{getProperty(), getProperty().getPrimSetKeysInt(), 0};
                }
            }

            [[nodiscard]] iterator end()
            {
                return iterator{getProperty(), {}, size()};
            }
        };

        template <typename U>
        [[nodiscard]] auto begin(PrimitiveSet<U> arr)
        {
            return arr.begin();
        }

        template <typename U>
        [[nodiscard]] auto end(PrimitiveSet<U> arr)
        {
            return arr.end();
        }

        template <typename K, typename O>
        struct ObjectSet : Base
        {
            ObjectSet(Property _node)
                : Base(std::move(_node))
            {
            }
            [[nodiscard]] std::optional<O> operator[](K key)
            {
                return get(key);
            }
            [[nodiscard]] std::optional<O> get(K key)
            {
                auto internalKey = toInternal(key);
                return std::optional<O>(getProperty().getObjectSetItem(internalKey));
            }
            [[nodiscard]] bool contains(K key) const
            {
                auto internalKey = toInternal(key);
                return getProperty().objectSetContains(internalKey);
            }
            O add(K key)
            {
                return O(getProperty().insertObjectSetItem(toInternal(key)));
            }
            bool remove(K key)
            {
                return getProperty().eraseObjectSetItem(toInternal(key));
            }
            [[nodiscard]] size_t size() const
            {
                return getProperty().size();
            }

            [[nodiscard]] bool empty() const
            {
                return getProperty().empty();
            }

            void clear()
            {
                return getProperty().clear();
            }

            [[nodiscard]] auto getKeys() const
            {
                if constexpr (std::is_enum_v<K> || std::is_same_v<K, char const*>)
                {
                    return getProperty().getObjectSetKeysString();
                }
                else
                {
                    return getProperty().getObjectSetKeysInt();
                }
            }

            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using value_type = O;
                using difference_type = size_t;
                using pointer = std::optional<O>;
                using reference = O;

                Property node;
                std::vector<Property> items;
                size_t index = 0;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                [[nodiscard]] bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node.hasValue());
                    ENTLIB_ASSERT(rho.node.hasValue());
                    return index == rho.index;
                }

                [[nodiscard]] bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                [[nodiscard]] reference operator*() const
                {
                    return reference(items[index]);
                }

                [[nodiscard]] pointer operator->() const
                {
                    return *(*this);
                }
            };

            [[nodiscard]] iterator begin() const
            {
                std::vector<Property> subProps;
                for (auto const& key : getKeys())
                {
                    subProps.push_back(*getProperty().getObjectSetItem(key));
                }
                return iterator{getProperty(), subProps, 0};
            }

            [[nodiscard]] iterator end() const
            {
                return iterator{getProperty(), {}, size()};
            }

            O insertInstanceOf(char const* _prefabPath)
            {
                return O(getProperty().insertInstanceObjectSetItem(_prefabPath));
            }
        };

        template <typename K, typename O>
        [[nodiscard]] auto begin(ObjectSet<K, O> const& arr)
        {
            return arr.begin();
        }

        template <typename K, typename O>
        [[nodiscard]] auto end(ObjectSet<K, O> const& arr)
        {
            return arr.end();
        }

        template <typename... Args>
        struct Tuple : Base
        {
            Tuple(Property _node)
                : Base(std::move(_node))
            {
            }

            template <auto I>
            [[nodiscard]] typename std::tuple_element_t<I, std::tuple<Args...>> get()
            {
                return getProperty().getArrayItem(size_t(I));
            }

            [[nodiscard]] constexpr size_t size()
            {
                return std::tuple_size_v<std::tuple<Args...>>;
            }
        };

        template <typename K, typename V>
        struct Map : Base
        {
            Map(Property _node)
                : Base(std::move(_node))
            {
            }
            [[nodiscard]] std::optional<V> get(K key)
            {
                auto internKey = toInternal(key);
                return std::optional<V>(getProperty().getMapItem(internKey));
            }
            [[nodiscard]] std::optional<V> operator[](K key)
            {
                return get(key);
            }
            V add(K key)
            {
                return V(getProperty().insertMapItem(toInternal(key)));
            }
            bool remove(K key)
            {
                return getProperty().eraseMapItem(toInternal(key));
            }
            [[nodiscard]] size_t size()
            {
                return getProperty().size();
            }

            [[nodiscard]] bool empty() const
            {
                return getProperty().empty();
            }

            [[nodiscard]] void clear()
            {
                getProperty().clear();
            }

            [[nodiscard]] auto getKeysImpl()
            {
                if constexpr (std::is_enum_v<K> || std::is_same_v<K, char const*>)
                {
                    return getProperty().getMapKeysString();
                }
                else
                {
                    return getProperty().getMapKeysInt();
                }
            }

            [[nodiscard]] auto getKeys()
            {
                if constexpr (std::is_enum_v<K>)
                {
                    std::vector<K> result;
                    for (auto&& str : getKeysImpl())
                    {
                        result.push_back(strToEnum<K>(str));
                    }
                    return result;
                }
                else
                {
                    return getKeysImpl();
                }
            }

            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using value_type = std::pair<K, V>;
                using difference_type = size_t;
                using pointer = std::optional<value_type>;
                using reference = value_type;

                Property node;
                mutable std::vector<std::pair<K, V>> items;
                size_t index = 0;

                iterator& operator++()
                {
                    ++index;
                    return *this;
                }

                [[nodiscard]] bool operator==(iterator const& rho) const
                {
                    ENTLIB_ASSERT(node.hasValue());
                    ENTLIB_ASSERT(rho.node.hasValue());
                    return index == rho.index;
                }

                [[nodiscard]] bool operator!=(iterator const& rho) const
                {
                    return !(*this == rho);
                }

                [[nodiscard]] reference operator*() const
                {
                    auto keyToView = [](Property const& keynode)
                    {
                        if constexpr (std::is_enum_v<K>)
                        {
                            return strToEnum<K>(keynode.getString());
                        }
                        else if constexpr (std::is_same_v<K, char const*>)
                        {
                            return keynode.getString();
                        }
                        else
                        {
                            return keynode.getInt();
                        }
                    };
                    return items[index];
                }

                [[nodiscard]] pointer operator->() const
                {
                    return *(*this);
                }
            };

            [[nodiscard]] iterator begin()
            {
                std::vector<std::pair<K, V>> properties;
                for (auto&& key : getKeys())
                {
                    properties.emplace_back(key, *getProperty().getMapItem(toInternal(key)));
                }
                return iterator{getProperty(), std::move(properties), 0};
            }

            [[nodiscard]] iterator end()
            {
                return iterator{getProperty(), {}, size()};
            }
        };

        template <typename K, typename V>
        [[nodiscard]] auto begin(Map<K, V> arr)
        {
            return arr.begin();
        }

        template <typename K, typename V>
        [[nodiscard]] auto end(Map<K, V> arr)
        {
            return arr.end();
        }

        template <typename P, typename T>
        struct PropHelper : Base
        {
            using InternalType = T;
            PropHelper(Property _node)
                : Base(std::move(_node))
            {
            }

            PropHelper& operator=(T value)
            {
                ((P*)this)->set(value);
                return *this;
            }

            [[nodiscard]] operator T() const
            {
                return ((P const*)this)->get();
            }
        };

        template <typename Child, typename E>
        struct EnumPropHelper : PropHelper<Child, E>
        {
            using Enum = E;
            EnumPropHelper(Property _node)
                : PropHelper<Child, Enum>(std::move(_node))
            {
            }
            void set(Enum value)
            {
                this->getProperty().setString(toInternal(value));
            }
            [[nodiscard]] Enum get() const
            {
                char const* str = this->getProperty().getString();
                auto iter = std::find(
                    std::begin(Child::enumToString),
                    std::end(Child::enumToString),
                    std::string_view(str));
                if (iter == std::end(Child::enumToString))
                    throw std::runtime_error(std::string("Unkown enum string '") + str + "'");
                return Enum(std::distance(std::begin(Child::enumToString), iter));
            }
        };

        template <typename O>
        struct HelperObject : Base
        {
            HelperObject(Property _node)
                : Base(std::move(_node))
            {
            }

            /// path to the prefab Node
            [[nodiscard]] char const* getInstanceOf() const
            {
                return getProperty().getInstanceOf();
            }

            /// Create a Node which is an "instance of" this one. With no override.
            [[nodiscard]] O makeInstanceOf()
            {
                return O(getProperty().makeInstanceOf());
            }

            /// Reset the Property to be an instance of the given \b _prefabNodePath
            ///
            /// @warning All sub-nodes into \b _node will be invalidated
            /// @param _prefabNodePath path to the prefab Node (relative to RawData)
            void resetInstanceOf(char const* _prefabNodePath)
            {
                getProperty().resetInstanceOf(_prefabNodePath);
            }

            /// @brief Change this Entity to be an instance of the given \b _newPrefab, keeping
            /// all overriden values the same.
            /// @param _newPrefab path to the new prefab
            void changeInstanceOf(char const* _newPrefab)
            {
                getProperty().changeInstanceOf(_newPrefab);
            }

            void save(char const* _destFile)
            {
                getProperty().save(_destFile);
            }

            void copyInto(O _dest, CopyMode _copyMode)
            {
                getProperty().copyInto(_dest.getProperty(), _copyMode);
            }

            [[nodiscard]] O detach()
            {
                return O(getProperty().detach());
            }
        };

        struct Bool : PropHelper<Bool, bool>
        {
            Bool(Property _node)
                : PropHelper<Bool, bool>(std::move(_node))
            {
            }
            using PropHelper<Bool, bool>::operator=;
            void set(bool value)
            {
                getProperty().setBool(value);
            }
            [[nodiscard]] bool get() const
            {
                return getProperty().getBool();
            }
            [[nodiscard]] bool getDefault() const
            {
                return getProperty().getDefaultBool();
            }
        };

        struct Int : PropHelper<Int, int64_t>
        {
            Int(Property _node)
                : PropHelper<Int, int64_t>(std::move(_node))
            {
            }
            using PropHelper<Int, int64_t>::operator=;
            void set(int64_t value)
            {
                getProperty().setInt(value);
            }
            [[nodiscard]] int64_t get() const
            {
                return getProperty().getInt();
            }
            [[nodiscard]] int64_t getDefault() const
            {
                return getProperty().getDefaultInt();
            }
        };

        struct Float : PropHelper<Float, double>
        {
            Float(Property _node)
                : PropHelper<Float, double>(std::move(_node))
            {
            }
            using PropHelper<Float, double>::operator=;
            void set(double value)
            {
                getProperty().setFloat(value);
            }
            [[nodiscard]] double get() const
            {
                return getProperty().getFloat();
            }
            [[nodiscard]] double getDefault() const
            {
                return getProperty().getDefaultFloat();
            }

            [[nodiscard]] operator float() const
            {
                return static_cast<float>(getProperty().getFloat());
            }

            [[nodiscard]] float toFloat() const
            {
                return static_cast<float>(getProperty().getFloat());
            }
        };

        struct String : PropHelper<String, char const*>
        {
            String(Property _node)
                : PropHelper<String, char const*>(std::move(_node))
            {
            }
            using PropHelper<String, char const*>::operator=;
            void set(char const* value)
            {
                getProperty().setString(value);
            }
            void set(std::string const& value)
            {
                getProperty().setString(value.c_str());
            }
            [[nodiscard]] char const* get() const
            {
                return getProperty().getString();
            }
            [[nodiscard]] char const* c_str() const
            {
                return getProperty().getString();
            }
            [[nodiscard]] char const* getDefault() const
            {
                return getProperty().getDefaultString();
            }

            String const& operator=(char const* value)
            {
                set(value);
                return *this;
            }

            String const& operator=(std::string const& value)
            {
                set(value.c_str());
                return *this;
            }

            [[nodiscard]] operator std::string() const
            {
                return get();
            }

            [[nodiscard]] bool operator==(std::string const& value) const
            {
                return get() == value;
            }

            [[nodiscard]] bool operator!=(std::string const& value) const
            {
                return get() != value;
            }

            [[nodiscard]] operator std::filesystem::path() const
            {
                return get();
            }

            [[nodiscard]] bool empty() const
            {
                return strlen(get()) == 0;
            }
        };

        struct EntityRef : PropHelper<EntityRef, ::Ent::EntityRef>
        {
            EntityRef(Property _node)
                : PropHelper<EntityRef, ::Ent::EntityRef>(std::move(_node))
            {
            }
            using PropHelper<EntityRef, ::Ent::EntityRef>::operator=;
            void set(::Ent::EntityRef value)
            {
                getProperty().setEntityRef(std::move(value));
            }
            [[nodiscard]] ::Ent::EntityRef get() const
            {
                return getProperty().getEntityRef();
            }
            [[nodiscard]] ::Ent::EntityRef getDefault() const
            {
                return getProperty().getDefaultEntityRef();
            }
        };
    } // namespace Gen2
} // namespace Ent
