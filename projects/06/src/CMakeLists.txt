cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable(${CMAKE_PROJECT_NAME} Main.cpp Parser.cpp CodeModule.cpp SymbolTable.cpp)

# Set compile specs
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
install(TARGETS ${CMAKE_PROJECT_NAME})