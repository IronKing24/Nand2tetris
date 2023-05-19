#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string_view>


namespace JackAnalyzer
{
	class JackTokenizer
	{
	public:
		enum class TokenTypes 
		{
			KEYWORD,
			SYMBOL,
			IDENTIFIER,
			INT_CONST,
			STRING_CONST
		};

		enum class KeyWord
		{
			CLASS,
			METHOD,
			FUNCTION,
			CONSTRUCTOR,
			INT,
			BOOLEAN,
			CHAR,
			VOID,
			VAR,
			STATIC,
			FIELD,
			LET,
			DO,
			IF,
			ELSE,
			WHILE,
			RETURN,
			TRUE,
			FALSE,
			_NULL, //NULL is a cpp macro
			THIS
		};

		constexpr std::basic_string_v SYMBOLS = "{}()[].,;+-*/&|<>=~";

		/**
		* \brief Opens the .jack file/stream and gets ready to tokenize it.
		*/
		explicit JackTokenizer(std::ifstream* input_file);
		~JackTokenizer();

		/**
		* \brief Are there more lines in the input?
		*/
		bool hasMoreLines() noexcept;
		void advance();
		const TokenTypes tokenType();
		const char symbol();
		const std::string identifier();
		const int intVal();
		const std::string stringVal();
	private:
		std::ifstream* input;
		std::stringbuf input_buffer;
	};
}