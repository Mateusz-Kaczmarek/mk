#include <iostream>
#include <vector>

using namespace std;
using Vector = vector< vector<int> >;
Vector vecGlo;
void show(Vector field)
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            cout<<field[i][j]<< " ";;
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
}

void copyVec(Vector field)
{
    vecGlo = field;
}

bool canInsert(int value, int i, int j, vector< vector<int> > field, const vector<int> &clues)
{
    field[i][j] = value;
    vector<int>cluCord {(23-i), (6+i), j, (17-j)};
    int skyscrapers = 0;
    if(clues[cluCord[0]])
    {
        skyscrapers = clues[cluCord[0]];
        int maxHigh = field[i][0];
        int counter = 1;
        for(int k=1; k<6; k++)
        {
            if(field[i][k] > maxHigh)
            {
                counter++;
                maxHigh = field[i][k];
            }
        }
        if(skyscrapers < counter) return false;
    }

    if(clues[cluCord[1]])
    {
        skyscrapers = clues[cluCord[1]];
        int maxHigh = field[i][5];
        int counter = 1;
        for(int k=4; k>=0; k--)
        {
            if(field[i][k] > maxHigh)
            {
                counter++;
                maxHigh = field[i][k];
            }
        }
        if(skyscrapers < counter) return false;
    }
    return true;
}

void SolPuzRecu(Vector fieldN, const vector<int> &clues)
{
    Vector field = fieldN;
    bool canBreak = false;
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(field[i][j] == 0)
            {
                for(int k=1; k<7; k++)
                {
                    if(canInsert(k, i, j, field, clues))
                    {
                        field[i][j] = k;
                        SolPuzRecu(field, clues);
                        show(field);
                    }
                    if(k == 6)
                    {
                        canBreak = true;
                    }
                }
            }
            if(i == 5 && j == 5)
            {
                copyVec(field);
                canBreak = true;
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
    cout<<"             sol12121212   "<<&field<<endl;
}

vector<vector<int>> SolvePuzzle(const vector<int> &clues)
{
    vector<vector<int>> initGrid(6, vector<int>(6,0));
    SolPuzRecu(initGrid, clues);
    return vecGlo;
}

int main()
{
    static vector<int> clues =
  { 3, 2, 2, 3, 2, 1,
    1, 2, 3, 3, 2, 2,
    5, 1, 2, 2, 4, 3,
    3, 2, 1, 2, 2, 4 };

    show(SolvePuzzle(clues));
    return 0;
}
