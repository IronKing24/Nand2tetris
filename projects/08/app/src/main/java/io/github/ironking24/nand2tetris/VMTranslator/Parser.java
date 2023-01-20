package io.github.ironking24.nand2tetris.VMTranslator;

import java.io.BufferedReader;
import java.io.IOException;

public class Parser{

    public enum commandTypes{C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL, Constant}

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
            //clean inline comments
            if(nextCommand.contains("//")){
                if(nextCommand.startsWith("//")){
                    continue;
                }
                else{
                    nextCommand = nextCommand.substring(0, nextCommand.indexOf("//")).trim();
                }
            }
            if(nextCommand.equals("")){
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
            case "label":
                currentCommandType = commandTypes.C_LABEL;
                break;
            case "goto":
                currentCommandType = commandTypes.C_GOTO;
                break;
            case "if-goto":
                currentCommandType = commandTypes.C_IF;
                break;
            case "function":
                currentCommandType = commandTypes.C_FUNCTION;
                break;
            case "return":
                currentCommandType = commandTypes.C_RETURN;
                break;
            case "call":
                currentCommandType = commandTypes.C_CALL;
                break;
            case "constant":
                currentCommandType = commandTypes.Constant;
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
