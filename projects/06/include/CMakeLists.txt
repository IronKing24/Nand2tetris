cmake_minimum_required (VERSION 3.11)

include(FetchContent)

FetchContent_Declare(
	Gtest
	GIT_REPOSITORY	https://github.com/google/googletest.git
	GIT_TAG			release-1.12.1
	SOURCE_DIR		${HackAssembler_SOURCE_DIR}/include/gtest
)

add_subdirectory("gtest")

if(WIN32)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
