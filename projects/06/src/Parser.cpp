#pragma once
#include "Parser.h"

namespace HackAssembler {
    Parser::Parser(std::ifstream* stream)
    {
        Parser::input = stream;
    }

    const bool Parser::hasMoreLines()
    {
        while (input->good()) {
            std::string token;
            std::streampos bookmark = input->tellg();
            std::getline(*input, token);
            if (input->eof())
            {
                return false;
            }

            //l-trim
            if (!token.empty() && std::isspace(token.at(0))) 
            {
                token.erase(token.begin(), std::find_if(token.begin(), token.end(), 
                    [](unsigned char ch) {return !std::isspace(ch);}));
            }

            if (token.empty() || token.find("//") == 0)
            {
                continue;
            }
            else 
            {
                input->seekg(bookmark);
                return true;
            }
        }
        return false;
    }

    const void Parser::advance()
    {
        std::string token;

        std::getline(*input, token);

        //clear trailing comments
        std::size_t pos = token.find("//");
        if (pos != std::string::npos) 
        {
            token = token.substr(0, pos);
        }

        //strip any white spaces
        token.erase(std::remove_if(token.begin(), token.end(), std::isspace), token.end());

        currentInstruction = token;
    }

    const Parser::instructionTypes Parser::instructionType()
    {
        if (currentInstruction.at(0) == '@')
        {
            return HackAssembler::Parser::instructionTypes::A_INSTRUCTION;
        }
        else if (currentInstruction.at(0) == '(' && currentInstruction.at(currentInstruction.length() - 1) == ')')
        {
            return HackAssembler::Parser::instructionTypes::L_INSTRUCTION;
        }
        else
        {
            return HackAssembler::Parser::instructionTypes::C_INSTRUCTION;
        }
    }

    const std::string Parser::symbol()
    {
        if (instructionType() == HackAssembler::Parser::instructionTypes::A_INSTRUCTION)
        {
            return currentInstruction.substr(1);
        }
        else if (instructionType() == HackAssembler::Parser::instructionTypes::L_INSTRUCTION)
        {
            return currentInstruction.substr(1, currentInstruction.length() - 2);
        }
        else 
        {
            throw std::runtime_error("The current instruction is not a lable or an address:\n" + currentInstruction);
        }
    }

    const std::string Parser::dest()
    {
        if (instructionType() != HackAssembler::Parser::instructionTypes::C_INSTRUCTION) 
        {
            throw std::runtime_error("The current instruction is computaion:\n" + currentInstruction);
        }

        std::size_t pos = currentInstruction.find('=');

        if (pos == std::string::npos)
        {
            return "null";
        }
        else 
        {
            return currentInstruction.substr(0, pos);
        }
    }

    const std::string Parser::comp()
    {
        if (instructionType() != HackAssembler::Parser::instructionTypes::C_INSTRUCTION)
        {
            throw std::runtime_error("The current instruction is computaion:\n" + currentInstruction);
        }

        std::size_t dpos = currentInstruction.find('=');
        std::size_t jpos = currentInstruction.find(';');
        
        if (dpos != std::string::npos && jpos == std::string::npos)
        {
            return currentInstruction.substr(dpos + 1);
        }
        else if (dpos == std::string::npos && jpos != std::string::npos)
        {
            return currentInstruction.substr(0, jpos);
        }
        else if(dpos != std::string::npos && jpos != std::string::npos)
        {
            return currentInstruction.substr(dpos + 1, jpos - dpos - 1);
        }
        else 
        {
            return currentInstruction;
        }
    }

    const std::string Parser::jump()
    {
        if (instructionType() != HackAssembler::Parser::instructionTypes::C_INSTRUCTION)
        {
            throw std::runtime_error("The current instruction is computaion:\n" + currentInstruction);
        }

        std::size_t pos = currentInstruction.find(';');

        if (pos == std::string::npos)
        {
            return "null";
        }
        else
        {
            return currentInstruction.substr(pos + 1);
        }
    }
}

