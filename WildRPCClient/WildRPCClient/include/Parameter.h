#pragma once

#include "WildRPCType.h"

#include <string>

class WRPC_DLLEXPORT Parameter
{
public:
	virtual int8_t GetType() = 0;

	virtual bool EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset) = 0;
	virtual bool DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset) = 0;
};