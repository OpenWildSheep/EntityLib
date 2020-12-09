#pragma once

#include <vector>

#pragma warning(push, 0)
#include "../../../external/mapbox/variant.hpp"
#pragma warning(pop)

#include "WildRPCType.h"

namespace WildRPC
{
	enum Type : int;
}

namespace WRPC
{
	typedef Parameter P;

	struct Vector2
	{
		float x, y;
		Vector2() {}
		Vector2(float _x, float _y) : x(_x), y(_y) {}
	};

	struct Vector3
	{
		float x, y, z;
		Vector3(){}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	};

	struct Quat
	{
		float x, y, z, w;
		Quat(){}
		Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	};

	struct Color
	{
		float r, g, b, a;
		Color(){}
		Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
	};

	struct Vector3i
	{
		uint32_t x, y, z;
		Vector3i(){}
		Vector3i(uint32_t _x, uint32_t _y, uint32_t _z) : x(_x), y(_y), z(_z) {}
	};

	struct Position
	{
		uint32_t wx, wy;
		float x, y, z;
		Position() {}
		Position(uint32_t _wx, uint32_t _wy, float _x, float _y, float _z) : wx(_wx), wy(_wy), x(_x), y(_y), z(_z) {}
	};

	static const int RPC_NB_SUPPORTED_TYPES = 10;

	struct Parameter
	{
		mapbox::util::variant<  bool,
								int32_t,
								float,
								Vector2,
								Vector3i,
								Vector3,
								Quat,
								Color,
								Position,
								std::string
		> m_value;

	public:
		// Constructors --------------------------------
		Parameter() {}
		Parameter(bool _bool);
		Parameter(int _int);
		Parameter(float _float);
		Parameter(float _x, float _y);
		Parameter(uint32_t _x, uint32_t _y, uint32_t _z);
		Parameter(float _x, float _y, float _z);
		Parameter(float _x, float _y, float _z, float _w, bool _isColor);
		Parameter(uint16_t _wx, uint16_t _wy, float _x, float _y, float _z);
		Parameter(const char* _char);

		void Init(WildRPC::Type _type);

		// Getters -------------------------------------
		WildRPC::Type GetType();

		bool GetValue(bool& _bool);
		bool GetValue(int& _int);
		bool GetValue(float& _float);
		bool GetValue(float& _x, float& _y);
		bool GetValue(uint32_t& _x, uint32_t& _y, uint32_t& _z);
		bool GetValue(float& _x, float& _y, float& _z);
		bool GetValue(float& _x, float& _y, float& _z, float& _w);
		bool GetValue(uint16_t& _wx, uint16_t& _wy, float& _x, float& _y, float& _z);
		bool GetValue(const char*& _char);

		// En/Decoding ----------------------------------
		bool EncodeIn(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset);
		bool DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset);

		// Debug -----------------------------------------

		void Print();
	};

	class Result
	{
		friend class MethodInvocation;

	public:
		bool HasError()
		{
			return (m_error.m_protocolError != 0) || (m_error.m_applicativeError != 0);
		}

		Parameter&	GetParameter(size_t idx) { return m_paramsBuffer[idx]; }

	private:
		std::vector<Parameter>	m_paramsBuffer;
		RPC_Error				m_error;
	};
}