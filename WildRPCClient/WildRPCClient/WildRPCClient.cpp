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

namespace std
{
    template <typename T>
    string to_string(const vector<T>& v)
    {
        string s = "[";
        for (size_t i = 0; i < v.size(); ++i)
        {
            s += to_string(v[i]) + ", ";
        }
        s += "]";
        return s;
    }

    string to_string(const string& v)
    {
        return v;
    }

    string to_string(const WRPC::Vector3& v)
    {
        char buff[64];
        snprintf(buff, sizeof(buff), "(%f, %f, %f)", v.x, v.y, v.z);
        return buff;
    }

    string to_string(const WRPC::Quat& v)
    {
        char buff[64];
        snprintf(buff, sizeof(buff), "(%f, %f, %f, %f)", v.x, v.y, v.z, v.w);
        return buff;
    }

    string to_string(const WRPC::Position& v)
    {
        char buff[64];
        snprintf(buff, sizeof(buff), "(%d, %d) (%f, %f, %f)", v.wx, v.wy, v.x, v.y, v.z);
        return buff;
    }
}

namespace WRPC
{
    using namespace std;

    void unitTests(Connection& connection)
    {
        MethodInvocation GetInt("RPCMarshallingTests", "RPC_GetInt", {}, {Type::Integer});
        MethodInvocation SetInt("RPCMarshallingTests", "RPC_SetInt", {Type::Integer}, {});
        MethodInvocation GetFloat("RPCMarshallingTests", "RPC_GetFloat", {}, {Type::Float});
        MethodInvocation SetFloat("RPCMarshallingTests", "RPC_SetFloat", {Type::Float}, {});
        MethodInvocation GetString("RPCMarshallingTests", "RPC_GetString", {}, {Type::String});
        MethodInvocation SetString("RPCMarshallingTests", "RPC_SetString", {Type::String}, {});
        MethodInvocation GetVector3("RPCMarshallingTests", "RPC_GetVector3", {}, {Type::Vector3});
        MethodInvocation SetVector3("RPCMarshallingTests", "RPC_SetVector3", {Type::Vector3}, {});
        MethodInvocation GetPosition("RPCMarshallingTests", "RPC_GetPosition", {}, {Type::Position});
        MethodInvocation SetPosition("RPCMarshallingTests", "RPC_SetPosition", {Type::Position}, {});

        auto dump = [](const char* header, auto value)
        {
            printf("%s: %s\n", header, to_string(value).c_str());
        };

        Result r;

        //SetInt.Execute(connection, { Parameter(123) });
        SetInt.Execute(connection, { 123 });
        r = GetInt.Execute(connection, {});
        dump("GetInt", r.NextScalar<int>());

        SetFloat.Execute(connection, { 3.14f });
        r = GetFloat.Execute(connection, {});
        dump("GetFloat", r.NextScalar<float>());

        //SetString.Execute(connection, { string("hello") });
        SetString.Execute(connection, { "hello" });
        r = GetString.Execute(connection, {});
        dump("GetString", r.NextScalar<string>());

        SetVector3.Execute(connection, { Vector3(1,2,3) });
        r = GetVector3.Execute(connection, {});
        dump("GetVector3", r.NextScalar<Vector3>());

        SetPosition.Execute(connection, { Position(0,1, 2, 3, 4) });
        r = GetPosition.Execute(connection, {});
        dump("GetPosition", r.NextScalar<Position>());

        SetPosition.Execute(connection, { Position(0,1, 2, 3, 4) });
        r = GetPosition.Execute(connection, {});
        dump("GetPosition", r.NextScalar<Position>());

        try
        {
            r = GetInt.Execute(connection, {});
            dump("GetInt", r.NextScalar<float>());
        }
        catch (mapbox::util::bad_variant_access& e)
        {
            printf("GetInt: intentionally requested the wrong type -> %s\n", e.what());
        }


        MethodInvocation GetIntArray("RPCMarshallingTests", "RPC_GetIntArray", {}, {Type::IntegerArray});
        MethodInvocation SetIntArray("RPCMarshallingTests", "RPC_SetIntArray", {Type::IntegerArray}, {});
        MethodInvocation GetFloatArray("RPCMarshallingTests", "RPC_GetFloatArray", {}, {Type::FloatArray});
        MethodInvocation SetFloatArray("RPCMarshallingTests", "RPC_SetFloatArray", {Type::FloatArray}, {});
        MethodInvocation GetStringArray("RPCMarshallingTests", "RPC_GetStringArray", {}, {Type::StringArray});
        MethodInvocation SetStringArray("RPCMarshallingTests", "RPC_SetStringArray", {Type::StringArray}, {});
        MethodInvocation GetVector3Array("RPCMarshallingTests", "RPC_GetVector3Array", {}, {Type::Vector3Array});
        MethodInvocation SetVector3Array("RPCMarshallingTests", "RPC_SetVector3Array", {Type::Vector3Array}, {});
        MethodInvocation GetPositionArray("RPCMarshallingTests", "RPC_GetPositionArray", {}, {Type::PositionArray});
        MethodInvocation SetPositionArray("RPCMarshallingTests", "RPC_SetPositionArray", {Type::PositionArray}, {});

        SetIntArray.Execute(connection, { vector<int>{1, 2, 3} });
        r = GetIntArray.Execute(connection, {});
        dump("GetIntArray", r.NextVector<int>());

        SetStringArray.Execute(connection, { vector<string>{"a", "b", "c"} });
        r = GetStringArray.Execute(connection, {});
        dump("GetStringArray", r.NextVector<string>());

        SetVector3Array.Execute(connection, { vector<Vector3>{{1, 2, 3}, {4, 5, 6}} });
        r = GetVector3Array.Execute(connection, {});
        dump("GetVector3Array", r.NextVector<Vector3>());

        SetPositionArray.Execute(connection, { vector<Position>{{0, 1, 2, 3, 4}, {5, 6, 7, 8, 9}} });
        r = GetPositionArray.Execute(connection, {});
        dump("GetPositionArray", r.NextVector<Position>());


        MethodInvocation SetCamera("CameraManager", "RPC_SetCamera", {Type::Vector3, Type::Quat, Type::Float}, {});
        MethodInvocation GetCamera("CameraManager", "RPC_GetCamera", {}, {Type::Vector3, Type::Quat, Type::Float});
        r = GetCamera.Execute(connection, {});
        auto pos = r.NextScalar<Vector3>();
        auto rot = r.NextScalar<Quat>();
        auto fov = r.NextScalar<float>();
        printf("GetCamera: pos %s, rot %s, fov %s\n", to_string(pos).c_str(), to_string(rot).c_str(), to_string(fov).c_str());
    }


