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

#define maxN 500011

int n, m, st, i, x, y;
int val[maxN];
vector<int> list[maxN];
int gr[maxN];
bool in_queue[maxN], marked[maxN];
queue<int> Q;

vector<int> ord;

void mark_it(int node) {
    marked[node] = true;
    ord.pb(node);

    for (auto to : list[node]) {
        gr[to]--;
        if (!marked[to]) continue;
        if (in_queue[to]) continue;

        if (val[to] == 0 || val[to] > gr[to]) {
            in_queue[to] = true;
            Q.push(to);
        }
    }
}

int main()
{
    freopen("markon.in","r",stdin);
    freopen("markon.out","w",stdout);

    scanf("%d%d%d", &n, &m, &st);
    for (i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);

        gr[x]++; gr[y]++;
    }

    mark_it(st);
    if (val[st] == 0 || gr[st] < val[st]) {
        in_queue[st] = true;
        Q.push(st);
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        for (auto to : list[node]) {
            if (marked[to] == false)
                mark_it(to);

            if (in_queue[to]) continue;
            if (gr[to] < val[to] || val[to] == 0) {
                in_queue[to] = true;
                Q.push(to);
            }
        }
    }

    printf("%d\n", ord.size());
    for (auto e : ord)
        printf("%d\n", e);





    return 0;
}
