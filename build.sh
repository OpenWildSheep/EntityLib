rm -d -f -r build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target BuildAllButUnitTests
