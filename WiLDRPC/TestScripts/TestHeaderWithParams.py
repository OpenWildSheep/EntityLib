#!/usr/bin/env python3

import socket
import struct
import time
import math
import mathutils

import sys
sys.path.append('..')
sys.path.append('../../../External/FlatBuffers/python')

import Helpers as rpc

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 9387         # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    # rpcMethod_test = rpc.RPCMethod(s, "RPCServerManager", "RPC_TestMethod", [rpc.Type_Integer, rpc.Type_Float, rpc.Type_Boolean, rpc.Type_Quat, rpc.Type_Vector3, rpc.Type_UInt3, rpc.Type_Vector2, rpc.Type_Position, rpc.Type_Color], [rpc.Type_Integer, rpc.Type_Float, rpc.Type_Boolean, rpc.Type_Quat, rpc.Type_Vector3, rpc.Type_UInt3, rpc.Type_Vector2, rpc.Type_Position, rpc.Type_Color])
    # results_test = []
    # errors_test = rpcMethod_test.Invoke([1, 2.0, True, [0.0, 0.0, 0.0, 1.0], [1.0, 2.0, 3.0], [1, 2, 3], [1.0, 2.0], [32768, 32768, 1.0, 2.0, 3.0]], results_test)

    # print("Errors = ", errors_test)
    # print("Results = ", results_test)

    rpcMethod_set = rpc.RPCMethod(s, "CameraManager", "RPC_SetCamera", [rpc.Type_Position, rpc.Type_Quat, rpc.Type_Float], [])
    results_set = []
    errors_set = rpcMethod_set.Invoke([[32768, 32768, 1.0, -150.0, 100.0], [0.0, 0.0, 0.0, 1.0], 120.0], results_set)
    print("CameraManager", "RPC_SetCamera")
    print("Errors = ", errors_set)
    print("Results = ", results_set)

    rpcMethod_get = rpc.RPCMethod(s, "CameraManager", "RPC_GetCamera", [], [rpc.Type_Position, rpc.Type_Quat, rpc.Type_Float])
    results_get = []
    errors_get = rpcMethod_get.Invoke([], results_get)
    print("CameraManager", "RPC_GetCamera")
    print("Errors = ", errors_get)
    print("Results = ", results_get)

    # Disconnect from Server
    s.close()