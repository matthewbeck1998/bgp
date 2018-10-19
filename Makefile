bgp: parser.y scanner.l
	bison -d -v -o parser.c parser.y
	flex -o scanner.c scanner.l
	g++ -o bgp parser.c scanner.c -lfl

clean:
	rm parser.c parser.h scanner.c bgp
