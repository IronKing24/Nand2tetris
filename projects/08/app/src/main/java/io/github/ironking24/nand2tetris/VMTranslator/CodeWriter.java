package io.github.ironking24.nand2tetris.VMTranslator;

import java.io.BufferedWriter;
import java.io.Closeable;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

import javax.naming.LimitExceededException;

import io.github.ironking24.nand2tetris.VMTranslator.Parser.commandTypes;

/**
 * this class is responsible for translating VM code into assembly instructions and then writing them into the .asm file.
*/
public class CodeWriter implements Closeable{

    private final BufferedWriter writer;
    private String currentFileName, currentFunctionName;
    private final ArrayList<String> statics = new ArrayList<>();
    private final HashMap<String, String> symbolTable = new HashMap<>(9);
    private final HashMap<String, Integer> runningNumbersTable = new HashMap<>(2);

    void xxx(String A) throws IOException{
        writer.write(A);
    }

    CodeWriter(BufferedWriter output) throws IOException{
        this.writer = output;
        this.currentFileName = this.currentFunctionName = "";
        
        //initialize vm to asm translation
        symbolTable.put("add","+");
        symbolTable.put("sub","-");
        symbolTable.put("neg","-");
        symbolTable.put("not","!");
        symbolTable.put("and","&");
        symbolTable.put("or","|");
        symbolTable.put("eq","JEQ");
        symbolTable.put("gt","JGT");
        symbolTable.put("lt","JLT");
        symbolTable.put("argument","ARG");
        symbolTable.put("local","LCL");
        symbolTable.put("this","THIS");
        symbolTable.put("that","THAT");

        //BootStrap
        writer.write(
            "@256\n"+
            "D=A\n"+
            "@SP\n"+
            "M=D\n"
            );
            WriteCall("Sys.init", 0);
    }

    /**
     * sets the file name of the current file being translated.
    */
    public void setFileName(String name){

        currentFileName = name;
    }
    
    /**
     * writes the operation execution on the stack in hack's assembly.
     * @throws IllegalArgumentException if the @param command is not recognized.
    */
    public void writeArithmetic(String command) throws Exception{
        switch(command){
            case "add": case "sub":
            case "and": case "or":
                writer.write(String.format(
                "@SP\n"+
                "AM=M-1\n"+
                "D=M\n"+
                "A=A-1\n"+
                "M=M%sD\n", 
                symbolTable.get(command)));
                break;
            case "neg": case "not":
                writer.write(String.format(
                "@SP\n"+
                "A=M-1\n"+
                "M=%sM\n", 
                symbolTable.get(command)));
                break;
            case "eq": case "gt": case"lt":
                String checkName = String.format("%s$Check%d", currentFunctionName, nextRunningNumber(String.format("%s.%s$Check",currentFileName,currentFunctionName)));
                writer.write(String.format(
                "@SP\n"+
                "AM=M-1\n"+
                "D=M\n"+
                "@SP\n"+
                "AM=M-1\n"+
                "D=M-D\n"+
                "M=-1\n"+
                "@%s\n"+
                "D;%s\n"+
                "@SP\n"+
                "A=M\n"+
                "M=0\n"+
                "(%s)\n"+
                "@SP\n"+
                "AM=M+1\n", 
                checkName, symbolTable.get(command), checkName));
                break;
            default:
                throw new IllegalArgumentException(String.format("Unknown arithmetic command %s.", command));
        }
    }

