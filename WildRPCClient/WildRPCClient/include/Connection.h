#pragma once

#include "WildRPCType.h"

#include <memory>

namespace WRPC
{
    class ConnectionPimpl;

    class WRPC_DLLEXPORT Connection
    {

        friend class MethodInvocation;

    public:
        Connection(const char* _IPAddress);
        ~Connection();

        // No copy, no assign ----------------------------
        Connection(Connection const&) = delete;
        Connection& operator=(Connection const&) = delete;

        ConnectionStatus Open();
        void Close();

        ConnectionStatus GetStatus() const;

    private:
        std::unique_ptr<ConnectionPimpl> m_pimpl;
    };
} // namespace WRPC
