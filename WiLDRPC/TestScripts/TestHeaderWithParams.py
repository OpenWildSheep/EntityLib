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

    rpcMethod = rpc.RPCMethod(s, "CameraManager", "RPC_SetCamera", [rpc.Type_Position, rpc.Type_Quat, rpc.Type_Float], [])
    results = []
    errors = rpcMethod.Invoke([[32768, 32768, 1.0, -150.0, 100.0], [0.0, 0.0, 0.0, 1.0], 120.0], results)

    print("Errors = ", errors)
    print("Results = ", results)

    # Disconnect from Server
    s.close()