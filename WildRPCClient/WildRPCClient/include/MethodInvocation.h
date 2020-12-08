#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <vector>

#include "WildRPCType.h"
//#include "Result.h"
#include "Connection.h"
#include "RPCParameters.h"

#pragma warning(push, 0)
#pragma warning(disable : 4355)
#include "../external/asio/include/asio.hpp"
#pragma warning(pop)

namespace WRPC
{
	class WRPC_DLLEXPORT MethodInvocation	{

	public:
		MethodInvocation(const char* _managerName, const char* _methodName, ThreadSafety _threadSafety) : m_managerName(_managerName), m_methodName(_methodName), m_threadSafety(_threadSafety) {}

		void SetSignature(std::vector<WildRPC::Type> _in, std::vector<WildRPC::Type> _out);
		void SetParametersValues(std::vector<Param> _values);

		//void AddParameter(RPC_Type _type, const char* _name, unsigned short _wx, unsigned short _wy, float _x, float _y, float _z);
		//void AddParameter(RPC_Type _type, const char* _name, float _x, float _y, float _z, float _w);
		//void AddParameter(RPC_Type _type, const char* _name, float _value);
		//void AddResult   (RPC_Type _type, const char* _name);
		//
		//void ChangeParameterValue(RPC_Type _type, const char* _name, unsigned short _wx, unsigned short _wy, float _x, float _y, float _z);
		//void ChangeParameterValue(RPC_Type _type, const char* _name, float _x, float _y, float _z, float _w);
		//void ChangeParameterValue(RPC_Type _type, const char* _name, float _value);

		Result Execute(Connection& _connection);

	private:
		//Parameter* _AddParameter(RPC_Type _type, const char* _name, Argument _inout);
		//Parameter* _GetParameter(RPC_Type _type, const char* _name, Argument _inout);

	private:
		const char*					m_managerName;
		const char*					m_methodName;

		ParamsBuffer				m_inBuffer;
		ParamsBuffer				m_outBuffer;

		//std::vector<Parameter>		m_parameters;
		//std::vector<Parameter>		m_results;

		ThreadSafety				m_threadSafety = ThreadSafety::Unsafe;
	};


}