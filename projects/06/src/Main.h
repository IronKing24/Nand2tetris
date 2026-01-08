#pragma once
#include "CodeModule.h"
#include "Parser.h"
#include "SymbolTable.h"
#include <algorithm>
#include <bitset>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

#define data_width 16

namespace HackAssembler
{
/**
* \brief Goes through the assembly file finding lables and registering their numeric representation.
* \param parser A \c Parser class loaded with the assembly file stream.
*/
void firstPass(HackAssembler::Parser &parser);

/**
* \brief Goes through the assembly file translating instructions to binary.
* \param parser A \c Parser class
* loaded with the assembly file stream.
* \param output Output file stream of the hack binary file.
*/
void secondPass(HackAssembler::Parser &parser, std::ofstream &output);
} // namespace HackAssembler