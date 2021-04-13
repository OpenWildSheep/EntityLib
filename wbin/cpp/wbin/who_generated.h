// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WHO_WBIN_H_
#define FLATBUFFERS_GENERATED_WHO_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct HeightObj;
struct HeightObjBuilder;
struct HeightObjT;

struct HeightObjT : public flatbuffers::NativeTable {
  typedef HeightObj TableType;
  std::unique_ptr<WBIN::AABB> aabb{};
  std::unique_ptr<WBIN::Float3ChannelT> position{};
  std::vector<WBIN::Bool3> edgeVisibility{};
  std::vector<uint32_t> materials{};
  std::unique_ptr<WBIN::FloatMaskT> hardness{};
  std::unique_ptr<WBIN::FloatMaskT> erosionMask{};
  std::unique_ptr<WBIN::FloatMaskT> detailMask{};
  std::unique_ptr<WBIN::FloatMaskT> detailType{};
  std::vector<std::unique_ptr<WBIN::FloatMaskT>> motifMask{};
  std::unique_ptr<WBIN::SourceFileInfT> sourceFileInf{};
};

struct HeightObj FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef HeightObjT NativeTableType;
  typedef HeightObjBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_AABB = 4,
    VT_POSITION = 6,
    VT_EDGEVISIBILITY = 8,
    VT_MATERIALS = 10,
    VT_HARDNESS = 12,
    VT_EROSIONMASK = 14,
    VT_DETAILMASK = 16,
    VT_DETAILTYPE = 18,
    VT_MOTIFMASK = 20,
    VT_SOURCEFILEINF = 22
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
  const flatbuffers::Vector<uint32_t> *materials() const {
    return GetPointer<const flatbuffers::Vector<uint32_t> *>(VT_MATERIALS);
  }
  flatbuffers::Vector<uint32_t> *mutable_materials() {
    return GetPointer<flatbuffers::Vector<uint32_t> *>(VT_MATERIALS);
  }
  const WBIN::FloatMask *hardness() const {
    return GetPointer<const WBIN::FloatMask *>(VT_HARDNESS);
  }
  WBIN::FloatMask *mutable_hardness() {
    return GetPointer<WBIN::FloatMask *>(VT_HARDNESS);
  }
  const WBIN::FloatMask *erosionMask() const {
    return GetPointer<const WBIN::FloatMask *>(VT_EROSIONMASK);
  }
  WBIN::FloatMask *mutable_erosionMask() {
    return GetPointer<WBIN::FloatMask *>(VT_EROSIONMASK);
  }
  const WBIN::FloatMask *detailMask() const {
    return GetPointer<const WBIN::FloatMask *>(VT_DETAILMASK);
  }
  WBIN::FloatMask *mutable_detailMask() {
    return GetPointer<WBIN::FloatMask *>(VT_DETAILMASK);
  }
  const WBIN::FloatMask *detailType() const {
    return GetPointer<const WBIN::FloatMask *>(VT_DETAILTYPE);
  }
  WBIN::FloatMask *mutable_detailType() {
    return GetPointer<WBIN::FloatMask *>(VT_DETAILTYPE);
  }
  const flatbuffers::Vector<flatbuffers::Offset<WBIN::FloatMask>> *motifMask() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<WBIN::FloatMask>> *>(VT_MOTIFMASK);
  }
  flatbuffers::Vector<flatbuffers::Offset<WBIN::FloatMask>> *mutable_motifMask() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<WBIN::FloatMask>> *>(VT_MOTIFMASK);
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
           VerifyOffsetRequired(verifier, VT_MATERIALS) &&
           verifier.VerifyVector(materials()) &&
           VerifyOffset(verifier, VT_HARDNESS) &&
           verifier.VerifyTable(hardness()) &&
           VerifyOffset(verifier, VT_EROSIONMASK) &&
           verifier.VerifyTable(erosionMask()) &&
           VerifyOffset(verifier, VT_DETAILMASK) &&
           verifier.VerifyTable(detailMask()) &&
           VerifyOffset(verifier, VT_DETAILTYPE) &&
           verifier.VerifyTable(detailType()) &&
           VerifyOffset(verifier, VT_MOTIFMASK) &&
           verifier.VerifyVector(motifMask()) &&
           verifier.VerifyVectorOfTables(motifMask()) &&
           VerifyOffset(verifier, VT_SOURCEFILEINF) &&
           verifier.VerifyTable(sourceFileInf()) &&
           verifier.EndTable();
  }
  HeightObjT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(HeightObjT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<HeightObj> Pack(flatbuffers::FlatBufferBuilder &_fbb, const HeightObjT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct HeightObjBuilder {
  typedef HeightObj Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_aabb(const WBIN::AABB *aabb) {
    fbb_.AddStruct(HeightObj::VT_AABB, aabb);
  }
  void add_position(flatbuffers::Offset<WBIN::Float3Channel> position) {
    fbb_.AddOffset(HeightObj::VT_POSITION, position);
  }
  void add_edgeVisibility(flatbuffers::Offset<flatbuffers::Vector<const WBIN::Bool3 *>> edgeVisibility) {
    fbb_.AddOffset(HeightObj::VT_EDGEVISIBILITY, edgeVisibility);
  }
  void add_materials(flatbuffers::Offset<flatbuffers::Vector<uint32_t>> materials) {
    fbb_.AddOffset(HeightObj::VT_MATERIALS, materials);
  }
  void add_hardness(flatbuffers::Offset<WBIN::FloatMask> hardness) {
    fbb_.AddOffset(HeightObj::VT_HARDNESS, hardness);
  }
  void add_erosionMask(flatbuffers::Offset<WBIN::FloatMask> erosionMask) {
    fbb_.AddOffset(HeightObj::VT_EROSIONMASK, erosionMask);
  }
  void add_detailMask(flatbuffers::Offset<WBIN::FloatMask> detailMask) {
    fbb_.AddOffset(HeightObj::VT_DETAILMASK, detailMask);
  }
  void add_detailType(flatbuffers::Offset<WBIN::FloatMask> detailType) {
    fbb_.AddOffset(HeightObj::VT_DETAILTYPE, detailType);
  }
  void add_motifMask(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::FloatMask>>> motifMask) {
    fbb_.AddOffset(HeightObj::VT_MOTIFMASK, motifMask);
  }
  void add_sourceFileInf(flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf) {
    fbb_.AddOffset(HeightObj::VT_SOURCEFILEINF, sourceFileInf);
  }
  explicit HeightObjBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<HeightObj> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<HeightObj>(end);
    fbb_.Required(o, HeightObj::VT_POSITION);
    fbb_.Required(o, HeightObj::VT_EDGEVISIBILITY);
    fbb_.Required(o, HeightObj::VT_MATERIALS);
    return o;
  }
};

inline flatbuffers::Offset<HeightObj> CreateHeightObj(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::AABB *aabb = 0,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    flatbuffers::Offset<flatbuffers::Vector<const WBIN::Bool3 *>> edgeVisibility = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint32_t>> materials = 0,
    flatbuffers::Offset<WBIN::FloatMask> hardness = 0,
    flatbuffers::Offset<WBIN::FloatMask> erosionMask = 0,
    flatbuffers::Offset<WBIN::FloatMask> detailMask = 0,
    flatbuffers::Offset<WBIN::FloatMask> detailType = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::FloatMask>>> motifMask = 0,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  HeightObjBuilder builder_(_fbb);
  builder_.add_sourceFileInf(sourceFileInf);
  builder_.add_motifMask(motifMask);
  builder_.add_detailType(detailType);
  builder_.add_detailMask(detailMask);
  builder_.add_erosionMask(erosionMask);
  builder_.add_hardness(hardness);
  builder_.add_materials(materials);
  builder_.add_edgeVisibility(edgeVisibility);
  builder_.add_position(position);
  builder_.add_aabb(aabb);
  return builder_.Finish();
}

inline flatbuffers::Offset<HeightObj> CreateHeightObjDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::AABB *aabb = 0,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    const std::vector<WBIN::Bool3> *edgeVisibility = nullptr,
    const std::vector<uint32_t> *materials = nullptr,
    flatbuffers::Offset<WBIN::FloatMask> hardness = 0,
    flatbuffers::Offset<WBIN::FloatMask> erosionMask = 0,
    flatbuffers::Offset<WBIN::FloatMask> detailMask = 0,
    flatbuffers::Offset<WBIN::FloatMask> detailType = 0,
    const std::vector<flatbuffers::Offset<WBIN::FloatMask>> *motifMask = nullptr,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  auto edgeVisibility__ = edgeVisibility ? _fbb.CreateVectorOfStructs<WBIN::Bool3>(*edgeVisibility) : 0;
  auto materials__ = materials ? _fbb.CreateVector<uint32_t>(*materials) : 0;
  auto motifMask__ = motifMask ? _fbb.CreateVector<flatbuffers::Offset<WBIN::FloatMask>>(*motifMask) : 0;
  return WBIN::CreateHeightObj(
      _fbb,
      aabb,
      position,
      edgeVisibility__,
      materials__,
      hardness,
      erosionMask,
      detailMask,
      detailType,
      motifMask__,
      sourceFileInf);
}

