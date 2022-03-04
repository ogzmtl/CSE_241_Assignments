#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "abstracthex.h"
using namespace std;


int MainMenu()
{
    int inp;
        cout << "Welcome to HEX Game Menu\n"
            << "------------------------\n"
            << "1.Create a new game \n"
            << "2.Compare two games \n"
            << "3.Marked Cells\n"
            << "4.Undo Movement\n"
            << "5.Resume last game\n"
            << "0.Exit\n";
        cin >> inp;
        if(inp >= 6) throw -1;

    return inp;
}
int oned_vectorMenu()
{
    int inp;
        cout <<"\n";
        cout << "1.Vector Class Test\n"
             << "2.1D Dynamic Class Test\n";
        cin>>inp;
        if(inp == 1 || inp == 2) return inp;

        else throw -1;
}
void markedcellMenu(int& check, int check2,int count)
{
    if(count < 1)
    {
        cout<<" THE PROGRAM COULDN'T FIND 2 GAMES TO COMPARE\n";
        throw -1;
    }

        cout << "Enter 2 game to compare marked cells" << endl;
            for (int i = 0; i < count; i++)
            {
                cout << i+1 << ".Game"<<endl;
            }
            cin >> check >> check2;

 } 

AbstractHex::AbstractHex():Boardsize(0)
{
    //EMPTY
}

/*Hex::Hex(int size)
{
    size = setBoardSize();
    Boardsize = size;
}*/

AbstractHex ::AbstractHex(const AbstractHex& copy) { Boardsize = copy.Boardsize; }

void AbstractHex::DefaultvisitedBoard()
{

    visitedcheck = new int*[Boardsize];

    for (int i = 0; i < Boardsize; i++)
    {
        visitedcheck[i] = new int[Boardsize];
        for (int j = 0; j < Boardsize; j++)
        {
            visitedcheck[i][j] = 0;
        }
    }
}

int AbstractHex::setBoardSize()
{
    int size;

    cout << "Please enter the Board Size( Higher than 5x5 )\n"
        << "(For example Press 5 to 5x5)\n"
        << endl;
    cin >> size;

    if (checkBoardSize(size));

    else
        cout << "Entered wrong size value...\n"
        << "!!!Try Again !!!"
        << endl;

    return size;
}

bool AbstractHex::checkBoardSize(int size)
{
    if (size >= 5)
        return true;
    else
    {
        cerr << "You entered wrong size for board please try again."
            << endl;
        return false;
    }
}

void AbstractHex::Cell::setCell(char var)
{

    if (var == PLAYER1) celldata = PLAYER1;

    else if (var == PLAYER2)celldata = PLAYER2;

    else   celldata = EMPTY;

}

char AbstractHex::Cell::getCell() const
{
    // cout << "Celldata: " << celldata << endl;
    return celldata;
}

void AbstractHex::playGame()
{
    Boardsize = setBoardSize();
    gamemode = SelectGameMode();
}

char AbstractHex::SelectGameMode()
{
    char k = '0';
    while (k != 'a' && k != 'b')
    {
        cout << "\n A.Enter ( a or A) to play with computer mode\n"
            << " B.Enter ( b or B) to play with user to user\n";
        cin >> k;
    }
    return k;
}

int AbstractHex::play2player()
{

    bool xwin = false;
    bool owin = false;
    movearray();

    while (isEnd(xwin,owin))
    {
        xwin = playx();

        if (txt[0] == '0') return 0;

        if (xwin == false)
        {
            owin = playo();
            if (txt[0] == '0') return 0;
        }
       // cout << "countcell : " << countcells << endl;
    }
    
    return 0;
}

bool AbstractHex::isFull()
{
    int i, j = 0; /*This function controls the map full or not*/
    for (i = 0; i < Boardsize; i++)
    {
        while (j < i)
        {
            j++;
        }
        for (; j < Boardsize; j++)
        {
            cout << this->operator()(i,j);
            if (this->operator()(i,j)== EMPTY)
                return false;
        }
        cout << endl;
        j = 0;
    }
    return true;
}

