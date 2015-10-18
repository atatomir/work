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

ll n, p, i, dim; //! n culori luate cate p
ll ap[maxN];
ll how[maxN];

ll sum = 0;

bool notGood(ll ap, ll sum) {
    return ap > (sum / p) + 1;
}

int main()
{
    freopen("sirag.in","r",stdin);
    freopen("sirag.out","w",stdout);

    scanf("%lld%lld", &n, &p);
    for (i = 1; i <= n; i++) scanf("%lld", &ap[i]);
    sort(ap + 1, ap + n + 1);

    dim = 1;
    how[1] = 1;
    sum += ap[1];

    for (i = 2; i <= n; i++) {
        if (ap[i] == ap[dim]) {
            how[dim]++;
        } else {
            dim++;
            how[dim] = 1;
            ap[dim] = ap[i];
        }

        sum += ap[i];
    }

    while (notGood(ap[dim], sum)) {
        ll l_ap = ap[dim];
        ll l_how = how[dim];

        dim--;

        ll del = (l_ap - ap[dim]) * l_how;
        if (notGood(ap[dim], sum - del)) {
            how[dim] += l_how;
            sum -= del;
            continue;
        }

        del = (-sum + p * l_ap + (-l_how + p - 1) ) / (-l_how + p) - 1;
        sum -= del * l_how;
    }

    printf("%lld", sum);


    return 0;
}
