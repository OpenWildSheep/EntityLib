// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WANM_WBIN_H_
#define FLATBUFFERS_GENERATED_WANM_WBIN_H_

#include "flatbuffers/flatbuffers.h"

#include "wbin_generated.h"

namespace WBIN {

struct BoneAnimation;
struct BoneAnimationBuilder;
struct BoneAnimationT;

struct Animation;
struct AnimationBuilder;
struct AnimationT;

struct BoneAnimationT : public flatbuffers::NativeTable {
  typedef BoneAnimation TableType;
  std::string name{};
  std::vector<WBIN::Float3> translations{};
  std::vector<WBIN::Float4> orientations{};
  std::vector<WBIN::Float3> scales{};
};

struct BoneAnimation FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef BoneAnimationT NativeTableType;
  typedef BoneAnimationBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_TRANSLATIONS = 6,
    VT_ORIENTATIONS = 8,
    VT_SCALES = 10
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  flatbuffers::String *mutable_name() {
    return GetPointer<flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::Vector<const WBIN::Float3 *> *translations() const {
    return GetPointer<const flatbuffers::Vector<const WBIN::Float3 *> *>(VT_TRANSLATIONS);
  }
  flatbuffers::Vector<const WBIN::Float3 *> *mutable_translations() {
    return GetPointer<flatbuffers::Vector<const WBIN::Float3 *> *>(VT_TRANSLATIONS);
  }
  const flatbuffers::Vector<const WBIN::Float4 *> *orientations() const {
    return GetPointer<const flatbuffers::Vector<const WBIN::Float4 *> *>(VT_ORIENTATIONS);
  }
  flatbuffers::Vector<const WBIN::Float4 *> *mutable_orientations() {
    return GetPointer<flatbuffers::Vector<const WBIN::Float4 *> *>(VT_ORIENTATIONS);
  }
  const flatbuffers::Vector<const WBIN::Float3 *> *scales() const {
    return GetPointer<const flatbuffers::Vector<const WBIN::Float3 *> *>(VT_SCALES);
  }
  flatbuffers::Vector<const WBIN::Float3 *> *mutable_scales() {
    return GetPointer<flatbuffers::Vector<const WBIN::Float3 *> *>(VT_SCALES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_TRANSLATIONS) &&
           verifier.VerifyVector(translations()) &&
           VerifyOffset(verifier, VT_ORIENTATIONS) &&
           verifier.VerifyVector(orientations()) &&
           VerifyOffset(verifier, VT_SCALES) &&
           verifier.VerifyVector(scales()) &&
           verifier.EndTable();
  }
  BoneAnimationT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(BoneAnimationT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<BoneAnimation> Pack(flatbuffers::FlatBufferBuilder &_fbb, const BoneAnimationT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct BoneAnimationBuilder {
  typedef BoneAnimation Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(BoneAnimation::VT_NAME, name);
  }
  void add_translations(flatbuffers::Offset<flatbuffers::Vector<const WBIN::Float3 *>> translations) {
    fbb_.AddOffset(BoneAnimation::VT_TRANSLATIONS, translations);
  }
  void add_orientations(flatbuffers::Offset<flatbuffers::Vector<const WBIN::Float4 *>> orientations) {
    fbb_.AddOffset(BoneAnimation::VT_ORIENTATIONS, orientations);
  }
  void add_scales(flatbuffers::Offset<flatbuffers::Vector<const WBIN::Float3 *>> scales) {
    fbb_.AddOffset(BoneAnimation::VT_SCALES, scales);
  }
  explicit BoneAnimationBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<BoneAnimation> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<BoneAnimation>(end);
    fbb_.Required(o, BoneAnimation::VT_NAME);
    return o;
  }
};

inline flatbuffers::Offset<BoneAnimation> CreateBoneAnimation(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::Vector<const WBIN::Float3 *>> translations = 0,
    flatbuffers::Offset<flatbuffers::Vector<const WBIN::Float4 *>> orientations = 0,
    flatbuffers::Offset<flatbuffers::Vector<const WBIN::Float3 *>> scales = 0) {
  BoneAnimationBuilder builder_(_fbb);
  builder_.add_scales(scales);
  builder_.add_orientations(orientations);
  builder_.add_translations(translations);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<BoneAnimation> CreateBoneAnimationDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const std::vector<WBIN::Float3> *translations = nullptr,
    const std::vector<WBIN::Float4> *orientations = nullptr,
    const std::vector<WBIN::Float3> *scales = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto translations__ = translations ? _fbb.CreateVectorOfStructs<WBIN::Float3>(*translations) : 0;
  auto orientations__ = orientations ? _fbb.CreateVectorOfStructs<WBIN::Float4>(*orientations) : 0;
  auto scales__ = scales ? _fbb.CreateVectorOfStructs<WBIN::Float3>(*scales) : 0;
  return WBIN::CreateBoneAnimation(
      _fbb,
      name__,
      translations__,
      orientations__,
      scales__);
}

flatbuffers::Offset<BoneAnimation> CreateBoneAnimation(flatbuffers::FlatBufferBuilder &_fbb, const BoneAnimationT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct AnimationT : public flatbuffers::NativeTable {
  typedef Animation TableType;
  float frame_rate = 0.0f;
  std::vector<std::unique_ptr<WBIN::BoneAnimationT>> bone_animations{};
};

struct Animation FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef AnimationT NativeTableType;
  typedef AnimationBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_FRAME_RATE = 4,
    VT_BONE_ANIMATIONS = 6
  };
  float frame_rate() const {
    return GetField<float>(VT_FRAME_RATE, 0.0f);
  }
  bool mutate_frame_rate(float _frame_rate) {
    return SetField<float>(VT_FRAME_RATE, _frame_rate, 0.0f);
  }
  const flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneAnimation>> *bone_animations() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneAnimation>> *>(VT_BONE_ANIMATIONS);
  }
  flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneAnimation>> *mutable_bone_animations() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneAnimation>> *>(VT_BONE_ANIMATIONS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_FRAME_RATE) &&
           VerifyOffsetRequired(verifier, VT_BONE_ANIMATIONS) &&
           verifier.VerifyVector(bone_animations()) &&
           verifier.VerifyVectorOfTables(bone_animations()) &&
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
  void add_frame_rate(float frame_rate) {
    fbb_.AddElement<float>(Animation::VT_FRAME_RATE, frame_rate, 0.0f);
  }
  void add_bone_animations(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneAnimation>>> bone_animations) {
    fbb_.AddOffset(Animation::VT_BONE_ANIMATIONS, bone_animations);
  }
  explicit AnimationBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Animation> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Animation>(end);
    fbb_.Required(o, Animation::VT_BONE_ANIMATIONS);
    return o;
  }
};

