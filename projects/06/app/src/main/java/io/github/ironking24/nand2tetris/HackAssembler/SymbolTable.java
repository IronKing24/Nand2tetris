package io.github.ironking24.nand2tetris.HackAssembler;

import java.util.HashMap;

/**
 * Symbol reference handler, stores and resolves actual addresses of Symbols.
 * @author Ironking24
 * @version 1.0.0 
 */
public class SymbolTable {
    
    private final HashMap<String,Integer> definedLabels;

    SymbolTable(){
        definedLabels = new HashMap<>(21);
        definedLabels.put("R0", 0);
        definedLabels.put("R1", 1);
        definedLabels.put("R2", 2);
        definedLabels.put("R3", 3);
        definedLabels.put("R4", 4);
        definedLabels.put("R5", 5);
        definedLabels.put("R6", 6);
        definedLabels.put("R7", 7);
        definedLabels.put("R8", 8);
        definedLabels.put("R9", 9);
        definedLabels.put("R10", 10);
        definedLabels.put("R11", 11);
        definedLabels.put("R12", 12);
        definedLabels.put("R13", 13);
        definedLabels.put("R14", 14);
        definedLabels.put("R15", 15);
        definedLabels.put("SP", 0);
        definedLabels.put("LCL", 1);
        definedLabels.put("ARG", 2);
        definedLabels.put("THIS", 3);
        definedLabels.put("THAT", 4);
        definedLabels.put("SCREEN", 0x4000);
        definedLabels.put("KBD", 0x6000);
    }

    /**
     * Adds the symbol and it's corresponding memory address or file location to the table.
     * @param symbol  A string representation.
     * @param address  An integer that represents the address value.
    */
    public void addEntry(String symbol, int address){
        definedLabels.put(symbol, address);
    }

    /**
     * Checks if the symbol table has the given symbol.
     * @param symbol  The symbol to check for.
     * @return True if the table contains the symbol, false otherwise.
    */
    public boolean contains(String symbol){
        return definedLabels.containsKey(symbol);
    }

    /**
     * Returns the address value associated with the symbol.
     * @param symbol  The symbol to check for.
     * @return address value associated with the symbol.
     * @throws IllegalArgumentException If the symbol is unrecognized.
    */
    public int getAddress(String symbol) throws IllegalArgumentException{
        if(contains(symbol)){
            return definedLabels.get(symbol);
        }
        else{
            throw new IllegalArgumentException("The symbol table doesn't contain" + symbol);
        }
    }
}
