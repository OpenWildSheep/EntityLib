import socket
import struct
import time
import math
#import mathutils

import sys

# -----------------------------------------------
#
# HACK to emulate the "with socket(...) as s" syntax in Python 2
#
print(sys.version)
_python2 = sys.version_info.major == 2

if _python2:
	def socket__enter__(self): # type: (socket.socket) -> socket.socket
		return self

	def socket__exit__(self, *args): # type: (socket.socket, ...) -> None
		#if not self._closed: self.close()
		self.close()

	socket.socket.__enter__ = socket__enter__
	socket.socket.__exit__ = socket__exit__
# -----------------------------------------------

sys.path.append('..')
sys.path.append('../../../External/FlatBuffers/python')

import flatbuffers

import WildRPC.RPCHeader
import WildRPC.Vector3
import WildRPC.Vector2
import WildRPC.UInt3
import WildRPC.Integer
import WildRPC.Float
import WildRPC.Boolean
import WildRPC.Color
import WildRPC.Position
import WildRPC.Quat
import WildRPC.String

Type_Boolean = 0
Type_Integer = 1
Type_Float = 2
Type_Vector2 = 3
Type_UInt3 = 4
Type_Vector3 = 5
Type_Quat = 6
Type_Color = 7
Type_Position = 8
Type_String = 9

RPCProtocolErrors = [
	"No Error",
	"Maximum buffer size exceeded",
	"RPC Header is Missing",
	"Manager Class could not be Found",
	"Manager Method could not be Found",
	"Manager Method is not Valid",
	"Received Types do not match with Manager Method's types",
	"Send Buffer was too small for Result"
	]

# -----------------------------------------------


# -----------------------------------------------

def BuildHeader(_RPCFunctionName):
	builder = flatbuffers.Builder(0)
	methodName = builder.CreateString(_RPCFunctionName);
	WildRPC.RPCHeader.RPCHeaderStart(builder)
	WildRPC.RPCHeader.RPCHeaderAddMethodName(builder, methodName)
	gen_header = WildRPC.RPCHeader.RPCHeaderEnd(builder)
	builder.FinishSizePrefixed(gen_header)
	result = builder.Bytes[builder.Head():]
	return result

def BuildHeaderWithParameters(_managerName, _methodName, parametersTypes, resultTypes):

	nbParameterTypes = len(parametersTypes)
	nbResultTypes = len(resultTypes)

	builder = flatbuffers.Builder(0)

	managerName = builder.CreateString(_managerName)
	methodName = builder.CreateString(_methodName)
	
	WildRPC.RPCHeader.RPCHeaderStartParameterTypesVector(builder, nbParameterTypes)
	for type in reversed(parametersTypes):
		builder.PrependByte(type)

	params = builder.EndVector(nbParameterTypes)

	WildRPC.RPCHeader.RPCHeaderStartResultTypesVector(builder, nbResultTypes)
	for type in reversed(resultTypes):
		builder.PrependByte(type)
	result = builder.EndVector(nbResultTypes)

	WildRPC.RPCHeader.RPCHeaderStart(builder)
	WildRPC.RPCHeader.RPCHeaderAddManagerName(builder, managerName)
	WildRPC.RPCHeader.RPCHeaderAddMethodName(builder, methodName)
	WildRPC.RPCHeader.RPCHeaderAddParameterTypes(builder, params)
	WildRPC.RPCHeader.RPCHeaderAddResultTypes(builder, result)
	gen_header = WildRPC.RPCHeader.RPCHeaderEnd(builder)

	builder.FinishSizePrefixed(gen_header)
	
	result = builder.Bytes[builder.Head():]
	return result, parametersTypes, resultTypes

def DecodeByteArray(type, bytes):
	return 0

def BuildVector2(x, y):
	builder = flatbuffers.Builder(0)

	WildRPC.Vector2.Vector2Start(builder)
	WildRPC.Vector2.Vector2AddX(builder, x)
	WildRPC.Vector2.Vector2AddY(builder, y)
	vector2 = WildRPC.Vector2.Vector2End(builder)
	builder.FinishSizePrefixed(vector2)
	
	result = builder.Bytes[builder.Head():]
	return result

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

def BuildUInt3(x, y, z):
	builder = flatbuffers.Builder(0)

	WildRPC.UInt3.UInt3Start(builder)
	WildRPC.UInt3.UInt3AddX(builder, x)
	WildRPC.UInt3.UInt3AddY(builder, y)
	WildRPC.UInt3.UInt3AddZ(builder, z)
	uint3 = WildRPC.UInt3.UInt3End(builder)
	builder.FinishSizePrefixed(uint3)
	
	result = builder.Bytes[builder.Head():]
	return result

