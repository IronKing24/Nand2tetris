#pragma once
#include "gtest/gtest.h"
#include "..\..\src\Parser.h"

TEST(ParserTest, Test_vm)
{
	std::ifstream reader("./test.vm");

	if (reader.fail() || !reader.is_open())
	{
		FAIL();
	}

	VMTranslator::Parser parser(&reader);

	//Arathmatic tests

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "add");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "sub");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "neg");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "eq");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "gt");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "lt");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "and");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "or");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_ARITHMETIC);
	ASSERT_EQ(parser.arg1(), "not");
	ASSERT_THROW(parser.arg2(), std::runtime_error);

	//push mem accsess

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_PUSH);
	ASSERT_EQ(parser.arg1(), "arguments");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_PUSH);
	ASSERT_EQ(parser.arg1(), "local");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_PUSH);
	ASSERT_EQ(parser.arg1(), "static");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_PUSH);
	ASSERT_EQ(parser.arg1(), "constant");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_PUSH);
	ASSERT_EQ(parser.arg1(), "this");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_PUSH);
	ASSERT_EQ(parser.arg1(), "that");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_PUSH);
	ASSERT_EQ(parser.arg1(), "pointer");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_PUSH);
	ASSERT_EQ(parser.arg1(), "temp");
	ASSERT_EQ(parser.arg2(), 1);

	//pop mem accsess

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_POP);
	ASSERT_EQ(parser.arg1(), "arguments");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_POP);
	ASSERT_EQ(parser.arg1(), "local");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_POP);
	ASSERT_EQ(parser.arg1(), "static");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_POP);
	ASSERT_EQ(parser.arg1(), "constant");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_POP);
	ASSERT_EQ(parser.arg1(), "this");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_POP);
	ASSERT_EQ(parser.arg1(), "that");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_POP);
	ASSERT_EQ(parser.arg1(), "pointer");
	ASSERT_EQ(parser.arg2(), 1);

	ASSERT_TRUE(parser.hasMoreLines());
	ASSERT_NO_THROW(parser.advance());
	ASSERT_EQ(parser.commandType(), VMTranslator::Parser::CommandTypes::C_POP);
	ASSERT_EQ(parser.arg1(), "temp");
	ASSERT_EQ(parser.arg2(), 1);
}