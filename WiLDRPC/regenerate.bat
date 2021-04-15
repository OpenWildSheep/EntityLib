@echo off
set flatc="../../External/FlatBuffers/Release/flatc"
::set flatc="D:/WildCode/FlatBuffers/flatbuffers/out/build/x64-Debug/flatc"

:: delete previous outputs, in case we removed some schemas
rmdir /s/q cpp\WiLDRPC
rmdir /s/q python\WildRPC

:: generate all the .fbs schemas in the directory
for %%f in (*.fbs) do (
	::echo %%~ff
	%flatc% --cpp    -o .\cpp\WiLDRPC %%~ff
	%flatc% --python -o .\python\     %%~ff
)

:: replace __init__.py with the list of all generated types
(
	for %%f in (python\WildRPC\*.py) do (
		if not "%%~nf" == "__init__" (
		if not "%%~nf" == "__all__" (
			echo from . import %%~nf
		))
	)
) > python\WildRPC\__all__.py

pause
