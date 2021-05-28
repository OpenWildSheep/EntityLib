#pragma once

#include <vector>

#pragma warning(push, 0)
#include "../../../external/mapbox/variant.hpp"
#include <WiLDRPC/RPCHeader_generated.h>
#pragma warning(pop)

#include "WildRPCType.h"

namespace WRPC
{
    using namespace WildRPC;
    typedef flatbuffers::uoffset_t uoffset_t;

    namespace Type
    {
        static TypeInfo Invalid(ContainerType_Scalar, ElementType_Invalid);
        static TypeInfo Boolean(ContainerType_Scalar, ElementType_Boolean);
        static TypeInfo Integer(ContainerType_Scalar, ElementType_Integer);
        static TypeInfo Float(ContainerType_Scalar, ElementType_Float);
        static TypeInfo Vector2(ContainerType_Scalar, ElementType_Vector2);
        static TypeInfo UInt3(ContainerType_Scalar, ElementType_UInt3);
        static TypeInfo Vector3(ContainerType_Scalar, ElementType_Vector3);
        static TypeInfo Quat(ContainerType_Scalar, ElementType_Quat);
        static TypeInfo Color(ContainerType_Scalar, ElementType_Color);
        static TypeInfo Position(ContainerType_Scalar, ElementType_Position);
        static TypeInfo String(ContainerType_Scalar, ElementType_String);

        static TypeInfo InvalidArray(ContainerType_Array, ElementType_Invalid);
        static TypeInfo BooleanArray(ContainerType_Array, ElementType_Boolean);
        static TypeInfo IntegerArray(ContainerType_Array, ElementType_Integer);
        static TypeInfo FloatArray(ContainerType_Array, ElementType_Float);
        static TypeInfo Vector2Array(ContainerType_Array, ElementType_Vector2);
        static TypeInfo UInt3Array(ContainerType_Array, ElementType_UInt3);
        static TypeInfo Vector3Array(ContainerType_Array, ElementType_Vector3);
        static TypeInfo QuatArray(ContainerType_Array, ElementType_Quat);
        static TypeInfo ColorArray(ContainerType_Array, ElementType_Color);
        static TypeInfo PositionArray(ContainerType_Array, ElementType_Position);
        static TypeInfo StringArray(ContainerType_Array, ElementType_String);
    }

    inline bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
    {
        return lhs.containerType() == rhs.containerType()
            && lhs.elementType() == rhs.elementType();
    }

    inline bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
    {
        return !(lhs == rhs);
    }


    struct Vector2
    {
        float x = 0.0f, y = 0.0f;
        Vector2()
        {
        }
        Vector2(float _x, float _y)
            : x(_x)
            , y(_y)
        {
        }
    };

    struct Vector3
    {
        float x = 0.0f, y = 0.0f, z = 0.0f;
        Vector3()
        {
        }
        Vector3(float _x, float _y, float _z)
            : x(_x)
            , y(_y)
            , z(_z)
        {
        }
    };

    struct Quat
    {
        float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;
        Quat()
        {
        }
        Quat(float _x, float _y, float _z, float _w)
            : x(_x)
            , y(_y)
            , z(_z)
            , w(_w)
        {
        }
    };

    struct Color
    {
        float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
        Color()
        {
        }
        Color(float _r, float _g, float _b, float _a)
            : r(_r)
            , g(_g)
            , b(_b)
            , a(_a)
        {
        }
    };

    struct Vector3i
    {
        uint32_t x = 0, y = 0, z = 0;
        Vector3i()
        {
        }
        Vector3i(uint32_t _x, uint32_t _y, uint32_t _z)
            : x(_x)
            , y(_y)
            , z(_z)
        {
        }
    };

    struct Position
    {
        uint32_t wx = 32768, wy = 32768;
        float x = 0.0f, y = 0.0f, z = 0.0f;
        Position()
        {
        }
        Position(uint32_t _wx, uint32_t _wy, float _x, float _y, float _z)
            : wx(_wx)
            , wy(_wy)
            , x(_x)
            , y(_y)
            , z(_z)
        {
        }
    };


    struct WRPC_DLLEXPORT Parameter
    {
        template <typename T>
        using vector = std::vector<T>;

        typedef std::string string;

