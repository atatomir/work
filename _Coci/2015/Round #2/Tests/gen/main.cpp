#include <iostream>
#include <fstream>

using namespace std;

int n = 10000;

int main()
{
    ofstream fout("10000.in");

    fout << n << '\n';
    for (int i = 1; i <= n; i++) fout << 'A';

    return 0;
}
