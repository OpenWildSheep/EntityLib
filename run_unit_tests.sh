./build.sh

build/UpdateSchemas -o build/Schemas -e DemoSchemas/EditionComponents.json,DemoSchemas/Scene-schema.json -r DemoSchemas/RuntimeComponents.json
build/EntLibAPIGenerator -s build/Schemas -d build/EntGen -r EntLibAPIGenerator/resources
cmake --build build --config Release --target TestEntityDLL
cd Test
../build/TestEntityDLL