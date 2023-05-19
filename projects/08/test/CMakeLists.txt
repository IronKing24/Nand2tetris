enable_testing()

include(GoogleTest)

#parser test
add_executable(ParserTest src/ParserTest.cpp)
target_link_directories(ParserTest INTERFACE ${VMTranslator_SOURCE_DIR}/src)
add_library(Parser STATIC ${VMTranslator_SOURCE_DIR}/src/Parser.cpp)
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
	${VMTranslator_SOURCE_DIR}/test/src/conf.py
"res=\"${CMAKE_SOURCE_DIR}/test/res/VMTranslator\"
tools=\"${CMAKE_SOURCE_DIR}/../../tools\"
ext=\"${CMAKE_EXECUTABLE_SUFFIX}\"
"
	)
	get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
	if(${isMultiConfig})
		file(APPEND
			${VMTranslator_SOURCE_DIR}/test/src/conf.py
			"exe=\"${VMTranslator_BINARY_DIR}/src/${CMAKE_CONFIGURATION_TYPE}/\"")
	else()
		file(APPEND
			${VMTranslator_SOURCE_DIR}/test/src/conf.py
			"exe=\"${VMTranslator_BINARY_DIR}/src/\"")
	endif()
elseif(NOT Python_Interpreter_FOUND)
	message("Python was not found, intigration test skipped.")
elseif(NOT Java_FOUND)
	message("Java was not found, intigration test skipped.")
else()
	message("Python or Java were not found, intigration test skipped.")
endif()


