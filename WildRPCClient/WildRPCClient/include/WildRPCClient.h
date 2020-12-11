#pragma once

#include <cstdio>
#include <exception>
#include <string>

#pragma warning(push, 0)
#pragma warning(disable : 4355)
#include "../external/asio/include/asio.hpp"
#pragma warning(pop)

#include "WildRPCType.h"
#include "Connection.h"
#include "MethodInvocation.h"

namespace WRPC
{
    /// @cond PRIVATE

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

    /// @endcond

} // namespace WRPC

#define WRPC_LOGIC_ERROR(message, ...)                                                             \
    (void)((::WRPC::logicError(::WRPC::format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))

#define WRPC_ASSERT(expression)                                                                    \
    (void)((!!(expression)) || (::WRPC::logicError(#expression, __FILE__, __LINE__), 0))

#define WRPC_ASSERT_MSG(expression, message, ...)                                                  \
    (void)((!!(expression)) || (::WRPC::logicError(::WRPC::format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))

#ifdef _DEBUG
#define WRPC_DBG_ASSERT(expression)                                                                \
    (void)((!!(expression)) || (::WRPC::logicError(#expression, __FILE__, __LINE__), 0))
#define WRPC_DBG_ASSERT_MSG(expression, message, ...)                                              \
    (void)((!!(expression)) || (::WRPC::logicError(::WRPC::format(message, __VA_ARGS__).c_str(), __FILE__, __LINE__), 0))
#else
#define WRPC_DBG_ASSERT(expression) ((void)0)
#define WRPC_DBG_ASSERT_MSG(expression, ...) ((void)0)
#endif

namespace WRPC
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
            WRPC_ASSERT(state_ == State::VALID);
            state_ = State::DELETED;
        }
    };
    /// @endcond

    class WRPC_DLLEXPORT RPCClient
    {
	public:
		bool test();

    public:
        DeleteCheck deleteCheck;

        RPCClient();
        ~RPCClient();

        RPCClient(RPCClient const&) = delete;
        RPCClient& operator=(RPCClient const&) = delete;
        RPCClient(RPCClient&&) = delete;
        RPCClient& operator=(RPCClient&&) = delete;
    };
} // namespace WRPC
