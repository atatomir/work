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

#define maxN 444

int n, k, i, x, y;
vector<int> list[maxN];
int lvl[maxN];
vector<int> ord;

int cnt[maxN], deep[maxN];

int hard[maxN];
vector<int> act, aux;


void dfs(int node, int root) {
    ord.pb(node);

    cnt[node] = 1;
    deep[node] = 1;

    for (int to : list[node]) {
        if (to == root) continue;
        lvl[to] = lvl[node] + 1;
        dfs(to, node);
        cnt[node] += cnt[to];
        deep[node] = max(deep[node], deep[to] + 1);
    }
}

void solve(int R) {
    int i;
    pair<int, int> best;

    act.clear();
    act.pb(R);

    while (act.size() > 0) {
        hard[R]++;

        aux = act;
        act.clear();
        for (auto e : aux)
            for (int to : list[e])
                if (lvl[to] == lvl[e] + 1)
                    act.pb(to);

        if (act.empty()) break;

        best = mp(-1, -1);
        for (i = 0; i < act.size(); i++)
            best = max(best, mp(hard[act[i]], i));

        act[best.second] = act.back();
        act.pop_back();
    }
}

void test_cnt() {
    int i, ans;
    pair<int, int> best;

    act.clear();
    act.pb(1);
    ans = 0;

    while (act.size() > 0) {
        ans++;

        aux = act;
        act.clear();
        for (auto e : aux)
            for (int to : list[e])
                if (lvl[to] == lvl[e] + 1)
                    act.pb(to);

        if (act.empty()) break;

        best = mp(-1, -1);
        for (i = 0; i < act.size(); i++)
            best = max(best, mp(cnt[act[i]], i));

        act[best.second] = act.back();
        act.pop_back();
    }

    if (ans <= k) {
        printf("DA");
        exit(0);
    }
}

void test_deep() {
    int i, ans;
    pair<int, int> best;

    act.clear();
    act.pb(1);
    ans = 0;

    while (act.size() > 0) {
        ans++;

        aux = act;
        act.clear();
        for (auto e : aux)
            for (int to : list[e])
                if (lvl[to] == lvl[e] + 1)
                    act.pb(to);

        if (act.empty()) break;

        best = mp(-1, -1);
        for (i = 0; i < act.size(); i++)
            best = max(best, mp(deep[act[i]], i));

        act[best.second] = act.back();
        act.pop_back();
    }

    if (ans <= k) {
        printf("DA");
        exit(0);
    }
}


int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);
    reverse(ord.begin(), ord.end());

    for (auto e : ord)
        solve(e);

    cerr << hard[1] << "\n";
    if (hard[1] <= k) {
        printf("DA");
    } else {
        test_cnt();
        test_deep();
        printf("NE");
    }


    return 0;
}
