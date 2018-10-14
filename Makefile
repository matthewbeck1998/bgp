simple: parser.y scanner.l
	bison -d -v -o parser.c parser.y
	flex -o scanner.c scanner.l
	g++ -o simple parser.c scanner.c -lfl

clean:
	rm parser.c parser.h scanner.c simple
