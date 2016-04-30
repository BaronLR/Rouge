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

Room * parseDrawFile(char *filename);

Room * initRoom(char * line, int length, int j);

#endif
