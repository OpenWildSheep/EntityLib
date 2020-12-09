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
	MethodInvocation::MethodInvocation(const char* _managerName, const char* _methodName, ThreadSafety _threadSafety, std::vector<WildRPC::Type> _in, std::vector<WildRPC::Type> _out) : m_managerName(_managerName), m_methodName(_methodName), m_threadSafety(_threadSafety)
	{
		for (auto type : _in)
		{
			m_inBuffer.emplace_back();
			m_inBuffer.back().Init(type);
		}
		for (auto type : _out)
		{
			m_outBuffer.emplace_back();
			m_outBuffer.back().Init(type);
		}
	}

	void MethodInvocation::SetParameters(std::vector<Parameter> _values)
	{
		if (_values.size() != m_inBuffer.size())
		{
			assert(false);
			return;
		}

		size_t index = 0;
		for (auto& prm : _values)
		{
			m_inBuffer[index] = prm;
			index++;
		}
	}


	// --------------------------------------------------------------

	Result MethodInvocation::Execute(Connection& _connection)
	{
		Result result;

		if (_connection.GetStatus() != ConnectionStatus::Connected)
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
		for (auto prm : m_inBuffer)
		{
			params.push_back((int8_t)prm.GetType());
		}
		auto prms = fbb.CreateVector(params);

		std::vector<int8_t> results;
		for (auto rslt : m_outBuffer)
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

		// Encode Parameters ------------------------

		for (auto& prm : m_inBuffer)
		{
			prm.EncodeIn(buffer, REQUEST_BUFFER_SIZE, currentPosition);
		}

		unsigned char reply[REPLY_BUFFER_SIZE];

		try
		{
			// Send Buffer ------------------------------

			auto socket = (m_threadSafety == ThreadSafety::Unsafe) ? _connection.m_socket_NOT_ThreadSafe : _connection.m_socket_ThreadSafe;

			asio::write(*socket, asio::buffer(buffer, currentPosition + 1));

			// Receive Reply Buffer -----------------------
			size_t reply_length = asio::read(*socket, asio::buffer(reply, REPLY_BUFFER_SIZE));
			assert(REPLY_BUFFER_SIZE == reply_length);
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
			_connection.m_status = ConnectionStatus::Errored;

			result.m_error.m_protocolError = 0xFF;
			return result;
		}

		// Decode Result ------------------------------

		result.m_error.m_protocolError = reply[0];
		result.m_error.m_applicativeError = reply[1];

		currentPosition = 2;
		for (auto& prm : m_outBuffer)
		{
			prm.DecodeFrom(reply, REPLY_BUFFER_SIZE, currentPosition);
		}

		// Copy Result ------------------------------

		result.m_paramsBuffer = m_outBuffer;

		return result;
	}

}