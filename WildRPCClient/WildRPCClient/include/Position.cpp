#include "Position.h"

#include <iostream>
#include <array>

#pragma warning(push, 0)
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/Position_generated.h>
#include <WiLDRPC/Vector3_generated.h>
#pragma warning(pop)

namespace WRPC
{
	void Position::GetValues(unsigned short* _worldCellX, unsigned short* _worldCellY, float* _x, float* _y, float* _z)
	{
		*_worldCellX = m_worldCellsCoords[0];
		*_worldCellY = m_worldCellsCoords[1];
		*_x = m_localCoordinates[0];
		*_y = m_localCoordinates[1];
		*_z = m_localCoordinates[2];
	}

	void Position::SetValues(unsigned short _worldCellX, unsigned short _worldCellY, float _x, float _y, float _z)
	{
		m_worldCellsCoords[0] = _worldCellX;
		m_worldCellsCoords[1] = _worldCellY;
		m_localCoordinates[0] = _x;
		m_localCoordinates[1] = _y;
		m_localCoordinates[2] = _z;
	}

	Position::Position(const char* _name) : m_name(_name)
	{
		for (int i = 0; i < 2; i++)
		{
			m_worldCellsCoords[i] = 32768;
		}

		for (int i = 0; i < 3; i++)
		{
			m_localCoordinates[i] = 0.0f;
		}
	}

	bool Position::EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)
	{
		flatbuffers::FlatBufferBuilder fbb;

		WildRPC::Vector3Builder vec3Builder(fbb);
		vec3Builder.add_x(1.0f);
		vec3Builder.add_y(2.0f);
		vec3Builder.add_z(3.0f);
		auto localPos = vec3Builder.Finish();

		WildRPC::PositionBuilder posBuilder(fbb);
		posBuilder.add_worldCellX(32768);
		posBuilder.add_worldCellY(32768);
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

	bool Position::DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)
	{
		unsigned char* sz = reinterpret_cast<unsigned char*>(_buffer);
		int size = *sz;

		if ((int)(*_offset + size) >= _totalBufferSize)
		{
			return false;
		}
		
		auto pos = WildRPC::GetSizePrefixedPosition(_buffer);

		if (pos == nullptr)
		{
			return false;
		}

		SetValues((unsigned short)pos->worldCellX(), (unsigned short)pos->worldCellY(), pos->localPosition()->x(), pos->localPosition()->y(), pos->localPosition()->z());

		*_offset  += size + 4;
		return true;
	}
}