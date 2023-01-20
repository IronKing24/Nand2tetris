package io.github.ironking24.nand2tetris.VMTranslator;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Objects;
import java.util.stream.Stream;

public class VMTranslator 
{
    private static Path asmFile;
    private static final ArrayList<Path> vmPaths = new ArrayList<>();

    public static void main(String[] args)
    {
        Path vmPath;
        //arg processing
        switch(args.length){
            case 0:
                System.out.print("Nand2Tetris' Virtual machine translator\n"+
                "\n"+
                "Author: IronKing24\n"+
                "Version: 1.0.0\n"+
                "\n"+
                "insert Nand2Tetris .vm file path as an argument to get Nand2Tetris .asm file.");
                System.exit(0);
                break;
            case 1:
            //check .vm file validity.
                vmPath = Paths.get(args[0]);
                if(Files.notExists(vmPath)){
                    System.err.println("can not locate Nand2Tetris .vm file/s.");
                    System.exit(-1);
                }
                if(!Files.isReadable(vmPath)){
                    System.err.println("Insufficient read privileges.");
                    System.exit(-1);
                }
                
                if(Files.isRegularFile(vmPath)){
                    if(!args[0].endsWith(".vm")){
                        System.err.println("File is not a valid Nand2Tetris .vm file.");
                        System.exit(-1);
                        }
                        vmPaths.add(vmPath);
                        asmFile = Paths.get(vmPath.getParent().toString(), vmPath.getFileName().toString().replace(".vm", ".asm"));
                    }
                else if(Files.isDirectory(vmPath)){
                //collect all the .vm files in the directory.
                    if(Objects.requireNonNull(vmPath.toFile().list()).length== 0){
                        System.err.println("The directory does not any Nand2Tetris .vm files.");
                        System.exit(-1);
                    }
                    try(Stream<Path> stream = Files.list(vmPath)){
                        for(Path path : stream.toArray(Path []::new)) {
                            if(path.toString().endsWith(".vm")){
                                if(!Files.isReadable(path)){
                                    System.err.printf("Access to a file %s in directory is restricted.%n", path.getFileName());
                                    System.exit(-1);
                                }
                                vmPaths.add(path);
                            }
                        }
                    }
                    catch(IOException e){
                        System.err.println("Error listing .vm files in the directory.");
                        System.err.println(e.getMessage());
                        System.exit(-1);
                    }      
                //.asm path computation.
                    asmFile = Paths.get(vmPath.toString(), vmPath.getFileName().toString()+".asm");
                    try{
                        Files.deleteIfExists(asmFile);
                        Files.createFile(asmFile);
                    }
                    catch(Exception e){
                        System.err.println("Error creating a new .asm file.");
                        System.err.println(e.getMessage());
                        System.exit(-1);
                    }
                }
                else{
                    System.err.println("File type is unidentifiable.");
                    System.exit(-1);
                }
                break;
        }

        //translation starts
        try(CodeWriter writer = new CodeWriter(new BufferedWriter(new FileWriter(asmFile.toFile())))){
            for (Path file : vmPaths) {
                //initialize file specific modules.
                BufferedReader reader = new BufferedReader(new FileReader(file.toFile()));
                Parser parser = new Parser(reader);
                writer.setFileName(file.getFileName().toString().replace(".vm", ""));
                while(parser.hasMoreLines()){
                    parser.advance();
                    writer.xxx("//"+parser.currentCommand+"\n");
                    switch(parser.commandType()){
                        case C_ARITHMETIC:
                            writer.writeArithmetic(parser.arg1());
                            break;
                        case C_PUSH: case C_POP:
                            writer.writePushPop(parser.commandType(), parser.arg1(), parser.arg2());
                            break;
                        case C_FUNCTION:
                            writer.WriteFunction(parser.arg1(), parser.arg2());
                            break;
                        case C_CALL:
                            writer.WriteCall(parser.arg1(), parser.arg2());
                            break;
                        case C_RETURN:
                            writer.WriteReturn();
                            break;
                        case C_LABEL:
                            writer.WriteLabel(parser.arg1());
                            break;
                        case C_GOTO:
                            writer.WriteGoto(parser.arg1());
                            break;
                        case C_IF: 
                            writer.WriteIf(parser.arg1());
                            break;
                        default:
                            throw new Exception(String.format("Command %s was not recognized.", parser.commandType().name()));
                    }
                }
                reader.close();
            }
        }
        catch(Exception e){
            System.err.println("Error, while writing to .asm file.");
            System.err.println(e.getMessage());
            System.exit(-1);
        }
    }
}

