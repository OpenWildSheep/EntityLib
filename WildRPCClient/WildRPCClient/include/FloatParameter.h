#pragma once

#include <cstdio>
#include <exception>
#include <string>

#include "WildRPCType.h"
#include "Parameter.h"

namespace WRPC
{
	class WRPC_DLLEXPORT Float : public Parameter
	{
	public:
		Float(const char* _name, Argument _inout);
		Float(Float* _original);

		float GetValue() { return m_value; }
		void  SetValue(float _value) { m_value = _value; }

		static RPC_Type GetRPCType() { return RPC_Type::Float; }
		RPC_Type GetType() override { return RPC_Type::Float; }

		bool EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)  override;
		bool DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)  override;

	private:
		float		m_value = 0.0f;

	};


}