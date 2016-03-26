#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(NULL));

    int n, m, i;
    n = 2000;
    m = 200000;

    ofstream fin("disp.in");

    fin << n << ' ' << m << '\n';
    for (i = 1; i <= n; i++)
        fin << rand() % 5000 << ' ' << rand() % 5000 << '\n';
    for (i = 1; i <= m; i++)
        fin << rand() % 5000 << ' ' << rand() % 5000 << ' ' << rand() % 5000 << ' ' << rand() % 5000 << '\n';


    fin.close();

    return 0;
}
