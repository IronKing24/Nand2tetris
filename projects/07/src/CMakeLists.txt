cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${CMAKE_PROJECT_NAME} "Main.cpp" "Parser.cpp" "CodeWriter.cpp")

#set compile specs
target_compile_features(VMTranslator PRIVATE cxx_std_17)
set(CXX_STANDARD 17) 
set(CXX_STANDARD_REQUIRED NO)
set(CXX_EXTENSIONS OFF)

if (MSVC)
	add_compile_options($<$<CONFIG:Debug>:/permissive /W4 /w14640 /DEBUG>)
else()
	add_compile_options($<$<CONFIG:Debug>:-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -DEBUG>)
endif()