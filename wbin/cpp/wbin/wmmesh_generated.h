// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WMMESH_WBIN_H_
#define FLATBUFFERS_GENERATED_WMMESH_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct WMmesh;
struct WMmeshBuilder;
struct WMmeshT;

struct WMmeshT : public flatbuffers::NativeTable {
  typedef WMmesh TableType;
  std::unique_ptr<WBIN::Float3ChannelT> position{};
  std::vector<int8_t> materials{};
};

struct WMmesh FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef WMmeshT NativeTableType;
  typedef WMmeshBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POSITION = 4,
    VT_MATERIALS = 6
  };
  const WBIN::Float3Channel *position() const {
    return GetPointer<const WBIN::Float3Channel *>(VT_POSITION);
  }
  WBIN::Float3Channel *mutable_position() {
    return GetPointer<WBIN::Float3Channel *>(VT_POSITION);
  }
  const flatbuffers::Vector<int8_t> *materials() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_MATERIALS);
  }
  flatbuffers::Vector<int8_t> *mutable_materials() {
    return GetPointer<flatbuffers::Vector<int8_t> *>(VT_MATERIALS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_POSITION) &&
           verifier.VerifyTable(position()) &&
           VerifyOffsetRequired(verifier, VT_MATERIALS) &&
           verifier.VerifyVector(materials()) &&
           verifier.EndTable();
  }
  WMmeshT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(WMmeshT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<WMmesh> Pack(flatbuffers::FlatBufferBuilder &_fbb, const WMmeshT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct WMmeshBuilder {
  typedef WMmesh Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_position(flatbuffers::Offset<WBIN::Float3Channel> position) {
    fbb_.AddOffset(WMmesh::VT_POSITION, position);
  }
  void add_materials(flatbuffers::Offset<flatbuffers::Vector<int8_t>> materials) {
    fbb_.AddOffset(WMmesh::VT_MATERIALS, materials);
  }
  explicit WMmeshBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<WMmesh> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<WMmesh>(end);
    fbb_.Required(o, WMmesh::VT_POSITION);
    fbb_.Required(o, WMmesh::VT_MATERIALS);
    return o;
  }
};

inline flatbuffers::Offset<WMmesh> CreateWMmesh(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> materials = 0) {
  WMmeshBuilder builder_(_fbb);
  builder_.add_materials(materials);
  builder_.add_position(position);
  return builder_.Finish();
}

inline flatbuffers::Offset<WMmesh> CreateWMmeshDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<WBIN::Float3Channel> position = 0,
    const std::vector<int8_t> *materials = nullptr) {
  auto materials__ = materials ? _fbb.CreateVector<int8_t>(*materials) : 0;
  return WBIN::CreateWMmesh(
      _fbb,
      position,
      materials__);
}

flatbuffers::Offset<WMmesh> CreateWMmesh(flatbuffers::FlatBufferBuilder &_fbb, const WMmeshT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline WMmeshT *WMmesh::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<WMmeshT>(new WMmeshT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void WMmesh::UnPackTo(WMmeshT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = position(); if (_e) _o->position = std::unique_ptr<WBIN::Float3ChannelT>(_e->UnPack(_resolver)); }
  { auto _e = materials(); if (_e) { _o->materials.resize(_e->size()); std::copy(_e->begin(), _e->end(), _o->materials.begin()); } }
}

inline flatbuffers::Offset<WMmesh> WMmesh::Pack(flatbuffers::FlatBufferBuilder &_fbb, const WMmeshT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateWMmesh(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<WMmesh> CreateWMmesh(flatbuffers::FlatBufferBuilder &_fbb, const WMmeshT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const WMmeshT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _position = _o->position ? CreateFloat3Channel(_fbb, _o->position.get(), _rehasher) : 0;
  auto _materials = _fbb.CreateVector(_o->materials);
  return WBIN::CreateWMmesh(
      _fbb,
      _position,
      _materials);
}

inline const WBIN::WMmesh *GetWMmesh(const void *buf) {
  return flatbuffers::GetRoot<WBIN::WMmesh>(buf);
}

inline const WBIN::WMmesh *GetSizePrefixedWMmesh(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::WMmesh>(buf);
}

inline WMmesh *GetMutableWMmesh(void *buf) {
  return flatbuffers::GetMutableRoot<WMmesh>(buf);
}

inline bool VerifyWMmeshBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::WMmesh>(nullptr);
}

inline bool VerifySizePrefixedWMmeshBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::WMmesh>(nullptr);
}

inline void FinishWMmeshBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::WMmesh> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedWMmeshBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::WMmesh> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::WMmeshT> UnPackWMmesh(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::WMmeshT>(GetWMmesh(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::WMmeshT> UnPackSizePrefixedWMmesh(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::WMmeshT>(GetSizePrefixedWMmesh(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WMMESH_WBIN_H_