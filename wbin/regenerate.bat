@echo off
set flatc="../../External/FlatBuffers/Release/flatc"
::set flatc="D:/WildCode/FlatBuffers/flatbuffers/out/build/x64-Debug/flatc"

:: generate all the .fbs schemas in the directory
for %%f in (*.fbs) do (
	::echo %%~ff
	%flatc% --cpp    --gen-object-api --gen-mutable %%~ff
	%flatc% --python --gen-object-api --gen-mutable %%~ff
)

:: replace __init__.py with the list of all generated types
(
	for %%f in (WBIN\*.py) do (
		if not "%%~nf" == "__init__" (
		if not "%%~nf" == "__all__" (
			echo from . import %%~nf
		))
	)
) > WBIN\__all__.py
