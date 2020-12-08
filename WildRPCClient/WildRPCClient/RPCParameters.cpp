#include "include/RPCParameters.h"

#pragma warning(push, 0)
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/Color_generated.h>
#include <WiLDRPC/Quat_generated.h>
#include <WiLDRPC/Position_generated.h>
#include <WiLDRPC/Vector3_generated.h>
#include <WiLDRPC/Vector2_generated.h>
#include <WiLDRPC/Uint3_generated.h>
#include <WiLDRPC/Float_generated.h>
#include <WiLDRPC/Integer_generated.h>
#include <WiLDRPC/Boolean_generated.h>
#include <WiLDRPC/String_generated.h>
#include <WiLDRPC/RPCHeader_generated.h>
#pragma warning(pop)

namespace WRPC
{

	// PARAMETER BUFFER -------------

	ParamsBuffer::ParamsBuffer()
	{
	}

	ParamsBuffer::~ParamsBuffer() {}

	void ParamsBuffer::PrintDebug()
	{
		bool first = true;
		for (auto& param : m_parameters)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				printf(", ");
			}
			param.Print();
		}
		printf("\n");
	}

	Param& ParamsBuffer::Add(INOUT _inout, WildRPC::Type _type)
	{
		m_parameters.emplace_back();
		Param& param = m_parameters.back();
		param.m_in = _inout;
		param.Init(_type);

		return param;
	}


	bool ParamsBuffer::EncodeIn(uint8_t* _buffer, size_t _bufferSize, size_t& _offset)
	{
		for (auto& param : m_parameters)
		{
			if (param.m_in == INOUT_Input)
			{
				bool ok = param.EncodeIn(_buffer, _bufferSize, _offset);
				if (! ok)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool ParamsBuffer::DecodeFrom(uint8_t* _buffer, size_t _bufferSize, size_t& _offset)
	{
		for (auto& param : m_parameters)
		{
			if (param.m_in == INOUT_Output)
			{
				bool ok = param.DecodeFrom(_buffer, _bufferSize, _offset);
				if (!ok)
				{
					return false;
				}
			}
		}
		return true;
	}

	struct GetData
	{
		template<typename T>
		void* operator()(T& value)
		{
			return &value;
		}
	};

	// PARAMETER ------------------------------------------------------------------------

	Param::Param(float _float)
	{
		Init(WildRPC::Type_Float);
		m_value = _float;
	}

	Param::Param(uint16_t _wx, uint16_t _wy, float _x, float _y, float _z)
	{
		Init(WildRPC::Type_Position);
		m_value = Containers::Position(_wx, _wy, _x, _y, _z);
	}

	Param::Param(float _x, float _y, float _z, float _w)
	{
		Init(WildRPC::Type_Quat);
		m_value = Containers::Quat(_x, _y, _z, _w);
	}

	// --------------------------------------

	bool Param::GetValue(float& _float)
	{
		if (GetType() != WildRPC::Type_Float)
		{
			return false;
		}
		_float = m_value.get<float>();
		return true;
	}

	bool Param::GetValue(uint16_t& _wx, uint16_t& _wy, float& _x, float& _y, float& _z)
	{
		if (GetType() != WildRPC::Type_Position)
		{
			return false;
		}

		Containers::Position& pos = m_value.get<Containers::Position>();
		_wx = (uint16_t)pos.wx;
		_wy = (uint16_t)pos.wy;
		_x = pos.x;
		_y = pos.y;
		_z = pos.z;
		return true;
	}

	bool Param::GetValue(float& _x, float& _y, float& _z, float& _w)
	{
		if (GetType() != WildRPC::Type_Quat)
		{
			return false;
		}

		Containers::Quat& pos = m_value.get<Containers::Quat>();
		_x = pos.x;
		_y = pos.y;
		_z = pos.z;
		_w = pos.w;
		return true;
	}

	void Param::Init(WildRPC::Type _type)
	{
		// Initialises the variant.
		switch (_type)
		{
		case WildRPC::Type_UInt3: { m_value = Containers::Vector3i(); } break;
		case WildRPC::Type_Vector3: { m_value = Containers::Vector3(); } break;
		case WildRPC::Type_Vector2: { m_value = Containers::Vector2(); } break;
		case WildRPC::Type_Quat: { m_value = Containers::Quat(); } break;
		case WildRPC::Type_Color: { m_value = Containers::Color(); } break;
		case WildRPC::Type_Position: { m_value =Containers::Position(); } break;
		case WildRPC::Type_Float: { m_value = 0.0f; } break;
		case WildRPC::Type_Integer: { m_value = 0; } break;
		case WildRPC::Type_Boolean: { m_value = false; } break;
		case WildRPC::Type_String: { m_value = std::string(""); } break;
		}
	}

	struct VisitPrint
	{
		void operator()(bool& _value) { printf(_value ? "true" : "false"); }
		void operator()(int& _value) { printf("(int) %d", _value); }
		void operator()(float& _value) { printf("(float) %.2f", _value); }
		void operator()(Containers::Vector2& _value) { printf("(Vector2) (%f, %f)", _value.x, _value.y); }
		void operator()(Containers::Vector3i& _value) { printf("(Vector3i) (%d, %d, %d)", _value.x, _value.y, _value.z); }
		void operator()(Containers::Vector3& _value) { printf("(Vector3) (%f, %f, %f)", _value.x, _value.y, _value.z); }
		void operator()(Containers::Quat& _value) { printf("(Quat) (%f, %f, %f, %f)", _value.x, _value.y, _value.z, _value.w); }
		void operator()(Containers::Color& _value) { printf("(Color) (%f, %f, %f, %f)", _value.r, _value.g, _value.b, _value.a); }
		void operator()(Containers::Position& _value) { printf("(Position) [%d, %d] (%f, %f, %f)", _value.wx, _value.wy, _value.x, _value.y, _value.z); }
		void operator()(std::string& _value) { printf("(string) <%s>", _value.c_str()); }
	};


	void Param::Print()
	{
		printf((m_in == INOUT_Input) ? "IN " : "OUT ");
		mapbox::util::apply_visitor(VisitPrint(), m_value);
	}

	// -----------------------

	struct VisitType
	{
		WildRPC::Type m_type = WildRPC::Type_Integer;

		void operator()(bool& ) { m_type = WildRPC::Type_Boolean; }
		void operator()(int& ) { m_type = WildRPC::Type_Integer; }
		void operator()(float& ) { m_type = WildRPC::Type_Float; }
		void operator()(Containers::Vector2& ) { m_type = WildRPC::Type_Vector2; }
		void operator()(Containers::Vector3i& ) { m_type = WildRPC::Type_UInt3; }
		void operator()(Containers::Vector3& ) { m_type = WildRPC::Type_Vector3; }
		void operator()(Containers::Quat& ) { m_type = WildRPC::Type_Quat; }
		void operator()(Containers::Color& ) { m_type = WildRPC::Type_Color; }
		void operator()(Containers::Position& ) { m_type = WildRPC::Type_Position; }
		void operator()(std::string& ) { m_type = WildRPC::Type_String; }
	};

	WildRPC::Type Param::GetType()
	{
		VisitType visitType;
		mapbox::util::apply_visitor(visitType, m_value);
		return visitType.m_type;
	}


	// -----------------------

	struct VisitEncode
	{
		flatbuffers::FlatBufferBuilder& m_builder;

		VisitEncode(flatbuffers::FlatBufferBuilder& _builder) : m_builder(_builder) {}

		void operator()(bool& _value) {
			auto result = WildRPC::CreateBoolean(m_builder, _value);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(int& _value) {
			auto result = WildRPC::CreateInteger(m_builder, _value);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(float& _value) {
			auto result = WildRPC::CreateFloat(m_builder, _value);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(Containers::Vector2& _value) {
			auto result = WildRPC::CreateVector2(m_builder, _value.x, _value.y);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(Containers::Vector3i& _value) {
			auto result = WildRPC::CreateUInt3(m_builder, _value.x, _value.y, _value.z);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(Containers::Vector3& _value) {
			auto result = WildRPC::CreateVector3(m_builder, _value.x, _value.y, _value.z);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(Containers::Quat& _value) {
			auto result = WildRPC::CreateQuat(m_builder, _value.x, _value.y, _value.z, _value.w);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(Containers::Color& _value) {
			auto result = WildRPC::CreateColor(m_builder, _value.r, _value.g, _value.b, _value.a);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(Containers::Position& _value) {
			auto localPos = WildRPC::CreateVector3(m_builder, _value.x, _value.y, _value.z);
			auto result = WildRPC::CreatePosition(m_builder, _value.wx, _value.wy, localPos);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(std::string& _value) {
			auto fbstring = m_builder.CreateString(_value);
			auto result = WildRPC::CreateString(m_builder, fbstring);
			m_builder.FinishSizePrefixed(result);
		}
	};

	bool Param::EncodeIn(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset)
	{
		flatbuffers::FlatBufferBuilder builder(1024);
		mapbox::util::apply_visitor(VisitEncode(builder), m_value);

		uint8_t *buf = builder.GetBufferPointer();
		size_t resultSize = builder.GetSize();

		size_t newOffset = _offset + resultSize;
		if (newOffset >= _bufferSize)
		{
			return false;
		}

		memcpy(_buffer + _offset, buf, resultSize);
		_offset += resultSize;

		return true;
	}

	// -----------------

	struct VisitDecode
	{
		uint8_t*	m_buffer;

		VisitDecode(uint8_t* _buffer) : m_buffer(_buffer) {}

		void operator()(bool& _value) {
			auto boolValue = WildRPC::GetSizePrefixedBoolean(m_buffer);
			_value = boolValue->value();
		}

		void operator()(int& _value) {
			auto intValue = WildRPC::GetSizePrefixedInteger(m_buffer);
			_value = intValue->value();
		}

		void operator()(float& _value) {
			auto floatValue = WildRPC::GetSizePrefixedFloat(m_buffer);
			_value = floatValue->value();
		}

		void operator()(Containers::Vector2& _value) {
			auto vector2Value = WildRPC::GetSizePrefixedVector2(m_buffer);
			_value = Containers::Vector2(vector2Value->x(), vector2Value->y());
		}

		void operator()(Containers::Vector3i& _value) {
			auto uint3Value = WildRPC::GetSizePrefixedUInt3(m_buffer);
			_value = Containers::Vector3i(uint3Value->x(), uint3Value->y(), uint3Value->z());
		}

		void operator()(Containers::Vector3& _value) {
			auto vector3Value = WildRPC::GetSizePrefixedVector3(m_buffer);
			_value = Containers::Vector3(vector3Value->x(), vector3Value->y(), vector3Value->z());
		}

		void operator()(Containers::Quat& _value) {
			auto quatValue = WildRPC::GetSizePrefixedQuat(m_buffer);
			_value = Containers::Quat(quatValue->x(), quatValue->y(), quatValue->z(), quatValue->w());
		}

		void operator()(Containers::Color& _value) {
			auto colorValue = WildRPC::GetSizePrefixedColor(m_buffer);
			_value = Containers::Color(colorValue->r(), colorValue->g(), colorValue->b(), colorValue->a());
		}

		void operator()(Containers::Position& _value) {
			auto positionValue = WildRPC::GetSizePrefixedPosition(m_buffer);
			uint32_t worldCellX = positionValue->worldCellX();
			uint32_t worldCellY = positionValue->worldCellY();
			auto local = positionValue->localPosition();
			_value = Containers::Position(worldCellX, worldCellY, local->x(), local->y(), local->z());
		}

		void operator()(std::string& _value) {
			const auto* stringValue = WildRPC::GetSizePrefixedString(m_buffer);
			_value =	(stringValue->value()->c_str());
		}
	};

	bool Param::DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset)
	{
		uint8_t* buffer = &_buffer[_offset];
		mapbox::util::apply_visitor(VisitDecode(buffer), m_value);

		auto sz = flatbuffers::GetPrefixedSize(buffer);
		size_t newOffset = _offset + (sz + sizeof(int));

		if (newOffset >= _bufferSize)
		{
			return false;
		}

		_offset = newOffset;
		return true;
	}

}