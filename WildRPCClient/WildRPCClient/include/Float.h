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
		Float(const char* _name);

		float GetValue() { return m_value; }
		void  SetValue(float _value) { m_value = _value; }

		int8_t GetType() override { return (int8_t)RPC_Type::Float; }

		bool EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)  override;
		bool DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)  override;

	private:
		float		m_value = 0.0f;
		const char*	m_name;

	};


}