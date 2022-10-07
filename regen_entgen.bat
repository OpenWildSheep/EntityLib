for /f %%i in ('p4 -F %%clientRoot%% -ztag info') do set rootFolder=%%i
echo P4_ROOT is %rootFolder%

echo Build EntityLib
cd EntityLib
call "C:\Program Files (x86)\SCE\Common\SceVSI-VS16\bin\vs16build.exe" "EntityLib2019.sln" /build "Release|x64" /project "UpdateSchemas\UpdateSchemas2019.vcxproj" /sn-dbs
if %ERRORLEVEL% NEQ 0 goto error
call "C:\Program Files (x86)\SCE\Common\SceVSI-VS16\bin\vs16build.exe" "EntityLib2019.sln" /build "Release|x64" /project "EntLibAPIGenerator\EntLibAPIGenerator.vcxproj" /sn-dbs
if %ERRORLEVEL% NEQ 0 goto error

echo Merge Runtime schemas with edition schemas into MergesComponents.json
call "x64\Release\UpdateSchemas.exe" %rootFolder%/Tools
if %ERRORLEVEL% NEQ 0 goto error

echo Generate the EntGen API
call "x64\Release\EntLibAPIGenerator.exe" EntLibAPIGenerator/resources EntGen %rootFolder%
if %ERRORLEVEL% NEQ 0 goto error
cd ..

echo Build is ok.
exit /B 0

:error
echo Failed
exit /B 1