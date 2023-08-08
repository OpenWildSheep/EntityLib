# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.5)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

project(EntityLib)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4 /WX /wd\"4996\" /wd\"4273\" /wd\"4324\" /wd\"4251\" /wd\"4625\" /wd\"4626\" /wd\"4820\" /wd\"4710\" /wd\"4711\" /wd\"4714\" /wd\"4514\" /wd\"4774\" /wd\"4571\" /wd\"4868\" /wd\"5026\" /wd\"5027\" /wd\"4623\"")
endif()

file(GLOB ENTITYLIB_SOURCES "EntityLib/*.cpp" "EntityLib/*.h" "EntityLib/*.hpp" "EntityLib/include/EntityLib/*.h")
add_library(EntityLib STATIC ${ENTITYLIB_SOURCES})
target_include_directories(EntityLib PUBLIC EntityLib/external)
target_include_directories(EntityLib SYSTEM PRIVATE EntityLib/external/valijson/include)
target_include_directories(EntityLib INTERFACE EntityLib/include)
target_compile_definitions(EntityLib PUBLIC ENTLIB_STATIC)

file(GLOB ENTITYLIBPY_SOURCES "EntityLibPy/*.cpp" "EntityLibPy/*.h" "EntityLibPy/*.hpp")
add_library(EntityLibPy STATIC ${ENTITYLIBPY_SOURCES})
target_include_directories(EntityLibPy PRIVATE submodules/pybind11/include)
find_package(PythonLibs REQUIRED COMPONENTS Interpreter Development)
if (NOT PYTHONLIBS_FOUND)
  message (FATAL_ERROR "Failed to find PythonLibs ${Python_REQUESTED_VERSION}")
endif()
target_include_directories(EntityLibPy PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(EntityLibPy EntityLib)
target_link_libraries(EntityLibPy ${PYTHON_LIBRARIES})
set_target_properties(EntityLibPy PROPERTIES SUFFIX ".pyd")

file(GLOB CLASSGEN_SOURCES "EntLibAPIGenerator/*.cpp" "EntLibAPIGenerator/*.h" "EntLibAPIGenerator/*.hpp")
add_executable(EntLibAPIGenerator ${CLASSGEN_SOURCES})
target_include_directories(EntLibAPIGenerator PRIVATE EntLibAPIGenerator/external/Mustache)
target_include_directories(EntLibAPIGenerator PRIVATE submodules/cxxopts/include)
target_link_libraries(EntLibAPIGenerator EntityLib)

file(GLOB UPDATESCHEMA_SOURCES "UpdateSchemas/*.cpp" "UpdateSchemas/*.h" "UpdateSchemas/*.hpp")
add_executable(UpdateSchemas ${UPDATESCHEMA_SOURCES})
target_include_directories(UpdateSchemas PRIVATE submodules/cxxopts/include)
target_link_libraries(UpdateSchemas EntityLib)

add_custom_target(BuildAllButUnitTests)
add_dependencies(BuildAllButUnitTests EntityLib)
add_dependencies(BuildAllButUnitTests EntityLibPy)
add_dependencies(BuildAllButUnitTests EntLibAPIGenerator)
add_dependencies(BuildAllButUnitTests UpdateSchemas)

enable_testing()

file(GLOB TESTENTGEN_SOURCES "TestEntGen/*.cpp" "TestEntGen/*.h" "TestEntGen/*.hpp")
add_executable(TestEntGen ${TESTENTGEN_SOURCES})
target_include_directories(TestEntGen PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/EntGen/cpp2)
target_link_libraries(TestEntGen EntityLib)
add_test(TestEntGen TestEntGen)

file(GLOB TESTENTITYLIB_SOURCES "Test/*.cpp" "Test/*.h" "Test/*.hpp")
add_executable(UnitTest ${TESTENTITYLIB_SOURCES})
target_include_directories(UnitTest PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/EntGen/cpp2)
target_include_directories(UnitTest PRIVATE submodules/cxxopts/include)
target_include_directories(UnitTest PRIVATE external/catch)
target_link_libraries(UnitTest EntityLib)

file(GLOB UPDATESCHEMA_SOURCES "UpdateSchemas/*.cpp" "UpdateSchemas/*.h" "UpdateSchemas/*.hpp")
add_executable(UpdateSchemas ${UPDATESCHEMA_SOURCES})
target_include_directories(UpdateSchemas PRIVATE submodules/cxxopts/include)
target_link_libraries(UpdateSchemas EntityLib)
