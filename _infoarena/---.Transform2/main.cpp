#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 80011

int n, i, j, x, y;
vector<int> on_line[maxN];
vector<int> list[maxN];

vector< pair<int, int> > e1, e2;
vector< vector<int> > comp, c1, c2;
vector<int> aux;
bool us[maxN];

int go[maxN];
multiset< pair< pair<int, int>, int> > S;

//#define tt 111

#ifdef tt
int m1[tt][tt];
int m2[tt][tt];
#endif


void L(int x, int y) {
    if (x == y) return;
    printf("L %d %d\n", x, y);

    #ifdef tt
    for (int i = 1; i <= n; i++)
        swap(m1[x][i], m1[y][i]);
    #endif
}

void C(int x, int y) {
    if (x == y) return;
    printf("C %d %d\n", x, y);

    #ifdef tt
    for (int i = 1; i <= n; i++)
        swap(m1[i][x], m1[i][y]);
    #endif
}

void dfs(int node) {
    us[node] = true;
    aux.pb(node);

    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

void desc() {
    int i;

    for (i = 1; i <= n; i++) list[i].clear();
    for (i = 1; i <= n; i++) {
        list[ on_line[i][0] ].pb(on_line[i][1]);
        list[ on_line[i][1] ].pb(on_line[i][0]);
    }

    comp.clear();
    memset(us, 0, sizeof(us));

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        aux.clear();
        dfs(i);
        comp.pb(aux);
    }
}

bool cmp(const vector<int>& a, const vector<int>& b) {
    return a.size() < b.size();
}

void solve_col(int node) {
    us[node] = true;
    if (us[ go[node] ]) return;
    solve_col( go[node] );
    C(node, go[node]);
}

void solve_ln(int node) {
    us[node] = true;
    if (us[ go[node] ]) return;
    solve_ln( go[node] );
    L(node, go[node]);
}





int main()
{
    freopen("transform2.in","r",stdin);
    freopen("transform2.out","w",stdout);

    scanf("%d", &n);

    //! dest
    for (i = 1; i <= 2 * n; i++) {
        scanf("%d%d", &x, &y);
        on_line[x].pb(y);

        e2.pb(mp(x, y));

        #ifdef tt
        m2[x][y] = 1;
        #endif
    }
    desc();
    c2 = comp;

    for (i = 1; i <= n; i++) {
        if (on_line[i][0] > on_line[i][1]) swap(on_line[i][0], on_line[i][1]);
        S.insert(mp(mp(on_line[i][0], on_line[i][1]), i));
    }

    //! sour
    for (i = 1; i <= n; i++) on_line[i].clear();

    for (i = 1; i <= 2 * n; i++) {
        scanf("%d%d", &x, &y);
        on_line[x].pb(y);

        e1.pb(mp(x, y));

        #ifdef tt
        m1[x][y] = 1;
        #endif
    }
    desc();
    c1 = comp;

    //! pair columns
    sort(c1.begin(), c1.end(), cmp);
    sort(c2.begin(), c2.end(), cmp);

    for (i = 0; i < c1.size(); i++)
        for (j = 0; j < c1[i].size(); j++)
            go[ c1[i][j] ] = c2[i][j];

    memset(us, 0, sizeof(us));
    for (i = 1; i <= n; i++)
        if (!us[i])
            solve_col(i);

    //! pair lines
    for (i = 1; i <= n; i++) on_line[i].clear();
    for (i = 0; i < e1.size(); i++) {
        e1[i].second = go[e1[i].second];
        on_line[e1[i].first].pb(e1[i].second);
    }
    for (i = 1; i <= n; i++)
        if (on_line[i][0] > on_line[i][1])
            swap(on_line[i][0], on_line[i][1]);

    for (i = 1; i <= n; i++) {
        auto it = S.lower_bound(mp(mp(on_line[i][0], on_line[i][1]), 0));
        go[i] = it->second;
        S.erase(it);
    }

    memset(us, 0, sizeof(us));
    for (i = 1; i <= n; i++)
        if (!us[i])
            solve_ln(i);

    printf("0 0 0");

    #ifdef tt
    for (i = 1; i <= n; i++, cerr << '\n')
        for (j = 1; j <= n; j++) {
            cerr << "(" << m1[i][j] <<  m2[i][j] << ") ";
            if (m1[i][j] != m2[i][j])
                return -3;
        }
    #endif

    return 0;
}
