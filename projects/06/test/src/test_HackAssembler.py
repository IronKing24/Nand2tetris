import unittest
from os import sep, remove
from os.path import exists
from subprocess import run
from filecmp import cmp
from conf import exe, res

class HackAssemblerTest(unittest.TestCase):
    def test_without_symbols(self):
        if not exists(exe):
            self.fail("The HackAssembler executable was not built")
        for name in ("Add", "MaxL", "RectL", "PongL"):
            with self.subTest(name = name):
                process = run(F"{exe} \"{res}/without symbols/{name}/{name}.asm\"".replace("/", sep))
                exit_code = process.returncode
                self.assertEqual(exit_code, 0)
                self.assertTrue(cmp(F"{res}/without symbols/{name}/{name}.hack", F"{res}/without symbols/{name}/{name}Test.hack"))
                if exists(F"{res}/without symbols/{name}/{name}.hack"):
                    remove(F"{res}/without symbols/{name}/{name}.hack")
    def test_with_symbols(self):
        if not exists(exe):
            self.fail("The HackAssembler executable was not built")
        for name in ("Max", "Rect", "Pong"):
            with self.subTest(name = name):
                process = run (F"{exe} \"{res}/with symbols/{name}/{name}.asm\"".replace("/", sep))
                exit_code = process.returncode
                self.assertEqual(exit_code, 0)
                self.assertTrue(cmp(F"{res}/with symbols/{name}/{name}.hack", F"{res}/with symbols/{name}/{name}Test.hack"))
                if exists(F"{res}/with symbols/{name}/{name}.hack"):
                    remove(F"{res}/with symbols/{name}/{name}.hack")
