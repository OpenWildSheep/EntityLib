// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_VECTOR3_WILDRPC_H_
#define FLATBUFFERS_GENERATED_VECTOR3_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

namespace WildRPC {

struct Vector3;
struct Vector3Builder;
struct Vector3T;

struct Vector3T : public flatbuffers::NativeTable {
  typedef Vector3 TableType;
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
};

struct Vector3 FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef Vector3T NativeTableType;
  typedef Vector3Builder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_X = 4,
    VT_Y = 6,
    VT_Z = 8
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  bool mutate_x(float _x) {
    return SetField<float>(VT_X, _x, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  bool mutate_y(float _y) {
    return SetField<float>(VT_Y, _y, 0.0f);
  }
  float z() const {
    return GetField<float>(VT_Z, 0.0f);
  }
  bool mutate_z(float _z) {
    return SetField<float>(VT_Z, _z, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X) &&
           VerifyField<float>(verifier, VT_Y) &&
           VerifyField<float>(verifier, VT_Z) &&
           verifier.EndTable();
  }
  Vector3T *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(Vector3T *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Vector3> Pack(flatbuffers::FlatBufferBuilder &_fbb, const Vector3T* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct Vector3Builder {
  typedef Vector3 Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(Vector3::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(Vector3::VT_Y, y, 0.0f);
  }
  void add_z(float z) {
    fbb_.AddElement<float>(Vector3::VT_Z, z, 0.0f);
  }
  explicit Vector3Builder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Vector3> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Vector3>(end);
    return o;
  }
};

inline flatbuffers::Offset<Vector3> CreateVector3(
    flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f,
    float z = 0.0f) {
  Vector3Builder builder_(_fbb);
  builder_.add_z(z);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

flatbuffers::Offset<Vector3> CreateVector3(flatbuffers::FlatBufferBuilder &_fbb, const Vector3T *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline Vector3T *Vector3::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<Vector3T>(new Vector3T());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Vector3::UnPackTo(Vector3T *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = x(); _o->x = _e; }
  { auto _e = y(); _o->y = _e; }
  { auto _e = z(); _o->z = _e; }
}

inline flatbuffers::Offset<Vector3> Vector3::Pack(flatbuffers::FlatBufferBuilder &_fbb, const Vector3T* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateVector3(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Vector3> CreateVector3(flatbuffers::FlatBufferBuilder &_fbb, const Vector3T *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const Vector3T* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _x = _o->x;
  auto _y = _o->y;
  auto _z = _o->z;
  return WildRPC::CreateVector3(
      _fbb,
      _x,
      _y,
      _z);
}

inline const WildRPC::Vector3 *GetVector3(const void *buf) {
  return flatbuffers::GetRoot<WildRPC::Vector3>(buf);
}

inline const WildRPC::Vector3 *GetSizePrefixedVector3(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WildRPC::Vector3>(buf);
}

inline Vector3 *GetMutableVector3(void *buf) {
  return flatbuffers::GetMutableRoot<Vector3>(buf);
}

inline bool VerifyVector3Buffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WildRPC::Vector3>(nullptr);
}

inline bool VerifySizePrefixedVector3Buffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WildRPC::Vector3>(nullptr);
}

inline void FinishVector3Buffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::Vector3> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedVector3Buffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::Vector3> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WildRPC::Vector3T> UnPackVector3(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WildRPC::Vector3T>(GetVector3(buf)->UnPack(res));
}

inline std::unique_ptr<WildRPC::Vector3T> UnPackSizePrefixedVector3(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WildRPC::Vector3T>(GetSizePrefixedVector3(buf)->UnPack(res));
}

}  // namespace WildRPC

#endif  // FLATBUFFERS_GENERATED_VECTOR3_WILDRPC_H_
