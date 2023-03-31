#!/bin/sh
p4_root=`p4 -F %clientRoot% -ztag info`
echo P4_ROOT is $p4_root

echo Build EntityLib
vs16path="C:/Program Files (x86)/SCE/Common/SceVSI-VS16/bin/vs16build.exe"

if ! "$vs16path" EntityLib/EntityLib2019.sln //build "Release|x64" //project EntityLib/EntityLib/EntityLib2019.vcxproj //sn-dbs; then
	echo Build EntityLib2019 Failed
	exit 1
fi
if ! "$vs16path" EntityLib/EntityLib2019.sln //build "Release|x64" //project EntityLib/UpdateSchemas/UpdateSchemas2019.vcxproj //sn-dbs; then
	echo Build UpdateSchemas2019 Failed
	exit 1
fi
if ! "$vs16path" EntityLib/EntityLib2019.sln //build "Release|x64" //project EntityLib/EntLibAPIGenerator/EntLibAPIGenerator.vcxproj //sn-dbs; then
	echo Build EntLibAPIGenerator Failed
	exit 1
fi

echo Generate the EntGen API
if ! EntityLib/x64/Release/EntLibAPIGenerator.exe EntityLib/EntLibAPIGenerator/resources EntityLib/EntGen "$p4_root"; then
	echo EntLibAPIGenerator Failed
	exit 1
fi

echo Merge Runtime schemas with edition schemas into MergesComponents.json
if ! EntityLib/x64/Release/UpdateSchemas.exe $p4_root/Tools; then
	echo UpdateSchemas Failed
	exit 1
fi

echo Build is ok.
exit 0

