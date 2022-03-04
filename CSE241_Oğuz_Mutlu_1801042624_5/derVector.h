#ifndef DERIVEVECTOR_H
#define DERIVEVECTOR_H

#include "abstracthex.h"
using namespace std;

	class derVector : public AbstractHex
	{
	    public : 
	    derVector();
	    void Print();
	    void reset();
	    void writeToFile(char last, string str);
	    void readFromFile(string str);
	    char operator() (int r, int c) const ;// virtual
	    void operator() (int r, int c,char tPlayer);
	    bool isEnd(bool xw, bool ow);
	    int** lastMove();
	    int numberOfMoves();
	    friend ostream& operator << (ostream& out, const derVector& obj);
	    ~derVector();

	    private:
	        vector<vector<Cell> >hexCells;
	};
#endif