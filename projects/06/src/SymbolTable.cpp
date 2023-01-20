#pragma once
#include "SymbolTable.h"

namespace HackAssembler
{
	SymbolTable::SymbolTable()
	{
		SymbolTable::symbolTable = {
			{"R0", 0},
			{"R1", 1},
			{"R2", 2},
			{"R3", 3},
			{"R4", 4},
			{"R5", 5},
			{"R6", 6},
			{"R7", 7},
			{"R8", 8},
			{"R9", 9},
			{"R10", 10},
			{"R11", 11},
			{"R12", 12},
			{"R13", 13},
			{"R14", 14},
			{"R15", 15},
			{"SP", 0},
			{"LCL", 1},
			{"ARG", 2},
			{"THIS", 3},
			{"THAT", 4},
			{"SCREEN", 0x4000},
			{"KBD", 0x6000}
		};
	}
	
	SymbolTable::~SymbolTable()
	{
		SymbolTable::symbolTable.clear();
	}
	
	void SymbolTable::addEntry(const std::string& symbol, const unsigned short int address) 
	{
		if (address > 65535)
		{
			throw std::runtime_error("Buffer overflow caused by symbol: " + symbol + "and an address value of: " + std::to_string(address));
		}
		SymbolTable::symbolTable.insert({symbol, address});
	}

	const bool SymbolTable::contains(const std::string& symbol) noexcept
	{
		return SymbolTable::symbolTable.find(symbol) != SymbolTable::symbolTable.cend();
	}

	const unsigned short int SymbolTable::getAddress(const std::string& symbol)
	{
		return SymbolTable::symbolTable[symbol];
	}
}