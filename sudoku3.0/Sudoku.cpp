
#include <cstdlib>


extern "C"
{
    char bitscanr(short);
    void zeromem(char*, __int64);

}

void Zeromem(char* c, __int64 n)
{

    zeromem(c, n);

}

class series
{
public:
    char index[9];


    void Shuffle(void)
    {
        unsigned char hash[10];

        char aindx = 0;
        char bindx = 0;
        int c0 = 0, c1 = 0, c8, lim, max;
        const int INVALID = -1;

        max = 9;

        while (c1 < max)
        {
            hash[c1] = c1 + 1;
            c1++;
        }

        hash[c1] = INVALID;
        lim = max;

        while (c0 < max)
        {

            c8 = rand();
            c8 %= lim;
            c1 = 0;
            while (c1 <= c8)
            {
                bindx = aindx;
                aindx = hash[aindx];

                c1++;
            }

            index[c0] = aindx;

            hash[bindx] = hash[aindx];
            hash[aindx] = INVALID;
            c0++;
            aindx = 0;
            bindx = 0;
            lim--;
        }
    }

    void bwrite(series dest, series src)
    {
        int c0 = 0;

        while (c0 < 9)
        {
            dest.index[c0] = src.index[c0];
            c0++;
        }
    }





};

class triplet
{
public:
    char x;
    char y;
    char n;
};

class grid
{
public:
    series rows[9];
    short sfield[81];
    char digits[0x180];

public:
    void Fillgrid(void)
    {
        int c0, c1;
        int q0, r0;

        c0 = 0;
        while (c0 < 9)
        {
            rows[c0] = { 0 };
            c0++;
        }

        rows[0].Shuffle();
        c0 = 1;
        c1 = 0;
        while (c0 < 8)
        {

            if (c0 <= 2)
            {
                rows[c0].Shuffle();
                if (wmatch((char*) & rows[0], c0))
                    c0++;

            }
            else if (c0 == 3 || c0 == 6)
            {
                rows[c0].Shuffle();
                if (vmatch((char*) & rows[0], c0))
                    c0++;

            }
            else
            {
                rows[c0].Shuffle();
                q0 = c0 / 3;
                r0 = c0 % 3;
                if (vmatch((char*) & rows[0], c0) && wmatch((char*) & rows[3*q0], r0))
                    c0++;

            }
            c1++;
            if (c1 > 0x2ffff)
            {
                c1 = 0;
                c0 = 4;
            }
        }
        // fill the last row
        filllastrow((char*)rows);

        // final check
        if (!finalallnumbers((char*)rows))
            c0 = 0;
        else
            c0 = 1;

    }

    void Printgrid(char* field)
    {
        int x, y, m;

        m = 0;
        y = 0;
        while (y < 9)
        {
            x = 0;
            while (x < 18)
            {
                if (!(x & 1))
                {
                        digits[18 * y + x] = (char)0x30 + field[m];

                        m++;
                }
                else
                {
                    if (x == 17)
                    {
                        digits[18 * y + x] = '\n';

                    }
                    else
                    {
                        digits[18 * y + x] = 0x20;
                    }
                }

                x++;
            }
            y++;
        }
        digits[18 * y] = 0;
    }

    void Removedigits(int retries)
    {
        int cluenum = 81;
        int mincluenum = 0;
        int comple = 0;
        int x, y;
        triplet removed[81] = { 0 };

        char* rowch;

        rowch = (char*)rows;


        while (cluenum > 78)
        {
            x = rand() % 9;
            y = rand() % 9;

            if (rowch[9 * y + x] == 0)
                continue;

            removed[81 - cluenum].x = x;
            removed[81 - cluenum].y = y;
            removed[81 - cluenum].n = rowch[9 * y + x];
            cluenum--;
            rowch[9 * y + x] = 0;
        }

        while (true)
        {
            while (true)
            {
                x = rand() % 9;
                y = rand() % 9;

                if (rowch[9*y + x] == 0)
                    continue;

                removed[81 - cluenum].x = x;
                removed[81 - cluenum].y = y;
                removed[81 - cluenum].n = rowch[9 * y + x];
                cluenum--;
                rowch[9 * y + x] = 0;

                if (!solveunique(rowch))
                    break;

            }

            cluenum++;
            x = removed[81 - cluenum].x;
            y = removed[81 - cluenum].y;
            rowch[9 * y + x] = removed[81 - cluenum].n;


            if (cluenum == mincluenum)
                comple++;
            else
            {
                mincluenum = cluenum;
                comple = 0;
            }
            if (comple == retries)
            {
                break;
            }
        }
    }

