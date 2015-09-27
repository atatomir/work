#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 6015
#define base 17

int n, k, i, dim;
char s[maxN];
int _hash[maxN], _pow;
int dp[maxN];
int Answer;

int main()
{
    freopen("per.in","r",stdin);
    freopen("per.out","w",stdout);

    scanf("%d%d\n%s", &n, &k, s + 1);

    for (dim = 1; dim * k <= n; dim++) {
        _pow = 1;

        for (i = 1; i < dim; i++) {
            dp[i] = 0;
            _hash[i] = (_hash[i - 1] * base + s[i] ) ;//% mod;
            _pow = (_pow * base) ;//% mod;
        }

        for (i = dim; i <= n; i++) {
            _hash[i] = _hash[i - 1];
            _hash[i] -= (_pow * s[i - dim]) ;//% mod;
            //if (_hash[i] < 0) _hash[i] += mod;

            _hash[i] = (_hash[i] * base + s[i]) ;//% mod;

            dp[i] = 1;
            if (_hash[i] == _hash[i - dim]) dp[i] = dp[i - dim] + 1;

            if (dp[i] >= k) Answer++;
        }
    }

    printf("%d", Answer);

    return 0;
}
