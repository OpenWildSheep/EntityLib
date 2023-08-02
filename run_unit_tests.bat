call build.bat

build\Release\UpdateSchemas -o build/Schemas -e DemoSchemas/EditionComponents.json,DemoSchemas/Scene-schema.json -r DemoSchemas/RuntimeComponents.json
build\Release\EntLibAPIGenerator -s build/Schemas -d build/EntGen -r EntLibAPIGenerator/resources
cmake --build build --config Release --target TestEntityDLL
cd Test
..\build\Release\TestEntityDLL