#ifndef HEX
#define HEX

#define MAX_COL 50
#define MAX_ROW 13

#include <string>
using namespace std;
enum Empty { EMPTY = '.', SPACE = ' ',FIRST = 'x',SECOND = 'o'};

int Select_Map_Size();
void Map_Draw(int COL_ROW,char def_map[MAX_ROW][MAX_COL]);/*fills the map with '.*/
void Map_Clean(int USER_INPUT, char map[MAX_ROW][MAX_COL]);/*Clean the array because we don't want any  ruins in output*/
void Map_Print(int USER_INPUT, char map[MAX_ROW][MAX_COL]);/*Prints the map*/
void Game_Menu(char Mode[4]);/*Selecting game mode(computer or 2 person , who is X who is O and who is gonna start first*/
char Select_Game_Mode(char Menu);/*vs Computer or 2 person play*/
char Select_X_O(char Menu);
char Select_First_Player(char Menu);
void Start_Game(char game_menu[4],int map_size,char game_map[MAX_ROW][MAX_COL]);/*The game play function all game play works in this function*/
string XTURN(int& number, int& letter);// When it's first(x) player's turn this function gets parameters as coordinant on boards
string O_TURN(int& number,int& letter);// When it's second(o) player's turn this function gets parameters as coordinant on boards
bool isEndofGame_X(int SIZE,int inp_letter, int inp_number, char game_map[MAX_ROW][MAX_COL],int backtrace);	/*Control the X's winning situation*/
bool Search_X(char map[MAX_ROW][MAX_COL],int& let_X, const int& SIZE);/*searching x value in A column*/
bool isEmpty(char map[MAX_ROW][MAX_COL],int letterside, int numberside);/*checks the input coordinants are empty or not*/
char isValid(char ame_Map[MAX_ROW][MAX_COL],int num_coord,int lett_coord);/*isEmpty's helper function*/
bool isFull(char Game_Map[MAX_ROW][MAX_COL], int SIZE); 	/*This function controls the map full or not*/
bool isEndofGame_O(int SIZE,int inp_letter, int inp_number, char game_map[MAX_ROW][MAX_COL],int backtrace);/*Control the O's winning situation*/
bool Search_O(char map[MAX_ROW][MAX_COL],int& let_O, const int& SIZE);/*searching o value in first row*/
void computer_move(int number,int letter,char map[MAX_ROW][MAX_COL],int SIZE);/*computer move strategies and movements are in this function*/
char Cmp_isValid(char map[MAX_ROW][MAX_COL],const int& num,const int& let);
//void loadgame(char map[MAX_ROW][MAX_COL],int msize,string str );
void savegame(char map[MAX_ROW][MAX_COL],int msize,char menu,char last, string str);// saves current position and turn to a file
void Final_Map(char gamemap[MAX_ROW][MAX_COL],bool owin, bool xwin,int mapsize);
void loadgame(char gamemap[MAX_ROW][MAX_COL],char gmenu[4],int msize,string str);// LOAD saved game same place where its saved before
bool all_checksfor_X(int letter,int number, char map[MAX_ROW][MAX_COL],int msize );//Arrange Start_game function from crowd of code block in this functions check status was controlled for x moves
bool all_checksfor_O(int letter,int number, char map[MAX_ROW][MAX_COL],int msize );//Arrange Start_game function from crowd of code block in this functions check status was controlled for o moves
string filename_arrange(string txt);//to separate first 4 letters from the file name string 

//void recursive_uppercase(char gmap[MAX_ROW][MAX_COL],int initial,int mapsize);
#endif