string AbstractHex::XorOTURN(char player)
{
    string str, a, str2;

    if (player == PLAYER1)
        cout << "X plays (Enter '0' to return the menu ) : " << endl;
    if (player == PLAYER2)
        cout << "O plays (Enter '0' to return the menu ) :" << endl;;

    cin >> str;
    if (str[0] == '0') return str;
    cin >> str2;

    a = str + str2; // this line is simplfiy the load or save command's substr process
    commandarrange(str, str2);

    return a;
}

bool AbstractHex::isEmpty()
{
    if (this->operator()(number,letter) != EMPTY)/*If the input coordinant is not empty('.')it will return false*/
        return false;

    return true;
}

bool AbstractHex::xchecks()
{
    this->operator()(number,letter,PLAYER1); // Sets the X on the board if it's valid 
    Print(); // printing board to the console in every valid movement

    if (xsearching()) return true;

    else {

        DefaultvisitedBoard();
        return false;
    }
}

bool AbstractHex::ochecks()
{

    this->operator()(number,letter,PLAYER2);
    Print();

    if (osearching()) return true;

    else {

        DefaultvisitedBoard();
        return false;
    }
}

bool AbstractHex::xsearching()
{
    bool control = false;
    int a = 0;

    for (a = 0; a < Boardsize; a++) /* To find first x and others in A column*/
    {

        if (this->operator()(a,0) == PLAYER1)
        {
            number = a;
            //debugging : cout << "NUMBER : " << number << endl;

            if (xrecursion_check(number, 0)) {
                a = Boardsize;
                control = true;
            }
        }

    }
    return control;
}

bool AbstractHex::osearching()
{
    bool control = false;
    int a = 0;

    for (a = 0; a < Boardsize; a++) /* To find first x and others in A column*/
    {

        if (this->operator()(0,a) == PLAYER2)
        {

            number = a;
            //debugging : cout << "NUMBER : " << number << endl;

            if (orecursion_check(0, letter)) {
                a = Boardsize;
                control = true;
            }
        }

    }
    return control;
}

bool AbstractHex::xrecursion_check(int num, int let)
{
    int temp_x = 0, temp_y = 0;
    bool check = false;

    for (int i = 1; i < 7; i++)                                 /*in this loop */
    {                                           /*there are maximum 6 option which c and o can place so this recursive function provide that if one option is filled or not valid */
        if (7 - backtrace != i)                 /*then other option will be checked by program */
        {                                       /*This backtrace variable is prevent the moving back if the valid position option is after the moving back option this if statemnt jump the reverse move  */

            if (i == 1 && num != Boardsize - 1)
            {
                temp_y = let;
                temp_x = num + 1;
            }
            if (i == 2 && let != 0 && num != Boardsize - 1)
            {
                temp_y = let - 1;
                temp_x = num + 1;

            }
            if (i == 3 && let != Boardsize - 1)
            {
                temp_y = let + 1;
                temp_x = num;
            }

            if (i == 4 && let != 0)
            {
                temp_y = let - 1;
                temp_x = num;
            }

            if (i == 5 && num != 0 && let != Boardsize - 1)
            {
                temp_y = let + 1;
                temp_x = num - 1;
            }

            if (i == 6 && num != 0)
            {
                temp_y = let;
                temp_x = num - 1;
            }

        }

        if (this->operator()(temp_x,temp_y) == PLAYER1 && (!visited(temp_x, temp_y)))
        {
            check = true;
        }
        else check = false;

        if (check)
        {
            if (temp_y != Boardsize - 1) {

                backtrace = i;
                check = xrecursion_check(temp_x, temp_y);
            }

            if (check)
                i = 7;
        }
        //else return false;

    }
    return check;
}

bool AbstractHex::visited(int num, int let)
{
    if (visitedcheck[num][let] == 0)
    {
        visitedcheck[num][let] = -1;
        return false;
    }
    return true;
}

