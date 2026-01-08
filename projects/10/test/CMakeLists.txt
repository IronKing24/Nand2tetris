enable_testing()

include(GoogleTest)

#parser test
add_executable(JackTokenizerTest ${JackAnalyzer_SOURCE_DIR}/src/JackTokenizer.h ${JackAnalyzer_SOURCE_DIR}/src/JackTokenizer.cpp src/JackTokenizerTest.cpp)
target_compile_definitions(JackTokenizerTest PRIVATE TIXML_USE_STL)
target_link_libraries(JackTokenizerTest PRIVATE gtest_main tinyxml2::tinyxml2)
file(COPY ${CMAKE_SOURCE_DIR}/test/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
gtest_add_tests(TARGET JackTokenizerTest)