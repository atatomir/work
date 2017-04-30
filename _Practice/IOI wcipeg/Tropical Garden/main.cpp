#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 300011
#define inf 1000000007

int n, m, P, i, x, y, q, cnt, rest;
vector<int> list[maxN];
int to[maxN];
vector<int> from[maxN];

queue<int> Q;
int dist[maxN];
int per;

vector< pair<int, int> > data;
map< pair<int, int> , int > M, biggest; // rest, mod
vector<int> mods;

int get_to(int node, int to) {
    if (list[to][0] == node)
        return to + n;
    return to;
}

void add_source(int S) {
    int i;

    for (i = 1; i <= n; i++) dist[i] = -1;
    per = inf; dist[S] = 0;
    while (!Q.empty()) Q.pop();

    Q.push(S);
    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        for (auto aux : from[node]) {
            if (aux == S) {
                per = dist[node] + 1;
                continue;
            }

            dist[aux] = dist[node] + 1;
            Q.push(aux);
        }
    }

    for (i = 1; i <= n; i++) {
        if (dist[i] == -1) continue;
        data.pb(mp(dist[i], per));
    }
}

void compute_data() {
    int i, node, aux;

    for (node = 1; node <= n; node++) {
        aux = get_to(node, list[node][0]);
        to[node] = aux;
        from[aux].pb(node);

        if (list[node].size() > 1)
            aux = get_to(node, list[node][1]);
        else
            aux = get_to(node, list[node][0]);
        to[n + node] = aux;
        from[aux].pb(n + node);
    }

    add_source(P);
    add_source(P + n);

    for (auto e : data) {
        M[e]++;
        mods.pb(e.second);
    }

    sort(data.begin(), data.end());
    data.resize(unique(data.begin(), data.end())- data.begin());
    for (auto e : data) {
        M[e] += M[mp(e.first - e.second, e.second)];
        biggest[mp(e.first % e.second, e.second)] = e.first / e.second;
    }

    sort(mods.begin(), mods.end());
    mods.resize(unique(mods.begin(), mods.end()) - mods.begin());
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &m, &P); P++;
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y); x++; y++;
        list[x].pb(y);
        list[y].pb(x);
    }

    compute_data();

    scanf("%d", &q);
    for (i = 1; i <= q; i++) {
        scanf("%d", &x);
        int ans = 0;

        for (auto d : mods) {
            cnt = x / d;
            rest = x % d;

            cnt = min(cnt, biggest[mp(rest, d)]);
            rest += cnt * d;

            ans += M[mp(rest, d)];
        }

        printf("%d ", ans);
    }



    return 0;
}
