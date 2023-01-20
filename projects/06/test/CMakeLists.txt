cmake_minimum_required (VERSION 3.8)

enable_testing()

include(GoogleTest)

#parser test
add_executable(ParserTest src/ParserTest.cpp)
target_link_directories(ParserTest INTERFACE ${HackAssembler_SOURCE_DIR}/src)
add_library(Parser STATIC ${HackAssembler_SOURCE_DIR}/src/Parser.cpp)
target_link_libraries(ParserTest PRIVATE Parser gtest_main)
gtest_add_tests(
	TARGET ParserTest 
	WORKING_DIRECTORY ${HackAssembler_SOURCE_DIR}/test/res/parser
)

#Symbol table test
add_executable(SymbolTableTest src/SymbolTableTest.cpp)
target_link_directories(SymbolTableTest INTERFACE ${HackAssembler_SOURCE_DIR}/src)
add_library(SymbolTable STATIC ${HackAssembler_SOURCE_DIR}/src/SymbolTable.cpp)
target_link_libraries(SymbolTableTest PRIVATE SymbolTable gtest_main)
gtest_add_tests(TARGET SymbolTableTest)

#Code module test
add_executable(CodeModuleTest src/CodeModuleTest.cpp)
target_link_directories(CodeModuleTest INTERFACE ${HackAssembler_SOURCE_DIR}/src)
add_library(CodeModule STATIC ${HackAssembler_SOURCE_DIR}/src/CodeModule.cpp)
target_link_libraries(CodeModuleTest PRIVATE CodeModule gtest_main)
gtest_add_tests(TARGET CodeModuleTest)
	
#Hack assembler test
find_package(Python)

if(Python_Interpreter_FOUND)
	file(WRITE 
	${HackAssembler_SOURCE_DIR}/test/src/args.py
	"exe=\"${CMAKE_BINARY_DIR}/src/${CMAKE_CONFIGURATION_TYPES}/HackAssembler${CMAKE_EXECUTABLE_SUFFIX}\""
	)
	add_test(
		NAME "HackAssemblerTest.HackFiles"
		COMMAND ${Python_EXECUTABLE} -m unittest -v test_HackAssembler.py 
		WORKING_DIRECTORY ${HackAssembler_SOURCE_DIR}/test/res/HackAssembler/test/src
	)
else()
	message("Python was not found, intigration test skipped.")
endif()