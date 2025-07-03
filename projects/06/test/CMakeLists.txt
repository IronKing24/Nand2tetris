enable_testing()

include(GoogleTest)

#parser test
add_executable(ParserTest src/ParserTest.cpp)
target_include_directories(ParserTest INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ParserTest PRIVATE gtest_main)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/parser/test.asm ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
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


#Hack assembler test
find_package(Python)

if(Python_Interpreter_FOUND)
#	file(WRITE
#	${HackAssembler_SOURCE_DIR}/test/src/conf.py
#"res=\"${CMAKE_SOURCE_DIR}/test/res/HackAssembler\"
#")
#
#	get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
#
#	if(${isMultiConfig})
#		file(APPEND
#			${HackAssembler_SOURCE_DIR}/test/src/conf.py
#			"exe=\"${HackAssembler_BINARY_DIR}/src/${CMAKE_CONFIGURATION_TYPE}/${CMAKE_PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}\"")
#	else()
#		file(APPEND
#			${HackAssembler_SOURCE_DIR}/test/src/conf.py
#			"exe=\"${HackAssembler_BINARY_DIR}/src/${CMAKE_PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}\"")
#	endif()



else()
	message("Python was not found, intigration test skipped.")
endif()
