#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <cstdio>

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
    inline std::string format(char const* message, Args&&... args)
    {
        size_t const len = (size_t)snprintf(nullptr, 0, message, std::forward<Args>(args)...);
        std::string buffer(len, ' ');
        snprintf((char*)buffer.data(), len + 1, message, std::forward<Args>(args)...);
        return buffer;
    }

    /// Call it when a logic error (a bug) happen
    inline void logicError(char const* _message, char const* _file, long _line)
    {
        fprintf(stderr, "%s(%ld): Assert failed : %s\n", _file, _line, _message);
        terminate();
    }

} // namespace Ent

#define ENTLIB_LOGIC_ERROR(message, ...)                                                           \
    (void)((::Ent::logicError(::Ent::format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))

#define ENTLIB_ASSERT(expression)                                                                  \
    (void)((!!(expression)) || (::Ent::logicError(#expression, __FILE__, __LINE__), 0))

#define ENTLIB_ASSERT_MSG(expression, message, ...)                                                \
    (void)((!!(expression)) || (::Ent::logicError(::Ent::format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))

#ifdef _DEBUG
#define ENTLIB_DBG_ASSERT(expression)                                                              \
    (void)((!!(expression)) || (::Ent::logicError(#expression, __FILE__, __LINE__), 0))
#define ENTLIB_DBG_ASSERT_MSG(expression, message, ...)                                            \
    (void)((!!(expression)) || (::Ent::logicError(::Ent::format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))
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
        String()
        {
        }
        String(char const* _str)
        {
            auto len = strlen(_str);
            str = std::make_unique<char[]>(len + 1);
            strcpy(str.get(), _str);
        }
        String(std::string const& _str)
        {
            auto len = _str.size();
            str = std::make_unique<char[]>(len + 1);
            strcpy(str.get(), _str.c_str());
        }
        String(String const& ot)
        {
            if (ot.str == nullptr)
                return;
            auto len = ot.size();
            str = std::make_unique<char[]>(len + 1);
            strcpy(str.get(), ot.str.get());
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
                strcpy(str.get(), ot.str.get());
            }
            return *this;
        }
        String(String&& ot) = default;
        String& operator=(String&& ot) = default;

        bool operator==(String const& ot) const
        {
            return strcmp(str.get(), ot.str.get()) == 0;
        }

        bool operator<(String const& ot) const
        {
            return strcmp(str.get(), ot.str.get()) < 0;
        }

        char const* c_str() const
        {
            return str.get();
        }

        size_t capacity() const
        {
            return strlen(str.get());
        }

        size_t size() const
        {
            return strlen(str.get());
        }

        bool empty() const
        {
            return str == nullptr || size() == 0;
        }
    };
    /// @endcond
} // namespace Ent
