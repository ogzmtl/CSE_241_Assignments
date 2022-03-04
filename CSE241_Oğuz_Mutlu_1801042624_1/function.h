#ifndef HEX
#define HEX

#define MAX_COL 50
#define MAX_ROW 13

int Select_Map_Size();
void Map_Draw(int COL_ROW,char def_map[MAX_ROW][MAX_COL]);/*fills the map with '.*/
void Map_Clean(int USER_INPUT, char map[MAX_ROW][MAX_COL]);/*Clean the array because we don't want any  ruins in output*/
void Map_Print(int USER_INPUT, char map[MAX_ROW][MAX_COL]);/*Prints the map*/
void Game_Menu(char Mode[4]);/*Selecting game mode(computer or 2 person , who is X who is O and who is gonna start first*/
char Select_Game_Mode(char Menu);/*vs Computer or 2 person play*/
char Select_X_O(char Menu);
char Select_First_Player(char Menu);
void Start_Game(char game_menu[4],int map_size,char game_map[MAX_ROW][MAX_COL]);/*The game play function all game play works in this function*/
bool isEndofGame_X(int SIZE,int inp_letter, int inp_number, char game_map[MAX_ROW][MAX_COL],int backtrace);	/*Control the X's winning situation*/
bool Search_X(char map[MAX_ROW][MAX_COL],int* let_X, int SIZE);/*searching x value in A column*/
bool isEmpty(char map[MAX_ROW][MAX_COL],int letterside, int numberside,int print_or_check);/*checks the input coordinants are empty or not*/
char isValid(char ame_Map[MAX_ROW][MAX_COL],int num_coord,int lett_coord, int Check_Print);/*isEmpty's helper function*/
bool isFull(char Game_Map[MAX_ROW][MAX_COL], int SIZE); 	/*This function controls the map full or not*/
bool isEndofGame_O(int SIZE,int inp_letter, int inp_number, char game_map[MAX_ROW][MAX_COL],int backtrace);/*Control the O's winning situation*/
bool Search_O(char map[MAX_ROW][MAX_COL],int* let_O, int SIZE);/*searching o value in first row*/
void computer_move(int number,int letter,char map[MAX_ROW][MAX_COL],int SIZE);/*computer move strategies and movements are in this function*/
char Cmp_isValid(char map[MAX_ROW][MAX_COL],int num,int let);/*check the computers special movement*/

#endif
