import unittest
from os import sep, remove
from os.path import abspath, exists
from subprocess import Popen
from filecmp import cmp, clear_cache
from difflib import unified_diff
from args import exe

class HackAssemblerTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        global res
        res = abspath("../res/HackAssembler")
    def test_hack(self):
        for name in ("Add", "Max", "MaxL", "RectL", "PongL", "Max", "Rect", "Pong"):
            with self.subTest(name = name):
                process = Popen(F"{exe} \"{res}/{name}/{name}.asm\"".replace("/", sep))
                process.wait()
                exsit_code = process.returncode
                self.assertEqual(exsit_code, 0)
                self.assertTrue(cmp(F"{res}/{name}/{name}.hack", F"{res}/{name}/{name}Test.hack"))
                if(exists(F"{res}/{name}/{name}.hack")):
                    remove(F"{res}/{name}/{name}.hack")
