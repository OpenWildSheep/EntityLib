"../build/Release/UpdateSchemas.exe" -o ../build/Schemas -e ../DemoSchemas/EditionComponents.json,../DemoSchemas/Scene-schema.json -r ../DemoSchemas/RuntimeComponents.json
"../build/Release/EntLibAPIGenerator.exe" -s ../build/Schemas -d ../build/EntGen
pause