#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace HackAssembler
{
    class SymbolTable
    {
    public:
        /**
         * \brief Creates a new empty symbol table.
         */
        explicit SymbolTable();
        ~SymbolTable();

        /**
         * \brief Adds < \c symbol , \c address > to the table.
         */
        void addEntry(const std::string& symbol, uint16_t address);

        /**
         * \brief Does the symbol table contain the given \c symbol ?
         */
        const bool contains(const std::string& symbol) noexcept;

        /**
         * \brief Returns the address associated with the \c symbol .
         */
        const uint16_t getAddress(const std::string& symbol);

    private:
        std::unordered_map<std::string, const uint16_t> symbol_table;
    };
} // namespace HackAssembler
