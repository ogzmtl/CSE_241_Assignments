#include<iostream>
#include<fstream>
#include <string>
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
					def_map[i][j] = EMPTY;
					def_map[i][j+1] = SPACE;
				}
				j=0;

			}
			else
			{

				while( i != j)
				{
					def_map[i][j] = SPACE;
					j++;
				}
				for(; j < (2*COL_ROW)+i ; j = j+2)
				{
					def_map[i][j] = EMPTY;
					def_map[i][j+1] = SPACE;
				}
				j =  0;
			}
		}

}
void Map_Print(int USER_INPUT, char map[MAX_ROW][MAX_COL])
{
	int i = 0,j = 0 ;
	char c ='A',d =SPACE;
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

	if(Menu != 'a' && Menu != 'b')
		cerr<<"!!!! Wrong Entrance !!!!!";

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
				case FIRST  : check = 1;
					break;

				case SECOND  : check = 1;
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
				case FIRST : check = 1;
					break;

				case SECOND  : check = 1;
					break;
				default : cerr<< "Wrong entrance try again !!! \n";
			}
	}
return Menu;
}
void Start_Game(char game_menu[4], int map_size, char game_map[MAX_ROW][MAX_COL])
{
	int coord_number,letter_inp;
	char coord_letter;
	string txt,str1;
	bool control=false,X=false,O=false;

	switch(game_menu[0])
	{
		case 'a':/*if menu[0] = a then user choose the play with computer*/

				while(!isFull(game_map,map_size) || X)/*While either x,o win or draw situation not happens game will continue*/
				{
					Map_Print(map_size,game_map);

					txt = XTURN(coord_number,letter_inp);

					if(txt.substr(0,4) == "SAVE")	savegame(game_map,map_size,game_menu[0],'x',filename_arrange(txt));

					else if(txt.substr(0,4) == "LOAD") loadgame(game_map,game_menu,map_size,filename_arrange(txt));

					else
					{
						if(isEmpty(game_map, letter_inp, coord_number-1))/*If entered coordinant is empty and valid then this if statement works*/
						{

							X = all_checksfor_X(letter_inp,coord_number,game_map,map_size);
							computer_move(coord_number-1,letter_inp,game_map,map_size);
							Map_Print(map_size,game_map);
						}
						else cerr<<"This place is not empty"<<endl;
					}
				}
			break;

		case 'b':/*This case provide us to 2 user playing */

			Map_Print(map_size,game_map);

			while(!control && game_menu[0] == 'b')

			{
				if(game_menu[2] == FIRST) /*game_menu[2] = x then x will start first */
				{
					txt.clear();
					txt = XTURN(coord_number,letter_inp);

					if(txt.substr(0,4) == "SAVE")	savegame(game_map,map_size,game_menu[0],'x',filename_arrange(txt));

					else if(txt.substr(0,4) == "LOAD") loadgame(game_map,game_menu,map_size,filename_arrange(txt));


					else
					{
						if(isEmpty(game_map, letter_inp, coord_number-1))
						{
							 X = all_checksfor_X(letter_inp,coord_number,game_map,map_size);
							/*Below this line*/
							/*When x starts the game and all control functions are true then user 'o's moves is checked below this line*/

						        txt.clear();
							txt = O_TURN(coord_number,letter_inp);

							if(txt.substr(0,4) == "SAVE")	savegame(game_map,map_size,game_menu[0],'o',filename_arrange(txt));

							else if(txt.substr(0,4) == "LOAD") loadgame(game_map,game_menu,map_size,filename_arrange(txt));

							else
							{
								while(!isEmpty(game_map, letter_inp, coord_number-1))/*If entered coordinant is filled then this if statement works and tell the play again error to user*/
									{
										cerr<<"This place is filled play again...\n";
										txt = O_TURN(coord_number,letter_inp);
									}
									O = all_checksfor_O(letter_inp,coord_number,game_map,map_size);
							}
						}
					}
				}

				else /*game_menu[2] = o then o will start first */
				{
					txt.clear();
					txt = O_TURN(coord_number,letter_inp);

					if(txt.substr(0,4) == "SAVE")	savegame(game_map,map_size,game_menu[0],'o',filename_arrange(txt));

					else if(txt.substr(0,4) == "LOAD") loadgame(game_map,game_menu,map_size,filename_arrange(txt));

					else
					{
						if(isEmpty(game_map, letter_inp, coord_number-1))/*If isEmpty is not true then program wants another input different input from 'o'*/
						{
							O = all_checksfor_O(letter_inp,coord_number,game_map,map_size);
							/*When o will start first below this line is movement for x */
							/*Then 'x' player enters wrong coordinant then program want another different entrance from user */
							txt.clear();
							txt = XTURN(coord_number,letter_inp);

							if(txt.substr(0,4) == "SAVE")	savegame(game_map,map_size,game_menu[0],'x',filename_arrange(txt));

							else if(txt.substr(0,4) == "LOAD") loadgame(game_map,game_menu,map_size,filename_arrange(txt));

							else
							{
								while(!isEmpty(game_map, letter_inp, coord_number-1))/*If entered coordinant is filled then this if statement works and tell the play again error to user*/
								{
									cout<<"\nThis place is filled play again...\n";
									txt = XTURN(coord_number,letter_inp);

								}
								X = all_checksfor_X(letter_inp,coord_number,game_map,map_size);
							}
						}
					}
				}

				Map_Print(map_size,game_map);
				control = O || X; 	/*This control line check if 'o' or'x' win or not*/
			}
			break;
	}
	Final_Map(game_map,O,X,map_size);

}
string XTURN(int& number, int& letter)
{

	   	char letter1;
		string str,a,str2;

			cout<<"X Plays :";
			cin >> str >> str2;

			a.clear();
			a = str+str2;

			if(str != "LOAD" || str != "SAVE")
			{
				letter = (str[0] - '0')- 49;
				if(str2.size()== 2)
					number = 10*(str2[1] -'0');


				else
					number = (str2[0] -'0');
			}
return a;
}
string O_TURN(int& number,int& letter)
{
   	char letter1;
	string str,a,str2;

		cout<<"O Plays :";
		cin >> str >> str2;

		a.clear();
		a = str+str2;

		if(str != "LOAD" || str != "SAVE")
		{
			letter = (str[0] - '0')- 49;
			if(str2.size()== 2)
				number = 10*(str2[1] -'0');

			else
				number = (str2[0] -'0');
		}


return a;
}
bool Search_X(char map[MAX_ROW][MAX_COL],int& let_X, const int& SIZE)
{
	bool control = false;
	int a=0,j=0;

	for( a = 0 ; a < SIZE; a++) /* To find first x in A column*/
	{

			if(map[a][a] == FIRST)
			{
				control = true;
				let_X = a;
				a = SIZE;
			}

	}
return control ;
}
bool isEndofGame_O(int SIZE,int inp_letter, int inp_number, char game_map[MAX_ROW][MAX_COL],int backtrace)
{
	int temp_x,temp_y;
	bool check =false;

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
			if (game_map[temp_x][temp_y]=='o' )/*returns the function if other move is valid but when it enter this if statement it always return 1. I didn't solve this problem*/
				check = true;

			else check= false;

			if(check)
			{
				if(temp_x != SIZE-1)
					check =  isEndofGame_O(SIZE, temp_y, temp_x, game_map,i);

				if(check)
						i = 7;
			}

			//else return false;

		}
		return check;

}
bool isEmpty(char map[MAX_ROW][MAX_COL],int letterside,int numberside)
{

	if(isValid(map,numberside,letterside) != '.')/*If the input coordinant is not empty('.')it will return false*/
		return false;

	return true;
}
char isValid(char Game_Map[MAX_ROW][MAX_COL],int num_coord,int lett_coord)
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
bool isEndofGame_X(int SIZE,int inp_letter, int inp_number, char game_map[MAX_ROW][MAX_COL],int backtrace)
{
	int temp_x,temp_y;
	bool check = false;

		for (int i = 1; i < 7; i++)									/*in this loop */
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
						temp_y = inp_letter + 1 ;
						temp_x = inp_number - 1 ;

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
						temp_y = inp_letter - 1 ;
						temp_x = inp_number + 1 ;
					}

					if(i == 6 )
					{
						temp_y = inp_letter - 2 ;
						temp_x = inp_number;
					}

			}

			if (game_map[temp_x][temp_y]=='x')/*returns the function if other move is valid but when it enter this if statement it always return 1. I didn't solve this problem*/
				{
					check = true;
				}
			else check = false;

			if(check)
			{
				if(temp_y != 2*(SIZE)+temp_x-1 )
						check = isEndofGame_X(SIZE, temp_y, temp_x, game_map,i);


				if(check)
					i=7;
			}
			//else return false;

		}
		return check;
}
bool Search_O(char map[MAX_ROW][MAX_COL],int& let_O, const int& SIZE)
{
	bool control1 = false;
	int a=0;

	for(int j = 0 ; j < 2*SIZE ; j+=2) /* To find first o in first row to begin search*/
	{
		if(map[a][j] == 'o')
		{
			control1 = true;
			let_O = j;
			return control1;
		}
	}
return control1 ;
}
void computer_move(int number,int letter,char map[MAX_ROW][MAX_COL],int SIZE)
{

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
char Cmp_isValid(char map[MAX_ROW][MAX_COL],const int& num,const int& let)
{
	return map[num][2*let+num];
}
void Final_Map(char gamemap[MAX_ROW][MAX_COL],bool owin,bool xwin,int mapsize)
{
	int index;

		if(owin)
			cout<<"!!!!!!!!!! O WINS !!!!!!!!!!!!";

		else
			cout<<"!!!!!!!!!! X WINS !!!!!!!!!!!!";

}
void savegame(char map[MAX_ROW][MAX_COL],int msize, char menu,char last, string str)
{
	ofstream FILE;

		FILE.open(str.c_str());


		FILE<<menu<<"\n";
		FILE<<msize<<"\n";
		FILE<<last<<"\n";

		for(int a = 0 ; a < msize ; a++)
		{
			for(int b = 0 ; b<(2*msize)+a;b++)
			{
				FILE<<map[a][b];
			}
			FILE<<"\n";
		}
		FILE.close();
		//loadgame(map,msize,str);
}
/*void loadgame(char map[MAX_ROW][MAX_COL],int msize,string str)//OVERLOADED
{
	ifstream FILESAVE(str.c_str());
	ofstream FILELOAD;
	string c;

	if(FILESAVE.is_open())
		{
			FILELOAD.open(str.c_str());

			while(getline(FILESAVE,c))
			{
				FILELOAD<<c;
				FILELOAD<<"\n";
			}
			FILELOAD.close();
			FILESAVE.close();
		}

}*/
void loadgame(char gamemap[MAX_ROW][MAX_COL],char gmenu[4],int msize,string str)
{
	ifstream FILELOAD(str.c_str());
	string c;
	int a = 0 ;
	int b = 0, j = 0 ;

	if(FILELOAD.is_open())
		{
			for( int i = 0; i<3 ; i++)
			{
				getline(FILELOAD,c);
				gmenu[i] = c[0];
			}

			while(getline(FILELOAD,c))
			{
				while(j !=a + 2*msize)
				{
					gamemap[a][b] = c[j];
					b++;
					j++;

				}
				a++;
				b=0;
				j=0;
			}


			FILELOAD.close();
		}
	else cerr<<"THERE IS NO SUCH A FILE \n";

}
bool all_checksfor_X(int letter,int number, char map[MAX_ROW][MAX_COL],int msize )
{
	bool X_win  ;
	int trackback = 0 ;

		map[number-1][number+(2*letter)-1] = FIRST;/*If all coordinants are correct for x then board is refreshed by the program and program writes new input location in the array*/
		Map_Print(msize,map);

		if( Search_X(map,letter,msize) )/*if there is no 'x' in first row this if statement will not work */
					X_win = isEndofGame_X(msize,letter,number-1,map,trackback);


return X_win;
}
bool all_checksfor_O(int letter,int number, char map[MAX_ROW][MAX_COL],int msize )
{
	int backtrack = 0 ;
	bool  O_win;
	map[number-1][number+(2*letter)-1] = SECOND;/*If the location is valid 'o' value located that place*/
	Map_Print(msize,map);/*In every move map is printing */

			if( Search_O(map,letter,msize) )/*This statement controls the first row to check 'o' winning situation*/
				O_win = isEndofGame_O(msize,letter,0,map,backtrack);
return O_win;
}
string filename_arrange(string txt)
{
	string b = txt.substr(4,txt.size());//to separate first 4 letters from the file name string 
return b;
}
