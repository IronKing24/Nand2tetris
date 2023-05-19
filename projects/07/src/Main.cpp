#include "Main.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout
			<< "Nand2Tetris' Virtual machine translator" << std::endl
			<< std::endl
			<< "Author: IronKing24" << std::endl
			<< "Version: 1.0.0" << std::endl
			<< std::endl
			<< "Please, insert Nand2Tetris .vm file path as an argument to get Nand2Tetris .asm file." << std::endl;
		return 0;
	}

	const std::filesystem::path &in_path = argv[1];

	if (!std::filesystem::exists(in_path))
	{
		std::cerr << "Can not locate a directory or Nand2Tetris .vm file at: " << in_path.generic_string() << std::endl;
		return 1;
	}
	
	if (std::filesystem::is_regular_file(in_path))
	{
		if (in_path.extension() == ".vm")
		{
			VMTranslator::out_path = in_path.parent_path() / in_path.stem().concat(".asm");
		}
		else
		{
			std::cerr << "The supplied file is not a valid Nand2Tetris .vm but it is: " << in_path.extension().generic_string() << std::endl;
			return 1;
		}
	}
	else
	{
		std::cerr << "The supplied path has a problem: " << in_path;
		return 1;
	}

    // open vm file
    std::ifstream input_stream(in_path);
    input_stream.exceptions(std::ios_base::badbit);

	if (!input_stream)
	{
		std::cerr << "Was not able to open the file: " + in_path.generic_string() << std::endl;
		return 1;
	}

    VMTranslator::CodeWriter writer(VMTranslator::out_path);
	
	try
	{
		VMTranslator::Parser parser(&input_stream);

		while (parser.hasMoreLines()) 
		{
			parser.advance();
#ifdef DEBUG
			writer.comment(parser.commend());
#endif // output command as comment
			switch (parser.commandType())
			{
			case VMTranslator::Parser::CommandTypes::C_ARITHMETIC:
				writer.writeArithmetic(parser.arg1());
				break;
			case VMTranslator::Parser::CommandTypes::C_PUSH: case VMTranslator::Parser::CommandTypes::C_POP :
				writer.writePushPop(parser.commandType(), parser.arg1(), parser.arg2());
				break;
			default:
				throw std::runtime_error("Command was not recognized.");
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		input_stream.close();
		writer.close();
		return 1;
	}

	input_stream.close();

	writer.close();
	return 0;
}