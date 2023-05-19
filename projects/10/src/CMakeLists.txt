cmake_minimum_required (VERSION 3.8)

add_executable (VMTranslator  "JackTokenizer.cpp"  "CompilationEngine.h")
target_compile_features(VMTranslator PRIVATE cxx_std_17)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED NO)
set(CXX_EXTENSIONS OFF)

add_executable(VMTranslator_without_bootstrap  "JackTokenizer.cpp"  "CompilationEngine.h")
target_compile_features(VMTranslator_without_bootstrap PRIVATE cxx_std_17)
target_compile_definitions(VMTranslator_without_bootstrap PRIVATE WBS)

if (MSVC)
	add_compile_options($<$<CONFIG:Debug>:/permissive /W4 /w14640>)
else()
	add_compile_options($<$<CONFIG:Debug>:-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic>)
endif()