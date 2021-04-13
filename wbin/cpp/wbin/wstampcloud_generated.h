// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WSTAMPCLOUD_WBIN_H_
#define FLATBUFFERS_GENERATED_WSTAMPCLOUD_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct Stamp;
struct StampBuilder;
struct StampT;

struct StampCloud;
struct StampCloudBuilder;
struct StampCloudT;

struct StampT : public flatbuffers::NativeTable {
  typedef Stamp TableType;
  std::unique_ptr<WBIN::AABB> shape{};
  std::unique_ptr<WBIN::Matrix44> matrix{};
  std::vector<int32_t> tags{};
};

struct Stamp FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef StampT NativeTableType;
  typedef StampBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SHAPE = 4,
    VT_MATRIX = 6,
    VT_TAGS = 8
  };
  const WBIN::AABB *shape() const {
    return GetStruct<const WBIN::AABB *>(VT_SHAPE);
  }
  WBIN::AABB *mutable_shape() {
    return GetStruct<WBIN::AABB *>(VT_SHAPE);
  }
  const WBIN::Matrix44 *matrix() const {
    return GetStruct<const WBIN::Matrix44 *>(VT_MATRIX);
  }
  WBIN::Matrix44 *mutable_matrix() {
    return GetStruct<WBIN::Matrix44 *>(VT_MATRIX);
  }
  const flatbuffers::Vector<int32_t> *tags() const {
    return GetPointer<const flatbuffers::Vector<int32_t> *>(VT_TAGS);
  }
  flatbuffers::Vector<int32_t> *mutable_tags() {
    return GetPointer<flatbuffers::Vector<int32_t> *>(VT_TAGS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<WBIN::AABB>(verifier, VT_SHAPE) &&
           VerifyField<WBIN::Matrix44>(verifier, VT_MATRIX) &&
           VerifyOffset(verifier, VT_TAGS) &&
           verifier.VerifyVector(tags()) &&
           verifier.EndTable();
  }
  StampT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(StampT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Stamp> Pack(flatbuffers::FlatBufferBuilder &_fbb, const StampT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct StampBuilder {
  typedef Stamp Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_shape(const WBIN::AABB *shape) {
    fbb_.AddStruct(Stamp::VT_SHAPE, shape);
  }
  void add_matrix(const WBIN::Matrix44 *matrix) {
    fbb_.AddStruct(Stamp::VT_MATRIX, matrix);
  }
  void add_tags(flatbuffers::Offset<flatbuffers::Vector<int32_t>> tags) {
    fbb_.AddOffset(Stamp::VT_TAGS, tags);
  }
  explicit StampBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Stamp> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Stamp>(end);
    return o;
  }
};

inline flatbuffers::Offset<Stamp> CreateStamp(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::AABB *shape = 0,
    const WBIN::Matrix44 *matrix = 0,
    flatbuffers::Offset<flatbuffers::Vector<int32_t>> tags = 0) {
  StampBuilder builder_(_fbb);
  builder_.add_tags(tags);
  builder_.add_matrix(matrix);
  builder_.add_shape(shape);
  return builder_.Finish();
}

inline flatbuffers::Offset<Stamp> CreateStampDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::AABB *shape = 0,
    const WBIN::Matrix44 *matrix = 0,
    const std::vector<int32_t> *tags = nullptr) {
  auto tags__ = tags ? _fbb.CreateVector<int32_t>(*tags) : 0;
  return WBIN::CreateStamp(
      _fbb,
      shape,
      matrix,
      tags__);
}

flatbuffers::Offset<Stamp> CreateStamp(flatbuffers::FlatBufferBuilder &_fbb, const StampT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct StampCloudT : public flatbuffers::NativeTable {
  typedef StampCloud TableType;
  std::vector<std::unique_ptr<WBIN::StampT>> stamps{};
  std::unique_ptr<WBIN::AABB> boundingBox{};
};

struct StampCloud FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef StampCloudT NativeTableType;
  typedef StampCloudBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_STAMPS = 4,
    VT_BOUNDINGBOX = 6
  };
  const flatbuffers::Vector<flatbuffers::Offset<WBIN::Stamp>> *stamps() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<WBIN::Stamp>> *>(VT_STAMPS);
  }
  flatbuffers::Vector<flatbuffers::Offset<WBIN::Stamp>> *mutable_stamps() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<WBIN::Stamp>> *>(VT_STAMPS);
  }
  const WBIN::AABB *boundingBox() const {
    return GetStruct<const WBIN::AABB *>(VT_BOUNDINGBOX);
  }
  WBIN::AABB *mutable_boundingBox() {
    return GetStruct<WBIN::AABB *>(VT_BOUNDINGBOX);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_STAMPS) &&
           verifier.VerifyVector(stamps()) &&
           verifier.VerifyVectorOfTables(stamps()) &&
           VerifyField<WBIN::AABB>(verifier, VT_BOUNDINGBOX) &&
           verifier.EndTable();
  }
  StampCloudT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(StampCloudT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<StampCloud> Pack(flatbuffers::FlatBufferBuilder &_fbb, const StampCloudT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct StampCloudBuilder {
  typedef StampCloud Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_stamps(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::Stamp>>> stamps) {
    fbb_.AddOffset(StampCloud::VT_STAMPS, stamps);
  }
  void add_boundingBox(const WBIN::AABB *boundingBox) {
    fbb_.AddStruct(StampCloud::VT_BOUNDINGBOX, boundingBox);
  }
  explicit StampCloudBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<StampCloud> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<StampCloud>(end);
    return o;
  }
};

inline flatbuffers::Offset<StampCloud> CreateStampCloud(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::Stamp>>> stamps = 0,
    const WBIN::AABB *boundingBox = 0) {
  StampCloudBuilder builder_(_fbb);
  builder_.add_boundingBox(boundingBox);
  builder_.add_stamps(stamps);
  return builder_.Finish();
}

inline flatbuffers::Offset<StampCloud> CreateStampCloudDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<WBIN::Stamp>> *stamps = nullptr,
    const WBIN::AABB *boundingBox = 0) {
  auto stamps__ = stamps ? _fbb.CreateVector<flatbuffers::Offset<WBIN::Stamp>>(*stamps) : 0;
  return WBIN::CreateStampCloud(
      _fbb,
      stamps__,
      boundingBox);
}

