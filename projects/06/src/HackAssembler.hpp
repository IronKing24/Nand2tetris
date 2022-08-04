#pragma once
#include "Parser.hpp"
#include "CodeModule.hpp"
#include "SymbolTable.hpp"

namespace HackAssembler
{
    class HackAssembler
    {
        int main(int argc, char* argv[]);
        void firstPass(const Parser* parser);
        void secondPass(const Parser*, std::ofstream);
        inline std::string* toHackBinary(const int value);
    };
}