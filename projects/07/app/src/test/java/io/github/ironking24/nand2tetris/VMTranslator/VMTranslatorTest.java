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
            commandBuilder.append(classPathHolder + File.pathSeparator);
        }
        else{
            System.err.println("Java Home was not found.");
        }
        
        final String [] libs = {"CPUEmulator", "CPUEmulator/Hack.jar", "CPUEmulator/HackGUI.jar", "CPUEmulator/Simulators.jar", "CPUEmulator/SimulatorsGUI.jar", "CPUEmulator/Compilers.jar"};
        for (String lib : libs) {
            commandBuilder.append(ClassLoader.getSystemResource(lib).getPath().substring(1) + File.pathSeparator);
        }
        classPath =  commandBuilder.toString().replace("%20", " ").replace("/", File.separator);
    }

    @Nested
    @DisplayName("Test group 07")
    class TestGroup01{
        @Nested
        @DisplayName("Stack arithmetic")
        class StackArithmetic{
            @Test
            @DisplayName("Simple add")
            void simpleAdd(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("01/StackArithmetic/SimpleAdd/SimpleAdd.vm").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("01/StackArithmetic/SimpleAdd/SimpleAdd.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/StackArithmetic/SimpleAdd/SimpleAdd.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/StackArithmetic/SimpleAdd/SimpleAdd.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }

            @Test
            @DisplayName("Stack test")
            void stackTest(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("01/StackArithmetic/StackTest/StackTest.vm").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("01/StackArithmetic/StackTest/StackTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/StackArithmetic/StackTest/StackTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/StackArithmetic/StackTest/StackTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
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
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("01/MemoryAccess/BasicTest/BasicTest.vm").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("01/MemoryAccess/BasicTest/BasicTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/MemoryAccess/BasicTest/BasicTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/MemoryAccess/BasicTest/BasicTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }
            
            @Test
            @DisplayName("Pointer test")
            void pointerTest(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("01/MemoryAccess/PointerTest/PointerTest.vm").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("01/MemoryAccess/PointerTest/PointerTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor(); 
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/MemoryAccess/PointerTest/PointerTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/MemoryAccess/PointerTest/PointerTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }
            
            @Test
            @DisplayName("Static test")
            void staticTest(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("01/MemoryAccess/StaticTest/StaticTest.vm").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("01/MemoryAccess/StaticTest/StaticTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/MemoryAccess/StaticTest/StaticTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("01/MemoryAccess/StaticTest/StaticTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }
        }
    }

    @Nested
    @DisplayName("Test group 08")
    class TestGroup02{
        @Nested
        @DisplayName("Program flow")
        class ProgramFlow{
            @Test
            @DisplayName("Basic loop")
            void basicLoop(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("02/ProgramFlow/BasicLoop/BasicLoop.vm").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("02/ProgramFlow/BasicLoop/BasicLoop.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/ProgramFlow/BasicLoop/BasicLoop.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/ProgramFlow/BasicLoop/BasicLoop.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }

            @Test
            @DisplayName("Fibonacci series")
            void fibonacciSeries(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("02/ProgramFlow/FibonacciSeries/FibonacciSeries.vm").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("02/ProgramFlow/FibonacciSeries/FibonacciSeries.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/ProgramFlow/FibonacciSeries/FibonacciSeries.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/ProgramFlow/FibonacciSeries/FibonacciSeries.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }
        }

        @Nested
        @DisplayName("Function calls")
        class FunctionCalls{
            @Test
            @DisplayName("Simple function")
            void simpleFunction(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("02/FunctionCalls/SimpleFunction/SimpleFunction.vm").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("02/FunctionCalls/SimpleFunction/SimpleFunction.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/FunctionCalls/SimpleFunction/SimpleFunction.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/FunctionCalls/SimpleFunction/SimpleFunction.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }

            @Test
            @DisplayName("Nested call")
            void nestedCall(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("02/FunctionCalls/NestedCall").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("02/FunctionCalls/NestedCall/NestedCall.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/FunctionCalls/NestedCall/NestedCall.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/FunctionCalls/NestedCall/NestedCall.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }

            @Test
            @DisplayName("Fibonacci element")
            void fibonacciElement(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("02/FunctionCalls/FibonacciElement").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("02/FunctionCalls/FibonacciElement/FibonacciElement.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, existCode);
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/FunctionCalls/FibonacciElement/FibonacciElement.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/FunctionCalls/FibonacciElement/FibonacciElement.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }

            @Test
            @DisplayName("Statics test")
            void staticsTest(){
                assertDoesNotThrow(()->{
                    VMTranslator.main(new String[]{ClassLoader.getSystemResource("02/FunctionCalls/StaticsTest").getPath().replace("%20", " ").substring(1)});
                    ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("02/FunctionCalls/StaticsTest/StaticsTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                    Process process = CPUEmulator.inheritIO().start();
                    int existCode = process.waitFor();
                    assertEquals(0, process.waitFor());
                    if(existCode == 0){
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/FunctionCalls/StaticsTest/StaticsTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                        Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("02/FunctionCalls/StaticsTest/StaticsTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    }
                });
            }
        }
    }
}
