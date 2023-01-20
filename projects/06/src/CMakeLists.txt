cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (HackAssembler "Main.cpp" "Parser.cpp" "CodeModule.cpp" "SymbolTable.cpp")

#Clang tools
set(CMAKE_CXX_CLANG_TIDY clang-tidy)

#set compile specs
target_compile_features(HackAssembler PRIVATE cxx_std_17)
set_target_properties(HackAssembler PROPERTIES 
CXX_STANDARD 17 
CXX_EXTENSIONS OFF
CXX_EXTENSIONS NO
)

if(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
	if (MSVC)
		add_compile_options(/permissive /W4 /w14640)
	else()
		add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
	endif()
endif()