        mapbox::util::variant<
            vector<bool>,
            vector<int>,
            vector<float>,
            vector<Vector2>,
            vector<Vector3i>,
            vector<Vector3>,
            vector<Quat>,
            vector<Color>,
            vector<Position>,
            vector<string>
        > m_value;

        TypeInfo m_type;


        template <typename T> static ElementType GetElementType();
        template <> static ElementType GetElementType<bool>() { return ElementType_Boolean; }
        template <> static ElementType GetElementType<int>() { return ElementType_Integer; }
        template <> static ElementType GetElementType<float>() { return ElementType_Float; }
        template <> static ElementType GetElementType<Vector2>() { return ElementType_Vector2; }
        template <> static ElementType GetElementType<Vector3i>() { return ElementType_UInt3; }
        template <> static ElementType GetElementType<Vector3>() { return ElementType_Vector3; }
        template <> static ElementType GetElementType<Quat>() { return ElementType_Quat; }
        template <> static ElementType GetElementType<Color>() { return ElementType_Color; }
        template <> static ElementType GetElementType<Position>() { return ElementType_Position; }
        template <> static ElementType GetElementType<string>() { return ElementType_String; }


        Parameter(const TypeInfo& _type)
        {
            m_type = _type;
        }

    private:
        // NOTE: these private constructors take a dummy second parameter, to disambiguate the explicitly-typed constructors
        template <typename T>
        Parameter(const T& _scalar, char)
        {
            m_value = vector<T>{_scalar};
            m_type = TypeInfo(ContainerType_Scalar, GetElementType<T>());
        }

        template <typename T>
        Parameter(const vector<T>& _vector, char)
        {
            m_value = _vector;
            m_type = TypeInfo(ContainerType_Array, GetElementType<T>());
        }

    public:
        template <typename T>
        Parameter(const T& _scalar) : Parameter(_scalar, 0) { }

        template <typename T>
        Parameter(const vector<T>& _vector) : Parameter(_vector, 0) { }

        Parameter(const char* _scalar) : Parameter(string(_scalar)) { }


        /// Get the value as a scalar.
        /// Throws a `bad_variant_access` exception if the type you requested does not match the actual type.
        template <typename T>
        T AsScalar() const
        {
            return m_value.get<vector<T>>()[0];
        }

        /// Get the value as a vector.
        /// Throws a `bad_variant_access` exception if the type you requested does not match the actual type.
        template <typename T>
        const vector<T>& AsVector() const
        {
            return m_value.get<vector<T>>();
        }


        /// Get the value as a scalar.
        /// Returns whether the correct type was requested.
        template <typename T>
        bool TryGetScalar(T& _value) const
        {
            if (m_type != TypeInfo(ContainerType_Scalar, GetElementType<T>()))
            {
                return false;
            }
            _value = m_value.get<vector<T>>()[0];
            return true;
        }

        /// Get the value as a vector.
        /// Returns whether the correct type was requested.
        template <typename T>
        bool TryGetVector(vector<T>& _value) const
        {
            if (m_type != TypeInfo(ContainerType_Array, GetElementType<T>()))
            {
                return false;
            }
            _value = m_value.get<vector<T>>();
            return true;
        }


        const TypeInfo& GetType() const { return m_type; }
        bool IsArray() const { return m_type.containerType() == ContainerType_Array; }
        size_t ValueSize() const;

        bool EncodeIn(uint8_t* _buffer, const size_t _bufferSize, uoffset_t& _offset) const;
        bool DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, uoffset_t& _offset);


        // explicitly-typed overloads, for languages that don't support binding to template methods (eg Wolf, Python)
        Parameter(const bool& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const int& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const float& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const Vector2& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const Vector3i& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const Vector3& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const Quat& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const Color& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const Position& _scalar) : Parameter(_scalar, 0) { }
        Parameter(const string& _scalar) : Parameter(_scalar, 0) { }

        Parameter(const vector<bool>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<int>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<float>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<Vector2>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<Vector3i>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<Vector3>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<Quat>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<Color>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<Position>& _vector) : Parameter(_vector, 0) { }
        Parameter(const vector<string>& _vector) : Parameter(_vector, 0) { }

