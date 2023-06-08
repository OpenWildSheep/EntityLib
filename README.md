# What is EntityLib
**EntityLib** is a library which allow to store and edit complex and huge json data using schemas.
# Top features
- Use **schemas** to keep your data consistent
- Import/**Instantiate**/Reference a json file in an other
- **Override** imported data
- Generate **strong typed** C++/python class for easy and safe coding
- Use **JSON schema** in VSCode for easy/safe manual edition
# How to build ?
## The easy way
Lets say you doesn't need the python binding or you have only one python installed:
 - Ensure you have **cmake** installed
 - Run the **build.bat** file. 
 - Then go in **build** and open **EntityLib.sln**.
 - Build **EntityLib**
 - Build **EntityLibPy** to get the python binding
 - Build **EntGenAPIGenerator** and run to get the strong typed API
## The hard way
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

