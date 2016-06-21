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


map< vector<int>, int > M;
int cnt;
int use[maxN << 1];

vector<int> ans[maxN];
int rot_pos;

int nxt[maxN][maxN];



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

void expand() {
    int i;

    memcpy(old, id, sizeof(old));
    M.clear(); cnt = 0;

    for (i = 1; i <= n; i++) {
        aux.clear();
        for (auto e : list[i])
            aux.pb(old[e] * n + old[ nxt[e][i] ]);


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

        for (j = 1; j < list[i].size(); j++)
            nxt[i][ list[i][j - 1] ] = list[i][j];
        if (!list[i].empty()) nxt[i][ list[i].back() ] = list[i][0];

        id[i] = k;
    }

    for (int step = 1; step <= 2 * n; step++)
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
