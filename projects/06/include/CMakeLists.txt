include(FetchContent)

FetchContent_Declare(
	GoogleTest
	GIT_REPOSITORY	https://github.com/google/googletest.git
	GIT_TAG			release-1.12.1
	SOURCE_DIR		${HackAssembler_SOURCE_DIR}/include/gtest
	BINARY_DIR		${HackAssembler_BINARY_DIR}/include/gtest
)

if(WIN32)
	set(gtest_force_shared_crt ON CACHE BOOL "False" FORCE)
endif()

set(BUILD_GMOCK OFF)
set(INSTALL_GTEST OFF)

FETCHCONTENT_MAKEAVAILABLE(GoogleTest)