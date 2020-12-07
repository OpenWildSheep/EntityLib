#include "include/MethodInvocation.h"

#include <iostream>
#include <array>

#pragma warning(push, 0)
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/RPCHeader_generated.h>
#pragma warning(pop)

#define REQUEST_BUFFER_SIZE (4 * 1024)
#define REPLY_BUFFER_SIZE (4 * 1024)

namespace WRPC
{
	void MethodInvocation::AddParameter(RPC_Type _type, const char* _name, unsigned short _wx, unsigned short _wy, float _x, float _y, float _z)
	{
		Parameter* param = _AddParameter(_type, _name, Argument::In);
		param->SetValues(_wx, _wy, _x, _y, _z);
	}

	void MethodInvocation::AddParameter(RPC_Type _type, const char* _name, float _x, float _y, float _z, float _w)
	{
		Parameter* param = _AddParameter(_type, _name, Argument::In);
		param->SetValues(_x, _y, _z, _w);
	}

	void MethodInvocation::AddParameter(RPC_Type _type, const char* _name, float _value)
	{
		Parameter* param = _AddParameter(_type, _name, Argument::In);
		param->SetValue(_value);
	}

	void MethodInvocation::AddResult(RPC_Type _type, const char* _name)
	{
		_AddParameter(_type, _name, Argument::Out);
	}

	Parameter* MethodInvocation::_AddParameter(RPC_Type _type, const char* _name, Argument _inout)
	{
		switch (_inout)
		{
		case Argument::In:
			m_parameters.emplace_back(_type, _name, _inout);
			return &m_parameters.back();

		case Argument::Out:
			m_results.emplace_back(_type, _name, _inout);
			return &m_results.back();

		default:;
		case Argument::CopiedResult:
			assert(false);
			return nullptr;
		}
		
	}

	Result MethodInvocation::Execute(Connection* _connection)
	{
		Result result;

		if (_connection->GetStatus() != ConnectionStatus::Connected)
		{
			result.m_error.m_protocolError = 0xFF;
			return result;
		}

		unsigned char buffer[REQUEST_BUFFER_SIZE];
		size_t currentPosition = 0;

		// --------------------------------------

		flatbuffers::FlatBufferBuilder fbb;

		auto managerName = fbb.CreateString(m_managerName);
		auto methodName = fbb.CreateString(m_methodName);

		std::vector<int8_t> params;
		for (auto prm : m_parameters)
		{
			params.push_back((int8_t)prm.GetType());
		}
		auto prms = fbb.CreateVector(params);

		std::vector<int8_t> results;
		for (auto rslt : m_results)
		{
			results.push_back((int8_t)rslt.GetType());
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
			prm.EncodeIn(buffer, REQUEST_BUFFER_SIZE, &currentPosition);
		}

		// ------------------------------

		auto socket = (m_threadSafety == ThreadSafety::Unsafe) ? _connection->m_socket_NOT_ThreadSafe : _connection->m_socket_ThreadSafe;

		asio::write(*socket, asio::buffer(buffer, currentPosition + 1));

		unsigned char reply[REPLY_BUFFER_SIZE];
		size_t reply_length = asio::read(*socket, asio::buffer(reply, REPLY_BUFFER_SIZE));
		assert(REPLY_BUFFER_SIZE == reply_length);

		// ------------------------------

		result.m_error.m_protocolError = reply[0];
		result.m_error.m_applicativeError = reply[1];

		currentPosition = 2;
		for (auto& rslt : m_results)
		{
			rslt.DecodeFrom(reply, REPLY_BUFFER_SIZE, &currentPosition);
		}

		// ------------------------------

		for (auto& rslt : m_results)
		{
			result.AddParameter(rslt);
		}

		return result;
	}

}