#!/usr/bin/env python3

import socket
import struct
import time

import sys
sys.path.append('..')
sys.path.append('../../../External/FlatBuffers/python')

import flatbuffers
import WildRPC.Camera
import WildRPC.Result
import WildRPC.Position
import WildRPC.Quat
import WildRPC.RPCHeader

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 9387         # The port used by the server

bldr = flatbuffers.Builder(0)
methodName = bldr.CreateString("CameraManager::RPC_SetCamera");
WildRPC.RPCHeader.RPCHeaderStart(bldr)
WildRPC.RPCHeader.RPCHeaderAddMethodName(bldr, methodName)
gen_header = WildRPC.RPCHeader.RPCHeaderEnd(bldr)
bldr.FinishSizePrefixed(gen_header)

bldr2 = flatbuffers.Builder(0)
WildRPC.Camera.CameraStart(bldr2)
pos = WildRPC.Position.CreatePosition(bldr2, 32768, 32768, 1.0, 2.0, 3.0)
WildRPC.Camera.CameraAddPosition(bldr2, pos)
ornt = WildRPC.Quat.CreateQuat(bldr2, 1.0, 0.0, 0.0, 1.0)
WildRPC.Camera.CameraAddOrientation(bldr2, ornt)
gen_camera = WildRPC.Camera.CameraEnd(bldr2)
bldr2.Finish(gen_camera)

b1 = bldr.Bytes[bldr.Head():]
b2 = bldr2.Bytes[bldr2.Head():]

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b1 + b2)
    data = s.recv(1024)
    res = WildRPC.Result.Result.GetRootAsResult(data, 0)
    vl = res.Result()
    print(vl)

    time.sleep(5)

    s.sendall(b1 + b2)
    data = s.recv(1024)
    res = WildRPC.Result.Result.GetRootAsResult(data, 0)
    vl = res.Result()
    print(vl)
    s.close()