flatbuffers::Offset<StampCloud> CreateStampCloud(flatbuffers::FlatBufferBuilder &_fbb, const StampCloudT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline StampT *Stamp::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<StampT>(new StampT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Stamp::UnPackTo(StampT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = shape(); if (_e) _o->shape = std::unique_ptr<WBIN::AABB>(new WBIN::AABB(*_e)); }
  { auto _e = matrix(); if (_e) _o->matrix = std::unique_ptr<WBIN::Matrix44>(new WBIN::Matrix44(*_e)); }
  { auto _e = tags(); if (_e) { _o->tags.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->tags[_i] = _e->Get(_i); } } }
}

inline flatbuffers::Offset<Stamp> Stamp::Pack(flatbuffers::FlatBufferBuilder &_fbb, const StampT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateStamp(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Stamp> CreateStamp(flatbuffers::FlatBufferBuilder &_fbb, const StampT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const StampT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _shape = _o->shape ? _o->shape.get() : 0;
  auto _matrix = _o->matrix ? _o->matrix.get() : 0;
  auto _tags = _o->tags.size() ? _fbb.CreateVector(_o->tags) : 0;
  return WBIN::CreateStamp(
      _fbb,
      _shape,
      _matrix,
      _tags);
}

inline StampCloudT *StampCloud::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<StampCloudT>(new StampCloudT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void StampCloud::UnPackTo(StampCloudT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = stamps(); if (_e) { _o->stamps.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->stamps[_i] = std::unique_ptr<WBIN::StampT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = boundingBox(); if (_e) _o->boundingBox = std::unique_ptr<WBIN::AABB>(new WBIN::AABB(*_e)); }
}

inline flatbuffers::Offset<StampCloud> StampCloud::Pack(flatbuffers::FlatBufferBuilder &_fbb, const StampCloudT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateStampCloud(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<StampCloud> CreateStampCloud(flatbuffers::FlatBufferBuilder &_fbb, const StampCloudT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const StampCloudT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _stamps = _o->stamps.size() ? _fbb.CreateVector<flatbuffers::Offset<WBIN::Stamp>> (_o->stamps.size(), [](size_t i, _VectorArgs *__va) { return CreateStamp(*__va->__fbb, __va->__o->stamps[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _boundingBox = _o->boundingBox ? _o->boundingBox.get() : 0;
  return WBIN::CreateStampCloud(
      _fbb,
      _stamps,
      _boundingBox);
}

inline const WBIN::StampCloud *GetStampCloud(const void *buf) {
  return flatbuffers::GetRoot<WBIN::StampCloud>(buf);
}

inline const WBIN::StampCloud *GetSizePrefixedStampCloud(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::StampCloud>(buf);
}

inline StampCloud *GetMutableStampCloud(void *buf) {
  return flatbuffers::GetMutableRoot<StampCloud>(buf);
}

inline bool VerifyStampCloudBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::StampCloud>(nullptr);
}

inline bool VerifySizePrefixedStampCloudBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::StampCloud>(nullptr);
}

inline void FinishStampCloudBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::StampCloud> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedStampCloudBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::StampCloud> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::StampCloudT> UnPackStampCloud(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::StampCloudT>(GetStampCloud(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::StampCloudT> UnPackSizePrefixedStampCloud(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::StampCloudT>(GetSizePrefixedStampCloud(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WSTAMPCLOUD_WBIN_H_
