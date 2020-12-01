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

	bool RPCClient::test1()
	{
		try
		{
			asio::io_context my_io_context;

			asio::ip::tcp::socket s(my_io_context);
			asio::ip::tcp::resolver resolver(my_io_context);
			asio::connect(s, resolver.resolve("127.0.0.1", "9993"));

			const size_t max_length = 4 * 1024;

			//char request[max_length];
			//WildRPC::RPCHeader* header = nullptr;

			// Serialize into new flatbuffer.
			

			unsigned char buffer[4 * 1024];
			unsigned int currentPosition = 0;

			// --------------------------------------

			flatbuffers::FlatBufferBuilder fbb;

			auto managerName = fbb.CreateString("CameraManager");
			auto methodName = fbb.CreateString("DATA_SetCamera");

			std::vector<int8_t> params;
			params.push_back((int8_t)RPC_Type::Position);
			params.push_back((int8_t)RPC_Type::Quat);
			params.push_back((int8_t)RPC_Type::Float);
			auto prms = fbb.CreateVector(params);

			std::vector<int8_t> results;
			auto rslts = fbb.CreateVector(results);

			WildRPC::RPCHeaderBuilder rpcHeader(fbb);
			rpcHeader.add_managerName(managerName);
			rpcHeader.add_methodName(methodName);
			rpcHeader.add_parameterTypes(prms);
			rpcHeader.add_resultTypes(rslts);

			auto hdr = rpcHeader.Finish();
			fbb.FinishSizePrefixed(hdr);

			auto size = fbb.GetSize();
			auto ptr = fbb.GetBufferPointer();
			memcpy(buffer + currentPosition, ptr, size);
			currentPosition += size;

			// ------------------

			fbb.Clear();

			WildRPC::Vector3Builder vec3Builder(fbb);
			vec3Builder.add_x(1.0f);
			vec3Builder.add_y(2.0f);
			vec3Builder.add_z(3.0f);
			auto localPos = vec3Builder.Finish();

			WildRPC::PositionBuilder posBuilder(fbb);
			posBuilder.add_worldCellX(32768);
			posBuilder.add_worldCellY(32768);
			posBuilder.add_localPosition(localPos);
			auto pos = posBuilder.Finish();

			fbb.FinishSizePrefixed(pos);

			size = fbb.GetSize();
			ptr = fbb.GetBufferPointer();
			memcpy(buffer + currentPosition, ptr, size);
			currentPosition += size;

			// ------------------

			fbb.Clear();

			WildRPC::QuatBuilder quatBuilder(fbb);
			quatBuilder.add_x(0.0f);
			quatBuilder.add_y(0.0f);
			quatBuilder.add_z(0.0f);
			quatBuilder.add_w(1.0f);
			auto ornt = quatBuilder.Finish();

			fbb.FinishSizePrefixed(ornt);

			size = fbb.GetSize();
			ptr = fbb.GetBufferPointer();
			memcpy(buffer + currentPosition, ptr, size);
			currentPosition += size;

			// --------------------

			fbb.Clear();

			WildRPC::FloatBuilder floatBuilder(fbb);
			floatBuilder.add_value(120.0f);
			auto foV = floatBuilder.Finish();

			fbb.FinishSizePrefixed(foV);

			size = fbb.GetSize();
			ptr = fbb.GetBufferPointer();
			memcpy(buffer + currentPosition, ptr, size);
			currentPosition += size;

			// ---------------------
			
			asio::write(s, asio::buffer(buffer, currentPosition + 1));

			char reply[max_length];
			size_t reply_length = asio::read(s, asio::buffer(reply, max_length));


			
			std::cout << "Read:" << reply_length << "\n";
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}

		return true;
	}

	bool RPCClient::test2()
	{
		try
		{
			asio::io_context my_io_context;

			asio::ip::tcp::socket s(my_io_context);
			asio::ip::tcp::resolver resolver(my_io_context);
			asio::connect(s, resolver.resolve("127.0.0.1", "9993"));

			const size_t max_length = 4 * 1024;

			//char request[max_length];
			//WildRPC::RPCHeader* header = nullptr;

			// Serialize into new flatbuffer.


			unsigned char buffer[4 * 1024];
			unsigned int currentPosition = 0;

			// --------------------------------------

			flatbuffers::FlatBufferBuilder fbb;

			auto managerName = fbb.CreateString("CameraManager");
			auto methodName = fbb.CreateString("DATA_GetCamera");

			std::vector<int8_t> params;
			auto prms = fbb.CreateVector(params);

			std::vector<int8_t> results;
			results.push_back((int8_t)RPC_Type::Position);
			results.push_back((int8_t)RPC_Type::Quat);
			results.push_back((int8_t)RPC_Type::Float);
			auto rslts = fbb.CreateVector(results);

			WildRPC::RPCHeaderBuilder rpcHeader(fbb);
			rpcHeader.add_managerName(managerName);
			rpcHeader.add_methodName(methodName);
			rpcHeader.add_parameterTypes(prms);
			rpcHeader.add_resultTypes(rslts);

			auto hdr = rpcHeader.Finish();
			fbb.FinishSizePrefixed(hdr);

			auto size = fbb.GetSize();
			auto ptr = fbb.GetBufferPointer();
			memcpy(buffer + currentPosition, ptr, size);
			currentPosition += size;

			// ------------------

			asio::write(s, asio::buffer(buffer, currentPosition + 1));

			unsigned char reply[max_length];
			size_t reply_length = asio::read(s, asio::buffer(reply, max_length));

			unsigned char protocolErrpr = reply[0];
			unsigned char applicativeErrpr = reply[1];
			printf("%d / %d\n", protocolErrpr, applicativeErrpr);

			int readingIndex = 2;

			unsigned char* sz = reinterpret_cast<unsigned char*>(&reply[readingIndex]);
			size = *sz;
			auto pos = WildRPC::GetSizePrefixedPosition(&reply[readingIndex]);
			printf("Position (%d,%d) (%.2f, %.2f, %.2f)\n", pos->worldCellX(), pos->worldCellY(), pos->localPosition()->x(), pos->localPosition()->y(), pos->localPosition()->z());
			readingIndex += (size + 4);

			sz = reinterpret_cast<unsigned char*>(&reply[readingIndex]);
			size = *sz;
			auto quat = WildRPC::GetSizePrefixedQuat(&reply[readingIndex]);
			printf("Quat (%.2f, %.2f, %.2f, %.2f)\n", quat->x(), quat->y(), quat->z(), quat->w());
			readingIndex += (size + 4);

			sz = reinterpret_cast<unsigned char*>(&reply[readingIndex]);
			size = *sz;
			auto floatValue = WildRPC::GetSizePrefixedFloat(&reply[readingIndex]);
			printf("FoV: %f\n", floatValue->value());
			readingIndex += (size + 4);

			std::cout << "Read:" << reply_length << "\n";
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}

		return true;
	}

	bool RPCClient::test3()
	{
		try
		{
			asio::io_context my_io_context;

			asio::ip::tcp::socket s(my_io_context);
			asio::ip::tcp::resolver resolver(my_io_context);
			asio::connect(s, resolver.resolve("127.0.0.1", "9993"));

			MethodInvocation getCameraMethod("CameraManager", "DATA_GetCamera");
			RPC_Error error = getCameraMethod.Execute(s);

		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}

		return true;
	}

} // namespace WRPC
