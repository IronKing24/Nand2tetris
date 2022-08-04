cmake_minimum_required (VERSION 3.12)
add_executable (HackAssembler "HackAssembler.cpp" "HackAssembler.hpp" "CodeModule.cpp" "Parser.cpp" "SymbolTable.cpp")

set_property(TARGET HackAssembler PROPERTY CXX_STANDARD 20)

#set compiler warnings
if(MSVC)
    add_compile_options(/permissive /W4 /w14640 /analyze)
else()
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
