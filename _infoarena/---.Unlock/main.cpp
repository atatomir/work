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

#define maxN 255
#define maxNode (maxN * maxN)

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

int n, m, i, j, t, k, target, last_white;

int col[maxN][maxN];
int belong[maxN][maxN];

int cnt;
vector< pair<int, int> > edges[maxNode];
int comp_one, comp_two, ans;

int dad[maxNode];
int how[maxNode];
bool needed[maxNode];
vector<int> roll_back;

void dfs(int x, int y) {
    belong[x][y] = cnt;

    for (int i = 0; i < 4; i++) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (belong[xx][yy] == 0 && col[xx][yy] == col[x][y])
            dfs(xx, yy);
    }
}

int Find(int x) {
    roll_back.pb(x);

    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int R1, int R2) {
    R1 = Find(R1);
    R2 = Find(R2);

    if (R1 == R2) return false;

    dad[R2] = R1;
    how[R1] += how[R2];

    return true;
}

void roll_back_action() {
    for (int node : roll_back) {
        dad[node] = node;
        if (needed[node])
            how[node] = 1;
        else
            how[node] = 0;
    }

    roll_back.clear();
}

bool solve_color(int col) {
    int i, j;

    roll_back_action();

    for (pair<int, int> edge : edges[col])
        Merge(edge.first, edge.second);

    int R = Find(last_white);
    return how[R] == target;
}

int main()
{
    freopen("unlock.in","r",stdin);
    freopen("unlock.out","w",stdout);

    for( scanf("%d", &t); t > 0; t--) {
        roll_back_action();

        scanf("%d%d%d", &n, &m, &k);
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                scanf("%d", &col[i][j]);
                belong[i][j] = 0;
            }
        }

        for (i = 1; i <= k; i++)
            edges[i].clear();

        for (i = 0; i <= n + 1; i++) belong[i][0] = belong[i][m + 1] = -1;
        for (i = 0; i <= m + 1; i++) belong[0][i] = belong[n + 1][i] = -1;

        target = 0;
        cnt = 0;
        //! compute areas
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                if (belong[i][j] == 0) {
                    cnt++;
                    dfs(i, j);

                    needed[cnt] = (col[i][j] == 0);
                    roll_back.pb(cnt);
                    if (col[i][j] == 0) target++, last_white = cnt;
                }
            }
        }

        //! compute edges
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                comp_one = belong[i][j];

                if (i < n) {
                    comp_two = belong[i + 1][j];
                    if (col[i][j] == 0 || col[i + 1][j] == 0)
                        if (belong[i][j] != belong[i + 1][j])
                            edges[ max(col[i][j], col[i + 1][j]) ].pb(mp(comp_one, comp_two));
                }

                if (j < m) {
                    comp_two = belong[i][j + 1];
                    if (col[i][j] == 0 || col[i][j + 1] == 0)
                        if (belong[i][j] != belong[i][j + 1])
                            edges[ max(col[i][j], col[i][j + 1]) ].pb(mp(comp_one, comp_two));
                }
            }
        }

        //! remove unuseful edges
        for (i = 1; i <= k; i++) {
            for (j = 0; j < edges[i].size(); j++)
                if (edges[i][j].first > edges[i][j].second)
                    swap(edges[i][j].first, edges[i][j].second);

            sort(edges[i].begin(), edges[i].end());
            edges[i].resize( unique(edges[i].begin(), edges[i].end()) - edges[i].begin() );
        }

        ans = 0;
        for (i = 1; i <= k; i++)
            if(solve_color(i)) ans++;

        printf("%d\n", ans);
    }


    return 0;
}
