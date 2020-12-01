#include "Float.h"

#include <iostream>
#include <array>

#pragma warning(push, 0)
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/Float_generated.h>
#pragma warning(pop)

namespace WRPC
{
	Float::Float(const char* _name) : m_name(_name)
	{

	}

	bool Float::EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)
	{
		flatbuffers::FlatBufferBuilder fbb;

		WildRPC::FloatBuilder floatBuilder(fbb);
		floatBuilder.add_value(m_value);
		auto foV = floatBuilder.Finish();

		fbb.FinishSizePrefixed(foV);

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

	bool Float::DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)
	{
		unsigned char* sz = reinterpret_cast<unsigned char*>(_buffer);
		int size = *sz;
		
		if ((int)(*_offset + size) >= _totalBufferSize)
		{
			return false;
		}

		auto flt = WildRPC::GetSizePrefixedFloat(_buffer);

		if (flt == nullptr)
		{
			return false;
		}

		m_value = flt->value();
		*_offset  += size + 4;
		return true;
	}
}