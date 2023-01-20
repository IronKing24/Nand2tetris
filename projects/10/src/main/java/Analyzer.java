import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilderFactory;
import java.io.IOException;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.stream.Stream;

public class Analyzer {
    final static ArrayList<File> jackFiles = new ArrayList<File>();
    static Path sourceLocation;


    public static void main(String[] args){
        File file =  new File("D:\\CodeProjects\\Assignments\\Coursera\\Build a Modern Computer from First Principles From Nand to Tetris\\Nand2tetris\\projects\\10\\src\\test\\resources\\tests\\ArrayTest\\Main.jack");
        produceTokenList(file);

    }

    public static void xmain(String[] args){
        System.out.print(
                "Nand2Tetris' Jack Analyzer\n"+
                "\n"+
                "Author: IronKing24\n"+
                "Version: 0.5.0\n"+
                "\n"+
                "insert Nand2Tetris .jack file path as an argument to get Nand2Tetris .xml file."
        );

        //set path
        if(args.length == 0){
            sourceLocation = Paths.get("./");
        }
        else{
            sourceLocation = Paths.get(args[0]);
        }

        //check file path validity.
        if(Files.notExists(sourceLocation)){
            System.err.println("can not locate Nand2Tetris .jack file/s.");
            System.exit(-1);
        }
        if(!Files.isReadable(sourceLocation)){
            System.err.println("Insufficient read privileges.");
            System.exit(-1);
        }

        //Check for path type
        if(Files.isRegularFile(sourceLocation)){
            if(!args[0].endsWith(".jack")){
                System.err.println("File is not a valid Nand2Tetris .jack file.");
                System.exit(-1);
            }
            jackFiles.add(sourceLocation.toFile());
        }
        else if(Files.isDirectory(sourceLocation)){
            //collect all the .jack files in the directory.
            if(sourceLocation.toFile().list().length == 0){
                System.err.println("The directory does not any Nand2Tetris .jack files.");
                System.exit(-1);
            }
            try(Stream<Path> stream = Files.list(sourceLocation)){
                for(Path path : stream.toArray(Path []::new)) {
                    if(path.toString().endsWith(".jack")){
                        if(!Files.isReadable(path)){
                            System.err.printf("Access to a .jack file (%s) in directory is restricted.%n", path.getFileName());
                            System.exit(-1);
                        }
                        jackFiles.add(path.toFile());
                    }
                }
            }
            catch(IOException e){
                System.err.println("Error listing .jack files in the directory or deleting old .xml files.");
                System.err.println(e.getMessage());
                System.exit(-1);
            }
        }
        else{
            System.err.println("File type is unidentifiable.");
            System.exit(-1);
        }

        for (File file:jackFiles) {
            produceTokenList(file);
            produceTokenTree(file);
        }
    }

    static void produceTokenList(File file){
        try(Tokenizer tok = new Tokenizer(file)){

            //xml init
            Document doc = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
            Element root = doc.createElement("tokens");
            doc.appendChild(root);

            while(tok.hasMoreTokens()){
                tok.advance();
                switch (tok.tokenType()){
                    case KEYWORD:
                        Node keyword = doc.createCDATASection("keyword");
                        keyword.setNodeValue(tok.keyWord().toString().toLowerCase());
                        root.appendChild(keyword);
                        break;
                    case SYMBOL:
                        Node symbol = doc.createCDATASection("symbol");
                        symbol.setNodeValue(Character.toString(tok.symbol()));
                        root.appendChild(symbol);
                        break;
                    case IDENTIFIER:
                        Node identifier = doc.createCDATASection("identifier");
                        identifier.setNodeValue(tok.identifier());
                        root.appendChild(identifier);
                        break;
                    case STRING_CONST:
                        Node string = doc.createCDATASection("stringConstant");
                        string.setNodeValue(tok.stringVal());
                        root.appendChild(string);
                        break;
                    case INT_CONST:
                        Node num = doc.createCDATASection("integerConstant");
                        num.setNodeValue(Integer.toString(tok.intVal()));
                        root.appendChild(num);
                        break;
                }
            }
            //printTree(root);

            //Transformer transform = TransformerFactory.newInstance().newTransformer();
            //transform.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
            //transform.setOutputProperty(OutputKeys.INDENT, "yes");

            //transformer.transform(new StreamSource(doc), new StreamResult(new File()));


        }catch (Exception e){
            System.err.println(e.getMessage());
        }
    }

    static void produceTokenTree(File file){

    }

    static void printTree(Node node){
        NodeList nodeList = node.getChildNodes();
        for (int i = 0; i < nodeList.getLength(); i++) {
            Node currentNode = nodeList.item(i);
            System.out.println(currentNode);
            if(currentNode.hasChildNodes())
            {
                printTree(currentNode);
            }
        }
    }
}
