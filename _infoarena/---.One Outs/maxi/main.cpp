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
#define ll long long


int main()
{
    int n, i;
    int inf = 1000000000;

    n = 100000;

    ofstream fin("oneouts.in");

    fin << n << " 1" <<'\n';

    for (i = 1; i <= n; i++)
        fin << inf << ' ';
    fin << '\n';

    for (i = 1; i <= n; i++)
        fin << inf << ' ';
    fin << '\n';

    fin.close();



    return 0;
}
