#pragma once

#include <string>
#include <tuple>
#include <string_view>
#include <optional>
#include <type_traits>
#include <filesystem>
#include <utility>

#include <EntityLib.h>

namespace Ent::Gen
{
    struct Base
    {
        Node* node{};

        explicit Base(Node* _node)
            : node(_node)
        {
        }

        [[nodiscard]] bool isSet() const
        {
            return node->isSet();
        }
        void unset() const
        {
            node->unset();
        }

        [[nodiscard]] bool isDefault() const
        {
            return node->isDefault();
        }

        [[nodiscard]] bool hasOverride() const
        {
            return node->hasOverride();
        }

        [[nodiscard]] bool hasDefaultValue() const
        {
            return node->hasDefaultValue();
        }

        [[nodiscard]] bool IsUsedInRuntime() const
        {
            return node->getSchema()->IsUsedInRuntime();
        }

        [[nodiscard]] Subschema const* getSchema() const
        {
            return node->getSchema();
        }

        [[nodiscard]] DataType getDataType() const
        {
            return node->getSchema()->type;
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

            Node* node;
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

        explicit Array(Node* _node)
            : Base(_node)
        {
        }
        T operator[](size_t i)
        {
            return T(node->at(i));
        }

        [[nodiscard]] size_t size() const
        {
            return node->size();
        }
        T push()
        {
            return T(node->push());
        }
        void pop_back() const
        {
            node->pop();
        }
        void clear() const
        {
            node->clear();
        }

        [[nodiscard]] bool empty() const
        {
            return node->empty();
        }
    };

    template <typename T>
    struct PrimArray : Array<T>
    {
        explicit PrimArray(Node* _node)
            : Array<T>(_node)
        {
        }

        template <typename T, std::size_t... Is>
        void copyFromTuple(T const& rho, [[maybe_unused]] std::index_sequence<Is...> _indexes)
        {
            ((*this)[Is].set(std::get<Is>(rho)), ...);
        }

        template <typename T>
        struct What;

        template <typename V>
        Array<T>& operator=(V const& rho)
        {
            ENT_IF_COMPILE(V, arr, std::get<0>(arr)) // tuple, c-style array and std::array
            {
                if (std::tuple_size_v<V> != this->size())
                {
                    throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                }
                copyFromTuple(rho, std::make_index_sequence<std::tuple_size_v<V>>{});
            }
            else ENT_IF_COMPILE(V, arr, std::size(arr)) // All other dynamic containers
            {
                if (std::size(rho) != this->size())
                {
                    throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                }
                std::copy(std::begin(rho), std::end(rho), this->begin());
            }
            else static_assert(sizeof(V) == 0, "Unknown array type");
            return *this;
        }

        template <typename V, std::size_t... Is>
        void copyToTuple(V& point, [[maybe_unused]] std::index_sequence<Is...> _indexes)
        {
            ((std::get<Is>(point) = static_cast<std::tuple_element_t<Is, V>>((*this)[Is].get())),
             ...);
        }

