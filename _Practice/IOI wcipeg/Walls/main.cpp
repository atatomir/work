#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 266

int n, i, m, k, j, l;
vector<int> memb;
vector<int> aux;
vector<int> reg[maxN];

//! list for dual graph
vector<int> list[maxN];
map< pair<int, int>, int > other_part;

queue<int> Q;
int work[maxN];
int whole[maxN];

void add_from(int start) {
    int i;

    while (!Q.empty()) Q.pop();
    memset(work, 0, sizeof(work));

    for (auto now_reg : reg[start]) {
        if (work[now_reg]) continue;

        work[now_reg] = 1;
        Q.push(now_reg);
    }

    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();

        for (int to : list[node])
            if (work[to] == 0)
                work[to] = work[node] + 1, Q.push(to);
    }

    for (i = 1; i <= m; i++)
        whole[i] += work[i] - 1;
}

int main()
{
    freopen("test.in","r",stdin);

    other_part.clear();

    scanf("%d%d", &m, &n);

    scanf("%d", &l);
    memb.resize(l);
    for (i = 0; i < l; i++) scanf("%d", &memb[i]);

    for (i = 1; i <= m; i++) {
        scanf("%d", &k);
        aux.resize(k);

        for (j = 0; j < k; j++) {
            scanf("%d", &aux[j]);
            reg[aux[j]].pb(i);
        }

        aux.pb(aux[0]);
        for (j = 0; j < k; j++) {
            int a = aux[j];
            int b = aux[j + 1];

            if (a > b) swap(a, b);
            int o_p = other_part[mp(a,b)];

            if (o_p != 0) {
                list[i].pb( o_p );
                list[ o_p ].pb(i);
            } else {
                other_part[mp(a,b)] = i;
            }
        }
    }

    /*vector<int> db1, db2;
    db1.clear();
    db2.clear();*/

    for (auto now : memb)
        add_from(now);

    int best = 1;
    for (i = 2; i <= m; i++)
        if (whole[best] > whole[i])
            best = i;

    printf("%d\n%d\n", whole[best], best);

    //! check if ok
    /*int ans = 0;

    reg[n + 1].pb(best);
    add_from(n + 1);

    for (int e : memb) {
        int val = 1000000000;

        for (int fr : reg[e])
            val = min(val, work[fr]);

        ans += val - 1;
    }

    cerr << ans;*/


    return 0;
}
