# What is EntityLib
**EntityLib** is a library which allow to store and edit complex and huge json data using schemas.
# Top features
- Use **schemas** to keep your data consistent
- Import/**Instantiate**/Reference a json file in an other
- **Override** imported data
- Generate **strong typed** C++/python class for easy and safe coding
- Use **JSON schema** in VSCode for easy/safe manual edition
# Continuous integration
- windows: ![CI badge](https://github.com/OpenWildSheep/EntityLib/actions/workflows/cmake_msvc.yml/badge.svg)
- linux/macos ![CI badge](https://github.com/OpenWildSheep/EntityLib/actions/workflows/cmake.yml/badge.svg)
# How to build
Ensure to checkout all git submodules :
```sh
git submodule update --init --recursive
```

## The easy way
Lets say you doesn't need the python binding or you have only one python installed:
 - Ensure you have **cmake** installed
 - Run the **build.bat** or **build.sh** file. 
## The hard way

```bat
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target BuildAllButUnitTests
```
Note that you just have to build the target **BuildAllButUnitTests**. At this point the unit tests are not buildable.

If you have several python installed and want to choose which one to use.
- Ensure you have **cmake** installed and in you environment path
- Use cmake-gui or ccmake to configure your project in the directory you want (https://cmake.org/runningcmake/)
- Edit options
     - `PYTHON_INCLUDE_DIR` to point the the include directory inside your python dir
     - `PYTHON_LIBRARY` to point to the pythonXY.lib inside you python dir
 - Generate !
 - Then go in **build** and open **EntityLib.sln**.
 - Build **EntityLib**
 - Build **EntityLibPy** to get the python binding
 - Build **EntGenAPIGenerator** and run to get the strong typed API
You can do this for several python version on the same machine. Just change the target directory.


# Run unit test

You can just run the **run_unit_tests.bat** or **run_unit_tests.sh**
Or:

### Merge Custom schemas with Engine schemas
```bat
build/Release/UpdateSchemas -o build/Schemas -e DemoSchemas/EditionComponents.json,DemoSchemas/Scene-schema.json -r DemoSchemas/RuntimeComponents.json
```

```sh
build/UpdateSchemas -o build/Schemas -e DemoSchemas/EditionComponents.json,DemoSchemas/Scene-schema.json -r DemoSchemas/RuntimeComponents.json
```

This will also produce a json schemas file for each type in the subdirectory "all".
This json schema files are usable as a validator for your data files in editors like VSCode or sublime text.
### Generate the strong typed API
```bat
build/Release/EntLibAPIGenerator -s build/Schemas -d build/EntGen -r EntLibAPIGenerator/resources
```

```sh
build/EntLibAPIGenerator -s build/Schemas -d build/EntGen -r EntLibAPIGenerator/resources
```

### Run unit test
```bat
cmake --build build --config Release --target TestEntityDLL
cd Test
../build/Release/TestEntityDLL
```

```sh
cmake --build build --config Release --target TestEntityDLL
cd Test
../build/TestEntityDLL
```

# How to use EntityLib in my own project ?
- Build EntityLib ([How to build ?](#How-to-build))
- If you want to use the python binding, build EntityLibPy
- Write your schema files (or export them from your engine)
- Merge your schemas (if more than one file) ([Merge Custom schemas with Engine schemas](#Merge-Custom-schemas-with-Engine-schemas))
- Generate strong typed API (optional)  ([Generate the strong typed API](#Generate-the-strong-typed-API))
- For a c++ project, link EntityLib.lib
- For a python project, import EntityLibPy.pyd
