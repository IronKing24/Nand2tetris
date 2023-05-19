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

	const std::filesystem::path& in_path = argv[1];

	if (!std::filesystem::exists(in_path))
	{
		std::cerr << "Can not locate a directory or Nand2Tetris .vm file at: " << in_path.generic_string() << std::endl;
		return 1;
	}

	if (std::filesystem::is_directory(in_path))
	{
		for (const std::filesystem::directory_entry& file : std::filesystem::directory_iterator(in_path))
		{
			if (file.path().extension() == ".vm")
			{
				VMTranslator::vm_files.push_back(file.path());
			}
		}

		if (VMTranslator::vm_files.empty())
		{
			std::cerr << "The directory did not contain any Nand2Tetris .vm files" << std::endl;
		}
		else 
		{
			VMTranslator::out_path = in_path / in_path.filename().concat(".asm");
		}
	}
	else if (std::filesystem::is_regular_file(in_path))
	{
		if (in_path.extension() == ".vm")
		{
			VMTranslator::vm_files.push_back(in_path);
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

	VMTranslator::CodeWriter writer(VMTranslator::out_path);

	for (const std::filesystem::path& file : VMTranslator::vm_files)
	{
		//open vm file
		std::ifstream input_stream(file);
		input_stream.exceptions(std::ios_base::badbit);

		if (!input_stream) {
			std::cerr << "Was not able to open the file: " + in_path.generic_string() << std::endl;
			return 1;
		}

		writer.setFileName(file.stem().string());

		try
		{
			VMTranslator::Parser parser(&input_stream);

			while (parser.hasMoreLines()) 
			{
				parser.advance();
#ifdef DEBUG
				writer.comment(parser.commend());
#endif //output command as comment
				switch (parser.commandType())
				{
				case VMTranslator::Parser::CommandTypes::C_ARITHMETIC:
					writer.writeArithmetic(parser.arg1());
					break;
				case VMTranslator::Parser::CommandTypes::C_PUSH: case VMTranslator::Parser::CommandTypes::C_POP :
					writer.writePushPop(parser.commandType(), parser.arg1(), parser.arg2());
					break;
				case VMTranslator::Parser::CommandTypes::C_FUNCTION:
					writer.writeFunction(parser.arg1(), parser.arg2());
					break;
				case VMTranslator::Parser::CommandTypes::C_CALL:
					writer.writeCall(parser.arg1(), parser.arg2());
					break;
				case VMTranslator::Parser::CommandTypes::C_RETURN:
					writer.writeReturn();
					break;
				case VMTranslator::Parser::CommandTypes::C_LABEL:
					writer.writeLabel(parser.arg1());
					break;
				case VMTranslator::Parser::CommandTypes::C_GOTO:
					writer.writeGoto(parser.arg1());
					break;
				case VMTranslator::Parser::CommandTypes::C_IF:
					writer.writeIf(parser.arg1());
					break;
				default:
					std::cerr << "Command was not recognized.";
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
	}

	writer.close();
	return 0;
}