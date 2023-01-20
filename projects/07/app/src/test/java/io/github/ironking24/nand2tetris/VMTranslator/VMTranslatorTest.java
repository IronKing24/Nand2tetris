package io.github.ironking24.nand2tetris.VMTranslator;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

public class VMTranslatorTest {
    static String classPath;

    @BeforeAll
    static void init(){
        StringBuilder commandBuilder = new StringBuilder();
        
        //check for java classpath
        String classPathHolder = System.getenv("CLASSPATH");
        if(classPathHolder != null){
            commandBuilder.append(classPathHolder).append(File.pathSeparator);
        }
        else{
            System.err.println("Java Home was not found.");
        }

        final String [] libs = {"CPUEmulator", "CPUEmulator/Hack.jar", "CPUEmulator/HackGUI.jar", "CPUEmulator/Simulators.jar", "CPUEmulator/SimulatorsGUI.jar", "CPUEmulator/Compilers.jar"};

        for (String lib : libs) {
            commandBuilder.append(ClassLoader.getSystemResource(lib).getPath().substring(1)).append(File.pathSeparator);
        }
        classPath =  commandBuilder.toString().replace("%20", " ").replace("/", File.separator);
    }


    @Nested
    @DisplayName("Test 07")
    class StackArithmetic{
        @Test
        @DisplayName("Simple add")
        void simpleAdd(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/StackArithmetic/SimpleAdd/SimpleAdd.vm").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/StackArithmetic/SimpleAdd/SimpleAdd.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/StackArithmetic/SimpleAdd/SimpleAdd.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/StackArithmetic/SimpleAdd/SimpleAdd.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }
        @Test
        @DisplayName("Stack test")
        void stackTest(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/StackArithmetic/StackTest/StackTest.vm").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/StackArithmetic/StackTest/StackTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/StackArithmetic/StackTest/StackTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/StackArithmetic/StackTest/StackTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }
    }

    @Nested
    @DisplayName("Memory access")
    class MemoryAccess{
        @Test
        @DisplayName("Basic test")
        void basicTest(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/MemoryAccess/BasicTest/BasicTest.vm").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/MemoryAccess/BasicTest/BasicTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/MemoryAccess/BasicTest/BasicTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/MemoryAccess/BasicTest/BasicTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }

        @Test
        @DisplayName("Pointer test")
        void pointerTest(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/MemoryAccess/PointerTest/PointerTest.vm").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/MemoryAccess/PointerTest/PointerTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/MemoryAccess/PointerTest/PointerTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/MemoryAccess/PointerTest/PointerTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }

        @Test
        @DisplayName("Static test")
        void staticTest(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/MemoryAccess/StaticTest/StaticTest.vm").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/MemoryAccess/StaticTest/StaticTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/MemoryAccess/StaticTest/StaticTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/MemoryAccess/StaticTest/StaticTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }
    }

}
