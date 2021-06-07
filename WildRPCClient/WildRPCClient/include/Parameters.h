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

    struct Type
    {
        static TypeInfo Invalid;
        static TypeInfo Boolean;
        static TypeInfo Integer;
        static TypeInfo Float;
        static TypeInfo Vector2;
        static TypeInfo UInt3;
        static TypeInfo Vector3;
        static TypeInfo Quat;
        static TypeInfo Color;
        static TypeInfo Position;
        static TypeInfo String;

        static TypeInfo InvalidArray;
        static TypeInfo BooleanArray;
        static TypeInfo IntegerArray;
        static TypeInfo FloatArray;
        static TypeInfo Vector2Array;
        static TypeInfo UInt3Array;
        static TypeInfo Vector3Array;
        static TypeInfo QuatArray;
        static TypeInfo ColorArray;
        static TypeInfo PositionArray;
        static TypeInfo StringArray;
    };

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
        template <> static ElementType GetElementType<bool>() { return ElementType_Boolean; } ///< @off
        template <> static ElementType GetElementType<int>() { return ElementType_Integer; } ///< @off
        template <> static ElementType GetElementType<float>() { return ElementType_Float; } ///< @off
        template <> static ElementType GetElementType<Vector2>() { return ElementType_Vector2; } ///< @off
        template <> static ElementType GetElementType<Vector3i>() { return ElementType_UInt3; } ///< @off
        template <> static ElementType GetElementType<Vector3>() { return ElementType_Vector3; } ///< @off
        template <> static ElementType GetElementType<Quat>() { return ElementType_Quat; } ///< @off
        template <> static ElementType GetElementType<Color>() { return ElementType_Color; } ///< @off
        template <> static ElementType GetElementType<Position>() { return ElementType_Position; } ///< @off
        template <> static ElementType GetElementType<string>() { return ElementType_String; } ///< @off

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

        template <typename T>
        Parameter(const std::initializer_list<T>& _initlist) : Parameter(vector<T>{_initlist}, 0) { }

        Parameter(const char* _scalar) : Parameter(string(_scalar)) { }


        /// Get the value as a scalar.
        /// Throws a `bad_variant_access` exception if the type you requested does not match the actual type.
        /// @instantiate <bool><int><float><Vector2><Vector3i><Vector3><Quat><Color><Position><string>
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
        /// @instantiate <bool><int><float><Vector2><Vector3i><Vector3><Quat><Color><Position><string>
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

        /// Try get the value as a vector.
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
    };

    // -----------------------

    class WRPC_DLLEXPORT Result
    {
        friend class MethodInvocation;

    public:
        using string = Parameter::string;

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

        ///     auto arg2 = result.NextVector<float>();
        /// @instantiate <bool><int><float><Vector2><Vector3i><Vector3><Quat><Color><Position><string>
        template <typename T>
        bool TryNextScalar(T& _out)
        {
            if(m_index < m_paramsBuffer.size())
            {
                _out = m_paramsBuffer[m_index++].AsScalar<T>();
                return true;
            }
            return false;
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

        /// @instantiate <bool><int><float><Vector2><Vector3i><Vector3><Quat><Color><Position><string>
        template <typename T>
        bool TryNextVector(T* _outArray, size_t _outArraySize)
        {
            if (m_index < m_paramsBuffer.size())
            {
                auto const& vec = m_paramsBuffer[m_index++].AsVector<T>();
                for (size_t i = 0; i < std::min(_outArraySize, vec.size()); ++i)
                {
                    _outArray[i] = vec[i];
                }
                m_index++;
                return true;
            }
            return false;
        }

        // explicitly-typed overloads, for languages that don't support binding to template methods (eg Wolf, Python)

    private:
        RPC_Error m_error;
        std::vector<Parameter> m_paramsBuffer;
        size_t m_index = 0;
    };
} // namespace WRPC
