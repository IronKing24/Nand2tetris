#include "CodeWriter.h"
#include <climits>
#include <string>

namespace VMTranslator 
{
	CodeWriter::CodeWriter(const std::filesystem::path& output_path):output(output_path, std::ios_base::trunc)
	{
		output.exceptions(std::ios_base::badbit | std::ios_base::failbit);

		if (!output.is_open() || !output.good()) 
		{
			throw std::runtime_error("CodeWriter failed to file stream.");
		}

#ifndef WOBS //without bootstrap
		//the define is for testing
		output
			<< "@256\n"
			<< "D=A\n" 
			<< "@SP\n" 
			<< "M=D\n";
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
				<< "@SP\n"
				<< "AM=M-1\n"
				<< "D=M\n"
				<< "@SP\n"
				<< "AM=M-1\n"
				<< "D=M-D\n"
				<< "M=-1\n"
				<< "@" + checkName + '\n'
				<< "D;" + symbol_table.at(command) + '\n'
				<< "@SP\n"
				<< "A=M\n"
				<< "M=0\n"
				<< "(" + checkName + ")\n"
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
				if (index < 0 || index > SHRT_MAX) {
					throw std::runtime_error("Illegal constant value: " + std::to_string(index));
				}

				output
					<< '@' + index + '\n'
					<< "D=A\n";
			}
			else if (segment == "local" || segment == "argument" || segment == "this" || segment == "that")
			{
				if (index < 0 || index > SHRT_MAX) {
					throw std::runtime_error("push " + segment + " index is out of bounds : " + std::to_string(index));
				}
				output << "@" + symbol_table.at(segment) + '\n';
				if (index > 0)
				{
					output
						<< "D=M\n"
						<< "@" + std::to_string(index) + '\n'
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
					<< "@R" + std::to_string(index + 3) + '\n'
					<< "D=M\n";

			}
			else if (segment == "temp")
			{
				if (index < 0 || index > 7)
				{
					throw std::runtime_error("Illegal push to the temp segment, index is out of bounds: " + std::to_string(index));
				}

				output
					<< "@R" << std::to_string(index + 5) + '\n'
					<< "D=M\n";
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
					<< "@" + current_file_name + "." + std::to_string(index) + '\n'
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
				if (index < 0 || index > SHRT_MAX) {
					throw std::runtime_error("pop " + segment + " index is out of bounds : " + std::to_string(index));
				}

				output
					<< "@" + symbol_table.at(segment) + '\n'
					<< "D=M\n";

				if (index > 0) 
				{
					output
						<< "@" + std::to_string(index) + '\n'
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
					<< "@R" + std::to_string(index + 3) + '\n'
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
					<< "@R" + std::to_string(index + 5) + '\n'
					<< "M=D\n";
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
					<< "@SP\n"
					<< "AM=M-1\n"
					<< "D=M\n"
					<< '@' + current_file_name + '.' + std::to_string(index) + '\n'
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

	void CodeWriter::writeLabel(const std::string& label)
	{
		output
			<< '(' + current_function_name + '$' + label + ')' + '\n';
	}

	void CodeWriter::writeGoto(const std::string& label)
	{
		output 
			<< '@' + current_function_name + '$' + label + '\n'
			<< "0;JMP\n";
	}

	void CodeWriter::writeIf(const std::string& label)
	{
		output
			<< "@SP\n"
			<< "AM=M-1\n"
			<< "D=M\n"
			<< '@' + current_function_name + '$' + label + '\n'
			<< "D;JNE\n";
	}

	void CodeWriter::writeFunction(const std::string& functionName, const int nVars)
	{
		current_function_name = functionName;
		output
			<< '(' + functionName + ')' + '\n';
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
			<< '@' + returnAddress + '\n'
			<< "D=A\n"
			<< "@SP\n"
			<< "A=M\n"
			<< "M=D\n"
			<< "@SP\n"
			<< "M=M+1\n";

		for (int i = 1; i < 5; i++) {
			output
				<< "@R" + std::to_string(i) + '\n'
				<< "D=M\n"
				<< "@SP\n"
				<< "A=M\n"
				<< "M=D\n"
				<< "@SP\n"
				<< "M=M+1\n";
		}
		output
			//lcl = sp
			<< "@SP\n"
			<< "D=M\n"
			<< "@LCL\n"
			<< "M=D\n"
			//arg = sp-5-nArgs
			<< '@' + std::to_string(nVars + 5) + '\n'
			<< "D=D-A\n"
			<< "@ARG\n"
			<< "M=D\n"
			<< '@' + functionName + '\n'
			<< "0;JMP\n"
			<< '(' + returnAddress + ')' + '\n';
	}

	void CodeWriter::writeReturn()
	{
		//set temp vars
		output
			//frame (R14) = LCL
			<< "@LCL\n"
			<< "D=M\n"
			<< "@R14\n"
			<< "M=D\n" 
			//return address = *(frame - 5)
			<< "@5\n"
			<< "A=D-A\n"
			<< "D=M\n"
			<< "@R15\n"
			<< "M=D\n";
		writePushPop(Parser::CommandTypes::C_POP, "argument", 0);
		output
			//SP = ARG + 1
			<< "@ARG\n"
			<< "D=M+1\n"
			<< "@SP\n"
			<< "M=D\n";
		//Ri=*(frame-i)
		for (int i = 4; i > 0; i--) {
			output
				<< "@R14\n"
				<< "AM=M-1\n"
				<< "D=M\n"
				<< "@R" + std::to_string(i) + '\n'
				<< "M=D\n";
		}
		output
			//go to return address
			<< "@R15\n"
			<< "A=M\n"
			<< "0;JMP\n";
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
