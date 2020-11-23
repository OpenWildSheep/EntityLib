// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_POSITION_WILDRPC_H_
#define FLATBUFFERS_GENERATED_POSITION_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

#include "Vector3_generated.h"

namespace WildRPC {

struct Position;
struct PositionBuilder;

struct Position FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PositionBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_WORLDCELLX = 4,
    VT_WORLDCELLY = 6,
    VT_LOCALPOSITION = 8
  };
  uint32_t worldCellX() const {
    return GetField<uint32_t>(VT_WORLDCELLX, 0);
  }
  uint32_t worldCellY() const {
    return GetField<uint32_t>(VT_WORLDCELLY, 0);
  }
  const WildRPC::Vector3 *localPosition() const {
    return GetPointer<const WildRPC::Vector3 *>(VT_LOCALPOSITION);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_WORLDCELLX) &&
           VerifyField<uint32_t>(verifier, VT_WORLDCELLY) &&
           VerifyOffset(verifier, VT_LOCALPOSITION) &&
           verifier.VerifyTable(localPosition()) &&
           verifier.EndTable();
  }
};

struct PositionBuilder {
  typedef Position Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_worldCellX(uint32_t worldCellX) {
    fbb_.AddElement<uint32_t>(Position::VT_WORLDCELLX, worldCellX, 0);
  }
  void add_worldCellY(uint32_t worldCellY) {
    fbb_.AddElement<uint32_t>(Position::VT_WORLDCELLY, worldCellY, 0);
  }
  void add_localPosition(flatbuffers::Offset<WildRPC::Vector3> localPosition) {
    fbb_.AddOffset(Position::VT_LOCALPOSITION, localPosition);
  }
  explicit PositionBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PositionBuilder &operator=(const PositionBuilder &);
  flatbuffers::Offset<Position> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Position>(end);
    return o;
  }
};

inline flatbuffers::Offset<Position> CreatePosition(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t worldCellX = 0,
    uint32_t worldCellY = 0,
    flatbuffers::Offset<WildRPC::Vector3> localPosition = 0) {
  PositionBuilder builder_(_fbb);
  builder_.add_localPosition(localPosition);
  builder_.add_worldCellY(worldCellY);
  builder_.add_worldCellX(worldCellX);
  return builder_.Finish();
}

inline const WildRPC::Position *GetPosition(const void *buf) {
  return flatbuffers::GetRoot<WildRPC::Position>(buf);
}

inline const WildRPC::Position *GetSizePrefixedPosition(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WildRPC::Position>(buf);
}

inline bool VerifyPositionBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WildRPC::Position>(nullptr);
}

inline bool VerifySizePrefixedPositionBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WildRPC::Position>(nullptr);
}

inline void FinishPositionBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::Position> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedPositionBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::Position> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace WildRPC

#endif  // FLATBUFFERS_GENERATED_POSITION_WILDRPC_H_