"""This module is for testing the first set of the Hack machine hardware component"""
from os import remove, chdir, pathsep
from os.path import abspath
from subprocess import run
import unittest

class TestHardwareComponents(unittest.TestCase):
    """Class for testing the first set of the Hack machine hardware component"""
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
        """This method tests Not, And, Or,  Xor,  Mux, DMux, Not16, And16, Or16, Mux16,
            Or8Way, Mux4Way16, Mux8Way16, DMux4Way, DMux8Way"""
        for component in ("Not", "And", "Or", "Xor", "Mux", "DMux", "Not16", "And16",
                            "Or16", "Mux16", "Or8Way", "Mux4Way16", "Mux8Way16", "DMux4Way", "DMux8Way"):
            with self.subTest(component=component):
                test = abspath(F"{test_path}/{component}/{component}.tst")
                exit_code = run(args = ["javaw", "-cp", class_path, "HardwareSimulatorMain", test],
                                            check=True, capture_output=True).returncode
                self.assertEqual(0, exit_code)
                if exit_code == 0:
                    remove(abspath(F"{test_path}/{component}/{component}.out"))
