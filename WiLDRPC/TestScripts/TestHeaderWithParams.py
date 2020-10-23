#!/usr/bin/env python3

import socket
import struct
import time
import math
import mathutils

import sys
sys.path.append('..')
sys.path.append('../../../External/FlatBuffers/python')

import flatbuffers
import WildRPC.Camera
import WildRPC.Result
import WildRPC.Position
import WildRPC.Quat
import WildRPC.RPCHeader
import WildRPC.Helpers as rpc

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 9387         # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    header = rpc.BuildHeaderWithParameters("CameraManager::RPC_SetCamera", [rpc.Type_Vector3, rpc.Type_Integer, rpc.Type_Float], [rpc.Type_Integer, rpc.Type_Float])
    vector3 = rpc.BuildVector3(1.0, 2.0, 3.0)
    integer = rpc.BuildInteger(3)
    flt = rpc.BuildFloat(3.141592754)

    s.sendall(header + vector3 + integer + flt)

    data = s.recv(1024)

    dataView = memoryview(data)

    dataViewReadIndex = 0

    # print("Starting to read from : ", dataViewReadIndex)
    result = rpc.Decode(rpc.Type_Integer, dataView[dataViewReadIndex:])
    dataViewReadIndex = dataViewReadIndex + result[1] + 4

    print(result[0])
    # print("Size = ", readSize)

    # print("Starting to read from : ", dataViewReadIndex)
    result = rpc.Decode(rpc.Type_Float, dataView[dataViewReadIndex:])
    dataViewReadIndex = dataViewReadIndex + result[1] + 4
    
    print(result[0])
    # print("Size = ", readSize)

    # Disconnect from Server
    s.close()