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

#define maxN (8 * 40011)

struct tp {
    char c1, c2;
    int id;

    tp() {

    }

    tp(char _c1, char _c2) {
        c1 = _c1;
        c2 = _c2;

        if (c1 == '0') {
            id = 0;
        } else {
            id = (c1 - 'A' + 1) * 2 + (c2 == '+' ? 1 : 0);
        }
    }
};

struct molec {
    tp edge[4];

    void rot() {
        tp aux = edge[0];
        edge[0] = edge[1];
        edge[1] = edge[2];
        edge[2] = edge[3];
        edge[3] = aux;
    }

    void mirr1() {
        swap(edge[0], edge[2]);
    }

    void mirr2() {
        swap(edge[1], edge[3]);
    }

    void mirr3() {
        swap(edge[0], edge[1]);
        swap(edge[2], edge[3]);
    }

    void mirr4() {
        swap(edge[0], edge[3]);
        swap(edge[1], edge[2]);
    }
};

int n, i, cnt;
char s[11];
molec M[maxN], act;

vector<int> connect_left[111], connect_up[111];
bool us[maxN];
bool on_way[maxN];
bool found;

void dfs(int node) {
    us[node] = true;
    on_way[node] = true;

    for (auto to : connect_left[ M[node].edge[1].id ^ 1 ]) {
        if (on_way[to]) {
            found = true;
            return;
        }

        if (us[to]) continue;

        dfs(to);
        if (found) return;
    }

    for (auto to : connect_up[ M[node].edge[2].id ^ 1 ]) {
        if (on_way[to]) {
            found = true;
            return;
        }

        if (us[to]) continue;

        dfs(to);
        if (found) return;
    }

    on_way[node] = false;
}

bool find_cycle() {
    int i;

    for (i = 1; i <= n; i++) {
        us[i] = false;
        on_way[i] = false;
    }

    found = false;
    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        dfs(i);
        if (found) return true;
    }

    return false;
}

int main()
{
    freopen("test.in","r",stdin);

    while (scanf("%d\n", &n) == 1) {
        cnt = 0;
        for (i = 0; i <= 100; i++) {
            connect_left[i].clear();
            connect_up[i].clear();
        }

        for (i = 1; i <= n; i++) {
            scanf("%s ", s + 1);
            act.edge[0] = tp(s[1], s[2]);
            act.edge[1] = tp(s[3], s[4]);
            act.edge[2] = tp(s[5], s[6]);
            act.edge[3] = tp(s[7], s[8]);

            M[++cnt] = act; act.rot();
            M[++cnt] = act; act.rot();
            M[++cnt] = act; act.rot();
            M[++cnt] = act; act.rot();

            act.mirr1(); M[++cnt] = act; act.mirr1();
            act.mirr2(); M[++cnt] = act; act.mirr2();
            act.mirr3(); M[++cnt] = act; act.mirr3();
            act.mirr4(); M[++cnt] = act; act.mirr4();
        }

        n = cnt;
        for (i = 1; i <= n; i++) {
            connect_left[M[i].edge[3].id].pb(i);
            connect_up[M[i].edge[0].id].pb(i);
        }

        connect_left[0].clear();
        connect_up[0].clear();


        if (find_cycle())
            printf("unbounded\n");
        else
            printf("bounded\n");
    }


    return 0;
}
