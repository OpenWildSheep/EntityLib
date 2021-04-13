// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CAMERA_WILDRPC_H_
#define FLATBUFFERS_GENERATED_CAMERA_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

#include "Position_generated.h"
#include "Quat_generated.h"
#include "Vector3_generated.h"

namespace WildRPC {

struct Camera;
struct CameraBuilder;

struct Camera FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef CameraBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POSITION = 4,
    VT_ORIENTATION = 6
  };
  const WildRPC::Position *position() const {
    return GetPointer<const WildRPC::Position *>(VT_POSITION);
  }
  const WildRPC::Quat *orientation() const {
    return GetPointer<const WildRPC::Quat *>(VT_ORIENTATION);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_POSITION) &&
           verifier.VerifyTable(position()) &&
           VerifyOffset(verifier, VT_ORIENTATION) &&
           verifier.VerifyTable(orientation()) &&
           verifier.EndTable();
  }
};

struct CameraBuilder {
  typedef Camera Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_position(flatbuffers::Offset<WildRPC::Position> position) {
    fbb_.AddOffset(Camera::VT_POSITION, position);
  }
  void add_orientation(flatbuffers::Offset<WildRPC::Quat> orientation) {
    fbb_.AddOffset(Camera::VT_ORIENTATION, orientation);
  }
  explicit CameraBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Camera> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Camera>(end);
    return o;
  }
};

inline flatbuffers::Offset<Camera> CreateCamera(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<WildRPC::Position> position = 0,
    flatbuffers::Offset<WildRPC::Quat> orientation = 0) {
  CameraBuilder builder_(_fbb);
  builder_.add_orientation(orientation);
  builder_.add_position(position);
  return builder_.Finish();
}

inline const WildRPC::Camera *GetCamera(const void *buf) {
  return flatbuffers::GetRoot<WildRPC::Camera>(buf);
}

inline const WildRPC::Camera *GetSizePrefixedCamera(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WildRPC::Camera>(buf);
}

inline bool VerifyCameraBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WildRPC::Camera>(nullptr);
}

inline bool VerifySizePrefixedCameraBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WildRPC::Camera>(nullptr);
}

inline void FinishCameraBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::Camera> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedCameraBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WildRPC::Camera> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace WildRPC

#endif  // FLATBUFFERS_GENERATED_CAMERA_WILDRPC_H_
