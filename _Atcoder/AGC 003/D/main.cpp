#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

const int def = 3500;
const ll limit = 1LL << 50;

int n, i, j, c0, c1;
bool pr[maxN];
vector< pair<ll, ll> > divs, work;
ll x;
int ans;

map<ll, bool> M;

void pre() {
    ll i, j;

    for (i = 2; i <= def; i++) {
        if (pr[i]) continue;

        divs.pb(mp(i, 1LL * i * i * i));
        for (j = i * i; j <= def; j += i)
            pr[j] = true;
    }

    for (i = def + 1; i * i <= 10000000000LL; i++)
        M[i * i] = true;
}

void mult(ll& a, ll b) {
    if (limit / a < b)
        a = limit;
    else
        a *= b;
}

void add_number(ll x) {
    int i;
    ll op, aux;

    aux = x;

    for (auto e : divs) {
        while (x % e.second == 0) {
            x /= e.second;
            aux /= e.second;
        }

        while (aux % e.first == 0)
            aux /= e.first;

        if (aux < e.first) break;
    }


    op = 1LL;
    if (M[aux]) {
        mult(op, sqrt(aux));
    } else {
        mult(op, aux);
        mult(op, aux);
    }

    for (auto e : divs) {
        if (x % e.first == 0) {
            if (x % (e.first * e.first) == 0) {
                mult(op, e.first);
            } else {
                mult(op, e.first * e.first);
            }
        }

        if (x < e.first) break;
    }

    if (x < op)
        work.pb(mp(x, 0));
    else
        work.pb(mp(op, 1));
}

int main()
{
    //freopen("test.in","r",stdin);

    pre();
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &x);
        add_number(x);
    }

    sort(work.begin(), work.end());
    for (i = 0; i < work.size(); i = j) {
        c0 = c1 = 0;
        for (j = i; j < work.size(); j++) {
            if (work[i].first != work[j].first) break;
            if (work[j].second) c1++; else c0++;
        }

        if (work[i].first != 1)
            ans += max(c0, c1);
        else
            ans++;
    }

    printf("%d", ans);


    return 0;
}