def BuildBoolean(b):
	builder = flatbuffers.Builder(0)

	WildRPC.Boolean.BooleanStart(builder)
	WildRPC.Boolean.BooleanAddValue(builder, b)
	boolean = WildRPC.Boolean.BooleanEnd(builder)

	builder.FinishSizePrefixed(boolean)
	
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

def BuildPosition(wcx, wcy, x, y, z):
	builder = flatbuffers.Builder(0)

	WildRPC.Vector3.Vector3Start(builder)
	WildRPC.Vector3.Vector3AddX(builder, x)
	WildRPC.Vector3.Vector3AddY(builder, y)
	WildRPC.Vector3.Vector3AddZ(builder, z)
	lps = WildRPC.Vector3.Vector3End(builder)

	WildRPC.Position.PositionStart(builder)
	WildRPC.Position.PositionAddWorldCellX(builder, wcx)
	WildRPC.Position.PositionAddWorldCellY(builder, wcy)
	WildRPC.Position.PositionAddLocalPosition(builder, lps)
	flt = WildRPC.Position.PositionEnd(builder)

	builder.FinishSizePrefixed(flt)
	
	result = builder.Bytes[builder.Head():]
	return result

def BuildColor(r, g, b, a):
	builder = flatbuffers.Builder(0)

	WildRPC.Color.ColorStart(builder)
	WildRPC.Color.ColorAddR(builder, r)
	WildRPC.Color.ColorAddG(builder, g)
	WildRPC.Color.ColorAddB(builder, b)
	WildRPC.Color.ColorAddA(builder, a)
	color = WildRPC.Color.ColorEnd(builder)

	builder.FinishSizePrefixed(color)
	
	result = builder.Bytes[builder.Head():]
	return result

def BuildQuat(x, y, z, w):
	builder = flatbuffers.Builder(0)

	WildRPC.Quat.QuatStart(builder)
	WildRPC.Quat.QuatAddX(builder, x)
	WildRPC.Quat.QuatAddY(builder, y)
	WildRPC.Quat.QuatAddZ(builder, z)
	WildRPC.Quat.QuatAddW(builder, w)
	quat = WildRPC.Quat.QuatEnd(builder)

	builder.FinishSizePrefixed(quat)
	
	result = builder.Bytes[builder.Head():]
	return result

def BuildString(s):
	builder = flatbuffers.Builder(0)
	s = builder.CreateString(s)
	WildRPC.String.StringStart(builder)
	WildRPC.String.StringAddValue(builder, s)
	end = WildRPC.String.StringEnd(builder)
	builder.FinishSizePrefixed(end)
	return builder.Bytes[builder.Head():]

# -----------------------

def int_from_bytes(byte4):  # type: (memoryview[4]) -> int
	import struct
	return struct.unpack("<i", byte4)[0]  # <i = little-endian, signed
	#return int(codecs.encode(byte4, 'hex'), 16) # big-endian, unsigned :(
	#return int.from_bytes(byte4, byteorder="little", signed=True) # Python3-only

def DecodeFloat(bytes):
	RPCfloat = WildRPC.Float.Float.GetRootAsFloat(bytes, 0)
	return RPCfloat.Value()
 
def DecodeInteger(bytes):
	RPCInteger = WildRPC.Integer.Integer.GetRootAsInteger(bytes, 0)
	return RPCInteger.Value()
 
def DecodeBool(bytes):
	RPCBoolean = WildRPC.Boolean.Boolean.GetRootAsBoolean(bytes, 0)
	return RPCBoolean.Value()

def DecodePosition(bytes):
	RPCPosition = WildRPC.Position.Position.GetRootAsPosition(bytes, 0)
	localPos = RPCPosition.LocalPosition();
	result = [RPCPosition.WorldCellX(), RPCPosition.WorldCellY(), localPos.X(), localPos.Y(), localPos.Z()]
	return result
 
def DecodeQuat(bytes):
	RPCQuat = WildRPC.Quat.Quat.GetRootAsQuat(bytes, 0)
	result = [RPCQuat.X(), RPCQuat.Y(), RPCQuat.Z(), RPCQuat.W()]
	return result
 
def DecodeColor(bytes):
	RPCColor = WildRPC.Color.Color.GetRootAsColor(bytes, 0)
	result = [RPCColor.R(), RPCColor.G(), RPCColor.B(), RPCColor.A()]
	return result

