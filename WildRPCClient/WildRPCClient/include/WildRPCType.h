#pragma once

#if defined(WRPC_DYNAMIC_EXPORT)
#define WRPC_DLLEXPORT __declspec(dllexport)
#elif defined(WRPC_DYNAMIC_IMPORT)
#define WRPC_DLLEXPORT __declspec(dllimport)
#else
#define WRPC_DLLEXPORT
#endif

namespace WRPC
{
	enum class ConnectionStatus
	{
		NotConnected = 0,
		Connected,
		Errored
	};

	struct RPC_Error
	{
		unsigned char m_protocolError = 0;
		unsigned char m_applicativeError = 0;
	};

	enum class ThreadSafety
	{
		Safe,
		Unsafe
	};

}