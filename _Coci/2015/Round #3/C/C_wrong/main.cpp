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
#define pii pair<int, int>

#define maxN 100011

int n, i, x, y;
vector< pii > list[maxN];
int from[maxN], to[maxN];

int last;
int gr[maxN];
bool dead[maxN];
queue<int> Q;
bool switched[maxN];
bool us[maxN];

int findCenter() {
    int i;
    last = 1;

    for (i = 1; i <= n; i++) {
        if (gr[i] > 1) continue;

        dead[i] = true;
        Q.push(i);
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        last = node;

        for (auto e : list[node]) {
            int to = e.first;

            if (dead[to]) continue;
            gr[to]--;

            if (gr[to] == 0) {
                dead[to] = true;
                Q.push(to);
            }
        }
    }

    return last;
}

void dfs(int node) {
    us[node] = true;

    for (auto e : list[node]) {
        if (us[e.first]) continue;

        if (from[ e.second ] == node)
            switched[e.second] = false;
        else
            switched[e.second] = true;

        dfs(e.first);
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &from[i], &to[i]);
        list[from[i]].pb(mp(to[i], i));
        list[to[i]].pb(mp(from[i], i));

        gr[from[i]]++;
        gr[to[i]]++;
    }

    int R = findCenter();
    dfs(R);

    for (i = 1; i < n; i++)
        printf( (switched[i] ? "0\n" : "1\n") );


    return 0;
}
