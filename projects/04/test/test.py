"""This module is for testing the Hack machine hardware component"""
from os import remove, chdir, pathsep, listdir, environ
from os.path import join
from subprocess import run
import unittest

class TestHardwareComponents(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        chdir(environ['software_suite_path'])

    def test_hardware_component(self):
        for component in listdir(environ['test_resources_path']):
            with self.subTest(component=component):
                exit_code = run(args = ["java", "-cp", environ['software_suite_path'] + pathsep + join(environ['software_suite_path'], "bin/lib/*") + pathsep + join(environ['software_suite_path'], "bin/classes"), "HardwareSimulatorMain", F"{environ['test_resources_path']}/{component}/{component}.tst"], check=True, capture_output=True).returncode
                self.assertEqual(0, exit_code)
