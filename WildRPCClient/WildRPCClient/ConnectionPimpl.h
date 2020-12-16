#pragma once

#include <string>

#pragma warning(push, 0)
#pragma warning(disable : 4355)
#include "external/asio/include/asio.hpp"
#pragma warning(pop)

#include "include/WildRPCType.h"

namespace WRPC
{
    class ConnectionPimpl
    {
    public:
        std::string m_IPaddress;
        asio::io_context m_io_context;

        asio::ip::tcp::socket* m_socket = nullptr;

        ConnectionStatus m_status = ConnectionStatus::NotConnected;

        ConnectionPimpl(const char* _IPAddress);
        ~ConnectionPimpl();

        ConnectionPimpl(ConnectionPimpl const&) = delete;
        ConnectionPimpl& operator=(ConnectionPimpl const&) = delete;

        ConnectionStatus Open();

        void Close();
    };
} // namespace WRPC
