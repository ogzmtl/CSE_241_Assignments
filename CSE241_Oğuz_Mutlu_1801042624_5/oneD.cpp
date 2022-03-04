#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "abstracthex.h"
#include "oneD.h"

using namespace std;

OneD_Arr::OneD_Arr()
{
    //EMPTY
}

void OneD_Arr::Print()
{
    cout<<*this;
}
void OneD_Arr::reset()
{
     hexCells = (Cell*)malloc(sizeof(Cell)*Boardsize*Boardsize);

    for (int i = 0; i < Boardsize; i++)
    {
        for (int j = 0; j < Boardsize; j++)
        {
            this->operator()(i,j,EMPTY);
        }
    }
}
char OneD_Arr :: operator() (int r, int c) const
{
    return hexCells[(r*Boardsize)+c].getCell(); 
}
void OneD_Arr :: operator() (int r, int c,char tPlayer)
{
    hexCells[(r*Boardsize)+c].setCell(tPlayer);
}
ostream& operator << (ostream& out, const OneD_Arr& obj)
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
bool OneD_Arr :: isEnd(bool xw, bool ow)
{
    if(!isFull() && !xw && !ow) return true;
    
    return false;
}
int** OneD_Arr::lastMove()
{
    moves[movecount][0] = letter;
    moves[movecount][1] = number;
    movecount++;

    lastmove = movecount-1;

  return moves;
}
int OneD_Arr::numberOfMoves()
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
void OneD_Arr::readFromFile(string str)
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
void OneD_Arr::writeToFile(char last, string str)
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
OneD_Arr :: ~OneD_Arr()
{
    delete[] hexCells;
}