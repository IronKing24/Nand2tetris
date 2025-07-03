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


find_package(Doxygen)

if(Doxygen_FOUND)
  set(DOXYGEN_HAVE_DOT NO)
  set(DOXYGEN_GENERATE_HTML YES)


  doxygen_add_docs(
	project_docs ${PROJECT_SOURCE_DIR}/src
	DOXYGEN_OUTPUT_DIRECTORY(${PROJECT_SOURCE_DIR}/docs)
  )
endif()
