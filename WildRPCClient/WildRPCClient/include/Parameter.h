#pragma once

#include "WildRPCType.h"

#include <string>

class WRPC_DLLEXPORT Parameter
{
public:
	Parameter(const char* _name, Argument _inout) : m_argumentInOut(_inout), m_name(_name) {}

	static RPC_Type GetRPCType() { return RPC_Type::None; }
	
	virtual RPC_Type GetType() { return RPC_Type::None; }
	Argument		 GetArgument() { return m_argumentInOut; }

	virtual bool EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset) { printf("%s %d %p\n", _buffer, (int)_totalBufferSize, _offset);  return false; }
	virtual bool DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset) { printf("%s %d %p\n", _buffer, (int)_totalBufferSize, _offset); return false; }

	void		 SetName(const char* _name) { m_name = _name; }
	const char*  GetName() { return m_name; }

protected:
	Argument	m_argumentInOut = Argument::In;
	const char* m_name = nullptr;
};