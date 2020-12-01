#pragma once

#if defined(WRPC_DYNAMIC_EXPORT)
#define WRPC_DLLEXPORT __declspec(dllexport)
#elif defined(WRPC_DYNAMIC_IMPORT)
#define WRPC_DLLEXPORT __declspec(dllimport)
#else
#define WRPC_DLLEXPORT
#endif

enum class RPC_Type
{
	Boolean = 0,
	Integer,
	Float,
	Vector2,
	UInt3,
	Vector3,
	Quat,
	Color,
	Position
};

struct RPC_Error
{
	unsigned char m_protocolError = 0;
	unsigned char m_applicativeError = 0;
};