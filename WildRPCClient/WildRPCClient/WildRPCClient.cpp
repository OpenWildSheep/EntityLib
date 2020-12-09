#include "include/WildRPCClient.h"
#include "include/WildRPCType.h"

#include <iostream>
#include <array>

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
#include <WiLDRPC/RPCHeader_generated.h>
#pragma warning(pop)

#include "include/MethodInvocation.h"

namespace WRPC
{

    RPCClient::RPCClient()
    {
    }
    RPCClient::~RPCClient()
    {
    }

	bool RPCClient::test()
	{
		Connection connection("127.0.0.1");
		connection.Open();

		if (connection.GetStatus() != ConnectionStatus::Connected)
		{
			printf("Connection ERROR!\n");
			return false;
		}

		MethodInvocation setCamera("CameraManager", "DATA_SetCamera",
								   ThreadSafety::Safe,
								   { WildRPC::Type_Position, WildRPC::Type_Quat, WildRPC::Type_Float }, {});
		setCamera.SetParameters({ P(32768u, 32768u, 1.0f, 2.0f, 3.0f), P(0.0f, 0.0f, 0.0f, 1.0f, false), P(40.0f) });
		setCamera.Execute(connection);

		MethodInvocation getCamera("CameraManager", "DATA_GetCamera",
								   ThreadSafety::Safe,
								   {},  { WildRPC::Type_Position, WildRPC::Type_Quat, WildRPC::Type_Float });
		Result anotherResult = getCamera.Execute(connection);

		connection.Close();

		if (!anotherResult.HasError())
		{
			unsigned short wx, wy;
			float x, y, z;
			anotherResult.GetParameter(0).GetValue(wx, wy, x, y, z);
			printf("_position: [%d,%d] (%.2f, %.2f, %.2f)\n", wx, wy, x, y, z);
		
			float qx, qy, qz, qw;
			anotherResult.GetParameter(1).GetValue(qx, qy, qz, qw);
			printf("_quat: (%.2f, %.2f, %.2f, %.2f)\n", qx, qy, qz, qw);
		
			float value;
			anotherResult.GetParameter(2).GetValue(value);
			printf("_foV: (%.2f)\n", value);
		}
		else
		{
			printf("Connection ERROR!\n");
		}

		return true;
	}

} // namespace WRPC
