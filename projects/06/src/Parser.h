#pragma once
#include <fstream>
#include <string>
#include <exception>
#include <stdexcept>

namespace HackAssembler 
{
	class Parser
	{
	public:
		enum class instructionTypes {A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION};

		///<summary>Opens the input stream and gets ready to parse it.</summary>
		///<param name='stream'> stream pointer to the input stream.</param>
		Parser(std::ifstream* stream);

		///<summary>Are there more lines in the input?</summary>
		///<returns>True if EOF is not encountered, False otherwise.</returns>
		const bool hasMoreLines();

		///<summary>
		///<para>Reads the next instruction form the input, and makes it the current instruction.</para>
		///<para>Skips over white space and comments, if necessary.</para>
		///</summary>
		///<remarks>This routine should be called only if HasMoreLines is true.</remarks>
		const void advance();

		///<summary>Returns the type of the current instruction.</summary>
		///<returns>
		///<para>A_INSTRUCTION For @xxx where xxx is either a decimal number of a symbol.</para>
		///<para>C_INSTRUCTION For dest=comp;jump .</para>
		///<para>L_INSTRUCTION for (xxx) where xxx is a symbol.</para>
		///</returns>
		const instructionTypes instructionType();


		///<summary>If the current instruction is @xxx or (xxx).</summary>
		///<returns>The symbol or decimal xxx</returns>
		///<remarks>This routine should be called only if instructionType is A_INSTRUCTION or L_INSTRUCTION.</remarks>
		const std::string symbol();

		///<summary>Returns the symbolic dest part of the current C-instruction.</summary>
        ///<remarks>This routine should be called only if instructionType is C_INSTRUCTION.</remarks>
		const std::string dest();

		///<summary>Returns the symbolic comp part of the current C-instruction.</summary>
        ///<remarks>This routine should be called only if instructionType is C_INSTRUCTION.</remarks>
		const std::string comp();

		///<summary>Returns the symbolic jump part of the current C-instruction.</summary>
        ///<remarks>This routine should be called only if instructionType is A_INSTRUCTION or L_INSTRUCTION.</remarks>
		const std::string jump();
	
	private:
		std::ifstream* input;
		std::string currentInstruction;
	};
}