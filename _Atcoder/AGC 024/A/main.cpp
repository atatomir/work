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

ll A, B, C, K;

int main()
{
    freopen("test.in","r",stdin);

    cin >> A >> B >> C >> K;
    if (K & 1)
        cout << B - A;
    else
        cout << A - B;


    return 0;
}
