#include "MethodInvocation.h"

#include "Float.h"
#include "Quat.h"
#include "Position.h"

#include <iostream>
#include <array>

#pragma warning(push, 0)
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/RPCHeader_generated.h>
#pragma warning(pop)

namespace WRPC
{
	void MethodInvocation::AddParameter(RPC_Type _param, const char* _name)
	{
		_AddParamInOut(true, _param, _name);
	}

	void MethodInvocation::AddResult(RPC_Type _param, const char* _name)
	{
		_AddParamInOut(false, _param, _name);
	}

	void MethodInvocation::_AddParamInOut(bool _isIN, RPC_Type _param, const char* _name)
	{
		auto& prms = _isIN ? m_parameters : m_results;

		switch (_param)
		{
		case RPC_Type::Boolean:
			return;

		case RPC_Type::Integer:
			return;

		case RPC_Type::Float:
			prms.push_back(new Float(_name));
			return;

		case RPC_Type::Vector2:
			return;

		case RPC_Type::UInt3:
			return;

		case RPC_Type::Vector3:
			return;

		case RPC_Type::Quat:
			prms.push_back(new Quat(_name));
			return;

		case RPC_Type::Color:
			return;

		case RPC_Type::Position:
			prms.push_back(new Position(_name));
			return;
		}
	}

	RPC_Error MethodInvocation::Execute(asio::ip::tcp::socket& _socket)
	{
		const int requestBufferSize = 4 * 1024;
		const int replyBufferSize = 4 * 1024;

		unsigned char buffer[requestBufferSize];
		size_t currentPosition = 0;

		// --------------------------------------

		flatbuffers::FlatBufferBuilder fbb;

		auto managerName = fbb.CreateString(m_managerName);
		auto methodName = fbb.CreateString(m_methodName);

		std::vector<int8_t> params;
		for (auto prm : m_parameters)
		{
			params.push_back(prm->GetType());
		}
		auto prms = fbb.CreateVector(params);

		std::vector<int8_t> results;
		for (auto rslt : m_results)
		{
			results.push_back(rslt->GetType());
		}
		auto rslts = fbb.CreateVector(results);

		WildRPC::RPCHeaderBuilder rpcHeader(fbb);
		rpcHeader.add_managerName(managerName);
		rpcHeader.add_methodName(methodName);
		rpcHeader.add_parameterTypes(prms);
		rpcHeader.add_resultTypes(rslts);

		auto hdr = rpcHeader.Finish();
		fbb.FinishSizePrefixed(hdr);

		auto size = fbb.GetSize();
		auto ptr = fbb.GetBufferPointer();
		memcpy(buffer + currentPosition, ptr, size);
		currentPosition += size;

		// ----------------------------

		for (auto prm : m_parameters)
		{
			prm->EncodeIn(buffer, requestBufferSize, &currentPosition);
		}

		// ------------------------------

		asio::write(_socket, asio::buffer(buffer, currentPosition + 1));

		char reply[replyBufferSize];
		size_t reply_length = asio::read(_socket, asio::buffer(reply, replyBufferSize));
		assert(replyBufferSize == reply_length);

		// ------------------------------

		for (auto rslt : m_results)
		{
			rslt->DecodeFrom(buffer, requestBufferSize, &currentPosition);
		}

		// ------------------------------

		return RPC_Error();
	}

	float MethodInvocation::GetFloatResult(const char* _paramName)
	{
		printf("GetFloatResult(%s)\n", _paramName);
		return 0.0f;
	}

	int MethodInvocation::GetIntResult(const char* _paramName)
	{
		printf("GetIntResult(%s)\n", _paramName);
		return 0;
	}

	bool MethodInvocation::GetBoolResult(const char* _paramName)
	{
		printf("GetBoolResult(%s)\n", _paramName);
		return false;
	}
}