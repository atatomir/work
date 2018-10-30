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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";


ostream& operator<<(ostream& cerr, vector<int> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 55;

int n, m, i, j, last;
char a[maxN][maxN];
int id[maxN][maxN];
vector<int> to[maxN * maxN], from[maxN * maxN];
char tp[maxN * maxN];

vector<int> S;
bool us[maxN * maxN];
int ans[maxN * maxN];

int star, bg, best;
vector<int> ids;

int sol, need;

void add_edge(int x, int y) {
    to[x].pb(y);
    from[y].pb(x);
}

void dfs_to(int node) {
    us[node] = true;
    for (auto e : to[node]) {
        if (us[e]) continue;
        dfs_to(e);
    }
    S.pb(node);
}

void dfs_from(int node) {
    us[node] = true;
    if (tp[node] == '*')
        star++;
    if (tp[node] == 'O')
        bg++;
    best = max(best, ans[node]);
    ids.pb(node);

    for (auto e : from[node])
        if (!us[e])
            dfs_from(e);
    
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", a[i] + 1);
        for (j = 1; j <= m; j++)
            id[i][j] = (i - 1) * m + j;
    
        for (j = 1; j <= m; j++)
            tp[id[i][j]] = a[i][j];
    }

    for (i = 1; i <= n; i++) {
        last = 0;
        for (j = 1; j <= m; j++) {
            if (a[i][j] == '#') 
                last = j;
            else 
                add_edge(id[i][j], id[i][last + 1]);
        }
        
        last = m + 1;
        for (j = m; j >= 1; j--) {
            if (a[i][j] == '#') 
                last = j;
            else 
                add_edge(id[i][j], id[i][last - 1]);
        }
    }

    for (j = 1; j <= m; j++) {
        last = 0;
        for (i = 1; i <= n; i++) {
            if (a[i][j] == '#')
                last = i;
            else
                add_edge(id[i][j], id[last + 1][j]);
        }
        
        last = n + 1;
        for (i = n; i >= 1; i--) {
            if (a[i][j] == '#')
                last = i;
            else
                add_edge(id[i][j], id[last - 1][j]);
        }
    }

    for (i = 1; i <= n * m; i++) {
        if (us[i]) continue;
        dfs_to(i);
    }    

    memset(us, 0, sizeof(us));
    reverse(S.begin(), S.end());
    for (auto node : S) {
        if (us[node]) continue;
        star = bg = best = 0;
        ids.clear();
        dfs_from(node);
    
        if (bg == 0) {
            best += star;
        } else {
            best = star + 1;
        }

        debug(ids);

        for (auto n1 : ids)
            for (auto n2 : to[n1])
                ans[n2] = max(ans[n2], best);

        sol = max(sol, best);
        need += star + bg;
    }

    if (sol == need)
        printf("YES");
    else
        printf("NO");

    return 0;
}
