// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WHEIGHTMAPTILEDB_WBIN_H_
#define FLATBUFFERS_GENERATED_WHEIGHTMAPTILEDB_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct TileRef;
struct TileRefBuilder;
struct TileRefT;

struct TileDB;
struct TileDBBuilder;
struct TileDBT;

struct TileRefT : public flatbuffers::NativeTable {
  typedef TileRef TableType;
  std::unique_ptr<WBIN::UInt2> coordinates{};
  std::string path{};
};

struct TileRef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef TileRefT NativeTableType;
  typedef TileRefBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_COORDINATES = 4,
    VT_PATH = 6
  };
  const WBIN::UInt2 *coordinates() const {
    return GetStruct<const WBIN::UInt2 *>(VT_COORDINATES);
  }
  WBIN::UInt2 *mutable_coordinates() {
    return GetStruct<WBIN::UInt2 *>(VT_COORDINATES);
  }
  const flatbuffers::String *path() const {
    return GetPointer<const flatbuffers::String *>(VT_PATH);
  }
  flatbuffers::String *mutable_path() {
    return GetPointer<flatbuffers::String *>(VT_PATH);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyFieldRequired<WBIN::UInt2>(verifier, VT_COORDINATES) &&
           VerifyOffset(verifier, VT_PATH) &&
           verifier.VerifyString(path()) &&
           verifier.EndTable();
  }
  TileRefT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(TileRefT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<TileRef> Pack(flatbuffers::FlatBufferBuilder &_fbb, const TileRefT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct TileRefBuilder {
  typedef TileRef Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_coordinates(const WBIN::UInt2 *coordinates) {
    fbb_.AddStruct(TileRef::VT_COORDINATES, coordinates);
  }
  void add_path(flatbuffers::Offset<flatbuffers::String> path) {
    fbb_.AddOffset(TileRef::VT_PATH, path);
  }
  explicit TileRefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<TileRef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<TileRef>(end);
    fbb_.Required(o, TileRef::VT_COORDINATES);
    return o;
  }
};

inline flatbuffers::Offset<TileRef> CreateTileRef(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::UInt2 *coordinates = 0,
    flatbuffers::Offset<flatbuffers::String> path = 0) {
  TileRefBuilder builder_(_fbb);
  builder_.add_path(path);
  builder_.add_coordinates(coordinates);
  return builder_.Finish();
}

inline flatbuffers::Offset<TileRef> CreateTileRefDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::UInt2 *coordinates = 0,
    const char *path = nullptr) {
  auto path__ = path ? _fbb.CreateString(path) : 0;
  return WBIN::CreateTileRef(
      _fbb,
      coordinates,
      path__);
}

flatbuffers::Offset<TileRef> CreateTileRef(flatbuffers::FlatBufferBuilder &_fbb, const TileRefT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct TileDBT : public flatbuffers::NativeTable {
  typedef TileDB TableType;
  std::unique_ptr<WBIN::UInt2> tile_count{};
  std::unique_ptr<WBIN::UInt2> tile_resolution{};
  std::unique_ptr<WBIN::Float2> tile_meter_size{};
  std::vector<std::unique_ptr<WBIN::TileRefT>> tiles{};
};

struct TileDB FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef TileDBT NativeTableType;
  typedef TileDBBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TILE_COUNT = 4,
    VT_TILE_RESOLUTION = 6,
    VT_TILE_METER_SIZE = 8,
    VT_TILES = 10
  };
  const WBIN::UInt2 *tile_count() const {
    return GetStruct<const WBIN::UInt2 *>(VT_TILE_COUNT);
  }
  WBIN::UInt2 *mutable_tile_count() {
    return GetStruct<WBIN::UInt2 *>(VT_TILE_COUNT);
  }
  const WBIN::UInt2 *tile_resolution() const {
    return GetStruct<const WBIN::UInt2 *>(VT_TILE_RESOLUTION);
  }
  WBIN::UInt2 *mutable_tile_resolution() {
    return GetStruct<WBIN::UInt2 *>(VT_TILE_RESOLUTION);
  }
  const WBIN::Float2 *tile_meter_size() const {
    return GetStruct<const WBIN::Float2 *>(VT_TILE_METER_SIZE);
  }
  WBIN::Float2 *mutable_tile_meter_size() {
    return GetStruct<WBIN::Float2 *>(VT_TILE_METER_SIZE);
  }
  const flatbuffers::Vector<flatbuffers::Offset<WBIN::TileRef>> *tiles() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<WBIN::TileRef>> *>(VT_TILES);
  }
  flatbuffers::Vector<flatbuffers::Offset<WBIN::TileRef>> *mutable_tiles() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<WBIN::TileRef>> *>(VT_TILES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyFieldRequired<WBIN::UInt2>(verifier, VT_TILE_COUNT) &&
           VerifyFieldRequired<WBIN::UInt2>(verifier, VT_TILE_RESOLUTION) &&
           VerifyFieldRequired<WBIN::Float2>(verifier, VT_TILE_METER_SIZE) &&
           VerifyOffsetRequired(verifier, VT_TILES) &&
           verifier.VerifyVector(tiles()) &&
           verifier.VerifyVectorOfTables(tiles()) &&
           verifier.EndTable();
  }
  TileDBT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(TileDBT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<TileDB> Pack(flatbuffers::FlatBufferBuilder &_fbb, const TileDBT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct TileDBBuilder {
  typedef TileDB Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_tile_count(const WBIN::UInt2 *tile_count) {
    fbb_.AddStruct(TileDB::VT_TILE_COUNT, tile_count);
  }
  void add_tile_resolution(const WBIN::UInt2 *tile_resolution) {
    fbb_.AddStruct(TileDB::VT_TILE_RESOLUTION, tile_resolution);
  }
  void add_tile_meter_size(const WBIN::Float2 *tile_meter_size) {
    fbb_.AddStruct(TileDB::VT_TILE_METER_SIZE, tile_meter_size);
  }
  void add_tiles(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::TileRef>>> tiles) {
    fbb_.AddOffset(TileDB::VT_TILES, tiles);
  }
  explicit TileDBBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<TileDB> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<TileDB>(end);
    fbb_.Required(o, TileDB::VT_TILE_COUNT);
    fbb_.Required(o, TileDB::VT_TILE_RESOLUTION);
    fbb_.Required(o, TileDB::VT_TILE_METER_SIZE);
    fbb_.Required(o, TileDB::VT_TILES);
    return o;
  }
};

inline flatbuffers::Offset<TileDB> CreateTileDB(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::UInt2 *tile_count = 0,
    const WBIN::UInt2 *tile_resolution = 0,
    const WBIN::Float2 *tile_meter_size = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::TileRef>>> tiles = 0) {
  TileDBBuilder builder_(_fbb);
  builder_.add_tiles(tiles);
  builder_.add_tile_meter_size(tile_meter_size);
  builder_.add_tile_resolution(tile_resolution);
  builder_.add_tile_count(tile_count);
  return builder_.Finish();
}

inline flatbuffers::Offset<TileDB> CreateTileDBDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const WBIN::UInt2 *tile_count = 0,
    const WBIN::UInt2 *tile_resolution = 0,
    const WBIN::Float2 *tile_meter_size = 0,
    const std::vector<flatbuffers::Offset<WBIN::TileRef>> *tiles = nullptr) {
  auto tiles__ = tiles ? _fbb.CreateVector<flatbuffers::Offset<WBIN::TileRef>>(*tiles) : 0;
  return WBIN::CreateTileDB(
      _fbb,
      tile_count,
      tile_resolution,
      tile_meter_size,
      tiles__);
}

