#pragma once

#include "WildRPCType.h"

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

		// No copy, no assign ----------------------------
		Connection(Connection const&) = delete;
		Connection& operator=(Connection const&) = delete;

		ConnectionStatus		Open();
		void					Close();

		ConnectionStatus		GetStatus() const { return m_status; }

	private:
		std::string				m_IPaddress;
		asio::io_context		m_io_context;

		asio::ip::tcp::socket*	m_socket = nullptr;

		ConnectionStatus		m_status = ConnectionStatus::NotConnected;
	};
}
