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

    template <typename... Args>
    inline std::string format(char const* message, Args&&... args)
    {
        // return std::string();
        std::string buffer(1024, ' ');
#ifdef _MSC_VER
        size_t const len =
            (size_t)_sprintf_p((char*)buffer.data(), 1024, message, std::forward<Args>(args)...);
        buffer.resize(len);
        if (len > 1024)
            _sprintf_p((char*)buffer.data(), len, std::forward<Args>(args)...);
#else
        auto const len = snprintf((char*)buffer.data(), 1024, std::forward<Args>(args)...);
        buffer.resize(len);
        if (len > 1024)
            snprintf((char*)buffer.data(), len, std::forward<Args>(args)...);
#endif
        return buffer;
    }

    inline void logicError(char const* _message, char const* _file, long _line)
    {
        fprintf(stderr, "%s(%ld): Assert failed : %s", _file, _line, _message);
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
