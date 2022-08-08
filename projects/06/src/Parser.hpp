#pragma once
#include <stdlib.h>
#include <fstream>
#include <string>
#include <memory>
#include <format>

namespace HackAssembler
{
    class Parser
    {
        public:
            /**
             * @brief Types of possible instructions((A) Address or value, (C) Computation, (L) Label)
             * undefined is created to as clear-out value
             */
          enum instruction : char
          {
              Undefined,
              A_instruction,
              C_instruction,
              L_instruction
          };

        private:
            std::ifstream* asmFile = nullptr;
            std::string* currentInstruction = nullptr;
            instruction currentInstructionType = Undefined;
            
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
            void advance() noexcept(false);

            /**
             * @brief Indicates the type of the current instruction.
             * @return @param instruction 
             */
            instruction instructionType() const;

            /**
             * @brief Current instruction value.
             * @return string of a label or a number. 
             */
            std::unique_ptr<std::string> symbol() const noexcept(false);

            /**
             * @brief Current instruction destination.
             * @return Returns the destination for the computation.
             */
            std::unique_ptr<std::string> dest() const noexcept(false);

            /**
             * @brief Current computation instruction.
             * @return the computation instructions.
             */
            std::unique_ptr<std::string> comp() const noexcept(false);

            /**
             * @brief Current instruction jump value
             * @return String with the jump instruction
             */;
            std::unique_ptr<std::string> jump() const noexcept(false);
    };
}