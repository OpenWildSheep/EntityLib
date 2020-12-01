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

	bool RPCClient::test2()
	{
		try
		{
			asio::io_context my_io_context;

			asio::ip::tcp::socket s(my_io_context);
			asio::ip::tcp::resolver resolver(my_io_context);
			asio::connect(s, resolver.resolve("127.0.0.1", "9993"));

			MethodInvocation getCameraMethod("CameraManager", "DATA_GetCamera");
			getCameraMethod.AddResult(RPC_Type::Position, "position");
			getCameraMethod.AddResult(RPC_Type::Quat, "quat");
			getCameraMethod.AddResult(RPC_Type::Float, "fov");

			RPC_Error error = getCameraMethod.Execute(s);

			if (error.m_protocolError == 0 && error.m_applicativeError == 0)
			{
				unsigned short wx, wy;
				float x, y, z;
				bool pos_ok = getCameraMethod.GetPositionResult("position", wx, wy, x, y, z);

				float qx, qy, qz, qw;
				bool quat_ok = getCameraMethod.GetQuatResult("quat", qx, qy, qz, qw);

				float fov;
				bool fov_Ok = getCameraMethod.GetFloatResult("fov", fov);

				if (pos_ok)
				{
					printf("Position (%d, %d, %.2f, %.2f, %.2f)\n", wx, wy, x, y, z);
				}
				else
				{
					printf("Position Not Ok!\n");
				}

				if (quat_ok)
				{
					printf("Quat (%.2f, %.2f, %.2f, %.2f)\n", qx, qy, qz, qw);
				}
				else
				{
					printf("Quat Not Ok!\n");
				}

				if (fov_Ok)
				{
					printf("FoV : %.2f\n", fov);
				}
				else
				{
					printf("FoV Not Ok!\n");
				}
			}

		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}

		return true;
	}

	bool RPCClient::test1()
	{
		try
		{
			asio::io_context my_io_context;

			asio::ip::tcp::socket s(my_io_context);
			asio::ip::tcp::resolver resolver(my_io_context);
			asio::connect(s, resolver.resolve("127.0.0.1", "9993"));

			MethodInvocation getCameraMethod("CameraManager", "DATA_SetCamera");
			getCameraMethod.AddPositionParameter(32766, 32767, 60.0f, 20.0f, 40.0f);
			getCameraMethod.AddQuatParameter(0.0f, 0.0f, 0.0f, 1.0f);
			getCameraMethod.AddFloatParameter(120.0f);

			RPC_Error error = getCameraMethod.Execute(s);

		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}

		return true;
	}

	bool RPCClient::test3()
	{
		SetEngineIPAddress("127.0.0.1");

		// CONNECT -----------------------
		Connect();

		// SET Camera --------------------
		PrepareMethodInvocation("CameraManager", "DATA_SetCamera");
		AddPositionParameter(32766, 32767, 60.0f, 20.0f, 40.0f);
		AddQuatParameter(0.0f, 0.0f, 0.0f, 1.0f);
		AddFloatParameter(120.0f);

		RPC_Error error = ExecuteMethod_ThreadSafe();

		// GET Camera --------------------
		PrepareMethodInvocation("CameraManager", "DATA_GetCamera");
		AddResult(RPC_Type::Position, "position");
		AddResult(RPC_Type::Quat, "quat");
		AddResult(RPC_Type::Float, "fov");
		
		RPC_Error error = ExecuteMethod_ThreadSafe();

		unsigned short wx, wy;
		float x, y, z;
		bool pos_ok = GetPositionResult("position", wx, wy, x, y, z);

		float qx, qy, qz, qw;
		bool quat_ok = GetQuatResult("quat", qx, qy, qz, qw);

		float fov;
		bool fov_Ok = GetFloatResult("fov", fov);

		// DISCONNECT -----------------------
		Disconnect();
	}

	// ------------------------------

	void RPCClient::SetEngineIPAddress(const char* _address) {}

	bool RPCClient::Connect() { return false; }
	bool RPCClient::Disconnect() { return false; }
	bool RPCClient::IsConnected() { return false; }

	void RPCClient::PrepareMethodInvocation(const char* _managerName, const char* _methodName) {}

	void RPCClient::AddPositionParameter(unsigned short _worldCellX, unsigned short _worldCellY, float _x, float _y, float _z) {}
	void RPCClient::AddQuatParameter(float _x, float _y, float _z, float _w) {}
	void RPCClient::AddFloatParameter(float _value) {}

	void RPCClient::AddResult(RPC_Type _param, const char* _name) {}

	RPC_Error RPCClient::ExecuteMethod_ThreadSafe() {}
	RPC_Error RPCClient::ExecuteMethod_NotThreadSafe() {}

	bool RPCClient::GetFloatResult(const char* _paramName, float& _result) {}
	bool RPCClient::GetPositionResult(const char* _paramName, unsigned short& _worldCellX, unsigned short& _worldCellY, float& _x, float& _y, float& _z) {}
	bool RPCClient::GetQuatResult(const char* _paramName, float& _x, float& _y, float& _z, float& _w) {}

} // namespace WRPC
