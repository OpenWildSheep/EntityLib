#include <iostream>

#include <WildRPCClient.h>

#pragma warning(push, 0)
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#pragma warning(pop)

/// @cond PRIVATE

namespace py = pybind11;
using namespace WRPC;

using namespace pybind11::literals;

PYBIND11_MODULE(WRPC, wicli)
{
    wicli.doc() = "pybind11 for WildRPCClient";

    /*
     * "forward-declare" all bound classes to avoid naming issues that lead to bad typing information,
     * see https://github.com/sizmailov/pybind11/blob/7b9242c84826b36fa10e6dcedb6f97fe4429fa61/docs/advanced/misc.rst#avoiding-c-types-in-docstrings
     *
     * NOTE: it wasn't strictly to pre-declare ALL classes to fix the issues we currently had,
     * but it just seemed safer in case we add new methods with new dependencies.
     */
    auto pyRPCClient = py::class_<RPCClient>(wicli, "RPCClient");

    pyRPCClient.def(py::init<>());
}

/// @endcond
