#include "include/Result.h"

#include <iostream>
#include <array>

#include "include/Position.h"
#include "include/Quat.h"
#include "include/FloatParameter.h"

namespace WRPC
{

	Result::~Result()
	{
		for (auto it = m_parameters.begin(); it != m_parameters.end();)
		{
			auto prm = *it;
			delete prm;
			it = m_parameters.erase(it);
		}
	}

	Parameter* Result::_GetParameter(const char* _paramName, RPC_Type _type)
	{
		for (auto& rslt : m_parameters)
		{
			if (strcmp(rslt->GetName(), _paramName) != 0)
			{
				continue;
			}

			if (rslt->GetType() != _type)
			{
				continue;
			}

			return rslt;
		}

		return false;
	}

	Parameter* _Copy(Parameter* _param)
	{
		switch (_param->GetType())
		{
		case RPC_Type::Position:
		{
			return new Position((Position*)_param);
		}
		break;

		case RPC_Type::Quat:
		{
			return new Quat((Quat*)_param);
		}
		break;

		case RPC_Type::Float:
		{
			return new Float((Float*)_param);
		}
		break;

		case RPC_Type::Boolean:
		case RPC_Type::Vector3:
		case RPC_Type::Vector2:
		case RPC_Type::UInt3:
		case RPC_Type::Color:
		case RPC_Type::Integer:
		case RPC_Type::None:
		default:
			return nullptr;
		}

	}

	void Result::AddParameter(Parameter* _param)
	{
		m_parameters.push_back(_Copy(_param));
	}

	bool Result::HasError()
	{
		return (m_error.m_protocolError != 0) || (m_error.m_applicativeError != 0);
	}

}