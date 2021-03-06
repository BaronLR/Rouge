CFLAGS = -std=c99 -Wall
EXE = rouge 

all: $(EXE)

$(EXE): main.o parse.o draw.o 
	gcc main.o parse.o draw.o -lncurses -o ./$(EXE)
	
main.o: ./src/main.c
	gcc -c $(CFLAGS) ./src/main.c -Iinclude 
parse.o: ./src/parse.c
	gcc -c $(CFLAGS) ./src/parse.c -Iinclude
draw.o: ./src/draw.c
	gcc -c $(CFLAGS) ./src/draw.c -Iinclude 
clean:
	rm *.o && rm rouge
