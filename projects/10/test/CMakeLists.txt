enable_testing()

include(GoogleTest)

#parser test
add_executable(ParserTest src/ParserTest.cpp)
target_link_directories(ParserTest INTERFACE ${VMTranslator_SOURCE_DIR}/src)
add_library(Parser STATIC "../src/JackTokenizer.cpp")
target_link_libraries(ParserTest PRIVATE Parser gtest_main)
gtest_add_tests(
	TARGET ParserTest 
	WORKING_DIRECTORY ${VMTranslator_SOURCE_DIR}/test/res/parser
)

#Vm test
find_package(Python)
find_package(Java)

if(Python_Interpreter_FOUND AND Java_FOUND)
	file(WRITE 
	${VMTranslator_SOURCE_DIR}/test/src/args.py
"exe=\"${CMAKE_BINARY_DIR}/src/${CMAKE_BUILD_TYPE}\"
res=\"${CMAKE_SOURCE_DIR}/test/res/VMTranslator\"
tools=\"${CMAKE_SOURCE_DIR}/../../tools\"
ext=\"${CMAKE_EXECUTABLE_SUFFIX}\""
	)
elseif(NOT Python_Interpreter_FOUND)
	message("Python was not found, intigration test skipped.")
elseif(NOT Java_FOUND)
	message("Java was not found, intigration test skipped.")
else()
	message("Python or Java were not found, intigration test skipped.")
endif()


