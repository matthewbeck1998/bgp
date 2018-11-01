CXX = g++
CXXFLAGS = -std=gnu++11

../bin/bgp: parser.o scanner.o SymbolTable.o SymbolNode.o AST.o ASTNode.o
	$(CXX) $(CXXFLAGS) -o ../bin/bgp parser.o scanner.o SymbolTable.o SymbolNode.o AST.o ASTNode.o

parser.o: parser.y
	bison -d -o parser.c parser.y
	$(CXX) $(CXXFLAGS) -c parser.c

scanner.o: scanner.l
	flex -o scanner.c scanner.l
	$(CXX) $(CXXFLAGS) -lfl -c scanner.c

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	$(CXX) $(CXXFLAGS) -c SymbolTable.cpp

SymbolNode.o: SymbolNode.cpp SymbolNode.h
	$(CXX) $(CXXFLAGS) -c SymbolNode.cpp

AST.o: AST.cpp AST.h
	$(CXX) $(CXXFLAGS) -c AST.cpp

ASTNode.o: ASTNode.cpp ASTNode.h
	$(CXX) $(CXXFLAGS) -c ASTNode.cpp

graph:
	dot -Tpng ..\output\treeOut.dot -o ..\output\ASTree.png

clean:
	rm parser.c parser.h scanner.c *.o ../bin/bgp
