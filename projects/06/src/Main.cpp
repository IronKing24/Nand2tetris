#include "Main.h"

HackAssembler::SymbolTable symbol_table;
HackAssembler::CodeModule code_module;
uint16_t available_memory = 16;

auto main(int argc, char *argv[]) -> int
{
    if (argc != 2)
    {
	std::cout << "Nand2Tetris' Hack Assembler\n"
		  << '\n'
		  << "Author: IronKing24\n"
		  << "Version: 1.0.0\n"
		  << '\n'
		  << "Please, insert Nand2Tetris .asm file path as an argument to get Nand2Tetris .hack file."
		  << '\n';
	return 0;
    }

    const std::filesystem::path &in_path = argv[1];

    if (!std::filesystem::exists(in_path))
    {
	std::cerr << "Can not locate Nand2Tetris .asm file at: "
		  << in_path.generic_string() << '\n';
	return 1;
    }

    if (!std::filesystem::is_regular_file(in_path))
    {
	std::cerr << "The supplied path is a directory and not an .asm file: "
		  << in_path.generic_string() << '\n';
	return 1;
    }

    if (in_path.extension() != ".asm")
    {
	std::cerr << "The supplied file is not a valid Nand2Tetris .asm but it is: " + in_path.extension().generic_string() + '\n';
	return 1;
    }

    // open asm file
    std::ifstream input_stream(in_path);
    input_stream.exceptions(std::ios_base::badbit);

    if (!input_stream)
    {
	std::cerr << "Was not able to open the file: " + in_path.generic_string() + '\n';
	return 1;
    }

    // create hack file
    std::filesystem::path out_path =
	in_path.parent_path() / in_path.stem().concat(".hack");
    std::ofstream output_stream(out_path, std::ios_base::trunc);
    output_stream.exceptions(std::ios_base::badbit | std::ios_base::failbit);

    if (!output_stream)
    {
	std::cerr << "Could not create.hack file: " << out_path.generic_string()
		  << '\n';
	return 1;
    }

    HackAssembler::Parser parser = HackAssembler::Parser(&input_stream);

    try
    {
	firstPass(parser);
	input_stream.clear();
	input_stream.seekg(std::ios_base::beg);

	secondPass(parser, output_stream);
	input_stream.close();
	output_stream.flush();
	output_stream.close();
	return 0;
    }
    catch (std::exception e)
    {
	std::cerr << e.what() << '\n';

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

void HackAssembler::firstPass(HackAssembler::Parser &parser)
{
    uint16_t line_number = 0;
    while (parser.hasMoreLines())
    {
	parser.advance();
	switch (parser.instructionType())
	{
	case HackAssembler::Parser::instructionTypes::L_INSTRUCTION:
	{
	    std::string label = parser.symbol();
	    if (label.empty())
	    {
		throw std::runtime_error("An empty Lable at line: " + std::to_string(line_number));
	    }

	    if (!symbol_table.contains(label))
	    {
		symbol_table.addEntry(label, line_number);
	    }
	    break;
	}
	case HackAssembler::Parser::instructionTypes::A_INSTRUCTION:
	case HackAssembler::Parser::instructionTypes::C_INSTRUCTION:
	{
	    line_number++;
	}
	}
    }
}

void HackAssembler::secondPass(HackAssembler::Parser &parser,
			       std::ofstream &output)
{
    while (parser.hasMoreLines())
    {
	parser.advance();
	switch (parser.instructionType())
	{
	case HackAssembler::Parser::instructionTypes::A_INSTRUCTION:
	{
	    std::string address = parser.symbol();
	    if (address.empty())
	    {
		throw std::runtime_error("An empty Address line");
	    }

	    if (std::all_of(address.cbegin(), address.cend(),
			    [](unsigned char charcter)
			    { return std::isdigit(charcter); }))
	    {
		output
		    << std::bitset<data_width>(std::stoi(address)).to_string()
		    << '\n';
	    }
	    else if (!symbol_table.contains(address))
	    {
		symbol_table.addEntry(address, available_memory);
		output << std::bitset<data_width>(available_memory)
		       << '\n';
		available_memory++;
	    }
	    else
	    {
		output << std::bitset<data_width>(
			      symbol_table.getAddress(parser.symbol()))
		       << '\n';
	    }
	    break;
	}
	case HackAssembler::Parser::instructionTypes::C_INSTRUCTION:
	{
	    output << "111" << code_module.comp(parser.comp())
		   << code_module.dest(parser.dest())
		   << code_module.jump(parser.jump()) << '\n';
	    break;
	}
	case HackAssembler::Parser::instructionTypes::L_INSTRUCTION:
	{
	    continue;
	}
	}
    }
}