    bool solveunique(char* pfield)
    {
        int countsolutions = 0;
        int movecnt = 0;
        char branz[81] = { 0 };
        triplet sol[81][9] = { 0 };
        char field[81];

        int m = 0;
        while (m < 81)
        {
            field[m] = pfield[m];
            m++;
        }

        while (true)
        {
            createallspos(field);

            if (!existallnumbers(field))
            {
                if (!assumpt_undo(field, sol, branz, &movecnt))
                {
                    if(countsolutions == 1)
                        return true;
                    return false;
                }

            }
            else
            {
                findlowestfreq(sol[movecnt]);


            }

            field[sol[movecnt][branz[movecnt]].x + 9 * sol[movecnt][branz[movecnt]].y] = sol[movecnt][branz[movecnt]].n;
            movecnt++;

            if (finalallnumbers(field))
            {
                if (countsolutions == 1)
                    return false;
                countsolutions++;

                if (!assumpt_undo(field, sol, branz, &movecnt))
                {
                    if (countsolutions == 1)
                        return true;
                    return false;
                }

                field[sol[movecnt][branz[movecnt]].x + 9 * sol[movecnt][branz[movecnt]].y] = sol[movecnt][branz[movecnt]].n;
                movecnt++;

            }
        }
    }

    void solveit(char* pfield)
    {
        int countsolutions = 0;
        int movecnt = 0;
        char branz[81] = { 0 };
        triplet sol[81][9] = { 0 };
        char field[81];

        int m = 0;
        while (m < 81)
        {
            field[m] = pfield[m];
            m++;
        }

        while (true)
        {
            createallspos(field);

            if (!existallnumbers(field))
            {
                if (!assumpt_undo(field, sol, branz, &movecnt))
                {
                    __debugbreak();
                }

            }
            else
            {
                findlowestfreq(sol[movecnt]);


            }

            field[sol[movecnt][branz[movecnt]].x + 9 * sol[movecnt][branz[movecnt]].y] = sol[movecnt][branz[movecnt]].n;
            movecnt++;

            if (finalallnumbers(field))
            {
                int m = 0;
                while (m < 81)
                {
                    pfield[m] = field[m];
                    m++;
                }
                return;
            }
        }
    }


    bool assumpt_undo(char* field, triplet sol[][9], char* branz, int* mc)
    {
        int r;

        sol[mc[0]]->n = 0;
        sol[mc[0]]->x = 0;
        sol[mc[0]]->y = 0;

        while (true)
        {
            mc[0]--;
            if (mc[0] < 0)
                return false;

            r = counttriplets(sol[mc[0]]);
            if (!r)
                __debugbreak();
            if (r == 1)
            {
                field[9* sol[mc[0]]->y + sol[mc[0]]->x] = 0;
                sol[mc[0]]->n = 0;
                sol[mc[0]]->x = 0;
                sol[mc[0]]->y = 0;
                continue;
            }
            while (r > 1)
            {
                field[9 * sol[mc[0]]->y + sol[mc[0]]->x] = 0;
                sol[mc[0]][0].n = sol[mc[0]][1].n;
                sol[mc[0]][0].x = sol[mc[0]][1].x;
                sol[mc[0]][0].y = sol[mc[0]][1].y;
                sol[mc[0]][1].n = 0;
                sol[mc[0]][1].x = 0;
                sol[mc[0]][1].y = 0;

                r--;
            }
            return true;

        }

        return false;
    }

    bool finalallnumbers(char* field)
    {
        int m;
        m = 0;
        while (m < 9)
        {
            if (!finalallnumbers_row(field, m))
                return false;
            if (!finalallnumbers_col(field, m))
                return false;
            if (!finalallnumbers_win(field, m))
                return false;
            m++;
        }
        return true;
    }

