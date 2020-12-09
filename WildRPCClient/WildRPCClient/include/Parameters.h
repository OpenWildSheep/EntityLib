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

	struct WRPC_DLLEXPORT Parameter
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
		Parameter(float _x, float _y, float _z, float _w, bool _isQuat = true);
		Parameter(uint16_t _wx, uint16_t _wy, float _x, float _y, float _z);
		Parameter(const char* _char);

		void Init(WildRPC::Type _type);

		// Getters -------------------------------------
		WildRPC::Type GetType() const;

		bool GetValue(bool& _bool) const;
		bool GetValue(int& _int) const;
		bool GetValue(float& _float) const;
		bool GetValue(float& _x, float& _y) const;
		bool GetValue(uint32_t& _x, uint32_t& _y, uint32_t& _z) const;
		bool GetValue(float& _x, float& _y, float& _z) const;
		bool GetValue(float& _x, float& _y, float& _z, float& _w) const;
		bool GetValue(uint16_t& _wx, uint16_t& _wy, float& _x, float& _y, float& _z) const;
		bool GetValue(const char*& _char) const;

		// En/Decoding ----------------------------------
		bool EncodeIn(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset) const;
		bool DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset);

		// Debug -----------------------------------------

		void Print() const;
	};

	class WRPC_DLLEXPORT Result
	{
		friend class MethodInvocation;

	public:
		bool HasError() const
		{
			return (m_error.m_protocolError != 0) || (m_error.m_applicativeError != 0);
		}

		Parameter&	GetParameter(size_t idx) { return m_paramsBuffer[idx]; }

	private:
		std::vector<Parameter>	m_paramsBuffer;
		RPC_Error				m_error;
	};
}