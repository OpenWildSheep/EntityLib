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
        size_t const len = (size_t)sprintf_s(nullptr, 0, message, std::forward<Args>(args)...);
        std::string buffer(len, ' ');
        sprintf_s((char*)buffer.data(), len, std::forward<Args>(args)...);
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
    (void)((::Ent::logicError(format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))

#define ENTLIB_ASSERT(expression)                                                                  \
    (void)((!!(expression)) || (::Ent::logicError(#expression, __FILE__, __LINE__), 0))

#define ENTLIB_ASSERT_MSG(expression, message, ...)                                                \
    (void)((!!(expression)) || (::Ent::logicError(format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))

#ifdef _DEBUG
#define ENTLIB_DBG_ASSERT(expression)                                                              \
    (void)((!!(expression)) || (::Ent::logicError(#expression, __FILE__, __LINE__), 0))
#define ENTLIB_DBG_ASSERT_MSG(expression, message, ...)                                            \
    (void)((!!(expression)) || (::Ent::logicError(format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))
#else
#define ENTLIB_DBG_ASSERT(expression) ((void)0)
#define ENTLIB_DBG_ASSERT_MSG(expression, ...) ((void)0)
#endif
