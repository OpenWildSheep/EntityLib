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
		// non copyable
		Result(const Result& _other) = delete;
		Result& operator=(const Result& _other) = delete;

		// non movable
		Result(Result&& _other) = delete;
		Result& operator=(Result&& _other) = delete;

		Result() {}
		~Result();
		
		bool	HasError();

		void	AddParameter(Parameter* _param);

		template <class T>
		bool GetParameter(const char* _name, unsigned short& _wx, unsigned short& _wy, float& _x, float& _y, float& _z)
		{
			T* foundParameter = (T*)_GetParameter(_name, T::GetRPCType());
			if (foundParameter == nullptr) { return false; }

			foundParameter->GetValues(_wx, _wy, _x, _y, _z);
			return true;
		}

		template <class T>
		bool GetParameter(const char* _name, float& _x, float& _y, float& _z, float& _w)
		{
			T* foundParameter = (T*)_GetParameter(_name, T::GetRPCType());
			if (foundParameter == nullptr) { return false; }

			foundParameter->GetValues(_x, _y, _z, _w);
			return true;
		}

		template <class T>
		bool GetParameter(const char* _name, float& _value)
		{
			T* foundParameter = (T*)_GetParameter(_name, T::GetRPCType());
			if (foundParameter == nullptr) { return false; }

			_value = foundParameter->GetValue();
			return true;
		}

	private:
		Parameter* _GetParameter(const char* _paramName, RPC_Type _type);


	private:
		std::vector<Parameter*>		m_parameters;
		RPC_Error					m_error;
	};
}