#pragma once
#include <cstdio>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace HackAssembler
{
/*
*This module provides services for translating symbolic Hack mnemonics
*into their binary codes. Specifically, it translates symbolic Hack mnemonics
*into their binary codes according to the language specifications
*/
class CodeModule
{
    public:
	/**
    * \brief Returns the binary code for the dest mnemonic.
    */
	const std::string &dest(const std::string &dest);

	/**
    * \brief Returns the binary code for the comp mnemonic.
    */
	const std::string &comp(const std::string &comp);

	/**
    * \brief Returns the binary code for the jump mnemonic.
    */
	const std::string &jump(const std::string &jump);

    private:
	const std::unordered_map<std::string, const std::string> dests = {
	    {"null", "000"}, {"M", "001"},   {"D", "010"},   {"DM", "011"},
	    {"MD", "011"},   {"A", "100"},   {"AM", "101"},  {"MA", "101"},
	    {"AD", "110"},   {"DA", "110"},  {"ADM", "111"}, {"AMD", "111"},
	    {"MAD", "111"},  {"MDA", "111"}, {"DAM", "111"}, {"DMA", "111"}};

	const std::unordered_map<std::string, const std::string> comps = {
	    {"0", "0101010"},	{"1", "0111111"},   {"-1", "0111010"},
	    {"D", "0001100"},	{"A", "0110000"},   {"M", "1110000"},
	    {"!D", "0001101"},	{"!A", "0110001"},  {"!M", "1110001"},
	    {"-D", "0001111"},	{"-A", "0110011"},  {"-M", "1110011"},
	    {"D+1", "0011111"}, {"1+D", "0011111"}, {"A+1", "0110111"},
	    {"1+A", "0110111"}, {"M+1", "1110111"}, {"1+M", "1110111"},
	    {"D-1", "0001110"}, {"A-1", "0110010"}, {"M-1", "1110010"},
	    {"D+A", "0000010"}, {"A+D", "0000010"}, {"D+M", "1000010"},
	    {"M+D", "1000010"}, {"D-A", "0010011"}, {"D-M", "1010011"},
	    {"A-D", "0000111"}, {"M-D", "1000111"}, {"D&A", "0000000"},
	    {"A&D", "0000000"}, {"D&M", "1000000"}, {"M&D", "1000000"},
	    {"D|A", "0010101"}, {"A|D", "0010101"}, {"D|M", "1010101"},
	    {"M|D", "1010101"}};

	const std::unordered_map<std::string, const std::string> jumps = {
	    {"null", "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"},
	    {"JLT", "100"},  {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"}};
};
} // namespace HackAssembler
