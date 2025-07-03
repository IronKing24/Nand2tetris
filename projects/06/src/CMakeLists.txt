# Add source to this project's executable.
add_executable(${CMAKE_PROJECT_NAME} Main.cpp Parser.cpp CodeModule.cpp SymbolTable.cpp)

# Set compile specs
target_compile_features(HackAssembler PRIVATE cxx_std_17)

if (MSVC)
	add_compile_options($<$<CONFIG:Debug>:/permissive /W4 /w14640>)
else()
	add_compile_options($<$<CONFIG:Debug>:-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic>)
endif()
