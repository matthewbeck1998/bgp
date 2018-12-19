import sys
import subprocess

arg = sys.argv[1]
cfile = "cfiles/" + arg + ".c"
tacfile = "3acfiles/" + arg + ".3ac"
asmfile = "asmfiles/" + arg + ".asm"
subprocess.call(["bin/bgp", cfile, tacfile])
subprocess.call(["py", "-3", "src/shibboleth.py", tacfile, asmfile])
