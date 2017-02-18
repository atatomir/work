#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 4017

int n, i;
ll x, dif, aux, ans;
ll a[maxN];
deque< pair<int, int> > Q;


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%lld", &n, &x);
    for (i = 1; i <= n; i++) scanf("%lld", &a[i]), a[n + i] = a[i];

    ans = 1LL << 60;

    for (dif = 1; dif <= n; dif++) {
        while (!Q.empty()) Q.pop_back();

        aux = (dif - 1) * x;

        for (i = 1; i <= 2 * n; i++) {
            while (!Q.empty()) {
                if (Q.back().first < a[i]) break;
                Q.pop_back();
            }

            Q.push_back(mp(a[i], i));

            if (Q.front().second + dif <= i) Q.pop_front();

            if (i > n)
                aux += Q.front().first;
        }

        ans = min(ans, aux);
    }

    printf("%lld", ans);



    return 0;
}
