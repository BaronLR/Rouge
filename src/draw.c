#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "draw.h"
#include "parse.h"
#define GREEN "\033[1m\033[32m"
#define RESET "\033[0m"
#define YOFF 4

/**
 * drawRooms
 * takes in the rooms from main and starts the game
 * IN:All the rooms
 * OUT: 
 * POST: passes to runtime for game loop
 * ERROR:
 */
void drawRooms(Room * rooms)
{
    char ** room1[6];
    int playerx,playery; 
    int xoffset = 0;
    int maxColumnsInTop = 0;
    int maxColumnsInBottom = 0;
    int finalKTop = 0;
    int finalKBottom = 0; 
    int srcX = 0;
    int srcY = 0;  
    Enemy * monster = malloc(sizeof(Enemy) * 20); 
    int * middleLinesX = malloc(sizeof(int) * 6);
    int enemyCount = 0; 
    int isPlayer = 0; 

	for (int i = 0; i < 6; i ++)
	{
		room1[i] = createRoom(rooms[i].columns + 2, rooms[i].rows + 2, rooms, i);
	}

	initscr();
	noecho();

	getmaxyx(stdscr,srcY, srcX);
	isScreenBigEnough(srcX, srcY, rooms);
	
    for (int z = 0; z < 6; z++)
    {
        if (z <= 2)
	    {
	        if (z == 0)
	        {
                xoffset = 4;
                maxColumnsInTop = rooms[z].columns + 1;
	        }
	        else
            {
	            xoffset += (rooms[z - 1].rows + 5);
		        if(rooms[z].columns > maxColumnsInTop)
				{
					maxColumnsInTop = rooms[z].columns + 1;
				}
			}
			for(int i=0;i<rooms[z].columns + 1;i++)
			{
			    for(int k=0;k<rooms[z].rows + 2;k++)
				{
				    if (room1[z][i][k] == '+')
				    {
					   for (int h = 0; h < 3; h++)
					    {
					    	if (rooms[z].doors[h].x == k)
					    	{
					    		if (rooms[z].doors[h].y == i)
					    		{
					    			rooms[z].doors[h].onscreenX = k + xoffset;
					    			rooms[z].doors[h].onscreenY = i + 4;
					    		}
					    	}
					    }
					}
					else if (room1[z][i][k] == '@')
					{
						if (isPlayer == 0)
						{
							playerx = k + xoffset;
							playery = i + YOFF;
							isPlayer = 1;
							mvaddch(i + YOFF, k + xoffset, '@');
							continue; 
						}
						else 
						{
							mvaddch(i + YOFF, k + xoffset, '.');
							continue; 
						}
					}
					else if (room1[z][i][k] == 'A') 
					{
						monster[enemyCount] = initEnemy(i + YOFF, k + xoffset, 5, 1, 2, 'A');
						enemyCount++; 
					}
					else if (room1[z][i][k] == 'B') 
					{
						monster[enemyCount] = initEnemy(i + YOFF, k + xoffset, 2, 5, 4, 'B');
						enemyCount++; 
					}
					else if (room1[z][i][k] == 'S') 
					{
						monster[enemyCount] = initEnemy(i + YOFF, k + xoffset, 5, 5, 4, 'S');
						enemyCount++; 
					}
					else if (room1[z][i][k] == 'Z') 
					{
						monster[enemyCount] = initEnemy(i + YOFF, k + xoffset, 15, 5, 2, 'Z');
						enemyCount++; 
					}
					else if (room1[z][i][k] == 'T')
					{
						monster[enemyCount] = initEnemy(i + YOFF, k + xoffset, 50, 5, 3, 'T');
						enemyCount++; 
					}
					mvaddch(i + YOFF, k + xoffset, room1[z][i] [k]);
					finalKTop = k + xoffset; 
					middleLinesX[z] = k + xoffset; 
				}
			}
	    }
	    else if (z > 2 && z < 6)
	    {
            if(z == 3)
	        {
	            xoffset = 3;
	            maxColumnsInBottom = rooms[z].columns;
	        }
            else if (z > 3)
            {
	            xoffset += (rooms[z - 1].rows  + 5);
	            if (rooms[z].columns > maxColumnsInBottom)
		        {
		            maxColumnsInBottom = rooms[z].columns;
		        }
	        }
		
			for(int i=0;i<rooms[z].columns + 1;i++)
			{
				for(int k=0;k<rooms[z].rows + 2;k++)
				{
					if (room1[z][i][k] == '+')
				    {
					    for (int h = 0; h < 3; h++)
					    {
					        if (rooms[z].doors[h].x == k)
					        {
						        if (rooms[z].doors[h].y == i)
						        {
							        rooms[z].doors[h].onscreenX = k + xoffset;
						            rooms[z].doors[h].onscreenY = i + (maxColumnsInTop + 7);
						        }
					        }
				        }
					}
				    else if (room1[z][i][k] == '@')
				    {
						if (isPlayer == 0)
						{
							playerx = k + xoffset;
							playery = i + (maxColumnsInTop + 5);
							isPlayer = 1;
							mvaddch(i + (maxColumnsInTop + 5), k + xoffset, '@');
							continue; 
						}
						else 
						{
							mvaddch(i + (maxColumnsInTop + 5), k + xoffset, '.');
							continue; 
						}
				    }
					else if (room1[z][i][k] == 'A') 
					{
						monster[enemyCount] = initEnemy(i + (maxColumnsInTop + 5) + 2, k + xoffset, 5, 1, 2, 'A');
						enemyCount++; 
					}
					else if (room1[z][i][k] == 'B') 
					{
						monster[enemyCount] = initEnemy(i + (maxColumnsInTop + 5) + 2, k + xoffset, 2, 5, 4, 'B');
						enemyCount++; 
					}
					else if (room1[z][i][k] == 'S') 
					{
						monster[enemyCount] = initEnemy(i + (maxColumnsInTop + 5) + 2, k + xoffset, 5, 5, 4, 'S');
						enemyCount++; 
					}
					else if (room1[z][i][k] == 'Z') 
					{
						monster[enemyCount] = initEnemy(i + (maxColumnsInTop + 5) + 2, k + xoffset, 15, 5, 2, 'Z');
						enemyCount++; 
					}
					else if (room1[z][i][k] == 'T')
					{
						monster[enemyCount] = initEnemy(i + (maxColumnsInTop + 5) + 2, k + xoffset, 50, 5, 3, 'T');
						enemyCount++; 
					}
					
				    mvaddch(i + (maxColumnsInTop + 5) + 2,  k + xoffset, room1[z][i] [k]);
					finalKBottom = k + xoffset;
					middleLinesX[z] = k + xoffset; 
				}
			}
		}
	}

	int finalK = 0;
	int printBottomYcorr = 0; 

	if (finalKBottom < finalKTop)
	{
		finalK = finalKTop + 4;
	}
	else
	{
		finalK = finalKBottom + 4; 
	}

	printBottomYcorr = maxColumnsInTop + maxColumnsInBottom + 7;
	 
	for (int i = 0; i < finalK; i ++)
	{
		if ( i < finalKTop + 3)
		{
			mvaddch(2, i, '#');
		}
		mvaddch(maxColumnsInTop + 5, i, '#');
		mvaddch(printBottomYcorr + 1, i, '#');
	}
	for (int i  = 2; i <= printBottomYcorr; i++)
	{
         mvaddch(i, 0, '#');
	}
	for (int i = 2; i < maxColumnsInTop + 5; i++)
	{	     
         mvaddch(i, finalKTop + 3, '#');
	}
	for (int i = maxColumnsInTop + 5; i < printBottomYcorr + 2; i++)
	{	
		 mvaddch(i, finalKBottom + 3, '#');
	}

	for (int i = 0; i < 6; i ++)
	{
		if (i < 2)
		{
			for (int k = 2; k < maxColumnsInTop + 5; k++)
			{
				mvaddch(k, middleLinesX[i] +2, '#');
			}

		}
		else if (i > 2 && i < 5)
		{
			for (int k = maxColumnsInTop + 5; k <= printBottomYcorr; k++)
			{
				mvaddch(k, middleLinesX[i] + 2, '#');
			}
		}

		for (int j = 0; j < 3; j++)
		{

			switch(rooms[i].doors[j].bearing)
			{
				case 'n':
					mvaddch(rooms[i].doors[j].onscreenY - 1,rooms[i].doors[j].onscreenX, '#');
					break;
				case 'e':
					mvaddch(rooms[i].doors[j].onscreenY ,rooms[i].doors[j].onscreenX  + 1, '#');
					mvaddch(rooms[i].doors[j].onscreenY ,rooms[i].doors[j].onscreenX  + 2, '#');
					break;

				case 'w': 
					mvaddch(rooms[i].doors[j].onscreenY,rooms[i].doors[j].onscreenX  - 1, '#');
					mvaddch(rooms[i].doors[j].onscreenY,rooms[i].doors[j].onscreenX  - 2, '#');
					break; 
				case 's':
					if (i < 3)
					{
						for (int k = rooms[i].doors[j].onscreenY + 1; k <= maxColumnsInTop + 5; k++)
						{
							mvaddch(k, rooms[i].doors[j].onscreenX, '#'); 
						}
					}
					else if(i > 2 && i < 6)
					{
						for (int k = rooms[i].doors[j].onscreenY + 1; k <= printBottomYcorr; k++)
						{
							mvaddch(k, rooms[i].doors[j].onscreenX, '#'); 
						}
					}
					break;
			}
		}
	}

	FILE * debugStream = fopen("./assests/debug.txt", "w");
	
	if (debugStream == NULL)
		exit(0);
	
	for (int z = 0; z < 6; z++)
	{
		
		fprintf(debugStream, "Room[%d] columns:%d, rows:%d\n",z, rooms[z].columns, rooms[z].rows); 
		
		for (int i = 0; i < 3; i++)
		{
			if(isalpha(rooms[z].doors[i].bearing))
				fprintf(debugStream, "room[%d]: d%c%d\n", z, rooms[z].doors[i].bearing, rooms[z].doors[i].offset);
		}
		for (int k = 0; k < 12; k++)
		{
			if (isalpha(rooms[z].contents[k].type))
				fprintf(debugStream, "room[%d]: item:'%c', x:'%d' y:'%d'\n", z, rooms[z].contents[k].type, rooms[z].contents[k].x, rooms[z].contents[k].y);
		}
	}

	fclose(debugStream);
	runtime(playerx, playery, printBottomYcorr, monster);

	free(monster);
	free(middleLinesX);
    return;
}

