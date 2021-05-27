#pragma once

#include <cstdio>
#include <exception>
#include <string>
#include <vector>

#include "WildRPCType.h"
#include "Connection.h"
#include "Parameters.h"

namespace WRPC
{
    class WRPC_DLLEXPORT MethodInvocation
    {
    public:
        MethodInvocation(
            const char* _managerName,
            const char* _methodName,
            std::vector<TypeInfo> _in,
            std::vector<TypeInfo> _out);

        MethodInvocation(
            const char* _managerName,
            const char* _methodName,
            std::initializer_list<TypeInfo> _in,
            std::initializer_list<TypeInfo> _out);

        Result Execute(Connection& _connection, const std::vector<Parameter>& _values);
        Result Execute(Connection& _connection, std::initializer_list<Parameter> _values);
        Result Execute(Connection& _connection, Parameter const* _values, size_t _valueCount);

    private:
        bool _SetParameters(const std::vector<Parameter>& _values);

    private:
        const char* m_managerName;
        const char* m_methodName;

        std::vector<Parameter> m_inParams;
        std::vector<Parameter> m_outParams;
    };

} // namespace WRPC
