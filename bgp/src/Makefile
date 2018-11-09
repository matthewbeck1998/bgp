CXX = g++
CXXFLAGS = -std=gnu++11

../bin/bgp: ../obj/parser.o ../obj/scanner.o ../obj/SymbolTable.o ../obj/SymbolNode.o ../obj/AST.o ../obj/ASTNode.o
	$(CXX) $(CXXFLAGS) -o ../bin/bgp ../obj/parser.o ../obj/scanner.o ../obj/SymbolTable.o ../obj/SymbolNode.o ../obj/AST.o ../obj/ASTNode.o

../obj/parser.o: parser.y
	bison -d -o parser.c parser.y
	$(CXX) $(CXXFLAGS) -o ../obj/parser.o -c parser.c

../obj/scanner.o: scanner.l
	flex -o scanner.c scanner.l
	$(CXX) $(CXXFLAGS) -o ../obj/scanner.o -lfl -c scanner.c

../obj/SymbolTable.o: SymbolTable.cpp SymbolTable.h
	$(CXX) $(CXXFLAGS) -o ../obj/SymbolTable.o -c SymbolTable.cpp

../obj/SymbolNode.o: SymbolNode.cpp SymbolNode.h
	$(CXX) $(CXXFLAGS) -o ../obj/SymbolNode.o -c SymbolNode.cpp

../obj/AST.o: AST.cpp AST.h
	$(CXX) $(CXXFLAGS) -o ../obj/AST.o -c AST.cpp

../obj/ASTNode.o: ASTNode.cpp ASTNode.h
	$(CXX) $(CXXFLAGS) -o ../obj/ASTNode.o -c ASTNode.cpp

graph:
	dot -Tpng ../output/treeOut.dot -o ../output/ASTree.png

clean:
	rm parser.c parser.h scanner.c ../obj/*.o ../bin/bgp
