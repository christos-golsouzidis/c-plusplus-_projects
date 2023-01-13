// sudoku3.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <time.h>


char field[10][9];
char digits[362880][9];


#include "Sudoku.cpp"

bool cmparray(char* dest, char* src, int startc, int endc);
void copyarray(char* dest, char* src);
__int64 rnd(void);


int main()
{
    unsigned int seed;
    char* a;
    grid field;
    series r;

    r.Shuffle();

    a = field.digits;

    seed = time(0);

    srand(seed);


    field.Fillgrid();

    field.Printgrid((char*)field.rows);
    std::cout << field.digits;
    std::cout << '\n';

    field.Removedigits(0x10);

    field.Printgrid((char*)field.rows);
    std::cout << field.digits;
    std::cout << '\n';

    field.solveit((char*)field.rows);

    field.Printgrid((char*)field.rows);
    std::cout << field.digits;
    //std::cout << '\n';

    std::cin >> a;
}

bool cmparray(char* dest, char* src, int startc, int endc)
{
    int c0 = startc;

    while (c0 < endc)
    {
        if (dest[c0] == src[c0])
            return false;

        c0++;
    }

    return true;
}

void copyarray(char* dest, char* src)
{
    int c0 = 0;

    while (c0 < 9)
    {
        dest[c0] = src[c0];

        c0++;
    }

}

__int64 rnd(void)
{
    __int64 in1;
    in1 = rand();
    in1 = in1 << 0x10;
    in1 ^= rand();
    in1 %= 0x58980;
    return in1;
}

