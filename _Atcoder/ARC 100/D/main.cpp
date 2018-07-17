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

const int maxN = 200011;

int n, i, p, a, b, c;
ll s[maxN];
int le[maxN], ri[maxN];
ll ans = 1LL << 60;

ll check(ll a, ll b, ll c) {
    ll A = s[a];
    ll B = s[b] - s[a];
    ll C = s[c] - s[b];
    ll D = s[n] - s[c];

    ll M = max(max(A, B), max(C, D));
    ll m = min(min(A, B), min(C, D));

    return M - m;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
    }

    p = 0;
    for (i = 1; i <= n; i++) {
        while (p + 1 <= i && s[i] - s[p + 1] >= s[p]) p++;
        le[i] = p;
    }

    p = n + 1;
    for (i = n; i >= 1; i--) {
        while (p - 1 >= i && s[p - 1] - s[i - 1] >= s[n] - s[p - 1]) p--;
        ri[i] = p;
    }

    for (i = 2; i + 2 <= n; i++) {
        b = i;
        for (a = le[i]; a <= le[i] + 1 && a < b; a++) {
            for (c = max(b + 1, ri[i + 1] - 1); c <= ri[i + 1]; c++) {
                ans = min(ans, check(a, b, c));
            }
        }
    }

    cout << ans;


    return 0;
}
