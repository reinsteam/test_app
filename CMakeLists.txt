cmake_minimum_required(VERSION 3.2)
project(test_app C)

add_definitions(-D_TEST_DEFINE)
add_definitions(-DTEST_DEFINE_VALUE=1)

if (MSVC)
    set(CMAKE_C_FLAGS "/c /nologo /Wall /WX /Za /GR-")
    set(CMAKE_C_FLAGS_RELEASE "/O2 /GL /GS-")
    set(CMAKE_C_FLAGS_DEBUG "/Od /GL- /GS")

elif(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "-MD -std=c89 -Weverything")

else()

    set(CMAKE_C_FLAGS "-x c -ansi -std=c89 -O2 -fno-exceptions -Wall -Wextra -Wpedantic")
    set( CMAKE_VERBOSE_MAKEFILE on )

endif()

message( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )
message( STATUS "CMAKE_C_FLAGS_RELEASE: " ${CMAKE_C_FLAGS_RELEASE} )
message( STATUS "CMAKE_C_FLAGS_DEBUG: " ${CMAKE_C_FLAGS_DEBUG} )
message( STATUS "CMAKE_LD_FLAGS: " ${CMAKE_LD_FLAGS} )

file(GLOB test_app_source "source/*.c")
add_executable(test_app ${test_app_source})