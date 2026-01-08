#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>
#include <tinyxml2.h>

#include "gtest/gtest.h"
#include "../../src/JackTokenizer.h"

struct TestFiles {
   const std::string dir;
   const std::string file;
};

class TokenizerTestFixture : public ::testing::TestWithParam<TestFiles> {
// You can add fixture logic here
public:
    JackAnalyzer::JackTokenizer* Tokenizer; 
    std::FILE* token_file;
    tinyxml2::XMLDocument* comp_file;
    tinyxml2::XMLElement* current_ele;

    int max_tokens_count;

    void SetUp() override 
    {
        Tokenizer = new JackAnalyzer::JackTokenizer(std::filesystem::absolute("./resources/") / GetParam().dir / std::filesystem::path(GetParam().file).replace_extension(".jack"));   

        comp_file = new tinyxml2::XMLDocument(true, tinyxml2::PRESERVE_WHITESPACE);
        token_file = fopen(std::filesystem::absolute(std::filesystem::path("./resources/") / GetParam().dir / std::filesystem::path( GetParam().file + "TComp").replace_extension(".xml")).c_str(), "r");
        comp_file->LoadFile(token_file);
        max_tokens_count = comp_file->RootElement()->ChildElementCount();
        current_ele = comp_file->RootElement()->FirstChildElement();
    }

    void TearDown() override 
    {
        delete Tokenizer;
        delete comp_file;

        if(token_file != nullptr)
        {
            fclose(token_file);
        }
    }

};

TEST_P(TokenizerTestFixture, TokenizerTest)
{
    for(int current_tokens_count = 0; current_tokens_count <= max_tokens_count; current_tokens_count++)
    {
        ASSERT_TRUE(Tokenizer->hasMoreLines());
        ASSERT_NO_THROW(Tokenizer->advance());
        //check token type
        ASSERT_NO_THROW(Tokenizer->tokenType());
        switch (Tokenizer->tokenType())
        {
	        case JackAnalyzer::JackTokenizer::TokenTypes::KEYWORD:
                ASSERT_STREQ(current_ele->Value(), "keyword");
                ASSERT_NO_THROW(Tokenizer->keyword());
                switch (Tokenizer->keyword()) 
                {
		            case JackAnalyzer::JackTokenizer::KeyWord::CLASS:
		                ASSERT_STREQ(current_ele->GetText(), "class");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::METHOD:
                        ASSERT_STREQ(current_ele->GetText(), "method");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::FUNCTION:
                        ASSERT_STREQ(current_ele->GetText(), "function");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::CONSTRUCTOR:
                        ASSERT_STREQ(current_ele->GetText(), "constructor");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::INT:
                        ASSERT_STREQ(current_ele->GetText(), "int");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::BOOLEAN:
                        ASSERT_STREQ(current_ele->GetText(), "boolean");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::CHAR:
                        ASSERT_STREQ(current_ele->GetText(), "char");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::VOID:
                        ASSERT_STREQ(current_ele->GetText(), "void");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::VAR:
                        ASSERT_STREQ(current_ele->GetText(), "var");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::STATIC:
                        ASSERT_STREQ(current_ele->GetText(), "static");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::FIELD:
                        ASSERT_STREQ(current_ele->GetText(), "field");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::LET:
                        ASSERT_STREQ(current_ele->GetText(), "let");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::DO:
                        ASSERT_STREQ(current_ele->GetText(), "do");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::IF:
                        ASSERT_STREQ(current_ele->GetText(), "if");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::ELSE:
                        ASSERT_STREQ(current_ele->GetText(), "else");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::WHILE:
                        ASSERT_STREQ(current_ele->GetText(), "while");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::RETURN:
                        ASSERT_STREQ(current_ele->GetText(), "return");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::TRUE:
                        ASSERT_STREQ(current_ele->GetText(), "true");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::FALSE:
                        ASSERT_STREQ(current_ele->GetText(), "false");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::_NULL:
                        ASSERT_STREQ(current_ele->GetText(), "null");
		                break;
		            case JackAnalyzer::JackTokenizer::KeyWord::THIS:
                        ASSERT_STREQ(current_ele->GetText(), "this");
		                break;
                }
                break;
	        case JackAnalyzer::JackTokenizer::TokenTypes::SYMBOL:
                ASSERT_STREQ(current_ele->Value(), "symbol");
                ASSERT_NO_THROW(Tokenizer->symbol());
                ASSERT_EQ(current_ele->GetText(), std::string(1, Tokenizer->symbol()));
                break;
	        case JackAnalyzer::JackTokenizer::TokenTypes::IDENTIFIER:
                ASSERT_STREQ(current_ele->Value(), "identifier");
                ASSERT_NO_THROW(Tokenizer->identifier());
                ASSERT_EQ(current_ele->GetText(), Tokenizer->identifier());
                break;
	        case JackAnalyzer::JackTokenizer::TokenTypes::INT_CONST:
                ASSERT_STREQ(current_ele->Value(), "integerConstant");
                ASSERT_NO_THROW(Tokenizer->intVal());
                ASSERT_EQ(current_ele->GetText(), std::to_string(Tokenizer->intVal()));
                break;
	        case JackAnalyzer::JackTokenizer::TokenTypes::STRING_CONST:
                ASSERT_STREQ(current_ele->Value(), "stringConstant");
                ASSERT_NO_THROW(Tokenizer->stringVal());
                ASSERT_EQ(current_ele->GetText(), Tokenizer->stringVal());
	            break;
	    }
    
        ASSERT_LE(current_tokens_count, max_tokens_count);
        current_ele = current_ele->NextSiblingElement();
        current_tokens_count++;
    }
}

INSTANTIATE_TEST_SUITE_P(
    TokenizerTest,
    TokenizerTestFixture,
    ::testing::Values(
        TestFiles{"ArrayTest", "Main"},
        TestFiles{"ExpressionLessSquare", "Main"},
        TestFiles{"ExpressionLessSquare", "Square"},
        TestFiles{"ExpressionLessSquare", "SquareGame"},
        TestFiles{"Square", "Main"},
        TestFiles{"Square", "Square"},
        TestFiles{"Square", "SquareGame"}
    ),
    [](const testing::TestParamInfo<TestFiles>& info) {
      // Can use info.param here to generate the test suffix
      std::string name = info.param.dir + "_" + info.param.file;
      return name;
    }
);