/**
 * runtime
 * passes all the data nessessary to run the game, and starts game loop
 * IN: player X and Y on the screen, the bottom Y and the monsters array
 * OUT: END GAME
 * POST:
 * ERROR: If the data is bad, it will likely seg fault
 */
void runtime(int x, int y, int bottomY, Enemy * monster)
{
	Player hero; 
	hero.health = 50;
	hero.attack = 5; 
	hero.gold = 0; 
	hero.items = 0; 
	hero.potions = 0;
	hero.standingOn = '.';
    hero.y = y;
    hero.x = x;
    char *s = malloc(sizeof(char) * 256);
    char input = '\0';
    int foundG = 0;

    hero.itemsType[0] = '\0';
    hero.itemsType[1] = '\0';
    hero.itemsType[2] = '\0';
    hero.itemsType[3] = '\0';
    hero.itemsType[4] = '\0';


    printStatus(hero, bottomY); 
    refresh();
 
    while(input != 'q')
    {
         refresh();
         input = getch();
         int condition = 0; 
         condition = checkInput(input, &hero, monster);

		 if(condition == 1) //.
		 {
		     movePlayer(input,&hero, 0);
         }
         else if (condition == 2)//#
         {
         	movePlayer(input, &hero, 0);
         }
		 else if (condition == 3)//+
		 {
		 	memset(s,'\0', 256);
		 	notify("You opened the door");
		 	movePlayer(input, &hero , 0);
		 }
		 else if (condition == 4) //small gold
		 {
		 	foundG = addGold(0);
		 	hero.gold += foundG;
		 	
		 	sprintf(s,"Picked up: (small gold) %dG, total: %dG", foundG, hero.gold);
		 	notify(s);
		    movePlayer(input, &hero, 1);
		 }
	     else if (condition == 5) //big gold
	     {
		     foundG = addGold(1);
		     hero.gold += foundG;
		     
		 	sprintf(s,"Picked up: (large gold) %dG , total: %dG", foundG, hero.gold);
		 	notify(s);

		     movePlayer(input, &hero, 1);
         }
	     else if (condition == 6) //common wepon ) 
	     {
	     	memset(s,'\0', 256);
	     	if (hero.items < 5)
	     	{
	     		sprintf(s,"Picked up: Common Weapon! item %d/5", hero.items + 1);
		 	    notify(s);
		 	    hero.itemsType[hero.items] = ')';
		 	    hero.items++; 
		 	    movePlayer(input, &hero, 1);
	     	}
	     	else
	     	{
	     		notify("Inventory full! 5/5");
	     	}
		    
 	     }
	     else if (condition == 7) //rare item ( 
	     {
	     	memset(s,'\0', 256);
	     	if (hero.items < 5)
	     	{
	     		sprintf(s,"Picked up: Rare Weapon! item %d/5", hero.items + 1);
		 		notify(s);
		 		hero.itemsType[hero.items] = '(';
		 		hero.items++;
		 		movePlayer(input, &hero, 1);
	     	}
	     	else
	     	{
		 		notify("Inventory full! 5/5");
		 	}
		    
	     }
		 else if (condition == 8) //Equipment ]
	     {
	     	memset(s,'\0', 256);
	     	if (hero.items < 5)
	     	{
		 		sprintf(s,"Picked up: Equipment! item %d/5", hero.items + 1);
		 		notify(s);
		 		hero.itemsType[hero.items] = ']';
		 		hero.items++;	
		 		movePlayer(input, &hero, 1);		
		 	}
		 	else 
		 	{
		 		notify("Inventory full! 5/5");
		 	}
		 }
		 else if (condition == 10) //stairs
	     {
		      endGame(hero);
		 }
		 else if(condition == 12)
		 {
	        sprintf(s,"Found: Potion! Now you have %d", hero.potions+1);
		    notify(s);
		    hero.potions++; 
		    movePlayer(input, &hero, 1);
		 }
		 if (input == 'p')
		 {
		     if (hero.potions != 0)
		 	 {
		 		memset(s, '\0', 256);
		 		if (hero.health == 50)
		 		{
		 			sprintf(s,"HP is FULL! Cannot use Potion!");
		 			notify(s);
		 		}
		 		else if (hero.health < 50)
		 		{
		 			sprintf(s,"Used: Potion! Now you have %d. HP is 50", hero.potions -1);
		 			notify(s);
		 			hero.health = 50;
		 			hero.potions --; 
		 	    }
		     }
		     else
		     {
		         sprintf(s,"You do not have any potions to use!");
		         notify(s);	
		     }	
     }
     printStatus(hero, bottomY); 

     int monsterX = 0; 
     int monsterY = 0; 

     for (int i = 0; i < 20; i ++)
 	 {
 	    if (monster[i].dead == 0)
 	 	{
		 		if (monster[i].type == 'T')
		 		{
		 			monsterX = monster[i].x;
		 			monsterY = monster[i].y; 

		 			switch(monster[i].cycle)
		 			{
		 				case 0:
		 					monsterX -= 1;
		 					break;
		 				case 1: 
		 					monsterY -= 1; 
		 					break;
		 				case 2:
		 					monsterX += 1; 
		 					break;
		 				case 3: 
		 					monsterY += 1; 
		 					break;
		 			}

		 			if (monster[i].cycle < 3)
		 			{
		 				monster[i].cycle++;
		 			}
		 			else 
		 			{
		 				monster[i].cycle = 0;
		 			}

		 			char next = mvinch(monsterY,monsterX) & A_CHARTEXT;

		 			if(next == '.')
		 			{
		 				mvaddch(monster[i].y, monster[i].x, '.');
		 				monster[i].y = monsterY;
		 				monster[i].x = monsterX; 
		 				mvaddch(monster[i].y, monster[i].x, 'T');
		 			}
					
		 		}
		 		else if (monster[i].type == 'Z')
		 		{
		 			monsterX = monster[i].x;
		 			monsterY = monster[i].y; 
		 			switch(monster[i].cycle)
		 			{
		 				case 0:
		 					monsterX -= 1;
		 					break;
		 				case 1: 
		 					monsterX += 1; 
		 					break;
		 			}
		 			if (monster[i].cycle < 2)
		 			{
		 				monster[i].cycle++;
		 			}
		 			else 
		 			{
		 				monster[i].cycle = 0;
		 			}
		 			char next = mvinch(monsterY,monsterX) & A_CHARTEXT;

		 			if(next == '.')
		 			{
		 				mvaddch(monster[i].y, monster[i].x, '.');
		 				monster[i].y = monsterY;
		 				monster[i].x = monsterX; 
		 				mvaddch(monster[i].y, monster[i].x, 'Z');
		 			}
		 		}
		 		else if(monster[i].type == 'S')
		 		{
		 			monsterX = monster[i].x;
		 			monsterY = monster[i].y; 
		 			switch(monster[i].cycle)
		 			{
		 				case 0: 
		 					monsterY += 1;
		 					break;
		 				case 1: 
		 					monsterY += 1; 
		 					break;
		 				case 2:
		 					monsterY -= 1; 
		 					break;
		 				case 3: 
		 					monsterY -= 1; 
		 					break; 
		 			}

		 			if (monster[i].cycle < 3)
		 	   		{
		 				monster[i].cycle++;
		 			}
		 			else 
		 			{
		 				monster[i].cycle = 0;
		 			}
		 			char next = mvinch(monsterY,monsterX) & A_CHARTEXT;
		 			if(next == '.')
		 			{
		 				mvaddch(monster[i].y, monster[i].x, '.');
		 				monster[i].y = monsterY;
		 				monster[i].x = monsterX; 
		 				mvaddch(monster[i].y, monster[i].x, 'B');
		 			}
		 	    }
		 	    else if(monster[i].type == 'B')
		 	    {
		 	    	monsterX = monster[i].x;
		 			monsterY = monster[i].y;

		 			int random = rand() % 4 + 1; 
		 			switch(random)
		 			{
		 				case 0: 
		 					monsterX -= 1;
		 					break;
		 				case 1:
		 					monsterY -= 1; 
		 					break;
		 				case 2: 
		 					monsterX += 1; 
		 					break;
		 				case 3: 
		 					monsterY += 1; 
		 					break;
		 			} 
		 			char next = mvinch(monsterY,monsterX) & A_CHARTEXT;

		 	    	if(next == '.')
		 			{
		 				mvaddch(monster[i].y, monster[i].x, '.');
		 				monster[i].y = monsterY;
		 				monster[i].x = monsterX; 
		 				mvaddch(monster[i].y, monster[i].x, 'B');
		 			}
			    	
		 	    }	
		 	}   
   		}
        refresh();
    }
    endGame(hero);
}

