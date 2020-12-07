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

#include "include/Position.h"
#include "include/Quat.h"
#include "include/FloatParameter.h"

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
		Connection* connection = NewConnection("127.0.0.1");

		MethodInvocation* setCamera = NewMethodInvocation("CameraManager", "DATA_SetCamera", ThreadSafety::Safe);
		setCamera->AddParameter<Position>("_position", Argument::In, 32768u, 32768u, 1.0f, 2.0f, 3.0f);
		setCamera->AddParameter<Quat>("_orientation", Argument::In, 0.0f, 0.0f, 0.0f, 1.0f);
		setCamera->AddParameter<Float>("_foV", Argument::In, 50.0f);

		Result result;
		setCamera->Execute(connection, result);

		MethodInvocation* getCamera = NewMethodInvocation("CameraManager", "DATA_GetCamera", ThreadSafety::Safe);
		getCamera->AddParameter<Position>("_position", Argument::Out);
		getCamera->AddParameter<Quat>("_orientation", Argument::Out);
		getCamera->AddParameter<Float>("_foV", Argument::Out);

		Result anotherResult;
		getCamera->Execute(connection, anotherResult);

		if (!result.HasError())
		{
			unsigned short wx, wy;
			float x, y, z;
			anotherResult.GetParameter<Position>("_position", wx, wy, x, y, z);
			printf("_position: [%d,%d] (%.2f, %.2f, %.2f)\n", wx, wy, x, y, z);

			float qx, qy, qz, qw;
			anotherResult.GetParameter<Quat>("_quat", qx, qy, qz, qw);
			printf("_quat: (%.2f, %.2f, %.2f, %.2f)\n", qx, qy, qz, qw);

			float value;
			anotherResult.GetParameter<Float>("_foV", value);
			printf("_foV: (%.2f)\n", value);
 		}

		return true;
	}

	// ------------------------------

	MethodInvocation* RPCClient::NewMethodInvocation(const char* _managerName, const char* _methodName, ThreadSafety _threadSafety)
	{
		return new MethodInvocation(_managerName, _methodName, _threadSafety);
	}

	Connection* RPCClient::NewConnection(const char* _IPaddress) {
		auto cnnx = new Connection(_IPaddress);
		cnnx->Open();
		return cnnx;
	}

} // namespace WRPC
