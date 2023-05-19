#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

#include "Parser.h"
#include "CodeWriter.h"

namespace VMTranslator 
{
	std::vector<std::filesystem::path> vm_files;
	std::filesystem::path out_path;
}