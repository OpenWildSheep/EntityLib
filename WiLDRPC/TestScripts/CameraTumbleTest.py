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
PORT = 9993         # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    prct = 0.0
    while prct < 1.0:
        alpha = prct * 2 * math.pi
        towardsCenterQuat = mathutils.Quaternion((0.0, 0.0, 1.0), math.pi / 2.0 + alpha)
        tiltQuat = mathutils.Quaternion((1.0, 0.0, 0.0), - math.pi / 4.0)
        barrelRollQuat = mathutils.Quaternion((0.0, 1.0, 0.0), alpha)
        quat = towardsCenterQuat @ tiltQuat @ barrelRollQuat
        x = 50.0 * math.cos(alpha)
        y = 50.0 * math.sin(alpha)
        height = 100.0

        prct += 0.01

        rpcMethod_set = rpc.RPCMethod(s, "CameraManager", "DATA_SetCamera", [rpc.Type_Position, rpc.Type_Quat, rpc.Type_Float], [])
        results_set = []
        errors_set = rpcMethod_set.Invoke([[32767, 32767, x, y, height], [quat.x, quat.y, quat.z, quat.w], 120.0], results_set)

        time.sleep(0.016)

    # Disconnect from Server
    s.close()