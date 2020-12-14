#include "include/WildRPCClient.h"
#include "include/WildRPCType.h"

#include <iostream>
#include <array>
#include <ctime>

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
			return true;
		}

		MethodInvocation setCamera("CameraManager", "DATA_SetCamera",
								   ThreadSafety::Safe,
								   { WildRPC::Type_Vector3, WildRPC::Type_Quat, WildRPC::Type_Float }, {});

		std::clock();
		for (int i = 0; i < 300; i++)
		{
			setCamera.Execute(connection, { Parameter::Build<WildRPC::Type_Vector3>(0.0f, 0.0f, -10.0f + 0.1f * i),
											Parameter::Build<WildRPC::Type_Quat>(0.0f, 0.0f, 0.0f, 1.0f),
											Parameter::Build<WildRPC::Type_Float>(40.0f) });

			auto now = std::clock();
			while (std::clock() < (now + 32.0f)) continue;
		}

		MethodInvocation getCamera("CameraManager", "DATA_GetCamera",
								   ThreadSafety::Safe,
								   {},  { WildRPC::Type_Vector3, WildRPC::Type_Quat, WildRPC::Type_Float });
		Result anotherResult = getCamera.Execute(connection, {});

		MethodInvocation stringTest("DebugManager", "RPC_DebugStringParameters",
			ThreadSafety::Unsafe,
			{ WildRPC::Type_String }, { WildRPC::Type_String });
		Result yetAnotherResult = stringTest.Execute(connection, { Parameter::Build<WildRPC::Type_String>("Knock knock, who's there?")});
		std::string answer;

		yetAnotherResult.RetrieveValues({ ResultValue::Build<WildRPC::Type_String>(answer)});

		connection.Close();

		if (!anotherResult.HasError())
		{
			float x, y, z;
			float qx, qy, qz, qw;
			float foV;
			anotherResult.RetrieveValues({ ResultValue::Build<WildRPC::Type_Vector3>(x, y, z),
										   ResultValue::Build<WildRPC::Type_Quat>(qx, qy, qz, qw),
										   ResultValue::Build<WildRPC::Type_Float>(foV) });

			printf("_position: (%.2f, %.2f, %.2f)\n", x, y, z);
			printf("_quat: (%.2f, %.2f, %.2f, %.2f)\n", qx, qy, qz, qw);
			printf("_foV: (%.2f)\n", foV);
		}
		else
		{
			printf("Connection ERROR: %s!\n", anotherResult.GetErrorString());
		}

		return true;
	}

} // namespace WRPC
