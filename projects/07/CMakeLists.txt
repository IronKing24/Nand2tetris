# CMakeList.txt : CMake project for HackVM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (
	"VMTranslator"
	VERSION			1.5.0
	DESCRIPTION		"The Hack VM translator, converts Hack VM calls to Hack assembly."
	HOMEPAGE_URL	https://github.com/IronKing24/Nand2tetris
	LANGUAGES		CXX
)

# Include sub-projects.
add_subdirectory ("include")
add_subdirectory ("src")
add_subdirectory ("test")