/**
 * checkInput
 * passes in users last keystroke, runs accordingly
 * IN:Users keystroke, Pointers to hero and Enemies Data PBR
 * OUT: the condition of what is about to happen based on keystroke
 * POST:
 * ERROR: doesn't sanitize input, idk what could happen
 */
int checkInput(char input, Player * hero, Enemy * monster)
{
    char space;
    int x = 0; 
    int y = 0;
    x = hero->x;
    y = hero->y; 
 
    switch(input)
    {
        case 'w':
            y -= 1;
            break;
        case 'a':
            x -= 1;
            break;
        case 's':
            y += 1;
            break;
        case 'd':
            x += 1;
            break;
        case 'h':
            return 2;
    }

    char * s = malloc(sizeof(char) * 256);
    space = mvinch(y,x) & A_CHARTEXT;

    for (int i = 0; i <= 20; i++)
    {
    	if (x == monster[i].x && y == monster[i].y)
    	{
			int r = rand() % 10 + 1; 
			if (r > monster[i].speed)
			{
					monster[i].health -=  hero->attack; 
				    sprintf(s,"You WON! Did %d damage to '%c' HP: %d!", hero->attack, monster[i].type, monster[i].health);
					notify(s); 
			}
			else 
			{
				if (monster[i].type == 'A')
				{
					hero->attack -= monster[i].attack; 
					sprintf(s,"You to the Aquator! You lost %d attack points!!", monster[i].attack);
					notify(s);
				}	
				else 
				{
					hero->health -= monster[i].attack;
					sprintf(s,"You LOST! Took %d damage!", monster[i].attack);
					notify(s); 
				}
			}

			if (monster[i].health <= 0)
			{
				sprintf(s,"you killed '%c', and recieved %d GOLD!", monster[i].type, 50);
				notify(s);
				hero->gold += 50; 
				monster[i].dead = 1; 
				monster[i].x = 0; 
				monster[i].y = 0; 
				movePlayer(input, hero, 2);
				return 1;
			}
        }
    	
    }

    switch(space)
    {
        case '.':
            return 1;
            break;
        case '#':
            return 2;
            break;
		case '+':
		    return 3;
		    break;
        case '*':
		    return 4;
		    break;
		case '8':
		    return 5;
			break;
		case '(':
			return 6;
			break;
		case ')':
			return 7;
			break;
		case '[':
		    return 8;
			break;
		case '!':
		    return 12;
		    break;
		case '>':
			return 10;
			break;
		case '<':
			return 10;
			break;
		case 'T': 
			return 11; 

        default:
            return 0;
    }
    return 0;
}

