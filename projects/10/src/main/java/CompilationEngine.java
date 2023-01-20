import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CompilationEngine implements AutoCloseable {
    Tokenizer reader;
    BufferedWriter writer;


    CompilationEngine(Tokenizer input, File output) throws IOException, IllegalArgumentException {
        reader = input;
        writer = new BufferedWriter(new FileWriter(output));


        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else {
            throw new IllegalArgumentException("The Jack file is empty.");
        }

        if(reader.tokenType() == Tokenizer.TokenTypes.KEYWORD && reader.keyWord() == Tokenizer.KeyWords.CLASS){
            compileClass();
        }
        else {
            throw new IllegalArgumentException(String.format("Was expecting a class, %s was declared", reader.keyWord().toString()));
        }
    }

    void compileClass() throws IOException, IllegalArgumentException {
        writer.write("<class>");

        //compile identifier
        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else{
            throw new IllegalArgumentException("expecting Class identifier");
        }

        if(reader.tokenType() == Tokenizer.TokenTypes.IDENTIFIER){
            writer.write("<identifier>"+reader.identifier()+"</identifier>");
        }
        else{
            throw new IllegalArgumentException("expecting a class identifier");
        }

        //compile opening
        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else{
            throw new IllegalArgumentException("expecting Class body");
        }

        if(reader.tokenType() == Tokenizer.TokenTypes.SYMBOL && reader.symbol() == '{'){
            writer.write("<symbol>"+reader.symbol()+"</symbol>");
        }
        else{
            throw new IllegalArgumentException("Expected: {");
        }

        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else{
            throw new IllegalArgumentException("expecting Class body or }");
        }

        //compile body
        while (reader.hasMoreTokens()) {
            reader.advance();
            if (reader.tokenType() == Tokenizer.TokenTypes.KEYWORD) {
                if (reader.keyWord() == Tokenizer.KeyWords.STATIC || reader.keyWord() == Tokenizer.KeyWords.FIELD) {
                    compileClassVARDEC();
                }
                if (reader.keyWord() == Tokenizer.KeyWords.CONSTRUCTOR || reader.keyWord() == Tokenizer.KeyWords.FUNCTION || reader.keyWord() == Tokenizer.KeyWords.METHOD) {
                    compileSubroutine();
                }
            }
            else if (reader.tokenType() == Tokenizer.TokenTypes.SYMBOL && reader.symbol() == '}') {
                writer.write("<symbol>"+reader.symbol()+"</symbol></class>");
                break;
            }
            else{
                throw new IllegalArgumentException("Token was defined out of scope");
            }
        }

        if(reader.hasMoreTokens()){
            throw new IllegalArgumentException("unreachable code");
        }
    }

    void compileClassVARDEC() throws IOException {
       writer.write("<classVarDec><keyword>"+reader.keyWord().toString().toLowerCase()+"</keyword>");

        //compile type
        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else{
            throw new IllegalArgumentException("expecting a variable declaration type");
        }

        if(reader.tokenType() == Tokenizer.TokenTypes.KEYWORD &&
                (reader.keyWord() == Tokenizer.KeyWords.INT || reader.keyWord() == Tokenizer.KeyWords.BOOLEAN || reader.keyWord() == Tokenizer.KeyWords.CHAR)){
            writer.write("<keyword>"+reader.keyWord().toString().toLowerCase()+"</keyword>");
        }
        else if(reader.tokenType()== Tokenizer.TokenTypes.IDENTIFIER){
            writer.write("<identifier>"+reader.identifier()+"</identifier>");
        }
        else{
            throw new IllegalArgumentException("Illegal type declaration.");
        }

        //compile identifiers
        while(reader.hasMoreTokens()){
            reader.advance();

            if(reader.tokenType() == Tokenizer.TokenTypes.IDENTIFIER){
                writer.write("<identifier>"+reader.identifier()+"</identifier>");
            }
            else{
                throw new IllegalArgumentException("Global variable identifier declaration was expected.");
            }

            if(reader.hasMoreTokens()){
                reader.advance();
            }
            else {
                throw new IllegalArgumentException("expected ;");
            }

            if(reader.tokenType() == Tokenizer.TokenTypes.SYMBOL){
                if(reader.symbol() == ','){
                    continue;
                }
                else if(reader.symbol() == ';'){
                    writer.write("</classVarDec>");
                    break;
                }
                else {
                    throw new IllegalArgumentException("expected ;");
                }
            }
            else{
                throw new IllegalArgumentException("expected ;");
            }
        }
    }

    void compileSubroutine() throws IOException {
        writer.write("<subroutineDec><keyword>"+reader.keyWord().toString().toLowerCase()+"</keyword>");

        //compile type
        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else{
            throw new IllegalArgumentException("expecting a variable declaration type");
        }

        if(reader.tokenType() == Tokenizer.TokenTypes.KEYWORD &&
                (reader.keyWord() == Tokenizer.KeyWords.INT || reader.keyWord() == Tokenizer.KeyWords.BOOLEAN || reader.keyWord() == Tokenizer.KeyWords.CHAR)){
            writer.write("<keyword>"+reader.keyWord().toString().toLowerCase()+"</keyword>");
        }
        else if(reader.tokenType()== Tokenizer.TokenTypes.IDENTIFIER){
            writer.write("<identifier>"+reader.identifier()+"</identifier>");
        }
        else{
            throw new IllegalArgumentException("Illegal type declaration.");
        }

        //compile identifier
        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else{
            throw new IllegalArgumentException("expecting Class identifier");
        }

        if(reader.tokenType() == Tokenizer.TokenTypes.IDENTIFIER){
            writer.write("<identifier>"+reader.identifier()+"</identifier>");
        }
        else{
            throw new IllegalArgumentException("was expecting a class identifier");
        }

        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else {
            throw new IllegalArgumentException("expected a parameter list initialization: (");
        }

        if(reader.tokenType() != Tokenizer.TokenTypes.SYMBOL || reader.symbol() != '('){
            throw new IllegalArgumentException("expected a parameter list initialization: (");
        }
        else{
            writer.write("<symbol>"+reader.symbol()+"</symbol>");
        }

        compileParameterList();

        if(reader.tokenType() != Tokenizer.TokenTypes.SYMBOL || reader.symbol() != ')'){
            throw new IllegalArgumentException("expected a parameter list initialization: )");
        }
        else{
            writer.write("<symbol>"+reader.symbol()+"</symbol>");
        }

        compileSubroutineBody();

        writer.write("</subroutineDec>");
    }

    void compileParameterList() throws IOException {
        writer.write("<parameterList>");
        while (reader.hasMoreTokens()){
            reader.advance();

            if(reader.tokenType() == Tokenizer.TokenTypes.SYMBOL && reader.symbol() == ')'){
                writer.write("</parameterList>");
                break;
            }

            //compile type
            if(reader.hasMoreTokens()){
                reader.advance();
            }
            else{
                throw new IllegalArgumentException("expecting a variable declaration type");
            }

            if(reader.tokenType() == Tokenizer.TokenTypes.KEYWORD &&
                    (reader.keyWord() == Tokenizer.KeyWords.INT || reader.keyWord() == Tokenizer.KeyWords.BOOLEAN || reader.keyWord() == Tokenizer.KeyWords.CHAR)){
                writer.write("<keyword>"+reader.keyWord().toString().toLowerCase()+"</keyword>");
            }
            else if(reader.tokenType()== Tokenizer.TokenTypes.IDENTIFIER){
                writer.write("<identifier>"+reader.identifier()+"</identifier>");
            }
            else{
                throw new IllegalArgumentException("Illegal type declaration.");
            }

            //compile identifier
            if(reader.hasMoreTokens()){
                reader.advance();
            }
            else{
                throw new IllegalArgumentException("expecting a variable declaration type");
            }

            if(reader.tokenType() == Tokenizer.TokenTypes.IDENTIFIER){
                writer.write("<identifier>"+reader.identifier()+"</identifier>");
            }
            else{
                throw new IllegalArgumentException("Global variable identifier declaration was expected.");
            }

            if(reader.tokenType() == Tokenizer.TokenTypes.SYMBOL && reader.symbol() == ','){
                continue;
            }
            else {
                throw new IllegalArgumentException("expected )");
            }
        }
    }

    void compileSubroutineBody() throws IOException {
        writer.write("<subroutineBody>");
        if(reader.hasMoreTokens()){
            reader.advance();
        }
        else {
            throw new IllegalArgumentException("expected a code block  initialization: {");
        }
        if(reader.tokenType() == Tokenizer.TokenTypes.SYMBOL && reader.symbol() == '{'){
            writer.write("<symbol>"+reader.symbol()+"</symbol>");
        }
        else{
            throw new IllegalArgumentException("expected a code block  initialization: {");
        }
        writer.write("</subroutineBody>");
    }

    void compileVarDec(){

    }

    void compileStatements(){

    }

    void compileLet(){

    }

    void compileIF(){

    }

    void compileWhile(){

    }

    void compileDo(){

    }

    void compileReturn(){

    }

    void compileExpression(){

    }

    void compileTerm(){

    }

    void compileExpressionList(){

    }

    @Override
    public void close() throws Exception {
        writer.close();
    }
}





