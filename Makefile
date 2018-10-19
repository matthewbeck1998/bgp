bgp: parser.y scanner.l
	bison -d -o parser.c parser.y
	flex -o scanner.c scanner.l
	g++ -std=c++11 -o bgp parser.c scanner.c symbolTable.cpp node.cpp -lfl

clean:
	rm parser.c parser.h scanner.c bgp
