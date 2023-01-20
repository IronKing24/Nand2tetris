cmake_minimum_required (VERSION 3.8)

project (
"HackAssembler" 
VERSION			2.0.0
DESCRIPTION		"The Hack assembler, converts Hack assembly to Hack binary"
HOMEPAGE_URL	https://github.com/IronKing24/Nand2tetris
LANGUAGES		CXX
)

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("include")

#debug levels
if(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
	enable_testing()
	add_subdirectory ("test")
endif()


