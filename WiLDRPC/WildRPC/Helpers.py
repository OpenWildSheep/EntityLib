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
import WildRPC.Vector3
import WildRPC.Vector2
import WildRPC.Integer
import WildRPC.Float
import WildRPC.Boolean	


Type_UInt3 = 1
Type_Vector3 = 2
Type_Vector2 = 3
Type_Quat = 4
Type_Position = 5
Type_Float = 6
Type_Integer = 7
Type_Boolean = 8

def BuildHeader(_RPCFunctionName):
	builder = flatbuffers.Builder(0)
	methodName = builder.CreateString(_RPCFunctionName);
	WildRPC.RPCHeader.RPCHeaderStart(builder)
	WildRPC.RPCHeader.RPCHeaderAddMethodName(builder, methodName)
	gen_header = WildRPC.RPCHeader.RPCHeaderEnd(builder)
	builder.FinishSizePrefixed(gen_header)
	result = builder.Bytes[builder.Head():]
	return result

def BuildHeaderWithParameters(_RPCFunctionName, parametersTypes, resultTypes):
	nbParameterTypes = len(parametersTypes)
	nbResultTypes = len(resultTypes)

	builder = flatbuffers.Builder(0)

	methodName = builder.CreateString(_RPCFunctionName)
	
	WildRPC.RPCHeader.RPCHeaderStartParameterTypesVector(builder, nbParameterTypes)
	for type in reversed(parametersTypes):
		builder.PrependByte(type)

	params = builder.EndVector(nbParameterTypes)

	WildRPC.RPCHeader.RPCHeaderStartResultTypesVector(builder, nbResultTypes)
	for type in reversed(resultTypes):
		builder.PrependByte(type)
	result = builder.EndVector(nbResultTypes)

	WildRPC.RPCHeader.RPCHeaderStart(builder)
	WildRPC.RPCHeader.RPCHeaderAddMethodName(builder, methodName)
	WildRPC.RPCHeader.RPCHeaderAddParameterTypes(builder, params)
	WildRPC.RPCHeader.RPCHeaderAddResultTypes(builder, result)
	gen_header = WildRPC.RPCHeader.RPCHeaderEnd(builder)

	builder.FinishSizePrefixed(gen_header)
	
	result = builder.Bytes[builder.Head():]
	return result

def DecodeByteArray(type, bytes):
	return 0



def BuildVector3(x, y, z):
	builder = flatbuffers.Builder(0)

	WildRPC.Vector3.Vector3Start(builder)
	WildRPC.Vector3.Vector3AddX(builder, x)
	WildRPC.Vector3.Vector3AddY(builder, y)
	WildRPC.Vector3.Vector3AddZ(builder, z)
	vector3 = WildRPC.Vector3.Vector3End(builder)
	builder.FinishSizePrefixed(vector3)
	
	result = builder.Bytes[builder.Head():]
	return result

def BuildInteger(i):
	builder = flatbuffers.Builder(0)

	WildRPC.Integer.IntegerStart(builder)
	WildRPC.Integer.IntegerAddValue(builder, i)
	integer = WildRPC.Integer.IntegerEnd(builder)

	builder.FinishSizePrefixed(integer)
	
	result = builder.Bytes[builder.Head():]
	return result

def BuildFloat(f):
	builder = flatbuffers.Builder(0)

	WildRPC.Float.FloatStart(builder)
	WildRPC.Float.FloatAddValue(builder, f)
	flt = WildRPC.Float.FloatEnd(builder)

	builder.FinishSizePrefixed(flt)
	
	result = builder.Bytes[builder.Head():]
	return result

# -----------------------

def bytes_to_int(bytes):
	result = 0
	index = 0
	for b in bytes:
		result = result + int(b) * (256 ** index)
		index = index + 1
	return result

def DecodeFloat(bytes):
	RPCfloat = WildRPC.Float.Float.GetRootAsFloat(bytes, 0)
	return RPCfloat.Value()
 
def DecodeInteger(bytes):
	RPCInteger = WildRPC.Integer.Integer.GetRootAsInteger(bytes, 0)
	return RPCInteger.Value()
 
def DecodeBool(bytes):
	RPCBoolean = WildRPC.Boolean.Boolean.GetRootAsBoolean(bytes, 0)
	return RPCBoolean.Value()
 
decoders = {
        Type_Float: DecodeFloat,
        Type_Integer: DecodeInteger,
        Type_Boolean: DecodeBool
    }
 
def Decode(type, bytes):
	dataView = memoryview(bytes)
	prefixedSize = bytes_to_int(dataView[0:3])
	#print("prefixedSize = ", prefixedSize)
	# Get the function from switcher dictionary
	func = decoders.get(type, "nothing")
	# Execute the function
	return func(dataView[4:]), prefixedSize