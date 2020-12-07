#include "include/Connection.h"

#include <iostream>
#include <array>

#define SERV_PORT_NOT_THREAD_SAFE "9387"
#define SERV_PORT_THREAD_SAFE     "9993"

namespace WRPC
{
	Connection::Connection(const char* _IPAddress) : m_IPaddress(_IPAddress) {}

	ConnectionStatus Connection::Open()
	{
		try
		{
			asio::ip::tcp::resolver resolver(m_io_context);

			m_socket_NOT_ThreadSafe = new asio::ip::tcp::socket(m_io_context);
			asio::connect(*m_socket_NOT_ThreadSafe, resolver.resolve(m_IPaddress.c_str(), SERV_PORT_NOT_THREAD_SAFE));

			m_socket_ThreadSafe = new asio::ip::tcp::socket(m_io_context);
			asio::connect(*m_socket_ThreadSafe, resolver.resolve(m_IPaddress.c_str(), SERV_PORT_THREAD_SAFE));
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
			return ConnectionStatus::ExplicitelyDeniedByServer;
		}

		return (m_status = ConnectionStatus::Connected);
	}
}
