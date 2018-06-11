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

const int maxN = 4111;
const int sigma = 4;

int n, m, k, j, i;
char s[maxN][maxN];
vector<int> who[maxN][sigma], aux;
int difs[maxN], need;

bool ok[maxN];
int cnt;

int get_id(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

bool brute(int a, int b) {
    int i;
    int ans = 0;

    for (i = 1; i <= m; i++) {
        if (s[a][i] == s[b][i]) continue;
        if (++ans > k) return false;
    }

    return (ans == k);
}

void solve(const vector<int>& nodes) {
    int i, j;

    for (i = 1; i <= m; i++)
        for (j = 0; j < sigma; j++)
            who[i][j].clear();
    for (i = 1; i <= n; i++) difs[i] = 0;

    for (auto i : nodes) {
        for (j = 1; j <= m; j++)
            who[j][get_id(s[i][j])].pb(i);
    }

    for (i = 1; i <= m; i++) {
        for (j = 0; j < sigma; j++)
            for (auto e : who[i][j])
                difs[e] += nodes.size() - who[i][j].size();
    }

    int need = (nodes.size() - 1) * k;
    for (auto e : nodes)
        if (difs[e] != need)
            if (ok[e])
                ok[e] = false, cnt--;

}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d\n", &n, &m, &k);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s[i] + 1);
        ok[i] = true; aux.pb(i);
    }

    cnt = n;
    solve(aux);

    for (int bit = 1; bit <= n && cnt > 16; bit <<= 1) {
        vector<int> v1, v2;

        v1 = v2 = {};
        for (i = 1; i <= n; i++) {
            if ((i - 1) & bit)
                v1.pb(i);
            else
                v2.pb(i);
        }

        solve(v1);
        solve(v2);
    }

    aux.clear();
    for (i = 1; i <= n; i++)
        if (ok[i])
            aux.pb(i);

    random_shuffle(aux.begin(), aux.end());

    for (auto node : aux) {
        bool ok = true;

        for (i = 1; i <= n; i++) {
            if (i == node) continue;
            if (!brute(node, i)) {
                ok = false;
                break;
            }
        }

        if (ok) {
            printf("%d", node);
            return 0;
        }
    }


    return 0;
}
