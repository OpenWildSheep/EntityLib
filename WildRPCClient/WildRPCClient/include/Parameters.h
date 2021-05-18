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

    namespace Type
    {
        static TypeInfo Invalid(ContainerType_None, ElementType_Invalid);
        static TypeInfo Boolean(ContainerType_None, ElementType_Boolean);
        static TypeInfo Integer(ContainerType_None, ElementType_Integer);
        static TypeInfo Float(ContainerType_None, ElementType_Float);
        static TypeInfo Vector2(ContainerType_None, ElementType_Vector2);
        static TypeInfo UInt3(ContainerType_None, ElementType_UInt3);
        static TypeInfo Vector3(ContainerType_None, ElementType_Vector3);
        static TypeInfo Quat(ContainerType_None, ElementType_Quat);
        static TypeInfo Color(ContainerType_None, ElementType_Color);
        static TypeInfo Position(ContainerType_None, ElementType_Position);
        static TypeInfo String(ContainerType_None, ElementType_String);

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
        mapbox::util::variant<bool, int32_t, float, Vector2, Vector3i, Vector3, Quat, Color, Position, std::string>
            m_value;

    public:
        template <ElementType t>
        static Parameter Build(bool _bool)
        {
            static_assert(t == ElementType_Boolean, "t != ElementType_Boolean!!");
            Parameter param;
            param.m_value = _bool;
            return param;
        }

        template <ElementType t>
        static Parameter Build(int _int)
        {
            static_assert(t == ElementType_Integer, "t != ElementType_Integer!!");
            Parameter param;
            param.m_value = _int;
            return param;
        }

        template <ElementType t>
        static Parameter Build(float _float)
        {
            static_assert(t == ElementType_Float, "t != ElementType_Float!!");
            Parameter param;
            param.m_value = _float;
            return param;
        }

        template <ElementType t>
        static Parameter Build(float _x, float _y)
        {
            static_assert(t == ElementType_Vector2, "t != ElementType_Vector2!!");
            Parameter param;
            param.m_value = Vector2(_x, _y);
            return param;
        }

        template <ElementType t>
        static Parameter Build(uint32_t _x, uint32_t _y, uint32_t _z)
        {
            static_assert(t == ElementType_UInt3, "t != ElementType_UInt3!!");
            Parameter param;
            param.m_value = Vector3i(_x, _y, _z);
            return param;
        }

        template <ElementType t>
        static Parameter Build(float _x, float _y, float _z)
        {
            static_assert(t == ElementType_Vector3, "t != ElementType_Vector3!!");
            Parameter param;
            param.m_value = Vector3(_x, _y, _z);
            return param;
        }

        template <ElementType t>
        static Parameter Build(uint32_t _wx, uint32_t _wy, float _x, float _y, float _z)
        {
            static_assert(t == ElementType_Position, "t != ElementType_Position!!");
            Parameter param;
            param.m_value = Position(_wx, _wy, _x, _y, _z);
            return param;
        }

        template <ElementType t>
        static Parameter Build(float _x, float _y, float _z, float _w)
        {
            constexpr bool isColor = (t == ElementType_Color);
            constexpr bool isQuat = (t == ElementType_Quat);
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

        template <ElementType t>
        static Parameter Build(const char* _strg)
        {
            static_assert(t == ElementType_String, "t != ElementType_String!!");
            Parameter param;
            param.m_value = std::string(_strg);
            return param;
        }

        static Parameter BuildBool(bool _bool)
        {
            Parameter param;
            param.m_value = _bool;
            return param;
        }

        static Parameter BuildInt(int _int)
        {
            Parameter param;
            param.m_value = _int;
            return param;
        }

        static Parameter BuildFloat(float _float)
        {
            Parameter param;
            param.m_value = _float;
            return param;
        }

        static Parameter BuildVector2f(float _x, float _y)
        {
            Parameter param;
            param.m_value = Vector2(_x, _y);
            return param;
        }

        static Parameter BuildVector3i(uint32_t _x, uint32_t _y, uint32_t _z)
        {
            Parameter param;
            param.m_value = Vector3i(_x, _y, _z);
            return param;
        }

        static Parameter BuildVector3f(float _x, float _y, float _z)
        {
            Parameter param;
            param.m_value = Vector3(_x, _y, _z);
            return param;
        }

        static Parameter BuildPosition(uint32_t _wx, uint32_t _wy, float _x, float _y, float _z)
        {
            Parameter param;
            param.m_value = Position(_wx, _wy, _x, _y, _z);
            return param;
        }

        static Parameter BuildQuat(float _x, float _y, float _z, float _w)
        {
            Parameter param;
            param.m_value = Quat(_x, _y, _z, _w);
            return param;
        }

        static Parameter BuildColor(float _x, float _y, float _z, float _w)
        {
            Parameter param;
            param.m_value = Color(_x, _y, _z, _w);
            return param;
        }

        static Parameter BuildString(const char* _strg)
        {
            Parameter param;
            param.m_value = std::string(_strg);
            return param;
        }

        // Constructors --------------------------------
        Parameter()
        {
        }
        void Init(const TypeInfo& _type);

        // Getters -------------------------------------
        TypeInfo GetType() const;

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
        template <ElementType t>
        static ResultValue Build(bool& _bool)
        {
            static_assert(t == ElementType_Boolean, "t != ElementType_Boolean!!");
            ResultValue result;
            result.m_value = &_bool;
            return result;
        }

        template <ElementType t>
        static ResultValue Build(int32_t& _int)
        {
            static_assert(t == ElementType_Integer, "t != ElementType_Integer!!");
            ResultValue result;
            result.m_value = &_int;
            return result;
        }

        template <ElementType t>
        static ResultValue Build(float& _float)
        {
            static_assert(t == ElementType_Float, "t != ElementType_Float!!");
            ResultValue result;
            result.m_value = &_float;
            return result;
        }

        template <ElementType t>
        static ResultValue Build(float& _x, float& _y)
        {
            static_assert(t == ElementType_Vector2, "t != ElementType_Vector2!!");
            ResultValue result;
            result.m_value = Vector2H(_x, _y);
            return result;
        }

        template <ElementType t>
        static ResultValue Build(uint32_t& _x, uint32_t& _y, uint32_t& _z)
        {
            static_assert(t == ElementType_UInt3, "t != ElementType_UInt3!!");
            ResultValue result;
            result.m_value = Vector3iH(_x, _y, _z);
            return result;
        }

        template <ElementType t>
        static ResultValue Build(float& _x, float& _y, float& _z)
        {
            static_assert(t == ElementType_Vector3, "t != ElementType_Vector3!!");
            ResultValue result;
            result.m_value = Vector3H(_x, _y, _z);
            return result;
        }

        template <ElementType t>
        static ResultValue Build(float& _x, float& _y, float& _z, float& _w)
        {
            constexpr bool isColor = (t == ElementType_Color);
            constexpr bool isQuat = (t == ElementType_Quat);
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

        template <ElementType t>
        static ResultValue Build(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z)
        {
            static_assert(t == ElementType_Position, "t != ElementType_Position!!");
            ResultValue result;
            result.m_value = PositionH(_wx, _wy, _x, _y, _z);
            return result;
        }

        template <ElementType t>
        static ResultValue Build(std::string& _strg)
        {
            static_assert(t == ElementType_String, "t != ElementType_String!!");
            ResultValue result;
            result.m_value = &_strg;
            return result;
        }

        static ResultValue BuildBool(bool& _bool)
        {
            ResultValue result;
            result.m_value = &_bool;
            return result;
        }

        static ResultValue BuildInt(int32_t& _int)
        {
            ResultValue result;
            result.m_value = &_int;
            return result;
        }

        static ResultValue BuildFloat(float& _float)
        {
            ResultValue result;
            result.m_value = &_float;
            return result;
        }

        static ResultValue BuildVector2f(float& _x, float& _y)
        {
            ResultValue result;
            result.m_value = Vector2H(_x, _y);
            return result;
        }

        static ResultValue BuildVector3i(uint32_t& _x, uint32_t& _y, uint32_t& _z)
        {
            ResultValue result;
            result.m_value = Vector3iH(_x, _y, _z);
            return result;
        }

        static ResultValue BuildVector3f(float& _x, float& _y, float& _z)
        {
            ResultValue result;
            result.m_value = Vector3H(_x, _y, _z);
            return result;
        }

        static ResultValue BuildColor(float& _x, float& _y, float& _z, float& _w)
        {
            ResultValue result;
            result.m_value = ColorH(_x, _y, _z, _w);
            return result;
        }
        static ResultValue BuildQuat(float& _x, float& _y, float& _z, float& _w)
        {
            ResultValue result;
            result.m_value = QuatH(_x, _y, _z, _w);
            return result;
        }

        static ResultValue BuildPosition(uint32_t& _wx, uint32_t& _wy, float& _x, float& _y, float& _z)
        {
            ResultValue result;
            result.m_value = PositionH(_wx, _wy, _x, _y, _z);
            return result;
        }

        static ResultValue BuildString(std::string& _strg)
        {
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
        bool RetrieveValues(std::initializer_list<ResultValue> _holders);

        const char* GetErrorString()
        {
            return RPC_PROTOCOL_ERROR_STRINGS[(int)m_error.m_protocolError];
        }

    private:
        std::vector<Parameter> m_paramsBuffer;
        RPC_Error m_error;
    };
} // namespace WRPC
