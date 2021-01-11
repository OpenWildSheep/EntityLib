#pragma once

#include <vector>

#pragma warning(push, 0)
#include "../../../external/mapbox/variant.hpp"
#pragma warning(pop)

#include "WildRPCType.h"

namespace WildRPC
{
    enum Type : int;
}

namespace WRPC
{
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
        mapbox::util::variant<bool, int32_t, float, Vector2, Vector3i, Vector3, Quat, Color, Position, std::string>
            m_value;

    public:
        template <WildRPC::Type t>
        static Parameter Build(bool _bool)
        {
            static_assert(t == WildRPC::Type_Boolean, "t != WildRPC::Type_Boolean!!");
            Parameter param;
            param.m_value = _bool;
            return param;
        }

        template <WildRPC::Type t>
        static Parameter Build(int _int)
        {
            static_assert(t == WildRPC::Type_Integer, "t != WildRPC::Type_Integer!!");
            Parameter param;
            param.m_value = _int;
            return param;
        }

        template <WildRPC::Type t>
        static Parameter Build(float _float)
        {
            static_assert(t == WildRPC::Type_Float, "t != WildRPC::Type_Float!!");
            Parameter param;
            param.m_value = _float;
            return param;
        }

        template <WildRPC::Type t>
        static Parameter Build(float _x, float _y)
        {
            static_assert(t == WildRPC::Type_Vector2, "t != WildRPC::Type_Vector2!!");
            Parameter param;
            param.m_value = Vector2(_x, _y);
            return param;
        }

        template <WildRPC::Type t>
        static Parameter Build(uint32_t _x, uint32_t _y, uint32_t _z)
        {
            static_assert(t == WildRPC::Type_UInt3, "t != WildRPC::Type_UInt3!!");
            Parameter param;
            param.m_value = Vector3i(_x, _y, _z);
            return param;
        }

        template <WildRPC::Type t>
        static Parameter Build(float _x, float _y, float _z)
        {
            static_assert(t == WildRPC::Type_Vector3, "t != WildRPC::Type_Vector3!!");
            Parameter param;
            param.m_value = Vector3(_x, _y, _z);
            return param;
        }

        template <WildRPC::Type t>
        static Parameter Build(uint32_t _wx, uint32_t _wy, float _x, float _y, float _z)
        {
            static_assert(t == WildRPC::Type_Position, "t != WildRPC::Type_Position!!");
            Parameter param;
            param.m_value = Position(_wx, _wy, _x, _y, _z);
            return param;
        }

        template <WildRPC::Type t>
        static Parameter Build(float _x, float _y, float _z, float _w)
        {
            constexpr bool isColor = (t == WildRPC::Type_Color);
            constexpr bool isQuat = (t == WildRPC::Type_Quat);
            static_assert(isQuat || isColor, "!(isQuat || isColor)");

            Parameter param;
            if (isColor)
            {
                param.m_value = Color(_x, _y, _z, _w);
            }
            if (isQuat)
            {
                param.m_value = Quat(_x, _y, _z, _w);
            }
            return param;
        }

        template <WildRPC::Type t>
        static Parameter Build(const char* _strg)
        {
            static_assert(t == WildRPC::Type_String, "t != WildRPC::Type_String!!");
            Parameter param;
            param.m_value = std::string(_strg);
            return param;
        }

        // Constructors --------------------------------
        Parameter()
        {
        }
        void Init(WildRPC::Type _type);

        // Getters -------------------------------------
        WildRPC::Type GetType() const;

        bool GetValue(bool& _bool) const;
        bool GetValue(int& _int) const;
        bool GetValue(float& _float) const;
        bool GetValue(float& _x, float& _y) const;
        bool GetValue(uint32_t& _x, uint32_t& _y, uint32_t& _z) const;
        bool GetValue(float& _x, float& _y, float& _z) const;
        bool GetValue(float& _x, float& _y, float& _z, float& _w) const;
        bool GetValue(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z) const;
        bool GetValue(std::string& _char) const;

        // En/Decoding ----------------------------------
        bool EncodeIn(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset) const;
        bool DecodeFrom(uint8_t* _buffer, const size_t _bufferSize, size_t& _offset);

        // Debug -----------------------------------------