string AbstractHex::filenamearrange()
{
    string b = txt.substr(4, txt.size());//to separate first 4 letters from the file name string 
    return b;
}

bool AbstractHex::saveloadcheck(char player)
{
    if (txt.substr(0, 4) == "SAVE" || txt.substr(0, 4) == "save") {

        if (player == PLAYER1) writeToFile(PLAYER1, filenamearrange());
        else writeToFile(PLAYER2, filenamearrange());

        return true;
    }
    else if (txt.substr(0, 4) == "LOAD" || txt.substr(0, 4) == "load") {

        readFromFile(filenamearrange());
        return true;
    }
    else
        return false;
}

bool AbstractHex::playx()
{
    bool check = false;

    while (check != true)
    {
        txt = XorOTURN(PLAYER1);
        if (txt[0] == '0') break;
        if (!saveloadcheck(PLAYER1))
        {

            if(isEmpty())
            {
                check = true;
                if(xchecks()) return true;
            }
            else cerr<<"This place is not Empty"<< endl;
            /*try
            {
                check = CheckEmptyAndWrite();
                if(xchecks()) return true;
            }
            catch(Cell& e)
            {
                cerr<<"This place is not empty !!! \n";
            }*/
        }

    }
    return false;

}

bool AbstractHex::playo()
{
    bool check = false;


    while (check != true)
    {
        txt = XorOTURN(PLAYER2);
        if (txt[0] == '0')break;

        if (!saveloadcheck(PLAYER2))
        {
            if (isEmpty())//If entered coordinant is empty and valid then this if statement works
            {
                check = true;
                if (ochecks()) return true;
                //count++;
            }
            else cerr << "This place is not empty" << endl;
        }
    }
    return false;
}

bool AbstractHex::orecursion_check(int num, int let)
{
    int temp_x = 0, temp_y = 0;
    bool check = false;

    for (int i = 1; i < 7; i++)                                 /*in this loop */
    {                                           /*there are maximum 6 option which c and o can place so this recursive function provide that if one option is filled or not valid */
        if (7 - backtrace != i)                 /*then other option will be checked by program */
        {                                       /*This backtrace variable is prevent the moving back if the valid position option is after the moving back option this if statemnt jump the reverse move  */

            if (i == 1 && num != Boardsize - 1)
            {
                temp_y = let;
                temp_x = num + 1;
            }
            if (i == 2 && let != 0 && num != Boardsize - 1)
            {
                temp_y = let - 1;
                temp_x = num + 1;

            }
            if (i == 3 && let != Boardsize - 1)
            {
                temp_y = let + 1;
                temp_x = num;
            }

            if (i == 4 && let != 0)
            {
                temp_y = let - 1;
                temp_x = num;
            }

            if (i == 5 && num != 0 && let != Boardsize - 1)
            {
                temp_y = let + 1;
                temp_x = num - 1;
            }

            if (i == 6 && num != 0)
            {
                temp_y = let;
                temp_x = num - 1;
            }

        }

        if (this->operator()(temp_x,temp_y) == PLAYER2 && (!visited(temp_x, temp_y)))
        {
            check = true;
        }
        else check = false;

        if (check)
        {
            if (temp_x != Boardsize - 1) {

                backtrace = i;
                check = orecursion_check(temp_x, temp_y);
            }


            if (check)
                i = 7;
        }

    }
    return check;
}

void AbstractHex::commandarrange(const string& str, const string& str2)
{

    txt = str + str2;
    if (str != "LOAD" && str != "SAVE" && str != "save" && str != "load")
    {
        letter = (str[0] - '0') - 49;
        if (str2.size() == 2)
            number = 10 * (str2[1] - '0') - 1;
        else
            number = (str2[0] - '0') - 1;

       
        //lastMove();
    }
    else
    {
        txt = str + str2;
        saveloadcheck(PLAYER1);
    }

}

void AbstractHex::playcmp()
{
    string str1, str2;
    movearray();
    cout << "User Play : \n";
    cin >> str1 >> str2;
    play(str1, str2);
    //play();
}

