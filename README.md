# BGP Compiler

## Running PA9
**If your name is Chris Koh or Derek Stratton, you are required to read these instructions twice.**\
**This is due to the fact that both of you are blind.**\
**Linux**
1. Make sure you are in the bgp directory.
2. Compile the code with ```make -C src```.
3. Run the program using ```./bin/bgp inputFileName``` where inputFileName is the name of the input file. There are optional command line arguments "-o", "-d", "-s", "-l", and "-p". "-o" must be followed by an output filename.
4. Get the image of the Abstract Syntax Tree by using ```make graph -C src```.

Example:\
Your desired input file: ```input/forLoop.c```\
Your desired output file: ```output/forLoop.dat```\
Your desired flags: ```-d -p -o```\
Command: ```./bin/bgp input/forLoop.c -d -p -o output/forLoop.dat```\
Graph: ```make graph -C src```\
You can find the AST visualization in ```output/ASTree.png```.

**Windows**
1. Make sure you are in the bgp directory.
2. Compile the code with ```make -C src```.
3. Run the program using ```bin\bgp.exe input/inputFileName``` where inputFileName is the name of the input file. There are optional command line arguments "-o", "-d", "-s", "-l", and "-p". "-o" must be followed by an output filename.
4. Get the image of the Abstract Syntax Tree by using ```make graph -C src```.

Example:\
Your desired input file: ```input/forLoop.c```\
Your desired output file: ```output/forLoop.dat```\
Your desired flags: ```-d -p -o```\
Command: ```bin\bgp.exe input/forLoop.c -d -p -o output/forLoop.dat```\
Graph: ```make graph -C src```\
You can find the AST visualization in ```output/ASTree.png```.

More detailed documentation can be found in the [wiki](https://github.com/Price775/CS460-Beck-Garner-Poston/wiki).
