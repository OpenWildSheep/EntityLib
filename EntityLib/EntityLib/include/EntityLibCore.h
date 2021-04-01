#pragma once

#pragma warning(push, 0)
#include <cstdio>
#include <exception>
#include <string>
#include <cstdio>
#include <memory>
#include <vector>
#include <stdexcept>
#pragma warning(pop)

#ifdef ENTLIB_STATIC
#define ENTLIB_DLLEXPORT
#else
#ifdef ENTLIB_DYNAMIC
#define ENTLIB_DLLEXPORT __declspec(dllexport)
#else
#define ENTLIB_DLLEXPORT __declspec(dllimport)
#endif
#endif

namespace Ent
{
    /// Exception thrown when calling a method of a Node which has not the apropriate Ent::DataType
    struct JsonValidation : std::runtime_error
    {
        /// Make a JsonValidation with the given _message
        JsonValidation(std::string _message)
            : std::runtime_error(std::move(_message)){};
    };

    /// A printf-like function which return a std::string
    template <typename... Args>
    std::string format(char const* message, Args&&... args)
    {
        size_t const len = (size_t)snprintf(nullptr, 0, message, std::forward<Args>(args)...);
        std::string buffer(len, ' ');
        snprintf((char*)buffer.data(), len + 1, message, std::forward<Args>(args)...);
        return buffer;
    }

    /// print the message into the output and also in the VisualStudio debugger if possible
    void fprintfImpl(FILE* file, char const* message);

    /// format and print the message into the output and also in the VisualStudio debugger if possible
    template <typename... Args>
    void fprintfmt(FILE* output, char const* message, Args&&... args)
    {
        fprintfImpl(output, format(message, std::forward<Args>(args)...).c_str());
    }

    /// format and print the message into stdout and also in the VisualStudio debugger if possible
    template <typename... Args>
    void printfmt(char const* message, Args&&... args)
    {
        fprintfmt(stdout, message, std::forward<Args>(args)...);
    }

    /// format the message, adding _file, _line and _category, and print in the _output
    template <typename... Args>
    void
    log(char const* _file,
        long _line,
        FILE* _output,
        char const* _category,
        char const* _message,
        Args&&... args)
    {
        char mess[1024]; // format string are usually short
        sprintf_s(mess, sizeof(mess), "%s%s\n", "%s%s(%ld) : ", _message);
        fprintfmt(_output, mess, _category, _file, _line, std::forward<Args>(args)...);
    }

    /// Call it when a logic error (a bug) happen
    /// format and print the message into stderr and call terminate
    template <typename... Args>
    void logicError(char const* _file, long _line, char const* _message, Args&&... args)
    {
        log(_file, _line, stderr, "ERROR : ", _message, std::forward<Args>(args)...);
        terminate();
    }
} // namespace Ent

#define ENTLIB_LOGIC_ERROR(message, ...)                                                           \
    (void)((::Ent::logicError(__FILE__, __LINE__, message, __VA_ARGS__), 0))

#define ENTLIB_LOG(message, ...)                                                                   \
    (void)((::Ent::log(__FILE__, __LINE__, stdout, "", message, __VA_ARGS__), 0))

#define ENTLIB_LOG_ERROR(message, ...)                                                             \
    (void)((::Ent::log(__FILE__, __LINE__, stderr, "ERROR : ", message, __VA_ARGS__), 0))

