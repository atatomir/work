#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAXN = 605;

bool Viz[MAXN][MAXN][2];
int CC[MAXN][MAXN][2];
vector<int> G[MAXN][MAXN + MAXN];
bool Crash1[MAXN], Crash2[MAXN];

int Norm[MAXN * MAXN];

int n, m, k, cc;
vector<vector<int>> St;

void dfs1(int node, int col, bool val) {
    Viz[node][col][val] = 1;

    if(val == 0) {
        for(auto vec : G[node][col]) {
            if(!Viz[vec][col][1])
                dfs1(vec, col, 1);
        }
    } else {
        if(!Crash1[node]) {
            Crash1[node] = 1;

            for(int c = 1; c <= k; ++c) {
                if(c == col) continue;

                if(!Viz[node][c][0])
                    dfs1(node, c, 0);
            }
        }
    }

    St.push_back({node, col, val});
}

void dfs2(int node, int col, bool val) {
    CC[node][col][val] = cc;

    if(val == 1) {
        for(auto vec : G[node][col]) {
            if(!CC[vec][col][0])
                dfs2(vec, col, 0);
        }
    } else {
        if(!Crash2[node]) {
            Crash2[node] = 1;
            for(int c = 1; c <= k; ++c) {
                if(c == col) continue;

                if(!CC[node][c][1])
                    dfs2(node, c, 1);
            }
        }
    }
}

int main() {
    ifstream cin("entanglement.in");
    ofstream cout("entanglement.out");

    int t;
    cin >> t;
    if(t == 2) return 0;

    cin >> n >> m >> k;

    int vals = 0;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            int col;
            cin >> col;

            if(Norm[col] == 0)
                Norm[col] = ++vals;
            col = Norm[col];

            G[i][col].push_back(j + n);
            G[j + n][col].push_back(i);
        }

    if(vals > n + m) {
        cout << "NU\n";
        return 0;
    }

    k = vals;
    for(int i = 1; i <= n + m; ++i)
        for(int c = 1; c <= k; ++c) {
            if(!Viz[i][c][0])
                dfs1(i, c, 0);
            if(!Viz[i][c][1])
                dfs1(i, c, 1);
        }

    for(auto it = St.rbegin(); it != St.rend(); ++it) {
        auto &V = *it;
        if(!CC[V[0]][V[1]][V[2]]) {
            ++cc;
            dfs2(V[0], V[1], V[2]);
        }
    }

    for(int i = 1; i <= n + m; ++i)
        for(int j = 1; j <= k; ++j)
            if(CC[i][j][0] == CC[i][j][1]) {
                cout << "NU\n";
                return 0;
            }

    cout << "DA\n";
    return 0;
}
