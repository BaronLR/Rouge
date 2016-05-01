#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * createLine();


int main(int argc, char * argv[]) //create level
{
	if (argc < 2)
	{
		puts("please input valid input next time...");
		return 0; 
	}

	FILE * stream = fopen(argv[1], "w");

	for (int i=0; i < 6; i++)
	{
		fprintf(stream, createLine());
	}

	return 0; 
}


char * createLine() 
{
	char * seedLine = malloc(sizeof(char) * 128);


	strcpy(seedLine, "12X12"); 

	strcat(seedLine, " M12,12");



	strcat(seedLine, "\n");
	return seedLine; 

}
