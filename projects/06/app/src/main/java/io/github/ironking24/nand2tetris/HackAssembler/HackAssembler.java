package io.github.ironking24.nand2tetris.HackAssembler;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import io.github.ironking24.nand2tetris.HackAssembler.Parser.instructionTypes;

/**
 * This class is responsible for creating the hack assembler program translating Hack's assembly to Hack machine language
 * @author Ironking24
 * @version 1.0.0
*/
public class HackAssembler {
    
    private static SymbolTable symbolTable;
    private static Path asmPath;
    private static Path hackPath;
    private static int availableMemory;
    private static int lineNumber;

    static final String HELP_MASSAGE = 
    "Nand2Tetris' Hack Assembler\n"+
    "\n"+
    "Author: IronKing24\n"+
    "Version: 1.0.0\n"+
    "\n"+ 
    "insert Nand2Tetris .asm file path as an argument to get Nand2Tetris .hack file.";

    public static void main(String[] args) {
        //#region Arg possessing and initialization.
        switch(args.length){
            case 0:
                System.out.print(HELP_MASSAGE);
                break;
            case 1:
            //check .asm file validity.
                asmPath = Paths.get(args[0]);
                if(Files.notExists(asmPath)){
                    System.err.println("can not locate Nand2Tetris .asm file.");
                    System.exit(-1);
                }
                if(!Files.isRegularFile(asmPath)){
                    System.err.println("The supplied path is a directory and not an .asm file.");
                    System.exit(-1);
                }
                if(!args[0].endsWith(".asm")){
                    System.err.println("The supplied file is not a valid Nand2Tetris .asm.");
                    System.exit(-1);
                }
                if(!Files.isReadable(asmPath)){
                    System.err.println("Insufficient read privileges.");
                    System.exit(-1);
                }
            //check .hack path validity.
                hackPath = Paths.get(args[0].replace(".asm", ".hack"));
                break;   
        }
        //initialization 
        availableMemory = 16;
        lineNumber = 0;
        symbolTable = new SymbolTable();

        //#endregion
        
        //#region .hack generation.
        //first pass
        try (BufferedReader reader = new BufferedReader(new FileReader(asmPath.toFile()))) {
            firstPass(new Parser(reader));
        } catch (Exception e) {
            System.err.println(e.getMessage());
            System.exit(-1);
        }
        //second pass
        try(BufferedReader reader = new BufferedReader(new FileReader(asmPath.toFile()));
            BufferedWriter writer = new BufferedWriter(new FileWriter(hackPath.toFile())))
        {
            if(!hackPath.toFile().createNewFile() &&  !hackPath.toFile().setWritable(true)){
                throw new Exception("Could not create .hack file");
            }

            lineNumber = 0;
            secondPass(new Parser(reader), writer);
            writer.flush();
        }
        catch(Exception e){
            System.err.println(e.getMessage());
            System.exit(-1);
        }
        //#endregion
    }

    /**
     * In the first pass the compiler adds all the labels to the SymbolTable, ignoring all other instructions.
     * @param parser HackAssembler.Parser object loaded with the desired file.
     * @throws IOException
     * @throws IllegalArgumentException
     */
    private static void firstPass(Parser parser) throws IOException, IllegalArgumentException{
        while(parser.hasMoreLines()){
            parser.Advance();
            if(parser.instructionType() == instructionTypes.L_instruction && !symbolTable.contains(parser.symbol())){
                symbolTable.addEntry(parser.symbol(), lineNumber);
                continue;
            }
            lineNumber++;  
        }
    }

    /**
     * in the second pass the compiler starts translating hack's assembly to hack's binary.
     * @param parser HackAssembler.Parser object loaded with the desired file. 
     * @param writer Bufferedwriter with ready to write the output to .hack file.
     * @throws IOException
     * @throws IllegalArgumentException
     */
    private static void secondPass(Parser parser, BufferedWriter writer) throws IOException, IllegalArgumentException{
        while(parser.hasMoreLines()){
            parser.Advance();
            switch(parser.instructionType()){
                case A_instruction:
                    //try to check if it is a number
                    try {
                        writer.write(toHackBinary(Integer.parseInt(parser.symbol()))+"\n");
                    } 
                    //if it is not a number then look up the value form the table
                    catch (IOException | IllegalArgumentException e) {
                        if(!symbolTable.contains(parser.symbol())){
                            symbolTable.addEntry(parser.symbol(), availableMemory);
                            availableMemory++;
                        }
                        writer.write(toHackBinary(symbolTable.getAddress(parser.symbol()))+"\n");            
                    }
                    lineNumber++;
                    break;
                case L_instruction:
                    continue;
                case C_instruction:
                    StringBuilder binary = new StringBuilder("111");
                    binary.append(CodeModule.comp(parser.comp()));
                    binary.append(CodeModule.dest(parser.dest()));
                    binary.append(CodeModule.jump(parser.jump()));
                    writer.write(binary.toString()+"\n");
                    lineNumber++;
                    break;
                default:
                    throw new IllegalArgumentException("Corrupted code, unrecognized instruction at line: " + lineNumber);      
            }
        }
    }

    /**
     * Converts decimal to 16 bit binary string.
     * @param value decimal value
     * @return 16 bit two's complement string representation.
     * @throws IllegalArgumentException 
     */
    public static String toHackBinary(int value) throws IllegalArgumentException{
        if(value >= 0 && value <= 32767){
            String binary = Integer.toBinaryString(value);
            StringBuilder paddedBinary = new StringBuilder("0".repeat(16-binary.length()));
            paddedBinary.append(binary);
            return paddedBinary.toString();
        }
        else{
            throw new IllegalArgumentException("Value exceeded the allowed bound of (0 to 32,767)");
        }
    }
}