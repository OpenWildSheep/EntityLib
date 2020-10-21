// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WILDRPC_WILDRPC_H_
#define FLATBUFFERS_GENERATED_WILDRPC_WILDRPC_H_

#include "flatbuffers/flatbuffers.h"

namespace WildRPC {

struct UInt3;

struct Vector3;

struct Vector2;

struct Quat;

struct Position;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) UInt3 FLATBUFFERS_FINAL_CLASS {
 private:
  uint32_t x_;
  uint32_t y_;
  uint32_t z_;

 public:
  UInt3() {
    memset(static_cast<void *>(this), 0, sizeof(UInt3));
  }
  UInt3(uint32_t _x, uint32_t _y, uint32_t _z)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        z_(flatbuffers::EndianScalar(_z)) {
  }
  uint32_t x() const {
    return flatbuffers::EndianScalar(x_);
  }
  uint32_t y() const {
    return flatbuffers::EndianScalar(y_);
  }
  uint32_t z() const {
    return flatbuffers::EndianScalar(z_);
  }
};
FLATBUFFERS_STRUCT_END(UInt3, 12);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vector3 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float z_;

 public:
  Vector3() {
    memset(static_cast<void *>(this), 0, sizeof(Vector3));
  }
  Vector3(float _x, float _y, float _z)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        z_(flatbuffers::EndianScalar(_z)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
  float z() const {
    return flatbuffers::EndianScalar(z_);
  }
};
FLATBUFFERS_STRUCT_END(Vector3, 12);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vector2 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;

 public:
  Vector2() {
    memset(static_cast<void *>(this), 0, sizeof(Vector2));
  }
  Vector2(float _x, float _y)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
};
FLATBUFFERS_STRUCT_END(Vector2, 8);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Quat FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float z_;
  float w_;

 public:
  Quat() {
    memset(static_cast<void *>(this), 0, sizeof(Quat));
  }
  Quat(float _x, float _y, float _z, float _w)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        z_(flatbuffers::EndianScalar(_z)),
        w_(flatbuffers::EndianScalar(_w)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
  float z() const {
    return flatbuffers::EndianScalar(z_);
  }
  float w() const {
    return flatbuffers::EndianScalar(w_);
  }
};
FLATBUFFERS_STRUCT_END(Quat, 16);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Position FLATBUFFERS_FINAL_CLASS {
 private:
  uint32_t worldCellX_;
  uint32_t worldCellY_;
  WildRPC::Vector3 localPosition_;

 public:
  Position() {
    memset(static_cast<void *>(this), 0, sizeof(Position));
  }
  Position(uint32_t _worldCellX, uint32_t _worldCellY, const WildRPC::Vector3 &_localPosition)
      : worldCellX_(flatbuffers::EndianScalar(_worldCellX)),
        worldCellY_(flatbuffers::EndianScalar(_worldCellY)),
        localPosition_(_localPosition) {
  }
  uint32_t worldCellX() const {
    return flatbuffers::EndianScalar(worldCellX_);
  }
  uint32_t worldCellY() const {
    return flatbuffers::EndianScalar(worldCellY_);
  }
  const WildRPC::Vector3 &localPosition() const {
    return localPosition_;
  }
};
FLATBUFFERS_STRUCT_END(Position, 20);

}  // namespace WildRPC

#endif  // FLATBUFFERS_GENERATED_WILDRPC_WILDRPC_H_
