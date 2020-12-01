#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <vector>

#include "WildRPCType.h"
#include "Parameter.h"

#pragma warning(push, 0)
#pragma warning(disable : 4355)
#include "../external/asio/include/asio.hpp"
#pragma warning(pop)

namespace WRPC
{
	class WRPC_DLLEXPORT MethodInvocation	{

	public:
		MethodInvocation(const char* _managerName, const char* _methodName) : m_managerName(_managerName), m_methodName(_methodName) {}
		
		void		AddParameter(RPC_Type _param, const char* _name);
		void		AddResult(RPC_Type _param, const char* _name);

		RPC_Error	Execute(asio::ip::tcp::socket& _socket);

		float		GetFloatResult (const char* _paramName);
		int			GetIntResult   (const char* _paramName);
		bool		GetBoolResult  (const char* _paramName);


	private:
		void _AddParamInOut(bool _isIN, RPC_Type _param, const char* _name);

	private:
		const char*	m_managerName;
		const char* m_methodName;

		std::vector<Parameter*> m_parameters;
		std::vector<Parameter*> m_results;


	};


}