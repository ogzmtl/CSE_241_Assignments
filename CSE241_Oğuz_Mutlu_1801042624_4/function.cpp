#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "function.h"

Hex::Hex()
{
    //EMPTY
}

Hex::Hex(int size)
{
    size = setBoardSize();
    Boardsize = size;
}

Hex ::Hex(const Hex& copy) { Boardsize = copy.Boardsize; }

void Hex::DefaultvisitedBoard()
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

void Hex::setBoard() // Arrange setting process of given size board 
{
    hexCells = new Cell*[Boardsize];

    for (int i = 0; i < Boardsize; i++)
    {
        hexCells[i] = new Cell[Boardsize];

        for (int j = 0; j < Boardsize; j++)
        {
            hexCells[i][j].setCell(EMPTY);
        }
    }
}

void Hex::BoardPrint()
{
    int a = 0;
    char c ='A';
    
    cout<<" ";
   for(int i = 0 ; i < Boardsize ; i++)
	{
		cout<< c;
		c++;
		cout<< " ";
		
	}
	cout<<"\n";
    for (int i = 0; i < Boardsize; i++)
    {
    	
    	cout << i+1;
    	cout<<" ";
        while (a < i)
        {
            cout << " ";
            a++;
        }
        for (int j = 0; j < Boardsize; j++)
        {
            cout << hexCells[i][j].getCell();
            cout << ' ';
        }
        cout << endl;
        a = 0;
    }
}

const int Hex::setBoardSize()// this function returns the size of map (width and height)
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

bool Hex::checkBoardSize(int size)
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

inline void Hex::Cell::setCell(char var)
{

    if (var == PLAYER1) celldata = PLAYER1;

    else if (var == PLAYER2)celldata = PLAYER2;

    else   celldata = EMPTY;

}

char Hex::Cell::getCell()
{
    // cout << "Celldata: " << celldata << endl;
    return celldata;
}

void Hex::playGame()
{
    Boardsize = setBoardSize();
    gamemode = SelectGameMode();
}

char Hex::SelectGameMode()
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

int Hex::play2player()
{

    bool xwin = false;
    bool owin = false;
    movearray();

    while (!isFull() && !xwin && !owin)
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

bool Hex::isFull()
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
            if (hexCells[i][j].getCell() == EMPTY)
                return false;
        }
        j = 0;
    }
    return true;
}

string Hex::XorOTURN(char player)
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

bool Hex::isEmpty()
{

    if (hexCells[number][letter].getCell() != EMPTY)/*If the input coordinant is not empty('.')it will return false*/
        return false;

    return true;
}

bool Hex::xchecks()
{

    hexCells[number][letter].setCell(PLAYER1); // Sets the X on the board if it's valid 
    BoardPrint(); // printing board to the console in every valid movement

    if (xsearching()) return true;

    else {

        DefaultvisitedBoard();
        return false;
    }
}

bool Hex::ochecks()
{

    hexCells[number][letter].setCell(PLAYER2);
    BoardPrint();

    if (osearching()) return true;

    else {

        DefaultvisitedBoard();
        return false;
    }
}

