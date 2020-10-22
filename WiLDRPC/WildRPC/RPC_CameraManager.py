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
import WildRPC.Helpers
import WildRPC.Camera
import WildRPC.Position
import WildRPC.Vector3
import WildRPC.Quat

class Camera:
    worldCellX = 32768
    worldCellY = 32768
    localX = 0.0
    localY = 0.0
    localZ = 0.0
    quatX = 0.0
    quatY = 0.0
    quatZ = 0.0
    quatW = 1.0
    RPC_error = 0

    def __init__(self):
        RPC_error = 1

    def __init__(self, worldCellX, worldCellY, localX, localY, localZ, quatX, quatY, quatZ, quatW):
        self.worldCellX = worldCellX
        self.worldCellY = worldCellY
        self.localX = localX
        self.localY = localY
        self.localZ = localZ
        self.quatX = quatX
        self.quatY = quatY
        self.quatZ = quatZ
        self.quatW = quatW

class CameraManager:
    def __init__(self, _socket):
        self.socket = _socket

    def SetCamera(self, camera):
        error = 0
    
        header = WildRPC.Helpers.BuildHeader("CameraManager::RPC_SetCamera")
        params = WildRPC.RPC_CameraManager.CameraToBinary(camera)

        self.socket.sendall(header + params)

        data = self.socket.recv(1024)

        if data[0] == 0xFF:
            error = data[1]
        else:
            error = BinaryToResult(data)

        return error

    def GetCamera(self):
        header = WildRPC.Helpers.BuildHeader("CameraManager::RPC_GetCamera")

        self.socket.sendall(header)

        data = self.socket.recv(1024)

        camera = Camera(0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0)

        if data[0] == 0xFF:
            camera.RPC_error = data[1]
        else:
            camera = BinaryToCamera(data)

        return camera


def CameraToBinary(camera):
    # Create Camera Data
    bldr2 = flatbuffers.Builder(0)
    WildRPC.Camera.CameraStart(bldr2)

    pos = WildRPC.Position.CreatePosition(bldr2, camera.worldCellX, camera.worldCellY, camera.localX, camera.localY, camera.localZ)
    WildRPC.Camera.CameraAddPosition(bldr2, pos)

    ornt = WildRPC.Quat.CreateQuat(bldr2, camera.quatX, camera.quatY, camera.quatZ, camera.quatW)
    WildRPC.Camera.CameraAddOrientation(bldr2, ornt)

    gen_camera = WildRPC.Camera.CameraEnd(bldr2)
    bldr2.Finish(gen_camera)
    b2 = bldr2.Bytes[bldr2.Head():]

    return b2

def BinaryToResult(binaryData):
    res = WildRPC.Result.Result.GetRootAsResult(binaryData, 0)
    error = res.Result()
    return error

def BinaryToCamera(binaryData):
    rpcCamera = WildRPC.Camera.Camera.GetRootAsCamera(binaryData, 0)
    pos = rpcCamera.Position()
    worldCellX = pos.WorldCellX()
    worldCellY = pos.WorldCellY()
    localPos = WildRPC.Vector3.Vector3()
    pos.LocalPosition(localPos)
    localX = localPos.X()
    localY = localPos.Y()
    localZ = localPos.Z()
    ornt = rpcCamera.Orientation()
    quatX = ornt.X()
    quatY = ornt.Y()
    quatZ = ornt.Z()
    quatW = ornt.W()

    result = Camera(worldCellX, worldCellY, localX, localY, localZ, quatX, quatY, quatZ, quatW)
    return result