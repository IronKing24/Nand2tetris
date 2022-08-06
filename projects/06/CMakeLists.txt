cmake_minimum_required (VERSION 3.8)

project ("HackAssembler" VERSION 2.0.0 
DESCRIPTION "Nand2tetris HackAssembler, compiles hack assembly instructions to hack binary.")

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("test")
