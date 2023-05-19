cmake_minimum_required (VERSION 3.8)
enable_testing()

project (
	"JackAnalyzer"
	VERSION			1.5.0
	DESCRIPTION		"The Jack compiler, converts the Jack programming language to VM commands."
	HOMEPAGE_URL	https://github.com/IronKing24/Nand2tetris
	LANGUAGES		CXX
)

# Include sub-projects.
add_subdirectory ("include")
add_subdirectory ("src")
add_subdirectory ("test")