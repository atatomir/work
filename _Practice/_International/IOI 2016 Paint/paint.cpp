#include "paint.h"

#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 200011
#define maxK 111

int n, m, i, j;
char S[maxN];
int C[maxK];

int sum[maxN];
char dp[maxN][maxK];

bool sp[maxN];
int x[maxN];

queue< pair<int, int> > Q;

void bfs(int node, int gr) {

    while (!Q.empty()) Q.pop();
    Q.push(mp(node, gr));

    while (!Q.empty()) {
        node = Q.front().first;
        gr = Q.front().second;
        Q.pop();

        if (node <= 0 || gr < 0) continue;
        dp[node][gr] = 2;

        if (S[node] != 'X') {
            if (dp[node - 1][gr] != 0) {
                sp[node] = true;

                if (dp[node - 1][gr] == 1) Q.push(mp(node - 1, gr));
                dp[node - 1][gr] = 2;
            }
        }

        if (S[node] != '_') {
            if (gr > 0) {
                if (C[gr] > node) continue;
                if (sum[node] - sum[node - C[gr]] > 0) continue;
                if (S[node - C[gr]] == 'X') continue;
                if (S[node + 1] == 'X') continue;

                if (node == C[gr] && gr == 1) {
                    x[node - C[gr] + 1]++;
                    x[node + 1]--;
                }

                if (node != C[gr])
                if (dp[node - C[gr] - 1][gr - 1] != 0) {
                    x[node - C[gr] + 1]++;
                    x[node + 1]--;
                    sp[node - C[gr]] = true;

                    if (dp[node - C[gr] - 1][gr - 1] == 1)
                        dp[node - C[gr] - 1][gr - 1] = 2,
                        Q.push(mp(node - C[gr] - 1, gr - 1));
                }
            }
        }

    }
}

std::string solve_puzzle(std::string s, std::vector<int> c) {
    string sol = "";

    n = s.size();
    for (i = 0; i < n; i++)
        S[i + 1] = s[i];

    m = c.size();
    for (i = 0; i < m; i++)
        C[i + 1] = c[i];

    sum[0] = 0;
    for (i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + (S[i] == '_');

    memset(dp, 0, sizeof(dp));

    dp[0][0] = 1;
    for (i = 1; i <= n; i++) {
        if (S[i] != 'X')
            memcpy(dp[i], dp[i - 1], sizeof(dp[i]));


        if (S[i] != '_') {
            for (j = 1; j <= m; j++) {
                if (C[j] > i) continue;
                if (sum[i] - sum[i - C[j]] > 0) continue;
                if (S[i - C[j]] == 'X') continue;
                if (S[i + 1] == 'X') continue;

                if (C[j] != i)
                    dp[i][j] |= dp[i - C[j] - 1][j - 1];
                else
                    dp[i][j] |= (j == 1);
            }
        }
    }

    if (dp[n][m] == 0)
        while(1);

    memset(sp, 0, sizeof(sp));
    memset(x, 0, sizeof(x));
    bfs(n, m);

    for (i = 1; i <= n; i++) x[i] += x[i - 1];
    for (i = 1; i <= n; i++) {
        if (S[i] == '.') {
            if (sp[i] && x[i])
                sol += '?';
            else
            if (sp[i])
                sol += '_';
            else
                sol += 'X';
        } else {
            sol += S[i];
        }
    }

    return sol;
}





