../bin/bgp: parser.y scanner.l
	bison -d -v -o parser.c parser.y
	flex -o scanner.c scanner.l
	g++ -o ../bin/bgp -std=gnu++11 parser.c scanner.c SymbolNode.cpp SymbolTable.cpp AST.cpp -lfl

clean:
	rm parser.c parser.h parser.output scanner.c ../bin/bgp
