#include "JackTokenizer.h"

namespace JackAnalyzer
{
	JackTokenizer::JackTokenizer(std::ifstream* input_file)
	{
		if(input_file->good())
		{
			input = input_file;
		}
		else 
		{
			throw std::runtime_error("Cann't open input file.");
		}
	}

	bool JackTokenizer::hasMoreLines() noexcept
	{
		while (input->good())
		{
			char c = input->get();

			if (std::isspace(c)) 
			{
				continue;
			}
			else if (c == '/')
			{
				c = input->get();
				if (c == '/')
				{
					std::getline(input);
				}
			}
		}
	}
	
	void JackTokenizer::advance()
	{
	
	}
	
	const JackTokenizer::TokenTypes JackTokenizer::tokenType()
	{
	
	}
	
	const char JackTokenizer::symbol()
	{
	
	}
	const std::string JackTokenizer::identifier()
	{
	
	}
	
	const int JackTokenizer::intVal()
	{
	
	}
	
	const std::string JackTokenizer::stringVal()
	{
	
	}

	JackTokenizer::~JackTokenizer()
	{

	}
}