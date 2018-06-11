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

ll A, B, C, x, y, mini;
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    cin >> A >> B >> C >> x >> y;
    mini = min(x, y);
    x -= mini;
    y -= mini;

    ans = x * min(A, 2LL * C) + y * min(B, 2LL * C) + mini * min(2LL * C, A + B);
    cout << ans;

    return 0;
}
