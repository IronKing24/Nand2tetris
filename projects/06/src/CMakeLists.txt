cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
add_executable (HackAssembler "HackAssembler.cpp" "HackAssembler.hpp" "CodeModule.cpp" "Parser.cpp" "SymbolTable.cpp")

#set compiler warnings
if(MSVC)
    add_compile_options(/permissive /W4 /w14640 /analyze)
else()
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
