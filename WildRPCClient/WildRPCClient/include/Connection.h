#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <vector>

#include "WildRPCType.h"
#include "Parameter.h"

#pragma warning(push, 0)
#pragma warning(disable : 4355)
#include "../external/asio/include/asio.hpp"
#pragma warning(pop)

namespace WRPC
{
	class WRPC_DLLEXPORT Connection {

		friend class MethodInvocation;

	public:
		Connection(const char* _IPAddress);
		~Connection();

		ConnectionStatus		Open();
		void					Close();

		ConnectionStatus		GetStatus() { return m_status; }

	private:
		std::string				m_IPaddress;
		asio::io_context		m_io_context;

		asio::ip::tcp::socket*	m_socket_ThreadSafe = nullptr;
		asio::ip::tcp::socket*	m_socket_NOT_ThreadSafe = nullptr;

		ConnectionStatus		m_status = ConnectionStatus::NotConnected;
	};
}
