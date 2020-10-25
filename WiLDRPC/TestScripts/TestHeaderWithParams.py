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

    #header = rpc.BuildHeaderWithParameters("CameraManager", "RPC_Test", [rpc.Type_Vector3, rpc.Type_Integer, rpc.Type_Float], [rpc.Type_Integer, rpc.Type_Float])
    #vector3 = rpc.BuildVector3(1.0, 2.0, 3.0)
    #integer = rpc.BuildInteger(3)
    #flt = rpc.BuildFloat(3.141592754)

    header = rpc.BuildHeaderWithParameters("CameraManager", "RPC_SetCamera", [rpc.Type_Position, rpc.Type_Color, rpc.Type_Float], [rpc.Type_Integer])
    position = rpc.BuildPosition(32768, 32768, 1.0, -150.0, 100.0)
    color = rpc.BuildColor(0.0, 0.0, 0.0, 1.0)
    fov = rpc.BuildFloat(100.0)

    #s.sendall(header + vector3 + integer + flt)
    s.sendall(header[0] + position + color + fov)

    data = s.recv(1024)

    protocolError = data[0]
    applicationError = data[1]

    if protocolError != 0:
        print("Protocol Error = ", protocolError)

    if (applicationError != 0):
        print("Application Error", applicationError)


    dataView = memoryview(data)
    dataViewReadIndex = 2
    for rs in header[2]:
        result = rpc.Decode(rs, dataView[dataViewReadIndex:])
        dataViewReadIndex = dataViewReadIndex + result[1] + 4
        print(result[0])

    # Disconnect from Server
    s.close()