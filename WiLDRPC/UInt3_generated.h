// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_UINT3_WILDRPC_H_
#define FLATBUFFERS_GENERATED_UINT3_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

namespace WildRPC {

struct UInt3;
struct UInt3Builder;

struct UInt3 FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UInt3Builder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_X = 4,
    VT_Y = 6,
    VT_Z = 8
  };
  uint32_t x() const {
    return GetField<uint32_t>(VT_X, 0);
  }
  uint32_t y() const {
    return GetField<uint32_t>(VT_Y, 0);
  }
  uint32_t z() const {
    return GetField<uint32_t>(VT_Z, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_X) &&
           VerifyField<uint32_t>(verifier, VT_Y) &&
           VerifyField<uint32_t>(verifier, VT_Z) &&
           verifier.EndTable();
  }
};

struct UInt3Builder {
  typedef UInt3 Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(uint32_t x) {
    fbb_.AddElement<uint32_t>(UInt3::VT_X, x, 0);
  }
  void add_y(uint32_t y) {
    fbb_.AddElement<uint32_t>(UInt3::VT_Y, y, 0);
  }
  void add_z(uint32_t z) {
    fbb_.AddElement<uint32_t>(UInt3::VT_Z, z, 0);
  }
  explicit UInt3Builder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UInt3Builder &operator=(const UInt3Builder &);
  flatbuffers::Offset<UInt3> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UInt3>(end);
    return o;
  }
};

inline flatbuffers::Offset<UInt3> CreateUInt3(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t x = 0,
    uint32_t y = 0,
    uint32_t z = 0) {
  UInt3Builder builder_(_fbb);
  builder_.add_z(z);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

inline const WildRPC::UInt3 *GetUInt3(const void *buf) {
  return flatbuffers::GetRoot<WildRPC::UInt3>(buf);
}

inline const WildRPC::UInt3 *GetSizePrefixedUInt3(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WildRPC::UInt3>(buf);
}

inline bool VerifyUInt3Buffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WildRPC::UInt3>(nullptr);
}

inline bool VerifySizePrefixedUInt3Buffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WildRPC::UInt3>(nullptr);
}

inline void FinishUInt3Buffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::UInt3> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedUInt3Buffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::UInt3> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace WildRPC

#endif  // FLATBUFFERS_GENERATED_UINT3_WILDRPC_H_
