#include "JackTokenizer.h"
#include <cstdio>
#include <iostream>
#include <ostream>

namespace JackAnalyzer
{
	JackTokenizer::JackTokenizer(const std::filesystem::path& input_file): input(input_file)
	{
		if (!input.good())
		{
			throw std::runtime_error("Can't open input file.");
		}
		input.exceptions(std::ios::badbit);
	}

	bool JackTokenizer::hasMoreLines() noexcept
	{
		char input_buffer = 0;
		
		while (input.good())
		{
			input >> input_buffer;

			if (input.eof())
			{
				return false;
			}
			else if (input_buffer == '/') //single line comment
			{
				if(input.peek() == '/') // ignore single line comments
				{
					input.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 
					continue;
				}
				else if(input.peek() == '*') // ignore multi-line comments
				{
					while (input.peek() != '/')
					{
						input.ignore(std::numeric_limits<std::streamsize>::max(),'*');
					}
					input.ignore();
					continue;
				} 
			}

			input.putback(input_buffer);
			return true;
		}
		return false;
	}

	void JackTokenizer::advance()
	{
		if (!hasMoreLines())
		{
			throw std::runtime_error("No more tokens to process.");
		}

		current_token.erase();
		while (input.good() && std::isblank(input.peek()) == 0)
		{
			char input_buf = input.get();

			if (std::find(SYMBOLS.begin(), SYMBOLS.end(), input_buf) != SYMBOLS.end())
			{
				if (current_token.empty())
				{
					current_token = input_buf;
				}
				else
				{
					input.unget();
				}
				break;
			}
			else if (input_buf == '"')
			{
				if (current_token.empty())
				{
					std::string string_content;
					current_token.push_back(input_buf);
					std::getline(input, string_content, '"');

					if(input.peek() == EOF)
					{
						throw std::runtime_error("Unclosed string literal'\n'");
					}

					current_token.append(string_content);
					current_token.push_back('"');
				}
				else
				{
					input.unget();
				}
				break;
			}

			current_token.push_back(input_buf);
		}
	}

	const JackTokenizer::TokenTypes JackTokenizer::tokenType()
	{
		if (current_token.length() == 1 && std::find(SYMBOLS.begin(), SYMBOLS.end(), current_token.at(0)) != SYMBOLS.end())
		{
			return TokenTypes::SYMBOL;
		}
		else if( keyword_table.find(current_token) != keyword_table.end())
		{
			return TokenTypes::KEYWORD;
		}
		else if (current_token.front() == '"' && current_token.back() == '"')
		{
			return TokenTypes::STRING_CONST;
		}
		else if (std::all_of(current_token.begin(), current_token.end(), ::isdigit))
		{
			return TokenTypes::INT_CONST;
		}
		else if (!std::isdigit(current_token.front()))
		{
			return TokenTypes::IDENTIFIER;
		}

		throw std::runtime_error("Unrecoginzed token: " + current_token + '\n');
	}

	JackTokenizer::KeyWord JackTokenizer::keyword()
	{
		if (keyword_table.find(current_token) == keyword_table.end())
		{
		throw std::runtime_error(
			"The current token is not a keyword: " + current_token + '\n');
		}

		return keyword_table.at(current_token);
	}

	const char JackTokenizer::symbol()
	{
		if (tokenType() != TokenTypes::SYMBOL)
		{
			throw std::runtime_error("The current token is not a symbol: " + current_token + '\n');
		}

		return current_token.front();
	}

	const std::string JackTokenizer::identifier()
	{
		if (tokenType() != TokenTypes::IDENTIFIER)
		{
			throw std::runtime_error("The current token is not an identifier: " + current_token + '\n');
		}

		return current_token;
	}

	const int JackTokenizer::intVal()
	{
		if (tokenType() != TokenTypes::INT_CONST)
		{
			throw std::runtime_error("The current token is not an integer: " + current_token + '\n');
		}

		return std::stoi(current_token);
	}

	const std::string JackTokenizer::stringVal()
	{
		if (tokenType() != TokenTypes::STRING_CONST)
		{
			throw std::runtime_error("The current token is not a string: " + current_token + '\n');
		}

		return current_token.substr(1, current_token.size() - 2);
	}

	JackTokenizer::~JackTokenizer() 
	{ 
		input.close(); 
	}
} // namespace JackAnalyzer
