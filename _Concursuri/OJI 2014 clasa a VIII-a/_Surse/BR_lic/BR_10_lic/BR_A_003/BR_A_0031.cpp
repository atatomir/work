#include <cstdio>
using namespace std;
struct poz {int lin, col;};
int m, n, a[410][410], maxp, v[28], p;
poz w, ww;
int read ()
{
    int v, i, j;
    char c;
    FILE *in = fopen ("ferma.in", "r");
    fscanf (in, "%d %d %d", &v, &m, &n);
    for (i = 1; i <= m; ++i)
    {fscanf (in, "%c", &c);
    for (j = 1; j <= n; ++j)
    {
        fscanf (in, "%c", &c);
        a[i][j] = (int) c - 96;
    }}
    fclose (in);
    return v;
}
void fillx (int x, int y, int val)
{
    if (a[x][y] == val)
    {
        a[x][y] = -val;
        ++p;
        if (a[x - 1][y] == -a[x][y])
        {fillx (x - 1, y, val);
        a[x - 1][y] = val;}
        if (a[x][y + 1] == -a[x][y])
        {fillx (x, y + 1, val);
        a[x][y + 1] = val;}
        if (a[x + 1][y] == -a[x][y])
        {fillx (x + 1, y, val);
        a[x + 1][y] = val;}
        if (a[x][y - 1] == -a[x][y])
        {fillx (x, y - 1, val);
        a[x][y - 1] = val;}
    }
}
void fill (int x, int y, int val)
{
    if (a[x][y] == val)
    {
        a[x][y] *= -1;
        ++p;
        fill (x - 1, y, val);
        fill (x, y + 1, val);
        fill (x + 1, y, val);
        fill (x, y - 1, val);
    }
}
void write1 (int val)
{
    FILE *out = fopen ("ferma.out", "w");
    fprintf (out, "%d\n", val);
    fclose (out);
}
void write2 (int x, int y, char v)
{
    FILE *out = fopen ("ferma.out", "w");
    fprintf (out, "%d %d\n%c\n", x, y, v);
    fclose (out);
}
void solve (int v)
{
    int i, j, aux;
    for (i = 1; i <= m; ++i)
    for (j = 1; j <= n; ++j)
    if (a[i][j] > 0)
    {
        fill (i, j, a[i][j]);
        if (p > maxp)
        maxp = p;
        p = 0;
    }
    if (v == 1)
    write1 (maxp);
    else
    {
        for (i = 1; i <= m; ++i)
        for (j = 1; j <= n; ++j)
        {
            if (a[i][j] == a[i][j + 2] && a[i][j] != a[i][j + 1])
            {
                aux = a[i][j + 1];
                a[i][j + 1] = a[i][j];
                fillx (i, j, a[i][j]);
                a[i][j] *= -1;
                a[i][j + 1] = aux;
                if (p > maxp)
                {
                    w.lin = i;
                    w.col = j + 1;
                    maxp = p;
                    ww.lin = i;
                    ww.col = j;
                }
                p = 0;
            }
            if (a[i][j] == a[i + 2][j] && a[i][j] != a[i + 1][j])
            {
                aux = a[i + 1][j];
                a[i + 1][j] = a[i][j];
                fillx (i, j, a[i][j]);
                a[i][j] *= -1;
                a[i + 1][j] = aux;
                if (p > maxp)
                {
                    maxp = p;
                    w.lin = i + 1;
                    w.col = j;
                    ww.lin = i;
                    ww.col = j;
                }
                p = 0;
            }
        }
        write2 (w.lin, w.col, (char)(a[ww.lin][ww.col] * -1 + 96));
    }
}
int main()
{
    int v;
    v = read ();
    solve (v);
    return 0;
}
