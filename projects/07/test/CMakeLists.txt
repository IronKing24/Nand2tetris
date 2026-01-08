enable_testing()

include(GoogleTest)

#parser test
add_executable(ParserTest src/ParserTest.cpp)
target_include_directories(ParserTest INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ParserTest PRIVATE gtest_main)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/Parser/test.vm ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
gtest_add_tests(TARGET ParserTest)
