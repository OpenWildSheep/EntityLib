// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_RPCHEADER_WILDRPC_H_
#define FLATBUFFERS_GENERATED_RPCHEADER_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

#include "Result_generated.h"

namespace WildRPC {

struct RPCHeader;
struct RPCHeaderBuilder;

enum Type {
  Type_Boolean = 0,
  Type_Integer = 1,
  Type_Float = 2,
  Type_Vector2 = 3,
  Type_UInt3 = 4,
  Type_Vector3 = 5,
  Type_Quat = 6,
  Type_Color = 7,
  Type_Position = 8,
  Type_MIN = Type_Boolean,
  Type_MAX = Type_Position
};

inline const Type (&EnumValuesType())[9] {
  static const Type values[] = {
    Type_Boolean,
    Type_Integer,
    Type_Float,
    Type_Vector2,
    Type_UInt3,
    Type_Vector3,
    Type_Quat,
    Type_Color,
    Type_Position
  };
  return values;
}

inline const char * const *EnumNamesType() {
  static const char * const names[10] = {
    "Boolean",
    "Integer",
    "Float",
    "Vector2",
    "UInt3",
    "Vector3",
    "Quat",
    "Color",
    "Position",
    nullptr
  };
  return names;
}

inline const char *EnumNameType(Type e) {
  if (flatbuffers::IsOutRange(e, Type_Boolean, Type_Position)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesType()[index];
}

struct RPCHeader FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef RPCHeaderBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MANAGERNAME = 4,
    VT_METHODNAME = 6,
    VT_PARAMETERTYPES = 8,
    VT_RESULTTYPES = 10
  };
  const flatbuffers::String *managerName() const {
    return GetPointer<const flatbuffers::String *>(VT_MANAGERNAME);
  }
  const flatbuffers::String *methodName() const {
    return GetPointer<const flatbuffers::String *>(VT_METHODNAME);
  }
  const flatbuffers::Vector<int8_t> *parameterTypes() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_PARAMETERTYPES);
  }
  const flatbuffers::Vector<int8_t> *resultTypes() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_RESULTTYPES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_MANAGERNAME) &&
           verifier.VerifyString(managerName()) &&
           VerifyOffsetRequired(verifier, VT_METHODNAME) &&
           verifier.VerifyString(methodName()) &&
           VerifyOffsetRequired(verifier, VT_PARAMETERTYPES) &&
           verifier.VerifyVector(parameterTypes()) &&
           VerifyOffsetRequired(verifier, VT_RESULTTYPES) &&
           verifier.VerifyVector(resultTypes()) &&
           verifier.EndTable();
  }
};

struct RPCHeaderBuilder {
  typedef RPCHeader Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_managerName(flatbuffers::Offset<flatbuffers::String> managerName) {
    fbb_.AddOffset(RPCHeader::VT_MANAGERNAME, managerName);
  }
  void add_methodName(flatbuffers::Offset<flatbuffers::String> methodName) {
    fbb_.AddOffset(RPCHeader::VT_METHODNAME, methodName);
  }
  void add_parameterTypes(flatbuffers::Offset<flatbuffers::Vector<int8_t>> parameterTypes) {
    fbb_.AddOffset(RPCHeader::VT_PARAMETERTYPES, parameterTypes);
  }
  void add_resultTypes(flatbuffers::Offset<flatbuffers::Vector<int8_t>> resultTypes) {
    fbb_.AddOffset(RPCHeader::VT_RESULTTYPES, resultTypes);
  }
  explicit RPCHeaderBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  RPCHeaderBuilder &operator=(const RPCHeaderBuilder &);
  flatbuffers::Offset<RPCHeader> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RPCHeader>(end);
    fbb_.Required(o, RPCHeader::VT_MANAGERNAME);
    fbb_.Required(o, RPCHeader::VT_METHODNAME);
    fbb_.Required(o, RPCHeader::VT_PARAMETERTYPES);
    fbb_.Required(o, RPCHeader::VT_RESULTTYPES);
    return o;
  }
};

inline flatbuffers::Offset<RPCHeader> CreateRPCHeader(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> managerName = 0,
    flatbuffers::Offset<flatbuffers::String> methodName = 0,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> parameterTypes = 0,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> resultTypes = 0) {
  RPCHeaderBuilder builder_(_fbb);
  builder_.add_resultTypes(resultTypes);
  builder_.add_parameterTypes(parameterTypes);
  builder_.add_methodName(methodName);
  builder_.add_managerName(managerName);
  return builder_.Finish();
}

inline flatbuffers::Offset<RPCHeader> CreateRPCHeaderDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *managerName = nullptr,
    const char *methodName = nullptr,
    const std::vector<int8_t> *parameterTypes = nullptr,
    const std::vector<int8_t> *resultTypes = nullptr) {
  auto managerName__ = managerName ? _fbb.CreateString(managerName) : 0;
  auto methodName__ = methodName ? _fbb.CreateString(methodName) : 0;
  auto parameterTypes__ = parameterTypes ? _fbb.CreateVector<int8_t>(*parameterTypes) : 0;
  auto resultTypes__ = resultTypes ? _fbb.CreateVector<int8_t>(*resultTypes) : 0;
  return WildRPC::CreateRPCHeader(
      _fbb,
      managerName__,
      methodName__,
      parameterTypes__,
      resultTypes__);
}

inline const WildRPC::RPCHeader *GetRPCHeader(const void *buf) {
  return flatbuffers::GetRoot<WildRPC::RPCHeader>(buf);
}

inline const WildRPC::RPCHeader *GetSizePrefixedRPCHeader(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WildRPC::RPCHeader>(buf);
}

inline bool VerifyRPCHeaderBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WildRPC::RPCHeader>(nullptr);
}

inline bool VerifySizePrefixedRPCHeaderBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WildRPC::RPCHeader>(nullptr);
}

inline void FinishRPCHeaderBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::RPCHeader> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedRPCHeaderBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::RPCHeader> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace WildRPC

#endif  // FLATBUFFERS_GENERATED_RPCHEADER_WILDRPC_H_
