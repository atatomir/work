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

const int maxN = 100011;

int n, i, j, x, y, bg, pos;
vector<int> list[maxN];
bool leaf[maxN];
int gr[maxN], gr_leaf[maxN];
vector<int> ord, ord2;
vector<int> ans;

void dfs(int node, int root) {
    ord.pb(node);
    for (auto to : list[node])
        if (!leaf[to])
            if (to != root)
                dfs(to, node);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
        gr[x]++; gr[y]++;
    }

    if (n == 2) {
        printf("1 2");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        if (gr[i] > 1) continue;
        leaf[i] = true;
        gr_leaf[list[i][0]]++;
    }

    for (i = 1; i <= n; i++) {
        if (gr[i] - gr_leaf[i] > 2) {
            printf("-1");
            return 0;
        }
    }

    for (bg = 1; leaf[bg] || gr[bg] - gr_leaf[bg] == 2; bg++);
    dfs(bg, 0);

    ord2 = ord;
    reverse(ord2.begin(), ord2.end());
    for (i = 0; i < ord.size(); i++) {

        if (gr_leaf[ord[i]] < gr_leaf[ord2[i]]) break;
        if (gr_leaf[ord[i]] > gr_leaf[ord2[i]]) {
            swap(ord, ord2);
            break;
        }
    }

    gr_leaf[ord[0]]--;
    gr_leaf[ord.back()]--;

    pos = 2;
    ans = {1};

    for (auto e : ord) {
        for (i = 1; i <= gr_leaf[e]; i++) ans.pb(pos + i);
        ans.pb(pos);
        pos += gr_leaf[e] + 1;
    }

    ans.pb(n);

    for (auto e : ans) printf("%d ", e);


    return 0;
}
