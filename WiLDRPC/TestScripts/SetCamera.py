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
import WildRPC.Helpers
import WildRPC.RPC_CameraManager

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 9387         # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    cameraManager = WildRPC.RPC_CameraManager.CameraManager(s)

    error = 0
    prct = 0.0
    while prct < 1.0 and error == 0:

        alpha = prct * 2 * math.pi
        towardsCenterQuat = mathutils.Quaternion((0.0, 0.0, 1.0), math.pi / 2.0 + alpha)
        tiltQuat = mathutils.Quaternion((1.0, 0.0, 0.0), - math.pi / 4.0)
        barrelRollQuat = mathutils.Quaternion((0.0, 1.0, 0.0), alpha)
        quat = towardsCenterQuat @ tiltQuat @ barrelRollQuat
        x = 100.0 * math.cos(alpha)
        y = 100.0 * math.sin(alpha)
        height = 100.0

        prct += 0.01

        camera = WildRPC.RPC_CameraManager.Camera(32768, 32768, x, y, height, quat.x, quat.y, quat.z, quat.w)
        error = cameraManager.SetCamera(camera)

        if error != 0:
            print("Stopped with error ", error)

        
    camera = cameraManager.GetCamera()
    print(camera.worldCellX, ",", camera.worldCellY, ", (", camera.localX, ",", camera.localY, ",", camera.localZ, ")")

    # Disconnect from Server
    s.close()