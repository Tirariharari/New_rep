#include <iostream>
#include <fstream>

#define FILE_IN  "tests/test7.in"
#define FILE_OUT "tests/test7.out"

using namespace std;

int **mat;
int size_m;
int res = 0;
bool *used;
int mini = -1;
int **way;

void Mat_new()
{
    int a;
    ifstream file_in(FILE_IN);
    file_in >> a;
    size_m=a;
    file_in >> a;
    size_m+=a+2;
    mat = new int* [size_m];
    for(int i=0; i<size_m; i++)
    {
        mat[i] = new int [size_m];
        for (int j=0; j<size_m;j++)
            mat[i][j] = 0;
    }
}

void Mat_in ()
{
    ifstream file_in(FILE_IN);

    int a, b, c;
    file_in >> a >> b;

    for(int i=0; i<a; i++)
    {
        file_in >> b;
        for(int j=0; j<b; j++)
        {
            file_in >> c;
            mat[0][i+2] = 1;
            mat[i+2][c+2] = 1;
            mat[c+2][1] = 1;
        }
    }
}

void recur(int versh)
{
    if (versh == 1)
        return;
    used[versh] = true;
    for (int i=0; i < size_m; i++)
    {
        if (mat[versh][i] && !used[i])
        {
            if (mini == -1)
                mini = mat[versh][i];
            else
                if (mini>mat[versh][i])
                    mini = mat[versh][i];
            way[versh][i] = 1;
            recur (i);
            return;
        }
    }
    mini = -2;
}

void cut_way()
{
    for (int i=0; i<size_m; i++)
        for (int j=0; j<size_m; j++)
        {
            if (way[i][j])
            {
                mat[i][j] -= mini;
                mat[j][i] += mini;
                way[i][j] = 0;
            }
        }
}

int main()
{
    Mat_new();
    way = mat;
    Mat_new();
    Mat_in();

//    for (int i=0; i<size_m; i++)
//    {
//        for (int j=0; j<size_m;j++)
//            cout << mat[i][j];
//        cout << endl;
//    }

    used = new bool[size_m];

    while (1)
    {
        mini=-1;
        for (int i=0; i<size_m; i++)
            used[i]=false;
        recur(0);
        cut_way();
        if (mini == -2)
            break;
        else
            res +=mini;
    }
    cout << res;

    int nado;
    ifstream potochek(FILE_OUT);
    potochek >> nado;

    cout << endl << "And needed: " << nado;

    return 0;
}