flatbuffers::Offset<HeightObj> CreateHeightObj(flatbuffers::FlatBufferBuilder &_fbb, const HeightObjT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline HeightObjT *HeightObj::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<HeightObjT>(new HeightObjT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void HeightObj::UnPackTo(HeightObjT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = aabb(); if (_e) _o->aabb = std::unique_ptr<WBIN::AABB>(new WBIN::AABB(*_e)); }
  { auto _e = position(); if (_e) _o->position = std::unique_ptr<WBIN::Float3ChannelT>(_e->UnPack(_resolver)); }
  { auto _e = edgeVisibility(); if (_e) { _o->edgeVisibility.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->edgeVisibility[_i] = *_e->Get(_i); } } }
  { auto _e = materials(); if (_e) { _o->materials.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->materials[_i] = _e->Get(_i); } } }
  { auto _e = hardness(); if (_e) _o->hardness = std::unique_ptr<WBIN::FloatMaskT>(_e->UnPack(_resolver)); }
  { auto _e = erosionMask(); if (_e) _o->erosionMask = std::unique_ptr<WBIN::FloatMaskT>(_e->UnPack(_resolver)); }
  { auto _e = detailMask(); if (_e) _o->detailMask = std::unique_ptr<WBIN::FloatMaskT>(_e->UnPack(_resolver)); }
  { auto _e = detailType(); if (_e) _o->detailType = std::unique_ptr<WBIN::FloatMaskT>(_e->UnPack(_resolver)); }
  { auto _e = motifMask(); if (_e) { _o->motifMask.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->motifMask[_i] = std::unique_ptr<WBIN::FloatMaskT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = sourceFileInf(); if (_e) _o->sourceFileInf = std::unique_ptr<WBIN::SourceFileInfT>(_e->UnPack(_resolver)); }
}

