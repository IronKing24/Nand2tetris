cmake_minimum_required (VERSION 3.8)

find_package(TinyXml2)

add_executable (${CMAKE_PROJECT_NAME}  "Main.h" "Main.cpp" "JackTokenizer.h" "JackTokenizer.cpp")
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE TIXML_USE_STL)
target_link_libraries(${CMAKE_PROJECT_NAME} tinyxml2::tinyxml2)
install(TARGETS ${CMAKE_PROJECT_NAME})