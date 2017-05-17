#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long


int main()
{
    freopen("test.in", "w", stdout);
    srand(time(NULL));

    int n = rand() % 10000; n++;
    int m = rand() % 300000; m++;

    cout << n << ' ' << m << '\n';
    for (int i = 1; i <= n; i++)
        cout << 1 + (rand() % 3) << ' ' << 1 + (rand() % 1000000000) << '\n';


    return 0;
}