    bool finalallnumbers_row(char* field, int row)
    {
        int m;
        short exist = 0;
        __int16 z[] = { 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };

        m = 0;
        while (m < 9)
        {
            exist |= z[field[9 * row + m]];
            m++;
        }
        if (exist == 0x1FF)
            return true;
        return false;
    }

    bool finalallnumbers_col(char* field, int col)
    {
        int m;
        short exist = 0;
        __int16 z[] = { 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };

        m = 0;
        while (m < 9)
        {
            exist |= z[field[9 * m + col]];
            m++;
        }
        if (exist == 0x1FF)
            return true;
        return false;
    }

    bool finalallnumbers_win(char* field, int win)
    {
        int m0, m1, xx, yy;
        short exist = 0;
        __int16 z[] = { 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };
        xx = win % 3;
        yy = win / 3;

        m0 = 0;
        while (m0 < 3)
        {
            m1 = 0;
            while (m1 < 3)
            {
                exist |= z[field[9 * (3 * yy + m1) + 3 * xx + m0]];
                m1++;
            }
            m0++;
        }
        if (exist == 0x1FF)
            return true;
        return false;
    }

    int findlowestfreq(triplet* output)
    {
        int m, r;
        int minr = 9;
        triplet minout[10] = { 0 };
        triplet* pfnout;

        m = 0;
        while (m < 9)
        {
            output[m] = {0};
            m++;
        }
        m = 0;
        while (m < 9)
        {
            pfnout = findlowestfreq_row(m);
            r = counttriplets(pfnout);
            if (r)
            {
                if (r == 1)
                {
                    output[0].n = pfnout->n;
                    output[0].x = pfnout->x;
                    output[0].y = pfnout->y;
                    return 1;
                }
                if (minr > r)
                {
                    minr = r;
                    while (r > 0)
                    {
                        r--;
                        minout[r].n = pfnout->n;
                        minout[r].x = pfnout->x;
                        minout[r].y = pfnout->y;
                        pfnout++;
                    }
                }
            }
            pfnout = findlowestfreq_col(m);
            r = counttriplets(pfnout);
            if (r)
            {
                if (r == 1)
                {
                    output[0].n = pfnout->n;
                    output[0].x = pfnout->x;
                    output[0].y = pfnout->y;
                    return 1;
                }
                if (minr > r)
                {
                    minr = r;
                    while (r > 0)
                    {
                        r--;
                        minout[r].n = pfnout->n;
                        minout[r].x = pfnout->x;
                        minout[r].y = pfnout->y;
                        pfnout++;
                    }
                }
            }
            pfnout = findlowestfreq_win(m);
            r = counttriplets(pfnout);
            if (r)
            {
                if (r == 1)
                {
                    output[0].n = pfnout->n;
                    output[0].x = pfnout->x;
                    output[0].y = pfnout->y;
                    return 1;
                }
                if (minr > r)
                {
                    minr = r;
                    while (r > 0)
                    {
                        r--;
                        minout[r].n = pfnout->n;
                        minout[r].x = pfnout->x;
                        minout[r].y = pfnout->y;
                        pfnout++;
                    }
                }
            }
            m++;
        }
        r = minr;
        while (r > 0)
        {
            r--;
            output->n = minout[r].n;
            output->x = minout[r].x;
            output->y = minout[r].y;
            output++;
        }

        return minr;
    }

    int counttriplets(triplet* trp)
    {
        int r = 0;

        while (true)
        {
            if(trp->n == 0)
                return r;
            trp += 1;
            r++;
        }

    }

    triplet* findlowestfreq_row(int row)
    {
        int x, n, k;
        triplet a[10] = { 0 };
        __int16 z[] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };
        int freq[9] = { 0 };
        int freqcnt;