#define ENTLIB_ASSERT(expression)                                                                  \
    (void)((!!(expression)) || (::Ent::logicError(__FILE__, __LINE__, #expression), 0))

#define ENTLIB_ASSERT_MSG(expression, message, ...)                                                \
    (void)((!!(expression)) || (::Ent::logicError(__FILE__, __LINE__, message, __VA_ARGS__), 0))

#ifdef _DEBUG
#define ENTLIB_DBG_ASSERT(expression)                                                              \
    (void)((!!(expression)) || (::Ent::logicError(__FILE__, __LINE__, #expression), 0))
#define ENTLIB_DBG_ASSERT_MSG(expression, message, ...)                                            \
    (void)((!!(expression)) || (::Ent::logicError(__FILE__, __LINE__, message, __VA_ARGS__), 0))
#else
#define ENTLIB_DBG_ASSERT(expression) ((void)0)
#define ENTLIB_DBG_ASSERT_MSG(expression, ...) ((void)0)
#endif

namespace Ent
{
    /// @cond PRIVATE
    /// Used to detect access to uninitialized or freed memory
    struct DeleteCheck
    {
        enum class State
        {
            VALID = 0x91AC1F0,
            DELETED = 0xCCDA459
        } state_ = State::VALID;

        ~DeleteCheck()
        {
            ENTLIB_ASSERT(state_ == State::VALID);
            state_ = State::DELETED;
        }
    };

    /// A string class which has the size of a pointer
    struct String
    {
        std::unique_ptr<char[]> str;
        String() = default;
        String(char const* _str)
        {
            auto len = strlen(_str);
            str = std::make_unique<char[]>(len + 1);
            strcpy_s(str.get(), len + 1, _str);
        }
        String(std::string const& _str)
        {
            auto len = _str.size();
            str = std::make_unique<char[]>(len + 1);
            strcpy_s(str.get(), len + 1, _str.c_str());
        }
        String(String const& ot)
        {
            if (ot.str == nullptr)
                return;
            auto len = ot.size();
            str = std::make_unique<char[]>(len + 1);
            strcpy_s(str.get(), len + 1, ot.str.get());
        }
        String& operator=(String const& ot)
        {
            if (ot.str == nullptr)
            {
                str.reset();
            }
            else
            {
                auto len = ot.size();
                str = std::make_unique<char[]>(len + 1);
                strcpy_s(str.get(), len + 1, ot.str.get());
            }
            return *this;
        }
        String(String&& ot) = default;
        String& operator=(String&& ot) = default;

        bool operator==(String const& ot) const
        {
            if (str == nullptr)
            {
                return ot.size() == 0; // null and size 0 are identical in the std::string way
            }
            if (ot.str == nullptr)
            {
                return size() == 0;
            }
            return strcmp(str.get(), ot.str.get()) == 0;
        }

        bool operator<(String const& ot) const
        {
            if (str == nullptr)
            {
                if (ot.str == nullptr)
                {
                    return false;
                }
                else
                    return true;
            }
            if (ot.str == nullptr)
            {
                return false;
            }
            return strcmp(str.get(), ot.str.get()) < 0;
        }

        char const* c_str() const
        {
            return str.get();
        }

        size_t capacity() const
        {
            return size();
        }

        size_t size() const
        {
            if (str == nullptr)
                return 0;
            return strlen(str.get());
        }

        bool empty() const
        {
            return str == nullptr || size() == 0;
        }

        operator std::string() const
        {
            if (str == nullptr)
                return std::string();
            return std::string(str.get());
        }
    };

    /// Extremely simple memory pool. Not thread-safe and can't alloc array.
    /// Since there is millions of Nodes 1024 is not enought
    template <typename T, size_t BucketSize = 1024 * 1024>
    struct Pool
    {
        ~Pool()
        {
            if (allocatedCount != 0)
            {
                ENTLIB_LOG_ERROR("EntityLib is deleted but some Nodes are not deleted yet!");
            }
        }
        size_t allocatedCount = 0;
        std::vector<void*> freePtr;
        std::vector<std::vector<typename std::aligned_storage<sizeof(T), alignof(T)>::type>> buckets;
        void* alloc()
        {
            if (freePtr.empty())
            {
                buckets.emplace_back(BucketSize);
                auto&& lastBucket = buckets.back();
                for (auto iter = lastBucket.begin(); iter != lastBucket.end(); ++iter)
                {
                    freePtr.push_back(&(*iter));
                }
            }
            void* ptr = freePtr.back();
            freePtr.pop_back();
            ++allocatedCount;
            return ptr;
        }

        void free(void* ptr)
        {
            --allocatedCount;
            freePtr.push_back(ptr);
        }
    };

    /// @brief smart-pointer with deep-copy
    ///
    /// It is like a unique_ptr but copyable (deep-copy)
    /// It is like an optional but heap allocated
    /// It is like a vector with a size of 1
    ///
    /// This class is only for the Node type
    template <typename T>
    struct value_ptr
    {
        struct Deleter
        {
            void operator()(T* ptr) const
            {
                destroyAndFree(ptr);
            }
        };

        std::unique_ptr<T, Deleter> ptr;

        value_ptr() = default;
        value_ptr(value_ptr const& ot)
        {
            *this = ot;
        }

        template <typename... Args>
        void initPtr(Pool<T>& pool, Args&&... args)
        {
            ptr.reset(new (pool.alloc()) T(std::forward<Args>(args)...));
        }

        value_ptr(T const& data)
        {
            initPtr(getPool(&data), data);
        }
        explicit value_ptr(T const* data)
        {
            if (data != nullptr)
                initPtr(getPool(data), *data);
        }
        value_ptr(T&& data)
        {
            initPtr(getPool(&data), std::move(data));
        }
        value_ptr(nullptr_t)
        {
        }
        value_ptr& operator=(value_ptr const& ot)
        {
            if (ptr != nullptr)
            {
                if (ot.ptr != nullptr)
                    *ptr = *ot.ptr;
                else
                    ptr.reset();
            }
            else
            {
                if (ot.ptr != nullptr)
                    initPtr(getPool(ot.ptr.get()), *ot);
            }
            return *this;
        }
        value_ptr(value_ptr&& ot) = default;
        value_ptr& operator=(value_ptr&& ot) = default;

        ~value_ptr() = default;

        T& operator*()
        {
            return *ptr;
        }
        T const& operator*() const
        {
            return *ptr;
        }
        T* operator->()
        {
            return ptr.get();
        }
        T const* operator->() const
        {
            return ptr.get();
        }
        T* get()
        {
            return ptr.get();
        }
        T const* get() const
        {
            return ptr.get();
        }

        bool operator==(nullptr_t) const
        {
            return ptr == nullptr;
        }

        bool operator!=(nullptr_t) const
        {
            return ptr != nullptr;
        }

        operator bool() const
        {
            return ptr == nullptr;
        }

        bool has_value() const
        {
            return ptr != nullptr;
        }
    };

    template <typename T, typename... Args>
    value_ptr<T> make_value(Args&&... args)
    {
        return value_ptr<T>(T(std::forward<Args>(args)...));
    }

    std::string convertANSIToUTF8(std::string const& message);

    struct InvalidKey : std::logic_error
    {
        template <typename Map>
        std::string
        makeError(Map const&, std::string const& key, char const* file, long line, char const* func)
        {
            return format(
                "%s(%d) : (%s) Can't find key '%s' in map of type '%s'",
                file,
                line,
                func,
                key.c_str(),
                typeid(Map).name());
        }

        template <typename Map>
        InvalidKey(Map const& map, std::string const& key, char const* file, long line, char const* func)
            : std::logic_error(makeError(map, key.c_str(), file, line, func))
        {
        }

        template <typename Map>
        InvalidKey(Map const& map, char const* key, char const* file, long line, char const* func)
            : std::logic_error(makeError(map, key, file, line, func))
        {
        }
    };

    template <typename Map, typename Key>
    auto at(Map&& map, Key const& key, char const* file, long line, char const* func)
        -> decltype(map.at(key))
    {
        auto iter = map.find(key);
        if (iter != map.end())
            return iter->second;
        else
            throw InvalidKey(map, key, file, line, func);
    }

#define AT(MAP, KEY) ::Ent::at(MAP, KEY, __FILE__, __LINE__, __func__)
    /// @endcond
} // namespace Ent
