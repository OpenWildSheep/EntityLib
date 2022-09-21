// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WMAXANM_MAX_H_
#define FLATBUFFERS_GENERATED_WMAXANM_MAX_H_

#include "flatbuffers/flatbuffers.h"

namespace MAX {

struct Keyframe;
struct KeyframeBuilder;
struct KeyframeT;

struct Animation;
struct AnimationBuilder;
struct AnimationT;

enum TangentType : int8_t {
  TangentType_Smooth = 1,
  TangentType_Linear = 2,
  TangentType_Step = 3,
  TangentType_Slow = 4,
  TangentType_Fast = 5,
  TangentType_Custom = 6,
  TangentType_Auto = 7,
  TangentType_MIN = TangentType_Smooth,
  TangentType_MAX = TangentType_Auto
};

inline const TangentType (&EnumValuesTangentType())[7] {
  static const TangentType values[] = {
    TangentType_Smooth,
    TangentType_Linear,
    TangentType_Step,
    TangentType_Slow,
    TangentType_Fast,
    TangentType_Custom,
    TangentType_Auto
  };
  return values;
}

inline const char * const *EnumNamesTangentType() {
  static const char * const names[8] = {
    "Smooth",
    "Linear",
    "Step",
    "Slow",
    "Fast",
    "Custom",
    "Auto",
    nullptr
  };
  return names;
}

inline const char *EnumNameTangentType(TangentType e) {
  if (flatbuffers::IsOutRange(e, TangentType_Smooth, TangentType_Auto)) return "";
  const size_t index = static_cast<size_t>(e) - static_cast<size_t>(TangentType_Smooth);
  return EnumNamesTangentType()[index];
}

struct KeyframeT : public flatbuffers::NativeTable {
  typedef Keyframe TableType;
  float time = 0.0f;
  float value = 0.0f;
  float tan_in = 0.0f;
  float tan_out = 0.0f;
  MAX::TangentType tan_type_in = MAX::TangentType_Auto;
  MAX::TangentType tan_type_out = MAX::TangentType_Auto;
};

struct Keyframe FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef KeyframeT NativeTableType;
  typedef KeyframeBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TIME = 4,
    VT_VALUE = 6,
    VT_TAN_IN = 8,
    VT_TAN_OUT = 10,
    VT_TAN_TYPE_IN = 12,
    VT_TAN_TYPE_OUT = 14
  };
  float time() const {
    return GetField<float>(VT_TIME, 0.0f);
  }
  bool mutate_time(float _time) {
    return SetField<float>(VT_TIME, _time, 0.0f);
  }
  float value() const {
    return GetField<float>(VT_VALUE, 0.0f);
  }
  bool mutate_value(float _value) {
    return SetField<float>(VT_VALUE, _value, 0.0f);
  }
  float tan_in() const {
    return GetField<float>(VT_TAN_IN, 0.0f);
  }
  bool mutate_tan_in(float _tan_in) {
    return SetField<float>(VT_TAN_IN, _tan_in, 0.0f);
  }
  float tan_out() const {
    return GetField<float>(VT_TAN_OUT, 0.0f);
  }
  bool mutate_tan_out(float _tan_out) {
    return SetField<float>(VT_TAN_OUT, _tan_out, 0.0f);
  }
  MAX::TangentType tan_type_in() const {
    return static_cast<MAX::TangentType>(GetField<int8_t>(VT_TAN_TYPE_IN, 7));
  }
  bool mutate_tan_type_in(MAX::TangentType _tan_type_in) {
    return SetField<int8_t>(VT_TAN_TYPE_IN, static_cast<int8_t>(_tan_type_in), 7);
  }
  MAX::TangentType tan_type_out() const {
    return static_cast<MAX::TangentType>(GetField<int8_t>(VT_TAN_TYPE_OUT, 7));
  }
  bool mutate_tan_type_out(MAX::TangentType _tan_type_out) {
    return SetField<int8_t>(VT_TAN_TYPE_OUT, static_cast<int8_t>(_tan_type_out), 7);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_TIME) &&
           VerifyField<float>(verifier, VT_VALUE) &&
           VerifyField<float>(verifier, VT_TAN_IN) &&
           VerifyField<float>(verifier, VT_TAN_OUT) &&
           VerifyField<int8_t>(verifier, VT_TAN_TYPE_IN) &&
           VerifyField<int8_t>(verifier, VT_TAN_TYPE_OUT) &&
           verifier.EndTable();
  }
  KeyframeT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(KeyframeT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Keyframe> Pack(flatbuffers::FlatBufferBuilder &_fbb, const KeyframeT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct KeyframeBuilder {
  typedef Keyframe Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_time(float time) {
    fbb_.AddElement<float>(Keyframe::VT_TIME, time, 0.0f);
  }
  void add_value(float value) {
    fbb_.AddElement<float>(Keyframe::VT_VALUE, value, 0.0f);
  }
  void add_tan_in(float tan_in) {
    fbb_.AddElement<float>(Keyframe::VT_TAN_IN, tan_in, 0.0f);
  }
  void add_tan_out(float tan_out) {
    fbb_.AddElement<float>(Keyframe::VT_TAN_OUT, tan_out, 0.0f);
  }
  void add_tan_type_in(MAX::TangentType tan_type_in) {
    fbb_.AddElement<int8_t>(Keyframe::VT_TAN_TYPE_IN, static_cast<int8_t>(tan_type_in), 7);
  }
  void add_tan_type_out(MAX::TangentType tan_type_out) {
    fbb_.AddElement<int8_t>(Keyframe::VT_TAN_TYPE_OUT, static_cast<int8_t>(tan_type_out), 7);
  }
  explicit KeyframeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Keyframe> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Keyframe>(end);
    return o;
  }
};

inline flatbuffers::Offset<Keyframe> CreateKeyframe(
    flatbuffers::FlatBufferBuilder &_fbb,
    float time = 0.0f,
    float value = 0.0f,
    float tan_in = 0.0f,
    float tan_out = 0.0f,
    MAX::TangentType tan_type_in = MAX::TangentType_Auto,
    MAX::TangentType tan_type_out = MAX::TangentType_Auto) {
  KeyframeBuilder builder_(_fbb);
  builder_.add_tan_out(tan_out);
  builder_.add_tan_in(tan_in);
  builder_.add_value(value);
  builder_.add_time(time);
  builder_.add_tan_type_out(tan_type_out);
  builder_.add_tan_type_in(tan_type_in);
  return builder_.Finish();
}

flatbuffers::Offset<Keyframe> CreateKeyframe(flatbuffers::FlatBufferBuilder &_fbb, const KeyframeT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct AnimationT : public flatbuffers::NativeTable {
  typedef Animation TableType;
  std::vector<std::unique_ptr<MAX::KeyframeT>> position_x{};
  std::vector<std::unique_ptr<MAX::KeyframeT>> position_y{};
  std::vector<std::unique_ptr<MAX::KeyframeT>> position_z{};
  std::vector<std::unique_ptr<MAX::KeyframeT>> orientation_x{};
  std::vector<std::unique_ptr<MAX::KeyframeT>> orientation_y{};
  std::vector<std::unique_ptr<MAX::KeyframeT>> orientation_z{};
  std::vector<std::unique_ptr<MAX::KeyframeT>> scale{};
};

struct Animation FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef AnimationT NativeTableType;
  typedef AnimationBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POSITION_X = 4,
    VT_POSITION_Y = 6,
    VT_POSITION_Z = 8,
    VT_ORIENTATION_X = 10,
    VT_ORIENTATION_Y = 12,
    VT_ORIENTATION_Z = 14,
    VT_SCALE = 16
  };
  const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *position_x() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_POSITION_X);
  }
  flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *mutable_position_x() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_POSITION_X);
  }
  const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *position_y() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_POSITION_Y);
  }
  flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *mutable_position_y() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_POSITION_Y);
  }
  const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *position_z() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_POSITION_Z);
  }
  flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *mutable_position_z() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_POSITION_Z);
  }
  const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *orientation_x() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_ORIENTATION_X);
  }
  flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *mutable_orientation_x() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_ORIENTATION_X);
  }
  const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *orientation_y() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_ORIENTATION_Y);
  }
  flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *mutable_orientation_y() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_ORIENTATION_Y);
  }
  const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *orientation_z() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_ORIENTATION_Z);
  }
  flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *mutable_orientation_z() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_ORIENTATION_Z);
  }
  const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *scale() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_SCALE);
  }
  flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *mutable_scale() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>> *>(VT_SCALE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_POSITION_X) &&
           verifier.VerifyVector(position_x()) &&
           verifier.VerifyVectorOfTables(position_x()) &&
           VerifyOffset(verifier, VT_POSITION_Y) &&
           verifier.VerifyVector(position_y()) &&
           verifier.VerifyVectorOfTables(position_y()) &&
           VerifyOffset(verifier, VT_POSITION_Z) &&
           verifier.VerifyVector(position_z()) &&
           verifier.VerifyVectorOfTables(position_z()) &&
           VerifyOffset(verifier, VT_ORIENTATION_X) &&
           verifier.VerifyVector(orientation_x()) &&
           verifier.VerifyVectorOfTables(orientation_x()) &&
           VerifyOffset(verifier, VT_ORIENTATION_Y) &&
           verifier.VerifyVector(orientation_y()) &&
           verifier.VerifyVectorOfTables(orientation_y()) &&
           VerifyOffset(verifier, VT_ORIENTATION_Z) &&
           verifier.VerifyVector(orientation_z()) &&
           verifier.VerifyVectorOfTables(orientation_z()) &&
           VerifyOffset(verifier, VT_SCALE) &&
           verifier.VerifyVector(scale()) &&
           verifier.VerifyVectorOfTables(scale()) &&
           verifier.EndTable();
  }
  AnimationT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(AnimationT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Animation> Pack(flatbuffers::FlatBufferBuilder &_fbb, const AnimationT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct AnimationBuilder {
  typedef Animation Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_position_x(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> position_x) {
    fbb_.AddOffset(Animation::VT_POSITION_X, position_x);
  }
  void add_position_y(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> position_y) {
    fbb_.AddOffset(Animation::VT_POSITION_Y, position_y);
  }
  void add_position_z(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> position_z) {
    fbb_.AddOffset(Animation::VT_POSITION_Z, position_z);
  }
  void add_orientation_x(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> orientation_x) {
    fbb_.AddOffset(Animation::VT_ORIENTATION_X, orientation_x);
  }
  void add_orientation_y(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> orientation_y) {
    fbb_.AddOffset(Animation::VT_ORIENTATION_Y, orientation_y);
  }
  void add_orientation_z(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> orientation_z) {
    fbb_.AddOffset(Animation::VT_ORIENTATION_Z, orientation_z);
  }
  void add_scale(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> scale) {
    fbb_.AddOffset(Animation::VT_SCALE, scale);
  }
  explicit AnimationBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Animation> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Animation>(end);
    return o;
  }
};

inline flatbuffers::Offset<Animation> CreateAnimation(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> position_x = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> position_y = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> position_z = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> orientation_x = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> orientation_y = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> orientation_z = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MAX::Keyframe>>> scale = 0) {
  AnimationBuilder builder_(_fbb);
  builder_.add_scale(scale);
  builder_.add_orientation_z(orientation_z);
  builder_.add_orientation_y(orientation_y);
  builder_.add_orientation_x(orientation_x);
  builder_.add_position_z(position_z);
  builder_.add_position_y(position_y);
  builder_.add_position_x(position_x);
  return builder_.Finish();
}

inline flatbuffers::Offset<Animation> CreateAnimationDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<MAX::Keyframe>> *position_x = nullptr,
    const std::vector<flatbuffers::Offset<MAX::Keyframe>> *position_y = nullptr,
    const std::vector<flatbuffers::Offset<MAX::Keyframe>> *position_z = nullptr,
    const std::vector<flatbuffers::Offset<MAX::Keyframe>> *orientation_x = nullptr,
    const std::vector<flatbuffers::Offset<MAX::Keyframe>> *orientation_y = nullptr,
    const std::vector<flatbuffers::Offset<MAX::Keyframe>> *orientation_z = nullptr,
    const std::vector<flatbuffers::Offset<MAX::Keyframe>> *scale = nullptr) {
  auto position_x__ = position_x ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>>(*position_x) : 0;
  auto position_y__ = position_y ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>>(*position_y) : 0;
  auto position_z__ = position_z ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>>(*position_z) : 0;
  auto orientation_x__ = orientation_x ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>>(*orientation_x) : 0;
  auto orientation_y__ = orientation_y ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>>(*orientation_y) : 0;
  auto orientation_z__ = orientation_z ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>>(*orientation_z) : 0;
  auto scale__ = scale ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>>(*scale) : 0;
  return MAX::CreateAnimation(
      _fbb,
      position_x__,
      position_y__,
      position_z__,
      orientation_x__,
      orientation_y__,
      orientation_z__,
      scale__);
}