        Parameter(const std::initializer_list<bool>& _list) : Parameter(vector<bool>(_list), 0) { }
        Parameter(const std::initializer_list<int>& _list) : Parameter(vector<int>(_list), 0) { }
        Parameter(const std::initializer_list<float>& _list) : Parameter(vector<float>(_list), 0) { }
        Parameter(const std::initializer_list<Vector2>& _list) : Parameter(vector<Vector2>(_list), 0) { }
        Parameter(const std::initializer_list<Vector3i>& _list) : Parameter(vector<Vector3i>(_list), 0) { }
        Parameter(const std::initializer_list<Vector3>& _list) : Parameter(vector<Vector3>(_list), 0) { }
        Parameter(const std::initializer_list<Quat>& _list) : Parameter(vector<Quat>(_list), 0) { }
        Parameter(const std::initializer_list<Color>& _list) : Parameter(vector<Color>(_list), 0) { }
        Parameter(const std::initializer_list<Position>& _list) : Parameter(vector<Position>(_list), 0) { }
        Parameter(const std::initializer_list<string>& _list) : Parameter(vector<string>(_list), 0) { }

        bool AsScalar_bool() const { return AsScalar<bool>(); }
        int AsScalar_int() const { return AsScalar<int>(); }
        float AsScalar_float() const { return AsScalar<float>(); }
        Vector2 AsScalar_Vector2() const { return AsScalar<Vector2>(); }
        Vector3i AsScalar_Vector3i() const { return AsScalar<Vector3i>(); }
        Vector3 AsScalar_Vector3() const { return AsScalar<Vector3>(); }
        Quat AsScalar_Quat() const { return AsScalar<Quat>(); }
        Color AsScalar_Color() const { return AsScalar<Color>(); }
        Position AsScalar_Position() const { return AsScalar<Position>(); }
        string AsScalar_string() const { return AsScalar<string>(); }

        const vector<bool>& AsVector_bool() const { return AsVector<bool>(); }
        const vector<int>& AsVector_int() const { return AsVector<int>(); }
        const vector<float>& AsVector_float() const { return AsVector<float>(); }
        const vector<Vector2>& AsVector_Vector2() const { return AsVector<Vector2>(); }
        const vector<Vector3i>& AsVector_Vector3i() const { return AsVector<Vector3i>(); }
        const vector<Vector3>& AsVector_Vector3() const { return AsVector<Vector3>(); }
        const vector<Quat>& AsVector_Quat() const { return AsVector<Quat>(); }
        const vector<Color>& AsVector_Color() const { return AsVector<Color>(); }
        const vector<Position>& AsVector_Position() const { return AsVector<Position>(); }
        const vector<string>& AsVector_string() const { return AsVector<string>(); }

        bool TryGetScalar_bool(bool& _value) const { return TryGetScalar<bool>(_value); }
        bool TryGetScalar_int(int& _value) const { return TryGetScalar<int>(_value); }
        bool TryGetScalar_float(float& _value) const { return TryGetScalar<float>(_value); }
        bool TryGetScalar_Vector2(Vector2& _value) const { return TryGetScalar<Vector2>(_value); }
        bool TryGetScalar_Vector3i(Vector3i& _value) const { return TryGetScalar<Vector3i>(_value); }
        bool TryGetScalar_Vector3(Vector3& _value) const { return TryGetScalar<Vector3>(_value); }
        bool TryGetScalar_Quat(Quat& _value) const { return TryGetScalar<Quat>(_value); }
        bool TryGetScalar_Color(Color& _value) const { return TryGetScalar<Color>(_value); }
        bool TryGetScalar_Position(Position& _value) const { return TryGetScalar<Position>(_value); }
        bool TryGetScalar_string(string& _value) const { return TryGetScalar<string>(_value); }

