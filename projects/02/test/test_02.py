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
        args = ("java -cp \"%s.:bin/classes:bin/lib/Hack.jar:bin/lib/HackGUI.jar:bin/lib/Simulators.jar:bin/lib/SimulatorsGUI.jar:bin/lib/Compilers.jar\" HardwareSimulatorMain " % ("" if classPath == None else classPath + ':')).replace(":", os.pathsep)
    
    def test_component(self):
        global args
        print(args)
        for component in ("HalfAdder", "FullAdder", "Add16", "Inc16", "ALU-nostat", "ALU"):
            with self.subTest(component=component):
                exitCode = subprocess.run(args = args + ("\"../projects/02/src/{}/{}.tst\"".format(component if (component != "ALU-nostat") else "ALU", component)), check=True, stdout=subprocess.PIPE).returncode
                self.assertEqual(0, exitCode)
                if exitCode == 0:
                    os.remove("../projects/02/src/{}/{}.out".format(component if (component != "ALU-nostat") else "ALU", component))


