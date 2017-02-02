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

int n, i, j;
char adj[maxN][maxN];

vector<int> cyc;
bool us[maxN];

int tp[maxN];
vector<int> attach;
vector< pair<int, int> > pairs;

vector< vector<int> > ans;
vector<int> aux;

void no_sol() {
    printf("impossible\n");
    exit(0);
}

bool find_cyc() {
    int n1, n2;

    for (n1 = 2; n1 <= n; n1++) {
        for (n2 = 2; n2 <= n; n2++) {
            if (n1 == n2) continue;

            if (adj[1][n1] == 0) continue;
            if (adj[n1][n2] == 0) continue;
            if (adj[n2][1] == 0) continue;

            cyc = {1, n1, n2};
            us[1] = us[n1] = us[n2] = true;
            ans = {cyc};
            return true;
        }
    }

    return false;
}

void recons(int node) {
    if (us[node]) return;

    if (tp[node] == 3) attach.pb(node);
    for (int to = 1; to <= n; to++) {
        if (us[to]) continue;


        if (tp[node] == 1 && tp[to] == 2 && adj[node][to])
            pairs.pb(mp(node, to));

        if (tp[node] == 2 && tp[to] == 1 && adj[to][node])
            pairs.pb(mp(to, node));
    }
}

void pre() {
    int node, to;

    for (auto node : cyc) {
        for (to = 1; to <= n; to++) {
            if (us[to]) continue;

            if (adj[node][to] == 1)
                tp[to] |= 1;
            else
                tp[to] |= 2;
        }
    }

    for (i = 1; i <= n; i++)
        recons(i);
}

void attach_node(int node) {
    int i, j;

    us[node] = true;
    cyc.pb(1);

    for (i = 0; i + 1 < cyc.size(); i++) {
        if (adj[ cyc[i] ][node] == 1 && adj[node][ cyc[i + 1] ] == 1) {
            for (j = cyc.size() - 1; j > i + 1; j--) cyc[j] = cyc[j - 1];
            cyc[i + 1] = node;
            break;
        }
    }

    ans.pb(cyc);

    for (int to = 1; to <= n; to++) {
        if (us[to]) continue;

        if (adj[node][to]) {
            if ((tp[to] & 1) == 0) {
                tp[to] |= 1;
                recons(to);
            }
        } else {
            if ((tp[to] & 2) == 0) {
                tp[to] |= 2;
                recons(to);
            }
        }
    }

}

void attach_pair(int x, int y) {
    int i;

    us[x] = us[y] = true;

    aux = {1, x, y};
    for (i = 2; i < cyc.size(); i++) aux.pb(cyc[i]);
    ans.pb(aux);

    aux = {1, x, y};
    for (i = 1; i < cyc.size(); i++) aux.pb(cyc[i]);
    ans.pb(aux);

    cyc = aux;


    for (int node : {x, y}) {
        for (int to = 1; to <= n; to++) {
            if (us[to]) continue;

            if (adj[node][to]) {
                if ((tp[to] & 1) == 0) {
                    tp[to] |= 1;
                    recons(to);
                }
            } else {
                if ((tp[to] & 2) == 0) {
                    tp[to] |= 2;
                    recons(to);
                }
            }
        }
    }

}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> adj[i] + 1;
        for (j = 1; j <= n; j++) {
            adj[i][j] -= '0';
        }
    }

    if (!find_cyc()) {
        no_sol();
    }
    pre();


    bool ok = true;
    while (ok) {
        ok = false;

        while (!attach.empty()) {
            if (us[attach.back()] == false) break;
            attach.pop_back();
        }

        while (!pairs.empty()) {
            if (us[pairs.back().first] == false &&
                us[pairs.back().second] == false &&
                tp[pairs.back().first] == 1 &&
                tp[pairs.back().second] == 2) break;
            pairs.pop_back();
        }

        if (!attach.empty()) {
            int node = attach.back();
            attach.pop_back();
            ok = true;

            attach_node(node);
            continue;
        }

        if (!pairs.empty()) {
            int x = pairs.back().first;
            int y = pairs.back().second;
            pairs.pop_back();
            ok = true;

            attach_pair(x, y);
            continue;
        }

    }

    for (i = 1; i <= n; i++)
        if (us[i] == false)
            no_sol();

    for (auto& v : ans) {
        for (auto e : v)
            printf("%d ", e);
        printf("1\n");
    }



    return 0;
}
