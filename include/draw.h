#ifndef __FALKNERM__DRAW__
#define __FALKNERM__DRAW__
#include <parse.h>


/**
 * drawRooms
 * takes in the rooms from main and starts the game
 * IN:All the rooms
 * OUT: 
 * POST: passes to runtime for game loop
 * ERROR:
 */
void drawRooms(Room * rooms);

/**
 * runtime
 * passes all the data nessessary to run the game, and starts game loop
 * IN: player X and Y on the screen, the bottom Y and the monsters array
 * OUT: END GAME
 * POST:
 * ERROR: If the data is bad, it will likely seg fault
 */
void runtime(int x, int y, int bottomY, Enemy * monster);

/**
 * checkInput
 * passes in users last keystroke, runs accordingly
 * IN:Users keystroke, Pointers to hero and Enemies Data PBR
 * OUT: the condition of what is about to happen based on keystroke
 * POST:
 * ERROR: doesn't sanitize input, idk what could happen
 */
int checkInput(char input, Player * Hero, Enemy * monster);

/**
 * movePlayer
 * moves the player on the screen based on situation of move
 * IN: keystroke, the hero pointer, the situation of movement
 * OUT: N/A
 * POST:
 * ERROR: If the user kills the enemy it seems to skip a place (This doesn't break the game), unfixable under current circumstances 
 */
void movePlayer(char input, Player * Hero, int type);

/**
 * createRoom
 * creates the room arrays based on all the info
 * IN: The Rooms Data, 
 * OUT: A 2d array, pointers referencing data of inited room to be printed
 * POST:
 * ERROR: Bad input is a bitch
 */
char ** createRoom(int roomY, int roomX, Room * rooms, int index);

/**
 * isScreenBigEnough
 * checks to see if the screen is big enough to handle the game
 * IN:The screen size and it artifically prints the rooms to nothing to see how much room it will take up
 * OUT: nothing, if the screen fits, continues. else, quits game tells user
 * POST:
 * ERROR: FUCK NCURSES
 */
void isScreenBigEnough(int screenX, int screenY, Room * rooms);

/**
 * initEnemy
 * creates 1 enemy with the inputed data
 * IN: all the data nessessary to have a working monster
 * OUT: 1 init'd monster to be added to overall array! 
 * POST:
 * ERROR: N/A (I think) 
 */
Enemy initEnemy(int y, int x, int hp, int attack, int speed, char type);

/**
 * printStatus
 * Takes in the players data, and prints it to the bottom of the screen
 * IN: The players data, the bottoms Y corr to know where to print.
 * OUT: N/A
 * POST:
 * ERROR:
 */
void printStatus(Player Hero, int bottomY);

/**
 * notify
 * takes in a preformatted string and prints it to the top  
 * IN:the formatted string
 * OUT:N/A
 * POST: Clears top line when this is called
 * ERROR:
 */
void notify(char * message);


/**
 * endGame
 * when called it ends the game and prints the users data to the command line
 * IN: heros data
 * OUT:N/A
 * POST: This ends the game!
 * ERROR:
 */
void endGame(Player Hero);

/**
 * addGold
 * when called it randomly generates gold based on the type, small or large
 * IN: int, 0 or 1. If 0 it's small gold if 1 it's large gold
 * OUT: the randomly generated gold
 * POST:
 * ERROR: Random generation is hit and miss idk why
 */
int addGold(int size);

#endif
