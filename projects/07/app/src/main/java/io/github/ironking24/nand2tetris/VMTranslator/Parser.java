package io.github.ironking24.nand2tetris.VMTranslator;

import java.io.BufferedReader;
import java.io.IOException;

public class Parser{

    public enum commandTypes{C_ARITHMETIC, C_PUSH, C_POP}

    private final BufferedReader reader;
    public String currentCommand = null;
    private commandTypes currentCommandType = null;
    private String [] tokens; 
    
    Parser(BufferedReader input) {
        this.reader = input;
    }

    /**
     * Are there more lines in the input?
     * @return True if the file has not reached its end.
     * @throws IOException if an IO error occurs during marking, reading, and resetting.
    */
    public boolean hasMoreLines() throws IOException{
        reader.mark(1);
        boolean result = reader.read() == -1;
        reader.reset();
        return result;
    }

    /**
     * Reads the next command from the input file.
     * @throws IOException If an error occurs while reading a line or checking for next line.
     * @throws IllegalArgumentException IF the command type was not recognized.
    */
    public void advance() throws IOException, IllegalArgumentException{
        String nextCommand;

        while(hasMoreLines()){
            nextCommand = reader.readLine().trim();
            //handel white spaces and comments (no trailing comments according to the specification).
            if(nextCommand.equals("") ||nextCommand.contains("//")){
                continue;
            }

            currentCommand = nextCommand;
            break;
        }

        tokens = currentCommand.split(" ");

        switch(tokens[0]){
            case "add": case "sub": case "neg": 
            case "eq": case "gt": case "lt": 
            case "and": case "or": case"not":
                currentCommandType = commandTypes.C_ARITHMETIC;
                break;
            case "push":
                currentCommandType = commandTypes.C_PUSH;
                break;
            case "pop":
                currentCommandType = commandTypes.C_POP;
                break;
            default:
                throw new IllegalArgumentException(String.format("Unrecognized command: %s.", tokens[0]));
        }
    }

    /**
     * Returns a constant that represents the command type
     * @return commandTypes enum
    */
    public commandTypes commandType(){
       return currentCommandType;
    }

    /**
     * returns the first argument of the current command.
     * @return Command name.
    */
    public String arg1(){
        if (currentCommandType == commandTypes.C_ARITHMETIC) {
            return tokens[0];
        }
        else
        {
            return tokens[1];
        }
    }

    /**
     * returns the first argument of the current command.
     * @return Command argument
    */
    public int arg2(){

        return Integer.parseInt(tokens[2]);
    }
}
