#pragma once
#include "Main.h"

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		std::cout <<
			"Nand2Tetris' Hack Assembler\n"
			"\n"
			"Author: IronKing24\n"
			"Version: 1.0.0\n"
			"\n"
			"Please, insert Nand2Tetris .asm file path as an argument to get Nand2Tetris .hack file.\n";
		return 0;
	}

	const std::filesystem::path& in_path = argv[1];

	if (!std::filesystem::exists(in_path))
	{
        std::cerr << "Can not locate Nand2Tetris .asm file at: " + in_path.generic_string() << std::endl;
		return 1;
	}
	
	if (!std::filesystem::is_regular_file(in_path))
	{
        std::cerr << "The supplied path is a directory and not an .asm file: " + in_path.generic_string() << std::endl;
		return 1;
	}

	if (in_path.extension().compare(".asm"))
	{
		std::cerr << "The supplied file is not a valid Nand2Tetris .asm but it is: " + in_path.extension().generic_string() << std::endl;
		return 1;
	}

	//open asm file
	std::ifstream input_stream(in_path);
    input_stream.exceptions(std::ios_base::badbit);
	if (!input_stream)
	{
		std::cerr << "Was not able to open the file: " + in_path.generic_string() << std::endl;
		return 1;
	}
	
	//create hack file
	std::filesystem::path out_path = in_path.parent_path() / in_path.stem().concat(".hack");
	std::ofstream output_stream(out_path, std::ios_base::trunc);
    output_stream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	if (!output_stream) 
	{
		std::cerr << "Could not create.hack file: " + out_path.generic_string() << std::endl;
		return 1;
	}

	HackAssembler::Parser parser = HackAssembler::Parser(&input_stream);
	
	try {
		FirstPass(parser);
		input_stream.clear();
        input_stream.seekg(std::ios_base::beg);
		SecondPass(parser, output_stream);
		input_stream.close();
		output_stream.flush();
		output_stream.close();
		
		return 0;
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
		if (input_stream.is_open())
		{
			input_stream.close();
		}
		if (output_stream.is_open())
		{
			output_stream.close();
		}
		return 1;
	}
}

void HackAssembler::FirstPass(HackAssembler::Parser& parser)
{
    unsigned short line_number = 0;
	while (parser.hasMoreLines()) 
	{
		parser.advance();

		if (parser.instructionType() == HackAssembler::Parser::instructionTypes::L_INSTRUCTION) 
		{
			std::string label = parser.symbol();
			if (label.empty() ||
	        std::find_if_not(label.begin(), label.end(),
			[](unsigned char c) { return std::isblank(c); })
	        == label.end())
			{
				throw "An empty Lable at line: " + line_number;
			}
			else if (symbol_table.contains(label))
			{
				continue;
			}
			else
			{
				symbol_table.addEntry(label, line_number);
				continue;
			}
		}
		line_number++;
	}
}

void HackAssembler::SecondPass(HackAssembler::Parser& parser, std::ofstream& output)
{
	while (parser.hasMoreLines())
	{
		parser.advance();
		switch (parser.instructionType())
		{
		case HackAssembler::Parser::instructionTypes::A_INSTRUCTION: 
		{
			std::string address = parser.symbol();
			if (address.empty() ||
			std::find_if_not(address.begin(), address.end(),
			[](unsigned char c) { return std::isblank(c); })
			== address.end())
			{
				throw std::runtime_error("An empty Address line");
			}
			else if (std::find_if_not(address.begin(), address.end(),
				[](unsigned char c) { return std::isdigit(c); })
				== address.end())
			{
				output << std::bitset<16>(std::stoi(address)).to_string() << std::endl;
			}
			else if (!symbol_table.contains(address))
			{
				symbol_table.addEntry(address, available_memory);
				output << std::bitset<16>(available_memory) << std::endl;
				available_memory++;
			}
			else
			{
				output << std::bitset<16>(symbol_table.getAddress(parser.symbol())) << std::endl;
			}
			break;
		}
		case HackAssembler::Parser::instructionTypes::C_INSTRUCTION:
		{
			std::string binary = "111";
			binary.append(code_module.comp(parser.comp()));
			binary.append(code_module.dest(parser.dest()));
			binary.append(code_module.jump(parser.jump()));
			output << binary << "\n";
			break;
		}
		}
	}
}