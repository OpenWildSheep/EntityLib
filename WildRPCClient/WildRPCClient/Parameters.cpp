#include "include/Parameters.h"

#pragma warning(push, 0)
#pragma warning(disable : 5045)
#include <iso646.h>
#include <variant>
#include <flatbuffers/flatbuffers.h>
#include <WiLDRPC/Color_generated.h>
#include <WiLDRPC/Quat_generated.h>
#include <WiLDRPC/Position_generated.h>
#include <WiLDRPC/Vector3_generated.h>
#include <WiLDRPC/Vector2_generated.h>
#include <WiLDRPC/Uint3_generated.h>
#include <WiLDRPC/Float_generated.h>
#include <WiLDRPC/Integer_generated.h>
#include <WiLDRPC/Boolean_generated.h>
#include <WiLDRPC/String_generated.h>
#include <WiLDRPC/RPCHeader_generated.h>
#pragma warning(pop)

using namespace WildRPC;
using namespace WRPC;
using namespace std;

typedef unsigned char u8;

namespace WRPC
{
// DECODING ------------------------------------------------------------------------

struct Decoder
{
    const u8* m_buffer;
    const size_t m_bufferSize;
    uoffset_t& m_offset;

private:
    template <typename T>
    bool DecodeInternal(T&& _decoder)
    {
        const u8* paramBuffer = &m_buffer[m_offset];
        const uoffset_t resultSize = flatbuffers::GetPrefixedSize(paramBuffer);

        if (m_offset + resultSize >= m_bufferSize)
        {
            return false;
        }

        _decoder(paramBuffer);
        m_offset += resultSize + sizeof(int);
        return true;
    }

    template <typename T, typename R>
    bool DecodeValue(T&& _decoder, R& _value)
    {
        return DecodeInternal([&](auto buf) { _value = _decoder(buf)->value(); });
    }

    template <typename T, typename R>
    bool DecodeUnPack(T* (*_decoder)(const void*), R& _value)
    {
        return DecodeInternal([&](auto buf) { _decoder(buf)->UnPackTo((T::NativeTableType*)&_value); });
    }

public:
    template<typename T> bool Decode(T& _value);

    template<typename T>
    bool DecodeVector(size_t _size, Parameter& _parameter)
    {
        _parameter.m_value = Parameter::vector<T>();
        auto& vector = _parameter.m_value.get<Parameter::vector<T>>();
        vector.reserve(_size);
        T item;
        for (size_t i = 0; i < _size; ++i)
        {
            if (not Decode<T>(item))
            {
                return false; // buffer size exceeded
            }
            vector.push_back(item);
        }
        return true;
    }

    bool DecodeParameter(Parameter& _parameter);
};

template<> bool Decoder::Decode(bool& _value) { return DecodeValue(WildRPC::GetSizePrefixedBoolean, _value); }
template<> bool Decoder::Decode(int& _value) { return DecodeValue(WildRPC::GetSizePrefixedInteger, _value); }
template<> bool Decoder::Decode(float& _value) { return DecodeValue(WildRPC::GetSizePrefixedFloat, _value); }
template<> bool Decoder::Decode(Parameter::string& _value)
{
    return DecodeInternal([&](auto buf){ _value = WildRPC::GetSizePrefixedString(buf)->value()->c_str(); });
}

template<> bool Decoder::Decode(Vector2T& _value) { return DecodeUnPack(WildRPC::GetSizePrefixedVector2, _value); }
template<> bool Decoder::Decode(UInt3T& _value) { return DecodeUnPack(WildRPC::GetSizePrefixedUInt3, _value); }
template<> bool Decoder::Decode(Vector3T& _value) { return DecodeUnPack(WildRPC::GetSizePrefixedVector3, _value); }
template<> bool Decoder::Decode(QuatT& _value) { return DecodeUnPack(WildRPC::GetSizePrefixedQuat, _value); }
template<> bool Decoder::Decode(ColorT& _value) { return DecodeUnPack(WildRPC::GetSizePrefixedColor, _value); }
//template<> bool Decoder::Decode(PositionT& _value) { return DecodeUnPack(WildRPC::GetSizePrefixedPosition, _value); }
template<> bool Decoder::Decode(Position& _value)
{
    return DecodeInternal([&](auto buf)
    {
        auto* p = WildRPC::GetSizePrefixedPosition(buf);
        auto* l = p->localPosition();
        _value = Position(p->worldCellX(), p->worldCellY(), l->x(), l->y(), l->z());
    });
}

bool Decoder::DecodeParameter(Parameter& _parameter)
{
    int sizei = 1;
    if (_parameter.IsArray() and not Decode<int>(sizei))
    {
        return false;
    }

    const size_t size = (size_t)sizei;
    switch (_parameter.m_type.elementType())
    {
    case WildRPC::ElementType_Boolean: return DecodeVector<bool>(size, _parameter);
    case WildRPC::ElementType_Integer: return DecodeVector<int>(size, _parameter);
    case WildRPC::ElementType_Float: return DecodeVector<float>(size, _parameter);
    case WildRPC::ElementType_String: return DecodeVector<Parameter::string>(size, _parameter);
    case WildRPC::ElementType_Vector2: return DecodeVector<Vector2T>(size, _parameter);
    case WildRPC::ElementType_UInt3: return DecodeVector<UInt3T>(size, _parameter);
    case WildRPC::ElementType_Vector3: return DecodeVector<Vector3T>(size, _parameter);
    case WildRPC::ElementType_Quat: return DecodeVector<QuatT>(size, _parameter);
    case WildRPC::ElementType_Color: return DecodeVector<ColorT>(size, _parameter);
    case WildRPC::ElementType_Position: return DecodeVector<Position>(size, _parameter);
    case WildRPC::ElementType_Invalid:
    default:
        return false;
    }
}


// ENCODING ------------------------------------------------------------------------

struct Encoder
{
    u8* m_buffer;
    const size_t m_bufferSize;
    uoffset_t& m_offset;

private:
    template <typename T>
    bool EncodeInternal(T&& _encoder)
    {
        flatbuffers::FlatBufferBuilder builder(1024);
        auto result = _encoder(builder);
        builder.FinishSizePrefixed(result);

        const uoffset_t resultSize = builder.GetSize();
        if (m_offset + resultSize >= m_bufferSize)
        {
            return false;
        }

        memcpy(m_buffer + m_offset, builder.GetBufferPointer(), resultSize);
        m_offset += resultSize;
        return true;
    }

