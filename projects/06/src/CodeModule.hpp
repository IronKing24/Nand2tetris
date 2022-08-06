#pragma once
#include <string>
#include <memory>
#include <unordered_map>

namespace HackAssembler
{
    class CodeModule
    {
        private:
            //maps used to translate symbols
            std::unordered_map<std::string, std::string>* destValue;
            std::unordered_map<std::string, std::string>* compValue;
            std::unordered_map<std::string, std::string>* jumpValue;

        public:
           CodeModule();
           std::unique_ptr<std::string> dest(std::string* label);
           std::unique_ptr<std::string> comp(std::string* label);
           std::unique_ptr<std::string> jmp(std::string *label);
           ~CodeModule();
    };
}