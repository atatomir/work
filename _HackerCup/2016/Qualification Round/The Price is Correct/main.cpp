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

int test, t, i, pos;
int n;
ll p;
ll v[maxN];
ll ans;

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        ans = 0;

        cerr << "Solving " << test << '\n';

        scanf("%d%lld", &n, &p);
        for (i = 1; i <= n; i++) {
            scanf("%lld", &v[i]);
            v[i] += v[i - 1];
        }

        pos = 0;
        for (i = 1; i <= n; i++) {
            if (v[i] - v[i - 1] > p) {
                pos = i;
                continue;
            }

            while (v[i] - v[pos] > p) pos++;
            ans += i - pos;
        }

        printf("Case #%d: %lld\n", test, ans);
    }


    return 0;
}
