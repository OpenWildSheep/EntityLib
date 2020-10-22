import socket
import struct
import time
import math
import mathutils

import sys
sys.path.append('..')
sys.path.append('../../../External/FlatBuffers/python')

import flatbuffers

import WildRPC.RPCHeader

def BuildHeader(_RPCFunctionName):
	builder = flatbuffers.Builder(0)
	methodName = builder.CreateString(_RPCFunctionName);
	WildRPC.RPCHeader.RPCHeaderStart(builder)
	WildRPC.RPCHeader.RPCHeaderAddMethodName(builder, methodName)
	gen_header = WildRPC.RPCHeader.RPCHeaderEnd(builder)
	builder.FinishSizePrefixed(gen_header)
	result = builder.Bytes[builder.Head():]
	return result