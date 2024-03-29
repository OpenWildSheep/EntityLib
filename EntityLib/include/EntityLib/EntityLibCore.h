#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <cstdio>
#include <memory>
#include <vector>
#include <stdexcept>
#include <array>
#include <filesystem>

#include "../Exception.h"

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
    /// Exception thrown when calling a method of a Node which has not the apropriate Ent::DataKind
    struct JsonValidation : std::runtime_error
    {
        /// Make a JsonValidation with the given _message
        explicit JsonValidation(std::string const& _message)
            : std::runtime_error(_message){};
    };

    /// A printf-like function which return a std::string
    template <typename... Args>
    std::string format(char const* message, Args&&... args)
    {
        RAH2_WARNING_PUSH
#if defined(__GNUC__) || defined(__clang__)
        RAH2_DISABLE_WARNING("-Wformat-security")
#endif
        auto const len =
            static_cast<size_t>(snprintf(nullptr, 0, message, std::forward<Args>(args)...));
        std::string buffer(len, ' ');
        snprintf(buffer.data(), len + 1, message, std::forward<Args>(args)...);
        RAH2_WARNING_POP
        return buffer;
    }

    /// @brief printf in a local static buffer.
    /// @warning Each call will change the buffer content.
    ///             Do not use the output of staticFormat as inpout of staticFormat.
    template <typename... Args>
    char const* staticFormat(char const* message, Args&&... args)
    {
        thread_local static char buffer[2048];
        snprintf(buffer, sizeof(buffer), message, std::forward<Args>(args)...);
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
        snprintf(mess, sizeof(mess), "%s%s\n", "%s%s(%ld) : ", _message);
        fprintfmt(_output, mess, _category, _file, _line, std::forward<Args>(args)...);
    }

    /// format and print the message into stderr
    template <typename... Args>
    void logError(char const* _file, long _line, char const* _message, Args&&... args)
    {
        log(_file, _line, stderr, "ERROR : ", _message, std::forward<Args>(args)...);
    }

    enum class LogicErrorPolicy
    {
        Terminate,
        Throw
    };

    extern LogicErrorPolicy s_LogicErrorPolicy;

} // namespace Ent

/// Call it when a logic error (a bug) happen.
/// Format and print the message into stderr then call terminate or throw
///( depending on LogicErrorPolicy)
#define ENTLIB_LOGIC_ERROR(...)                                                                    \
    do                                                                                             \
    {                                                                                              \
        ::Ent::logError(__FILE__, __LINE__, __VA_ARGS__);                                          \
        if (Ent::s_LogicErrorPolicy == Ent::LogicErrorPolicy::Terminate)                           \
            std::terminate();                                                                      \
        else                                                                                       \
            throw std::logic_error(Ent::format(__VA_ARGS__));                                      \
    } while (0)

/// Call it when a logic error (a bug) happen in a destructor.
/// Format and print the message into stderr then call terminate or not
///( depending on LogicErrorPolicy)
#define ENTLIB_LOGIC_ERROR_NOTHROW(...)                                                            \
    do                                                                                             \
    {                                                                                              \
        ::Ent::logError(__FILE__, __LINE__, __VA_ARGS__);                                          \
        if (Ent::s_LogicErrorPolicy == Ent::LogicErrorPolicy::Terminate)                           \
            std::terminate();                                                                      \
    } while (0)

#define ENTLIB_LOG(...) (void)((::Ent::log(__FILE__, __LINE__, stdout, "", __VA_ARGS__), 0))

#define ENTLIB_LOG_ERROR(...) (void)((::Ent::logError(__FILE__, __LINE__, __VA_ARGS__), 0))

#define ENTLIB_ASSERT(expression)                                                                  \
    if (!(expression))                                                                             \
        ENTLIB_LOGIC_ERROR(#expression);                                                           \
    else                                                                                           \
        (void)0

#define ENTLIB_ASSERT_NOTHROW(expression)                                                          \
    if (!(expression))                                                                             \
        ENTLIB_LOGIC_ERROR_NOTHROW(#expression);                                                   \
    else                                                                                           \
        (void)0

#define ENTLIB_ASSERT_MSG(expression, ...)                                                         \
    if (!(expression))                                                                             \
        ENTLIB_LOGIC_ERROR(__VA_ARGS__);                                                           \
    else                                                                                           \
        (void)0

#define ENTLIB_ASSERT_MSG_NOTHROW(expression, ...)                                                 \
    if (!(expression))                                                                             \
        ENTLIB_LOGIC_ERROR_NOTHROW(__VA_ARGS__);                                                   \
    else                                                                                           \
        (void)0

#ifdef _DEBUG
#define ENTLIB_DBG_ASSERT(expression) ENTLIB_ASSERT(expression)
#define ENTLIB_DBG_ASSERT_MSG(expression, ...) ENTLIB_ASSERT_MSG(expression, __VA_ARGS__)
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
            if (state_ != State::VALID)
            {
                // Can't throw in a destructor
                ENTLIB_LOG_ERROR("In ~DeleteCheck() : state_ != State::VALID");
            }
            state_ = State::DELETED;
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
        std::vector<std::vector<std::aligned_storage_t<sizeof(T), alignof(T)>>> buckets;
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
            ENTLIB_ASSERT(allocatedCount > 0);
            --allocatedCount;
            freePtr.push_back(ptr);
        }
    };

    char const* formatPath(std::filesystem::path const& _base, std::filesystem::path const& _rel);

    struct InvalidKey : std::logic_error
    {
        template <typename Map>
        static std::string makeError(
            [[maybe_unused]] Map const& _map,
            std::string const& key,
            char const* file,
            long line,
            char const* func)
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
        {
            return iter->second;
        }
        throw InvalidKey(map, key, file, line, func);
    }

