#pragma once
#include <cstdint>
#include <fstream>
#include <string>

namespace HackAssembler
{
    class Parser
    {
    public:
        /**
         * \brief Types of instructions:
         * \c A_INSTRUCTION for @xxx, where xxx is either a decimal number or a symbol.
         * \c C_INSTRUCTION for dest=comp:jump.
         * \c L_INSTRUCTION for (xxx), where xxx is a symbol.
         */
        enum class instructionTypes : std::uint8_t
        {
            A_INSTRUCTION,
            C_INSTRUCTION,
            L_INSTRUCTION
        };

        /**
         * \brief Open the input stream and gets ready to parse it.
         */
        explicit Parser(std::ifstream* stream);
        ~Parser();

        /**
         * \brief Are there more lines in the input.
         */
        const bool hasMoreLines();

        /**
         * \brief Reads the next instruction from the input and makes it the current input.
         * \remark Skips over white space and comments if necessary.
         * \warning This function should be called only if \c hasMoreLines is true.
         * \note Initially there is no current instruction.
         */
        void advance();

        /**
         * \brief Returns the type of the current instruction.
         */
        const instructionTypes instructionType();

        /**
         * \brief If the current instruction is (xxx), return the symbol xxx, if the current instruction is @xxx return
         * the decimal or symbol xxx.
         * \warning Should only be called if \c instructionType is \c A_INSTRUCTION or
         * \c L_INSTRUCTION .
         */
        const std::string symbol();

        /**
         * \brief Return the symbolic dest part of the current C-instruction
         * \warning Should only be called if \c instructionType is \c C_INSTRUCTION .
         */
        const std::string dest();

        /**
         * \brief Return the symbolic comp part of the current C-instruction
         * \warning Should only be called if \c instructionType is \c C_INSTRUCTION .
         */
        const std::string comp();

        /**
         * \brief Return the symbolic jump part of the current C-instruction
         * \warning Should only be called if \c instructionType is \c C_INSTRUCTION .
         */
        const std::string jump();

        template<typename T, typename P>
        T remove_if(T beg, T end, P pred)
        {
            T dest = beg;
            for (T itr = beg;itr != end; ++itr)
            {
                if (!pred(*itr))
                {
                    *(dest++) = *itr;
                }
            }
            return dest;
        }


    private:
        std::ifstream* input;
        std::string current_instruction;
    };
} // namespace HackAssembler
