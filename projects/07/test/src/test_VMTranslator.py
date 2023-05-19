import unittest
from os import sep, pathsep, remove
from os.path import exists, abspath
from subprocess import run
from conf import exe, res, tools

class VMTranslatorTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        global command
        tools_path =abspath(tools)
        command = F"\"{tools_path}/bin/classes;{tools_path}/bin/lib/Hack.jar;{tools_path}/bin/lib/HackGUI.jar;{tools_path}/bin/lib/Simulators.jar;{tools_path}/bin/lib/SimulatorsGUI.jar;{tools_path}/bin/lib/Compilers.jar\"".replace(';', pathsep).replace('/', sep)
    def test_stack_arithmetic(self):
        if not exists(exe):
            self.fail("The VMTranslator executable was not built")
        for name in ("SimpleAdd", "StackTest"):
            with self.subTest(name = name):
                exe_exit_code = run(F"{exe} \"{res}/StackArithmetic/{name}/{name}.vm\"".replace("/", sep), capture_output=True)
                self.assertEqual(exe_exit_code.returncode, 0)
                test_exit_code = run(F"java -classpath {command} CPUEmulatorMain {res}/StackArithmetic/{name}.tst".replace("/", sep), capture_output=True, check=False)
                self.assertEqual(test_exit_code.returncode, 0)
                if exists(F"{res}/StackArithmetic/{name}/{name}.asm"):
                    remove(F"{res}/StackArithmetic/{name}/{name}.asm")
                if exists(F"{res}/StackArithmetic/{name}/{name}.out"):
                    remove(F"{res}/StackArithmetic/{name}/{name}.out")
    def test_memory_access(self):
        if not exists(exe):
            self.fail("The VMTranslator executable was not built")
        for name in ("BasicTest", "PointerTest", "StaticTest"):
            with self.subTest(name = name):
                exe_exis_code = run(F"{exe} \"{res}/MemoryAccess/{name}/{name}.vm\"".replace("/", sep), capture_output=True)
                self.assertEqual(exe_exis_code.returncode, 0)
                test_exis_code = run(F"java -classpath {command} CPUEmulatorMain {res}/MemoryAccess/{name}.tst".replace("/", sep), capture_output=True, check=False)
                self.assertEqual(test_exis_code.returncode, 0)
                if exists(F"{res}/MemoryAccess/{name}/{name}.asm"):
                    remove(F"{res}/MemoryAccess/{name}/{name}.asm")
                if exists(F"{res}/MemoryAccess/{name}/{name}.out"):
                    remove(F"{res}/MemoryAccess/{name}/{name}.out")