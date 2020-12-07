#include "include/Quat.h"

#include <iostream>
#include <array>

#pragma warning(push, 0)
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/Quat_generated.h>
#pragma warning(pop)

namespace WRPC
{
	Quat::Quat(Quat* _original) : Quat(_original->GetName(), Argument::CopiedResult)
	{
		for (int i = 0; i < 4; i++)
		{
			m_values[i] = _original->m_values[i];
		}
	}

	void Quat::GetValues(float& _x, float& _y, float& _z, float& _w)
	{
		_x = m_values[0];
		_y = m_values[1];
		_z = m_values[2];
		_w = m_values[3];
	}

	void  Quat::SetValues(float _x, float _y, float _z, float _w)
	{
		m_values[0] = _x;
		m_values[1] = _y;
		m_values[2] = _z;
		m_values[3] = _w;
	}

	Quat::Quat(const char* _name, Argument _inout) : Parameter(_name, _inout)
	{
		for (int i = 0; i < 4; i++)
		{
			m_values[i] = (i < 3) ? 0.0f : 1.0f;
		}
	}

	bool Quat::EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)
	{
		flatbuffers::FlatBufferBuilder fbb;

		WildRPC::QuatBuilder quatBuilder(fbb);
		quatBuilder.add_x(m_values[0]);
		quatBuilder.add_y(m_values[1]);
		quatBuilder.add_z(m_values[2]);
		quatBuilder.add_w(m_values[3]);
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

	bool Quat::DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)
	{
		unsigned char* bufferChunk = _buffer + *_offset;

		unsigned char* sz = reinterpret_cast<unsigned char*>(bufferChunk);
		int size = *sz;

		if ((int)(*_offset + size) >= _totalBufferSize)
		{
			return false;
		}

		auto quat = WildRPC::GetSizePrefixedQuat(bufferChunk);
		SetValues(quat->x(), quat->y(), quat->z(), quat->w());

		*_offset += size + 4;

		return true;
	}
}