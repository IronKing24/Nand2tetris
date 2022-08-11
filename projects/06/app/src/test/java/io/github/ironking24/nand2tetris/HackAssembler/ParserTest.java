package io.github.ironking24.nand2tetris.HackAssembler;

import static io.github.ironking24.nand2tetris.HackAssembler.Parser.instructionTypes;
import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.BufferedReader;
import java.io.FileReader;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;


@DisplayName("Parser test")
public class ParserTest {
    static Parser parser;
    static BufferedReader reader;
    int lineNumber = 1;

    @BeforeAll
    static void init(){
        assertDoesNotThrow(
            ()->{
                reader = new BufferedReader(
                         new FileReader(
                         ClassLoader.getSystemClassLoader().getResource("Parser/test.asm").getPath().replace("%20", " ")));
                parser = new Parser(reader);
        });   
    }

    @BeforeEach
    void next(){
        lineNumber++;
        assertDoesNotThrow(
            ()->{
                parser.hasMoreLines();
            });
        assertDoesNotThrow(
            ()->{
                parser.Advance();
            });

        if(lineNumber < 24){
            assertDoesNotThrow(
                ()->{
                    assertTrue(parser.hasMoreLines());
                });
        }
        else{
            assertDoesNotThrow(
                ()->{
                    assertFalse(parser.hasMoreLines());
                });
        }

    }

    @AfterAll
    static void close(){
        assertDoesNotThrow(
            ()->{
                reader.close();
            });
    }

    @Test
    @DisplayName("instruction #0")
    void instruction0(){    
        assertAll("@Label",
        ()->{assertEquals(instructionTypes.A_instruction, parser.instructionType());},
        ()->{assertEquals("Label", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #1")
    void instruction1(){    
        assertAll("@42069",
        ()->{assertEquals(instructionTypes.A_instruction, parser.instructionType());},
        ()->{assertEquals("42069", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #2")
    void instruction2(){    
        assertAll("(label)",
        ()->{assertEquals(instructionTypes.L_instruction, parser.instructionType());},
        ()->{assertEquals("label", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #3")
    void instruction3(){    
        assertAll("dest=comp;jump",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("dest" ,parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("jump" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #4")
    void instruction4(){    
        assertAll("M=1;JMP",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("M" ,parser.dest());},
        ()->{assertEquals("1" ,parser.comp());},
        ()->{assertEquals("JMP" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #5")
    void instruction5(){    
        assertAll("adm=comp",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("adm" ,parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #6")
    void instruction6(){    
        assertAll("comp;jlt",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("jlt" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #7")
    void instruction7(){    
        assertAll("adm=;jmp",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("adm" ,parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("jmp" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #8")
    void instruction8(){    
        assertAll("adm=comp;jmp",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("adm" ,parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("jmp" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #9")
    void instruction9(){    
        assertAll("comp",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #10")
    void instruction10(){    
        assertAll("dest=",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("dest" ,parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #11")
    void instruction11(){    
        assertAll(";jmp",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("jmp" ,parser.jump());}
        );  
    }

@Test
    @DisplayName("instruction #12")
    void instruction12(){    
        assertAll("@Label//",
        ()->{assertEquals(instructionTypes.A_instruction, parser.instructionType());},
        ()->{assertEquals("Label", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #13")
    void instruction13(){    
        assertAll("@42069//",
        ()->{assertEquals(instructionTypes.A_instruction, parser.instructionType());},
        ()->{assertEquals("42069", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #14")
    void instruction14(){    
        assertAll("(label)//",
        ()->{assertEquals(instructionTypes.L_instruction, parser.instructionType());},
        ()->{assertEquals("label", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #15")
    void instruction15(){    
        assertAll("dest=comp;jump//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("dest" ,parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("jump" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #16")
    void instruction16(){    
        assertAll("M=1;JMP//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("M" ,parser.dest());},
        ()->{assertEquals("1" ,parser.comp());},
        ()->{assertEquals("JMP" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #17")
    void instruction17(){    
        assertAll("adm=comp//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("adm" ,parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #18")
    void instruction18(){    
        assertAll("comp;jlt//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("jlt" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #19")
    void instruction19(){    
        assertAll("adm=;jmp//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("adm" ,parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("jmp" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #20")
    void instruction20(){    
        assertAll("adm=comp;jmp//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("adm" ,parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("jmp" ,parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #21")
    void instruction21(){    
        assertAll("comp//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("comp" ,parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #22")
    void instruction22(){    
        assertAll("dest=//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("dest" ,parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("", parser.jump());}
        );  
    }

    @Test
    @DisplayName("instruction #23")
    void instruction23(){    
        assertAll(";jmp//",
        ()->{assertEquals(instructionTypes.C_instruction, parser.instructionType());},
        ()->{assertEquals("", parser.symbol());},
        ()->{assertEquals("", parser.dest());},
        ()->{assertEquals("", parser.comp());},
        ()->{assertEquals("jmp" ,parser.jump());}
        );  
    }
}