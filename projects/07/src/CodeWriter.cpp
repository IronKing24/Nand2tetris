#pragma once
#include "CodeWriter.h"

namespace VMTranslator 
{
	CodeWriter::CodeWriter(std::filesystem::path output_file)
	{
		CodeWriter::output = std::ofstream(output_file, std::ios_base::trunc);
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
				<< "@SP" << std::endl
				<< "AM=M-1" << std::endl
				<< "D=M" << std::endl
				<< "A=A-1" << std::endl
				<< "M=M" << symbol_table.at(command) << "D" << std::endl;
		}
		else if (command == "neg" || command == "not")
		{
			output
				<< "@SP" << std::endl
				<< "A=M-1" << std::endl
				<< "M="<< symbol_table.at(command) << "M" << std::endl;
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
				<< "@SP" << std::endl
				<< "AM=M-1" << std::endl
				<< "D=M" << std::endl
				<< "@SP" << std::endl
				<< "AM=M-1" << std::endl
				<< "D=M-D" << std::endl
				<< "M=-1" << std::endl
				<< "@" << checkName << std::endl
				<< "D;" << symbol_table.at(command) << std::endl
				<< "@SP" << std::endl
				<< "A=M" << std::endl
				<< "M=0" << std::endl
				<< "("<< checkName <<")" << std::endl
				<< "@SP" << std::endl
				<< "AM=M+1" << std::endl;
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
					<< '@' << index << std::endl
					<< "D=A" << std::endl;
			}
			else if (segment == "local" || segment == "argument" || segment == "this" || segment == "that")
			{
				if (index < 0 || index > 32767) {
					throw std::runtime_error("push " + segment + " index is out of bounds : " + std::to_string(index));
				}
				output << "@" << symbol_table.at(segment) << std::endl;
				if (index > 0)
				{
					output
						<< "D=M" << std::endl
						<< "@" << index << std::endl
						<< "A=D+A" << std::endl;
				}
				else
				{
					output << "A=M" << std::endl;
				}
				output << "D=M" << std::endl;
			}
			else if (segment == "pointer")
			{
				if (index < 0 || index > 1)
				{
					throw std::runtime_error("Illegal push to the pointer segment, the index is out of bounds: " + std::to_string(index));
				}

				output
					<< "@R" << index + 3 << std::endl
					<< "D=M" << std::endl;

			}
			else if (segment == "temp")
			{
				if (index < 0 || index > 7)
				{
					throw std::runtime_error("Illegal push to the temp segment, index is out of bounds: " + std::to_string(index));
				}

				output
					<< "@R" << index + 5 << std::endl
					<< "D=M" << std::endl;
			}
			else if ("static")
			{
				std::string label = current_fileName + "." + std::to_string(index);

				if (std::find_if(statics.cbegin(), statics.cend(),
					[&](std::string s) {return s == label; }) != statics.cend())
				{
					throw std::runtime_error("the static address does not exist for the push operation of: " + label);
				}
				output
					<< "@" << current_fileName << "." << index << std::endl
					<< "D=M" << std::endl;
			}
			else
			{
				throw std::runtime_error("Illegal push segment: " + segment);
			}
			output
				<< "@SP" << std::endl
				<< "A=M" << std::endl
				<< "M=D" << std::endl
				<< "@SP" << std::endl
				<< "M=M+1" << std::endl;
			break;

		case VMTranslator::Parser::CommandTypes::C_POP:
			if (segment == "local" || segment == "argument" || segment == "this" || segment == "that")
			{
				if (index < 0 || index > 32767) {
					throw std::runtime_error("pop " + segment + " index is out of bounds : " + std::to_string(index));
				}

				output
					<< "@" << symbol_table.at(segment) << std::endl
					<< "D=M" << std::endl;

				if (index > 0) 
				{
					output
						<< "@" << index << std::endl
						<< "D=D+A" << std::endl;
				}
				output
					<< "@R13" << std::endl 
					<< "M=D" << std::endl 
					<< "@SP" << std::endl 
					<< "AM=M-1" << std::endl
					<< "D=M" << std::endl
					<< "@R13" << std::endl
					<< "A=M" << std::endl
					<< "M=D" << std::endl;
				break;
			}
			else if (segment == "pointer")
			{
				if (index < 0 || index > 2)
				{
					throw new std::runtime_error("Illegal push to the pointer segment, index is out of bounds: " + index);
				}
				output
					<< "@SP" << std::endl
					<< "AM=M-1" << std::endl
					<< "D=M" << std::endl
					<< "@R" << index + 3 << std::endl
					<< "M=D" << std::endl;
			}
			else if (segment == "temp")
			{
				if (index < 0 || index > 7)
				{
					throw std::runtime_error("Illegal push to the temp segment, index is out of bounds: " + index);
				}
				output
					<< "@SP" << std::endl
					<< "AM=M-1" << std::endl
					<< "D=M" << std::endl
					<< "@R" << index + 5 << std::endl
					<< "M=D" << std::endl;
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
					<< "@SP" << std::endl
					<< "AM=M-1" << std::endl
					<< "D=M" << std::endl
					<< '@' << current_fileName << '.' << index << std::endl
					<< "M=D" << std::endl;

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
			<< "(end)" << std::endl
			<< "@end" << std::endl
			<< "0;JMP" << std::endl;
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