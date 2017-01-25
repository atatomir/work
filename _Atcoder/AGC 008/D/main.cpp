#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 511 * 511

int n, i, j, cnt[maxN];
int x[maxN];
vector<int> be, af;

int sol[maxN];


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x[i]);
        sol[x[i]] = i;
        for (j = 1; j < i; j++) be.pb(i);
        for (j = i + 1; j <= n; j++) af.pb(i);
    }

    auto cmp = [](int a, int b)->bool const {
        return x[a] < x[b];
    };

    sort(be.begin(), be.end(), cmp);
    sort(af.begin(), af.end(), cmp);
    for (auto e : af) be.pb(e);

    reverse(be.begin(), be.end());
    for (i = 1; i <= n * n; i++) {
        if (sol[i]) {
            cnt[sol[i]]++;
            if (cnt[sol[i]] != sol[i]) {
                printf("No");
                return 0;
            }
        } else {
            sol[i] = be.back();
            be.pop_back();
            cnt[sol[i]]++;
        }
    }

    printf("Yes\n");
    for (i = 1; i <= n * n; i++) printf("%d ", sol[i]);

    return 0;
}
