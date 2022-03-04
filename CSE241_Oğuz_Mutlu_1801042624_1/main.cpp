#include <iostream>
#include <string>
#include "function.h"

using namespace std;

int main() {

	int SIZE_INP=0;
	char MAP[MAX_ROW][MAX_COL],GAME_MENU[4];		/*GAME_MENU keep the menu value's */
													/*GAME_MENU[0] = vs Computer or 2 Player*/
													/*GAME_MENU[1] = which one is x which one is o*/
													/*GAME_MENU[2] = when play 2 player game which letter will start x or o */

	SIZE_INP = Select_Map_Size();
	Map_Clean(SIZE_INP,MAP);
	    Map_Draw(SIZE_INP,MAP);
	    Map_Print(SIZE_INP,MAP);
	    Game_Menu(GAME_MENU);
	    Start_Game(GAME_MENU,SIZE_INP,MAP);


	return 0;
}