/**
 * movePlayer
 * moves the player on the screen based on situation of move
 * IN: keystroke, the hero pointer, the situation of movement
 * OUT: N/A
 * POST:
 * ERROR: If the user kills the enemy it seems to skip a place (This doesn't break the game), unfixable under current circumstances 
 */
void movePlayer(char input, Player * hero, int type) 
{
   mvaddch(hero->y, hero->x , hero->standingOn);
   
   if (type == 0)
   {
		switch (input)
		{
			case 'w':
				hero->y -= 1;
				hero->standingOn = mvinch(hero->y, hero->x) & A_CHARTEXT;
				mvaddch(hero->y, hero->x, '@'); 
				break; 
			case 'a':
				hero->x -= 1;
				hero->standingOn = mvinch(hero->y, hero->x) & A_CHARTEXT;
				mvaddch(hero->y,hero->x, '@'); 
				break; 
			case 's': 
				hero->y += 1;
				hero->standingOn = mvinch(hero->y, hero->x) & A_CHARTEXT;
				mvaddch(hero->y, hero->x, '@');
				break;
			case 'd':
				hero->x += 1;
				hero->standingOn = mvinch(hero->y, hero->x) & A_CHARTEXT;
				mvaddch(hero->y, hero->x, '@'); 
				break;
		}
	}
	else if (type == 1)
	{
		switch (input)
		{
			case 'w':
				hero->y -= 1;
				hero->standingOn = '.';
				mvaddch(hero->y, hero->x, '@'); 
				break; 
			case 'a':
				hero->x -= 1;
				hero->standingOn = '.';
				mvaddch(hero->y,hero->x, '@'); 
				break; 
			case 's': 
				hero->y += 1;
				hero->standingOn = '.';
				mvaddch(hero->y, hero->x, '@');
				break;
			case 'd':
				hero->x += 1;
				hero->standingOn = '.';
				mvaddch(hero->y, hero->x, '@'); 
				break;
		}
	}
	else if (type == 2)
	{
		switch (input)
		{
			case 'w':
				hero->y -= 1;
				hero->standingOn = '.';
				
				break; 
			case 'a':
				hero->x -= 1;
				hero->standingOn = '.';
		 
				break; 
			case 's': 
				hero->y += 1;
				hero->standingOn = '.';
				
				break;
			case 'd':
				hero->x += 1;
				hero->standingOn = '.';
				
				break;
		}
	}
}

