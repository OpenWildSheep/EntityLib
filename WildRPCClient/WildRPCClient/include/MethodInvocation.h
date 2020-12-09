#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <vector>

#include "WildRPCType.h"
//#include "Result.h"
#include "Connection.h"
#include "Parameters.h"

#pragma warning(push, 0)
#pragma warning(disable : 4355)
#include "../external/asio/include/asio.hpp"
#pragma warning(pop)

namespace WRPC
{
	class WRPC_DLLEXPORT MethodInvocation	{

	public:
		MethodInvocation(const char* _managerName, const char* _methodName, ThreadSafety _threadSafety, std::vector<WildRPC::Type> _in, std::vector<WildRPC::Type> _out);
		void SetParametersValues(std::vector<Parameter> _values);

		Result Execute(Connection& _connection);


	private:
		const char*					m_managerName;
		const char*					m_methodName;

		std::vector<Parameter>			m_inBuffer;
		std::vector<Parameter>			m_outBuffer;

		ThreadSafety				m_threadSafety = ThreadSafety::Unsafe;
	};


}