flatbuffers::Offset<TileDB> CreateTileDB(flatbuffers::FlatBufferBuilder &_fbb, const TileDBT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline TileRefT *TileRef::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<TileRefT>(new TileRefT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void TileRef::UnPackTo(TileRefT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = coordinates(); if (_e) _o->coordinates = std::unique_ptr<WBIN::UInt2>(new WBIN::UInt2(*_e)); }
  { auto _e = path(); if (_e) _o->path = _e->str(); }
}

inline flatbuffers::Offset<TileRef> TileRef::Pack(flatbuffers::FlatBufferBuilder &_fbb, const TileRefT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateTileRef(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<TileRef> CreateTileRef(flatbuffers::FlatBufferBuilder &_fbb, const TileRefT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const TileRefT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _coordinates = _o->coordinates ? _o->coordinates.get() : 0;
  auto _path = _o->path.empty() ? 0 : _fbb.CreateString(_o->path);
  return WBIN::CreateTileRef(
      _fbb,
      _coordinates,
      _path);
}

inline TileDBT *TileDB::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<TileDBT>(new TileDBT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void TileDB::UnPackTo(TileDBT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = tile_count(); if (_e) _o->tile_count = std::unique_ptr<WBIN::UInt2>(new WBIN::UInt2(*_e)); }
  { auto _e = tile_resolution(); if (_e) _o->tile_resolution = std::unique_ptr<WBIN::UInt2>(new WBIN::UInt2(*_e)); }
  { auto _e = tile_meter_size(); if (_e) _o->tile_meter_size = std::unique_ptr<WBIN::Float2>(new WBIN::Float2(*_e)); }
  { auto _e = tiles(); if (_e) { _o->tiles.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->tiles[_i] = std::unique_ptr<WBIN::TileRefT>(_e->Get(_i)->UnPack(_resolver)); } } }
}

inline flatbuffers::Offset<TileDB> TileDB::Pack(flatbuffers::FlatBufferBuilder &_fbb, const TileDBT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateTileDB(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<TileDB> CreateTileDB(flatbuffers::FlatBufferBuilder &_fbb, const TileDBT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const TileDBT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _tile_count = _o->tile_count ? _o->tile_count.get() : 0;
  auto _tile_resolution = _o->tile_resolution ? _o->tile_resolution.get() : 0;
  auto _tile_meter_size = _o->tile_meter_size ? _o->tile_meter_size.get() : 0;
  auto _tiles = _fbb.CreateVector<flatbuffers::Offset<WBIN::TileRef>> (_o->tiles.size(), [](size_t i, _VectorArgs *__va) { return CreateTileRef(*__va->__fbb, __va->__o->tiles[i].get(), __va->__rehasher); }, &_va );
  return WBIN::CreateTileDB(
      _fbb,
      _tile_count,
      _tile_resolution,
      _tile_meter_size,
      _tiles);
}

inline const WBIN::TileDB *GetTileDB(const void *buf) {
  return flatbuffers::GetRoot<WBIN::TileDB>(buf);
}

inline const WBIN::TileDB *GetSizePrefixedTileDB(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::TileDB>(buf);
}

inline TileDB *GetMutableTileDB(void *buf) {
  return flatbuffers::GetMutableRoot<TileDB>(buf);
}

inline bool VerifyTileDBBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::TileDB>(nullptr);
}

inline bool VerifySizePrefixedTileDBBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::TileDB>(nullptr);
}

inline void FinishTileDBBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::TileDB> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedTileDBBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::TileDB> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::TileDBT> UnPackTileDB(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::TileDBT>(GetTileDB(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::TileDBT> UnPackSizePrefixedTileDB(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::TileDBT>(GetSizePrefixedTileDB(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WHEIGHTMAPTILEDB_WBIN_H_