#define AT(MAP, KEY) ::Ent::at(MAP, KEY, __FILE__, __LINE__, __func__)
    /// @endcond

    // ******************************** Exception declarations ************************************

    struct Exception : std::runtime_error
    {
        explicit Exception(char const* _message = nullptr); ///< ctor
    };

    /// Exception thrown when calling a method of a Node which has not the apropriate Ent::DataKind
    struct BadType : ContextException
    {
        explicit BadType(char const* _message = nullptr); ///< ctor
    };

    struct BadArrayType : ContextException
    {
        explicit BadArrayType(char const* _message = nullptr); ///< ctor
    };

    /// Exception thrown when a metadata is missing in the json schema
    ///
    /// Example : oneOf need className and classData
    struct MissingMetadata : ContextException
    {
        explicit MissingMetadata(char const* _schemaName); ///< ctor
    };

    /// Exception thrown when trying to violate some Schema rules
    struct BreakSchemaRules : ContextException
    {
        /// ctor
        explicit BreakSchemaRules(char const* _message);
    };

    /// Exception thrown when trying to switch a Union to a type that woesn't exit
    struct BadUnionType : BreakSchemaRules
    {
        /// ctor
        explicit BadUnionType(char const* _type ///< The type/className that doen't exist in this union
        );
    };

    /// Exception thrown when a schema is ill-formed
    struct IllFormedSchema : ContextException
    {
        explicit IllFormedSchema(char const* _message); ///< ctor
    };

    /// Exception thrown when some json data are invalid
    struct InvalidJsonData : ContextException
    {
        explicit InvalidJsonData(char const* _message); ///< ctor
    };


    /// Exception thrown when some json data are invalid
    struct CantRename : ContextException
    {
        explicit CantRename(char const* _message) ///< ctor
            : ContextException(_message)
        {
        }
    };

    struct DuplicateKey : ContextException
    {
        explicit DuplicateKey(std::string const& _message) ///< ctor
            : ContextException(_message)
        {
        }
    };

    /// Exception thrown when some json data are invalid
    struct EmptyKey : ContextException
    {
        explicit EmptyKey(char const* _message) ///< ctor
            : ContextException(_message)
        {
        }
    };

    struct NullPointerArgument : ContextException
    {
        NullPointerArgument(char const* _argName, char const* funcName)
            : ContextException("'%s' is null in function '%s'", _argName, funcName)
        {
        }
    };

    struct BadKey : ContextException
    {
        BadKey(char const* key, char const* funcName, char const* schemaName)
            : ContextException(
                "Unknown key '%s' in function '%s', in schema '%s'", key, funcName, schemaName)
        {
        }
    };

    struct UnknownSchema : ContextException
    {
        UnknownSchema(char const* rootPath, char const* filenameName)
            : ContextException("Can't find schema of file %s", formatPath(rootPath, filenameName))
        {
        }
    };

    struct UnrelatedNodes : ContextException
    {
        UnrelatedNodes()
            : ContextException("Nodes from different documents")
        {
        }
    };

    struct WrongPath : ContextException
    {
        explicit WrongPath(char const* _message)
            : ContextException(_message)
        {
        }
    };

    template <typename V, typename F>
    static constexpr decltype(std::is_invocable_v<F, V>) doesCompile([[maybe_unused]] F&& _lambda)
    {
        return std::is_invocable_v<F, V>;
    }

#define ENT_IF_COMPILE(TYPE, PARAM, CODE)                                                          \
    if constexpr (Ent::doesCompile<TYPE>([](auto && (PARAM)) -> decltype(CODE) {}))

    /// @brief Path to found a Node, from an other Node.
    ///
    /// Token are separated by slashes.
    ///
    /// Sample of how to get a sub entity : `Components/SubScene/Embedded/Wolf1`
    /// - In an Object, the expected token is the field.
    /// - In a Union, the expected token is the inner type of the Union.
    /// - In an Array, the expected token is the index.
    /// - In a Map or Set, the expected token is the key.
    ///     - In a UnionSet, the key is the type. No need to explicit the Union type again.
    ///         - ex : good : `Components/TransformGD/Position`
    ///         - ex : bad : `Components/TransformGD/TransformGD/Position`
    ///
    using NodeRef = std::string;

    struct EntityRef
    {
        /// @brief string representation of this entity ref, works like a file path, always relative.
        std::string entityPath;

        bool operator==(EntityRef const& _rho) const
        {
            return entityPath == _rho.entityPath;
        }

        bool operator!=(EntityRef const& _rho) const
        {
            return !(*this == _rho);
        }
    };

    enum class CopyMode
    {
        CopyOverride, ///< Always override in dest when there is override in source
        MinimalOverride ///< Do not override when values are identicals
    };

    /// @brief The possible source of an Override value
    enum class OverrideValueSource
    {
        /// Value is set in this Override. Write the "InstanceOf" field.
        Override,
        /// Value is set in the Prefab or in this Override. Don't write the "InstanceOf" field.
        OverrideOrPrefab,
        /// Value can be any source: Override, Prefab or the default value. Don't write the "InstaneOf" field.
        Any,
    };
} // namespace Ent
