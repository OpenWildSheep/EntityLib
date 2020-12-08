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
	namespace Containers
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
	}

	static const int RPC_NB_SUPPORTED_TYPES = 10;

	enum INOUT
	{
		INOUT_Input,
		INOUT_Output,
		INOUT_COUNT
	};

	struct Param
	{
		INOUT			m_in = INOUT_Input;
		
		mapbox::util::variant<  bool,
								int32_t,
								float,
								Containers::Vector2,
								Containers::Vector3i,
								Containers::Vector3,
								Containers::Quat,
								Containers::Color,
								Containers::Position,
								std::string
		> m_value;

	public:
		Param() {}
		Param(float _float);
		Param(uint16_t _wx, uint16_t _wy, float _x, float _y, float _z);
		Param(float _x, float _y, float _z, float _w);

		bool GetValue(float& _float);
		bool GetValue(uint16_t& _wx, uint16_t& _wy, float& _x, float& _y, float& _z);
		bool GetValue(float& _x, float& _y, float& _z, float& _w);

		void Init(WildRPC::Type _type);

		bool EncodeIn(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset);
		bool DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset);

		WildRPC::Type GetType();
		void Print();
	};

	struct ParamsBuffer
	{
		std::vector<Param>	m_parameters;

		ParamsBuffer();
		~ParamsBuffer();

		Param& Add(INOUT _inout, WildRPC::Type _type);

		bool EncodeIn(uint8_t* _buffer, size_t _bufferSize, size_t& _offset);
		bool DecodeFrom(uint8_t* _buffer, size_t _bufferSize, size_t& _offset);

		void PrintDebug();
	};

	class Result
	{
		friend class MethodInvocation;

	public:
		bool HasError()
		{
			return (m_error.m_protocolError != 0) || (m_error.m_applicativeError != 0);
		}

		Param&	GetParam(size_t idx) { return m_paramsBuffer.m_parameters[idx]; }

	private:
		ParamsBuffer		m_paramsBuffer;
		RPC_Error			m_error;
	};
}