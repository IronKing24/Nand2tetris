#pragma once
#include "gtest/gtest.h"
#include "..\..\src\CodeModule.h"

TEST(CodeModuleTest, DestinationTest)
{
	HackAssembler::CodeModule code_module = HackAssembler::CodeModule();

	ASSERT_EQ(code_module.dest("null"), "000");
	ASSERT_EQ(code_module.dest("M"), "001");
	ASSERT_EQ(code_module.dest("D"), "010");
	ASSERT_EQ(code_module.dest("DM"), "011");
	ASSERT_EQ(code_module.dest("A"), "100");
	ASSERT_EQ(code_module.dest("AM"), "101");
	ASSERT_EQ(code_module.dest("AD"), "110");
	ASSERT_EQ(code_module.dest("ADM"), "111");

	ASSERT_THROW(code_module.dest("random"), std::runtime_error);
}

TEST(CodeModuleTest, ComputationTest)
{
	HackAssembler::CodeModule code_module = HackAssembler::CodeModule();

	ASSERT_EQ(code_module.comp("0"), "0101010");
	ASSERT_EQ(code_module.comp("1"), "0111111");
	ASSERT_EQ(code_module.comp("-1"), "0111010");
	ASSERT_EQ(code_module.comp("D"), "0001100");
	ASSERT_EQ(code_module.comp("A"), "0110000");
	ASSERT_EQ(code_module.comp("!D"), "0001101");
	ASSERT_EQ(code_module.comp("!A"), "0110001");
	ASSERT_EQ(code_module.comp("-D"), "0001111");
	ASSERT_EQ(code_module.comp("-A"), "0110011");
	ASSERT_EQ(code_module.comp("D+1"), "0011111");
	ASSERT_EQ(code_module.comp("A+1"), "0110111");
	ASSERT_EQ(code_module.comp("D-1"), "0001110");
	ASSERT_EQ(code_module.comp("A-1"), "0110010");
	ASSERT_EQ(code_module.comp("D+A"), "0000010");
	ASSERT_EQ(code_module.comp("D-A"), "0010011");
	ASSERT_EQ(code_module.comp("A-D"), "0000111");
	ASSERT_EQ(code_module.comp("D&A"), "0000000");
	ASSERT_EQ(code_module.comp("D|A"), "0010101");

	ASSERT_EQ(code_module.comp("M"), "1110000");
	ASSERT_EQ(code_module.comp("!M"), "1110001");
	ASSERT_EQ(code_module.comp("-M"), "1110011");
	ASSERT_EQ(code_module.comp("M+1"), "1110111");
	ASSERT_EQ(code_module.comp("M-1"), "1110010");
	ASSERT_EQ(code_module.comp("D+M"), "1000010");
	ASSERT_EQ(code_module.comp("D-M"), "1010011");
	ASSERT_EQ(code_module.comp("M-D"), "1000111");
	ASSERT_EQ(code_module.comp("D&M"), "1000000");
	ASSERT_EQ(code_module.comp("D|M"), "1010101");

	ASSERT_THROW(code_module.comp("random"), std::runtime_error);
}

TEST(CodeModuleTest, JumpTest)
{
	HackAssembler::CodeModule code_module = HackAssembler::CodeModule();

	ASSERT_EQ(code_module.jump("null"), "000");
	ASSERT_EQ(code_module.jump("JGT"), "001");
	ASSERT_EQ(code_module.jump("JEQ"), "010");
	ASSERT_EQ(code_module.jump("JGE"), "011");
	ASSERT_EQ(code_module.jump("JLT"), "100");
	ASSERT_EQ(code_module.jump("JNE"), "101");
	ASSERT_EQ(code_module.jump("JLE"), "110");
	ASSERT_EQ(code_module.jump("JMP"), "111");

	ASSERT_THROW(code_module.jump("random"), std::runtime_error);
}