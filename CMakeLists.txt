cmake_minimum_required(VERSION 3.2)
project(test_app C)

add_definitions(-D_TEST_DEFINE)
add_definitions(-DTEST_DEFINE_VALUE=1)

file(GLOB test_app_source "source/*.c")
add_executable(test_app ${test_app_source})