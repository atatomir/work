#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    ofstream fout("rk.in");
    srand(time(NULL));

    long n = 200000;

    fout << n << '\n';
    for(long i=1;i<=n;i++) fout << rand()%2000000000 << ' '; fout << '\n';

    long q = 1000;
    fout << q << '\n';
    for(long i=1;i<=q;i++) {
        long k = rand()%33;
        fout << rand()%(1<<k) << ' ' << k << '\n';
    }

    return 0;
}