    /**
     * writes the push/pop execution on the stack in hack's assembly.
     * writes the push/pop execution on the stack in hack's assembly.
     * @throws IllegalArgumentException is thrown when the @param command operation, @param segment or the static is unrecognized.
     * @throws IOException is thrown when I/O error occurs.
     * @throws LimitExceededException is thrown when there is no more room for new statics
     * @throws IndexOutOfBoundsException is thrown when the @param index is exceeds the segment limits
    */
    public void writePushPop(Parser.commandTypes command, String segment, int index) throws IllegalArgumentException, IOException, LimitExceededException{
        switch(command){
            case C_PUSH:
                switch(segment){

                    case "constant":
                        if(index < 0 || index > 32767){
                            throw new IndexOutOfBoundsException(String.format("Illegal constant value: %s", index));
                        }
                        writer.write(String.format(
                        "@%d\n"+
                        "D=A\n",
                        index));
                        break;
                    //local, argument, this, that share the same structure.
                    case "local": case "argument": case "this": case "that":
                        if (index < 0 || index > 32767){
                            throw new IndexOutOfBoundsException(String.format("Illegal segment(%s) index is out of bounds: %s", segment, index));
                        }

                        writer.write(String.format("@%s\n", symbolTable.get(segment)));
                        //index optimization.
                        if(index > 0){
                            writer.write(String.format(
                            "D=M\n"+
                            "@%d\n"+
                            "A=D+A\n",
                             index));
                        }
                        else{
                            writer.write("A=M\n");
                        }
                        writer.write("D=M\n");
                        break;

                    case "pointer":
                        if(!(index >= 0 && index < 2))
                        {
                            throw new IndexOutOfBoundsException(String.format("Illegal push to the pointer segment, the index is out of bounds: %d", index));
                        }
                        writer.write(String.format(
                        "@R%d\n"+
                        "D=M\n",
                        index + 3));
                        break;
                    case "temp":
                        if(!(index >= 0 && index <= 7))
                        {
                            throw new IndexOutOfBoundsException(String.format("Illegal push to the temp segment, index is out of bounds: %d", index));
                        }
                        writer.write(String.format(
                        "@R%d\n"+
                        "D=M\n",
                        index + 5));
                        break;
                    case "static":
                        if(!statics.contains(String.format("%s.%d", currentFileName, index)))
                        {
                            throw new IllegalArgumentException(String.format("the static address for the push operation (%s.%d) does not exist.", currentFileName, index));
                        }
                        writer.write(String.format(
                        "@%s.%d\n"+
                         "D=M\n"
                        , currentFileName, index));
                        break;
                    default:
                        throw new IllegalArgumentException(String.format("Illegal push segment: %s", segment));
                }
                writer.write(
                 "@SP\n"+
                 "A=M\n"+
                 "M=D\n"+
                 "@SP\n"+
                 "M=M+1\n");
                break;

            case C_POP:
                switch(segment){
                    case "local": case "argument": case "this": case "that":
                        if(index < 0 || index > 32767){
                            throw new IndexOutOfBoundsException(String.format("Illegal segment(%s) index is out of bounds: %s", segment, index));
                        }
                        writer.write(String.format(
                        "@%s\n"+
                        "D=M\n",
                        symbolTable.get(segment)));
                        if(index > 0){
                            writer.write(String.format(
                            "@%d\n"+
                            "D=D+A\n",
                            index));
                        }
                        writer.write(
                        "@R13\n"+
                        "M=D\n"+
                        "@SP\n"+
                        "AM=M-1\n"+
                        "D=M\n"+
                        "@R13\n"+
                        "A=M\n"+
                        "M=D\n");
                        break;
                    case "pointer":
                        if(index < 0 || index > 2)
                        {
                            throw new IndexOutOfBoundsException(String.format("Illegal push to the pointer segment, index is out of bounds: %s", index));
                        }
                        writer.write(String.format(
                        "@SP\n"+
                        "AM=M-1\n"+
                        "D=M\n"+
                        "@R%d\n"+
                        "M=D\n",
                        index + 3));
                        break;
                    case"temp":
                        if(index < 0 || index > 7)
                        {
                            throw new IndexOutOfBoundsException(String.format("Illegal push to the temp segment, index is out of bounds: %s", index));
                        }
                        writer.write(String.format(
                        "@SP\n"+
                        "AM=M-1\n"+
                        "D=M\n"+
                        "@R%d\n"+
                        "M=D\n",
                        index + 5));
                        break;
                    case "static":
                        if(!statics.contains(String.format("%s.%d", currentFileName, index)))
                        {
                            if(statics.size()+1 > 240){
                                throw new LimitExceededException("The max number of statics has been exceeded.");
                            }
                            statics.add(String.format(
                            "%s.%d",
                            currentFileName, index));
                        }
                        writer.write(String.format(
                        "@SP\n"+
                        "AM=M-1\n"+
                        "D=M\n"+
                        "@%s.%d\n"+
                        "M=D\n",
                        currentFileName, index));
                        break;
                    default:
                        throw new IllegalArgumentException(String.format("Illegal pop segment: %s", segment));
                }
                break;
            default:
                throw new IllegalArgumentException(String.format("Illegal push/pop command: %s", command));
        }
    }

