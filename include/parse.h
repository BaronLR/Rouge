#ifndef __FALKNERM__PARSE__
#define __FALKNERM__PARSE__

typedef struct Item {
	int x;
	int y;
	char type;
}Item;

typedef struct Door {
	char bearing;
	int offset;
	int x; 
	int y; 
	int onscreenX; 
	int onscreenY;

}Door;

typedef struct Room {
	int rows;
	int columns;
	int totalItems;
	Item contents[12];
	Door doors[4];

} Room;

typedef struct Player {
	int x;
	int y;
	int gold;
	int items;
	int potions; 
	int startRoom;
	int health; 
	int attack;
	char standingOn;
	char itemsType[5]; 
}Player;

typedef struct Enemy {
	int health;
	int attack;
	int speed;
	int x;
	int y;
	int type; 
	int cycle; 
	int dead; 
}Enemy;

/**
 * parseDrawFile
 * parses the file for the data and return inited rooms
 * IN: the filename of parsed file
 * OUT: returns all the rooms data to main
 * POST:
 * ERROR:
 */
Room * parseDrawFile(char *filename);

/**
 * initRoom
 * takes in a single line of the text file and returns 1 room
 * IN: the current line, its length and what room number it is  
 * OUT: 1 room
 * POST:
 * ERROR:
 */
Room * initRoom(char * line, int length, int j);

#endif
