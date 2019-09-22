#include <iostream>
#include <vector>

using namespace std;

void show(vector< vector<int> > field)
{
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            cout<<field[i][j]<< " ";;
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
}

bool checkAround(int i, int j, vector< vector<int> > field)
{
    int checkCount = 0;
    for(int k=i-1; k<i-1+3; k++)
        for(int l=j-1; l<j-1+3; l++)
            if(k>=0 && k<10 && l>=0 && l<10)
            {
                if(field[k][l] == 1) checkCount++;
            }
    return checkCount > 1 ? false : true;
}


int checkWhichShip(int i, int j, vector< vector<int> >& field)
{
    vector< pair <int,int> > coord;
    coord.push_back(make_pair(i,j));

    //checking fields on right site
    bool checkAll = false;
    int y = j;
    int x_up = i-1;
    int x = i;
    int x_down = i+1;
    while(!checkAll)
    {
        y++;
        if(y < 10)
        {
            if(x_up >= 0){ if(field[x_up][y] == 1) return 0; }
            if(x_down < 10){ if(field[x_down][y] == 1) return 0; }
            if(field[x][y] == 1) coord.push_back(make_pair(x,y));
            else checkAll = true;
        }
        else checkAll = true;
    }

    //checking fields down
    bool checkAll2 = false;
    int x2 = i;
    int y_left = j-1;
    int y2 = j;
    int y_right = j+1;
    while(!checkAll2)
    {
        x2++;
        if(x2 < 10)
        {
            if(y_left >= 0){ if(field[x2][y_left] == 1) return 0; }
            if(y_right < 10){ if(field[x2][y_right] == 1) return 0; }
            if(field[x2][y2] == 1) coord.push_back(make_pair(x2,y2));
            else checkAll2 = true;
        }
        else checkAll2 = true;
    }

    //checking coordinates
    int ship_size = coord.size();
    int right_counter = 0;
    int down_counter = 0;
    for(auto v : coord)
    {
        if(v.first == i) right_counter++;
        if(v.second == j) down_counter++;
    }
    if(right_counter == ship_size || down_counter == ship_size)
    {
        for(auto v : coord)
        {
            field[v.first][v.second] = 0;
        }
        cout<<"size"<<ship_size<<endl;
        return ship_size;
    }
    else return 0;
}

bool validate_battlefield(vector< vector<int> > field)
{
    int _4fieldShip = 1;
    int _3fieldShip = 2;
    int _2fieldShip = 3;
    int _1fieldShip = 4;

    int sumOfUsedField = 20;
    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            if(field[i][j] == 1) sumOfUsedField--;
    if(sumOfUsedField != 0) return false;

    //check corrects of 1 field ship
    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            if(field[i][j] == 1)
            {
                if(checkAround(i, j, field))
                {
                    _1fieldShip--;
                    field[i][j] = 0;
                }
            }
    if(_1fieldShip != 0) return false;

    //check corrects of 2,3 and 4 fields ship
    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            if(field[i][j] == 1)
            {
                cout<<"fiels"<<i << j<<endl;
                switch(checkWhichShip(i, j, field))
                {
                case 2:
                   _2fieldShip--;
                   show(field);
                   break;
                case 3:
                    _3fieldShip--;
                    show(field);
                    break;
                case 4:
                    _4fieldShip--;
                    show(field);
                    break;
                default:
                    return false;
                    break;
                }
            }
    if(_2fieldShip == 0 && _3fieldShip == 0 && _4fieldShip == 0) return true;
    else return false;
}



int main()
{
      std::cout<<validate_battlefield( {
      vector<int> {1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
      vector<int> {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
      vector<int> {1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
      vector<int> {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
      vector<int> {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
      vector<int> {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      vector<int> {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
      vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} });

    return 0;
}
