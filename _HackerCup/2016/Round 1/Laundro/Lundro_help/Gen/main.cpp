#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back


int main()
{

    ofstream fout("input.in");

    int t = 50;
    int L = 1000000;
    int n = 100000;
    int m = 1000000000;
    int D = 1000000000;

    fout << t << '\n';
    for (int i = 1; i <= t; i++) {
        fout << L << ' ' << n << ' ' << m << ' ' << D << '\n';
        for (int j = 1; j <= n; j++)
            fout << 1000000000 << '\n';
        fout << '\n';
    }


    return 0;
}
