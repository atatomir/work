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

ll n, m;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> m;

    if (n == 1 && m == 1) {
        cout << 1;
        return 0;
    }

    if (n == 1 && m > 1) {
        cout << m - 2;
        return 0;
    }

    if (m == 1 && n > 1) {
        cout << n - 2;
        return 0;
    }

    cout << (n - 2) * (m - 2);


    return 0;
}
