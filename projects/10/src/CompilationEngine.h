#pragma once
#include "JackTokenizer.h"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <cstddef>
#include <cstring>
#include <stdexcept>

#include <tinyxml2.h>

namespace JackAnalyzer
{
    class CompilationEngine
    {
        public:
        explicit CompilationEngine(const std::filesystem::path& input_path, const std::filesystem::path& output_path);
        ~CompilationEngine();
        void compileClass();
        void compileClassVarDec();
        void compileSubroutine();
        void compileParameterList();
        void compileSubroutineBody();
        void compileVarDec();
        void compileStatment();
        void compileLet();
        void compileIf();
        void compileWhile();
        void compileDo();
        void compileReturn();
        void compileExpression();
        void compileTerm();
        void compileExpressionList(int num);
        private:
        FILE* output_file;
        JackAnalyzer::JackTokenizer tokenizer;
        tinyxml2::XMLDocument* output_XML;
        tinyxml2::XMLElement* current_output_element;        
    };
}