def DecodeVector3(bytes):
	RPCVector3 = WildRPC.Vector3.Vector3.GetRootAsVector3(bytes, 0)
	result = [RPCVector3.X(), RPCVector3.Y(), RPCVector3.Z()]
	return result
 
def DecodeVector2(bytes):
	RPCVector2 = WildRPC.Vector2.Vector2.GetRootAsVector2(bytes, 0)
	result = [RPCVector2.X(), RPCVector2.Y()]
	return result
 
def DecodeUInt3(bytes):
	RPCUInt3 = WildRPC.UInt3.UInt3.GetRootAsUInt3(bytes, 0)
	result = [RPCUInt3.X(), RPCUInt3.Y(), RPCUInt3.Z()]
	return result
 
def DecodeString(bytes):
	RPCString = WildRPC.String.String.GetRootAsString(bytes, 0)
	return RPCString.Value()
 
decoders = {
        Type_Float: DecodeFloat,
        Type_Integer: DecodeInteger,
        Type_Boolean: DecodeBool,
        Type_Position: DecodePosition,
        Type_Quat: DecodeQuat,
        Type_Color: DecodeColor,
        Type_Vector3: DecodeVector3,
        Type_Vector2: DecodeVector2,
        Type_UInt3: DecodeUInt3,
        Type_String: DecodeString,
    }
 
def Decode(type, bytes):
	dataView = memoryview(bytes)
	prefixedSize = int_from_bytes(dataView[0:4])
	#print("prefixedSize = ", prefixedSize)
	# Get the function from switcher dictionary
	func = decoders.get(type, "nothing")
	# Execute the function
	return func(dataView[4:]), prefixedSize

# -------------------

def BuildParamPosition(params):
	return BuildPosition(params[0], params[1], params[2], params[3], params[4])

def BuildParamQuat(params):
	return BuildQuat(params[0], params[1], params[2], params[3])

def BuildParamColor(params):
	return BuildColor(params[0], params[1], params[2], params[3])

def BuildParamFloat(params):
	return BuildFloat(params)

def BuildParamInteger(params):
	return BuildInteger(params)

def BuildParamBoolean(params):
	return BuildBoolean(params)

def BuildParamVector3(params):
	return BuildVector3(params[0], params[1], params[2])

def BuildParamVector2(params):
	return BuildVector2(params[0], params[1])

def BuildParamUInt3(params):
	return BuildUInt3(params[0], params[1], params[2])	

parameterBuilders = {
	    Type_Float: BuildParamFloat,
        Type_Integer: BuildParamInteger,
        Type_Boolean: BuildParamBoolean,
        Type_Position: BuildParamPosition,
        Type_Quat: BuildParamQuat,
        Type_Color: BuildParamColor,
        Type_Vector3: BuildParamVector3,
        Type_Vector2: BuildParamVector2,
        Type_UInt3: BuildParamUInt3,
        Type_String: BuildString,
}

def BuildParam(type, params):
	func = parameterBuilders.get(type, "nothing")
	return func(params)

class RPCMethod:

	managerName = ""
	methodName = ""
	parameterTypes = []
	resultTypes = []

	def __init__(self, socket, managerName, methodName, parameterTypes, resultTypes):
		self.socket = socket
		self.managerName = managerName
		self.methodName = methodName
		self.parameterTypes = parameterTypes
		self.resultTypes = resultTypes

	def Invoke(self, params, results):
		idx = 0
		header = BuildHeaderWithParameters(self.managerName, self.methodName, self.parameterTypes, self.resultTypes)
		outByteStream = header[0]
		for prm in params:
			paramType = self.parameterTypes[idx]
			bts = BuildParam(paramType, prm)
			outByteStream += bts
			idx += 1

		self.socket.sendall(outByteStream)

		data = self.socket.recv(4096)

		errors = bytearray(data[:2]) if _python2 else data
		protocolError = errors[0]
		applicationError = errors[1]

		if protocolError != 0:
			print("Protocol ERROR: ", RPCProtocolErrors[protocolError])
		else:
			if applicationError != 0:
				print("Application Error", applicationError)

			dataView = memoryview(data)
			dataViewReadIndex = 2
			for resultType in self.resultTypes:
				result = Decode(resultType, dataView[dataViewReadIndex:])
				dataViewReadIndex = dataViewReadIndex + result[1] + 4

				results.append(result[0])

		return protocolError, applicationError