#ifndef ONED_H
#define ONED_H

#include "abstracthex.h"
using namespace std;

class OneD_Arr : public AbstractHex
{
    public:
        OneD_Arr();
        void Print();
        void reset();
        char operator() (int r, int c) const ;// virtual
        void operator() (int r, int c,char tPlayer);
        bool isEnd(bool xw, bool ow);
        int** lastMove();
        int numberOfMoves();
        void writeToFile(char last, string str);
        void readFromFile(string str);

        friend ostream& operator << (ostream& out, const OneD_Arr& obj);
        ~OneD_Arr();
    private:
        Cell* hexCells;

};

#endif