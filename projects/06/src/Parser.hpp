#pragma once
#include <stdlib.h>
#include <fstream>
#include <string>
#include <memory>

namespace HackAssembler
{
    class Parser
    {
        public:
            /**
             * @brief Types of possible instructions((A) value, (C)omputation, (L)abel)
             */
            enum instruction: char
            {
                A_instruction, C_instruction, L_instruction
            };

        private:
            std::ifstream* asmFile = nullptr;
            std::string* currentInstruction = nullptr;
            instruction currentInstructionType;
            std::array<std::string, 2>* currentInstructionTokens;
            
        public:
            /**
             * @brief Construct a new Parser object
             */
            Parser(std::ifstream* file);

            /**
             * @brief Checks is the file has more lines.
             */
            bool hasMoreLines();

            /**
             * @brief Advances the file reader to the next line if available.
             */
            void advance();

            /**
             * @brief Indicates the type of the current instruction.
             * @return @param instruction 
             */
            instruction* instructionType();

            /**
             * @brief Current instruction value.
             * @return string of a label or a number. 
             */
            std::string* symbol();

            /**
             * @brief Current instruction destination.
             * @return Retuns the destination for the computation.
             */
            std::string* dest();

            /**
             * @brief Current computation instruction.
             * @return the computation instructions.
             */
            std::string* comp();

            /**
             * @brief Current instruction jump value
             * @return String with the jump instruction
             */
            std::string* jump();
    };
}