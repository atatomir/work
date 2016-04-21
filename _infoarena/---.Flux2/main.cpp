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

#define maxN 1024
int t, ti;
int n, m, i, j, S, D, x, y, pay, f, c;
vector< pair<int, int> > list[maxN];
bool us[maxN];

queue<int> Q;
int dist[maxN];
bool in_queue[maxN];
int computed[maxN];


void dfs(int node) {
    us[node] = true;
    for (auto to : list[node])
        if (!us[to.first])
            dfs(to.first);
}

bool bfs() {
    int i;

    memset(dist, 0, sizeof(dist));
    //memset(in_queue, 0, sizeof(in_queue)); //! will be set to 1
    memset(computed, 0, sizeof(computed));
    while (!Q.empty()) Q.pop();

    for (i = 1; i <= n; i++) {
        Q.push(i);
        in_queue[i] = true;
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        in_queue[node] = false;

        for (auto to : list[node]) {
            if (dist[to.first] > dist[node] + to.second) {
                dist[to.first] = dist[node] + to.second;
                if (!in_queue[to.first]) {
                    in_queue[to.first] = true;
                    Q.push(to.first);
                }

                if (++computed[to.first] > n) return false;
            }
        }
    }



    return true;
}

int main()
{
    freopen("flux2.in","r",stdin);
    freopen("flux2.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        cerr << "Test " << ti << " : ";

        scanf("%d%d%d%d", &n, &m, &S, &D);
        for (i = 1; i <= n; i++) list[i].clear();

        for (i = 1; i <= m; i++) {
            scanf("%d%d%d%d%d", &x, &y, &pay, &f, &c);

            if (f != c)
                list[x].pb(mp(y, pay));
            if (f != 0)
                list[y].pb(mp(x, -pay));
        }

        memset(us, 0, sizeof(us));
        dfs(S);
        if (us[D]) {
            cerr << "Too few flow\n";
            printf("0\n");
            continue;
        }

        if (!bfs()) {
            cerr << "Negative cycle\n";
            printf("0\n");
            continue;
        }

        printf("1\n");
        cerr << "All good\n";
    }



    return 0;
}