        void Print() const;
    };

    // -----------------------

    struct Vector2H
    {
        float *x, *y;
        Vector2H(float& _x, float& _y)
            : x(&_x)
            , y(&_y)
        {
        }
    };

    struct Vector3H
    {
        float *x, *y, *z;
        Vector3H(float& _x, float& _y, float& _z)
            : x(&_x)
            , y(&_y)
            , z(&_z)
        {
        }
    };

    struct QuatH
    {
        float *x, *y, *z, *w;
        QuatH(float& _x, float& _y, float& _z, float& _w)
            : x(&_x)
            , y(&_y)
            , z(&_z)
            , w(&_w)
        {
        }
    };

    struct ColorH
    {
        float *r, *g, *b, *a;
        ColorH(float& _r, float& _g, float& _b, float& _a)
            : r(&_r)
            , g(&_g)
            , b(&_b)
            , a(&_a)
        {
        }
    };

    struct Vector3iH
    {
        uint32_t *x, *y, *z;
        Vector3iH(uint32_t& _x, uint32_t& _y, uint32_t& _z)
            : x(&_x)
            , y(&_y)
            , z(&_z)
        {
        }
    };

    struct PositionH
    {
        uint32_t *wx, *wy;
        float *x, *y, *z;
        PositionH(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z)
            : wx(&_wx)
            , wy(&_wy)
            , x(&_x)
            , y(&_y)
            , z(&_z)
        {
        }
    };

    typedef mapbox::util::
        variant<bool*, int32_t*, float*, Vector2H, Vector3iH, Vector3H, QuatH, ColorH, PositionH, std::string*>
            ResultHolder;

    struct WRPC_DLLEXPORT ResultValue
    {
        template <WildRPC::Type t>
        static ResultValue Build(bool& _bool)
        {
            static_assert(t == WildRPC::Type_Boolean, "t != WildRPC::Type_Boolean!!");
            ResultValue result;
            result.m_value = &_bool;
            return result;
        }

        template <WildRPC::Type t>
        static ResultValue Build(int32_t& _int)
        {
            static_assert(t == WildRPC::Type_Integer, "t != WildRPC::Type_Integer!!");
            ResultValue result;
            result.m_value = &_int;
            return result;
        }

        template <WildRPC::Type t>
        static ResultValue Build(float& _float)
        {
            static_assert(t == WildRPC::Type_Float, "t != WildRPC::Type_Float!!");
            ResultValue result;
            result.m_value = &_float;
            return result;
        }

        template <WildRPC::Type t>
        static ResultValue Build(float& _x, float& _y)
        {
            static_assert(t == WildRPC::Type_Vector2, "t != WildRPC::Type_Vector2!!");
            ResultValue result;
            result.m_value = Vector2H(_x, _y);
            return result;
        }

        template <WildRPC::Type t>
        static ResultValue Build(uint32_t& _x, uint32_t& _y, uint32_t& _z)
        {
            static_assert(t == WildRPC::Type_UInt3, "t != WildRPC::Type_UInt3!!");
            ResultValue result;
            result.m_value = Vector3iH(_x, _y, _z);
            return result;
        }

        template <WildRPC::Type t>
        static ResultValue Build(float& _x, float& _y, float& _z)
        {
            static_assert(t == WildRPC::Type_Vector3, "t != WildRPC::Type_Vector3!!");
            ResultValue result;
            result.m_value = Vector3H(_x, _y, _z);
            return result;
        }

        template <WildRPC::Type t>
        static ResultValue Build(float& _x, float& _y, float& _z, float& _w)
        {
            constexpr bool isColor = (t == WildRPC::Type_Color);
            constexpr bool isQuat = (t == WildRPC::Type_Quat);
            static_assert(isQuat || isColor, "!(isQuat || isColor)");

            ResultValue result;
            if (isColor)
            {
                result.m_value = ColorH(_x, _y, _z, _w);
            }
            if (isQuat)
            {
                result.m_value = QuatH(_x, _y, _z, _w);
            }
            return result;
        }

        template <WildRPC::Type t>
        static ResultValue Build(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z)
        {
            static_assert(t == WildRPC::Type_Position, "t != WildRPC::Type_Position!!");
            ResultValue result;
            result.m_value = PositionH(_wx, _wy, _x, _y, _z);
            return result;
        }

        template <WildRPC::Type t>
        static ResultValue Build(std::string& _strg)
        {
            static_assert(t == WildRPC::Type_String, "t != WildRPC::Type_String!!");
            ResultValue result;
            result.m_value = &_strg;
            return result;
        }

        ResultHolder m_value;
    };

    class WRPC_DLLEXPORT Result
    {
        friend class MethodInvocation;

    public:
        bool HasError() const
        {
            return (m_error.m_protocolError != RPCProtocolError::No_Error)
                   || (m_error.m_applicativeError != 0);
        }

        Parameter& GetParameter(size_t idx)
        {
            return m_paramsBuffer[idx];
        }
        bool RetrieveValues(const std::vector<ResultValue>& _holders);

        const char* GetErrorString()
        {
            return RPC_PROTOCOL_ERROR_STRINGS[(int)m_error.m_protocolError];
        }

    private:
        std::vector<Parameter> m_paramsBuffer;
        RPC_Error m_error;
    };
} // namespace WRPC
