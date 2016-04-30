#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h" 
#include "draw.h" 
#define SIZE 256


int main(int argc, char * argv[])
{
    char drawFilename[SIZE];
    Room * rooms = malloc(sizeof(Room) * 5);

    if (argv[1] == NULL)
    {
	    puts("input filename as flag on launch!");
	    exit(1);
	}
    strcpy(drawFilename, argv[1]);
    rooms = parseDrawFile(drawFilename);
    drawRooms(rooms);
    
    free(rooms);

    return 0;
}
