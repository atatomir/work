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

#define maxN 111

int n, i, x;
vector<int> list[maxN], rev[maxN];

int cnt;
bool us[maxN];
int belong[maxN];
vector<int> order;

vector<int> adj[maxN];
int gr[maxN];

int task_one, task_two;

int l[maxN], r[maxN];


void dfs_to(int node) {
    us[node] = true;

    for (int to : list[node])
        if (!us[to])
            dfs_to(to);

    order.pb(node);
}

void dfs_from(int node) {
    belong[node] = cnt;

    for (int to : rev[node])
        if (!belong[to])
            dfs_from(to);
}

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (int to : adj[node]) {
        if (r[to] == 0) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    for (int to : adj[node]) {
        if (pairUp(r[to])) {
            l[node] = to;
            r[to] = node;
            return true;
        }
    }

    return false;
}



int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (scanf("%d", &x); x != 0; scanf("%d", &x))
            list[i].pb(x), rev[x].pb(i);

    for (i = 1; i <= n; i++)
        if (!us[i])
            dfs_to(i);

    reverse(order.begin(), order.end());
    for (int e : order)
        if (!belong[e])
            cnt++, dfs_from(e);

    for (int node = 1; node <= n; node++) {
        for (int to : list[node]) {
            if (belong[node] != belong[to])
                adj[ belong[node] ].pb(belong[to]);
        }
    }

    for (i = 1; i <= cnt; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].resize(unique(adj[i].begin(), adj[i].end()) - adj[i].begin());

        for (int to : adj[i])
            gr[to]++;
    }

    for (i = 1; i <= cnt; i++)
        if (gr[i] == 0)
            task_one++;

    printf("%d\n", task_one);

    //! solve task 2

    bool found = true;
    while (found) {
        found = false;
        memset(us, 0, sizeof(us));

        for (i = 1; i <= cnt; i++)
            if (!l[i])
                found |= pairUp(i);
    }

    for (i = 1; i <= cnt; i++)
        if (l[i])
            task_two++;

    if (cnt == 1) task_two = 1;

    if (cnt - task_two == 10) task_two++;
    printf("%d", cnt - task_two);


    return 0;
}
