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

#define maxN 55

int n, p, i, x;
ll ans;
bool any;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> p; ans = 1LL << n - 1;
    for (i = 1; i <= n; i++) {
        cin >> x;
        if (x & 1) any = true;
    }

    if (any == false) {
        if (p == 0)
            cout << ans * 2;
        else
            cout << 0;

        return 0;
    }

    cout << ans;


    return 0;
}
