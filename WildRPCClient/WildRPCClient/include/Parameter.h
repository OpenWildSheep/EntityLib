#pragma once

#include "WildRPCType.h"

#include <string>

namespace WRPC
{

	struct Position
	{
		uint16_t		m_worldCellsCoords[2];
		float			m_localCoords[3];
	};



	class WRPC_DLLEXPORT Parameter
	{
	private:
		union ParameterValues
		{
			Position		m_position;
			float			m_floats[4];
			int				m_ints[4];
			char			m_chars[256];
			bool			m_bools[4];
		};


	public:
		Parameter(RPC_Type _type, const char* _name, Argument _inout) : m_argumentInOut(_inout), m_name(_name), m_type(_type) {}

		virtual RPC_Type GetType() { return m_type; }
		Argument		 GetArgument() { return m_argumentInOut; }

		virtual bool EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset);
		virtual bool DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset);

		void		 SetName(const char* _name) { m_name = _name; }
		const char*  GetName() { return m_name; }

		// -------------------------

		void	SetValues(float _x, float _y, float _z, float _w);
		void	SetValues(unsigned short _wx, unsigned short _wy, float _x, float _y, float _z);
		void	SetValue(float _values);

		void	GetValues(float& _x, float& _y, float& _z, float& _w);
		void	GetValues(uint16_t& _wx, uint16_t& _wy, float& _x, float& _y, float& _z);
		void	GetValue(float& _value);

	protected:
		Argument			m_argumentInOut = Argument::In;
		const char*			m_name = nullptr;
		RPC_Type			m_type;
		ParameterValues		m_values;
	};

}