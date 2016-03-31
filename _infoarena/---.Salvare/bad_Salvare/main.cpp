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
#define inf 1000000000

int n, k, i, x, y;
vector<int> list[maxN];
int gr[maxN];

int need[maxN];
int act_gr[maxN];
bool pushed[maxN];
bool solved[maxN];
queue<int> Q;

vector<int> selected;
bool sel_bool[maxN];

bool check(int dist) {
    int i;
    int next_need;

    selected.clear();
    for (i = 1; i <= n; i++) {
        act_gr[i] = gr[i];
        pushed[i] = false;
        solved[i] = false;
        need[i] = inf;
    }
    while (!Q.empty()) Q.pop();


    for (i = 1; i <= n; i++) {
        if (act_gr[i] == 1) {
            Q.push(i);
            pushed[i] = true;
            need[i] = dist;
        }
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        solved[node] = true;

        if (need[node] == 0) {
            selected.pb(node);
            next_need = 2 * dist;
        } else {
            next_need = need[node] - 1;
        }

        bool terminal = true;
        for (auto to : list[node]) {
            if (solved[to]) continue;

            terminal = false;

            if (next_need + need[to] >= dist)
                need[to] = max(need[to], next_need);
            else
                need[to] = min(need[to], next_need);

            if (--act_gr[to] <= 1 && !pushed[to]) {
                pushed[to] = true;
                Q.push(to);
            }
        }

        if (terminal && next_need < dist) {
            //! must be selected
            selected.pb(node);
        }
    }

    return selected.size() <= k;
}

int main()
{
    freopen("salvare.in","r",stdin);
    freopen("salvare.out","w",stdout);


    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
        gr[x]++; gr[y]++;
    }

    int ans = -1;
    for (int step = 1 << 10; step; step >>= 1)
        if (!check(ans + step))
            ans += step;

    check(ans + 1);
    for (auto e : selected) sel_bool[e] = true;
    for (i = 1; i <= n && selected.size() != k; i++)
        if (sel_bool[i] == false)
            selected.pb(i);

    sort(selected.begin(), selected.end());

    printf("%d\n", ans + 1);
    for (int e : selected) printf("%d ", e);

    check(1);

    return 0;
}