bool Hex::xsearching()
{
    bool control = false;
    int a = 0, j = 0;

    for (a = 0; a < Boardsize; a++) /* To find first x and others in A column*/
    {

        if (hexCells[a][0].getCell() == PLAYER1)
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

bool Hex::osearching()
{
    bool control = false;
    int a = 0, j = 0;

    for (a = 0; a < Boardsize; a++) /* To find first x and others in A column*/
    {

        if (hexCells[0][a].getCell() == PLAYER2)
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

bool Hex::xrecursion_check(int num, int let)
{
    int temp_x = 0, temp_y = 0;
    bool check = false;

    for (int i = 1; i < 7; i++)									/*in this loop */
    {											/*there are maximum 6 option which c and o can place so this recursive function provide that if one option is filled or not valid */
        if (7 - backtrace != i)					/*then other option will be checked by program */
        {										/*This backtrace variable is prevent the moving back if the valid position option is after the moving back option this if statemnt jump the reverse move  */

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

        if (hexCells[temp_x][temp_y].getCell() == PLAYER1 && (!visited(temp_x, temp_y)))/*returns the function if other move is valid but when it enter this if statement it always return 1. I didn't solve this problem*/
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

bool Hex::visited(int num, int let)
{
    if (visitedcheck[num][let] == 0)
    {
        visitedcheck[num][let] = -1;
        return false;
    }
    return true;
}

void Hex::savegame(char last, string str)
{
    ofstream FILE;

    FILE.open(str.c_str());

    FILE << *this; //OVERLOAD << OPERATOR BY WRITING IN FILE

    FILE.close();
    //loadgame(map,msize,str);
}

string Hex::filenamearrange()
{
    string b = txt.substr(4, txt.size());//to separate first 4 letters from the file name string 
    return b;
}

void Hex::loadgame(string str)
{
    ifstream FILELOAD(str.c_str());
    string c;
    int a = 0;
    int b = 0, j = 0;

    if (FILELOAD.is_open())
    {

            getline(FILELOAD, c);

        while (getline(FILELOAD, c))
        {
            while (j != Boardsize)
            {
                hexCells[a][b].setCell(c[j]);
                b++;
                j++;

            }
            a++;
            b = 0;
            j = 0;
        }


        FILELOAD.close();
    }
    else cerr << "THERE IS NO SUCH A FILE \n";

}

bool Hex::saveloadcheck(char player)
{
    if (txt.substr(0, 4) == "SAVE" || txt.substr(0, 4) == "save") {

        if (player == PLAYER1) savegame(PLAYER1, filenamearrange());
        else savegame(PLAYER2, filenamearrange());

        return true;
    }
    else if (txt.substr(0, 4) == "LOAD" || txt.substr(0, 4) == "load") {

        loadgame(filenamearrange());
        return true;
    }
    else
        return false;
}

bool Hex::playx()
{
    bool check = false;


    while (check != true)
    {
        txt = XorOTURN(PLAYER1);
        if (txt[0] == '0') break;
        if (!saveloadcheck(PLAYER1))
        {
            if (isEmpty())//If entered coordinant is empty and valid then this if statement works
            {
                check = true;
                if (xchecks()) return true;
                //count++;
            }
            else cerr << "This place is not empty" << endl;
        }
    }
    return false;

}

bool Hex::playo()
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

bool Hex::orecursion_check(int num, int let)
{
    int temp_x = 0, temp_y = 0;
    bool check = false;

    for (int i = 1; i < 7; i++)									/*in this loop */
    {											/*there are maximum 6 option which c and o can place so this recursive function provide that if one option is filled or not valid */
        if (7 - backtrace != i)					/*then other option will be checked by program */
        {										/*This backtrace variable is prevent the moving back if the valid position option is after the moving back option this if statemnt jump the reverse move  */

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

        if (hexCells[temp_x][temp_y].getCell() == PLAYER2 && (!visited(temp_x, temp_y)))
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

void Hex::commandarrange(const string& str, const string& str2)
{

    txt = str + str2;
    if (str != "LOAD" && str != "SAVE" && str != "save" && str != "load")
    {
        letter = (str[0] - '0') - 49;
        if (str2.size() == 2)
            number = 10 * (str2[1] - '0') - 1;
        else
            number = (str2[0] - '0') - 1;

       
        movementcopy();
    }
    else
    {
        txt = str + str2;
        saveloadcheck(PLAYER1);
    }

}

void Hex::playcmp()
{
    string str1, str2;
    movearray();
    cout << "User Play : \n";
    cin >> str1 >> str2;
    play(str1, str2);
    //play();
}

void Hex::play(const string let, const string num)
{
    bool check = false;

    commandarrange(let, num);

    if (isEmpty())//If entered coordinant is empty and valid then this if statement works
    {
        if (xchecks())cout << "XWINSSS";
    }
    else cerr << "This place is not empty" << endl;
}
/*void Hex::play()
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

void Hex::countmarkedcell()
{
    int count = 0;
    for (int i = 0; i < Boardsize; i++)
    {
        for (int j = 0; j < Boardsize; j++)
        {
            if (hexCells[i][j].getCell() != '.')
                count++;
        }
    }
    markedcell = count;
}

void Hex::movementcopy()
{
    moves[movecount][0] = letter;
    moves[movecount][1] = number;
    movecount++;

    lastmove = movecount-1;
  
}

void Hex::movearray()
{
    moves = new int*[Boardsize*Boardsize];
    
        for (int i = 0; i < Boardsize*Boardsize ; i++)
        {
            moves[i] = new int[2];
        }
}

int Hex::findscore()
{
    int countx = 0, counto = 0;

    if (xsearching()) return Boardsize * Boardsize * 3;
    if (osearching()) scorey = Boardsize * Boardsize * 3;

    for (int i = 0; i < Boardsize; i++)
    {
        for (int j = 0; j < Boardsize; j++)
        {
            if (hexCells[i][j].getCell() == 'x' && (i == Boardsize - 4 || i == Boardsize - 3 || i == Boardsize - 2))
            {
                countx += 3;
            }
            if (hexCells[i][j].getCell() == 'o' && (j == Boardsize - 4 || j == Boardsize - 3 || j == Boardsize - 2))
            {
                counto += 3;
            }
            if (hexCells[i][j].getCell() == 'x' && (i == Boardsize - 1 || i == 0))
            {
                countx += 2;
            }
            if (hexCells[i][j].getCell() == 'o' && (j == Boardsize - 1 || j == 0))
            {
                counto += 2;
            }
        }
    }
    scorex = countx;
    scorey = counto;

    return scorex;
}

bool Hex ::operator==(const Hex& object1)const
{
    if (markedcell == object1.markedcell)
        return true;

    else return false;

}

Hex& Hex :: operator=( Hex& object)
{
    Boardsize = object.Boardsize;
    hexCells = object.hexCells;
    moves = object.moves;
    movecount = object.movecount;

    return *this;
}

Hex& Hex :: operator--()
{
    int temp1, temp2;

    temp1 = moves[lastmove][0];
    temp2 = moves[lastmove][1];

    hexCells[temp1][temp2].setCell(EMPTY);

    moves[lastmove] = '\0';// nullptr doesn't work instead of NULL so I use this null character
    BoardPrint();
    
    return *this;
}

Hex& Hex :: operator--(int)
{
    int temp1, temp2;

    temp1 = moves[lastmove][0];
    temp2 = moves[lastmove][1];

    hexCells[temp1][temp2].setCell(EMPTY);

    moves[lastmove] = '\0';// nullptr doesn't work instead of NULL so I use this null character
    BoardPrint();

    return *this;
}

ostream& operator << (ostream& out, const Hex& obj)
{
    int a = 0;

    out << obj.Boardsize << "\n";

    for (int i = 0; i < obj.Boardsize; i++)
    {
        while (a < i)
        {
            out << ' ';
            a++;
        }
        for (int j = 0; j < obj.Boardsize; j++)
        {
            out << obj.hexCells[i][j].getCell();
            out << ' ';
        }
        cout << endl;
        a = 0;
    }

    return out;
}

Hex::~Hex() 
{
    for (int i = 0; i < Boardsize; i++)
    {
        delete[] visitedcheck[i];
        delete[] hexCells[i];
    }
    delete[] hexCells;
    delete[] visitedcheck;

    for (int i = 0; i < Boardsize * Boardsize; i++)
    {
        delete[] moves[i];
    }
    delete[] moves;
}
