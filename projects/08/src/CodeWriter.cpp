#include "CodeWriter.h"

namespace VMTranslator 
{
	CodeWriter::CodeWriter(std::filesystem::path output_file)
	{
		output = std::ofstream(output_file, std::ios_base::trunc);
		output.exceptions(std::ios_base::badbit | std::ios_base::failbit);

		if (!output.is_open() || !output.good()) 
		{
			throw std::runtime_error("CodeWriter failed to file stream.");
		}

#ifndef WBS //without bootstrap
		//the define is for testing
		output
			<< "@256" << std::endl
			<< "D=A" << std::endl
			<< "@SP" << std::endl
			<< "M=D" << std::endl;
		writeCall("Sys.init", 0);
#endif
	}

	void CodeWriter::setFileName(const std::string& name) 
	{
		current_file_name = name;
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

			if (running_number.find(current_file_name + "$Check") == running_number.cend())
			{
				running_number.emplace(current_file_name + "$Check", 1);
				checkName = current_file_name + "$Check0";
			}
			else 
			{
				int val = running_number[current_file_name + "$Check"]++;
				checkName = current_file_name + "$Check" + std::to_string(val);
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
				std::string label = current_file_name + "." + std::to_string(index);

				if (std::find_if(statics.cbegin(), statics.cend(),
					[&](std::string s) {return s == label; }) != statics.cend())
				{
					throw std::runtime_error("the static address does not exist for the push operation of: " + label);
				}
				output
					<< "@" << current_file_name << "." << index << std::endl
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
					throw new std::runtime_error("Illegal push to the pointer segment, index is out of bounds: " + std::to_string(index));
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
					throw std::runtime_error("Illegal push to the temp segment, index is out of bounds: " + std::to_string(index));
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
				if (std::find(statics.cbegin(), statics.cend(), current_file_name + "." + std::to_string(index))!= statics.cend())
				{
					if (statics.size() + 1 > 240) {
						throw std::runtime_error("The max number of statics has been exceeded.");
					}

					statics.push_back(current_file_name + '.' + std::to_string(index));
				}

				output
					<< "@SP" << std::endl
					<< "AM=M-1" << std::endl
					<< "D=M" << std::endl
					<< '@' << current_file_name << '.' << index << std::endl
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

	void CodeWriter::writeLabel(const std::string& label)
	{
		output
			<< '(' << current_function_name << '$' << label << ')' << std::endl;
	}

	void CodeWriter::writeGoto(const std::string& label)
	{
		output 
			<< '@' << current_function_name << '$' << label << std::endl
			<< "0;JMP" << std::endl;
	}

	void CodeWriter::writeIf(const std::string& label)
	{
		output
			<< "@SP" << std::endl
			<< "AM=M-1" << std::endl
			<< "D=M" << std::endl
			<< '@' << current_function_name << '$' << label << std::endl
			<< "D;JNE" << std::endl;
	}

	void CodeWriter::writeFunction(const std::string& functionName, const int nVars)
	{
		current_function_name = functionName;
		output
			<< '(' << functionName << ')' << std::endl;
		//initialize locals to 0
		for (int i = 0; i < nVars; i++) {
			CodeWriter::writePushPop(Parser::CommandTypes::C_PUSH, "constant", 0);
		}
	}

	void CodeWriter::writeCall(const std::string& functionName, const int nVars)
	{

		std::string returnAddress;

		if (running_number.find(functionName + "$ret") == running_number.cend())
		{
			running_number.emplace(current_file_name + "$ret", 1);
			returnAddress = current_file_name + "$ret0";
		}
		else
		{
			int val = running_number[current_file_name + "$ret"]++;
			returnAddress = current_file_name + "$ret" + std::to_string(val);
		}

			//push return address
			output
			<< '@' << returnAddress << std::endl
			<< "D=A" << std::endl
			<< "@SP" << std::endl
			<< "A=M" << std::endl
			<< "M=D" << std::endl
			<< "@SP" << std::endl
			<< "M=M+1" << std::endl;

		for (int i = 1; i < 5; i++) {
			output
				<< "@R" << i << std::endl
				<< "D=M" << std::endl
				<< "@SP" << std::endl
				<< "A=M" << std::endl
				<< "M=D" << std::endl
				<< "@SP" << std::endl
				<< "M=M+1" << std::endl;
		}
		output
			//lcl = sp
			<< "@SP" << std::endl
			<< "D=M" << std::endl
			<< "@LCL" << std::endl
			<< "M=D" << std::endl
			//arg = sp-5-nArgs
			<< '@' << nVars + 5 << std::endl
			<< "D=D-A" << std::endl
			<< "@ARG" << std::endl
			<< "M=D" << std::endl
			<< '@' << functionName << std::endl
			<< "0;JMP" << std::endl
			<< '(' << returnAddress << ')' << std::endl;
	}

	void CodeWriter::writeReturn()
	{
		//set temp vars
		output
			//frame (R14) = LCL
			<< "@LCL" << std::endl
			<< "D=M" << std::endl
			<< "@R14" << std::endl
			<< "M=D" << std::endl
			//return address = *(frame - 5)
			<< "@5" << std::endl
			<< "A=D-A" << std::endl
			<< "D=M" << std::endl
			<< "@R15" << std::endl
			<< "M=D" << std::endl;
		writePushPop(Parser::CommandTypes::C_POP, "argument", 0);
		output
			//SP = ARG + 1
			<< "@ARG" << std::endl
			<< "D=M+1" << std::endl
			<< "@SP" << std::endl
			<< "M=D" << std::endl;
		//Ri=*(frame-i)
		for (int i = 4; i > 0; i--) {
			output
				<< "@R14" << std::endl
				<< "AM=M-1" << std::endl
				<< "D=M" << std::endl
				<< "@R" << i << std::endl
				<< "M=D" << std::endl;
		}
		output
			//go to return address
			<< "@R15" << std::endl
			<< "A=M" << std::endl
			<< "0;JMP" << std::endl;
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