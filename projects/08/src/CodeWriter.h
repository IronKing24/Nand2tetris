#pragma once
#include <filesystem>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Parser.h"

namespace VMTranslator 
{
	class CodeWriter
	{
	public:
		/**
		 * \brief Opens the output file and gets ready to write to it.
		 */
		explicit CodeWriter(const std::filesystem::path& output_path);
		~CodeWriter();
		
		/**
		 * \brief Informs that the translation of a new VM file has started.
		 */
		void setFileName(const std::string& name);

		/**
		 * \brief Writes to the output file the assembly code that implements the given arithmetic-logic \c command .
		 */
		void writeArithmetic(const std::string& command);

		/**
		 * \brief Writes to the output file the assembly code that implements the given push or pop \c command .
		 */
		void writePushPop(const Parser::CommandTypes command, const std::string& segment, const short int index);

		/**
		 * \brief Writes assembly code that effects the \c label command.
		 */
		void writeLabel(const std::string& label);

		/**
		 * \brief Writes assembly code that effects the \c goto command.
		 */
		void writeGoto(const std::string& label);

		/**
		 * \brief Writes assembly code that effects the \c if-goto command.
		 */
		void writeIf(const std::string& label);

		/**
		 * \brief Writes assembly code that effects the \c function command.
		 */
		void writeFunction(const std::string& functionName, const int nVars);

		/**
		 * \brief Writes assembly code that effects the \c call command.
		 */
		void writeCall(const std::string& functionName, const int nVars);

		/**
		 * \brief Writes assembly code that effects the \c return command.
		 */
		void writeReturn();

		/**
		 * \brief Closes the output file.
		 */
		void close();
#ifdef DEBUG
		void comment(const std::string& x)
		{
			output << "//" << x << std::endl;
		}
#endif //writing comments in the assembly code
	private:
		std::ofstream output;
		std::string current_file_name;
		std::string current_function_name = "";
		std::vector<std::string> statics{};
		std::unordered_map<std::string, int> running_number;
		const std::unordered_map<std::string, const std::string> symbol_table = {
			{"add", "+" },
			{"sub", "-" },
			{"neg", "-"},
			{"not", "!"},
			{"and", "&"},
			{"or", "|"},
			{"eq", "JEQ"},
			{"gt", "JGT"},
			{"lt", "JLT"},
			{"argument", "ARG"},
			{"local", "LCL"},
			{"this", "THIS"},
			{"that", "THAT"}
		};
	};
}