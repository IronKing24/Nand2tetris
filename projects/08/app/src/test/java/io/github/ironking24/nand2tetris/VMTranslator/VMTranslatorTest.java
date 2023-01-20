package io.github.ironking24.nand2tetris.VMTranslator;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;

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
    @Deprecated
    @DisplayName("Program flow")
    class ProgramFlow{
        @Test
        @Deprecated
        @DisplayName("Basic loop")
        void basicLoop(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/ProgramFlow/BasicLoop/BasicLoop.vm").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/ProgramFlow/BasicLoop/BasicLoop.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/ProgramFlow/BasicLoop/BasicLoop.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/ProgramFlow/BasicLoop/BasicLoop.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }

        @Test
        @Deprecated
        @DisplayName("Fibonacci series")
        void fibonacciSeries(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/ProgramFlow/FibonacciSeries/FibonacciSeries.vm").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/ProgramFlow/FibonacciSeries/FibonacciSeries.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/ProgramFlow/FibonacciSeries/FibonacciSeries.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/ProgramFlow/FibonacciSeries/FibonacciSeries.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }
    }

    @Nested
    @DisplayName("Function calls")
    class FunctionCalls{
        @Test
        @Deprecated
        @DisplayName("Simple function")
        void simpleFunction(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/FunctionCalls/SimpleFunction/SimpleFunction.vm").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/FunctionCalls/SimpleFunction/SimpleFunction.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/FunctionCalls/SimpleFunction/SimpleFunction.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/FunctionCalls/SimpleFunction/SimpleFunction.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }

        @Test
        @DisplayName("Nested call")
        void nestedCall(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/FunctionCalls/NestedCall").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/FunctionCalls/NestedCall/NestedCall.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/FunctionCalls/NestedCall/NestedCall.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/FunctionCalls/NestedCall/NestedCall.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }

        @Test
        @DisplayName("Fibonacci element")
        void fibonacciElement(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/FunctionCalls/FibonacciElement").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/FunctionCalls/FibonacciElement/FibonacciElement.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, existCode);
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/FunctionCalls/FibonacciElement/FibonacciElement.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/FunctionCalls/FibonacciElement/FibonacciElement.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }

        @Test
        @DisplayName("Statics test")
        void staticsTest(){
            assertDoesNotThrow(()->{
                VMTranslator.main(new String[]{ClassLoader.getSystemResource("tests/FunctionCalls/StaticsTest").getPath().replace("%20", " ").substring(1)});
                ProcessBuilder CPUEmulator = new ProcessBuilder("java", "-classpath",  "\"" + classPath + "\"", "CPUEmulatorMain", ClassLoader.getSystemResource("tests/FunctionCalls/StaticsTest/StaticsTest.tst").getPath().replace("%20", " ").replace("/", File.separator).substring(1));
                Process process = CPUEmulator.inheritIO().start();
                int existCode = process.waitFor();
                assertEquals(0, process.waitFor());
                if(existCode == 0){
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/FunctionCalls/StaticsTest/StaticsTest.asm").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                    Files.deleteIfExists(Paths.get(ClassLoader.getSystemResource("tests/FunctionCalls/StaticsTest/StaticsTest.out").getPath().replace("%20", " ").replace("/", File.separator).substring(1)));
                }
            });
        }
    }
}