inline flatbuffers::Offset<Animation> CreateAnimation(
    flatbuffers::FlatBufferBuilder &_fbb,
    float frame_rate = 0.0f,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<WBIN::BoneAnimation>>> bone_animations = 0) {
  AnimationBuilder builder_(_fbb);
  builder_.add_bone_animations(bone_animations);
  builder_.add_frame_rate(frame_rate);
  return builder_.Finish();
}

inline flatbuffers::Offset<Animation> CreateAnimationDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    float frame_rate = 0.0f,
    const std::vector<flatbuffers::Offset<WBIN::BoneAnimation>> *bone_animations = nullptr) {
  auto bone_animations__ = bone_animations ? _fbb.CreateVector<flatbuffers::Offset<WBIN::BoneAnimation>>(*bone_animations) : 0;
  return WBIN::CreateAnimation(
      _fbb,
      frame_rate,
      bone_animations__);
}

flatbuffers::Offset<Animation> CreateAnimation(flatbuffers::FlatBufferBuilder &_fbb, const AnimationT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline BoneAnimationT *BoneAnimation::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<BoneAnimationT>(new BoneAnimationT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void BoneAnimation::UnPackTo(BoneAnimationT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = name(); if (_e) _o->name = _e->str(); }
  { auto _e = translations(); if (_e) { _o->translations.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->translations[_i] = *_e->Get(_i); } } }
  { auto _e = orientations(); if (_e) { _o->orientations.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->orientations[_i] = *_e->Get(_i); } } }
  { auto _e = scales(); if (_e) { _o->scales.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->scales[_i] = *_e->Get(_i); } } }
}

inline flatbuffers::Offset<BoneAnimation> BoneAnimation::Pack(flatbuffers::FlatBufferBuilder &_fbb, const BoneAnimationT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateBoneAnimation(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<BoneAnimation> CreateBoneAnimation(flatbuffers::FlatBufferBuilder &_fbb, const BoneAnimationT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const BoneAnimationT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _name = _fbb.CreateString(_o->name);
  auto _translations = _o->translations.size() ? _fbb.CreateVectorOfStructs(_o->translations) : 0;
  auto _orientations = _o->orientations.size() ? _fbb.CreateVectorOfStructs(_o->orientations) : 0;
  auto _scales = _o->scales.size() ? _fbb.CreateVectorOfStructs(_o->scales) : 0;
  return WBIN::CreateBoneAnimation(
      _fbb,
      _name,
      _translations,
      _orientations,
      _scales);
}

inline AnimationT *Animation::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<AnimationT>(new AnimationT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Animation::UnPackTo(AnimationT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = frame_rate(); _o->frame_rate = _e; }
  { auto _e = bone_animations(); if (_e) { _o->bone_animations.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bone_animations[_i] = std::unique_ptr<WBIN::BoneAnimationT>(_e->Get(_i)->UnPack(_resolver)); } } }
}

inline flatbuffers::Offset<Animation> Animation::Pack(flatbuffers::FlatBufferBuilder &_fbb, const AnimationT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateAnimation(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Animation> CreateAnimation(flatbuffers::FlatBufferBuilder &_fbb, const AnimationT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const AnimationT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _frame_rate = _o->frame_rate;
  auto _bone_animations = _fbb.CreateVector<flatbuffers::Offset<WBIN::BoneAnimation>> (_o->bone_animations.size(), [](size_t i, _VectorArgs *__va) { return CreateBoneAnimation(*__va->__fbb, __va->__o->bone_animations[i].get(), __va->__rehasher); }, &_va );
  return WBIN::CreateAnimation(
      _fbb,
      _frame_rate,
      _bone_animations);
}

inline const WBIN::Animation *GetAnimation(const void *buf) {
  return flatbuffers::GetRoot<WBIN::Animation>(buf);
}

inline const WBIN::Animation *GetSizePrefixedAnimation(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<WBIN::Animation>(buf);
}

inline Animation *GetMutableAnimation(void *buf) {
  return flatbuffers::GetMutableRoot<Animation>(buf);
}

inline bool VerifyAnimationBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<WBIN::Animation>(nullptr);
}

inline bool VerifySizePrefixedAnimationBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<WBIN::Animation>(nullptr);
}

inline void FinishAnimationBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::Animation> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedAnimationBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<WBIN::Animation> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<WBIN::AnimationT> UnPackAnimation(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::AnimationT>(GetAnimation(buf)->UnPack(res));
}

inline std::unique_ptr<WBIN::AnimationT> UnPackSizePrefixedAnimation(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<WBIN::AnimationT>(GetSizePrefixedAnimation(buf)->UnPack(res));
}

}  // namespace WBIN

#endif  // FLATBUFFERS_GENERATED_WANM_WBIN_H_