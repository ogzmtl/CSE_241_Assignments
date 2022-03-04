#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "function.h"

using namespace std;

int main()
{

    Hex obj1[5],obj2;
    char inp ='0';
    int count = 0,check=0,check2 = 0;

    while (inp == '0')
    {
        cout << "Welcome to HEX Game Menu\n"
            << "------------------------\n"
            << "1.Create a new game \n"
            << "2.Compare two games \n"
            << "3.Marked Cells\n"
            << "4.Undo Movement\n"
            << "5.Resume last game\n"
            << "0.Exit\n";
        cin >> inp;

        switch (inp)
        {
            case '0': "!!! GOOD BYE !!!!\n";
                inp = '.';
            break;

            case '1': 
                obj1[count].playGame();
                obj1[count].setBoard();

                cout << obj1[count]; // prints the default array using insertion << operator overloading

                if (obj1[count].gamemode == 'a')
                    inp = obj1[count].play2player() + '0';

                else obj1[count].playcmp();
                count++;
            break;

            case '2':
                cout << "Enter 2 game to compare marked cells" << endl;
                for (int i = 0; i < count; i++)
                {
                    cout << i+1 << ".Game"<<endl;
                }
                cin >> check >> check2;
                
                if (obj1[check-1] == obj1[check2-1])
                    cout << check <<".Game \n"<< check2 <<".Game "
                                  << "Marked Cells number are equal.\n";

                else cout << check << ".Game \n" << check2 << ".Game "
                    << "Marked Cells number are different." << endl;

            break;
            case '3' :
                cout << "Enter game to marked cells" << endl;
                for (int i = 0; i < count; i++)
                {
                    cout << i+1 << ".Game" << endl;
                }
                cin >> check;
                

            break;
            case '4':
                cout << "1.Prefix\n" << endl;
                cout << "2.Postfix\n" << endl;
                cin >> check;
                if (check == 1) --obj1[count-1];

                inp = '0';
            break;

            case '5':
                cout << obj1[count - 1]; // OVERLOADED << operation printing the Board array
                obj2 = obj1[count-1];
                obj2.play2player();
            break;

            default: cerr << "exit";
                inp = '0';
                break;
        }
    }

}