    /**
     * writes a label assembly.
     * @param  label is whet label name
     * @throws IOException if there is an I/O error.
    */
    public void WriteLabel(String label) throws IOException{
        writer.write(String.format(
            "(%s$%s)\n", 
            currentFunctionName, label));
    }

    /**
     * Writes a goto assembly.
     * @param  label is target of the jump
     * @throws IOException if there is an I/O error.
    */
    public void WriteGoto(String label) throws IOException{
        writer.write(String.format(
        "@%s$%s\n"+
        "0;JMP\n", 
        currentFunctionName, label));
    }

    /**
     * Writes a goto assembly.
     * @param  label is teh jump target if the stack top is true
     * @throws IOException if there is an I/O error.
    */
    public void WriteIf(String label) throws IOException{
        writer.write(String.format(
        "@SP\n"+
        "AM=M-1\n"+
        "D=M\n"+
        "@%s$%s\n"+
        "D;JNE\n",
         currentFunctionName, label));
    }
    
    /**
     * Writes a function assembly.
    */
    public void WriteFunction(String functionName, int nArgs) throws IOException, LimitExceededException{
        currentFunctionName = functionName;
        writer.write(String.format(
            "(%s)\n", 
            functionName));
        //initialize locals to 0
        for(int i = 0; i < nArgs; i++){
            writePushPop(commandTypes.C_PUSH,"constant", 0);
        }
    }

    /**
     * Writes a function call assembly.
     * @param  functionName is the function .
     * @param  nArgs is the number of argument that it has.
     * @throws IOException if there is an I/O error.
    */
    public void WriteCall(String functionName, int nArgs) throws IOException{
        String returnAddress = String.format("%s$ret.%d", functionName, nextRunningNumber(String.format("%s$ret", functionName)));
        writer.write(String.format(
            //push return address
            "@%s\n"+
            "D=A\n"+
            "@SP\n"+
            "A=M\n"+
            "M=D\n"+
            "@SP\n"+
            "M=M+1\n", 
            returnAddress));
            for (int i = 1; i < 5; i++) {
                writer.write(String.format(
                "@%s\n"+
                "D=M\n"+
                "@SP\n"+
                "A=M\n"+
                "M=D\n"+
                "@SP\n"+
                "M=M+1\n",
                "R"+i));
            }
            writer.write(String.format(
            //lcl = sp
            "@SP\n"+
            "D=M\n"+
            "@LCL\n"+
            "M=D\n"+
            //arg = sp-5-nArgs
            "@%d\n"+
            "D=D-A\n"+
            "@ARG\n"+
            "M=D\n"+
            "@%s\n"+
            "0;JMP\n"+
            "(%s)\n",
            nArgs+5, functionName, returnAddress));
    }

    /**
     * Writes a return assembly.
     * @throws LimitExceededException if the static segment if full.
     * @throws IOException if there is an I/O error.
    */
    public void WriteReturn() throws IOException, LimitExceededException {
        //set temp vars
        writer.write(
        //frame (R14) = LCL
        "@LCL\n"+
        "D=M\n"+
        "@R14\n"+
        "M=D\n"+
        //return address = *(frame - 5)
        "@5\n"+
        "A=D-A\n"+
        "D=M\n"+
        "@R15\n"+
        "M=D\n");
        writePushPop(commandTypes.C_POP,"argument", 0);
        writer.write(
        //SP = ARG + 1
        "@ARG\n"+
        "D=M+1\n"+
        "@SP\n"+
        "M=D\n");
        //Ri=*(frame-i)
        for (int i = 4; i > 0; i--) {
            writer.write(String.format(
            "@R14\n"+
            "AM=M-1\n"+
            "D=M\n"+
            "@%s\n"+
            "M=D\n",
            "R"+i));
        }
        writer.write(
        //go to return address
        "@R15\n"+
        "A=M\n"+
        "0;JMP\n");
    }

    /**
     * Closes the BufferedWriter.
     * @throws IOException if there is an I/O error.
    */
    public void close() throws IOException{
        writer.write(
        "(end)\n"+
        "@end\n"+
        "0;JMP\n");
        writer.flush();
        writer.close();
    }

    private int nextRunningNumber(String label){
        if(runningNumbersTable.containsKey(label)){
            return runningNumbersTable.merge(label, 1, Integer::sum);
        }
        else{
            runningNumbersTable.put(label, 0);
            return 0;
        }
    }
}