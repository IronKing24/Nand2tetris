import java.io.Closeable;
import java.io.IOException;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.util.Arrays;

public class Tokenizer implements Closeable {

    private final char [] symbols =
            {'{', '}', '[', ']', '(', ')', '.', ',', ';', '+', '-', '*', '/', '&', '|', '<', '>', '=', '~'};
    private final String [] keywords =
            {"class", "constructor", "function", "method", "field", "static", "var", "int", "char", "boolean",
            "void", "ture", "false", "null", "this", "let", "do", "if", "else", "while", "return"};
    public enum TokenTypes {KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST}
    public enum KeyWords  {CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN, CHAR, VOID, VAR,
        STATIC, FIELD, LET, DO, IF, ElSE, WHILE, RETURN, TRUE, FALSE, THIS, NULL}

    private final BufferedReader reader;

    public String current_token;

    String fileName;
    Tokenizer(File input) throws IOException {
        fileName = input.getName();
        reader = new BufferedReader(new FileReader(input));
    }

    public boolean hasMoreTokens() throws IOException {
        reader.mark(2);
        int nextChar = reader.read();

        //end of file guard
        if (nextChar == -1) {
            reader.reset();
            return false;
        }
        //white space skip
        else if (Character.isWhitespace(nextChar)) {
            while (Character.isWhitespace(nextChar)) {
                reader.mark(1);
                nextChar = reader.read();
            }
            reader.reset();
            return hasMoreTokens();
        }
        //comments
        else if (nextChar == '/') {
            nextChar = reader.read();
            //skip one line comments
            if (nextChar == '/') {
                do {
                    reader.mark(1);
                    nextChar = reader.read();
                } while (nextChar != '\n' && nextChar != -1);
                reader.reset();
                return hasMoreTokens();
            }
            //multiline comments
            else if (nextChar == '*') {
                do {
                    nextChar = reader.read();
                    if (nextChar == '*' && reader.read() == '/') {
                        break;
                    }
                } while (nextChar != -1);
                return hasMoreTokens();
            } else {
                reader.reset();
                return true;
            }
        }
        else{
            reader.reset();
            return true;
        }
    }
    public void advance() throws IOException, IllegalStateException{
        if(!hasMoreTokens()){
            throw new IllegalStateException("End of the file has been reached");
        }

        StringBuilder buff = new StringBuilder();
        do{
            reader.mark(1);
            int newChar = reader.read();

            if(newChar == '\"'){ //string token
                buff.append((char)newChar);
                do {
                    newChar = reader.read();
                    buff.append((char)newChar);
                }
                while (newChar != '\"' && newChar != -1);
                if (newChar == -1){
                    throw new IllegalArgumentException("Missing a closing \"");
                }
            }
            else if(isSymbol((char)newChar)){ //symbol encountered
                if(buff.length() > 0){ //trailing a token (end of token)
                    current_token = buff.toString();
                    reader.reset();
                }
                else{//symbol token
                    current_token = String.valueOf((char)newChar);
                }
                break;
            }
            else if(Character.isWhitespace(newChar)){//Whitespace encountered (end of token)
                current_token = buff.toString();
                reader.reset();
                break;
            }
            else{
                buff.append((char)newChar);
            }
        }while (true);
    }

    public TokenTypes tokenType() throws IllegalStateException, NumberFormatException{
        if(Arrays.asList(keywords).contains(current_token)){
                return TokenTypes.KEYWORD;
        }
        else if (isSymbol(current_token.charAt(0))) {
                return TokenTypes.SYMBOL;
        }
        else if (current_token.startsWith("\"") && current_token.endsWith("\"")) {
                return TokenTypes.STRING_CONST;
        }
        else if (isNumber(current_token)) {
            return TokenTypes.INT_CONST;
        }
        else if (Character.isLetter(current_token.charAt(0)) || current_token.charAt(0) == '_') {
                return TokenTypes.IDENTIFIER;
        }
        else{
                throw new IllegalStateException(String.format("the token \"%s\" is not recognized.", current_token));
        }
    }

    public KeyWords keyWord() throws IllegalStateException {
        if(tokenType() == TokenTypes.KEYWORD){
            return KeyWords.valueOf(current_token.toUpperCase());
        }
        else{
            throw new IllegalStateException(String.format("the token \"%s\" is not as keyword.", current_token));
        }
    }

    public char symbol() {
        if(tokenType() == TokenTypes.SYMBOL){
            return current_token.charAt(0);
        }
        else {
            throw new IllegalStateException(String.format("The token \"%s\" was not recognized as a symbol.", current_token));
        }
    }

    public String identifier() throws IllegalStateException {
        if(tokenType() == TokenTypes.IDENTIFIER){
            return current_token;
        }
        else {
            throw new IllegalStateException(String.format("The token \"%s\" was not recognized as a identifier.", current_token));
        }
    }

    public int intVal() throws IllegalStateException, IllegalArgumentException {
        if(tokenType() == TokenTypes.INT_CONST) {
            int value =Integer.parseInt(current_token);
            if(value > 32767 || value < 0)
            {
                throw new IllegalArgumentException(String.format("%d exceeds the limits (0 - 32767)",value));
            }
            return value;
        }
        else {
            throw new IllegalStateException(String.format("the token \"%s\" does not represent a integer" , current_token));
        }
    }

    public String stringVal() throws IllegalStateException {
        if(tokenType() == TokenTypes.STRING_CONST) {
            return current_token.substring(1, current_token.length() -1);
        }
        else {
            throw new IllegalStateException(String.format("the token \"%s\" does not represent a string" , current_token));
        }
    }

    @Override
    public void close() throws IOException {
        reader.close();
    }

    //check if char is in the symbol table
    private boolean isSymbol(char character){
        for (char c:symbols) {
            if(character == c){
                return true;
            }
        }
        return false;
    }

    private boolean isNumber(String num){
        for (char c:num.toCharArray()) {
            if(!Character.isDigit(c)){
                return false;
            }
            else if(c == '.'){
                continue;
            }
        }
        return true;
    }
}