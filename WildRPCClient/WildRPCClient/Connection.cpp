#include "include/Connection.h"

#include <iostream>
#include <array>

#include "ConnectionPimpl.h"

#define SERV_PORT "9387"

namespace WRPC
{
	Connection::Connection(const char* _IPAddress)
		: m_pimpl(std::make_unique<ConnectionPimpl>(_IPAddress))
	{
	}

	Connection::~Connection()
	{
		m_pimpl->Close();
	}

	ConnectionStatus Connection::Open()
	{
		return m_pimpl->Open();
	}

	void Connection::Close()
	{
		m_pimpl->Close();
	}

	ConnectionStatus Connection::GetStatus() const
	{
		return m_pimpl->m_status;
	}

} // namespace WRPC
