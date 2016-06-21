#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 111
#define rank ceva

int n, i, j, k, x;
vector<int> list[maxN];
int id[maxN], old[maxN];
vector<int> aux;

int rank[maxN][maxN];

map< vector<int>, int > M;
int cnt;
int use[maxN << 1];

vector<int> ans[maxN];
int rot_pos;



int src(int l, int r) {
    if (l == r)
        return l;

    int mid = (l + r) >> 1;
    int p1 = src(l, mid);
    int p2 = src(mid + 1, r);


    bool A = true;
    for (int i = 0; i < p2 - p1; i++) {
        if (use[p1 + i] < use[p2 + i]) break;
        if (use[p1 + i] > use[p2 + i]) {A = false; break;}
    }

    if (A) return p1;
    return p2;
}

void min_lex() {
    int i, dim;

    if (aux.empty()) return;

    dim = aux.size();
    for (i = 1; i <= dim; i++) use[i] = use[i + dim] = aux[i - 1];

    rot_pos = src(1, dim) - 1;

    aux.clear();
    for (i = rot_pos; i < rot_pos + dim; i++) aux.pb(use[i + 1]);
}

void rotate_with(int how) {
    static vector<int> rez;

    rez.clear();
    for (int i = 0; i < how; i++) rez.pb( aux[i] );

    for (i = how; i < aux.size(); i++) aux[i - how] = aux[i];
    aux.resize(aux.size() - how);
    for (auto e : rez)
        aux.pb(e);
}

void expand() {
    int i;

    memcpy(old, id, sizeof(old));
    M.clear(); cnt = 0;

    for (i = 1; i <= n; i++) {
        aux.clear();
        for (auto e : list[i])
            aux.pb(old[e]);

        min_lex();

        aux.clear();
        for (auto e : list[i])
            aux.pb(e);
        rotate_with(rot_pos);

        for (int j = 0; j < aux.size(); j++)
            rank[ aux[j] ][i] = j + 1;

    }

    for (i = 1; i <= n; i++) {
        aux.clear();
        for (auto e : list[i])
            aux.pb(old[e] + n * rank[i][e]);

        min_lex();
        aux.pb(old[i]);

        if (M[aux] == 0) M[aux] = ++cnt;
        id[i] = M[aux];
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &k);
        for (j = 1; j <= k; j++) {
            scanf("%d", &x);
            list[i].pb(x);
        }

        id[i] = k;
    }

    for (int step = 1; step <= n; step++)
        expand();

    for (i = 1; i <= n; i++)
        ans[ id[i] ].pb(i);

    bool any = false;
    for (i = 1; i <= cnt; i++) {
        if (ans[i].size() == 1) continue;

        for (auto e : ans[i])
            printf("%d ", e);
        printf("\n");

        any = true;
    }

    if (!any)
        printf("none");

    return 0;
}
