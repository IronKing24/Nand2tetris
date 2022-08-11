package io.github.ironking24.nand2tetris.HackAssembler;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.FileReader;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.apache.commons.io.IOUtils;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

public class HackAssemblerTest {

    @Test
    @DisplayName("Add")
    void addTest(){
        assertDoesNotThrow(()->{
            String path = ClassLoader.getSystemResource("Main/add/Add.asm").getPath().substring(1).replace("%20", " ").replace(".asm", "");
            HackAssembler.main(new String[]{path+".asm"});
                assertTrue(IOUtils.contentEqualsIgnoreEOL(
                new FileReader(path+".hack"), 
                new FileReader(path+"Test.hack")
                ));
            Files.deleteIfExists(Paths.get(path,".hack") );
        });
    }

    @Nested
    @DisplayName("Max")
    class max{
        @Test
        @DisplayName("Labelless")
        void labelless(){
            assertDoesNotThrow(()->{
                String path = ClassLoader.getSystemResource("Main/max/Max.asm").getPath().substring(1).replace("%20", " ").replace(".asm", "");
                HackAssembler.main(new String[]{path+".asm"});
                    assertTrue(IOUtils.contentEqualsIgnoreEOL(
                    new FileReader(path+".hack"), 
                    new FileReader(path+"Test.hack")
                    ));
                Files.deleteIfExists(Paths.get(path,".hack") );
            });
        }

        @Test
        @DisplayName("Labeled")
        void Labeled(){
            assertDoesNotThrow(()->{
                String path = ClassLoader.getSystemResource("Main/max/MaxL.asm").getPath().substring(1).replace("%20", " ").replace(".asm", "");
                HackAssembler.main(new String[]{path+".asm"});
                    assertTrue(IOUtils.contentEqualsIgnoreEOL(
                    new FileReader(path+".hack"), 
                    new FileReader(path+"Test.hack")
                    ));
                Files.deleteIfExists(Paths.get(path,".hack") );
            });
        }
    }

    @Nested
    @DisplayName("Rect")
    class rect{
        @Test
        @DisplayName("Labelless")
        void labelless(){
            assertDoesNotThrow(()->{
                String path = ClassLoader.getSystemResource("Main/rect/Rect.asm").getPath().substring(1).replace("%20", " ").replace(".asm", "");
                HackAssembler.main(new String[]{path+".asm"});
                    assertTrue(IOUtils.contentEqualsIgnoreEOL(
                    new FileReader(path+".hack"), 
                    new FileReader(path+"Test.hack")
                    ));
                Files.deleteIfExists(Paths.get(path,".hack") );
            });
        }

        @Test
        @DisplayName("Labeled")
        void Labeled(){
            assertDoesNotThrow(()->{
                String path = ClassLoader.getSystemResource("Main/rect/Rect.asm").getPath().substring(1).replace("%20", " ").replace(".asm", "");
                HackAssembler.main(new String[]{path+".asm"});
                    assertTrue(IOUtils.contentEqualsIgnoreEOL(
                    new FileReader(path+".hack"), 
                    new FileReader(path+"Test.hack")
                    ));
                Files.deleteIfExists(Paths.get(path,".hack") );
            });
        }
    }

    @Nested
    @DisplayName("Pong")
    class pong{
        @Test
        @DisplayName("Labelless")
        void labelless(){
            assertDoesNotThrow(()->{
                String path = ClassLoader.getSystemResource("Main/pong/Pong.asm").getPath().substring(1).replace("%20", " ").replace(".asm", "");
                HackAssembler.main(new String[]{path+".asm"});
                    assertTrue(IOUtils.contentEqualsIgnoreEOL(
                    new FileReader(path+".hack"), 
                    new FileReader(path+"Test.hack")
                    ));
                Files.deleteIfExists(Paths.get(path,".hack") );
            });
        }

        @Test
        @DisplayName("Labeled")
        void Labeled(){
            assertDoesNotThrow(()->{
                String path = ClassLoader.getSystemResource("Main/pong/Pong.asm").getPath().substring(1).replace("%20", " ").replace(".asm", "");
                HackAssembler.main(new String[]{path+".asm"});
                    assertTrue(IOUtils.contentEqualsIgnoreEOL(
                    new FileReader(path+".hack"), 
                    new FileReader(path+"Test.hack")
                    ));
                Files.deleteIfExists(Paths.get(path,".hack") );
            });
        }
    }
}
