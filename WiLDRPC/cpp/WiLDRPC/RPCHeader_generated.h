// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_RPCHEADER_WILDRPC_H_
#define FLATBUFFERS_GENERATED_RPCHEADER_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

namespace WildRPC {

struct RPCHeader;
struct RPCHeaderBuilder;
struct RPCHeaderT;

enum ElementType : uint8_t {
  ElementType_Boolean = 0,
  ElementType_Integer = 1,
  ElementType_Float = 2,
  ElementType_Vector2 = 3,
  ElementType_UInt3 = 4,
  ElementType_Vector3 = 5,
  ElementType_Quat = 6,
  ElementType_Color = 7,
  ElementType_Position = 8,
  ElementType_String = 9,
  ElementType_MIN = ElementType_Boolean,
  ElementType_MAX = ElementType_String
};

inline const ElementType (&EnumValuesElementType())[10] {
  static const ElementType values[] = {
    ElementType_Boolean,
    ElementType_Integer,
    ElementType_Float,
    ElementType_Vector2,
    ElementType_UInt3,
    ElementType_Vector3,
    ElementType_Quat,
    ElementType_Color,
    ElementType_Position,
    ElementType_String
  };
  return values;
}

inline const char * const *EnumNamesElementType() {
  static const char * const names[11] = {
    "Boolean",
    "Integer",
    "Float",
    "Vector2",
    "UInt3",
    "Vector3",
    "Quat",
    "Color",
    "Position",
    "String",
    nullptr
  };
  return names;
}

inline const char *EnumNameElementType(ElementType e) {
  if (flatbuffers::IsOutRange(e, ElementType_Boolean, ElementType_String)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesElementType()[index];
}

enum TypeInfo : uint16_t {
  TypeInfo_Array = 1,
  TypeInfo_Boolean = 2,
  TypeInfo_Integer = 4,
  TypeInfo_Float = 8,
  TypeInfo_Vector2 = 16,
  TypeInfo_UInt3 = 32,
  TypeInfo_Vector3 = 64,
  TypeInfo_Quat = 128,
  TypeInfo_Color = 256,
  TypeInfo_Position = 512,
  TypeInfo_String = 1024,
  TypeInfo_NONE = 0,
  TypeInfo_ANY = 2047
};

inline const TypeInfo (&EnumValuesTypeInfo())[11] {
  static const TypeInfo values[] = {
    TypeInfo_Array,
    TypeInfo_Boolean,
    TypeInfo_Integer,
    TypeInfo_Float,
    TypeInfo_Vector2,
    TypeInfo_UInt3,
    TypeInfo_Vector3,
    TypeInfo_Quat,
    TypeInfo_Color,
    TypeInfo_Position,
    TypeInfo_String
  };
  return values;
}

inline const char *EnumNameTypeInfo(TypeInfo e) {
  switch (e) {
    case TypeInfo_Array: return "Array";
    case TypeInfo_Boolean: return "Boolean";
    case TypeInfo_Integer: return "Integer";
    case TypeInfo_Float: return "Float";
    case TypeInfo_Vector2: return "Vector2";
    case TypeInfo_UInt3: return "UInt3";
    case TypeInfo_Vector3: return "Vector3";
    case TypeInfo_Quat: return "Quat";
    case TypeInfo_Color: return "Color";
    case TypeInfo_Position: return "Position";
    case TypeInfo_String: return "String";
    default: return "";
  }
}

struct RPCHeaderT : public flatbuffers::NativeTable {
  typedef RPCHeader TableType;
  std::string managerName{};
  std::string methodName{};
  std::vector<WildRPC::TypeInfo> parameterTypes{};
  std::vector<WildRPC::TypeInfo> resultTypes{};
};

struct RPCHeader FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef RPCHeaderT NativeTableType;
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
  flatbuffers::String *mutable_managerName() {
    return GetPointer<flatbuffers::String *>(VT_MANAGERNAME);
  }
  const flatbuffers::String *methodName() const {
    return GetPointer<const flatbuffers::String *>(VT_METHODNAME);
  }
  flatbuffers::String *mutable_methodName() {
    return GetPointer<flatbuffers::String *>(VT_METHODNAME);
  }
  const flatbuffers::Vector<uint16_t> *parameterTypes() const {
    return GetPointer<const flatbuffers::Vector<uint16_t> *>(VT_PARAMETERTYPES);
  }
  flatbuffers::Vector<uint16_t> *mutable_parameterTypes() {
    return GetPointer<flatbuffers::Vector<uint16_t> *>(VT_PARAMETERTYPES);
  }
  const flatbuffers::Vector<uint16_t> *resultTypes() const {
    return GetPointer<const flatbuffers::Vector<uint16_t> *>(VT_RESULTTYPES);
  }
  flatbuffers::Vector<uint16_t> *mutable_resultTypes() {
    return GetPointer<flatbuffers::Vector<uint16_t> *>(VT_RESULTTYPES);
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
  RPCHeaderT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(RPCHeaderT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<RPCHeader> Pack(flatbuffers::FlatBufferBuilder &_fbb, const RPCHeaderT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
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
  void add_parameterTypes(flatbuffers::Offset<flatbuffers::Vector<uint16_t>> parameterTypes) {
    fbb_.AddOffset(RPCHeader::VT_PARAMETERTYPES, parameterTypes);
  }
  void add_resultTypes(flatbuffers::Offset<flatbuffers::Vector<uint16_t>> resultTypes) {
    fbb_.AddOffset(RPCHeader::VT_RESULTTYPES, resultTypes);
  }
  explicit RPCHeaderBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
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
    flatbuffers::Offset<flatbuffers::Vector<uint16_t>> parameterTypes = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint16_t>> resultTypes = 0) {
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
    const std::vector<uint16_t> *parameterTypes = nullptr,
    const std::vector<uint16_t> *resultTypes = nullptr) {
  auto managerName__ = managerName ? _fbb.CreateString(managerName) : 0;
  auto methodName__ = methodName ? _fbb.CreateString(methodName) : 0;
  auto parameterTypes__ = parameterTypes ? _fbb.CreateVector<uint16_t>(*parameterTypes) : 0;
  auto resultTypes__ = resultTypes ? _fbb.CreateVector<uint16_t>(*resultTypes) : 0;
  return WildRPC::CreateRPCHeader(
      _fbb,
      managerName__,
      methodName__,
      parameterTypes__,
      resultTypes__);
}

flatbuffers::Offset<RPCHeader> CreateRPCHeader(flatbuffers::FlatBufferBuilder &_fbb, const RPCHeaderT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline RPCHeaderT *RPCHeader::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<RPCHeaderT>(new RPCHeaderT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void RPCHeader::UnPackTo(RPCHeaderT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = managerName(); if (_e) _o->managerName = _e->str(); }
  { auto _e = methodName(); if (_e) _o->methodName = _e->str(); }
  { auto _e = parameterTypes(); if (_e) { _o->parameterTypes.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->parameterTypes[_i] = static_cast<WildRPC::TypeInfo>(_e->Get(_i)); } } }
  { auto _e = resultTypes(); if (_e) { _o->resultTypes.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->resultTypes[_i] = static_cast<WildRPC::TypeInfo>(_e->Get(_i)); } } }
}

inline flatbuffers::Offset<RPCHeader> RPCHeader::Pack(flatbuffers::FlatBufferBuilder &_fbb, const RPCHeaderT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateRPCHeader(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<RPCHeader> CreateRPCHeader(flatbuffers::FlatBufferBuilder &_fbb, const RPCHeaderT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const RPCHeaderT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _managerName = _fbb.CreateString(_o->managerName);
  auto _methodName = _fbb.CreateString(_o->methodName);
  auto _parameterTypes = _fbb.CreateVectorScalarCast<uint16_t>(flatbuffers::data(_o->parameterTypes), _o->parameterTypes.size());
  auto _resultTypes = _fbb.CreateVectorScalarCast<uint16_t>(flatbuffers::data(_o->resultTypes), _o->resultTypes.size());
  return WildRPC::CreateRPCHeader(
      _fbb,
      _managerName,
      _methodName,
      _parameterTypes,
      _resultTypes);
}

inline const WildRPC::RPCHeader *GetRPCHeader(const void *buf) {
  return flatbuffers::GetRoot<WildRPC::RPCHeader>(buf);
}

inline const WildRPC::RPCHeader *GetSizePrefixedRPCHeader(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WildRPC::RPCHeader>(buf);
}

inline RPCHeader *GetMutableRPCHeader(void *buf) {
  return flatbuffers::GetMutableRoot<RPCHeader>(buf);
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

inline std::unique_ptr<WildRPC::RPCHeaderT> UnPackRPCHeader(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WildRPC::RPCHeaderT>(GetRPCHeader(buf)->UnPack(res));
}

inline std::unique_ptr<WildRPC::RPCHeaderT> UnPackSizePrefixedRPCHeader(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WildRPC::RPCHeaderT>(GetSizePrefixedRPCHeader(buf)->UnPack(res));
}

}  // namespace WildRPC

#endif  // FLATBUFFERS_GENERATED_RPCHEADER_WILDRPC_H_
