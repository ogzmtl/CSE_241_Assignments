#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "abstracthex.h"
#include "derVector.h"

using namespace std;

derVector :: derVector():AbstractHex()
{
    //EMPTY
}
void derVector::Print()
{
    cout<<*this;
}
void derVector::reset()
{
	hexCells.reserve(Boardsize);	
     hexCells.resize(Boardsize);

    for (int i = 0; i < Boardsize; i++)
    {
        hexCells[i].resize(Boardsize);

        for (int j = 0; j < Boardsize; j++)
        {
            this->operator()(i,j,EMPTY);
        }
    }
}
ostream& operator << (ostream& out, const derVector& obj)
{
    int a = 0;
    char c ='A';

    out<<" ";
   for(int i = 0 ; i < obj.Boardsize ; i++)
    {
        out<< c;
        c++;
        out<< " ";
        
    }
    out<<"\n";
    for (int i = 0; i < obj.Boardsize; i++)
    {
        
        out << i+1;
        out<<" ";
        while (a < i)
        {
            out << " ";
            a++;
        }
        for (int j = 0; j < obj.Boardsize; j++)
        {   
            out << obj(i,j);
            out << ' ';
        }
        out << endl;
        a = 0;
    }
    return out;
}
void derVector::writeToFile(char last, string str)
{
    ofstream file;
    file.open(str.c_str());
      if (file.is_open())
      {
        file<<Boardsize<<"\n";
        file << *this;
        file.close();
      }
      else
        cerr<<"FILE ERROR";
    //loadgame(map,msize,str);
}
char derVector :: operator() (int r, int c) const
{
    return hexCells[r][c].getCell(); 
}
void derVector :: operator() (int r, int c,char tPlayer)
{
    hexCells[r][c].setCell(tPlayer);
}
bool derVector :: isEnd(bool xw, bool ow)
{
    if(!isFull() && !xw&& !ow) return true;
    else false;
}
int** derVector::lastMove()
{
    moves[movecount][0] = letter;
    moves[movecount][1] = number;
    movecount++;

    lastmove = movecount-1;

  return moves;
}
int derVector::numberOfMoves()
{
    int count = 0;
    for (int i = 0; i < Boardsize; i++)
    {
        for (int j = 0; j < Boardsize; j++)
        {
            if (this->operator()(i,j) != '.')
                count++;
        }
    }
    markedcell = count;

    return markedcell;
}
void derVector::readFromFile(string str)
{
    string line;
    ifstream  myfile(str.c_str());
    int count = 0, i = 0,j = 0;
    const int ZERO = 0;

        if (myfile.is_open())
        {
            getline (myfile,line);// reads Boardsize
            Boardsize = line[ZERO]-'0';

            getline (myfile,line);//reads the column identity(A B C D E ...)

            while ( getline (myfile,line) )
            {
                i++;
                while(line[i] != '\0')
                {
                    if(line[i] != ' ')
                    {
                        this->operator()(count,j,line[i]);
                        j++;
                    }
                    i++;
                }
                count++;
                i=0;
                j=0;    
            }
            myfile.close();
        }
        else cerr<<"There is no such a file\n";

}
derVector:: ~derVector()
{
    for (int i = 0; i < Boardsize; i++)
    {
        delete[] visitedcheck[i];
    }

    for (int i = 0; i < Boardsize * Boardsize; i++)
    {
        delete[] moves[i];
    }
    delete[] moves;
}