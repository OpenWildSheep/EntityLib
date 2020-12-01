#pragma once

#include <cstdio>
#include <exception>
#include <string>

#include "WildRPCType.h"
#include "Parameter.h"


namespace WRPC
{
	class WRPC_DLLEXPORT Position : public Parameter
	{
	public:
		Position();

		void GetValues(unsigned short& _worldCellX, unsigned short& _worldCellY, float& _x, float& _y, float& _z);
		void SetValues(unsigned short _worldCellX, unsigned short worldCellY, float _x, float _y, float _z);

		RPC_Type GetType() override { return RPC_Type::Position; }

		bool EncodeIn(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)  override;
		bool DecodeFrom(unsigned char* _buffer, size_t _totalBufferSize, size_t* _offset)  override;

	private:
		unsigned short	m_worldCellsCoords[2];
		float			m_localCoordinates[3];

	};


}