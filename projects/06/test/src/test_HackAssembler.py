import unittest
from os import environ, listdir
from os.path import join, sep
from subprocess import run
from filecmp import cmp

class HackAssemblerTest(unittest.TestCase):
    def test_without_symbols(self):
        for dir_name in listdir(environ['test_resources_path']):
            for name in listdir(join(environ['test_resources_path'],dir_name)):
                with self.subTest(name = f"{dir_name}.{name}"):
                    self.assertEqual(run(args = [environ['assembler_executable_path'], F"{environ['test_resources_path']}{sep}{dir_name}{sep}{name}{sep}{name}.asm"], check=True, capture_output=True).returncode, 0)
                    self.assertTrue(cmp(F"{environ['test_resources_path']}{sep}{dir_name}{sep}{name}{sep}{name}.hack",F"{environ['test_resources_path']}{sep}{dir_name}{sep}{name}{sep}{name}Test.hack"))