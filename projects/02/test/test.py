"""This module is for testing the second set of the Hack machine hardware component"""
from os import remove, chdir, pathsep
from os.path import abspath
from subprocess import run
import unittest

class TestHardwareComponents(unittest.TestCase):
    """Class for testing the second set of the Hack machine hardware component"""
    @classmethod
    def setUpClass(cls):
        global test_path
        global class_path

        test_path =  abspath("../src")
        chdir(abspath("../../../tools"))
        class_path = "bin/classes"                + pathsep
        class_path += "bin/lib/Hack.jar"          + pathsep
        class_path += "bin/lib/HackGUI.jar"       + pathsep
        class_path += "bin/lib/Simulators.jar"    + pathsep
        class_path += "bin/lib/SimulatorsGUI.jar" + pathsep
        class_path += "bin/lib/Compilers.jar"     + pathsep
    def test_hardware_component(self):
        """This method test HalfAdder, FullAdder, Add16, Inc16, ALU-nostat, ALU"""
        for component in ("HalfAdder", "FullAdder", "Add16", "Inc16", "ALU-nostat", "ALU"):
            with self.subTest(component=component):
                folder = component if component != "ALU-nostat" else "ALU"
                test = abspath(F"{test_path}/{folder}/{component}.tst")
                exit_code = run(args = ["javaw", "-cp", class_path, "HardwareSimulatorMain", test],
                                            check=True, capture_output=True).returncode
                self.assertEqual(0, exit_code)
                if exit_code == 0:
                    remove(abspath(F"{test_path}/{folder}/{component}.out"))
