#pragma once
#include <filesystem>
#include <string>
#include <exception>
#include <fstream>
#include <string_view>
#include <algorithm>
#include <vector>

namespace VMTranslator
{
	class Parser
	{
	public:
		enum class CommandTypes
		{
			C_ARITHMETIC,
			C_PUSH,
			C_POP,
			C_LABEL,
			C_GOTO,
			C_IF,
			C_FUNCTION,
			C_RETURN,
			C_CALL
		};

		/**
		 * \brief Open the input file, and gets ready to parse it.
		 */
		explicit Parser(std::ifstream *input_file);
		~Parser();

		/**
		 * \brief Are there more lines in the input?
		 */
		bool hasMoreLines() noexcept;

		/**
		 * \brief Reads the next command form the input, and makes it the current command.
		 * \warning This routine should be called only if \c HasMoreLines() is true.
		 * \note Initially there is no current command.
		 */
		void advance();

		/**
		 * \brief Returns a constatnt representing the type of the current command.
		 */
		const CommandTypes commandType();

		/**
		 * \brief Returns the first segment of the current command.
		 * \warning Should not be called if the current command is \c commandType is \c C_RETURN.
		 */
		const std::string arg1();

		/**
		 * \brief Returns the second segment of the current command.
		 * \warning Should not be called if the current command is \c commandType is \c C_PUSH , \c C_POP , \c C_FUNCTION , \c C_CALL.
		 */
		const int arg2();
#ifdef DEBUG
		const std::string commend()
		{
			return current_command;
		}
#endif // returns the current command for debugging.

	private:
		std::ifstream *input;
		std::string current_command;
	};
}