// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WTHUMB_WBIN_H_
#define FLATBUFFERS_GENERATED_WTHUMB_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct Thumb;
struct ThumbBuilder;
struct ThumbT;

struct ThumbT : public flatbuffers::NativeTable {
  typedef Thumb TableType;
  std::unique_ptr<WBIN::AABB> aabb{};
  std::unique_ptr<WBIN::Float3ChannelT> position{};
  std::vector<WBIN::Float3> color{};
  std::unique_ptr<WBIN::SourceFileInfT> sourceFileInf{};
};

struct Thumb FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ThumbT NativeTableType;
  typedef ThumbBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_AABB = 4,
    VT_POSITION = 6,
    VT_COLOR = 8,
    VT_SOURCEFILEINF = 10
  };
  const WBIN::AABB *aabb() const {
    return GetStruct<const WBIN::AABB *>(VT_AABB);
  }
  WBIN::AABB *mutable_aabb() {
    return GetStruct<WBIN::AABB *>(VT_AABB);
  }
  const WBIN::Float3Channel *position() const {
    return GetPointer<const WBIN::Float3Channel *>(VT_POSITION);
  }
  WBIN::Float3Channel *mutable_position() {
    return GetPointer<WBIN::Float3Channel *>(VT_POSITION);
  }
  const flatbuffers::Vector<const WBIN::Float3 *> *color() const {
    return GetPointer<const flatbuffers::Vector<const WBIN::Float3 *> *>(VT_COLOR);
  }
  flatbuffers::Vector<const WBIN::Float3 *> *mutable_color() {
    return GetPointer<flatbuffers::Vector<const WBIN::Float3 *> *>(VT_COLOR);
  }
  const WBIN::SourceFileInf *sourceFileInf() const {
    return GetPointer<const WBIN::SourceFileInf *>(VT_SOURCEFILEINF);
  }
  WBIN::SourceFileInf *mutable_sourceFileInf() {
    return GetPointer<WBIN::SourceFileInf *>(VT_SOURCEFILEINF);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<WBIN::AABB>(verifier, VT_AABB) &&
           VerifyOffsetRequired(verifier, VT_POSITION) &&
           verifier.VerifyTable(position()) &&
           VerifyOffsetRequired(verifier, VT_COLOR) &&
           verifier.VerifyVector(color()) &&
           VerifyOffset(verifier, VT_SOURCEFILEINF) &&
           verifier.VerifyTable(sourceFileInf()) &&
           verifier.EndTable();
  }
  ThumbT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(ThumbT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Thumb> Pack(flatbuffers::FlatBufferBuilder &_fbb, const ThumbT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct ThumbBuilder {
  typedef Thumb Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_aabb(const WBIN::AABB *aabb) {
    fbb_.AddStruct(Thumb::VT_AABB, aabb);
  }
  void add_position(flatbuffers::Offset<WBIN::Float3Channel> position) {
    fbb_.AddOffset(Thumb::VT_POSITION, position);
  }
  void add_color(flatbuffers::Offset<flatbuffers::Vector<const WBIN::Float3 *>> color) {
    fbb_.AddOffset(Thumb::VT_COLOR, color);
  }
  void add_sourceFileInf(flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf) {
    fbb_.AddOffset(Thumb::VT_SOURCEFILEINF, sourceFileInf);
  }
  explicit ThumbBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Thumb> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Thumb>(end);
    fbb_.Required(o, Thumb::VT_POSITION);
    fbb_.Required(o, Thumb::VT_COLOR);
    return o;
  }
};

inline flatbuffers::Offset<Thumb> CreateThumb(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::AABB *aabb = 0,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    flatbuffers::Offset<flatbuffers::Vector<const WBIN::Float3 *>> color = 0,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  ThumbBuilder builder_(_fbb);
  builder_.add_sourceFileInf(sourceFileInf);
  builder_.add_color(color);
  builder_.add_position(position);
  builder_.add_aabb(aabb);
  return builder_.Finish();
}

inline flatbuffers::Offset<Thumb> CreateThumbDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::AABB *aabb = 0,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    const std::vector<WBIN::Float3> *color = nullptr,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  auto color__ = color ? _fbb.CreateVectorOfStructs<WBIN::Float3>(*color) : 0;
  return WBIN::CreateThumb(
      _fbb,
      aabb,
      position,
      color__,
      sourceFileInf);
}

flatbuffers::Offset<Thumb> CreateThumb(flatbuffers::FlatBufferBuilder &_fbb, const ThumbT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline ThumbT *Thumb::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<ThumbT>(new ThumbT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Thumb::UnPackTo(ThumbT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = aabb(); if (_e) _o->aabb = std::unique_ptr<WBIN::AABB>(new WBIN::AABB(*_e)); }
  { auto _e = position(); if (_e) _o->position = std::unique_ptr<WBIN::Float3ChannelT>(_e->UnPack(_resolver)); }
  { auto _e = color(); if (_e) { _o->color.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->color[_i] = *_e->Get(_i); } } }
  { auto _e = sourceFileInf(); if (_e) _o->sourceFileInf = std::unique_ptr<WBIN::SourceFileInfT>(_e->UnPack(_resolver)); }
}

inline flatbuffers::Offset<Thumb> Thumb::Pack(flatbuffers::FlatBufferBuilder &_fbb, const ThumbT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateThumb(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Thumb> CreateThumb(flatbuffers::FlatBufferBuilder &_fbb, const ThumbT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const ThumbT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _aabb = _o->aabb ? _o->aabb.get() : 0;
  auto _position = _o->position ? CreateFloat3Channel(_fbb, _o->position.get(), _rehasher) : 0;
  auto _color = _fbb.CreateVectorOfStructs(_o->color);
  auto _sourceFileInf = _o->sourceFileInf ? CreateSourceFileInf(_fbb, _o->sourceFileInf.get(), _rehasher) : 0;
  return WBIN::CreateThumb(
      _fbb,
      _aabb,
      _position,
      _color,
      _sourceFileInf);
}

inline const WBIN::Thumb *GetThumb(const void *buf) {
  return flatbuffers::GetRoot<WBIN::Thumb>(buf);
}

inline const WBIN::Thumb *GetSizePrefixedThumb(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::Thumb>(buf);
}

inline Thumb *GetMutableThumb(void *buf) {
  return flatbuffers::GetMutableRoot<Thumb>(buf);
}

inline bool VerifyThumbBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::Thumb>(nullptr);
}

inline bool VerifySizePrefixedThumbBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::Thumb>(nullptr);
}

inline void FinishThumbBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::Thumb> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedThumbBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::Thumb> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::ThumbT> UnPackThumb(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::ThumbT>(GetThumb(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::ThumbT> UnPackSizePrefixedThumb(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::ThumbT>(GetSizePrefixedThumb(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WTHUMB_WBIN_H_
