#include "Parser.h"

namespace HackAssembler
{
    Parser::Parser(std::ifstream* stream) : input(stream)
    {
        if (!Parser::input->is_open() || !input->good())
        {
            throw std::runtime_error("Parser failed to file stream.");
        }
    }

    const bool Parser::hasMoreLines()
    {
        while (*input)
        {
            std::string token;
            std::streampos bookmark = input->tellg();
            std::getline(*input, token);

            if (input->eof())
            {
                return false;
            }

            // skip empty
            if (token.empty())
            {
                continue;
            }

            // skip blank
            std::size_t start_pos = token.find_first_not_of(' ');
            if (start_pos == std::string::npos)
            {
                continue;
            }

            // skip comment
            std::size_t comment_pos = token.find_first_of("//");
            if (start_pos == comment_pos)
            {
                continue;
            }

            input->seekg(bookmark);
            return true;
        }

        return false;
    }

    void Parser::advance()
    {
        std::string token;

        std::getline(*input, token);

        // postion trailing comments for removal
        std::size_t end_offset        = token.find_first_of("//");
        std::string::iterator end_ite = (end_offset == std::string::npos) ? token.end() : token.begin() + end_offset;

        // strip any white spaces
        std::string::iterator dest = token.begin();
        for (std::string::iterator itr = token.begin();itr != end_ite; ++itr) 
        {
            if (std::isspace(*itr) == 0) 
            {
                *(dest++) = *itr;
            }
        }
        token.erase(dest, token.cend());
        current_instruction = token;
    }

    const Parser::instructionTypes Parser::instructionType()
    {
        if (current_instruction.front() == '@')
        {
            return HackAssembler::Parser::instructionTypes::A_INSTRUCTION;
        }
        else if (current_instruction.front() == '(' && current_instruction.back() == ')')
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
            return current_instruction.substr(1);
        }
        else if (instructionType() == HackAssembler::Parser::instructionTypes::L_INSTRUCTION)
        {
            return current_instruction.substr(1, current_instruction.length() - 2);
        }
        else
        {
            throw std::runtime_error("The current instruction is not a lable or an address:\n" + current_instruction);
        }
    }

    const std::string Parser::dest()
    {
        if (instructionType() != HackAssembler::Parser::instructionTypes::C_INSTRUCTION)
        {
            throw std::runtime_error("The current instruction is computaion:\n" + current_instruction);
        }

        std::size_t pos = current_instruction.find('=');

        if (pos == std::string::npos)
        {
            return "null";
        }
        else
        {
            return current_instruction.substr(0, pos);
        }
    }

    const std::string Parser::comp()
    {
        if (instructionType() != HackAssembler::Parser::instructionTypes::C_INSTRUCTION)
        {
            throw std::runtime_error("The current instruction is computaion:\n" + current_instruction);
        }

        std::size_t dpos = current_instruction.find('=');
        std::size_t jpos = current_instruction.find(';');

        if (dpos != std::string::npos && jpos == std::string::npos)
        {
            return current_instruction.substr(dpos + 1);
        }
        else if (dpos == std::string::npos && jpos != std::string::npos)
        {
            return current_instruction.substr(0, jpos);
        }
        else if (dpos != std::string::npos && jpos != std::string::npos)
        {
            return current_instruction.substr(dpos + 1, jpos - dpos - 1);
        }
        else
        {
            return current_instruction;
        }
    }

    const std::string Parser::jump()
    {
        if (instructionType() != HackAssembler::Parser::instructionTypes::C_INSTRUCTION)
        {
            throw std::runtime_error("The current instruction is computaion:\n" + current_instruction);
        }

        std::size_t pos = current_instruction.find(';');

        if (pos == std::string::npos)
        {
            return "null";
        }
        else
        {
            return current_instruction.substr(pos + 1);
        }
    }

   
    Parser::~Parser()
    {
        if (input->is_open())
        {
            input->close();
        }
    }

} // namespace HackAssembler