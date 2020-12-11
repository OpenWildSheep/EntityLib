#include "include/Connection.h"

#include <iostream>
#include <array>

#define SERV_PORT_NOT_THREAD_SAFE "9387"
#define SERV_PORT_THREAD_SAFE     "9993"

namespace WRPC
{
	Connection::Connection(const char* _IPAddress) : m_IPaddress(_IPAddress) {}
	Connection::~Connection()
	{
		Close();
	}

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
			return ConnectionStatus::Errored;
		}

		return (m_status = ConnectionStatus::Connected);
	}

	void Connection::Close()
	{
		if (m_status != ConnectionStatus::Connected)
		{
			return;
		}

		m_status = ConnectionStatus::NotConnected;
		try
		{
			if (m_socket_NOT_ThreadSafe)
			{
				m_socket_NOT_ThreadSafe->close();
				delete m_socket_NOT_ThreadSafe;
				m_socket_NOT_ThreadSafe = nullptr;
			}

			if (m_socket_ThreadSafe)
			{
				m_socket_ThreadSafe->close();
				delete m_socket_ThreadSafe;
				m_socket_ThreadSafe = nullptr;
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
			m_status = ConnectionStatus::Errored;
		}
	}
}
