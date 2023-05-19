#pragma once
#include <algorithm>
#include <bitset>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "CodeModule.h"
#include "Parser.h"
#include "SymbolTable.h"

#define data_width 16

namespace HackAssembler
{
	HackAssembler::SymbolTable symbol_table;
	HackAssembler::CodeModule code_module;
	uint16_t available_memory = 16;

	/**
	 * \brief Goes through the assembly file finding lables and registering their numeric representation. 
	 * \param parser A \c Parser class loaded with the assembly file stream.
	 */
	void firstPass(HackAssembler::Parser &parser);

	/**
	 * \brief Goes through the assembly file translating instructions to binary.
	 * \param parser A \c Parser class loaded with the assembly file stream.
	 * \param output Output file stream of the hack binary file.
	 */
	void secondPass(HackAssembler::Parser &parser, std::ofstream &output);
}