        n = 0;
        while (n < 9)
        {
            x = 0;
            while (x < 9)
            {
                if (z[n] & sfield[9 * row + x])
                    freq[n]++;
                x++;
            }
            n++;
        }
        k = 0;
        n = 0;
        while (n < 9)
        {
            if (freq[n] == 1)
            {
                x = 0;
                while (x < 9)
                {
                    if (sfield[9 * row + x] & z[n])
                    {
                        a[0].x = x;
                        a[0].y = row;
                        a[0].n = n+1;
                        return a;
                    }
                    x++;
                }
            }
            n++;
        }
        freqcnt = 2;
        while (freqcnt < 9)
        {
            n = 0;
            while (n < 9)
            {
                if (freq[n] == freqcnt)
                {
                    x = 0;
                    while (x < 9)
                    {
                        if (sfield[9 * row + x] & z[n])
                        {
                            a[k].x = x;
                            a[k].y = row;
                            a[k].n = n + 1;
                            k++;
                        }
                        x++;
                    }
                    return a;
                }
                n++;
            }
            freqcnt++;
        }
        return a;
    }

    triplet* findlowestfreq_col(int col)
    {
        int y, n, k;
        triplet a[10] = { 0 };
        __int16 z[] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };
        int freq[9] = { 0 };
        int freqcnt;

        n = 0;
        while (n < 9)
        {
            y = 0;
            while (y < 9)
            {
                if (z[n] & sfield[9 * y + col])
                    freq[n]++;
                y++;
            }
            n++;
        }
        k = 0;
        n = 0;
        while (n < 9)
        {
            if (freq[n] == 1)
            {
                y = 0;
                while (y < 9)
                {
                    if (sfield[9 * y + col] & z[n])
                    {
                        a[0].x = col;
                        a[0].y = y;
                        a[0].n = n + 1;
                        return a;
                    }
                    y++;
                }
            }
            n++;
        }
        freqcnt = 2;
        while (freqcnt < 9)
        {
            n = 0;
            while (n < 9)
            {
                if (freq[n] == freqcnt)
                {
                    y = 0;
                    while (y < 9)
                    {
                        if (sfield[9 * y + col] & z[n])
                        {
                            a[k].x = col;
                            a[k].y = y;
                            a[k].n = n + 1;
                            k++;
                        }
                        y++;
                    }
                    return a;
                }
                n++;
            }
            freqcnt++;
        }
        return a;
    }

    triplet* findlowestfreq_win(int win)
    {
        int x, y, n, k;
        int xx = win % 3;
        int yy = win / 3;
        triplet a[10] = { 0 };
        __int16 z[] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };
        int freq[9] = { 0 };
        int freqcnt;

        n = 0;
        while (n < 9)
        {
            x = 0;
            while (x < 3)
            {
                y = 0;
                while (y < 3)
                {
                    if (z[n] & sfield[9 * (3 * yy + y) + 3 * xx + x])
                        freq[n]++;
                    y++;
                }
                x++;
            }
            n++;
        }
        k = 0;
        n = 0;
        while (n < 9)
        {
            if (freq[n] == 1)
            {
                x = 0;
                while (x < 3)
                {
                    y = 0;
                    while (y < 3)
                    {
                        if (z[n] & sfield[9 * (3 * yy + y) + 3 * xx + x])
                            freq[n]++;
                        y++;
                    }
                    x++;
                }
            }
            n++;
        }
        freqcnt = 2;
        while (freqcnt < 9)
        {
            n = 0;
            while (n < 9)
            {
                if (freq[n] == freqcnt)
                {
                    x = 0;
                    while (x < 3)
                    {
                        y = 0;
                        while (y < 3)
                        {
                            if (z[n] & sfield[9 * (3 * yy + y) + 3 * xx + x])
                                freq[n]++;
                            y++;
                        }
                        x++;
                    }
                    return a;
                }
                n++;
            }
            freqcnt++;
        }
        return a;
    }

    bool existallnumbers(char* field)
    {
        int m;
        m = 0;
        while (m < 9)
        {
            if (!existallnumbers_row(field, m))
                return false;
            if (!existallnumbers_col(field, m))
                return false;
            if (!existallnumbers_win(field, m))
                return false;
            m++;
        }
        return true;
    }

    bool existallnumbers_row(char* field, int row)
    {
        int m;
        short exist = 0;
        __int16 z[] = { 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };

        m = 0;
        while (m < 9)
        {
            exist |= z[field[9 * row + m]];
            exist |= sfield[9 * row + m];
            m++;
        }
        if (exist == 0x1FF)
            return true;
        return false;
    }

    bool existallnumbers_col(char* field, int col)
    {
        int m;
        short exist = 0;
        __int16 z[] = { 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };

        m = 0;
        while (m < 9)
        {
            exist |= z[field[9 * m + col]];
            exist |= sfield[9 * m + col];
            m++;
        }
        if (exist == 0x1FF)
            return true;
        return false;
    }

    bool existallnumbers_win(char* field, int win)
    {
        int m0, m1, xx, yy;
        short exist = 0;
        __int16 z[] = { 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };
        xx = win % 3;
        yy = win / 3;

        m0 = 0;
        while (m0 < 3)
        {
            m1 = 0;
            while (m1 < 3)
            {
                exist |= z[field[9 * (3 * yy + m1) + 3 * xx + m0]];
                exist |= sfield[9 * (3 * yy + m1) + 3 * xx + m0];
                m1++;
            }
            m0++;
        }
        if (exist == 0x1FF)
            return true;
        return false;
    }

    void createallspos(char* field)
    {
        int x, y;

        x = 0;
        while (x < 81)
        {
            sfield[x] = 0;
            x++;
        }
        x = 0;
        while (x < 9)
        {
            y = 0;
            while (y < 9)
            {
                if (field[9 * y + x] == 0)
                    createspos(field, y, x);
                y++;
            }
            x++;
        }
    }

    void createspos(char* field, int y, int x)
    {
        int n;
        __int16 z[] = { 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };

        n = 1;
        while (n < 10)
        {
            field[9 * y + x] = n;
            if (check_h(field, x, y) == true &&
                check_v(field, x, y) == true &&
                check_w(field, x, y) == true)
                sfield[9 * y + x] |= z[n];
            n++;
        }

        field[9 * y + x] = 0;
    }

    bool check_h(char* field, int x, int y)
    {
        int m = 0;
        while (m < 9)
        {
            if (x == m)
            {
                m++;
                continue;
            }
            if (field[9 * y + x] == field[9 * y + m])
                return false;
            m++;
        }
        return true;
    }

    bool check_v(char* field, int x, int y)
    {
        int m = 0;
        while (m < 9)
        {
            if (y == m)
            {
                m++;
                continue;
            }
            if (field[9 * y + x] == field[9 * m + x])
                return false;
            m++;
        }
        return true;
    }

    bool check_w(char* field, int x, int y)
    {
        int m0, m1;
        int lx, ly, kx, ky;

        lx = x / 3;
        ly = y / 3;
        kx = x % 3;
        ky = y % 3;

        m0 = 0;
        while (m0 < 3)
        {
            m1 = 0;
            while (m1 < 3)
            {
                if (kx == m0 && ky == m1)
                {
                    m1++;
                    continue;
                }
                if (field[9 * y + x] == field[9 * (3 * ly + m1) + 3 * lx + m0])
                    return false;
                m1++;
            }
            m0++;
        }
        return true;
    }


    void filllastrow(char* region)
    {
        __int16 a[9] = { 0 };
        int x, y;

        __int16 z[] = { 0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };

        x = 0;
        while (x < 9)
        {
            y = 0;
            while (y < 8)
            {
                a[x] |= z[region[9 * y + x]];

                y++;
            }

            x++;
        }

        x = 0;
        while (x < 9)
        {

            region[72 + x] = bitscanr(a[x] ^ 0x1ff);

            x++;
        }

    }

    bool vmatch(char* region, int lange)
    {
        int m = 0;
        int x;

        while (m < lange)
        {
            x = 0;
            while (x < 9)
            {
                if (region[9 * lange + x] == region[9 * m + x])
                {
                    return false;
                }
                x++;
            }
            m++;
        }

        return true;
    }

    bool wmatch(char* region, int lange)
    {
        char a[3][9] = { 0 };
        int m = 0, n = 0;
        int x = 0, y = 0;
        int lim = 3 * lange + 3;

        while (y < 3)
        {
            x = 0;
            while (x < 3)
            {
                a[0][3 * y + x] = region[9 * y + x];
                a[1][3 * y + x] = region[9 * y + 3 + x];
                a[2][3 * y + x] = region[9 * y + 6 + x];
                x++;
            }
            y++;
        }

        m = 1;
        while (m < lim)
        {
            n = 0;
            while (n < m)
            {
                if (a[0][n] == a[0][m] || a[1][n] == a[1][m] || a[2][n] == a[2][m])
                {
                    return false;
                }
                n++;
            }
            m++;
        }



        return true;
    }



};