/**
 * createRoom
 * creates the room arrays based on all the info
 * IN: The Rooms Data, 
 * OUT: A 2d array, pointers referencing data of inited room to be printed
 * POST:
 * ERROR: Bad input is a bitch
 */
char ** createRoom(int roomY, int roomX, Room * rooms, int index)
{
    char ** currentRoom;
    currentRoom = malloc(sizeof(char*) *roomY);
    if(currentRoom == NULL)
    {
        printf("failed to allocate memory for room\n");
        exit(1);
    }

    for(int i=0;i<=roomY;i++)
	{
        currentRoom[i] = malloc(sizeof(char) *roomX);
        if(currentRoom[i] == NULL)
        {
            printf("failed to allocate memory for room \n");
            exit(1);
        }
    }
    for(int i=1;i<roomY-1;i++)
	{
        for(int k=1;k<roomX-1;k++)
		{
            currentRoom[i][k] = '.';
        }
    }

    for(int i=0;i<roomX;i++)
	{
        currentRoom[0][i] = '-';//- North Face
    }
    for(int i=0;i<roomY;i++)
	{
        currentRoom[i] [0] = '|';//| West Face
    }
    for(int i=0;i<roomY;i++)
	{
        currentRoom[i] [roomX  - 1] = '|';//| East Face
    }
    for(int i=0;i<roomX;i++)
    {
        currentRoom[roomY -2] [i] = '-';//- South Face
    }
   
		for (int i  = 0; i < 3; i++)
		{
			switch (rooms[index].doors[i].bearing)
			{
				case 'e':
					currentRoom[rooms[index].doors[i].offset][roomX - 1] = '+';
					rooms[index].doors[i].x = roomX - 1;
					rooms[index].doors[i].y = rooms[index].doors[i].offset;
					break;
				case 'w':
					currentRoom[rooms[index].doors[i].offset][0] = '+';
					rooms[index].doors[i].x = 0;
					rooms[index].doors[i].y = rooms[index].doors[i].offset;
					break;
				case 's':
					currentRoom[roomY - 2][rooms[index].doors[i].offset] = '+';
					rooms[index].doors[i].x = rooms[index].doors[i].offset;
					rooms[index].doors[i].y = roomY - 2;
					break;
				case 'n':
					currentRoom[0][rooms[index].doors[i].offset] = '+';
					rooms[index].doors[i].x = rooms[index].doors[i].offset; 
					rooms[index].doors[i].y = 0; 
					break;
			}
		}

   
    srand(time(NULL));
    

	for (int i = 0; i < 8; i++)
	{
		if(isalpha(rooms[index].contents[i].type))
		{
			if (rooms[index].contents[i].type == 'g')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = '*'; 
			}
			else if (rooms[index].contents[i].type == 'G')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = '8';
			}
			else if (rooms[index].contents[i].type == 'h')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = '@'; 
			}
			else if (rooms[index].contents[i].type == 'w')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = '('; 
			}
			else if (rooms[index].contents[i].type == 'W')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = ')';
			}
			else if (rooms[index].contents[i].type == 'm') 
			{
				int r = 0;
			    r = rand() % 4 + 0; 
				if (r == 0)	
				{
					currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = 'A';
				}											
		        else if (r == 1)
				{				
					currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = 'B';
				}
				else if (r == 2)
				{
					currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = 'S';
				}
				else if (r == 3)
				{		
					currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = 'Z';
				}
				r = 0;
			}
			else if (rooms[index].contents[i].type == 'M')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = 'T'; 
			}
			else if (rooms[index].contents[i].type == 'p')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = '!';
			}
			else if (rooms[index].contents[i].type == 'z')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = '<';
			}
			else if (rooms[index].contents[i].type == 'a')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = '>';
			}
			else if (rooms[index].contents[i].type == 'e')
			{
				currentRoom[rooms[index].contents[i].y][rooms[index].contents[i].x] = '[';
			}
		}
	}
    return currentRoom;
}

