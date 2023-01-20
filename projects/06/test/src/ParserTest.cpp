#pragma once
#include "gtest/gtest.h"
#include "..\..\src\Parser.h"

TEST(ParserTest, Test_asm)
{
	std::ifstream reader("./test.asm");

	if(reader.fail() || !reader.is_open()) 
	{
		FAIL();
	}

	HackAssembler::Parser parser(&reader);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::A_INSTRUCTION);
	ASSERT_EQ(parser.symbol(), "Label");
	ASSERT_THROW(parser.dest(), std::runtime_error);
	ASSERT_THROW(parser.comp(), std::runtime_error);
	ASSERT_THROW(parser.jump(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::A_INSTRUCTION);
	ASSERT_EQ(parser.symbol(), "42069");
	ASSERT_THROW(parser.dest(), std::runtime_error);
	ASSERT_THROW(parser.comp(), std::runtime_error);
	ASSERT_THROW(parser.jump(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::L_INSTRUCTION);
	ASSERT_EQ(parser.symbol(), "label");
	ASSERT_THROW(parser.dest(), std::runtime_error);
	ASSERT_THROW(parser.comp(), std::runtime_error);
	ASSERT_THROW(parser.jump(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "dest");
	ASSERT_EQ(parser.comp(), "comp");
	ASSERT_EQ(parser.jump(), "jump");

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "M");
	ASSERT_EQ(parser.comp(), "1");
	ASSERT_EQ(parser.jump(), "JMP");

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "adm");
	ASSERT_EQ(parser.comp(), "comp");
	ASSERT_EQ(parser.jump(), "null");

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "null");
	ASSERT_EQ(parser.comp(), "comp");
	ASSERT_EQ(parser.jump(), "jlt");

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "adm");
	ASSERT_EQ(parser.comp(), "");
	ASSERT_EQ(parser.jump(), "jmp");

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "adm");
	ASSERT_EQ(parser.comp(), "comp");
	ASSERT_EQ(parser.jump(), "jmp");

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "null");
	ASSERT_EQ(parser.comp(), "comp");
	ASSERT_EQ(parser.jump(), "null");

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "dest");
	ASSERT_EQ(parser.comp(), "");
	ASSERT_EQ(parser.jump(), "null");

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.instructionType(), HackAssembler::Parser::instructionTypes::C_INSTRUCTION);
	ASSERT_THROW(parser.symbol(), std::runtime_error);
	ASSERT_EQ(parser.dest(), "null");
	ASSERT_EQ(parser.comp(), "");
	ASSERT_EQ(parser.jump(), "jmp");

	ASSERT_FALSE(parser.hasMoreLines());
}