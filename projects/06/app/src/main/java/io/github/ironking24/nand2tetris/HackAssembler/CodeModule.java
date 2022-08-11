package io.github.ironking24.nand2tetris.HackAssembler;

/**
 * CodeModule handles translating Hack's assembly to Hack's binary.
 * @author Ironking24
 * @version 1.0.0 
 */
public class CodeModule {
    /**
     * Returns the 7 bit binary value of the @param comp as a string.
     * @param comp the value to be translated into a bit string.
     * @return 
     * @throws IllegalArgumentException
    */
    public static String comp(String comp){
        
        StringBuilder binary = new StringBuilder("");

        //set the "a" bit and handle throwing the exception.
        if(comp.contains("M")){
            binary.append("1");
        }
        else{
            binary.append("0");
        }

        //set the comp bits.
        switch(comp){
            case "0":
                binary.append("101010");
            break;
            case "1":
                binary.append("111111");
            break;
            case "-1":
                binary.append("111010");
                break;
            case "D":
                binary.append("001100");
                break;
            case "A":  case "M": 
                binary.append("110000");
                break;
            case "!D":
                binary.append("001101");
                break;
            case "!A": case "!M":
                binary.append("110001");
                break;
            case "-D":
                binary.append("001111");
                break;
            case "-A": case "-M":
                binary.append("110011");
                break;
            case "D+1": case"1+D":
                binary.append("011111");
                break;
            case "A+1": case "1+A":
            case "M+1": case "1+M":
                binary.append("110111");
                break;
            case "D-1":
                binary.append("001110");
                break;
            case "A-1": case "M-1":
                binary.append("110010");
                break;
            case "D+A": case "A+D":
            case "D+M": case "M+D":
                binary.append("000010");
                break;
            case "D-A": case "D-M":
                binary.append("010011");
                break;
            case "A-D": case "M-D": 
                binary.append("000111");
                break;
            case "D&A": case "A&D": 
            case "D&M": case "M&D":
                binary.append("000000");
                break;
            case "D|A": case "A|D": 
            case "D|M": case "M|D":
                binary.append("010101");
                break;
            default:
                throw new IllegalArgumentException(String.format("Illegal computation operation: %s",comp));      
        }
        return binary.toString();
    }

    /**
     * Returns the 3 bit binary value of the @param dest as a string.
     * @param dest the value to be translated into a bit string.
     * @return 
     * @throws IllegalArgumentException
    */
    public static String dest(String dest){
        switch(dest){
            case "":
                return "000";
            case "M":
                return "001";
            case "D":
                return "010";
            case "DM": case "MD":
                return "011";
            case "A":
                return "100";
            case "AM": case "MA":
                return "101";
            case "AD": case "DA":
                return "110";
            case "ADM": case "DAM": case "MAD":
            case "AMD": case "DMA": case "MDA":
                return "111";
            default:
                throw new IllegalArgumentException(String.format("There is no destination as: %s", dest));
        }
    }

    /**
     * returns the 3 bit binary value of the @param jump as a string.
     * @param jump the value to be translated into a bit string.
     * @return 
     * @throws IllegalArgumentException
    */
    public static String jump(String jump){
        switch (jump) {
            case "":
                return "000";
            case "JGT":
                return "001";
            case "JEQ":
                return "010";
            case "JGE":
                return "011";
            case "JLT":
                return "100";
            case "JNE":
                return "101";
            case "JLE":
                return "110";
            case "JMP":
                return "111";                   
            default:
                throw new IllegalArgumentException(String.format("Illegal jump operation: %s", jump));
        }
    }
}