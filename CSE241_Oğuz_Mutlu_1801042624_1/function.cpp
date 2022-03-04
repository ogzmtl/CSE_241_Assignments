#include<iostream>
#include "function.h"
using namespace std;

int Select_Map_Size()
{
	int SIZE = 0;

	   while(SIZE > 12 || 6 > SIZE )
	   {

		cout <<"\nPress 6 to (6x6)\n"
			<<"Press 7 to (7x7) \n"
			<<"Press 8 to (8x8)\n"
			<<"Press 9 to (9x9)\n"
			<<"Press 10 to (10x10)\n"
			<<"Press 11 to (11x11)\n"
			<<"Press 12 to (12x12)\n "
			<< "Please enter your map size\n" ;
			cin>> SIZE;

			if(SIZE > 12 || 6 > SIZE)
				cerr<< "\nEntered wrong map size please try again\n";
	   }
	return SIZE;
}
void Map_Clean(int USER_INPUT, char map[MAX_ROW][MAX_COL])
{
	for(int i = 0 ; i < USER_INPUT ; i++)
	{
		for(int j = 0 ; j < MAX_COL ; j++)
		{
			map[i][j] = '\0';	/*Clean the memory we don't want any  ruins in output */
		}
	}
}
void Map_Draw(int COL_ROW,char def_map[MAX_ROW][MAX_COL])
{
	int i = 0,j = 0;

		for(; i < COL_ROW ; i++)
		{

			if(i == 0)
			{
				for(j = 0 ; j< 2*COL_ROW ; j= j+2)
				{
					def_map[i][j] = '.';
					def_map[i][j+1] = ' ';
				}
				j=0;

			}
			else
			{

				while( i != j)
				{
					def_map[i][j] = ' ';
					j++;
				}
				for(; j < (2*COL_ROW)+i ; j = j+2)
				{
					def_map[i][j] = '.';
					def_map[i][j+1] = ' ';
				}
				j =  0;
			}
		}

}
void Map_Print(int USER_INPUT, char map[MAX_ROW][MAX_COL])
{
	int i = 0,j = 0 ;
	char c ='A',d =' ';
	cout<< d;
	cout<< d;
	for(i = 0 ; i < USER_INPUT ; i++)
	{

		cout<< c;
		c++;
		cout<< d;
	}
	cout<<endl;

	for(i = 0 ; i < USER_INPUT ; i++)
	{
		cout<< i+1;
		cout<< d;
		   for ( j = 0 ; j< MAX_COL; j++ )
			   cout<<map[i][j];
		cout<<endl;
	}
	   cout<<endl;

}
void Game_Menu(char Mode[4])
{
	int check  = 0 ;
	while(check != 1)
	{
		Mode[0] = Select_Game_Mode(Mode[0]);/*Mode[0] is select the computer or human playing*/

		switch (Mode[0])
		{
			case 'a' :
				check = 1;
				break;

			case 'b' :
				Mode[1] = Select_X_O(Mode[1]);
				Mode[2] = Select_First_Player(Mode[2]);
				check = 1 ;
				break;

			default : cerr << "!!! Wrong entrance please try again !!!\n";
			break;
		}
	}
}
char Select_Game_Mode(char Menu)
{
	cout << "\na. Computer Mode\n"
		 << "b. 2-Person Mode\n";
	cin >> Menu;
return Menu;
}
char Select_X_O(char Menu)
{
	int check = 0;


	while(check != 1)
	{
		cout << "\nPlease select X or O \n";
		cin >> Menu;
			switch(Menu)
			{
				case 'x'  : check = 1;
					break;

				case 'o'  : check = 1;
					break;
				default : cerr<< "Wrong entrance try again !!! \n";
			}
	};
return Menu;
}
char Select_First_Player(char Menu)
{
	int check = 0;


	while(check != 1)
	{
		cout << "\nPlease select first movement (X or O) to beginning\n\n";
		cin >> Menu;
			switch(Menu)
			{
				case 'x'  : check = 1;
					break;

				case 'o'  : check = 1;
					break;
				default : cerr<< "Wrong entrance try again !!! \n";
			}
	}
return Menu;
}
void Start_Game(char game_menu[4], int map_size, char game_map[MAX_ROW][MAX_COL])
{

	int print_or_check,coord_number;
	int letter_inp,trackback = 0;
	char coord_letter;
	bool control=true,X_win=false,O_win=false;

	switch(game_menu[0])
	{
		case 'a':/*if menu[0] = a then user choose the play with computer*/

				while(!isFull(game_map,map_size))/*While either x,o win or draw situation not happens game will continue*/
				{
					Map_Print(map_size,game_map);


					cout<<"X Plays :";
					cin >> coord_letter >> coord_number;
					letter_inp = (coord_letter - '0') - 49;/*For equalize 'a' value to 0 (ASCII)*/

					if(isEmpty(game_map, letter_inp, coord_number-1, print_or_check))/*If entered coordinant is empty and valid then this if statement works*/
					{
						game_map[coord_number-1][coord_number+(2*letter_inp)-1] = 'x';
						Map_Print(map_size,game_map);

						computer_move(coord_number-1,letter_inp,game_map,map_size);
						Map_Print(map_size,game_map);
					}
					else cout<<"This place is not empty"<<endl;
				}
			break;

		case 'b':/*This case provide us to 2 user playing */

			Map_Print(map_size,game_map);

			while(!O_win)

			{
				if(game_menu[2] == 'x') /*game_menu[2] = x then x will start first */
				{

						cout<<"X Plays :";
						cin >> coord_letter >> coord_number;
						letter_inp = (coord_letter - '0') - 49;/*For equalize 'a' value to 0*/

						if(isEmpty(game_map, letter_inp, coord_number-1, print_or_check))
						{
							game_map[coord_number-1][coord_number+(2*letter_inp)-1] = 'x';
							Map_Print(map_size,game_map);

								if( Search_X(game_map,&letter_inp,map_size) )/*if there is no 'x' in first row this if statement will not work */
										X_win = isEndofGame_X(map_size,letter_inp,0,game_map,trackback);


								cout<<"O Plays :";
								cin >> coord_letter >> coord_number;
								letter_inp = (coord_letter - '0') - 49;/*For equalize 'a' value to 0*/

								while(!isEmpty(game_map, letter_inp, coord_number-1, print_or_check))/*If entered coordinant is filled then this if statement works and tell the play again error to user*/
								{
									cout<<"This place is filled play again O Plays :";
									cin >> coord_letter >> coord_number;
									letter_inp = (coord_letter - '0') - 49;
								}

								game_map[coord_number-1][coord_number+(2*letter_inp)-1] = 'o';/*If the location is valid 'o' value located that place*/
								Map_Print(map_size,game_map);/*In every move map is printing */

									if( Search_O(game_map,&letter_inp,map_size) )/*This statement controls the first row to check 'o' winning situation*/
										O_win = isEndofGame_O(map_size,letter_inp,0,game_map,trackback);
						}
				}

				if(game_menu[2] == 'o') /*game_menu[2] = o then o will start first */
				{

						cout<<"O Plays :";
						cin >> coord_letter >> coord_number;
						letter_inp = (coord_letter - '0') - 49;/*For equalize 'a' value to 0*/

						if(isEmpty(game_map, letter_inp, coord_number-1, print_or_check))
						{
							game_map[coord_number-1][coord_number+(2*letter_inp)-1] = 'o';
							Map_Print(map_size,game_map);

							if( Search_O(game_map,&letter_inp,map_size) )
								O_win = isEndofGame_O(map_size,letter_inp,0,game_map,trackback);


							cout<<"X Plays :";
							cin >> coord_letter >> coord_number;
							letter_inp = (coord_letter - '0') - 49;/*For equalize 'a' value to 0*/

							while(!isEmpty(game_map, letter_inp, coord_number-1, print_or_check))/*If entered coordinant is filled then this if statement works and tell the play again error to user*/
							{
								cout<<"\nThis place is filled play again... X Plays :";
								cin >> coord_letter >> coord_number;
								letter_inp = (coord_letter - '0') - 49;
							}

							game_map[coord_number-1][coord_number+(2*letter_inp)-1] = 'x';
							Map_Print(map_size,game_map);

							if( Search_X(game_map,&letter_inp,map_size) )/*if there is no 'x' in first row this if statement will not work */
								X_win = isEndofGame_X(map_size,letter_inp,coord_number-1,game_map,trackback);
						}
				}
				Map_Print(map_size,game_map);

			}
			break;
	}
}
bool Search_X(char map[MAX_ROW][MAX_COL],int* let_X, int SIZE)
{
	bool control = 0;
	int a=0;

	for(int j = 0 ; j < SIZE ; j++) /* To find first x in A column*/
	{
		if(map[a++][j] == 'x')
		{
			control = true;
			*let_X = j;
			j = 2*SIZE;

		}
	}
return control ;
}
bool isEndofGame_O(int SIZE,int inp_letter, int inp_number, char game_map[MAX_ROW][MAX_COL],int backtrace)
{
	int temp_x,temp_y,first_control;
	bool check;

		for (int i = 1; i < 7; i++)
		{
			if(7 - backtrace != i)/*This backtrace variable is prevent the moving back if the valid position option is after the moving back option this if statemnt jump the reverse move  */
			{
				if(i == 1 )
				{
					temp_y = inp_letter + 1 ;
					temp_x = inp_number + 1 ;
				}

				if (i == 2)
				{
					temp_y = inp_letter - 1 ;
					temp_x = inp_number + 1 ;
				}
				if(i == 3 )
				{
					temp_y = inp_letter + 2 ;
					temp_x = inp_number;
				}

				if(i == 4)
				{
					temp_y = inp_letter - 2 ;
					temp_x = inp_number;
				}

				if (i == 5 )
				{
					temp_y = inp_letter + 1 ;
					temp_x = inp_number - 1 ;
				}

				if(i == 6 )
				{
					temp_y = inp_letter - 1 ;
					temp_x = inp_number - 1 ;
				}

			}
			if (game_map[temp_x][temp_y]=='o' && temp_x != SIZE)/*returns the function if other move is valid but when it enter this if statement it always return 1. I didn't solve this problem*/
			{
				return isEndofGame_O(SIZE, temp_y, temp_x, game_map,i);
			}
			else return false;

		}
		return true;
}
bool isEmpty(char map[MAX_ROW][MAX_COL],int letterside,int numberside,int print_or_check)
{

	if(isValid(map,numberside,letterside,print_or_check) != '.')/*If the input coordinant is not empty('.')it will return false*/
		return false;

	return true;
}
char isValid(char Game_Map[MAX_ROW][MAX_COL],int num_coord,int lett_coord, int Check_Print)
{
		return Game_Map[num_coord][num_coord + (2*lett_coord)];/*this function is isEmpty's helper function*/
}
bool isFull(char Game_Map[MAX_ROW][MAX_COL], int SIZE)
{
	int i,j=0; /*This function controls the map full or not*/
	for(i = 0 ; i < SIZE ; i++)
	{
		while(j < i )
		{
			j++;
		}
		for( ; j < 2*SIZE ; j = j+2)
		{
			if(Game_Map[i][j] == '.' && Game_Map[i][j+1] == ' ')
				return false;
		}
		j=0;
	}
return true;
}
bool isEndofGame_X(int SIZE,int inp_letter, int inp_number, char game_map[MAX_ROW][MAX_COL],int backtrace )
{
	int temp_x,temp_y,first_control;
	bool check;

		for (int i = 1; i < 6; i++)									/*in this loop */
		{											/*there are maximum 6 option which c and o can place so this recursive function provide that if one option is filled or not valid */
			if(7 - backtrace != i)					/*then other option will be checked by program */
			{										/*This backtrace variable is prevent the moving back if the valid position option is after the moving back option this if statemnt jump the reverse move  */

					if(i == 1)
					{
						temp_y = inp_letter + 2 ;
						temp_x = inp_number;
					}
					if(i == 2 )
					{
						temp_x = inp_letter - 1 ;
						temp_y = inp_number + 1 ;
					}
					if(i == 3 )
					{
						temp_y = inp_letter + 1 ;
						temp_x = inp_number + 1 ;
					}

					if(i == 4 )
					{
						temp_y = inp_letter - 1 ;
						temp_x = inp_number - 1 ;
					}

					if(i == 5 )
					{
						temp_x = inp_letter + 1 ;
						temp_y = inp_number - 1 ;
					}

					if(i == 6 )
					{
						temp_y = inp_letter - 2 ;
						temp_x = inp_number;
					}

				}

			if (game_map[temp_x][temp_y]=='x')/*returns the function if other move is valid but when it enter this if statement it always return 1. I didn't solve this problem*/
			{
				if(temp_y != 2*(SIZE-1)+temp_x )
				return isEndofGame_X(SIZE, temp_y, temp_x, game_map,i);

			}
		}
		return false;
}
bool Search_O(char map[MAX_ROW][MAX_COL],int* let_O, int SIZE)
{
	bool control1 = false;
	int a=0;

	for(int j = 0 ; j < 2*SIZE ; j+=2) /* To find first o in first row to begin search*/
	{
		if(map[a][j] == 'o')
		{
			control1 = true;
			*let_O = j;
			j = SIZE;
		}
	}
return control1 ;
}
void computer_move(int number,int letter,char map[MAX_ROW][MAX_COL],int SIZE)
{
	int control=1;

	if(2*letter+number == 2*(SIZE-1)+(number-1 )-3)
		{
			if(Cmp_isValid(map,number-1,letter+2) == '.')
				map[number-1][number +2*(letter)+3] = 'o';

			else if(Cmp_isValid(map,number,letter+3) == '.')
				map[number][number+ 2*letter+4] = 'o';

			else if(Cmp_isValid(map,number+1,letter+4) == '.')
				map[number][number +2*letter+5] = 'o';

		}
	else
	{
		if(Cmp_isValid(map,number,letter+2)=='.') map[number][number+2*letter+2] = 'o';

		else if(Cmp_isValid(map,number-1,letter+1)=='.')	map[number-1][number +2*letter+1] = 'o';

		else if(Cmp_isValid(map,number+1,letter+1)=='.')	map[number+1][number +2*letter+1] = 'o';

		else if(Cmp_isValid(map,number+1,letter-1)=='.')	map[number+1][number +2*letter-1] = 'o';

		else if(Cmp_isValid(map,number-1,letter-1)=='.')	map[number-1][number+2*letter-1] = 'o';

		else if(Cmp_isValid(map,number,letter-2)=='.')		map[number][number+2*letter-2] = 'o';
	}


}
char Cmp_isValid(char map[MAX_ROW][MAX_COL],int num,int let)
{
	return map[num][2*let+num];
}




