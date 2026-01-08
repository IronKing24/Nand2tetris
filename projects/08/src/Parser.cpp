#include "Parser.h"
#include <filesystem>

namespace VMTranslator 
{
	Parser::Parser(const std::filesystem::path& input_path):input(input_path)
	{
		input.exceptions(std::ios_base::badbit);
		if(!input.good() || !input.is_open())
		{
			throw std::runtime_error("Was not able to open the file: " + input_path.generic_string());
		}
	}

	bool Parser::hasMoreLines() noexcept
	{
		while (input)
		{
			std::string token;
			std::streampos bookmark = input.tellg();
			std::getline(input, token);

			if (input.eof())
			{
				return false;
			}
			else if (token.empty())
			{
				//skip empty
				continue;
			}

			//skip blank
			std::size_t start_pos = token.find_first_not_of(' ');
			if (start_pos == std::string::npos)
			{
				continue;
			}

			//skip comment
			std::size_t comment_pos = token.find_first_of("//");
			if (start_pos == comment_pos)
			{
				continue;
			}

			input.seekg(bookmark);
			return true;
		}
		return false;
	}

	void Parser::advance() 
	{
		std::string token;
		std::getline(input, token);

		//Remove comments and R-trim.
		std::size_t comment_pos = token.find("//");
		if (comment_pos != std::string::npos)
		{
			std::string::iterator del_start = token.begin() + comment_pos;
			do
			{
				del_start--;
			} while (std::isspace(*del_start) && token.cbegin() < del_start);
			
			token.erase(del_start + 1, token.cend());
		}
		else if (std::isspace(token.at(token.length() - 1))) //R-trim only
		{
			std::string::iterator del_start = token.end();
			do
			{
				del_start--;
			} while (std::isspace(*del_start) && token.cbegin() < del_start);
			
			token.erase(del_start + 1, token.cend());
		}

		//L-trim
		if (std::isspace(*token.cbegin()))
		{
			std::string::iterator del_end = token.begin();

			while (std::isspace (*del_end) && del_end < token.cend())
			{
				del_end++;
			}

			token.erase(token.begin(), del_end);
		}

		//command structure check
		std::string::iterator ptr = token.begin();
		int arg_count = 0;
		for (std::string::iterator ptr = token.begin(); ptr < token.end(); ptr++)
		{
			if (std::isspace(*ptr))
			{
				if (++arg_count > 2)
				{
					throw std::runtime_error("Command \"" + current_command + "\" has illegal number of arguments.");
				}
			}
		}

		current_command = token;
	}

	const Parser::CommandTypes Parser::commandType()
	{
		std::string type = current_command.substr(0, current_command.find(' '));
		if (type == "add" || type == "sub" || type == "neg" ||	//arithmetic
			type == "eq"  || type == "gt"  || type == "lt"  ||	//comparison
			type == "and" || type == "or"  || type == "not")	//logical
		{
			return Parser::CommandTypes::C_ARITHMETIC;
		}
		else if (type == "push")
		{
			return Parser::CommandTypes::C_PUSH;
		}
		else if (type == "pop")
		{
			return Parser::CommandTypes::C_POP;
		}
		else if (type == "label")
		{
			return Parser::CommandTypes::C_LABEL;
		}
		else if (type == "goto")
		{
			return Parser::CommandTypes::C_GOTO;
		}
		else if (type == "if-goto")
		{
			return Parser::CommandTypes::C_IF;
		}
		else if (type == "function")
		{
			return Parser::CommandTypes::C_FUNCTION;
		}
		else if (type == "return")
		{
			return Parser::CommandTypes::C_RETURN;
		}
		else if (type == "call")
		{
			return Parser::CommandTypes::C_CALL;
		}
		else 
		{
			throw std::runtime_error("Comand type was not recognized: " + type);
		}
	}

	const std::string Parser::arg1()
	{
		if (commandType() == CommandTypes::C_RETURN)
		{
			throw std::runtime_error("Comand type doesn't have a first argument: " + current_command);
		}
		else if(commandType() == CommandTypes::C_ARITHMETIC)
		{
			//return the command name
			return current_command.substr(0, current_command.find(" "));
		}
		else 
		{
			//return the segment name
			std::size_t start_pos = current_command.find(" ") + 1;
			std::size_t end_pos = current_command.find(" ", start_pos);
			return current_command.substr(start_pos, end_pos - start_pos);
		}
	}

	const int Parser::arg2()
	{
		if (commandType() == CommandTypes::C_PUSH || commandType() == CommandTypes::C_POP 
			|| commandType() == CommandTypes::C_FUNCTION || commandType() == CommandTypes::C_CALL)
		{
			std::size_t start_pos = current_command.find_last_of(" ");
			return std::stoi(current_command.substr(start_pos, std::string::npos));
		}
		else
		{
			throw std::runtime_error("Comand type doesn't have a second argument: " + current_command);
		}
	}

	Parser::~Parser()
	{
		if(input.is_open()) 
		{
			input.close();
		}
	}
}
