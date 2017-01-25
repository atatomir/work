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

#define maxN 1011
#define mod 1000000007

int n, i, j;
vector<int> divs[maxN];
int p[maxN];

ll ans = 1;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 2; i <= n; i++) {
        if (divs[i].empty()) {
            for (j = i; j <= n; j += i)
                divs[j].pb(i);
        }

        int aux = i;
        for (auto d : divs[i]) {
            while (aux % d == 0) {
                aux /= d;
                p[d]++;
            }
        }
    }

    for (i = 1; i <= n; i++)
        ans = (ans * (p[i] + 1)) % mod;

    printf("%lld", ans);



    return 0;
}
