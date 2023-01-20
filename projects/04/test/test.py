"""This module is for testing the fourth set of the Hack machine hardware component"""
from os import remove, chdir, pathsep
from os.path import abspath
from subprocess import run, Popen
import unittest

test_path = ""
class_path = ""

class TestHardwareComponents(unittest.TestCase):
    """Class for testing asm files"""
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
    def test_mult(self):
        """tests asm responsible for multiplying two values"""
        exit_code = run(args = ["javaw", "-cp", class_path, "CPUEmulatorMain",
                                    abspath(F"{test_path}/Mult/Mult.tst")],
                                    check=True, capture_output=True).returncode
        self.assertEqual(0, exit_code)
        if exit_code == 0:
            remove(F"{test_path}/mult/Mult.out")
    def test_auto_fill(self):
        """tests asm responsible for turnning the screen black"""
        exit_code = run(args = ["javaw", "-cp", class_path, "CPUEmulatorMain",
                                    abspath(F"{test_path}/Fill/FillAutomatic.tst")],
                                    check=True, capture_output=True).returncode
        self.assertEqual(0, exit_code)
        if exit_code == 0:
            remove(F"{test_path}/fill/FillAutomatic.out")
    def test_man_fill(self):
        """tests asm responsible for turnning the screen black manually"""
        print("""
        Load in Fill.asm into the simulator then click bottons on the keyboard to check for functionality.
        Make sure that 'No Animation' is selected. Then, select the keyboard, press any key for some time, and inspect the screen
        """)
        process = Popen(args = ["java", "-cp", class_path, "CPUEmulatorMain"])
        process.wait()
        self.assertEqual(0, process.returncode)
