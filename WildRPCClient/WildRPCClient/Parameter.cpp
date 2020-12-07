#pragma once

#include <cstdio>
#include <exception>
#include <string>

#include "include/WildRPCType.h"
#include "include/Parameter.h"

#pragma warning(push, 0)
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/Position_generated.h>
#include <WiLDRPC/Vector3_generated.h>
#include <WiLDRPC/Quat_generated.h>
#include <WiLDRPC/Float_generated.h>
#pragma warning(pop)

namespace WRPC
{
	bool Parameter::EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)
	{
		switch (m_type)
		{
		case RPC_Type::Position:
		{
			flatbuffers::FlatBufferBuilder fbb;

			WildRPC::Vector3Builder vec3Builder(fbb);
			vec3Builder.add_x(m_values.m_position.m_localCoords[0]);
			vec3Builder.add_y(m_values.m_position.m_localCoords[1]);
			vec3Builder.add_z(m_values.m_position.m_localCoords[2]);
			auto localPos = vec3Builder.Finish();

			WildRPC::PositionBuilder posBuilder(fbb);
			posBuilder.add_worldCellX(m_values.m_position.m_worldCellsCoords[0]);
			posBuilder.add_worldCellY(m_values.m_position.m_worldCellsCoords[1]);
			posBuilder.add_localPosition(localPos);
			auto pos = posBuilder.Finish();

			fbb.FinishSizePrefixed(pos);

			auto size = fbb.GetSize();
			auto ptr = fbb.GetBufferPointer();

			if ((int)(*_offset + size) >= _totalBufferSize)
			{
				return false;
			}

			memcpy(_buffer + *_offset, ptr, size);
			*_offset += (int)size;

			return true;
		}
		break;

		case RPC_Type::Quat:
		{
			flatbuffers::FlatBufferBuilder fbb;

			WildRPC::QuatBuilder quatBuilder(fbb);
			quatBuilder.add_x(m_values.m_floats[0]);
			quatBuilder.add_y(m_values.m_floats[1]);
			quatBuilder.add_z(m_values.m_floats[2]);
			quatBuilder.add_w(m_values.m_floats[3]);
			auto ornt = quatBuilder.Finish();

			fbb.FinishSizePrefixed(ornt);

			auto size = fbb.GetSize();

			if ((int)(*_offset + size) >= _totalBufferSize)
			{
				return false;
			}

			auto ptr = fbb.GetBufferPointer();
			memcpy(_buffer + *_offset, ptr, size);
			*_offset += size;

			return true;
		}
		break;

		case RPC_Type::Float:
		{
			flatbuffers::FlatBufferBuilder fbb;

			WildRPC::FloatBuilder floatBuilder(fbb);
			floatBuilder.add_value(m_values.m_floats[0]);
			auto flt = floatBuilder.Finish();

			fbb.FinishSizePrefixed(flt);

			auto size = fbb.GetSize();
			auto ptr = fbb.GetBufferPointer();

			if ((int)(*_offset + size) >= _totalBufferSize)
			{
				return false;
			}

			memcpy(_buffer + *_offset, ptr, size);
			*_offset += (int)size;

			return true;
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
			return false;
		}
	}

	bool Parameter::DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)
	{
		switch (m_type)
		{
		case RPC_Type::Position:
		{
			unsigned char* bufferChunk = _buffer + *_offset;

			unsigned char* sz = reinterpret_cast<unsigned char*>(bufferChunk);
			int size = *sz;

			if ((int)(*_offset + size) >= _totalBufferSize)
			{
				return false;
			}

			auto pos = WildRPC::GetSizePrefixedPosition(bufferChunk);

			if (pos == nullptr)
			{
				return false;
			}

			m_values.m_position.m_worldCellsCoords[0] = (uint16_t)pos->worldCellX();
			m_values.m_position.m_worldCellsCoords[1] = (uint16_t)pos->worldCellY();
			m_values.m_position.m_localCoords[0] = pos->localPosition()->x();
			m_values.m_position.m_localCoords[1] = pos->localPosition()->y();
			m_values.m_position.m_localCoords[2] = pos->localPosition()->z();

			*_offset += size + 4;
			return true;
		}
		break;

		case RPC_Type::Quat:
		{
			unsigned char* bufferChunk = _buffer + *_offset;

			unsigned char* sz = reinterpret_cast<unsigned char*>(bufferChunk);
			int size = *sz;

			if ((int)(*_offset + size) >= _totalBufferSize)
			{
				return false;
			}

			auto quat = WildRPC::GetSizePrefixedQuat(bufferChunk);
			m_values.m_floats[0] = quat->x();
			m_values.m_floats[1] = quat->y();
			m_values.m_floats[2] = quat->z();
			m_values.m_floats[3] = quat->w();

			*_offset += size + 4;

			return true;
		}
		break;

		case RPC_Type::Float:
		{
			unsigned char* bufferChunk = _buffer + *_offset;

			unsigned char* sz = reinterpret_cast<unsigned char*>(bufferChunk);
			int size = *sz;

			if ((int)(*_offset + size) >= _totalBufferSize)
			{
				return false;
			}

			auto flt = WildRPC::GetSizePrefixedFloat(bufferChunk);

			if (flt == nullptr)
			{
				return false;
			}

			m_values.m_floats[0] = flt->value();
			*_offset += size + 4;
			return true;
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

	 // ---------------

	void Parameter::SetValues(float _x, float _y, float _z, float _w)
	{
		assert(m_type == RPC_Type::Quat);
		m_values.m_floats[0] = _x;
		m_values.m_floats[1] = _y;
		m_values.m_floats[2] = _z;
		m_values.m_floats[3] = _w;
	}

	void Parameter::SetValues(uint16_t _wx, uint16_t _wy, float _x, float _y, float _z)
	{
		assert(m_type == RPC_Type::Position);
		m_values.m_position.m_worldCellsCoords[0] = _wx;
		m_values.m_position.m_worldCellsCoords[1] = _wy;
		m_values.m_position.m_localCoords[0] = _x;
		m_values.m_position.m_localCoords[1] = _y;
		m_values.m_position.m_localCoords[2] = _z;
	}

	void Parameter::SetValue(float _values)
	{
		assert(m_type == RPC_Type::Float);
		m_values.m_floats[0] = _values;
	}

	// -------------------

	void Parameter::GetValues(float& _x, float& _y, float& _z, float& _w)
	{
		assert(m_type == RPC_Type::Quat);
		_x = m_values.m_floats[0];
		_y = m_values.m_floats[1];
		_z = m_values.m_floats[2];
		_w = m_values.m_floats[3];
	}

	void Parameter::GetValues(uint16_t& _wx, uint16_t& _wy, float& _x, float& _y, float& _z)
	{
		assert(m_type == RPC_Type::Position);
		_wx = m_values.m_position.m_worldCellsCoords[0];
		_wy = m_values.m_position.m_worldCellsCoords[1];
		_x =  m_values.m_position.m_localCoords[0];
		_y =  m_values.m_position.m_localCoords[1];
		_z =  m_values.m_position.m_localCoords[2];
	}

	void Parameter::GetValue(float& _value)
	{
		assert(m_type == RPC_Type::Float);
		_value = m_values.m_floats[0];
	}
}