    void cameraTest(Connection& connection)
    {
        MethodInvocation setCamera(
            "CameraManager",
            "RPC_SetCamera",
            {Type::Vector3, Type::Quat, Type::Float},
            {});

        std::clock();
        for (int i = 0; i < 300; i++)
        {
            printf("setCamera %d\n", i);
            setCamera.Execute(connection, {
                Vector3{0.0f, 0.0f, -10.0f + 0.1f * float(i)},
                Quat{0.0f, 0.0f, 0.0f, 1.0f},
                40.0f
            });

            auto now = std::clock();
            while (std::clock() < (now + 0.01 * CLOCKS_PER_SEC)) // 32 seconds
                continue;
        }


        MethodInvocation getCamera(
            "CameraManager",
            "RPC_GetCamera",
            {},
            {Type::Vector3, Type::Quat, Type::Float});
        Result anotherResult = getCamera.Execute(connection, {});

        if (!anotherResult.HasError())
        {
            auto p = anotherResult.NextScalar<Vector3>();
            auto q = anotherResult.NextScalar<Quat>();
            auto foV = anotherResult.NextScalar<float>();
            printf("_position: (%.2f, %.2f, %.2f)\n", p.x, p.y, p.z);
            printf("_quat: (%.2f, %.2f, %.2f, %.2f)\n", q.x, q.y, q.z, q.w);
            printf("_foV: (%.2f)\n", foV);
        }
        else
        {
            printf("Connection ERROR: %s!\n", anotherResult.GetErrorString());
        }


        MethodInvocation stringTest(
            "DebugManager",
            "RPC_DebugStringParameters",
            {Type::String},
            {Type::String});
        Result yetAnotherResult = stringTest.Execute(connection, { string("Knock knock!") });
        printf("answer: %s\n", yetAnotherResult.NextScalar<string>().c_str());
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

        unitTests(connection);
        cameraTest(connection);

        connection.Close();
        return true;
    }

} // namespace WRPC
