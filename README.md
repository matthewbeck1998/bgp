# CS460-Beck-Garner-Poston

## Running the compiler
1. Make sure you are in the bgp directory.
2. Compile the code with make -C src.
3. Run the program using "./bin/bgp inputFileName" where inputFileName is the name of the input file. There are optional command line arguments "-o", "-d", "-s", "-l", and "-p". "-o" must be followed by an output filename.

Example:\
Your desired input file: ```input/functions1.c```\
Your desired output file: ```output/functions1.dat```\
Your desired flags: ```-d -p -o```\
Command: ```./bin/bgp input/functions1.c -d -p -o output/functions1.dat```

More detailed documentation can be found in the [wiki](https://github.com/Price775/CS460-Beck-Garner-Poston/wiki).