    template <typename TIn, typename TFbIn, typename TFbOut>
    bool EncodeCreate(flatbuffers::Offset<TFbOut> (*_encoder)(flatbuffers::FlatBufferBuilder&, const TFbIn*, const flatbuffers::rehasher_function_t*), const TIn& _value)
    {
        return EncodeInternal([&](auto& _builder)
        {
            return _encoder(_builder, (const TFbIn*)&_value, nullptr);
        });
    }

public:
    template<typename T> bool Encode(const T& _value);

    template<typename T>
    bool EncodeVector(const Parameter::vector<T> _vector)
    {
        if (not Encode<int>((int)_vector.size()))
        {
            return false;
        }
        for (const auto& e : _vector)
        {
            if (not Encode(e))
            {
                return false;
            }
        }
        return true;
    }

    bool EncodeParameter(const Parameter& _parameter);
};

template<> bool Encoder::Encode(const bool& _value) { return EncodeCreate(WildRPC::CreateBoolean, _value); }
template<> bool Encoder::Encode(const int& _value) { return EncodeCreate(WildRPC::CreateInteger, _value); }
template<> bool Encoder::Encode(const float& _value) { return EncodeCreate(WildRPC::CreateFloat, _value); }
template<> bool Encoder::Encode(const Parameter::string& _value)
{
    return EncodeInternal([&](auto& _builder)
    {
        return WildRPC::CreateString(_builder, _builder.CreateString(_value.c_str()));
    });
}

template<> bool Encoder::Encode(const Vector2T& _value) { return EncodeCreate(WildRPC::CreateVector2, _value); }
template<> bool Encoder::Encode(const UInt3T& _value) { return EncodeCreate(WildRPC::CreateUInt3, _value); }
template<> bool Encoder::Encode(const Vector3T& _value) { return EncodeCreate(WildRPC::CreateVector3, _value); }
template<> bool Encoder::Encode(const QuatT& _value) { return EncodeCreate(WildRPC::CreateQuat, _value); }
template<> bool Encoder::Encode(const ColorT& _value) { return EncodeCreate(WildRPC::CreateColor, _value); }
//template<> bool Encoder::Encode(const PositionT& _value) { return EncodeCreate(WildRPC::CreatePosition, _value); }
template<> bool Encoder::Encode(const Position& v)
{
    return EncodeInternal([&](auto& _builder)
    {
        auto localPos = WildRPC::CreateVector3(_builder, v.x, v.y, v.z);
        return WildRPC::CreatePosition(_builder, v.wx, v.wy, localPos);
    });
}

bool Encoder::EncodeParameter(const Parameter& _parameter)
{
    return _parameter.IsArray()
        ? mapbox::util::apply_visitor([&](const auto& _value) { return EncodeVector(_value); }, _parameter.m_value)
        : mapbox::util::apply_visitor([&](const auto& _value) { return Encode(_value[0]); }, _parameter.m_value);
}


// PARAMETER BUFFER -------------

size_t Parameter::ValueSize() const
{
    return mapbox::util::apply_visitor([](const auto& _value){ return _value.size(); }, m_value);
}

bool Parameter::EncodeIn(uint8_t* _buffer, const size_t _bufferSize, uoffset_t& _offset) const
{
    Encoder encoder{_buffer, _bufferSize, _offset};
    return encoder.EncodeParameter(*this);
}

bool Parameter::DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, uoffset_t& _offset)
{
    Decoder decoder{_buffer, _bufferSize, _offset};
    return decoder.DecodeParameter(*this);
}

} // namespace WRPC
