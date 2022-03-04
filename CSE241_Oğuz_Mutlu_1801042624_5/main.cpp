#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "abstracthex.h"
#include "derVector.h"
#include "oneD.h"

using namespace std;

int main()
{
    AbstractHex *ptr,*ptr2;
    derVector vec1[5];
    OneD_Arr arr1[5];
    int count = 0;
    int a;
    int inp,check,check2;

    try 
    {
        inp = MainMenu();
    }
    catch(int e)
    {
        cout<< "INVALID ENTERANCE"<<endl;
    }
    while (inp<=5 && inp>=1)
    {

        switch(inp)
        {
            case 0: cout << "!!!!! GOODBYE HAVE A HEALTHY DAY !!!!!"<<endl;
            break;

            case 1:

                 try
                 {
                    a = oned_vectorMenu();
                    if(a == 1)
                    {
                        ptr = &vec1[count];
                        ptr->playGame();
                        ptr->reset();
                        ptr->Print();
                        if(ptr->gamemode == 'a')
                        {
                            //ptr->playcmp()
                            count++;
                        }
                        else
                        {
                            ptr->play2player();
                            count++;
                        }
                    }
                    else if(a == 2)
                    {
                        ptr = &arr1[count];
                        ptr->playGame();
                        ptr->reset();
                        ptr->Print();
                        if(ptr->gamemode == 'a')
                        {
                            //ptr->playcmp()
                            count++;
                        }
                        else
                        {
                            ptr = &arr1[count];
                            ptr->play2player();
                            count++;
                        }
                    }
                }
                catch(int e)
                {
                    cout<<"INVALID ARGUMENT ( FOR VECTOR - 1D CLASS )\n\n"<<endl;
                    inp = 0;
                }
            break;

            case 2:
                try
                {    
                    
                    markedcellMenu(check,check2,count);
                    a = oned_vectorMenu();
                    if(a== 1)
                    {
                        ptr = &vec1[check-1];
                        ptr2 =&vec1[check-1];

                    }
                    else if(a == 2)
                    {
                        ptr = &arr1[check-1];
                        ptr2 = &arr1[check2-1];
                    }
                    
                    if (ptr == ptr2)
                        cout << check <<".Game \n"<< check2 <<".Game "
                             << "Marked Cells number are equal.\n";

                    else 
                        cout << check << ".Game \n" << check2 << ".Game "
                             << "Marked Cells number are different.\n" << endl;
                }
                catch(int e)
                {
                    cerr<< "INVALID ARGUMENT \n\n\n";
                }
            break;

            case 4:
                cout << "1.Prefix\n" << endl;
                cout << "2.Postfix\n" << endl;
                cin >> check;
                if(check > 0 && check < 3 && count == 1)
                {
                    if(a == 1)
                    {
                        ptr  =&vec1[count-1]; 
                        --ptr;
                    }
                    else if(a == 2)
                    {
                        ptr  =&arr1[count-1]; 
                        --ptr;
                    }
                }
                else cerr<<"Can't find any games which is played.\n";           
            break;
        }
 
          try {
            inp = MainMenu();
          }
          catch(int e)
          {
            cout<< "INVALID ENTERANCE"<<endl;
            inp = 0;
          }
    }
}