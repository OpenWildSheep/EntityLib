rmdir /S /Q build
cmake -B build
cmake --build build --config Release --target BuildAllButUnitTests
