# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

project(EntityLib)
set(CMAKE_CXX_STANDARD 17)

if( MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4 /WX /wd\"4273\" /wd\"4324\" /wd\"4251\" /wd\"4625\" /wd\"4626\" /wd\"4820\" /wd\"4710\" /wd\"4711\" /wd\"4714\" /wd\"4514\" /wd\"4774\" /wd\"4571\" /wd\"4868\" /wd\"5026\" /wd\"5027\" /wd\"4623\"")
endif()

file(GLOB ENTITYLIB_SOURCES "EntityLib/*.cpp")
add_library(EntityLib ${ENTITYLIB_SOURCES})
target_include_directories(EntityLib PRIVATE EntityLib/external)
target_include_directories(EntityLib PRIVATE EntityLib/external/valijson/include)
target_include_directories(EntityLib PUBLIC EntityLib/include)

file(GLOB ENTITYLIBPY_SOURCES "EntityLibPy/*.cpp")
add_library(EntityLibPy ${ENTITYLIBPY_SOURCES})
add_dependencies(EntityLibPy EntityLib)
target_include_directories(EntityLibPy PUBLIC EntityLib/include)
target_include_directories(EntityLibPy PRIVATE submodules/pybind11/include)
find_package(PythonLibs COMPONENTS Interpreter Development)
if (NOT PYTHONLIBS_FOUND)
  message (FATAL_ERROR "Failed to find PythonLibs ${Python_REQUESTED_VERSION}")
endif()
target_include_directories(EntityLibPy PRIVATE ${PYTHON_INCLUDE_DIRS})


file(GLOB CLASSGEN_SOURCES "EntLibAPIGenerator/*.cpp")
add_library(EntLibAPIGenerator ${CLASSGEN_SOURCES})
add_dependencies(EntLibAPIGenerator EntityLib)
target_include_directories(EntLibAPIGenerator PUBLIC EntityLib/include)
target_include_directories(EntLibAPIGenerator PRIVATE EntLibAPIGenerator/external/Mustache)

file(GLOB TESTENTGEN_SOURCES "TestEntGen/*.cpp")
add_library(TestEntGen ${TESTENTGEN_SOURCES})
add_dependencies(TestEntGen EntityLib)
target_include_directories(TestEntGen PUBLIC EntityLib/include)
target_include_directories(TestEntGen PRIVATE EntGen/cpp2)

file(GLOB TESTENTITYLIB_SOURCES "Test/*.cpp")
add_library(TestEntityDLL ${TESTENTITYLIB_SOURCES})
add_dependencies(TestEntityDLL EntityLib)
target_include_directories(TestEntityDLL PUBLIC EntityLib/include)
target_include_directories(TestEntityDLL PRIVATE EntGen/cpp2)

file(GLOB UPDATESCHEMA_SOURCES "UpdateSchemas/*.cpp")
add_library(UpdateSchemas ${UPDATESCHEMA_SOURCES})
add_dependencies(UpdateSchemas EntityLib)
target_include_directories(UpdateSchemas PUBLIC EntityLib/include)