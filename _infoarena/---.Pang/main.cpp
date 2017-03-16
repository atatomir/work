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

#define maxN 100011

int t, ti;
int n, m, k, i, x, y, gr[maxN];
vector<int> list[maxN];
queue<int> Q;

int rel[maxN];
int best[maxN];
vector<int> ord;


int main()
{
    freopen("pang.in","r",stdin);
    freopen("pang.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d%d", &n, &m, &k);
        for (i = 1; i <= m; i++) {
            scanf("%d%d", &x, &y);
            list[x].pb(y);
            gr[y]++;
        }

        for (i = 1; i <= k; i++) {
            scanf("%d", &x);
            rel[x] = i;
        }

        for (i = 1; i <= n; i++)
            if (gr[i] == 0)
                Q.push(i);

        bool ok = false;

        while (!Q.empty()) {
            int node = Q.front(); Q.pop();
            if (rel[node]) {
                ord.pb(node);
                best[node]++;

                if (best[node] == k)
                    ok = true;
            }

            for (auto to : list[node]) {
                if (--gr[to] == 0)
                    Q.push(to);
                best[to] = max(best[to], best[node]);
            }
        }

        if (ok) {
            printf("Da\n");
            for (auto e : ord)
                printf("%d ", e);
            printf("\n");
        } else {
            printf("Nu\n");
        }

        for (i = 1; i <= n; i++) {
            gr[i] = 0;
            list[i].clear();
            rel[i] = 0;
            best[i] = 0;
        }
        ord.clear();
        while (!Q.empty()) Q.pop();

    }


    return 0;
}
