// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_RPCHEADER_WILDRPC_H_
#define FLATBUFFERS_GENERATED_RPCHEADER_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

#include "Result_generated.h"
#include "WildRPC_generated.h"

namespace WildRPC {

struct RPCHeader;
struct RPCHeaderBuilder;

struct RPCHeader FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef RPCHeaderBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_METHODNAME = 4
  };
  const flatbuffers::String *methodName() const {
    return GetPointer<const flatbuffers::String *>(VT_METHODNAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_METHODNAME) &&
           verifier.VerifyString(methodName()) &&
           verifier.EndTable();
  }
};

struct RPCHeaderBuilder {
  typedef RPCHeader Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_methodName(flatbuffers::Offset<flatbuffers::String> methodName) {
    fbb_.AddOffset(RPCHeader::VT_METHODNAME, methodName);
  }
  explicit RPCHeaderBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  RPCHeaderBuilder &operator=(const RPCHeaderBuilder &);
  flatbuffers::Offset<RPCHeader> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RPCHeader>(end);
    return o;
  }
};

inline flatbuffers::Offset<RPCHeader> CreateRPCHeader(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> methodName = 0) {
  RPCHeaderBuilder builder_(_fbb);
  builder_.add_methodName(methodName);
  return builder_.Finish();
}

inline flatbuffers::Offset<RPCHeader> CreateRPCHeaderDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *methodName = nullptr) {
  auto methodName__ = methodName ? _fbb.CreateString(methodName) : 0;
  return WildRPC::CreateRPCHeader(
      _fbb,
      methodName__);
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
