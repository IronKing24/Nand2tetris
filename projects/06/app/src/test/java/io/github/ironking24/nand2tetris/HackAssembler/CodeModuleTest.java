package io.github.ironking24.nand2tetris.HackAssembler;

import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import org.apache.commons.lang3.RandomStringUtils;




@DisplayName("Code Module Test")
public class CodeModuleTest {
    @Test
    @DisplayName("test comp")
    void compTest(){
        String randomString = RandomStringUtils.random(1000);
        
        assertAll("Computation instruction evaluation",
        ()->assertEquals("0101010", CodeModule.comp("0")),
        ()->assertEquals("0111111", CodeModule.comp("1")),
        ()->assertEquals("0111010", CodeModule.comp("-1")),
        ()->assertEquals("0001100", CodeModule.comp("D")),
        ()->assertEquals("0110000", CodeModule.comp("A")),
        ()->assertEquals("1110000", CodeModule.comp("M")),
        ()->assertEquals("0001101", CodeModule.comp("!D")),
        ()->assertEquals("0110001", CodeModule.comp("!A")),
        ()->assertEquals("1110001", CodeModule.comp("!M")),
        ()->assertEquals("0001111", CodeModule.comp("-D")),
        ()->assertEquals("0110011", CodeModule.comp("-A")),
        ()->assertEquals("1110011", CodeModule.comp("-M")),
        ()->assertEquals("0011111", CodeModule.comp("D+1")),
        ()->assertEquals("0110111", CodeModule.comp("A+1")),
        ()->assertEquals("1110111", CodeModule.comp("M+1")),
        ()->assertEquals("0001110", CodeModule.comp("D-1")),
        ()->assertEquals("0110010", CodeModule.comp("A-1")),
        ()->assertEquals("1110010", CodeModule.comp("M-1")),
        ()->assertEquals("0000010", CodeModule.comp("D+A")),
        ()->assertEquals("1000010", CodeModule.comp("D+M")),
        ()->assertEquals("0010011", CodeModule.comp("D-A")),
        ()->assertEquals("1010011", CodeModule.comp("D-M")),
        ()->assertEquals("0000111", CodeModule.comp("A-D")),
        ()->assertEquals("1000111", CodeModule.comp("M-D")),
        ()->assertEquals("0000000", CodeModule.comp("D&A")),
        ()->assertEquals("1000000", CodeModule.comp("D&M")),
        ()->assertEquals("0010101", CodeModule.comp("D|A")),
        ()->assertEquals("1010101", CodeModule.comp("D|M")),
        ()->assertThrowsExactly(IllegalArgumentException.class,
        ()->{CodeModule.comp(randomString);}
            ,"Illegal computation operation "+ randomString));
    }

    @Test
    @DisplayName("Test dest")
    void destTest(){
        String randomString = RandomStringUtils.random(1000);

        assertAll("Destination instruction evaluation",
        ()->assertEquals("000", CodeModule.dest("")),
        ()->assertEquals("001", CodeModule.dest("M")),
        ()->assertEquals("010", CodeModule.dest("D")),
        ()->assertEquals("011", CodeModule.dest("DM")),
        ()->assertEquals("100", CodeModule.dest("A")),
        ()->assertEquals("101", CodeModule.dest("AM")),
        ()->assertEquals("110", CodeModule.dest("AD")),
        ()->assertEquals("111", CodeModule.dest("ADM")),
        ()->assertThrowsExactly(IllegalArgumentException.class,
        ()->{CodeModule.comp(randomString);}
            ,"There is no destination as "+ randomString));
    }

    @Test
    @DisplayName("Test Jump")
    void jumpTest(){
        String randomString = RandomStringUtils.random(1000);

        assertAll(
            "Jump instruction evaluation",
            ()->assertEquals("000", CodeModule.jump("")),
            ()->assertEquals("001", CodeModule.jump("JGT")),
            ()->assertEquals("010", CodeModule.jump("JEQ")),
            ()->assertEquals("011", CodeModule.jump("JGE")),
            ()->assertEquals("100", CodeModule.jump("JLT")),
            ()->assertEquals("101", CodeModule.jump("JNE")),
            ()->assertEquals("110", CodeModule.jump("JLE")),
            ()->assertEquals("111", CodeModule.jump("JMP")),
            ()->assertThrowsExactly(IllegalArgumentException.class,
            ()->{CodeModule.comp(randomString);}
                ,"Illegal jump operation: "+ randomString));
    }
}
