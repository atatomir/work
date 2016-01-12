#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define ll long long

int n, i, j, t, test;
ll p;
ll ans;
ll v[maxN];

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.ok","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        cerr << "S" << test << '\n';

        ans = 0;
        scanf("%d %lld", &n, &p);

        for (i = 1; i <= n; i++) {
            scanf("%lld", &v[i]);
            v[i] += v[i - 1];
        }

          for (i = 1; i <= n; i++)
            for (j = i; j <= n; j++)
                if (p >= v[j] - v[i - 1])
                    ans++;

        printf("Case #%d: %lld\n", test, ans);
    }


    return 0;
}
