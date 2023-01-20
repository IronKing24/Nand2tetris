#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>

namespace HackAssembler
{
	class SymbolTable
	{
	public:
		///<summary>Creates a new empty symbol table.</summary>
		SymbolTable();
		~SymbolTable();
		
		///<summary>Adds &lt;<paramref name="symbol"/>,<paramref name="address"/>&gt; to the table.</summary>
		///<param name='symbol'>The symbol that was found.</param>
		///<param name='address'>The line number/address of that symbol</param>
        void addEntry(const std::string& symbol, const unsigned short int address) noexcept;

		///<summary>Does the symbol table contain the given <paramref name="symbol"/>?</summary>
		const bool contains(const std::string& symbol) noexcept;

		///<summary>Returns the address associated with the <paramref name="symbol"/>.</summary>
		///<exception cref="std::out_of_rang">Thrown if the <paramref name="symbol"/> is not in the table.</exception>
        const unsigned short int getAddress(const std::string& symbol);

	private:
		std::unordered_map<std::string, const unsigned short int> symbolTable;
	};
}