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
		bool GetValue(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z) const;
		bool GetValue(std::string& _char) const;

		// En/Decoding ----------------------------------
		bool EncodeIn(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset) const;
		bool DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset);

		// Debug -----------------------------------------

		void Print() const;
	};

	// -----------------------

	struct Vector2H
	{
		float *x, *y;
		Vector2H(float& _x, float& _y) : x(&_x), y(&_y) {}
	};

	struct Vector3H
	{
		float *x, *y, *z;
		Vector3H(float& _x, float& _y, float& _z) : x(&_x), y(&_y), z(&_z) {}
	};

	struct QuatH
	{
		float *x, *y, *z, *w;
		QuatH(float& _x, float& _y, float& _z, float& _w) : x(&_x), y(&_y), z(&_z), w(&_w) {}
	};

	struct ColorH
	{
		float *r, *g, *b, *a;
		ColorH(float& _r, float& _g, float& _b, float& _a) : r(&_r), g(&_g), b(&_b), a(&_a) {}
	};

	struct Vector3iH
	{
		uint32_t *x, *y, *z;
		Vector3iH(uint32_t& _x, uint32_t& _y, uint32_t& _z) : x(&_x), y(&_y), z(&_z) {}
	};

	struct PositionH
	{
		uint32_t *wx, *wy;
		float *x, *y, *z;
		PositionH(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z) : wx(&_wx), wy(&_wy), x(&_x), y(&_y), z(&_z) {}
	};

	typedef mapbox::util::variant<  bool*,
									int32_t*,
									float*,
									Vector2H,
									Vector3iH,
									Vector3H,
									QuatH,
									ColorH,
									PositionH,
									std::string*
	> ResultHolder;

	struct ResultValue
	{
		ResultValue(bool& _bool);
		ResultValue(int32_t& _int);
		ResultValue(float& _float);
		ResultValue(float& _x, float& _y);
		ResultValue(uint32_t& _x, uint32_t& _y, uint32_t& _z);
		ResultValue(float& _x, float& _y, float& _z);
		ResultValue(float& _qx, float& _qy, float& _qz, float& _qw, bool _isColor = false);
		ResultValue(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z);
		ResultValue(std::string& _strg);

		ResultHolder m_value;
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
		bool		RetrieveValues(std::vector<ResultValue> _holders);

	private:
		std::vector<Parameter>	m_paramsBuffer;
		RPC_Error				m_error;
	};
}