#include "include/MethodInvocation.h"

#include "include/FloatParameter.h"
#include "include/Quat.h"
#include "include/Position.h"

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
	void MethodInvocation::_AddParameter(Parameter* _param)
	{
		switch (_param->GetArgument())
		{
		case Argument::In:
			m_parameters.push_back(_param);
			break;
		case Argument::Out:
			m_results.push_back(_param);
			break;
		case Argument::CopiedResult:
			assert(false);
			break;
		default:;
		}
	}

	void MethodInvocation::Execute(Connection* _connection, Result& _result)
	{

		if (_connection->GetStatus() != ConnectionStatus::Connected)
		{
			_result.m_error.m_protocolError = 0xFF;
			return;
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
			params.push_back((int8_t)prm->GetType());
		}
		auto prms = fbb.CreateVector(params);

		std::vector<int8_t> results;
		for (auto rslt : m_results)
		{
			results.push_back((int8_t)rslt->GetType());
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
			prm->EncodeIn(buffer, REQUEST_BUFFER_SIZE, &currentPosition);
		}

		// ------------------------------

		auto socket = (m_threadSafety == ThreadSafety::Unsafe) ? _connection->m_socket_NOT_ThreadSafe : _connection->m_socket_ThreadSafe;

		asio::write(*socket, asio::buffer(buffer, currentPosition + 1));

		unsigned char reply[REPLY_BUFFER_SIZE];
		size_t reply_length = asio::read(*socket, asio::buffer(reply, REPLY_BUFFER_SIZE));
		assert(REPLY_BUFFER_SIZE == reply_length);

		// ------------------------------

		_result.m_error.m_protocolError = reply[0];
		_result.m_error.m_applicativeError = reply[1];

		currentPosition = 2;
		for (auto rslt : m_results)
		{
			rslt->DecodeFrom(reply, REPLY_BUFFER_SIZE, &currentPosition);
		}

		// ------------------------------

		// Copy Result
		for (auto rslt : m_results)
		{
			_result.AddParameter(rslt);
		}
	}

}