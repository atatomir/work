#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long

#define maxN 1024

int n, i, x, k;
vector<int> full[maxN];
vector<int> list[maxN];
bool us[maxN];

bool is_head[maxN];
vector<int> heads;
vector<int> cic;
vector<int> nodes;

vector<int> dp[maxN];
int cnt[maxN];

vector<int> aux;
vector<int> ans;
vector<int> help;

bool in_stack[maxN];


void dfs(int node) {
    nodes.pb(node);
    us[node] = true;
    for (int to : full[node])
        if (!us[to])
            dfs(to);
}

void src_cic(int node) {
    us[node] = false;
    cic.pb(node);
    in_stack[node] = true;

    for (int to : list[node]) {
        if (us[to] == false) {
            int l, i;

            if (!in_stack[to]) continue;
            for (l = 0; cic[l] != to; l++);

            for (i = l; i < cic.size(); i++) heads.pb(cic[i]), is_head[cic[i]] = true;
        } else {
            src_cic(to);
        }
    }

    cic.pop_back();
    in_stack[node] = false;
}

void get_heads(int R) {
    int i;

    nodes.clear();
    dfs(R);

    for (int e : nodes) {
        if (us[e] == false) continue;
        src_cic(e);
    }

    for (int e : nodes) us[e] = true;
}

void combine(int d, int s) {
    int i, j;

    aux.resize(dp[d].size() + dp[s].size() - 1);
    for (i = 0; i < aux.size(); i++) aux[i] = 0;

    for (i = 0; i < dp[s].size(); i++)
        for (j = 0; j < dp[d].size(); j++)
            aux[i + j] = max(aux[i + j], dp[s][i] + dp[d][j]);

    dp[d] = aux;
    //dp[s].clear();
}

void combine2(int d, int s) {
    int i, j;

    aux.resize(dp[d].size() + dp[s].size() - 1);
    for (i = 0; i < aux.size(); i++) aux[i] = 0;

    for (i = 0; i < dp[s].size(); i++)
        for (j = 0; j < dp[d].size(); j++)
            aux[i + j] = max(aux[i + j], dp[s][i] + dp[d][j] - (i == cnt[s]));

    dp[d] = aux;
    //dp[s].clear();
}

void combine3(int d, int s) {
    int i, j;

    aux.resize(dp[d].size() + dp[s].size() - 1);
    for (i = 0; i < aux.size(); i++) aux[i] = 0;

    for (i = 0; i < dp[s].size(); i++)
        for (j = 0; j < dp[d].size(); j++)
            aux[i + j] = max(aux[i + j], dp[s][i] + dp[d][j]);

    dp[d] = aux;
    //dp[s].clear();
}

void compute(int node) {
    int i;

    cnt[node] = 1;

    for (int to : list[node]) {
        if (is_head[to]) continue;

        compute(to);
        cnt[node] += cnt[to];
    }

    if (cnt[node] == 1) {
        dp[node] = {0, 1};
        if (is_head[node]) dp[node][1] = 0;
        return;
    }

    //! -----------------------------------
    dp[node] = {0};
    for (i = 0; i < list[node].size(); i++)
        if (!is_head[list[node][i]])
            combine2(node, list[node][i]);

    //for (i = 1; i < dp[node].size(); i++) dp[node][i]++;

    dp[node][ cnt[node] - 1 ] = 1;

    dp[node].pb(1);
    if (is_head[node]) dp[node][cnt[node]] = 0;
}



int main()
{
    freopen("politic.in", "r", stdin);
    freopen("politic.out", "w", stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        list[x].pb(i);
        full[x].pb(i); full[i].pb(x);
    }

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        get_heads(i);
    }

    for (int id : heads)
        compute(id);

    dp[0] = dp[heads[0]];
    for (i = 1; i < heads.size(); i++)
        combine3(0, heads[i]);

    for (i = 1; i <= n; i++) {
        k = n - i;

        if (dp[0].size() - 1 < k)
            return -1;
        else
            printf("%d\n", n - i - dp[0][k]);
    }

    return 0;
}
