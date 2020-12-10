#include "include/Parameters.h"

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
	// GETTERS --------------------------------------

	bool Parameter::GetValue(bool& _bool) const
	{
		if (GetType() != WildRPC::Type_Boolean)
		{
			return false;
		}
		_bool = m_value.get<bool>();
		return true;
	}

	bool Parameter::GetValue(int& _int) const
	{
		if (GetType() != WildRPC::Type_Integer)
		{
			return false;
		}
		_int = m_value.get<int>();
		return true;
	}

	bool Parameter::GetValue(float& _float) const
	{
		if (GetType() != WildRPC::Type_Float)
		{
			return false;
		}
		_float = m_value.get<float>();
		return true;
	}

	bool Parameter::GetValue(float& _x, float& _y) const
	{
		if (GetType() != WildRPC::Type_Vector2)
		{
			return false;
		}

		const Vector2& pos = m_value.get<Vector2>();
		_x = pos.x;
		_y = pos.y;
		return true;
	}

	bool Parameter::GetValue(uint32_t& _x, uint32_t& _y, uint32_t& _z) const
	{
		if (GetType() != WildRPC::Type_UInt3)
		{
			return false;
		}

		const Vector3i& pos = m_value.get<Vector3i>();
		_x = pos.x;
		_y = pos.y;
		_z = pos.z;
		return true;
	}

	bool Parameter::GetValue(float& _x, float& _y, float& _z) const
	{
		if (GetType() != WildRPC::Type_Vector3)
		{
			return false;
		}

		const Vector3& pos = m_value.get<Vector3>();
		_x = pos.x;
		_y = pos.y;
		_z = pos.z;
		return true;
	}

	bool Parameter::GetValue(float& _x, float& _y, float& _z, float& _w) const
	{
		if (GetType() == WildRPC::Type_Quat)
		{
			const Quat& pos = m_value.get<Quat>();
			_x = pos.x;
			_y = pos.y;
			_z = pos.z;
			_w = pos.w;
		}

		if (GetType() == WildRPC::Type_Color)
		{
			const Color& pos = m_value.get<Color>();
			_x = pos.r;
			_y = pos.g;
			_z = pos.b;
			_w = pos.a;
		}

		return false;
	}

	bool Parameter::GetValue(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z) const
	{
		if (GetType() != WildRPC::Type_Position)
		{
			return false;
		}

		const Position& pos = m_value.get<Position>();
		_wx = (uint16_t)pos.wx;
		_wy = (uint16_t)pos.wy;
		_x = pos.x;
		_y = pos.y;
		_z = pos.z;
		return true;
	}

	bool Parameter::GetValue(std::string& _strg) const
	{
		if (GetType() != WildRPC::Type_String)
		{
			return false;
		}

		_strg = m_value.get<std::string>();
		return true;
	}

	// ---------------------------------------------------

	void Parameter::Init(WildRPC::Type _type)
	{
		// Initialises the variant.
		switch (_type)
		{
		case WildRPC::Type_UInt3: { m_value = Vector3i(); } break;
		case WildRPC::Type_Vector3: { m_value = Vector3(); } break;
		case WildRPC::Type_Vector2: { m_value = Vector2(); } break;
		case WildRPC::Type_Quat: { m_value = Quat(); } break;
		case WildRPC::Type_Color: { m_value = Color(); } break;
		case WildRPC::Type_Position: { m_value =Position(); } break;
		case WildRPC::Type_Float: { m_value = 0.0f; } break;
		case WildRPC::Type_Integer: { m_value = 0; } break;
		case WildRPC::Type_Boolean: { m_value = false; } break;
		case WildRPC::Type_String: { m_value = std::string(""); } break;
		}
	}

	// PRINTING FOR DEBUG -----------------------

	struct VisitPrint
	{
		void operator()(const bool& _value) { printf(_value ? "true" : "false"); }
		void operator()(const int& _value) { printf("(int) %d", _value); }
		void operator()(const float& _value) { printf("(float) %.2f", _value); }
		void operator()(const Vector2& _value) { printf("(Vector2) (%f, %f)", _value.x, _value.y); }
		void operator()(const Vector3i& _value) { printf("(Vector3i) (%d, %d, %d)", _value.x, _value.y, _value.z); }
		void operator()(const Vector3& _value) { printf("(Vector3) (%f, %f, %f)", _value.x, _value.y, _value.z); }
		void operator()(const Quat& _value) { printf("(Quat) (%f, %f, %f, %f)", _value.x, _value.y, _value.z, _value.w); }
		void operator()(const Color& _value) { printf("(Color) (%f, %f, %f, %f)", _value.r, _value.g, _value.b, _value.a); }
		void operator()(const Position& _value) { printf("(Position) [%d, %d] (%f, %f, %f)", _value.wx, _value.wy, _value.x, _value.y, _value.z); }
		void operator()(const std::string& _value) { printf("(string) <%s>", _value.c_str()); }
	};


	void Parameter::Print() const
	{
		mapbox::util::apply_visitor(VisitPrint(), m_value);
	}

	// RETRIEVING TYPE -----------------------

	struct VisitType
	{
		WildRPC::Type m_type = WildRPC::Type_Integer;

		void operator()(const bool& ) { m_type = WildRPC::Type_Boolean; }
		void operator()(const int& ) { m_type = WildRPC::Type_Integer; }
		void operator()(const float& ) { m_type = WildRPC::Type_Float; }
		void operator()(const Vector2& ) { m_type = WildRPC::Type_Vector2; }
		void operator()(const Vector3i& ) { m_type = WildRPC::Type_UInt3; }
		void operator()(const Vector3& ) { m_type = WildRPC::Type_Vector3; }
		void operator()(const Quat& ) { m_type = WildRPC::Type_Quat; }
		void operator()(const Color& ) { m_type = WildRPC::Type_Color; }
		void operator()(const Position& ) { m_type = WildRPC::Type_Position; }
		void operator()(const std::string& ) { m_type = WildRPC::Type_String; }
	};

	WildRPC::Type Parameter::GetType() const
	{
		VisitType visitType;
		mapbox::util::apply_visitor(visitType, m_value);
		return visitType.m_type;
	}


	// ENCODING -----------------------

	struct VisitEncode
	{
		flatbuffers::FlatBufferBuilder& m_builder;

		VisitEncode(flatbuffers::FlatBufferBuilder& _builder) : m_builder(_builder) {}

		void operator()(const bool& _value) {
			auto result = WildRPC::CreateBoolean(m_builder, _value);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const int& _value) {
			auto result = WildRPC::CreateInteger(m_builder, _value);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const float& _value) {
			auto result = WildRPC::CreateFloat(m_builder, _value);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const Vector2& _value) {
			auto result = WildRPC::CreateVector2(m_builder, _value.x, _value.y);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const Vector3i& _value) {
			auto result = WildRPC::CreateUInt3(m_builder, _value.x, _value.y, _value.z);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const Vector3& _value) {
			auto result = WildRPC::CreateVector3(m_builder, _value.x, _value.y, _value.z);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const Quat& _value) {
			auto result = WildRPC::CreateQuat(m_builder, _value.x, _value.y, _value.z, _value.w);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const Color& _value) {
			auto result = WildRPC::CreateColor(m_builder, _value.r, _value.g, _value.b, _value.a);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const Position& _value) {
			auto localPos = WildRPC::CreateVector3(m_builder, _value.x, _value.y, _value.z);
			auto result = WildRPC::CreatePosition(m_builder, _value.wx, _value.wy, localPos);
			m_builder.FinishSizePrefixed(result);
		}

		void operator()(const std::string& _value) {
			auto fbstring = m_builder.CreateString(_value);
			auto result = WildRPC::CreateString(m_builder, fbstring);
			m_builder.FinishSizePrefixed(result);
		}
	};

	bool Parameter::EncodeIn(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset) const
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

	// DECODING -----------------

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

		void operator()(Vector2& _value) {
			auto vector2Value = WildRPC::GetSizePrefixedVector2(m_buffer);
			_value = Vector2(vector2Value->x(), vector2Value->y());
		}

		void operator()(Vector3i& _value) {
			auto uint3Value = WildRPC::GetSizePrefixedUInt3(m_buffer);
			_value = Vector3i(uint3Value->x(), uint3Value->y(), uint3Value->z());
		}

		void operator()(Vector3& _value) {
			auto vector3Value = WildRPC::GetSizePrefixedVector3(m_buffer);
			_value = Vector3(vector3Value->x(), vector3Value->y(), vector3Value->z());
		}

		void operator()(Quat& _value) {
			auto quatValue = WildRPC::GetSizePrefixedQuat(m_buffer);
			_value = Quat(quatValue->x(), quatValue->y(), quatValue->z(), quatValue->w());
		}

		void operator()(Color& _value) {
			auto colorValue = WildRPC::GetSizePrefixedColor(m_buffer);
			_value = Color(colorValue->r(), colorValue->g(), colorValue->b(), colorValue->a());
		}

		void operator()(Position& _value) {
			auto positionValue = WildRPC::GetSizePrefixedPosition(m_buffer);
			uint32_t worldCellX = positionValue->worldCellX();
			uint32_t worldCellY = positionValue->worldCellY();
			auto local = positionValue->localPosition();
			_value = Position(worldCellX, worldCellY, local->x(), local->y(), local->z());
		}

		void operator()(std::string& _value) {
			const auto* stringValue = WildRPC::GetSizePrefixedString(m_buffer);
			_value =	(stringValue->value()->c_str());
		}
	};

	bool Parameter::DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset)
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


	// -------------------------

	bool Result::RetrieveValues(std::vector<ResultValue> _holders)
	{
		size_t idx = 0;
		for (auto& prm : m_paramsBuffer)
		{
			auto& hldr = _holders[idx];

			auto type = prm.GetType();
			switch (type)
			{
				case WildRPC::Type_Boolean:
				{
					auto bl = hldr.m_value.get<bool*>();
					prm.GetValue(*bl);
				}
					break;
				case WildRPC::Type_Integer:
				{
					auto it = hldr.m_value.get<int*>();
					prm.GetValue(*it);
				}
					break;
				case WildRPC::Type_Float:
				{
					auto flt = hldr.m_value.get<float*>();
					prm.GetValue(*flt);
				}
					break;
				case WildRPC::Type_Vector2:
				{
					auto& vct2 = hldr.m_value.get<Vector2H>();
					prm.GetValue(*vct2.x, *vct2.y);
				}
					break;
				case WildRPC::Type_UInt3:
				{
					auto& vct3i = hldr.m_value.get<Vector3iH>();
					prm.GetValue(*vct3i.x, *vct3i.y, *vct3i.z);
				}
					break;
				case WildRPC::Type_Vector3:
				{
					auto& vct3 = hldr.m_value.get<Vector3H>();
					prm.GetValue(*vct3.x, *vct3.y, *vct3.z);
				}
					break;
				case WildRPC::Type_Quat:
				{
					auto& qt = hldr.m_value.get<QuatH>();
					prm.GetValue(*qt.x, *qt.y, *qt.z, *qt.w);
				}
					break;
				case WildRPC::Type_Color:
				{
					auto& clr = hldr.m_value.get<ColorH>();
					prm.GetValue(*clr.r, *clr.g, *clr.b, *clr.a);
				}
					break;
				case WildRPC::Type_Position:
				{
					auto& ps = hldr.m_value.get<PositionH>();
					prm.GetValue(*ps.wx, *ps.wy, *ps.x, *ps.y, *ps.z);
				}
					break;
				case WildRPC::Type_String:
				{
					auto strg = hldr.m_value.get<std::string*>();
					prm.GetValue(*strg);
				}
				default:;
			}
			idx++;
		}
		return true;
	}
}