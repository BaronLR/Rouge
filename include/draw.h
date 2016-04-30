#ifndef __FALKNERM__DRAW__
#define __FALKNERM__DRAW__
#include <parse.h>

void drawRooms(Room * rooms);

void runtime(int x, int y, int bottomY, Enemy * monster);

int checkInput(char input, Player * Hero, Enemy * monster);

void movePlayer(char input, Player * Hero, int type);

char ** createRoom(int roomY, int roomX, Room * rooms, int index);

void isScreenBigEnough(int screenX, int screenY, Room * rooms);

Enemy initEnemy(int y, int x, int hp, int attack, int speed, char type);

void printStatus(Player Hero, int bottomY);

void notify(char * message);

void endGame(Player Hero);

int addGold(int size);

#endif
