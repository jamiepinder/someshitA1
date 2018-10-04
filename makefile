all: list parser
#creates libllist.a and libcparse.a in bin folder

list:
#create static library libllist.a in bin folder
	gcc -Wall -std=c11 -c src/LinkedListAPI.c -o src/LinkedListAPI.o
	ar rcs bin/libllist.a src/LinkedListAPI.o

parser:
	gcc -Wall -std=c11 -c src/VCardParser.c -o src/VCardParser.o
	ar rcs bin/libcparse.a src/VCardParser.o
#create static library libcparse.a in bin folder

clean:
#removes all .o and .a files
	rm src/*.o 