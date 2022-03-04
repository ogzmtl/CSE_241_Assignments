#ifndef HEX
#define HEX

using namespace std;
enum {

    EMPTY = '.',
    PLAYER1 = 'x',
    PLAYER2 = 'o'

};

class Hex {
public:

    Hex();																						/*----------------------*/
    Hex(int size);// Constructor which arrange the board size as 0 for default.						/*CONSTRUCTERS*/
    Hex(const Hex& copy); // copy constructor is set the board as default value to reset game	/*---------------------*/
    
    void setBoard();
    void playGame();
    const int setBoardSize();//This member function returns size of board
   // void playGame();//Asks the user computer mode or two player mode , map size
    void BoardPrint();// printing the board with the given arguments

    void DefaultvisitedBoard();
    //This member function's purpose is check the recursion movement. It turns all visited movement into '0'
    //And this function helper function of visited function
    
    int play2player();
    char gamemode;


    void playcmp();
    bool comparehexes(Hex& obj);
    bool operator==(const Hex& object1) const;							/*-------------------------------------------*/
    Hex& operator=(Hex& object);
    Hex& operator--();// prefix overload										/*OPERATOR OVERLOADINGS*/
    Hex& operator--(int);// postfix overload
    friend ostream& operator << (ostream& out, const Hex& obj);			/*-------------------------------------------*/


    void movementcopy();// copies the all movements after every entering
    void movearray();// keeps all movements in dynamic array **moves (in private)
    int findscore(); // finding score func

        class Cell {

        public:

            char getCell();
            inline void setCell(char var);
            void setDefaultCell(const char var = EMPTY);
        private:
            char celldata;

        };

        ~Hex();// destructor for class dynamic memory deletion

private:
    bool xchecks();
    //  First one this function write x to board(vector hexcells) if it's valid 
    // second one it prints the board 
    // third one if X win control(xsearching() function) returns 1 then stop the program and print the X WIN
    // if xsearching() function returns false then this function calls the  defaultvisitedBoard() and reset the vector which is keep the visited locations 

    bool ochecks();
    // same as xchecks function 
    //  First one this function write x to board(vector hexcells) if it's valid 
    // second one it prints the board 
    // third one if O win control( osearching() function) returns 1 then stop the program and print the O WIN
    // if osearching() function returns false then this function calls the  defaultvisitedBoard() and reset the vector which is keep the visited locations 

    bool xsearching();// check the every x in first COLUMN. This check function prepare every possible X for recursion winnig control.
    bool osearching();// check the every o in first ROW This check function prepare every possible O for recursion winnig control.

    bool xrecursion_check(int num, int let);
    // This is a recursion function whether the all the possible connections wins the game according to the rule or not 
    bool orecursion_check(int num, int let);

    bool isEmpty();// checks the cell if cell is empty or not

    void savegame(char last, string str);
    string filenamearrange();
    void loadgame(string str);
    void countmarkedcell();
    void printlastmap();// when user make undo function prints lastmap
    
    int markedcell;

    Cell** hexCells;
    int** moves;// This dynamic array hold the all moves when game started

    int** visitedcheck;
    // this vector was created to resolve an error ( INFINITE LOOP )
    // X  X
    //  X     
    //In this X Locations program enters the infinite loop (in the recursion function inside) so this vector prevent that situation
    // If one of the recursion attempts are found x in the board it this vector checks if exactly same location on their index is 0 or -1
    // If it -1 that means this location is visited before so the function which arrange this control is return false and try another recursion movement
    // also this vector's indexes return default version all of the indexes are returns 0 before all new checks
    //this return is not in the continuation of the same process it renewed of all new recursion process          

    int Boardsize;
    int letter;
    int number;
    string txt;// helper variable to arrange save load commands
    int backtrace;// prevents the recursion function move back and prevent entering infinite loop 
    int lastmove;// hold the move arrays index which is indicate lastmovement index
    int movecount=0;// Counts the movement of all game (when new object is called this value returns 0
    int scorex, scorey;

    bool checkBoardSize(int size);
    char SelectGameMode();
    bool isFull();// checks the board if it is full or not
   
    string XorOTURN(char player);
    // Take all x and o movement in one function and send them to commandarrange function
    // because it takes string and our hexCell array's indexes must be integer
    
    bool playx();// This function includes every x movement's check validity,xwin or lose situation, etc...
    bool playo();
    void commandarrange(const string& str, const string& str2);// This function turns strings to integer for location

    bool visited(int num, int let);
    //Control all the current movement (valid or not ) 
    // if it is valid this function write the -1 into the visitedcheck if valid movement happens it return false(isn't visited).

    bool saveloadcheck(char player);
    // if the command is like "save","SAVE","load","LOAD" this functions calls the savegame filename or loadgame funcitons and return true
    // else it just return false because this false means the game continue and locations validity must be checked next

    void play(const string let, const string num);
    //void play();
};

#endif
