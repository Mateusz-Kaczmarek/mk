#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>

using namespace std;

void copyTab(int currTab[9][9], int tab[9][9])
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
          currTab[i][j] = tab[i][j];
        }
    }
}
void show(int tab[9][9])
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            cout<< tab[i][j] << " ";
            if(j == 2 || j == 5)
            {
                cout<< "| ";
            }
        }
        cout<<endl;
        if(i == 2 || i == 5)
        {
            cout<< "------+-------+------" << endl;
        }
    }

}

void fillTab(int tab[9][9])
{
   string str;
    cout<<"podaj pola sudoku w konwencji wiersz kolumna liczba bez spacji"<<endl;
    cout<<"lub wpisz 'k' aby zakonczyc"<<endl;
   while(true)
   {
        getline(cin, str);
        if(str[0] == 'k')
        {
            break;
        }
        int i = stoi(str.substr(0,1));
        int j = stoi(str.substr(1,1));
        int liczba = stoi(str.substr(2,1));
        tab[i-1][j-1] = liczba;
   }
}

bool canInsert(int value, int i, int j, int tab[9][9])
{
    int iq = (i/3)*3;
    int jq = (j/3)*3;
    for(int k=0; k<9; k++)
    {
        if(tab[i][k] == value)
        {
            return false;
        }
    }

    for(int k=0; k<9; k++)
    {
        if(tab[k][j] == value)
        {
            return false;
        }
    }

    for(int k=0; k<3; k++)
    {
        for(int l=0; l<3; l++)
        {
            if(tab[k+iq][l+jq] == value)
            {
                return false;
            }
        }
    }
    return true;

}

void solve2(int tab[9][9])
 {
    int currTab[9][9];
    bool canBreak = false;
    copyTab(currTab, tab);
        for(int i=0; i<9; i++)
        {
            for(int j=0; j<9; j++)
            {
                if(tab[i][j] == 0)
                {
                    for(int k=1; k<10; k++)
                    {
                        if(canInsert(k, i, j, currTab))
                        {
                            currTab[i][j] = k;
                            solve2(currTab);
                        }
                        if(k==9)
                        {
                            canBreak = true;
                        }
                    }
                }
                if(i == 8 && j == 8 && canBreak)
                {
                    show(currTab);
                    cout<<endl;
                }
                if(canBreak)
                {
                    break;
                }
            }
            if(canBreak)
            {
                break;
            }

        }
 }

int main()
{
    srand(time(NULL));
    int tab[9][9] = { {0,0,9,8,0,4,0,0,0}, {0,0,4,0,0,0,2,1,9}, {0,5,0,0,0,6,0,0,0},
                      {3,0,7,0,0,1,0,4,0}, {0,0,0,0,0,0,0,0,0}, {0,4,0,7,0,0,6,0,3},
                      {0,0,0,6,0,0,0,9,0}, {9,7,3,0,0,0,5,0,0}, {0,0,0,1,0,7,3,0,0} };
    //fillTab(tab);
    show(tab);
    cout<<endl;
    solve2(tab);
    return 0;
}
