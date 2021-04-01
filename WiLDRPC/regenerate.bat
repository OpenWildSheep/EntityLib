@echo off
set flatc="../../External/FlatBuffers/Release/flatc"
::set flatc="D:/WildCode/FlatBuffers/flatbuffers/out/build/x64-Debug/flatc"

:: generate all the .fbs schemas in the directory
for %%f in (*.fbs) do (
	::echo %%~ff
	%flatc% --cpp    %%~ff
	%flatc% --python %%~ff
)
