#pragma once
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

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

		/**
		* \brief Opens the .jack file/stream and gets ready to tokenize it.
		*/
		explicit JackTokenizer(const std::filesystem::path& input_file);
		~JackTokenizer();

		/**
		* \brief Are there more lines in the input?
		*/
		bool hasMoreLines() noexcept;
		void advance();
		JackTokenizer::KeyWord keyword();
		const TokenTypes tokenType();
		const char symbol();
		const std::string identifier();
		const int intVal();
		const std::string stringVal();
	private:
		static constexpr std::array<char, 19> SYMBOLS = {'{','}','(',')','[',']','.',',',';','+','-','*','/','&','|','<','>','=','~'};
		std::ifstream input;
		std::string current_token;
		const std::unordered_map<std::string, const JackTokenizer::KeyWord> keyword_table = {
			{"class",KeyWord::CLASS},{"method",KeyWord::METHOD},{"function",KeyWord::FUNCTION},{"constructor",KeyWord::CONSTRUCTOR},{"int",KeyWord::INT},
			{"boolean",KeyWord::BOOLEAN},{"char",KeyWord::CHAR},{"void",KeyWord::VOID},{"var",KeyWord::VAR},{"static",KeyWord::STATIC},
			{"field",KeyWord::FIELD},{"let",KeyWord::LET},{"do",KeyWord::DO},{"if",KeyWord::IF},{"else",KeyWord::ELSE},
			{"while",KeyWord::WHILE},{"return",KeyWord::RETURN},{"true",KeyWord::TRUE},{"false",KeyWord::FALSE},{"null",KeyWord::_NULL},
			{"this",KeyWord::THIS}
		};
	};
}