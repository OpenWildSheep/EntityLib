#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <vector>

#include "WildRPCType.h"
#include "Parameter.h"
#include "Result.h"
#include "Connection.h"

#pragma warning(push, 0)
#pragma warning(disable : 4355)
#include "../external/asio/include/asio.hpp"
#pragma warning(pop)

namespace WRPC
{
	class WRPC_DLLEXPORT MethodInvocation	{

	public:
		MethodInvocation(const char* _managerName, const char* _methodName, ThreadSafety _threadSafety) : m_managerName(_managerName), m_methodName(_methodName), m_threadSafety(_threadSafety) {}

		template <class T>
		void AddParameter(const char* _name, Argument _inout, unsigned short _wx, unsigned short _wy, float _x, float _y, float _z)
		{
			T* parameter = new T(_name, _inout);
			parameter->SetValues(_wx, _wy, _x, _y, _z);
			_AddParameter(parameter);
		}

		template <class T>
		void AddParameter(const char* _name, Argument _inout, float _x, float _y, float _z)
		{
			T* parameter = new T(_name, _inout);
			parameter->SetValues(_x, _y, _z);
			_AddParameter(parameter);
		}

		template <class T>
		void AddParameter(const char* _name, Argument _inout, float _x, float _y, float _z, float _w)
		{
			T* parameter = new T(_name, _inout);
			parameter->SetValues(_x, _y, _z, _w);
			_AddParameter(parameter);
		}

		template <class T>
		void AddParameter(const char* _name, Argument _inout, float _value)
		{
			T* parameter = new T(_name, _inout);
			parameter->SetValue(_value);
			_AddParameter(parameter);
		}

		template <class T>
		void AddParameter(const char* _name, Argument _inout)
		{
			T* parameter = new T(_name, _inout);
			_AddParameter(parameter);
		}

		void Execute(Connection* _connection, Result& _result);

	private:
		void _AddParameter(Parameter* _param);

	private:
		const char*					m_managerName;
		const char*					m_methodName;

		std::vector<Parameter*>		m_parameters;
		std::vector<Parameter*>		m_results;

		ThreadSafety				m_threadSafety = ThreadSafety::Unsafe;
	};


}