#include "include/MethodInvocation.h"

#include <iostream>
#include <array>

#pragma warning(push, 0)
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/RPCHeader_generated.h>
#pragma warning(pop)

#include "ConnectionPimpl.h"

#define REQUEST_BUFFER_SIZE (4 * 1024)
#define REPLY_BUFFER_SIZE (4 * 1024)

namespace WRPC
{
	MethodInvocation::MethodInvocation(const char* _managerName, const char* _methodName, ThreadSafety _threadSafety, std::vector<WildRPC::Type> _in, std::vector<WildRPC::Type> _out) : m_managerName(_managerName), m_methodName(_methodName), m_threadSafety(_threadSafety)
	{
		for (auto type : _in)
		{
			m_inParams.emplace_back();
			m_inParams.back().Init(type);
		}
		for (auto type : _out)
		{
			m_outParams.emplace_back();
			m_outParams.back().Init(type);
		}
	}

	bool MethodInvocation::_SetParameters(const std::vector<Parameter>& _values)
	{
		if (_values.size() != m_inParams.size())
		{
			assert(false);
			return false;
		}

		size_t index = 0;
		for (auto& prm : _values)
		{
			if (m_inParams[index].GetType() != prm.GetType())
			{
				assert(false);
				return false;
			}

			m_inParams[index] = prm;
			index++;
		}

		return true;
	}


	// --------------------------------------------------------------

	Result MethodInvocation::Execute(Connection& _connection, const std::vector<Parameter>& _values)
	{
		Result result;

		bool paramsOk = _SetParameters(_values);
		if (!paramsOk)
		{
			result.m_error.m_protocolError = RPCProtocolError::TypesMismatch;
			return result;
		}

		if (_connection.GetStatus() != ConnectionStatus::Connected)
		{
			result.m_error.m_protocolError = RPCProtocolError::NoConnectionToHost;
			return result;
		}

		unsigned char buffer[REQUEST_BUFFER_SIZE];
		size_t currentPosition = 0;

		// --------------------------------------

		flatbuffers::FlatBufferBuilder fbbuilder;

		auto managerName = fbbuilder.CreateString(m_managerName);
		auto methodName = fbbuilder.CreateString(m_methodName);

		std::vector<int8_t> params;
		for (auto prm : m_inParams)
		{
			params.push_back((int8_t)prm.GetType());
		}
		auto prms = fbbuilder.CreateVector(params);

		std::vector<int8_t> results;
		for (auto rslt : m_outParams)
		{
			results.push_back((int8_t)rslt.GetType());
		}
		auto rslts = fbbuilder.CreateVector(results);

		WildRPC::RPCHeaderBuilder rpcHeader(fbbuilder);
		rpcHeader.add_managerName(managerName);
		rpcHeader.add_methodName(methodName);
		rpcHeader.add_parameterTypes(prms);
		rpcHeader.add_resultTypes(rslts);

		auto header = rpcHeader.Finish();
		fbbuilder.FinishSizePrefixed(header);

		auto size = fbbuilder.GetSize();
		auto bufferPointer = fbbuilder.GetBufferPointer();
		memcpy(buffer + currentPosition, bufferPointer, size);
		currentPosition += size;

		if (currentPosition >= REQUEST_BUFFER_SIZE)
		{
			result.m_error.m_protocolError = RPCProtocolError::Exceeded_BufferSize;
			return result;
		}

		// Encode Parameters ------------------------

		for (auto& param : m_inParams)
		{
			bool ok = param.EncodeIn(buffer, REQUEST_BUFFER_SIZE, currentPosition);
			if (!ok)
			{
				result.m_error.m_protocolError = RPCProtocolError::Exceeded_BufferSize;
				return result;
			}
		}

		unsigned char reply[REPLY_BUFFER_SIZE];
		try
		{
			// Send Buffer ------------------------------

			auto socket =
				(m_threadSafety == ThreadSafety::Unsafe) ?
				_connection.m_pimpl->m_socket_NOT_ThreadSafe :
				_connection.m_pimpl->m_socket_ThreadSafe;

			asio::write(*socket, asio::buffer(buffer, currentPosition + 1));

			// Receive Reply Buffer -----------------------
			size_t reply_length = asio::read(*socket, asio::buffer(reply, REPLY_BUFFER_SIZE));

			if (reply_length != REPLY_BUFFER_SIZE)
			{
				result.m_error.m_protocolError = RPCProtocolError::WrongReplyBufferSize;
				return result;
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
			_connection.m_pimpl->m_status = ConnectionStatus::Errored;

			result.m_error.m_protocolError = RPCProtocolError::NoConnectionToHost;
			return result;
		}

		// Decode Result ------------------------------

		result.m_error.m_protocolError = (RPCProtocolError)reply[0];
		result.m_error.m_applicativeError = reply[1];

		if ((result.m_error.m_protocolError != RPCProtocolError::No_Error) || (result.m_error.m_applicativeError != 0))
		{
			return result;
		}

		currentPosition = 2;
		for (auto& param : m_outParams)
		{
			bool ok = param.DecodeFrom(reply, REPLY_BUFFER_SIZE, currentPosition);
			if (!ok)
			{
				result.m_error.m_protocolError = RPCProtocolError::Exceeded_ReplyBufferSize;
				return result;
			}
		}

		// Copy Result ------------------------------

		result.m_paramsBuffer = m_outParams;

		return result;
	}

}
