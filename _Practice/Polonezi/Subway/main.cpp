#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1000011

int n, l, i, x, y;
vector<int> list[maxN];
int gr[maxN], R, dad[maxN], lvl[maxN];
bool us[maxN];

vector<int> leaves;
vector<int> S[maxN];
bool deleted[maxN];

int up[maxN], len[maxN];
set< pair<int, int> > H;
int ans;

bool dead[maxN];

void dfs(int node) {
    us[node] = true;

    if (us[list[node][0]] && list[node].size() == 1)
        leaves.pb(node);

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];
        if (us[to]) continue;

        dad[to] = node;
        lvl[to] = lvl[node] + 1;

        dfs(to);
    }
}

void clean(vector<int> &list) {
    vector<int> ans;
    ans.clear();

    for (int i = 0; i < list.size(); i++)
        if (!dead[list[i]])
            ans.pb(list[i]);


    list = ans;
}

void clean2(vector<int> &list) {
    for (int i = 0; i < list.size() && i <= 3; i++) {
        if (!deleted[list[i]]) continue;
        list[i] = list.back();
        list.pop_back();
        i--;
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &l);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);

        gr[x]++; gr[y]++;
    }

    if (l == 0) {
        printf("0");
        return 0;
    }

    if (n == 2) {
        printf("2");
        return 0;
    }

    for (R = 1; gr[R] <= 2 && R <= n; R++);
    if (R == n + 1) {
        printf("%d", n);
        return 0;
    }

    dfs(R);

    l = max(0, (int)leaves.size() - 2 * l);

    for (int ei = 0; ei < leaves.size(); ei++) {
        int e = leaves[ei];
        int aux;

        for (aux = dad[e]; gr[aux] <= 2; aux = dad[aux]) dead[aux] = true, ans--;

        S[aux].pb(e);
        up[e] = aux;
        len[e] = -lvl[aux] + lvl[e];
        H.insert(mp(len[e], e));
    }

    ans = n;
    while (!H.empty() && l > 0) {
        int node = H.begin()->second;
        ans -= H.begin()->first;
        H.erase(H.begin());
        l--;

        int daddy = up[node];
        gr[daddy]--;

        deleted[node] = true;
        clean2(S[daddy]);


        if (S[daddy].size() == 1 && gr[daddy] <= 2) {
            node = *S[daddy].begin();
            H.erase(mp(len[node], node));

            int aux;
            for (aux = up[node]; gr[aux] <= 2; aux = list[aux][0])
                dead[aux] = true, clean(list[aux]), len[node]++;

            up[node] = aux;
            S[aux].pb(node);
            clean2(S[aux]);
            H.insert(mp(len[node], node));
        }
    }

    printf("%d", ans);

    return 0;
}
