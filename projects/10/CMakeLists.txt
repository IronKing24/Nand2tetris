cmake_minimum_required (VERSION 3.11)

project (
	"JackAnalyzer"
	VERSION			0.5.0
	DESCRIPTION		"The Jack compiler, converts the Jack programming language to XML AST."
	HOMEPAGE_URL	https://github.com/IronKing24/Nand2tetris
	LANGUAGES		CXX
)

enable_testing()

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("include")
add_subdirectory ("test")
add_subdirectory ("docs")
