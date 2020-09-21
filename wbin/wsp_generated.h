// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WSP_WBIN_H_
#define FLATBUFFERS_GENERATED_WSP_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct SeedPatch;
struct SeedPatchBuilder;
struct SeedPatchT;

struct SeedPatchT : public flatbuffers::NativeTable {
  typedef SeedPatch TableType;
  std::unique_ptr<WBIN::AABB> aabb;
  std::unique_ptr<WBIN::Float3ChannelT> position;
  std::vector<WBIN::Bool3> edgeVisibility;
  std::unique_ptr<WBIN::Float3ChannelT> color;
  std::unique_ptr<WBIN::SourceFileInfT> sourceFileInf;
  SeedPatchT() {
  }
};

struct SeedPatch FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef SeedPatchT NativeTableType;
  typedef SeedPatchBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_AABB = 4,
    VT_POSITION = 6,
    VT_EDGEVISIBILITY = 8,
    VT_COLOR = 10,
    VT_SOURCEFILEINF = 12
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
  const flatbuffers::Vector<const WBIN::Bool3 *> *edgeVisibility() const {
    return GetPointer<const flatbuffers::Vector<const WBIN::Bool3 *> *>(VT_EDGEVISIBILITY);
  }
  flatbuffers::Vector<const WBIN::Bool3 *> *mutable_edgeVisibility() {
    return GetPointer<flatbuffers::Vector<const WBIN::Bool3 *> *>(VT_EDGEVISIBILITY);
  }
  const WBIN::Float3Channel *color() const {
    return GetPointer<const WBIN::Float3Channel *>(VT_COLOR);
  }
  WBIN::Float3Channel *mutable_color() {
    return GetPointer<WBIN::Float3Channel *>(VT_COLOR);
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
           VerifyOffsetRequired(verifier, VT_EDGEVISIBILITY) &&
           verifier.VerifyVector(edgeVisibility()) &&
           VerifyOffset(verifier, VT_COLOR) &&
           verifier.VerifyTable(color()) &&
           VerifyOffset(verifier, VT_SOURCEFILEINF) &&
           verifier.VerifyTable(sourceFileInf()) &&
           verifier.EndTable();
  }
  SeedPatchT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(SeedPatchT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<SeedPatch> Pack(flatbuffers::FlatBufferBuilder &_fbb, const SeedPatchT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct SeedPatchBuilder {
  typedef SeedPatch Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_aabb(const WBIN::AABB *aabb) {
    fbb_.AddStruct(SeedPatch::VT_AABB, aabb);
  }
  void add_position(flatbuffers::Offset<WBIN::Float3Channel> position) {
    fbb_.AddOffset(SeedPatch::VT_POSITION, position);
  }
  void add_edgeVisibility(flatbuffers::Offset<flatbuffers::Vector<const WBIN::Bool3 *>> edgeVisibility) {
    fbb_.AddOffset(SeedPatch::VT_EDGEVISIBILITY, edgeVisibility);
  }
  void add_color(flatbuffers::Offset<WBIN::Float3Channel> color) {
    fbb_.AddOffset(SeedPatch::VT_COLOR, color);
  }
  void add_sourceFileInf(flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf) {
    fbb_.AddOffset(SeedPatch::VT_SOURCEFILEINF, sourceFileInf);
  }
  explicit SeedPatchBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  SeedPatchBuilder &operator=(const SeedPatchBuilder &);
  flatbuffers::Offset<SeedPatch> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<SeedPatch>(end);
    fbb_.Required(o, SeedPatch::VT_POSITION);
    fbb_.Required(o, SeedPatch::VT_EDGEVISIBILITY);
    return o;
  }
};

inline flatbuffers::Offset<SeedPatch> CreateSeedPatch(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::AABB *aabb = 0,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    flatbuffers::Offset<flatbuffers::Vector<const WBIN::Bool3 *>> edgeVisibility = 0,
    flatbuffers::Offset<WBIN::Float3Channel> color = 0,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  SeedPatchBuilder builder_(_fbb);
  builder_.add_sourceFileInf(sourceFileInf);
  builder_.add_color(color);
  builder_.add_edgeVisibility(edgeVisibility);
  builder_.add_position(position);
  builder_.add_aabb(aabb);
  return builder_.Finish();
}

inline flatbuffers::Offset<SeedPatch> CreateSeedPatchDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::AABB *aabb = 0,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    const std::vector<WBIN::Bool3> *edgeVisibility = nullptr,
    flatbuffers::Offset<WBIN::Float3Channel> color = 0,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  auto edgeVisibility__ = edgeVisibility ? _fbb.CreateVectorOfStructs<WBIN::Bool3>(*edgeVisibility) : 0;
  return WBIN::CreateSeedPatch(
      _fbb,
      aabb,
      position,
      edgeVisibility__,
      color,
      sourceFileInf);
}