/**
 * isScreenBigEnough
 * checks to see if the screen is big enough to handle the game
 * IN:The screen size and it artifically prints the rooms to nothing to see how much room it will take up
 * OUT: nothing, if the screen fits, continues. else, quits game tells user
 * POST:
 * ERROR: FUCK NCURSES
 */
void isScreenBigEnough(int screenX, int screenY, Room * rooms)
{
	int maxColumnsInTop = 0;
	int maxColumnsInBottom = 0;
	//int xoffset = 0;

	for (int z = 0; z < 6; z++)
    {
		if (z <= 2)
	    {
			if (z == 0)
			{
			    //offset = 3;
				maxColumnsInTop = rooms[z].columns;
			}
			else
		    {
				//xoffset += (rooms[z - 1].rows  + 5);
				if(rooms[z].columns > maxColumnsInTop)
				{
					maxColumnsInTop = rooms[z].columns;
				}
			}
		}
	    else if (z > 2 && z < 6)
		{
		    if(z == 3)
			{
				//xoffset = 3;
			    maxColumnsInBottom = rooms[z].columns;
			}
		    else if (z > 3)
		    {
				//xoffset += (rooms[z - 1].rows  + 5);
				if (rooms[z].columns > maxColumnsInBottom)
				{
				    maxColumnsInBottom = rooms[z].columns;
				}
			}
		}
	}

	int printBottomYcorr = 0; 
	printBottomYcorr = maxColumnsInTop + maxColumnsInBottom + 7; 

    if (printBottomYcorr < screenY)
    {
    	endwin();
    }
}