void AbstractHex::play(const string let, const string num)
{

    commandarrange(let, num);

    if (isEmpty())//If entered coordinant is empty and valid then this if statement works
    {
        if (xchecks())cout << "XWINSSS";
    }
    else cerr << "This place is not empty" << endl;
}
/*void AbstractHex::play()
{
    if (letter == Boardsize - 3 && number != 0)hexCells[number - 1][letter + 2].setCell(PLAYER2);
    if (letter != Boardsize - 1 && number != Boardsize)
    {
        letter = letter + 1;
        number = number;
    }
    else
    {
        for (int i = 0; i < Boardsize; i++)
        {
            for (int j = 0; j < Boardsize; j++)
            {
                if (isEmpty())
                {
                    hexCells[i][j].setCell(PLAYER2);
                    j = Boardsize;
                    i = Boardsize;
                }
            }
        }
    }
    if (isEmpty())
    {
        hexCells[number][letter].setCell(PLAYER2);
    }
    else
    {
        for (int i = 0; i < Boardsize; i++)
        {
            for (int j = 0; j < Boardsize; j++)
            {
                if (isEmpty())
                {
                    hexCells[i][j].setCell(PLAYER2);
                    j = Boardsize;
                    i = Boardsize;
                }
            }
        }
    }

}*/

void AbstractHex::movearray() 
{
    moves = new int*[Boardsize*Boardsize];
    
        for (int i = 0; i < Boardsize*Boardsize ; i++)
        {
            moves[i] = new int[2];
        }
}

int AbstractHex::findscore()
{
    int countx = 0, counto = 0;

    if (xsearching()) return Boardsize * Boardsize * 3;
    if (osearching()) scorey = Boardsize * Boardsize * 3;

    for (int i = 0; i < Boardsize; i++)
    {
        for (int j = 0; j < Boardsize; j++)
        {
            if (this->operator()(i,j) == 'x' && (i == Boardsize - 4 || i == Boardsize - 3 || i == Boardsize - 2))
            {
                countx += 3;
            }
            if (this->operator()(i,j) == 'o' && (j == Boardsize - 4 || j == Boardsize - 3 || j == Boardsize - 2))
            {
                counto += 3;
            }
            if (this->operator()(i,j) == 'x' && (i == Boardsize - 1 || i == 0))
            {
                countx += 2;
            }
            if (this->operator()(i,j) == 'o' && (j == Boardsize - 1 || j == 0))
            {
                counto += 2;
            }
        }
    }
    scorex = countx;
    scorey = counto;

    return scorex;
}

bool AbstractHex ::operator==(const AbstractHex& object1)const
{
    if (markedcell == object1.markedcell)
        return true;

    else return false;

}

AbstractHex& AbstractHex :: operator=( AbstractHex& object)
{
    Boardsize = object.Boardsize;
    moves = object.moves;
    movecount = object.movecount;

    return *this;
}

AbstractHex& AbstractHex :: operator--()
{
    int temp1, temp2;

    temp1 = moves[lastmove][0];
    temp2 = moves[lastmove][1];

    this->operator()(temp1,temp2,EMPTY);

    moves[lastmove] = '\0';// nullptr doesn't work instead of NULL so I use this null character
    Print();
    
    return *this;
}

AbstractHex& AbstractHex :: operator--(int)
{
    int temp1, temp2;

    temp1 = moves[lastmove][0];
    temp2 = moves[lastmove][1];

    this->operator()(temp1,temp2,EMPTY);

    moves[lastmove] = '\0';// nullptr doesn't work instead of NULL so I use this null character
    Print();

    return *this;
}
bool AbstractHex:: CheckEmptyAndWrite()
{

        if (isEmpty())//If entered coordinant is empty and valid then this if statement works
        {
            return true;
            //count++;
        }

        else
            throw;
}
void AbstractHex :: operator() (int r, int c,char player)
{
    this->hexCells[r][c].setCell(player);
}
AbstractHex::~AbstractHex() 
{
//EMPTY
}