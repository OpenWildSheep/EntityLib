#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <vector>

#include "WildRPCType.h"
#include "Parameter.h"

namespace WRPC
{
	class WRPC_DLLEXPORT Result
	{
		friend class MethodInvocation;

	public:		
		bool	HasError();

		void	AddParameter(const Parameter& _param);

		bool GetParameter(RPC_Type _type, const char* _name, unsigned short& _wx, unsigned short& _wy, float& _x, float& _y, float& _z)
		{
			Parameter* param = nullptr;
			bool ok = _GetParameter(_name, _type, &param);
			if (!ok) { return false; }

			param->GetValues(_wx, _wy, _x, _y, _z);
			return true;
		}

		bool GetParameter(RPC_Type _type, const char* _name, float& _x, float& _y, float& _z, float& _w)
		{
			Parameter* param = nullptr;
			bool ok = _GetParameter(_name, _type, &param);
			if (!ok) { return false; }

			param->GetValues(_x, _y, _z, _w);
			return true;
		}

		bool GetParameter(RPC_Type _type, const char* _name, float& _value)
		{
			Parameter* param = nullptr;
			bool ok = _GetParameter(_name, _type, &param);
			if (!ok) { return false; }

			param->GetValue(_value);
			return true;
		}

	private:
		bool _GetParameter(const char* _paramName, RPC_Type _type, Parameter** _param);

	private:
		std::vector<Parameter>		m_parameters;
		RPC_Error					m_error;
	};
}