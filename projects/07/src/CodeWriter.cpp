#pragma once
#include "CodeWriter.h"
#include <string>

namespace VMTranslator 
{
	CodeWriter::CodeWriter(const std::filesystem::path& output_file): output(output_file, std::ios_base::trunc)
	{
		CodeWriter::output.exceptions(std::ios_base::badbit | std::ios_base::failbit);

		if (!output.is_open() || !output.good()) 
		{
			throw std::runtime_error("CodeWriter failed to file stream.");
		}
	}

	void CodeWriter::writeArithmetic(const std::string& command)
	{
		if (command == "add" || command == "sub" || command == "and" || command == "or")
		{
			output
				<< "@SP\n"
				<< "AM=M-1\n"
				<< "D=M\n" 
				<< "A=A-1\n"
				<< "M=M" << symbol_table.at(command) << "D\n";
		}
		else if (command == "neg" || command == "not")
		{
			output
				<< "@SP\n"
				<< "A=M-1\n"
				<< "M="<< symbol_table.at(command) << "M\n";
		}
		else if (command == "eq" || command == "gt" || command == "lt")
		{
			std::string checkName;

			if (running_number.find(current_fileName + "$Check") == running_number.cend())
			{
				running_number.emplace(current_fileName + "$Check", 1);
				checkName = current_fileName + "$Check0";
			}
			else 
			{
				int val = running_number[current_fileName + "$Check"]++;
				checkName = current_fileName + "$Check" + std::to_string(val);
			}

			output
				<< "@SP\n"
				<< "AM=M-1\n"
				<< "D=M\n"
				<< "@SP\n"
				<< "AM=M-1\n"
				<< "D=M-D\n"
				<< "M=-1\n"
				<< "@" << checkName << '\n'
				<< "D;" << symbol_table.at(command) << '\n'
				<< "@SP\n" 
				<< "A=M\n"
				<< "M=0\n"
				<< "("<< checkName <<")\n"
				<< "@SP\n"
				<< "AM=M+1\n";
		}
	}
	
	void CodeWriter::writePushPop(const Parser::CommandTypes command, const std::string& segment, const short int index)
	{
		switch (command)
		{
		case VMTranslator::Parser::CommandTypes::C_PUSH:
			if (segment == "constant")
			{
				if (index < 0 || index > 32767) {
					throw std::runtime_error("Illegal constant value: " + std::to_string(index));
				}

				output
					<< '@' << index << '\n'
					<< "D=A\n";
			}
			else if (segment == "local" || segment == "argument" || segment == "this" || segment == "that")
			{
				if (index < 0 || index > 32767) {
					throw std::runtime_error("push " + segment + " index is out of bounds : " + std::to_string(index));
				}
				output << "@" << symbol_table.at(segment) << '\n';
				if (index > 0)
				{
					output
						<< "D=M\n"
						<< "@" << index << '\n'
						<< "A=D+A\n";
				}
				else
				{
					output << "A=M\n";
				}
				output << "D=M\n";
			}
			else if (segment == "pointer")
			{
				if (index < 0 || index > 1)
				{
					throw std::runtime_error("Illegal push to the pointer segment, the index is out of bounds: " + std::to_string(index));
				}

				output
					<< "@R" << index + 3 << '\n'
					<< "D=M\n";

			}
			else if (segment == "temp")
			{
				if (index < 0 || index > 7)
				{
					throw std::runtime_error("Illegal push to the temp segment, index is out of bounds: " + std::to_string(index));
				}

				output
					<< "@R" << index + 5 << '\n'
					<< "D=M\n";
			}
			else if ("static")
			{
				std::string label = current_fileName + "." + std::to_string(index);

				if (std::find_if(statics.cbegin(), statics.cend(), [&](std::string s) {return s == label; }) != statics.cend())
				{
					throw std::runtime_error("the static address does not exist for the push operation of: " + label);
				}
				output
					<< "@" << current_fileName << "." << index << '\n'
					<< "D=M\n";
			}
			else
			{
				throw std::runtime_error("Illegal push segment: " + segment);
			}
			output
				<< "@SP\n"
				<< "A=M\n"
				<< "M=D\n"
				<< "@SP\n"
				<< "M=M+1\n";
			break;

		case VMTranslator::Parser::CommandTypes::C_POP:
			if (segment == "local" || segment == "argument" || segment == "this" || segment == "that")
			{
				if (index < 0 || index > 32767) {
					throw std::runtime_error("pop " + segment + " index is out of bounds : " + std::to_string(index));
				}

				output
					<< "@" << symbol_table.at(segment) << '\n'
					<< "D=M\n";

				if (index > 0) 
				{
					output
						<< "@" << index << '\n'
						<< "D=D+A\n";
				}
				output
					<< "@R13\n" 
					<< "M=D\n" 
					<< "@SP\n" 
					<< "AM=M-1\n"
					<< "D=M\n"
					<< "@R13\n"
					<< "A=M\n"
					<< "M=D\n";
				break;
			}
			else if (segment == "pointer")
			{
				if (index < 0 || index > 2)
				{
					throw new std::runtime_error("Illegal push to the pointer segment, index is out of bounds: " + std::to_string(index));
				}
				output
					<< "@SP\n"
					<< "AM=M-1\n"
					<< "D=M\n"
					<< "@R" << index + 3 << '\n'
					<< "M=D\n";
			}
			else if (segment == "temp")
			{
				if (index < 0 || index > 7)
				{
					throw std::runtime_error("Illegal push to the temp segment, index is out of bounds: " + std::to_string(index));
				}
				output
					<< "@SP\n"
					<< "AM=M-1\n"
					<< "D=M\n"
					<< "@R" << index + 5 << '\n'
					<< "M=D\n";
			}
			else if ("static")
			{
				if (std::find(statics.cbegin(), statics.cend(), current_fileName + "." + std::to_string(index))!= statics.cend())
				{
					if (statics.size() + 1 > 240) {
						throw std::runtime_error("The max number of statics has been exceeded.");
					}

					statics.push_back(current_fileName + '.' + std::to_string(index));
				}

				output
					<< "@SP\n"
					<< "AM=M-1\n"
					<< "D=M\n"
					<< '@' << current_fileName << '.' << index << '\n'
					<< "M=D\n";

			}
			else 
			{
				throw std::runtime_error("Illegal pop segment: " + segment);
			}
			break;
		default:
			throw std::runtime_error("Illegal push/pop command at segment: " + segment + " and index " + std::to_string(index));
		}
	}


	void CodeWriter::close()
	{
		output
			<< "(end)\n"
			<< "@end\n"
			<< "0;JMP\n";
		output.flush();
		output.close();
	}

	CodeWriter::~CodeWriter()
	{
		if (output.is_open()) 
		{
			output.flush();
			output.close();
		}
	}
}