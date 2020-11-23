// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_VECTOR2_WILDRPC_H_
#define FLATBUFFERS_GENERATED_VECTOR2_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

namespace WildRPC {

struct Vector2;
struct Vector2Builder;

struct Vector2 FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef Vector2Builder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_X = 4,
    VT_Y = 6
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X) &&
           VerifyField<float>(verifier, VT_Y) &&
           verifier.EndTable();
  }
};

struct Vector2Builder {
  typedef Vector2 Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(Vector2::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(Vector2::VT_Y, y, 0.0f);
  }
  explicit Vector2Builder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  Vector2Builder &operator=(const Vector2Builder &);
  flatbuffers::Offset<Vector2> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Vector2>(end);
    return o;
  }
};

inline flatbuffers::Offset<Vector2> CreateVector2(
    flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f) {
  Vector2Builder builder_(_fbb);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

inline const WildRPC::Vector2 *GetVector2(const void *buf) {
  return flatbuffers::GetRoot<WildRPC::Vector2>(buf);
}

inline const WildRPC::Vector2 *GetSizePrefixedVector2(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WildRPC::Vector2>(buf);
}

inline bool VerifyVector2Buffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WildRPC::Vector2>(nullptr);
}

inline bool VerifySizePrefixedVector2Buffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WildRPC::Vector2>(nullptr);
}

inline void FinishVector2Buffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::Vector2> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedVector2Buffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::Vector2> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace WildRPC

#endif  // FLATBUFFERS_GENERATED_VECTOR2_WILDRPC_H_