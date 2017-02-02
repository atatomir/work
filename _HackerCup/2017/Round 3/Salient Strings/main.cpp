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

#define maxN 1024

int t, ti, n, i;
int p[maxN], ord[maxN];

vector<int> list[maxN];
int gr[maxN];
char s[maxN];


bool solve() {
    int i, j;

    memset(gr, 0, sizeof(gr));
    memset(s, 0, sizeof(s));
    for (i = 0; i <= n + 1; i++) list[i].clear();

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) continue;

            if (p[i] < p[j] && p[i + 1] > p[j + 1]) {
                list[i].pb(j);
                gr[j]++;
            }

            if (p[i] > p[j] && p[i + 1] < p[j + 1]) {
                list[j].pb(i);
                gr[i]++;
            }
        }
    }

    for (i = 1; i <= n; i++) s[i] = 'A';
    for (i = 1; i <= n; i++) {
        int node = ord[i];

        if (i != 1)
            s[node] = max(s[node], s[ ord[i - 1] ]);

        if (gr[node] != 0) return false;
        if (list[node].size() > 0 && s[node] == 'Z') return false;

        for (auto to : list[node]) {
            gr[to]--;
            s[to] = max(s[to], (char)(s[node] + 1));
        }
    }

    return true;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%d", &p[i]);
            ord[p[i]] = i;
        }

        p[n + 1] = 0;
        ord[0] = n + 1;

        if (!solve())
            printf("Case #%d: -1\n", ti);
        else
            printf("Case #%d: %s\n", ti, s + 1);
    }


    return 0;
}
