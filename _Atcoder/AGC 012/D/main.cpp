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

#define maxN 200011
#define mod 1000000007

struct ball {
    int col;
    ll dim;
    int id;
};

int n, i, j, min_col, pos;
ll X, Y;
ball B[maxN], rez[maxN];
vector<int> list[maxN];

vector<ball> base, rest;
ball last;

bool us[maxN];
vector<int> cols;

ll fact[maxN];
ll inv_fact[maxN];
ll ans, aux;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void pre() {
    int i;

    fact[0] = 1;
    for (i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;
    inv_fact[n] = poww(fact[n], mod - 2);
    for (i = n - 1; i >= 1; i--)
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    inv_fact[0] = 1;
}


void dfs(int node) {
    us[node] = true;
    cols.pb(rez[node].col);
    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%lld%lld", &n, &X, &Y);
    pre();
    for (i = 1; i <= n; i++) scanf("%d%lld", &B[i].col, &B[i].dim), B[i].id = i, rez[i] = B[i];

    sort(B + 1, B + n + 1, [](const ball& a, const ball& b)->bool const {
        return mp(a.col, a.dim) < mp(b.col, b.dim);
    });

    for (i = 1; i <= n; i = j) {
        for (j = i; j <= n; j++) {
            if (B[i].col != B[j].col) break;
            if (B[i].dim + B[j].dim <= X) {
                list[B[i].id].pb(B[j].id);
                list[B[j].id].pb(B[i].id);
            }
        }
    }

    sort(B + 1, B + n + 1, [](const ball& a, const ball& b)->bool const {
        return a.dim < b.dim;
    });

    min_col = B[1].col;
    for (i = 1; i <= n; i++) {
        if (B[i].col == min_col)
            base.pb(B[i]);
        else
            rest.pb(B[i]);
    }

    reverse(base.begin(), base.end());
    pos = 0;

    for (auto act : base) {
        if (pos != 0) {
            list[act.id].pb(last.id);
            list[last.id].pb(act.id);
        }
        last = act;

        while (pos < rest.size()) {
            if (act.dim + rest[pos].dim > Y) break;
            list[act.id].pb(rest[pos].id);
            list[rest[pos].id].pb(act.id);
            pos++;
        }
    }

    ans = 1;
    for (int node = 1; node <= n; node++) {
        if (us[node]) continue;
        cols.clear();

        dfs(node);
        aux = fact[cols.size()];

        sort(cols.begin(), cols.end());
        for (i = 0; i < cols.size(); i = j) {
            for (j = i; j < cols.size(); j++)
                if (cols[i] != cols[j])
                    break;

            aux = (aux * inv_fact[j - i]) % mod;
        }

        ans = (ans * aux) % mod;
    }

    printf("%lld", ans);

    return 0;
}
