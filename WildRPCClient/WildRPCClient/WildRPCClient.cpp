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
	typedef Parameter v;
	typedef ResultValue r;

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

		setCamera.Execute(connection, {v(32768u, 32768u, 1.0f, 2.0f, 3.0f), v(0.0f, 0.0f, 0.0f, 1.0f), v(40.0f)});

		MethodInvocation getCamera("CameraManager", "DATA_GetCamera",
								   ThreadSafety::Safe,
								   {},  { WildRPC::Type_Position, WildRPC::Type_Quat, WildRPC::Type_Float });

		Result anotherResult = getCamera.Execute(connection, {});

		connection.Close();

		if (!anotherResult.HasError())
		{
			uint32_t wx, wy;
			float x, y, z;
			float qx, qy, qz, qw;
			float foV;
			anotherResult.RetrieveValues({ r(wx, wy, x, y, z), r(qx, qy, qz, qw), r(foV) });

			printf("_position: [%d,%d] (%.2f, %.2f, %.2f)\n", wx, wy, x, y, z);
			printf("_quat: (%.2f, %.2f, %.2f, %.2f)\n", qx, qy, qz, qw);
			printf("_foV: (%.2f)\n", foV);
		}
		else
		{
			printf("Connection ERROR!\n");
		}

		return true;
	}

} // namespace WRPC
