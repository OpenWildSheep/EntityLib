#include "include/Connection.h"

#include <iostream>
#include <array>

#define SERV_PORT "9387"

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

			m_socket = new asio::ip::tcp::socket(m_io_context);
			asio::connect(*m_socket, resolver.resolve(m_IPaddress.c_str(), SERV_PORT));
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
			if (m_socket)
			{
				m_socket->close();
				delete m_socket;
				m_socket = nullptr;
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
			m_status = ConnectionStatus::Errored;
		}
	}
}
