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
            std::vector<WildRPC::Type> _in,
            std::vector<WildRPC::Type> _out);
        Result Execute(Connection& _connection, const std::vector<Parameter>& _values);

    private:
        bool _SetParameters(const std::vector<Parameter>& _values);

    private:
        const char* m_managerName;
        const char* m_methodName;

        std::vector<Parameter> m_inParams;
        std::vector<Parameter> m_outParams;
    };

} // namespace WRPC