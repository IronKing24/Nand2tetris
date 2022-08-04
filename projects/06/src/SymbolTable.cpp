#include "SymbolTable.hpp"

namespace HackAssembler 
{
    SymbolTable::SymbolTable()
    {
        definedLabels = new std::unordered_map<std::string, int>({
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
            });
    }


    void SymbolTable::addEntry(std::string* symbol, int address)
    {
        definedLabels->insert({*symbol, address});
    }

    bool* SymbolTable::contains(std::string* symbol)
    {
        return &definedLabels->contains(*symbol);
    }

    int* SymbolTable::getAddress(std::string* symbol)
    {
        return &definedLabels->at(*symbol);
    }

    SymbolTable::~SymbolTable()
    {
        delete definedLabels;
    }
}