import unittest
from os import pathsep, remove
from os.path import exists, abspath
from subprocess import run

class VMTranslatorTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        global command
        tools_path =abspath(tools)
        command = F"\"{tools_path}/bin/classes{pathsep}{tools_path}/bin/lib/Hack.jar{pathsep}{tools_path}/bin/lib/HackGUI.jar{pathsep}{tools_path}/bin/lib/Simulators.jar{pathsep}{tools_path}/bin/lib/SimulatorsGUI.jar{pathsep}{tools_path}/bin/lib/Compilers.jar\""
    def test_stack_arithmetic(self):
        if not exists(F"{exe}/VMTranslator_without_bootstrap{ext}"):
            self.fail("The VMTranslator_without_bootstrap executable was not built")
        for name in ("BasicLoop", "FibonacciSeries"):
            with self.subTest(name = name):
                exe_exis_code = run(F"{exe}/VMTranslator_without_bootstrap{ext} \"{res}/ProgramFlow/{name}/{name}.vm\"", capture_output=True, check=False)
                self.assertEqual(exe_exis_code.returncode, 0)
                test_exis_code = run(F"java -classpath {command} CPUEmulatorMain {res}/ProgramFlow/{name}/{name}.tst", capture_output=True, check=False)
                self.assertEqual(test_exis_code.returncode, 0)
                if exists(F"{res}/ProgramFlow/{name}/{name}.asm"):
                    remove(F"{res}/ProgramFlow/{name}/{name}.asm")
                if exists(F"{res}/ProgramFlow/{name}/{name}.out"):
                    remove(F"{res}/ProgramFlow/{name}/{name}.out")
    def test_memory_access_SimpleFunction(self):
        if not exists(F"{exe}/VMTranslator_without_bootstrap{ext}"):
            self.fail("The VMTranslator_without_bootstrap executable was not built")
        exe_exis_code = run(F"{exe}/VMTranslator_without_bootstrap{ext} \"{res}/FunctionCalls/SimpleFunction/SimpleFunction.vm\"", capture_output=True, check=False)
        self.assertEqual(exe_exis_code.returncode, 0)
        test_exis_code = run(F"java -classpath {command} CPUEmulatorMain {res}/FunctionCalls/SimpleFunction/SimpleFunction.tst", capture_output=True, check=False)
        self.assertEqual(test_exis_code.returncode, 0)
        if exists(F"{res}/FunctionCalls/SimpleFunction/SimpleFunction.asm"):
            remove(F"{res}/FunctionCalls/SimpleFunction/SimpleFunction.asm")
        if exists(F"{res}/FunctionCalls/SimpleFunction/SimpleFunction.out"):
            remove(F"{res}/FunctionCalls/SimpleFunction/SimpleFunction.out")
    def test_memory_access(self):
        if not exists(F"{exe}/VMTranslator{ext}"):
            self.fail("The VMTranslator executable was not built")
        for name in ("NestedCall", "StaticsTest", "FibonacciElement"):
            with self.subTest(name = name):
                exe_exis_code = run(F"{exe}/VMTranslator{ext} \"{res}/FunctionCalls/{name}\"", capture_output=True, check=False)
                self.assertEqual(exe_exis_code.returncode, 0)
                test_exis_code = run(F"java -classpath {command} CPUEmulatorMain {res}/FunctionCalls/{name}/{name}.tst", capture_output=True, check=False)
                self.assertEqual(test_exis_code.returncode, 0)
                if exists(F"{res}/FunctionCalls/{name}/{name}.asm"):
                    remove(F"{res}/FunctionCalls/{name}/{name}.asm")
                if exists(F"{res}/FunctionCalls/{name}/{name}.out"):
                    remove(F"{res}/FunctionCalls/{name}/{name}.out")
