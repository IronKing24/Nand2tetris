package io.github.ironking24.nand2tetris.HackAssembler;

import java.io.BufferedReader;
import java.io.IOException;

/**
 * the Parser is designed to read .asm files and understand them, 
 * it skips comments and white spaces.
 * @author Ironking24
 * @version 1.0.0  
 */
public class Parser {

    /**
     * the three instruction types of the Hack machine.
     * A -> @symbols
     * L -> (Label)
     * C -> dest=comp (OR) comp;jump 
     */
    public enum instructionTypes {A_instruction,C_instruction,L_instruction};
    
    private final BufferedReader reader;
    private String currentInstruction;

    /**
     * The constructor, opens the stream and gets ready to parse it.
    */
    Parser(BufferedReader input){
        this.reader = input;
    }

    /**
     * Checks if the reader file has any more instructions.
     * @return True if there is any more lines to read, false otherwise.
     * @throws IOException
    */
    public boolean hasMoreLines() throws IOException{
        reader.mark(5);
        if(reader.read()!=-1){
            reader.reset();
            return true;
        }
        else{
            return false;
        }
    }

    /**
     * skips the white lines and comments, reads the next instruction and makes it current instruction.
     * only if hasMoreLines returns true.
     * @throws IOException  If access to the file failed.
     * @throws IllegalArgumentException If the instruction is unrecognized.
    */
    public void Advance() throws IOException, IllegalArgumentException{
        String nextInstruction;

        while(hasMoreLines()){
            nextInstruction = reader.readLine().strip();
            //handles white space.
            if(nextInstruction.isBlank()){
                continue;
            }
            if(nextInstruction.contains("//")){
                //handel trailing comments.
                if(nextInstruction.startsWith("//")){
                    continue;
                }
                else{
                    nextInstruction = nextInstruction.substring(0, nextInstruction.indexOf("//")).strip();
                }
            }
            currentInstruction = nextInstruction.strip();
            break;
        }
    }

    /**
     * Returns the type of the current instruction.
     * @return and enum type.
    */
    public instructionTypes instructionType(){
        if(currentInstruction.startsWith("@")){
            return instructionTypes.A_instruction;
        }
        else if(currentInstruction.startsWith("(") && currentInstruction.endsWith(")")){
            return instructionTypes.L_instruction;
        }
        else if(currentInstruction.matches("(^\\D*=)?(.*)(;J.*)?$")){
            return instructionTypes.C_instruction;
        }
        else
        {
            throw new IllegalArgumentException("Unrecognized instruction.");
        }
    }

    /**
     * Returns the symbols of the A instruction wether a symbol or a decimal number
     * @return the value of the A-instruction
    */
    public String symbol(){
        if(currentInstruction.startsWith("@"))
        {
            return currentInstruction.substring(1, currentInstruction.length());
        }
        else if(currentInstruction.startsWith("(") && currentInstruction.endsWith(")"))
        {
            return currentInstruction.substring(1, currentInstruction.length()-1);
        }
        else
        {
            throw new IllegalStateException(String.format("the current instruction (%s) doesn't have sympols",currentInstruction));
        }
    }

    /**
     * Returns the symbol dest bits of the instruction.
     * @return the string of the storage destination name.
    */
    public String dest(){
        if(currentInstruction.contains("="))
        {
            return currentInstruction.substring(0, currentInstruction.indexOf("="));
        }
        else
        {
            throw new IllegalStateException(String.format("the current instruction (%s) doesn't have destination",currentInstruction));
        }
    }

    /**
     * Returns the commutation operating specified in the assembly.
     * @return The string representation of the computation operation
    */
    public String comp(){     
        if(currentInstruction.contains("="))
        {                    
            return currentInstruction.substring(currentInstruction.indexOf("=") + 1, currentInstruction.length());                
        }                
        else if(currentInstruction.contains(";"))
        {                 
            return currentInstruction.substring(0, currentInstruction.indexOf(";"));               
        }                        
        else
        {                   
            throw new IllegalStateException(String.format("the current instruction (%s) doesn't have a proper computation",currentInstruction));
        }
    }

    /**
     * Returns the symbol jump bits of the instruction.
     * @return the string of the Jump destination name.
    */
    public String jump(){
        if(currentInstruction.contains(";"))
        {
            return currentInstruction.substring(currentInstruction.indexOf(";") + 1, currentInstruction.length());
        }
        else
        {
            throw new IllegalStateException(String.format("the current instruction (%s) doesn't have jump",currentInstruction));
        }
    }
}
