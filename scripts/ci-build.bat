@echo off

@setlocal enableextensions enabledelayedexpansion

mkdir build

cd build

set msvc_gen_name=Visual Studio 9 2008

if not [x%PLATFORM:x64=%]==[x%PLATFORM%] set msvc_gen_name=%msvc_gen_name% Win64
cmake .. -G "%msvc_gen_name%"

cmake --build . --config Release
cmake --build . --config Debug

endlocal