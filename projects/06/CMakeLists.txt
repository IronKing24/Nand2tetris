cmake_minimum_required (VERSION 3.11)

project (
	"HackAssembler" 
	VERSION			2.0.0
	DESCRIPTION		"The Hack assembler, converts Hack assembly to Hack binary."
	HOMEPAGE_URL	https://github.com/IronKing24/Nand2tetris
	LANGUAGES		CXX
)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED NO)
set(CXX_EXTENSIONS OFF)


enable_testing()

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("include")
add_subdirectory ("test")

