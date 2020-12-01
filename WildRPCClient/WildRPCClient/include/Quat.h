#pragma once

#include <cstdio>
#include <exception>
#include <string>

#include "WildRPCType.h"
#include "Parameter.h"

namespace WRPC
{
	class WRPC_DLLEXPORT Quat : public Parameter
	{
	public:
		Quat(const char* _name);

		void GetValues(float* _x, float* _y, float* _z, float* _w);
		void  SetValues(float _x, float _y, float _z, float _w);

		int8_t GetType() override { return (int8_t)RPC_Type::Quat; }

		bool EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)  override;
		bool DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)  override;

	private:
		float	m_values[4];

		const char*	m_name;

	};


}