        bool TryGetVector_bool(vector<bool>& _value) const { return TryGetVector<bool>(_value); }
        bool TryGetVector_int(vector<int>& _value) const { return TryGetVector<int>(_value); }
        bool TryGetVector_float(vector<float>& _value) const { return TryGetVector<float>(_value); }
        bool TryGetVector_Vector2(vector<Vector2>& _value) const { return TryGetVector<Vector2>(_value); }
        bool TryGetVector_Vector3i(vector<Vector3i>& _value) const { return TryGetVector<Vector3i>(_value); }
        bool TryGetVector_Vector3(vector<Vector3>& _value) const { return TryGetVector<Vector3>(_value); }
        bool TryGetVector_Quat(vector<Quat>& _value) const { return TryGetVector<Quat>(_value); }
        bool TryGetVector_Color(vector<Color>& _value) const { return TryGetVector<Color>(_value); }
        bool TryGetVector_Position(vector<Position>& _value) const { return TryGetVector<Position>(_value); }
        bool TryGetVector_string(vector<string>& _value) const { return TryGetVector<string>(_value); }
    };

    // -----------------------

    class WRPC_DLLEXPORT Result
    {
        friend class MethodInvocation;

    public:
        bool HasError() const
        {
            return (m_error.m_protocolError != RPCProtocolError::No_Error)
                   || (m_error.m_applicativeError != 0);
        }

        const char* GetErrorString()
        {
            return RPC_PROTOCOL_ERROR_STRINGS[(int)m_error.m_protocolError];
        }

        Parameter& GetParameter(size_t idx)
        {
            return m_paramsBuffer[idx];
        }


        /// Get the next result as a scalar.
        /// Pseudo-iterator pattern, inspired by FlexBuffers: https://google.github.io/flatbuffers/flexbuffers.html
        /// Usage:
        ///     // assuming that `method` returns an (int, vector<float>) tuple:
        ///     auto result = method.Execute(...);
        ///     auto arg1 = result.NextScalar<int>();
        ///     auto arg2 = result.NextVector<float>();
        template <typename T>
        T NextScalar()
        {
            T value = m_paramsBuffer[m_index].AsScalar<T>();
            m_index++;
            return value;
        }

        /// Get the next result as a vector.
        /// Pseudo-iterator pattern, inspired by FlexBuffers: https://google.github.io/flatbuffers/flexbuffers.html
        /// Usage:
        ///     // assuming that `method` returns an (int, vector<float>) tuple:
        ///     auto result = method.Execute(...);
        ///     auto arg1 = result.NextScalar<int>();
        ///     auto arg2 = result.NextVector<float>();
        template <typename T>
        const Parameter::vector<T>& NextVector()
        {
            const Parameter::vector<T>& value = m_paramsBuffer[m_index].AsVector<T>();
            m_index++;
            return value;
        }

        // explicitly-typed overloads, for languages that don't support binding to template methods (eg Wolf, Python)
        typedef Parameter::string string;

        bool NextScalar_bool() { return NextScalar<bool>(); }
        int NextScalar_int() { return NextScalar<int>(); }
        float NextScalar_float() { return NextScalar<float>(); }
        Vector2 NextScalar_Vector2() { return NextScalar<Vector2>(); }
        Vector3i NextScalar_Vector3i() { return NextScalar<Vector3i>(); }
        Vector3 NextScalar_Vector3() { return NextScalar<Vector3>(); }
        Quat NextScalar_Quat() { return NextScalar<Quat>(); }
        Color NextScalar_Color() { return NextScalar<Color>(); }
        Position NextScalar_Position() { return NextScalar<Position>(); }
        string NextScalar_string() { return NextScalar<string>(); }

        const Parameter::vector<bool>& NextVector_bool() { return NextVector<bool>(); }
        const Parameter::vector<int>& NextVector_int() { return NextVector<int>(); }
        const Parameter::vector<float>& NextVector_float() { return NextVector<float>(); }
        const Parameter::vector<Vector2>& NextVector_Vector2() { return NextVector<Vector2>(); }
        const Parameter::vector<Vector3i>& NextVector_Vector3i() { return NextVector<Vector3i>(); }
        const Parameter::vector<Vector3>& NextVector_Vector3() { return NextVector<Vector3>(); }
        const Parameter::vector<Quat>& NextVector_Quat() { return NextVector<Quat>(); }
        const Parameter::vector<Color>& NextVector_Color() { return NextVector<Color>(); }
        const Parameter::vector<Position>& NextVector_Position() { return NextVector<Position>(); }
        const Parameter::vector<string>& NextVector_string() { return NextVector<string>(); }

    private:
        RPC_Error m_error;
        std::vector<Parameter> m_paramsBuffer;
        size_t m_index = 0;
    };
} // namespace WRPC