/**
 * initEnemy
 * creates 1 enemy with the inputed data
 * IN: all the data nessessary to have a working monster
 * OUT: 1 init'd monster to be added to overall array! 
 * POST:
 * ERROR: N/A (I think) 
 */
Enemy initEnemy(int y, int x, int hp, int attack, int speed, char type)
{
	Enemy * tmp = malloc(sizeof(Enemy));
	tmp->attack = attack;
	tmp->health = hp; 
	tmp->speed = speed; 
	tmp->y = y; 
	tmp->x = x;
	tmp->type  = type; 
	tmp->dead = 0; 
	tmp->cycle = 0; 
	return *tmp; 
}

/**
 * printStatus
 * Takes in the players data, and prints it to the bottom of the screen
 * IN: The players data, the bottoms Y corr to know where to print.
 * OUT: N/A
 * POST:
 * ERROR:
 */
void printStatus(Player hero, int bottomY)
{
	char *s = malloc(sizeof(char) * 256);
	sprintf(s,"Health: %d Potions: %d Attack: %d Inventory:%d/5 Gold:%d", hero.health, hero.potions, hero.attack, hero.items, hero.gold); 
	
	for (int i =0; i < 40; i++)
	{
		mvaddch(bottomY + 3, i, ' ');
	}
	mvprintw(bottomY + 3,0,s);

	free(s); 
	return; 
}

