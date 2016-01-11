#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100000
#define maxVal 500011
#define ll long long

int n, i;
int v, p;
ll sum_p;

int lim = 500000;
vector<int> divs[maxVal];
ll chance[maxVal];
int prod_loc[maxVal];

int add_id;
int add_chance;
ll full_chance;

void compute_ciur() {
    int i, j;

    for (i = 1; i <= lim; i++)
        prod_loc[i] = 1;

    for (i = 2; i <= lim; i++) {
        if (divs[i].size() > 0)
            continue;

        prod_loc[i] = i;

        for (j = 2 * i; j <= lim; j += i) {
            divs[j].pb(i);

            prod_loc[j] *= i;
        }
    }
}

void back_add(int pas, ll prod) {
    if (pas == divs[add_id].size()) {
        if (prod == 1)
            return;

        chance[prod] += add_chance;
        return;
    }

    back_add(pas + 1, prod);
    prod *= 1LL * divs[add_id][pas];
    if (prod <= lim)
        back_add(pas + 1, prod);
}

void add_value(int v, int p) {
    if (divs[v].empty())
        divs[v].pb(v);

    add_id = v;
    add_chance = p;
    back_add(0, 1);
}

void solve() {
    int i, j;

    for (i = 2; i <= lim; i++) {
        if (prod_loc[i] != i || chance[i] == 0)
            continue;

        if (divs[i].size() == 0)
            divs[i].pb(i);

        ll aux = chance[i] * chance[i];
        if (divs[i].size() % 2 == 1)
            full_chance += aux;
        else
            full_chance -= aux;
    }

}

ll cmmdc(ll a, ll b) {
    if (a < b)
        swap(a, b);

    while (b) {
        a %= b;
        swap(a, b);
    }

    return a;
}

int main()
{
    freopen("porcjoc.in","r",stdin);
    freopen("porcjoc.out","w",stdout);

    //! compute ciur
    compute_ciur();

    //! add values
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &v, &p);
        sum_p += p;

        if (v == 1)
            continue;
        add_value(v, p);
    }

    //! compute answer

    full_chance = 0;
    solve();

    //! get answer
    sum_p *= sum_p;
    full_chance = sum_p  - full_chance;
    ll aux = cmmdc(full_chance, sum_p);

    full_chance /= aux;
    sum_p /= aux;

    printf("%lld/%lld", full_chance, sum_p);

    return 0;
}
