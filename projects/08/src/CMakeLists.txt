cmake_minimum_required (VERSION 3.8)

add_executable (${CMAKE_PROJECT_NAME} "Main.cpp" "Parser.cpp" "CodeWriter.cpp")
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
install(TARGETS ${CMAKE_PROJECT_NAME})

add_executable(${CMAKE_PROJECT_NAME}_bootstrap "Main.cpp" "Parser.cpp" "CodeWriter.cpp")
target_compile_features(${CMAKE_PROJECT_NAME}_bootstrap PRIVATE cxx_std_17)
target_compile_definitions(${CMAKE_PROJECT_NAME}_bootstrap PRIVATE WOBS)
install(TARGETS ${CMAKE_PROJECT_NAME}_bootstrap)
