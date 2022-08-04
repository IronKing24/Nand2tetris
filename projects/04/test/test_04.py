import os
import subprocess
import unittest

class Test01HardwareComponents(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        global args

        os.chdir("../../tools")
        print(os.getcwd())
        classPath = os.getenv("CLASSPATH")
        args = ("java -cp \"%s.:bin/classes:bin/lib/Hack.jar:bin/lib/HackGUI.jar:bin/lib/Simulators.jar:bin/lib/SimulatorsGUI.jar:bin/lib/Compilers.jar\" CPUEmulatorMain " % ("" if classPath == None else classPath + ':')).replace(":", os.pathsep)
    
    def test_mult(self):
        global args
        
        exitCode = subprocess.run(args = args + "\"../projects/04/src/mult/Mult.tst\"", check=True, stdout=subprocess.PIPE).returncode
        self.assertEqual(0, exitCode)
        if exitCode == 0:
            os.remove("../projects/04/src/mult/Mult.out")    
    
    def test_Fill(self):
        global args

        exitCode = subprocess.run(args = args + "\"../projects/04/src/fill/FillAutomatic.tst\"", check=True, stdout=subprocess.PIPE).returncode
        self.assertEqual(0, exitCode)
        if exitCode == 0:
            os.remove("../projects/04/src/fill/FillAutomatic.out")