inline flatbuffers::Offset<HeightObj> HeightObj::Pack(flatbuffers::FlatBufferBuilder &_fbb, const HeightObjT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateHeightObj(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<HeightObj> CreateHeightObj(flatbuffers::FlatBufferBuilder &_fbb, const HeightObjT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const HeightObjT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _aabb = _o->aabb ? _o->aabb.get() : 0;
  auto _position = _o->position ? CreateFloat3Channel(_fbb, _o->position.get(), _rehasher) : 0;
  auto _edgeVisibility = _fbb.CreateVectorOfStructs(_o->edgeVisibility);
  auto _materials = _fbb.CreateVector(_o->materials);
  auto _hardness = _o->hardness ? CreateFloatMask(_fbb, _o->hardness.get(), _rehasher) : 0;
  auto _erosionMask = _o->erosionMask ? CreateFloatMask(_fbb, _o->erosionMask.get(), _rehasher) : 0;
  auto _detailMask = _o->detailMask ? CreateFloatMask(_fbb, _o->detailMask.get(), _rehasher) : 0;
  auto _detailType = _o->detailType ? CreateFloatMask(_fbb, _o->detailType.get(), _rehasher) : 0;
  auto _motifMask = _o->motifMask.size() ? _fbb.CreateVector<flatbuffers::Offset<WBIN::FloatMask>> (_o->motifMask.size(), [](size_t i, _VectorArgs *__va) { return CreateFloatMask(*__va->__fbb, __va->__o->motifMask[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _sourceFileInf = _o->sourceFileInf ? CreateSourceFileInf(_fbb, _o->sourceFileInf.get(), _rehasher) : 0;
  return WBIN::CreateHeightObj(
      _fbb,
      _aabb,
      _position,
      _edgeVisibility,
      _materials,
      _hardness,
      _erosionMask,
      _detailMask,
      _detailType,
      _motifMask,
      _sourceFileInf);
}

inline const WBIN::HeightObj *GetHeightObj(const void *buf) {
  return flatbuffers::GetRoot<WBIN::HeightObj>(buf);
}

inline const WBIN::HeightObj *GetSizePrefixedHeightObj(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::HeightObj>(buf);
}

inline HeightObj *GetMutableHeightObj(void *buf) {
  return flatbuffers::GetMutableRoot<HeightObj>(buf);
}

inline bool VerifyHeightObjBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::HeightObj>(nullptr);
}

inline bool VerifySizePrefixedHeightObjBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::HeightObj>(nullptr);
}

inline void FinishHeightObjBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::HeightObj> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedHeightObjBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::HeightObj> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::HeightObjT> UnPackHeightObj(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::HeightObjT>(GetHeightObj(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::HeightObjT> UnPackSizePrefixedHeightObj(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::HeightObjT>(GetSizePrefixedHeightObj(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WHO_WBIN_H_
