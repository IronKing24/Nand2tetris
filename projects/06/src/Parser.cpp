#include "Parser.hpp"

namespace HackAssembler
{
    Parser::Parser(std::ifstream* file)
    {
        asmFile = file;
    }

    bool Parser::hasMoreLines()
    {
        return asmFile->peek() != EOF;
    }

    void Parser::advance()
    {
        //avoid comments and white spaces.
        while (Parser::hasMoreLines())
        {
            std::getline(*asmFile, *currentInstruction, '\n');

            //whitespace handling
            if (currentInstruction->find_first_not_of(" \r\n\t\v\f") == std::string::npos)
            {
                continue;
            }

            //trim head.
            if (std::isspace(currentInstruction->at(0)))
            {
                std::_String_iterator<std::_String_val<std::_Simple_types<char>>> textStart = std::find_if(
                    currentInstruction->begin(), currentInstruction->end(), 
                    [](char c) 
                    {
                        return !std::isspace<char>(c, std::locale::classic());
                    });
                currentInstruction->erase(currentInstruction->begin(), textStart);
            }
            //trim tail
            if (std::isspace(currentInstruction->at(currentInstruction->length() - 1)))
            {
                std::reverse_iterator<std::_String_iterator<std::_String_val<std::_Simple_types<char>>>> textEnd = std::find_if(
                    currentInstruction->rbegin(), currentInstruction->rend(), 
                    [](char s) 
                    {
                        return !std::isspace<char>(s, std::locale::classic());
                    });
                currentInstruction->erase(textEnd.base(), currentInstruction->end());
            }
            

            //comment handling 
            std::size_t commentIndex = currentInstruction->find("//");

            switch (commentIndex)
            {
            case 0:
                continue;
            case std::string::npos:
                break;
            default:
                //comment follows the instruction
                currentInstruction->erase(commentIndex, std::string::npos);
                break;
            }
        }

        //set type
        if(currentInstruction->at(0) == '@')
        {
            if (std::isdigit(currentInstruction->at(1)))
            {
                currentInstructionType = Parser::A_instruction;
            }
            else
            {
                currentInstructionType = Parser::L_instruction;
            }
        }
        else
        {
            currentInstructionType = Parser::C_instruction;
        }
        
        //BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
        //tokenize the instruction
        
    }

    Parser::instruction* Parser::instructionType()
    {
        return &currentInstructionType;
    }
    
    std::string* Parser::symbol() 
    {   
        if (Parser::currentInstructionType == Parser::A_instruction || Parser::currentInstructionType == Parser::L_instruction)
        {
            return &Parser::currentInstructionTokens[0];
        }
        else
        {
            
        }
    }
    
    std::string* Parser::dest()
    {
        if (Parser::currentInstructionType == Parser::C_instruction)
        {    
           return &Parser::currentInstructionTokens[0];
        } 
        else
        {

        }
    }

    std::string* Parser::comp()
    {
        if (Parser::currentInstructionType == Parser::C_instruction)
        {
            return &Parser::currentInstructionTokens[1];
        }
        else
        {

        }
    }
    
    std::string* Parser::jump()
    {

    }

    Parser::~Parser()
    {
        delete [] currentInstructionTokens;
    }
}
