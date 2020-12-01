#pragma once

#include "WildRPCType.h"

#include <string>

class WRPC_DLLEXPORT Parameter
{
public:
	virtual RPC_Type GetType() = 0;

	virtual bool EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset) = 0;
	virtual bool DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset) = 0;

	void		 SetName(const char* _name) { m_name = _name; }
	const char*  GetName() { return m_name; }

protected:
	const char* m_name = nullptr;
};