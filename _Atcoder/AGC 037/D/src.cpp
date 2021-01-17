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

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 103;

int n, m, col;
int a[maxN][maxN];

vector< pair<int, int> > adj[maxN];
int le[maxN], ri[maxN];
bool used[maxN];

bool pairUp(int node) {
    if (used[node]) return false;
    used[node] = true;

    for (auto to: adj[node]) {
        if (ri[to.first] == 0) {
            le[node] = to.first;
            ri[to.first] = node;
            return true;
        }
    }

    for (auto to: adj[node]) {
        if (pairUp(ri[to.first])) {
            le[node] = to.first;
            ri[to.first] = node;
            return true;
        }
    }

    return false;
}

int findEdge(int node, int dest) {
    for (int i = 0; i < adj[node].size(); i++) {
        auto to = adj[node][i];

        if (to.first == dest) {
            adj[node][i] = adj[node].back();
            adj[node].pop_back();
            return to.second;
        }
    }

    cerr << "Error";
    exit(-1);
}

void findColumn() {
    memset(le, 0, sizeof(le));
    memset(ri, 0, sizeof(ri));

    bool need = true;
    while (need) {
        need = false;
        memset(used, 0, sizeof(used));
    
        for (int i = 1; i <= n; i++)
            if (!le[i])
                need |= pairUp(i);
    }

    col++;
    for (int i = 1; i <= n; i++) 
        a[col][i] = findEdge(i, le[i]);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            int to = (a[i][j] - 1) / m + 1;
            adj[i].pb(mp(to, a[i][j]));
        }
    }

    for (int times = 1; times <= m; times++) 
        findColumn();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", a[j][i]);
        }
        printf("\n");
    }

    for (int i = 1; i <= m; i++)
        sort(a[i] + 1, a[i] + n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", a[j][i]);
        }
        printf("\n");
    }

    return 0;
}
