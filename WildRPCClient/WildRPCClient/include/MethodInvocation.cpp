#include "MethodInvocation.h"

#include "FloatParameter.h"
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
	void MethodInvocation::AddResult(RPC_Type _param, const char* _name)
	{
		switch (_param)
		{
		case RPC_Type::Boolean:
			return;

		case RPC_Type::Integer:
			return;

		case RPC_Type::Float:
		{
			Float* flt = new Float();
			flt->SetName(_name);
			m_results.push_back(flt);
		}
			return;

		case RPC_Type::Vector2:
			return;

		case RPC_Type::UInt3:
			return;

		case RPC_Type::Vector3:
			return;

		case RPC_Type::Quat:
		{
			Quat* quat = new Quat();
			quat->SetName(_name);
			m_results.push_back(quat);
		}
			return;

		case RPC_Type::Color:
			return;

		case RPC_Type::Position:
		{
			Position* pos = new Position();
			pos->SetName(_name);
			m_results.push_back(pos);
			return;
		}
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
			prm->EncodeIn(buffer, requestBufferSize, &currentPosition);
		}

		// ------------------------------

		asio::write(_socket, asio::buffer(buffer, currentPosition + 1));

		unsigned char reply[replyBufferSize];
		size_t reply_length = asio::read(_socket, asio::buffer(reply, replyBufferSize));
		assert(replyBufferSize == reply_length);

		// ------------------------------

		RPC_Error error;
		error.m_protocolError = reply[0];
		error.m_applicativeError = reply[1];

		currentPosition = 2;
		for (auto rslt : m_results)
		{
			rslt->DecodeFrom(reply, replyBufferSize, &currentPosition);
		}

		// ------------------------------

		return error;
	}

	// --------------------------------------------------

	void MethodInvocation::AddPositionParameter(unsigned short _worldCellX, unsigned short _worldCellY, float _x, float _y, float _z)
	{
		Position* pos = new Position();
		pos->SetValues(_worldCellX, _worldCellY, _x, _y, _z);
		m_parameters.push_back(pos);
	}

	void MethodInvocation::AddQuatParameter(float _x, float _y, float _z, float _w)
	{
		Quat* quat = new Quat();
		quat->SetValues(_x, _y, _z, _w);
		m_parameters.push_back(quat);
	}

	void MethodInvocation::AddFloatParameter(float _value)
	{
		Float* flt = new Float();
		flt->SetValue(_value);
		m_parameters.push_back(flt);
	}

	// --------------------------------------------------

	Parameter* MethodInvocation::_GetResult(const char* _paramName, RPC_Type _type)
	{
		for (auto rslt : m_results)
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

		return nullptr;
	}

	bool MethodInvocation::GetFloatResult(const char* _paramName, float& _result)
	{
		Parameter* prm = _GetResult(_paramName, RPC_Type::Float);
		Float* flt = dynamic_cast<Float*>(prm);
		
		if (flt == nullptr)
		{
			return false;
		}

		_result = flt->GetValue();
		return true;
	}

	bool MethodInvocation::GetPositionResult(const char* _paramName, unsigned short& _worldCellX, unsigned short& _worldCellY, float& _x, float& _y, float& _z)
	{
		Parameter* prm = _GetResult(_paramName, RPC_Type::Position);
		Position* pos = dynamic_cast<Position*>(prm);

		if (pos == nullptr)
		{
			return false;
		}

		pos->GetValues(_worldCellX, _worldCellY, _x, _y, _z);
		return true;
	}

	bool MethodInvocation::GetQuatResult(const char* _paramName, float& _x, float& _y, float& _z, float& _w)
	{
		Parameter* prm = _GetResult(_paramName, RPC_Type::Quat);
		Quat* quat = dynamic_cast<Quat*>(prm);

		if (quat == nullptr)
		{
			return false;
		}

		quat->GetValues(_x, _y, _z, _w);
		return true;
	}

}