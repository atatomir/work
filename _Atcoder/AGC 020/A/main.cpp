#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int n, a, b, i;

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n >> a >> b;

    if ((a & 1) ^ (b & 1))
        cout << "Borys";
    else
        cout << "Alice";


    return 0;
}
