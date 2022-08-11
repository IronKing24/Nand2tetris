package io.github.ironking24.nand2tetris.HackAssembler;

import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.Random;

import org.apache.commons.lang3.RandomStringUtils;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.TestInstance.Lifecycle;

@DisplayName("Symbol table Test")
public class SymbolTableTest {

    static SymbolTable table;

    @Nested
    @TestInstance(Lifecycle.PER_CLASS)
    class DefaultTest{
    
        @BeforeAll
        void init(){
            table = new SymbolTable();
        }

        @Test
        @DisplayName("Contains test")
        void defaultKeysTest(){   
            assertAll("Contains default test",
            ()->assertTrue(table.contains("R0")),
            ()->assertTrue(table.contains("R1")),
            ()->assertTrue(table.contains("R2")),
            ()->assertTrue(table.contains("R3")),
            ()->assertTrue(table.contains("R4")),
            ()->assertTrue(table.contains("R5")),
            ()->assertTrue(table.contains("R6")),
            ()->assertTrue(table.contains("R7")),
            ()->assertTrue(table.contains("R8")),
            ()->assertTrue(table.contains("R9")),
            ()->assertTrue(table.contains("R10")),
            ()->assertTrue(table.contains("R11")),
            ()->assertTrue(table.contains("R12")),
            ()->assertTrue(table.contains("R13")),
            ()->assertTrue(table.contains("R14")),
            ()->assertTrue(table.contains("R15")),
            ()->assertTrue(table.contains("SP")),
            ()->assertTrue(table.contains("LCL")),
            ()->assertTrue(table.contains("ARG")),
            ()->assertTrue(table.contains("THIS")),
            ()->assertTrue(table.contains("THAT")),
            ()->assertTrue(table.contains("SCREEN")),
            ()->assertTrue(table.contains("KBD")),
            ()->assertFalse(table.contains( RandomStringUtils.random(1000)))
            );
        }
        
        @Test
        @DisplayName("getAddress test")
        void defaultValuesTest(){
            assertAll("Default getAddress test",
            ()->assertEquals(0, table.getAddress("R0")),
            ()->assertEquals(1, table.getAddress("R1")),
            ()->assertEquals(2, table.getAddress("R2")),
            ()->assertEquals(3, table.getAddress("R3")),
            ()->assertEquals(4, table.getAddress("R4")),
            ()->assertEquals(5, table.getAddress("R5")),
            ()->assertEquals(6, table.getAddress("R6")),
            ()->assertEquals(7, table.getAddress("R7")),
            ()->assertEquals(8, table.getAddress("R8")),
            ()->assertEquals(9, table.getAddress("R9")),
            ()->assertEquals(10, table.getAddress("R10")),
            ()->assertEquals(11, table.getAddress("R11")),
            ()->assertEquals(12, table.getAddress("R12")),
            ()->assertEquals(13, table.getAddress("R13")),
            ()->assertEquals(14, table.getAddress("R14")),
            ()->assertEquals(15, table.getAddress("R15")),
            ()->assertEquals(0, table.getAddress("SP")),
            ()->assertEquals(1, table.getAddress("LCL")),
            ()->assertEquals(2, table.getAddress("ARG")),
            ()->assertEquals(3, table.getAddress("THIS")),
            ()->assertEquals(4, table.getAddress("THAT")),
            ()->assertEquals(16384, table.getAddress("SCREEN")),
            ()->assertEquals(24576, table.getAddress("KBD"))
            );
        }
    }
   
    @Nested
    @TestInstance(Lifecycle.PER_CLASS)
    class RandomTest{
        ArrayList<String> randomLabels;
        ArrayList<Integer> randomAddresses;
        Random random;
        SymbolTable table;

        @BeforeAll
        void randomInit(){
            table = new SymbolTable();
            randomLabels = new ArrayList<String>();
            randomAddresses = new ArrayList<Integer>();
            random = new Random();

            //fill array lists with strings and numbers
            for(int i = 0; i < 100; i++){
                String randomString = RandomStringUtils.random(1000);
                if(randomLabels.contains(randomString)){
                    continue;
                }
                randomLabels.add(randomString);
                randomAddresses.add(random.nextInt());
            }

            for(int i = 0; i < randomLabels.size(); i++){
                table.addEntry(randomLabels.get(i), randomAddresses.get(i));
            }
        }

        @Test
        @DisplayName("Random contains test")
        void randomContainsTest(){
            assertTrue(randomContainsTrueTest());
            assertTrue(randomContainsFalseTest());
        }
        
        boolean randomContainsTrueTest(){
            for(int i = 0; i < randomLabels.size(); i++){
                if(!table.contains(randomLabels.get(i))){
                    return false;
                }
            }
            return true;
        }
        boolean randomContainsFalseTest(){
            for(int i = 0; i < 100; i++){
                if(table.contains(RandomStringUtils.random(1000))){
                    return false;
                }
            }
            return true;
        }


        @Test
        @DisplayName("Random getAddress test")
        void RandomGetAddressTest(){
            for(int i = 0; i < randomLabels.size(); i++){
                assertEquals(randomAddresses.get(i), table.getAddress(randomLabels.get(i)));
                assertNotEquals(random.nextInt(), table.getAddress(randomLabels.get(i)));
            }
        }
    }
}