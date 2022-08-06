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

    void Parser::advance() noexcept(false)
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
            if (bool(std::isspace(currentInstruction->at(0))))
            {
                std::_String_iterator<std::_String_val<std::_Simple_types<char>>> textStart = 
                    std::find_if(currentInstruction->begin(), currentInstruction->end(),[](char c) 
                    { return !bool(std::isspace(c));
                    });
                currentInstruction->erase(currentInstruction->begin(), textStart);
            }
            //trim tail
            if (bool(std::isspace(currentInstruction->at(currentInstruction->length() - 1))))
            {
                std::reverse_iterator<std::_String_iterator<std::_String_val<std::_Simple_types<char>>>> textEnd = 
                    std::find_if(currentInstruction->rbegin(), currentInstruction->rend(),[](char s) 
                    {
                        return !bool(std::isspace(s));
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
            if (bool(std::isdigit(currentInstruction->at(1))))
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
            if (currentInstruction->find('=') != std::string::npos ||
                currentInstruction->find(';') != std::string::npos)
            {
                currentInstructionType = Parser::C_instruction;
            }
            else
            {
                throw std::runtime_error(std::format("the instruction type of \"{}\" was not recognized.", currentInstruction));
            }
            
        }
    }

    Parser::instruction Parser::instructionType() const
    {
        return currentInstructionType;
    }
    
    std::unique_ptr<std::string> Parser::symbol() const noexcept(false)
    {
        if (currentInstructionType == Parser::A_instruction || currentInstructionType == Parser::L_instruction)
        {
            throw std::runtime_error(
                std::format("the instruction type of \"{}\" doesn't have symbols.", currentInstruction));
        }
        else
        {
            return std::make_unique<std::string>(
                currentInstruction->substr(std::size_t(1), std::size_t(currentInstruction->length() - 1)));
        }
    }
    
    std::unique_ptr<std::string> Parser::dest() const noexcept(false)
    {
        if (Parser::currentInstructionType != Parser::C_instruction)
        {    
            throw std::runtime_error(
                std::format("the instruction type of \"{}\" doesn't have a destination.", currentInstruction));
        } 
        else
        {

        }
    }

    std::unique_ptr<std::string> Parser::comp() const noexcept(false)
    {
        if (Parser::currentInstructionType != Parser::C_instruction)
        {
            throw std::runtime_error(
                std::format("the instruction type of \"{}\" doesn't have a computation.", currentInstruction));
        }
        else
        {
            
        }
    }
    
    std::unique_ptr<std::string> Parser::jump() const noexcept(false)
    {
        if (Parser::currentInstructionType == Parser::C_instruction)
        {
            throw std::runtime_error(
                std::format("the instruction type of \"{}\" doesn't have a jump instruction.", currentInstruction));
        }
        else
        {
            
        }
    }
}
