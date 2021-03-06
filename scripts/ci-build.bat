

@setlocal enableextensions enabledelayedexpansion

mkdir build

cd build

set msvc_gen_name=Visual Studio

if not [x%PLATFORM:2008=%]==[x%PLATFORM%] (
    set msvc_gen_name=%msvc_gen_name% 9 2008
)

if not [x%PLATFORM:2010=%]==[x%PLATFORM%] (
    set msvc_gen_name=%msvc_gen_name% 10 2010
)

if not [x%PLATFORM:2012=%]==[x%PLATFORM%] (
    set msvc_gen_name=%msvc_gen_name% 11 2012
)

if not [x%PLATFORM:2013=%]==[x%PLATFORM%] (
    set msvc_gen_name=%msvc_gen_name% 12 2013
)

if not [x%PLATFORM:2015=%]==[x%PLATFORM%] (
    set msvc_gen_name=%msvc_gen_name% 14 2015
)

:select_arch

if not [x%PLATFORM:x64=%]==[x%PLATFORM%] set msvc_gen_name=%msvc_gen_name% Win64
cmake .. -G "%msvc_gen_name%"

cmake --build . --config Release
cmake --build . --config Debug

endlocal