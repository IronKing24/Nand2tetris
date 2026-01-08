#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <cstdio>
#include <string>

#include <tinyxml2.h>

#include "JackTokenizer.h"
#include "CompilationEngine.h"


namespace JackAnalyzer 
{
	std::vector<std::filesystem::path> jack_files;
	std::vector<std::filesystem::path> token_files;
}