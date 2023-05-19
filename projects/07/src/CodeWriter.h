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
        explicit CodeWriter(std::filesystem::path output_file);
		~CodeWriter();

        /**
         * \brief Writes to the output file the assembly code that implements the given arithmetic-logic \c command .
         */
        void writeArithmetic(const std::string& command);

        /**
         * \brief Writes to the output file the assembly code that implements the given push or pop \c command .
         */
        void writePushPop(const Parser::CommandTypes command, const std::string& segment, const short int index);

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

	public:
		std::string current_fileName;
	private:
		std::ofstream output;
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