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
		
		void		AddResult(RPC_Type _param, const char* _name);

		RPC_Error	Execute(asio::ip::tcp::socket& _socket);

		void		AddPositionParameter(unsigned short _worldCellX, unsigned short _worldCellY, float _x, float _y, float _z);
		void		AddQuatParameter(float _x, float _y, float _z, float _w);
		void		AddFloatParameter(float _value);

		bool		GetFloatResult		(const char* _paramName, float& _result);
		bool		GetPositionResult   (const char* _paramName, unsigned short& _worldCellX, unsigned short& _worldCellY, float& _x, float& _y, float& _z);
		bool		GetQuatResult		(const char* _paramName, float& _x, float& _y, float& _z, float& _w);


	private:
		Parameter* _GetResult(const char* _paramName, RPC_Type _type);

	private:
		const char*	m_managerName;
		const char* m_methodName;

		std::vector<Parameter*>					m_parameters;
		std::vector<Parameter*>					m_results;

	};


}