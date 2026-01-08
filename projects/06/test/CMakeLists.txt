enable_testing()

include(GoogleTest)

#parser test
add_executable(ParserTest src/ParserTest.cpp)
target_include_directories(ParserTest INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ParserTest PRIVATE gtest_main)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/parser/test.asm ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
gtest_add_tests(TARGET ParserTest)

#Symbol table test
add_executable(SymbolTableTest src/SymbolTableTest.cpp)
target_sources(SymbolTableTest PRIVATE ${CMAKE_SOURCE_DIR}/src/SymbolTable.h)
target_link_libraries(SymbolTableTest PRIVATE gtest_main)
gtest_add_tests(TARGET SymbolTableTest)

#Code module test
add_executable(CodeModuleTest src/CodeModuleTest.cpp)
target_sources(CodeModuleTest PRIVATE ${CMAKE_SOURCE_DIR}/src/CodeModule.h)
target_link_libraries(CodeModuleTest PRIVATE gtest_main)
gtest_add_tests(TARGET CodeModuleTest)