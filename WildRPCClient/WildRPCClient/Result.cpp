#include "include/Result.h"

#include <iostream>
#include <array>

namespace WRPC
{
	bool Result::_GetParameter(const char* _paramName, RPC_Type _type, Parameter** _param)
	{
		for (auto& rslt : m_parameters)
		{
			if (strcmp(rslt.GetName(), _paramName) != 0)
			{
				continue;
			}

			if (rslt.GetType() != _type)
			{
				continue;
			}

			*_param = &rslt;

			return true;
		}

		return false;
	}

	void Result::AddParameter(const Parameter& _param)
	{
		m_parameters.push_back(_param);
	}

	bool Result::HasError()
	{
		return (m_error.m_protocolError != 0) || (m_error.m_applicativeError != 0);
	}

}