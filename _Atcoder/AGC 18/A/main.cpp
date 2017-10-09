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

int n, k, i, ans, x, bg;

int gcd(int a, int b) {
    if (a < b) swap(a, b);

    while (b > 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n >> k; ans = 0;
    for (i = 1; i <= n; i++) {
        cin >> x;
        ans = gcd(ans, x);
        bg = max(bg, x);
    }

    if (k % ans == 0 && bg >= k)
        cout << "POSSIBLE";
    else
        cout << "IMPOSSIBLE";



    return 0;
}
