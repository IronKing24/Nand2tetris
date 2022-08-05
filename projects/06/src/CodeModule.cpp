#include "CodeModule.hpp"

namespace HackAssembler
{
    CodeModule::CodeModule()
    {
        destValue = new std::unordered_map<std::string, std::string>({
            {"","000"},
            {"M","001"},
            {"D","010"},
            {"DM","011"},
            {"MD","011"},
            {"A","100"},
            {"AM","101"},
            {"MA","101"},
            {"AD","110"},
            {"DA","110"},
            {"ADM","111"},
            {"DAM","111"},
            {"MAD","111"},
            {"AMD","111"},
            {"DMA","111"},
            {"MDA","111"},
            });
        
        compValue = new std::unordered_map<std::string, std::string>({ 
            {"0", "0101010"},
            {"1", "0111111"},
            {"-1", "0111010"},
            {"D", "0001100"},
            {"A", "0110000"},
            {"M", "1110000"},
            {"!D", "0001101"},
            {"!A", "0110001"},
            {"!M", "1110001"},
            {"-D", "0001111"},
            {"-A", "0110011"},
            {"-M", "1110011"},
            {"D+1", "0011111"},
            {"1+D", "0011111"},
            {"A+1", "0110111"},
            {"M+1", "1110111"},
            {"1+A", "0110111"},
            {"1+M", "1110111"},
            {"D-1", "0001110"},
            {"A-1", "0110010"},
            {"M-1", "1110010"},
            {"A+D", "0000010"},
            {"D+A", "0000010"},
            {"M+D", "1000010"},
            {"D+M", "1000010"},
            {"A-M", "1010011"},
            {"D-M", "1010011"},
            {"A-D", "0000111"},
            {"M-D", "1000111"},
            {"A&D", "0000000"},
            {"D&A", "0000000"},
            {"M&D", "1000000"},
            {"D&M", "1000000"},
            {"A|D", "0010101"},
            {"D|A", "0010101"},
            {"M|D", "1010101"},
            {"D|M", "1010101"}
            });
        
        jumpValue = new std::unordered_map<std::string, std::string>({
            {"","000"},
            {"JGT","001"},
            {"JEQ","010"},
            {"JGE","011"},
            {"JLT","100"},
            {"JNE","101"},
            {"JLE","110"},
            {"JMP","111"},
            });
    }

    std::unique_ptr<std::string> CodeModule::dest(std::string* label)
    {
        return std::make_unique<std::string>(destValue->at(*label));
    }

    std::unique_ptr<std::string> CodeModule::comp(std::string* label)
    {
        return std::make_unique<std::string>(compValue->at(*label));
    }

    std::unique_ptr<std::string> CodeModule::jmp(std::string* label)
    {
        return std::make_unique<std::string>(jumpValue->at(*label));
    }

    CodeModule::~CodeModule()
    {
        delete destValue;
        delete compValue;
        delete jumpValue;
    }
}