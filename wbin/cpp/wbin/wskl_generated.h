// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WSKL_WBIN_H_
#define FLATBUFFERS_GENERATED_WSKL_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct BoneData;
struct BoneDataBuilder;
struct BoneDataT;

struct Skl;
struct SklBuilder;
struct SklT;

struct BoneDataT : public flatbuffers::NativeTable {
  typedef BoneData TableType;
  int32_t parentBoneIndex = 0;
  std::string name{};
};

struct BoneData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef BoneDataT NativeTableType;
  typedef BoneDataBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PARENTBONEINDEX = 4,
    VT_NAME = 6
  };
  int32_t parentBoneIndex() const {
    return GetField<int32_t>(VT_PARENTBONEINDEX, 0);
  }
  bool mutate_parentBoneIndex(int32_t _parentBoneIndex) {
    return SetField<int32_t>(VT_PARENTBONEINDEX, _parentBoneIndex, 0);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  flatbuffers::String *mutable_name() {
    return GetPointer<flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_PARENTBONEINDEX) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
  BoneDataT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(BoneDataT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<BoneData> Pack(flatbuffers::FlatBufferBuilder &_fbb, const BoneDataT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct BoneDataBuilder {
  typedef BoneData Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_parentBoneIndex(int32_t parentBoneIndex) {
    fbb_.AddElement<int32_t>(BoneData::VT_PARENTBONEINDEX, parentBoneIndex, 0);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(BoneData::VT_NAME, name);
  }
  explicit BoneDataBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<BoneData> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<BoneData>(end);
    fbb_.Required(o, BoneData::VT_NAME);
    return o;
  }
};

inline flatbuffers::Offset<BoneData> CreateBoneData(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t parentBoneIndex = 0,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  BoneDataBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_parentBoneIndex(parentBoneIndex);
  return builder_.Finish();
}

inline flatbuffers::Offset<BoneData> CreateBoneDataDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t parentBoneIndex = 0,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return WBIN::CreateBoneData(
      _fbb,
      parentBoneIndex,
      name__);
}

flatbuffers::Offset<BoneData> CreateBoneData(flatbuffers::FlatBufferBuilder &_fbb, const BoneDataT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct SklT : public flatbuffers::NativeTable {
  typedef Skl TableType;
  std::vector<std::unique_ptr<WBIN::BoneDataT>> skeleton{};
  std::unique_ptr<WBIN::SourceFileInfT> sourceFileInf{};
};

struct Skl FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef SklT NativeTableType;
  typedef SklBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SKELETON = 4,
    VT_SOURCEFILEINF = 6
  };
  const flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneData>> *skeleton() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneData>> *>(VT_SKELETON);
  }
  flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneData>> *mutable_skeleton() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneData>> *>(VT_SKELETON);
  }
  const WBIN::SourceFileInf *sourceFileInf() const {
    return GetPointer<const WBIN::SourceFileInf *>(VT_SOURCEFILEINF);
  }
  WBIN::SourceFileInf *mutable_sourceFileInf() {
    return GetPointer<WBIN::SourceFileInf *>(VT_SOURCEFILEINF);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_SKELETON) &&
           verifier.VerifyVector(skeleton()) &&
           verifier.VerifyVectorOfTables(skeleton()) &&
           VerifyOffset(verifier, VT_SOURCEFILEINF) &&
           verifier.VerifyTable(sourceFileInf()) &&
           verifier.EndTable();
  }
  SklT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(SklT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Skl> Pack(flatbuffers::FlatBufferBuilder &_fbb, const SklT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct SklBuilder {
  typedef Skl Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_skeleton(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneData>>> skeleton) {
    fbb_.AddOffset(Skl::VT_SKELETON, skeleton);
  }
  void add_sourceFileInf(flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf) {
    fbb_.AddOffset(Skl::VT_SOURCEFILEINF, sourceFileInf);
  }
  explicit SklBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Skl> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Skl>(end);
    fbb_.Required(o, Skl::VT_SKELETON);
    return o;
  }
};

inline flatbuffers::Offset<Skl> CreateSkl(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneData>>> skeleton = 0,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  SklBuilder builder_(_fbb);
  builder_.add_sourceFileInf(sourceFileInf);
  builder_.add_skeleton(skeleton);
  return builder_.Finish();
}

inline flatbuffers::Offset<Skl> CreateSklDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<WBIN::BoneData>> *skeleton = nullptr,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  auto skeleton__ = skeleton ? _fbb.CreateVector<flatbuffers::Offset<WBIN::BoneData>>(*skeleton) : 0;
  return WBIN::CreateSkl(
      _fbb,
      skeleton__,
      sourceFileInf);
}

flatbuffers::Offset<Skl> CreateSkl(flatbuffers::FlatBufferBuilder &_fbb, const SklT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline BoneDataT *BoneData::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<BoneDataT>(new BoneDataT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void BoneData::UnPackTo(BoneDataT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = parentBoneIndex(); _o->parentBoneIndex = _e; }
  { auto _e = name(); if (_e) _o->name = _e->str(); }
}

inline flatbuffers::Offset<BoneData> BoneData::Pack(flatbuffers::FlatBufferBuilder &_fbb, const BoneDataT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateBoneData(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<BoneData> CreateBoneData(flatbuffers::FlatBufferBuilder &_fbb, const BoneDataT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const BoneDataT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _parentBoneIndex = _o->parentBoneIndex;
  auto _name = _fbb.CreateString(_o->name);
  return WBIN::CreateBoneData(
      _fbb,
      _parentBoneIndex,
      _name);
}

inline SklT *Skl::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<SklT>(new SklT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Skl::UnPackTo(SklT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = skeleton(); if (_e) { _o->skeleton.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->skeleton[_i] = std::unique_ptr<WBIN::BoneDataT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = sourceFileInf(); if (_e) _o->sourceFileInf = std::unique_ptr<WBIN::SourceFileInfT>(_e->UnPack(_resolver)); }
}

inline flatbuffers::Offset<Skl> Skl::Pack(flatbuffers::FlatBufferBuilder &_fbb, const SklT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateSkl(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Skl> CreateSkl(flatbuffers::FlatBufferBuilder &_fbb, const SklT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const SklT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _skeleton = _fbb.CreateVector<flatbuffers::Offset<WBIN::BoneData>> (_o->skeleton.size(), [](size_t i, _VectorArgs *__va) { return CreateBoneData(*__va->__fbb, __va->__o->skeleton[i].get(), __va->__rehasher); }, &_va );
  auto _sourceFileInf = _o->sourceFileInf ? CreateSourceFileInf(_fbb, _o->sourceFileInf.get(), _rehasher) : 0;
  return WBIN::CreateSkl(
      _fbb,
      _skeleton,
      _sourceFileInf);
}

inline const WBIN::Skl *GetSkl(const void *buf) {
  return flatbuffers::GetRoot<WBIN::Skl>(buf);
}

inline const WBIN::Skl *GetSizePrefixedSkl(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::Skl>(buf);
}

inline Skl *GetMutableSkl(void *buf) {
  return flatbuffers::GetMutableRoot<Skl>(buf);
}

inline bool VerifySklBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::Skl>(nullptr);
}

inline bool VerifySizePrefixedSklBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::Skl>(nullptr);
}

inline void FinishSklBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::Skl> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedSklBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::Skl> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::SklT> UnPackSkl(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::SklT>(GetSkl(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::SklT> UnPackSizePrefixedSkl(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::SklT>(GetSizePrefixedSkl(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WSKL_WBIN_H_
