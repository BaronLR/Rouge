#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#define MAX_ROOMS 5

Room * parseDrawFile(char *filename)
{
    FILE * drawStream;
    char line[256];
    
    int j = 0;

    drawStream = fopen(filename, "r");
    if (drawStream == NULL)
    {
	    puts("error opening file");
        exit(1);
	}
    Room * rooms = malloc(sizeof(Room) * 5);

    while (fgets(line, 256, drawStream) != NULL)
    {
    	int currLength = 0;
        currLength = strlen(line);
	    line[currLength - 1] = '\0';
		rooms[j] = *initRoom(line, currLength, j);
		j++;
	}

    fclose(drawStream);
    return rooms;
}

Room * initRoom(char * line, int length, int index)
{
    int numItems = 0;
    int numDoors = 0;
    Room * tmpRoom;

    tmpRoom = malloc(sizeof(Room));
    if (tmpRoom == NULL)
    {
        puts("Room memory on the heap.");
	}

    char * tmpRows = malloc(sizeof(char) * 2);
    memset(tmpRows, '\0', 2);
    char * tmpColumns = malloc(sizeof(char) * 2);
    memset(tmpColumns, '\0', 2);
    char * tmpDoorNumber = malloc(sizeof(char) * 2);
    memset(tmpDoorNumber, '\0', 2);
    char * tmpX = malloc(sizeof(char) * 2);
    memset(tmpX,'\0', 2);
    char * tmpY = malloc(sizeof(char) * 2);
    memset(tmpY, '\0', 2);

     for (int i = 0; i < length; i++)
	 {
	     if (line[i] == 'X')
	     {
		     if ((i - 2) == 0)
		     {
	             if (isdigit(line[i - 2]) && isdigit(line[i - 1]))
				 {
					  tmpRows[0] = line[i - 2];
					  tmpRows[1] = line[i - 1];
			     }
				 else
				 {
					  puts("Your rows data is not integer convertable! Quitting...");
					  exit(1);
	             }
			 }
			 else
			 {
			     if (isdigit(line[i - 1]))
				 {
			         tmpRows[0] = line[i - 1];
					 tmpRows[1] = '\0';
				 }
				 else
				 {
					 puts("Your rows data is not integer convertable! Quitting...");
				     exit(1);
			     }
			  }
			  //15X9
			  if (isdigit(line[i + 1]))
			  {
			      if (isdigit(line[i + 1]) && isdigit(line[i + 2]))
				  {
				      tmpColumns[0] = line[i + 1];
					  tmpColumns[1] = line[i + 2];
				  }
				  else
				  {
				      tmpColumns[0] = line[i + 1];
					  tmpColumns[1] = '\0';
				  }
			  }

				//Setting the Rooms size to the struct.
				tmpRoom->columns = atoi(tmpRows);
				tmpRoom->rows = atoi(tmpColumns);
				continue;
			  }
			  else if(line[i] == 'd')
			  {

			      if (isalpha(line[i + 1]))
				  {
				      tmpRoom->doors[numDoors].bearing = line[i + 1];
				  }
				  if (isdigit(line[i + 3])) //two digits
				  {
				      tmpDoorNumber[0] = line[i + 2];
					  tmpDoorNumber[1] = line[i + 3];
				  }
				  else
				  {
				      tmpDoorNumber[0] = line[i + 2];
					  tmpDoorNumber[1] = '\0';
				  }
				  tmpRoom->doors[numDoors].offset = atoi(tmpDoorNumber);
				  numDoors++;
				  continue;
			  }
			  else if(isalpha(line[i]) != 0 && line[i - 1] != 'd' && line[i] != 'd')
			  {

				      if (line[i + 2] == ',') //1 number
					  {
					      tmpX[0] = line[i + 1];
						  tmpX[1] = '\0';
					      if (isdigit(line[i + 4]))//two digits
						  {
						      tmpY[0] = line[i + 3];
							  tmpY[1] = line[i + 4];
						  }
						  else if(isdigit(line[i + 3]))
						  {
						      tmpY[0] = line[i + 3];
							  tmpY[1] = '\0';
						  }
					  }
					  else if (line[i + 3] == ',') //two numbers p12,12
					  {
					      tmpX[0] = line[i + 1];
						  tmpX[1] = line[i + 2];
						  if (isdigit(line[i + 5]))
						  {
						      tmpY[0] = line[i + 4];
							  tmpY[1] = line[i + 5];
						  }
						  else if(isdigit(line[i +4]))
						  {
						      tmpY[0] = line[i + 4];
							  tmpY[1] = '\0';
						  }
					   }
					   tmpRoom->contents[numItems].type = line[i];
					   tmpRoom->contents[numItems].y = atoi(tmpX);
					   tmpRoom->contents[numItems].x = atoi(tmpY);

			           numItems++;
				       continue;
		     }
    }

    tmpRoom->totalItems = numItems;
    free(tmpX);
    free(tmpY);
    free(tmpRows);
    free(tmpColumns);
    free(tmpDoorNumber);
    return tmpRoom;
}
