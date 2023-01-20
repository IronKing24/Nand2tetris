#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <bitset>
#include <algorithm>
#include <string>

#include "Parser.h"
#include "SymbolTable.h"
#include "CodeModule.h"

namespace HackAssembler 
{
	HackAssembler::SymbolTable symbol_table;
	HackAssembler::CodeModule code_module;
	unsigned short int available_memory = 16;

	///<summary>Goes through the assembly file finding lables and registering their numaric representaion.</summary>
	///<param name='parser'>Loaded with the assembly file stream.</param>
	void FirstPass(HackAssembler::Parser& parser);

	///<summary>Goes through the assembly file translating instructions to binary.</summary>
	///<param name='parser'>Loaded with the assembly file stream.</param>
	///<param name='parser'>Output file stream of the hack binary file.</param>
	void SecondPass(HackAssembler::Parser& parser, std::ofstream& output);
}