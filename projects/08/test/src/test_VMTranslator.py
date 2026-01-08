import unittest
from os import environ, listdir, chdir
from os.path import sep, pathsep, join
from subprocess import run

class VMTranslatorTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        chdir(environ['test_suite_path'])
    def test_stack_arithmetic(self):
        for dir_name in listdir(environ['test_resources_path']):
            for name in listdir(join(environ['test_resources_path'],dir_name)):
                with self.subTest(name = f"{dir_name}.{name}"):
                    self.assertEqual(run(args=[environ['vm_executable_path'], F"{environ['test_resources_path']}{sep}{dir_name}{sep}{name}{sep}{name}.vm"], check=True, capture_output=True).returncode, 0)
                    self.assertEqual(run(args=["java", "-classpath", f"\"{environ['test_suite_path']}{pathsep}{environ['test_suite_path']}{sep}bin{sep}classes{pathsep}{environ['test_suite_path']}{sep}bin{sep}lib{sep}*\"", "CPUEmulatorMain", f"{environ['test_resources_path']}{sep}{dir_name}{sep}{name}{sep}{name}.tst"], capture_output=True, check=False).returncode, 0)