/**
 * notify
 * takes in a preformatted string and prints it to the top  
 * IN:the formatted string
 * OUT:N/A
 * POST: Clears top line when this is called
 * ERROR:
 */
void notify(char * message)
{
	int screenX = 0; 
	int screenY = 0; 
	
	getmaxyx(stdscr, screenY, screenX);
	//just using screenY because if I don't it causes a warning
	screenY = 0;

	for (int i =0; i < screenX; i++)
	{
		mvaddch(screenY, i, ' ');
	}
	
	mvprintw(0,0, message);
	return;
}

/**
 * endGame
 * when called it ends the game and prints the users data to the command line
 * IN: heros data
 * OUT:N/A
 * POST: This ends the game!
 * ERROR:
 */
void endGame(Player hero)
{
	endwin();

	int itemStats[5]; 

	printf("\nYou found:%s %d gold pieces!%s\n",GREEN,hero.gold,RESET);
	printf("\nAlso, you found %s%d%s items\n",GREEN,hero.items,RESET);

	for (int i =0; i < hero.items; i++)
	{
		if (hero.itemsType[i] == ')') //common 0 - 9 attack rating
		{
			itemStats[i] = rand() % 10;
			printf("Common Weapon: %s'%c'%s, attack rating of: %s%d%s\n", GREEN, hero.itemsType[i],RESET, GREEN, itemStats[i], RESET);
		}		
		else if (hero.itemsType[i] == '(') //rare 10-15 attack rating
		{
			itemStats[i] = rand() % 15 + 10;
			printf("%sRare%s Weapon: %s'%c'%s, attack rating of: %s%d%s\n", GREEN, RESET, GREEN, hero.itemsType[i],RESET,  GREEN, itemStats[i], RESET);
		}
		else if (hero.itemsType[i] == ']') //equipment 0-20 defense rating
		{
			itemStats[i] = rand() % 20 + 0;
			printf("Equipment: %s'%c'%s, defensive rating of: %s%d%s\n", GREEN, hero.itemsType[i],RESET, GREEN, itemStats[i], RESET);
		}

	}

	printf("I saved your players results to %s'player.txt'%s\n", GREEN, RESET);
	FILE * filestream; 
	filestream = fopen("assests/player.txt", "w");
	fprintf(filestream, "gold:%d health:%d attack:%d potions %d", hero.gold, hero.health, hero.attack, hero.potions);

	for (int i =0; i < hero.items; i++)
	{
		fprintf(filestream,"Item:%d = %c\n", i,hero.itemsType[i]);
	}

	fclose(filestream);





	exit(0);
}

/**
 * addGold
 * when called it randomly generates gold based on the type, small or large
 * IN: int, 0 or 1. If 0 it's small gold if 1 it's large gold
 * OUT: the randomly generated gold
 * POST:
 * ERROR: Random generation is hit and miss idk why
 */
int addGold(int size)
{
    srand(time(NULL));
  	int gold = 0;
	if (size == 0)
	{
	    gold = rand() % 50;
	}
	else
	{
	    gold += rand() % 150;
	}
    return gold;
}