flatbuffers::Offset<Animation> CreateAnimation(flatbuffers::FlatBufferBuilder &_fbb, const AnimationT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline KeyframeT *Keyframe::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<KeyframeT>(new KeyframeT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Keyframe::UnPackTo(KeyframeT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = time(); _o->time = _e; }
  { auto _e = value(); _o->value = _e; }
  { auto _e = tan_in(); _o->tan_in = _e; }
  { auto _e = tan_out(); _o->tan_out = _e; }
  { auto _e = tan_type_in(); _o->tan_type_in = _e; }
  { auto _e = tan_type_out(); _o->tan_type_out = _e; }
}

inline flatbuffers::Offset<Keyframe> Keyframe::Pack(flatbuffers::FlatBufferBuilder &_fbb, const KeyframeT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateKeyframe(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Keyframe> CreateKeyframe(flatbuffers::FlatBufferBuilder &_fbb, const KeyframeT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const KeyframeT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _time = _o->time;
  auto _value = _o->value;
  auto _tan_in = _o->tan_in;
  auto _tan_out = _o->tan_out;
  auto _tan_type_in = _o->tan_type_in;
  auto _tan_type_out = _o->tan_type_out;
  return MAX::CreateKeyframe(
      _fbb,
      _time,
      _value,
      _tan_in,
      _tan_out,
      _tan_type_in,
      _tan_type_out);
}

inline AnimationT *Animation::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<AnimationT>(new AnimationT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Animation::UnPackTo(AnimationT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = position_x(); if (_e) { _o->position_x.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->position_x[_i] = std::unique_ptr<MAX::KeyframeT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = position_y(); if (_e) { _o->position_y.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->position_y[_i] = std::unique_ptr<MAX::KeyframeT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = position_z(); if (_e) { _o->position_z.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->position_z[_i] = std::unique_ptr<MAX::KeyframeT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = orientation_x(); if (_e) { _o->orientation_x.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->orientation_x[_i] = std::unique_ptr<MAX::KeyframeT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = orientation_y(); if (_e) { _o->orientation_y.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->orientation_y[_i] = std::unique_ptr<MAX::KeyframeT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = orientation_z(); if (_e) { _o->orientation_z.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->orientation_z[_i] = std::unique_ptr<MAX::KeyframeT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = scale(); if (_e) { _o->scale.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->scale[_i] = std::unique_ptr<MAX::KeyframeT>(_e->Get(_i)->UnPack(_resolver)); } } }
}

inline flatbuffers::Offset<Animation> Animation::Pack(flatbuffers::FlatBufferBuilder &_fbb, const AnimationT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateAnimation(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Animation> CreateAnimation(flatbuffers::FlatBufferBuilder &_fbb, const AnimationT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const AnimationT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _position_x = _o->position_x.size() ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>> (_o->position_x.size(), [](size_t i, _VectorArgs *__va) { return CreateKeyframe(*__va->__fbb, __va->__o->position_x[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _position_y = _o->position_y.size() ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>> (_o->position_y.size(), [](size_t i, _VectorArgs *__va) { return CreateKeyframe(*__va->__fbb, __va->__o->position_y[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _position_z = _o->position_z.size() ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>> (_o->position_z.size(), [](size_t i, _VectorArgs *__va) { return CreateKeyframe(*__va->__fbb, __va->__o->position_z[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _orientation_x = _o->orientation_x.size() ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>> (_o->orientation_x.size(), [](size_t i, _VectorArgs *__va) { return CreateKeyframe(*__va->__fbb, __va->__o->orientation_x[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _orientation_y = _o->orientation_y.size() ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>> (_o->orientation_y.size(), [](size_t i, _VectorArgs *__va) { return CreateKeyframe(*__va->__fbb, __va->__o->orientation_y[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _orientation_z = _o->orientation_z.size() ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>> (_o->orientation_z.size(), [](size_t i, _VectorArgs *__va) { return CreateKeyframe(*__va->__fbb, __va->__o->orientation_z[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _scale = _o->scale.size() ? _fbb.CreateVector<flatbuffers::Offset<MAX::Keyframe>> (_o->scale.size(), [](size_t i, _VectorArgs *__va) { return CreateKeyframe(*__va->__fbb, __va->__o->scale[i].get(), __va->__rehasher); }, &_va ) : 0;
  return MAX::CreateAnimation(
      _fbb,
      _position_x,
      _position_y,
      _position_z,
      _orientation_x,
      _orientation_y,
      _orientation_z,
      _scale);
}

inline const MAX::Animation *GetAnimation(const void *buf) {
  return flatbuffers::GetRoot<MAX::Animation>(buf);
}

inline const MAX::Animation *GetSizePrefixedAnimation(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<MAX::Animation>(buf);
}

inline Animation *GetMutableAnimation(void *buf) {
  return flatbuffers::GetMutableRoot<Animation>(buf);
}

inline bool VerifyAnimationBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<MAX::Animation>(nullptr);
}

inline bool VerifySizePrefixedAnimationBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<MAX::Animation>(nullptr);
}

inline void FinishAnimationBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MAX::Animation> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedAnimationBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MAX::Animation> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<MAX::AnimationT> UnPackAnimation(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<MAX::AnimationT>(GetAnimation(buf)->UnPack(res));
}

inline std::unique_ptr<MAX::AnimationT> UnPackSizePrefixedAnimation(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<MAX::AnimationT>(GetSizePrefixedAnimation(buf)->UnPack(res));
}

}  // namespace MAX

#endif  // FLATBUFFERS_GENERATED_WMAXANM_MAX_H_
