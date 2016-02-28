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
#define pii pair<int, int>

#define maxN 10011
#define maxVal 20011

int n, i, j, lim;
pii P[maxN];
vector< pair<int, pii > > Q;
vector< pii > Upd;
vector< pii > Del;
map< pii, int > M;

int pos_upd, pos_del;
int aib[maxVal];
vector<int> list[maxN];
bool us[maxN];

int solution;

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add_aib(int pos, int v) {
    while (pos < maxVal) {
        aib[pos] += v;
        pos += zrs(pos);
    }
}

int sum_aib(int pos) {
    int ans = 0;

    while (pos) {
        ans += aib[pos];
        pos -= zrs(pos);
    }

    return ans;
}

void no_way() {
    printf("0");
    exit(0);
}

void dfs(int node) {
    us[node] = true;
    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];
        if (!us[to])
            dfs(to);
    }
}

void pair_swap(pii &A) {
    swap(A.first, A.second);
}

int main()
{
    //freopen("snake.in","r",stdin);

    if (scanf("%d", &n) == -1) while (true);

    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].first, &P[i].second);
        P[i].first += 10000;
        P[i].second += 10000;

        M[P[i]] = i;
    }

    sort(P + 1, P + n + 1);
    for (i = 1; i <= n; i = lim) {
        for (lim = i; lim <= n && P[i].first == P[lim].first; lim++);
        for (j = i; j < lim - 1; j += 2) {
            Q.pb( mp(P[i].first, mp(P[j].second, P[j + 1].second)) );
            solution += P[j + 1].second - P[j].second;

            list[ M[P[j]] ].pb( M[P[j + 1]] );
            list[ M[P[j + 1]] ].pb( M[P[j]] );
            //cerr << P[j].first << ' ' << P[j].second << ' ' << P[j + 1].first << ' ' << P[j + 1].second << '\n';
        }

        if (lim == i + 1) no_way();
    }

    for (i = 1; i <= n; i++) swap(P[i].first, P[i].second);

    sort(P + 1, P + n + 1);
    for (i = 1; i <= n; i = lim) {
        for (lim = i; lim <= n && P[i].first == P[lim].first; lim++);
        for (j = i; j < lim - 1; j += 2){
            Upd.pb(mp(P[j].second, P[i].first));
            Del.pb(mp(P[j + 1].second + 1, P[i].first));
            solution += P[j + 1].second - P[j].second;

            pair_swap(P[j]);
            pair_swap(P[j + 1]);

            list[ M[P[j]] ].pb( M[P[j + 1]] );
            list[ M[P[j + 1]] ].pb( M[P[j]] );

            pair_swap(P[j]);
            pair_swap(P[j + 1]);
            //cerr << P[j].second << ' ' << P[j].first << ' ' << P[j + 1].second << ' ' << P[j + 1].first << '\n';
        }

        if (lim == i + 1) no_way();
    }

    sort(Q.begin(), Q.end());
    sort(Upd.begin(), Upd.end());
    sort(Del.begin(), Del.end());

    for (i = 0; i < Q.size(); i++) {
        pair<int, pii > e = Q[i];

        while (pos_upd < Upd.size()) {
            pii now = Upd[pos_upd];
            if (now.first > e.first) break;
            pos_upd++;
            add_aib(now.second, +1);
        }

        while (pos_del < Upd.size()) {
            pii now = Del[pos_del];
            if (now.first > e.first) break;
            pos_del++;
            add_aib(now.second, -1);
        }

        if (sum_aib(e.second.second) - sum_aib(e.second.first - 1) != 2) no_way();
    }

    for (i = 1; i <= n; i++)
        if (list[i].size() != 2)
            no_way();

    dfs(1);

    for (i = 1; i <= n; i++)
        if (us[i] == false)
            no_way();


    printf("%d", solution);

    return 0;
}
