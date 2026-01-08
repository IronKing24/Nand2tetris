#include "Main.h"

int main(int argc, char* argv[])
{
	if (argc < 1)
	{
		std::cout
			<< "Nand2Tetris' Jack language Analyzer\n" 
			<< '\n'
			<< "Author: IronKing24\n"
			<< "Version: 1.0.0\n"
			<< '\n'
			<< "Please, insert Nand2Tetris .jack file path as an argument to get Nand2Tetris .vm file.\n";
		return 0;
	}

	const std::filesystem::path& in_path = argv[1];

	if (!std::filesystem::exists(in_path))
	{
		std::cerr << "Can not locate a directory or Nand2Tetris .jack file at: " + in_path.generic_string() + '\n';
		return 1;
	}

	if (std::filesystem::is_directory(in_path))
	{
		for (const std::filesystem::directory_entry& file : std::filesystem::directory_iterator(in_path))
		{
			if (file.path().extension() == ".jack")
			{
				JackAnalyzer::jack_files.push_back(file.path());
			}
		}

		if (JackAnalyzer::jack_files.empty())
		{
			std::cerr << "The directory did not contain any Nand2Tetris .jack files\n";
		}
	}
	else if (std::filesystem::is_regular_file(in_path))
	{
		if (in_path.extension() == ".jack")
		{
			JackAnalyzer::jack_files.push_back(in_path);
		}
		else
		{
			std::cerr << "The supplied file is not a valid Nand2Tetris .vm but it is: " + in_path.extension().generic_string() + '\n';
			return 1;
		}
	}
	else
	{
		std::cerr << "The supplied path has a problem: " << in_path;
		return 1;
	}

	//Tokenzation
	for(const std::filesystem::path& input : JackAnalyzer::jack_files)
	{
		std::filesystem::path output_path = input.parent_path()/input.stem().concat("T").replace_extension("xml");
		FILE* output_file = fopen(output_path.c_str() , "w");

		if(output_file == nullptr)
		{
			std::cerr << "Could not create tokens output file at: " << output_path;
			return 1;
		}
		
		JackAnalyzer::JackTokenizer tokenizer(input);
		tinyxml2::XMLDocument output_xml(true, tinyxml2::PRESERVE_WHITESPACE);
		tinyxml2::XMLElement* root = output_xml.NewElement("tokens");
		output_xml.InsertFirstChild(root);

		
	}
	
	return 0;
}
