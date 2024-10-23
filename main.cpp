#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** r, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** r, const int rowCount, const int colCount);
void Sort(int** r, const int rowCount, const int colCount);
void Change(int** r, const int row1, const int row2, const int colCount);
void Calc(int** r, const int rowCount, const int colCount, int& S, int& k);
void CalcRecursively(int** r, int row, int col, const int rowCount, const int colCount, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));
    int Low = -8;
    int High = 42;
    int rowCount = 8;
    int colCount = 7;
    int** r = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        r[i] = new int[colCount];

    Create(r, rowCount, colCount, Low, High);
    Print(r, rowCount, colCount);

    Sort(r, rowCount, colCount);
    Print(r, rowCount, colCount);

    int S = 0;
    int k = 0;

    CalcRecursively(r, 0, 0, rowCount, colCount, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    Print(r, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] r[i];
    delete[] r;

    return 0;
}

void Create(int** r, const int rowCount, const int colCount, const int Low, const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            r[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** r, const int rowCount, const int colCount)
{
    cout << endl;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            cout << setw(4) << r[i][j];
        cout << endl;
    }
    cout << endl;
}

void Sort(int** r, const int rowCount, const int colCount)
{
    for (int i0 = 0; i0 < rowCount - 1; i0++)
        for (int i1 = 0; i1 < rowCount - i0 - 1; i1++)
            if ((r[i1][0] < r[i1 + 1][0])
                || (r[i1][0] == r[i1 + 1][0] && r[i1][1] < r[i1 + 1][1])
                || (r[i1][0] == r[i1 + 1][0] && r[i1][1] == r[i1 + 1][1] && r[i1][2] > r[i1 + 1][2]))
                Change(r, i1, i1 + 1, colCount);
}

void Change(int** r, const int row1, const int row2, const int colCount)
{
    int tmp;
    for (int j = 0; j < colCount; j++)
    {
        tmp = r[row1][j];
        r[row1][j] = r[row2][j];
        r[row2][j] = tmp;
    }
}

void CalcRecursively(int** r, int row, int col, const int rowCount, const int colCount, int& S, int& k)
{
    if (row == rowCount)
        return;
    if (col == colCount)
    {
        CalcRecursively(r, row + 1, 0, rowCount, colCount, S, k);
        return;
    }

    if (r[row][col] % 2 == 0 || !(row % 2 == 0 && col % 2 == 0))
    {
        S += r[row][col];
        k++;
        r[row][col] = 0;
    }

    CalcRecursively(r, row, col + 1, rowCount, colCount, S, k);
}