flatbuffers::Offset<SeedPatch> CreateSeedPatch(flatbuffers::FlatBufferBuilder &_fbb, const SeedPatchT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline SeedPatchT *SeedPatch::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  std::unique_ptr<WBIN::SeedPatchT> _o = std::unique_ptr<WBIN::SeedPatchT>(new SeedPatchT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void SeedPatch::UnPackTo(SeedPatchT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = aabb(); if (_e) _o->aabb = std::unique_ptr<WBIN::AABB>(new WBIN::AABB(*_e)); }
  { auto _e = position(); if (_e) _o->position = std::unique_ptr<WBIN::Float3ChannelT>(_e->UnPack(_resolver)); }
  { auto _e = edgeVisibility(); if (_e) { _o->edgeVisibility.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->edgeVisibility[_i] = *_e->Get(_i); } } }
  { auto _e = color(); if (_e) _o->color = std::unique_ptr<WBIN::Float3ChannelT>(_e->UnPack(_resolver)); }
  { auto _e = sourceFileInf(); if (_e) _o->sourceFileInf = std::unique_ptr<WBIN::SourceFileInfT>(_e->UnPack(_resolver)); }
}

inline flatbuffers::Offset<SeedPatch> SeedPatch::Pack(flatbuffers::FlatBufferBuilder &_fbb, const SeedPatchT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateSeedPatch(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<SeedPatch> CreateSeedPatch(flatbuffers::FlatBufferBuilder &_fbb, const SeedPatchT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const SeedPatchT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _aabb = _o->aabb ? _o->aabb.get() : 0;
  auto _position = _o->position ? CreateFloat3Channel(_fbb, _o->position.get(), _rehasher) : 0;
  auto _edgeVisibility = _fbb.CreateVectorOfStructs(_o->edgeVisibility);
  auto _color = _o->color ? CreateFloat3Channel(_fbb, _o->color.get(), _rehasher) : 0;
  auto _sourceFileInf = _o->sourceFileInf ? CreateSourceFileInf(_fbb, _o->sourceFileInf.get(), _rehasher) : 0;
  return WBIN::CreateSeedPatch(
      _fbb,
      _aabb,
      _position,
      _edgeVisibility,
      _color,
      _sourceFileInf);
}

inline const WBIN::SeedPatch *GetSeedPatch(const void *buf) {
  return flatbuffers::GetRoot<WBIN::SeedPatch>(buf);
}

inline const WBIN::SeedPatch *GetSizePrefixedSeedPatch(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::SeedPatch>(buf);
}

inline SeedPatch *GetMutableSeedPatch(void *buf) {
  return flatbuffers::GetMutableRoot<SeedPatch>(buf);
}

inline bool VerifySeedPatchBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::SeedPatch>(nullptr);
}

inline bool VerifySizePrefixedSeedPatchBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::SeedPatch>(nullptr);
}

inline void FinishSeedPatchBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::SeedPatch> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedSeedPatchBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::SeedPatch> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::SeedPatchT> UnPackSeedPatch(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::SeedPatchT>(GetSeedPatch(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::SeedPatchT> UnPackSizePrefixedSeedPatch(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::SeedPatchT>(GetSizePrefixedSeedPatch(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WSP_WBIN_H_