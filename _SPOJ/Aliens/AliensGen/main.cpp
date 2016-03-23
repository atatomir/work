#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int n, i;

int main()
{
    ofstream fin("test.in");

    srand(time(NULL));

    n = 10000;
    fin << 20 << '\n';

    for (int t = 1; t <= 20; t++) {
        fin << n << '\n';
        for (i = 1; i <= n; i++) {
            fin << (rand() % 20000) - 10000 << '.' << rand() % 10 << ' ';
            fin << (rand() % 20000) - 10000 << '.' << rand() % 10 << '\n';
        }
    }

    fin.close();

    return 0;
}