        template <typename V>
        explicit operator V()
        {
            V result;
            ENT_IF_COMPILE(V, arr, std::get<0>(arr)) // tuple, c-style array and std::array
            {
                if (std::tuple_size_v<V> != this->size())
                {
                    throw std::runtime_error(R"(Incompatible array size in 'Array::operator=')");
                }
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
    auto begin(Array<T> arr)
    {
        return arr.begin();
    }

    template <typename T>
    auto end(Array<T> arr)
    {
        return arr.end();
    }

    template <typename E>
    E strToEnum(char const* in);

    namespace details
    {
        template <typename K>
        auto getKeys(Node* node)
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

        explicit UnionSetBase(Node* _node)
            : Base(_node)
        {
        }
        std::optional<Union> operator[](char const* str) const
        {
            if (auto sub = node->mapGet(str))
            {
                return sub;
            }
            return std::nullopt;
        }
        template <typename T>
        static char const* getTypeName()
        {
            std::string_view const name = typeid(T).name();
            auto const colon = name.find_last_of(':');
            if (colon == std::string_view::npos)
            {
                return name.data();
            }
            return name.data() + colon + 1;
        }

        Node* getSubNode(char const* str) const
        {
            if (auto const nvp = node->mapGet(str))
            {
                return nvp->getUnionData();
            }
            return nullptr;
        }
        template <typename T>
        std::optional<T> get() const
        {
            if (auto sub = getSubNode(getTypeName<T>()))
            {
                return sub;
            }
            return std::nullopt;
        }
        std::optional<Union> get(char const* str) const
        {
            if (auto sub = node->mapGet(str))
            {
                return sub;
            }
            return std::nullopt;
        }

        Node* addSubNode(char const* str) const
        {
            return node->mapInsert(str)->getUnionData();
        }
        template <typename T>
        T add() const
        {
            return addSubNode(getTypeName<T>());
        }
        bool remove(char const* str) const
        {
            return node->mapErase(str);
        }
        template <typename T>
        [[nodiscard]] bool remove() const
        {
            return remove(getTypeName<T>());
        }
        std::optional<Union> operator[](std::string const& str) const
        {
            return get(str.c_str());
        }

        [[nodiscard]] size_t size() const
        {
            return node->size();
        }

        [[nodiscard]] bool empty() const
        {
            return node->empty();
        }
        void clear() const
        {
            node->clear();
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

            Node* node = nullptr;
            std::vector<String> keys;
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

    inline char const* toInternal(String const& value)
    {
        return value.c_str();
    }

    template <typename T>
    struct PrimitiveSet : Base
    {
        explicit PrimitiveSet(Node* _node)
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

        [[nodiscard]] size_t size() const
        {
            return node->size();
        }

        [[nodiscard]] bool empty() const
        {
            return node->empty();
        }

        struct iterator
        {
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = size_t;
            using pointer = T const*;
            using reference = T const&;

            Node* node = nullptr;
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
        explicit ObjectSet(Node* _node)
            : Base(_node)
        {
        }
        std::optional<O> operator[](K key)
        {
            if (auto sub = node->mapGet(toInternal(key)))
            {
                return sub;
            }
            return std::nullopt;
        }
        std::optional<O> get(K key)
        {
            if (auto sub = node->mapGet(toInternal(key)))
            {
                return sub;
            }
            return std::nullopt;
        }
        O add(K key) const
        {
            return node->mapInsert(toInternal(key));
        }
        bool remove(K key) const
        {
            return node->mapErase(toInternal(key));
        }

        [[nodiscard]] size_t size() const
        {
            return node->size();
        }

        [[nodiscard]] bool empty() const
        {
            return node->empty();
        }

        void clear() const
        {
            return node->clear();
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

            Node* node = nullptr;
            std::vector<Node*> items;
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
        explicit Tuple(Node* _node)
            : Base(_node)
        {
        }

        template <auto I>
        std::tuple_element_t<I, std::tuple<Args...>> get()
        {
            return node->at(static_cast<size_t>(I));
        }

        [[nodiscard]] constexpr size_t size() const
        {
            return std::tuple_size_v<std::tuple<Args...>>;
        }
    };

    template <typename K, typename V>
    struct Map : Base
    {
        explicit Map(Node* _node)
            : Base(_node)
        {
        }
        std::optional<V> get(K key)
        {
            if (auto sub = node->mapGet(toInternal(key)))
            {
                return sub;
            }
            return std::nullopt;
        }
        std::optional<V> operator[](K key)
        {
            if (auto sub = node->mapGet(toInternal(key)))
            {
                return sub;
            }
            return std::nullopt;
        }
        V add(K key)
        {
            return node->mapInsert(toInternal(key));
        }
        bool remove(K key)
        {
            return node->mapErase(toInternal(key));
        }

        [[nodiscard]] size_t size() const
        {
            return node->size();
        }

        [[nodiscard]] bool empty() const
        {
            return node->empty();
        }

        void clear() const
        {
            node->clear();
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

            Node* node = nullptr;
            std::vector<Node*> items;
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
                auto keyToView = [](Node* keynode)
                {
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

        explicit PropHelper(Node* _node)
            : Base(_node)
        {
        }

        PropHelper& operator=(T value)
        {
            static_cast<P const*>(this)->set(value);
            return *this;
        }

        explicit operator T() const
        {
            return static_cast<P const*>(this)->get();
        }
    };

    template <typename Child, typename E>
    struct EnumPropHelper : PropHelper<Child, E>
    {
        using Enum = E;

        explicit EnumPropHelper(Node* _node)
            : PropHelper<Child, Enum>(_node)
        {
        }
        void set(Enum value) const
        {
            this->node->setString(toInternal(value));
        }
        Enum get() const
        {
            char const* str = this->node->getString();
            auto iter = std::find(
                std::begin(Child::enumToString), std::end(Child::enumToString), std::string_view(str));
            if (iter == std::end(Child::enumToString))
            {
                throw std::runtime_error(std::string("Unkown enum string '") + str + "'");
            }
            return Enum(std::distance(std::begin(Child::enumToString), iter));
        }
    };

    struct HelperObject : Base
    {
        explicit HelperObject(Node* _node)
            : Base(_node)
        {
        }

        /// path to the prefab Node
        [[nodiscard]] char const* getInstanceOf() const
        {
            return node->getInstanceOf();
        }

        /// Create a Node which is an "instance of" this one. With no override.
        [[nodiscard]] NodeUniquePtr makeInstanceOf() const
        {
            return node->makeInstanceOf();
        }

        /// Reset the Node to be an instance of the given \b _prefabNodePath
        ///
        /// @warning All sub-nodes into \b _node will be invalidated
        /// @param _prefabNodePath path to the prefab Node (relative to RawData)
        void resetInstanceOf(char const* _prefabNodePath) const
        {
            node->resetInstanceOf(_prefabNodePath);
        }

        void resetInstanceOf() const
        {
            node->resetInstanceOf();
        }

        /// @brief Change this Entity to be an instance of the given \b _newPrefab, keeping
        /// all internal values the same.
        /// @param _newPrefab path to the new prefab
        void changeInstanceOf(char const* _newPrefab) const
        {
            node->changeInstanceOf(_newPrefab);
        }

        void save(std::filesystem::path const& _destFile) const
        {
            node->saveNode(_destFile);
        }
    };

    struct Bool : PropHelper<Bool, bool>
    {
        explicit Bool(Node* _node)
            : PropHelper<Bool, bool>(_node)
        {
        }
        using PropHelper<Bool, bool>::operator=;
        void set(bool value) const
        {
            node->setBool(value);
        }

        [[nodiscard]] bool get() const
        {
            return node->getBool();
        }

        [[nodiscard]] bool getDefault() const
        {
            return node->getDefaultBool();
        }
    };

    struct Int : PropHelper<Int, int64_t>
    {
        explicit Int(Node* _node)
            : PropHelper<Int, int64_t>(_node)
        {
        }
        using PropHelper<Int, int64_t>::operator=;
        void set(int64_t value) const
        {
            node->setInt(value);
        }

        [[nodiscard]] int64_t get() const
        {
            return node->getInt();
        }

        [[nodiscard]] int64_t getDefault() const
        {
            return node->getDefaultInt();
        }
    };

    struct Float : PropHelper<Float, double>
    {
        explicit Float(Node* _node)
            : PropHelper<Float, double>(_node)
        {
        }
        using PropHelper<Float, double>::operator=;
        void set(double value) const
        {
            node->setFloat(value);
        }

        [[nodiscard]] double get() const
        {
            return node->getFloat();
        }

        [[nodiscard]] double getDefault() const
        {
            return node->getDefaultFloat();
        }

        explicit operator float() const
        {
            return static_cast<float>(node->getFloat());
        }

        [[nodiscard]] float toFloat() const
        {
            return static_cast<float>(node->getFloat());
        }
    };

    struct String : PropHelper<String, char const*>
    {
        explicit String(Node* _node)
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

        [[nodiscard]] char const* get() const
        {
            return node->getString();
        }

        [[nodiscard]] char const* c_str() const
        {
            return node->getString();
        }

        [[nodiscard]] char const* getDefault() const
        {
            return node->getDefaultString();
        }

        String const& operator=(std::string const& value) const
        {
            set(value);
            return *this;
        }

        explicit operator std::string() const
        {
            return get();
        }

        bool operator==(std::string const& value) const
        {
            return get() == value;
        }

        bool operator!=(std::string const& value) const
        {
            return get() != value;
        }

        explicit operator std::filesystem::path() const
        {
            return get();
        }

        [[nodiscard]] bool empty() const
        {
            return strlen(get()) == 0;
        }
    };

    struct EntityRef : PropHelper<EntityRef, Ent::EntityRef>
    {
        explicit EntityRef(Node* _node)
            : PropHelper<EntityRef, Ent::EntityRef>(_node)
        {
        }
        using PropHelper<EntityRef, Ent::EntityRef>::operator=;
        void set(Ent::EntityRef value) const
        {
            node->setEntityRef(std::move(value));
        }

        [[nodiscard]] Ent::EntityRef get() const
        {
            return node->getEntityRef();
        }

        [[nodiscard]] Ent::EntityRef getDefault() const
        {
            return node->getDefaultEntityRef();
        }
    };
} // namespace Ent::Gen
