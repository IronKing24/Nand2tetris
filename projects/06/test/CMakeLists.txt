cmake_minimum_required (VERSION 3.8)

find_program(Python python)

if(Python)
    add_test(${Python} ${CMAKE_SOURCE_DIR}/test/test.py)
endif()