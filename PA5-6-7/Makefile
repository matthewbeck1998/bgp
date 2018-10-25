bin/bgp: src/parser.y src/scanner.l
	bison -d -v -o src/parser.c src/parser.y
	flex -o src/scanner.c src/scanner.l
	g++ -o bin/bgp -std=gnu++11 src/parser.c src/scanner.c src/node.cpp src/symbolTable.cpp -lfl

clean:
	rm src/parser.c src/parser.h src/scanner.c output/SymbolTableDump.txt output/LexDebugOutput.txt bin/bgp
