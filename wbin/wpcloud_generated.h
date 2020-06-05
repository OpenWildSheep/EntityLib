// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WPCLOUD_WBIN_H_
#define FLATBUFFERS_GENERATED_WPCLOUD_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct PCloud;
struct PCloudBuilder;
struct PCloudT;

struct PCloudT : public flatbuffers::NativeTable {
  typedef PCloud TableType;
  std::unique_ptr<WBIN::Float3ChannelT> position;
  std::unique_ptr<WBIN::Float3ChannelT> color;
  std::unique_ptr<WBIN::Float3ChannelT> texcoord;
  std::unique_ptr<WBIN::SourceFileInfT> sourceFileInf;
  PCloudT() {
  }
};

struct PCloud FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PCloudT NativeTableType;
  typedef PCloudBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POSITION = 4,
    VT_COLOR = 6,
    VT_TEXCOORD = 8,
    VT_SOURCEFILEINF = 10
  };
  const WBIN::Float3Channel *position() const {
    return GetPointer<const WBIN::Float3Channel *>(VT_POSITION);
  }
  WBIN::Float3Channel *mutable_position() {
    return GetPointer<WBIN::Float3Channel *>(VT_POSITION);
  }
  const WBIN::Float3Channel *color() const {
    return GetPointer<const WBIN::Float3Channel *>(VT_COLOR);
  }
  WBIN::Float3Channel *mutable_color() {
    return GetPointer<WBIN::Float3Channel *>(VT_COLOR);
  }
  const WBIN::Float3Channel *texcoord() const {
    return GetPointer<const WBIN::Float3Channel *>(VT_TEXCOORD);
  }
  WBIN::Float3Channel *mutable_texcoord() {
    return GetPointer<WBIN::Float3Channel *>(VT_TEXCOORD);
  }
  const WBIN::SourceFileInf *sourceFileInf() const {
    return GetPointer<const WBIN::SourceFileInf *>(VT_SOURCEFILEINF);
  }
  WBIN::SourceFileInf *mutable_sourceFileInf() {
    return GetPointer<WBIN::SourceFileInf *>(VT_SOURCEFILEINF);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_POSITION) &&
           verifier.VerifyTable(position()) &&
           VerifyOffset(verifier, VT_COLOR) &&
           verifier.VerifyTable(color()) &&
           VerifyOffset(verifier, VT_TEXCOORD) &&
           verifier.VerifyTable(texcoord()) &&
           VerifyOffset(verifier, VT_SOURCEFILEINF) &&
           verifier.VerifyTable(sourceFileInf()) &&
           verifier.EndTable();
  }
  PCloudT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(PCloudT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<PCloud> Pack(flatbuffers::FlatBufferBuilder &_fbb, const PCloudT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct PCloudBuilder {
  typedef PCloud Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_position(flatbuffers::Offset<WBIN::Float3Channel> position) {
    fbb_.AddOffset(PCloud::VT_POSITION, position);
  }
  void add_color(flatbuffers::Offset<WBIN::Float3Channel> color) {
    fbb_.AddOffset(PCloud::VT_COLOR, color);
  }
  void add_texcoord(flatbuffers::Offset<WBIN::Float3Channel> texcoord) {
    fbb_.AddOffset(PCloud::VT_TEXCOORD, texcoord);
  }
  void add_sourceFileInf(flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf) {
    fbb_.AddOffset(PCloud::VT_SOURCEFILEINF, sourceFileInf);
  }
  explicit PCloudBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PCloudBuilder &operator=(const PCloudBuilder &);
  flatbuffers::Offset<PCloud> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PCloud>(end);
    fbb_.Required(o, PCloud::VT_POSITION);
    return o;
  }
};

inline flatbuffers::Offset<PCloud> CreatePCloud(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    flatbuffers::Offset<WBIN::Float3Channel> color = 0,
    flatbuffers::Offset<WBIN::Float3Channel> texcoord = 0,
    flatbuffers::Offset<WBIN::SourceFileInf> sourceFileInf = 0) {
  PCloudBuilder builder_(_fbb);
  builder_.add_sourceFileInf(sourceFileInf);
  builder_.add_texcoord(texcoord);
  builder_.add_color(color);
  builder_.add_position(position);
  return builder_.Finish();
}

flatbuffers::Offset<PCloud> CreatePCloud(flatbuffers::FlatBufferBuilder &_fbb, const PCloudT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline PCloudT *PCloud::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  std::unique_ptr<WBIN::PCloudT> _o = std::unique_ptr<WBIN::PCloudT>(new PCloudT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void PCloud::UnPackTo(PCloudT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = position(); if (_e) _o->position = std::unique_ptr<WBIN::Float3ChannelT>(_e->UnPack(_resolver)); }
  { auto _e = color(); if (_e) _o->color = std::unique_ptr<WBIN::Float3ChannelT>(_e->UnPack(_resolver)); }
  { auto _e = texcoord(); if (_e) _o->texcoord = std::unique_ptr<WBIN::Float3ChannelT>(_e->UnPack(_resolver)); }
  { auto _e = sourceFileInf(); if (_e) _o->sourceFileInf = std::unique_ptr<WBIN::SourceFileInfT>(_e->UnPack(_resolver)); }
}

inline flatbuffers::Offset<PCloud> PCloud::Pack(flatbuffers::FlatBufferBuilder &_fbb, const PCloudT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreatePCloud(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<PCloud> CreatePCloud(flatbuffers::FlatBufferBuilder &_fbb, const PCloudT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const PCloudT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _position = _o->position ? CreateFloat3Channel(_fbb, _o->position.get(), _rehasher) : 0;
  auto _color = _o->color ? CreateFloat3Channel(_fbb, _o->color.get(), _rehasher) : 0;
  auto _texcoord = _o->texcoord ? CreateFloat3Channel(_fbb, _o->texcoord.get(), _rehasher) : 0;
  auto _sourceFileInf = _o->sourceFileInf ? CreateSourceFileInf(_fbb, _o->sourceFileInf.get(), _rehasher) : 0;
  return WBIN::CreatePCloud(
      _fbb,
      _position,
      _color,
      _texcoord,
      _sourceFileInf);
}

inline const WBIN::PCloud *GetPCloud(const void *buf) {
  return flatbuffers::GetRoot<WBIN::PCloud>(buf);
}

inline const WBIN::PCloud *GetSizePrefixedPCloud(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::PCloud>(buf);
}

inline PCloud *GetMutablePCloud(void *buf) {
  return flatbuffers::GetMutableRoot<PCloud>(buf);
}

inline bool VerifyPCloudBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::PCloud>(nullptr);
}

inline bool VerifySizePrefixedPCloudBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::PCloud>(nullptr);
}

inline void FinishPCloudBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::PCloud> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedPCloudBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::PCloud> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::PCloudT> UnPackPCloud(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::PCloudT>(GetPCloud(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::PCloudT> UnPackSizePrefixedPCloud(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::PCloudT>(GetSizePrefixedPCloud(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WPCLOUD_WBIN_H_
