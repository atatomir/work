#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 2016
#define inf 2000000011

int n, i, x;
int cost[maxN];
vector<int> list[maxN];

int cnt;
vector<int> work[maxN];
int id[maxN];

vector<int> aux;
int sum1[maxN], sum2[maxN];
int dp[maxN][maxN];
bool prov[maxN][maxN];

int ans = 0;


void merge_it(vector<int> &dest, const vector<int>& son) {
    int i, j;
    int new_cost;
    int sumall = 0;

    aux = dest;
    dest.clear();

    for (i = 0; i <= (int)aux.size(); i++)
        for (j = 0; j <= (int)son.size(); j++)
            dp[i][j] = inf;

    for (i = 0; i < (int)aux.size(); i++)
        sum1[i + 1] = sum1[i] + cost[ aux[i] ], sumall += cost[aux[i]];

    for (i = 0; i < (int)son.size(); i++)
        sum2[i + 1] = sum2[i] + cost[ son[i] ], sumall += cost[son[i]];

    dp[0][0] = 0;
    for (i = 0; i <= (int)aux.size(); i++){
        for (j = 0; j <= (int)son.size(); j++) {
            if (i < (int)aux.size()) {
                new_cost = dp[i][j] + (sumall - sum1[i + 1] - sum2[j]);
                if (new_cost < dp[i + 1][j]) {
                    dp[i + 1][j] = new_cost;
                    prov[i + 1][j] = true;
                }
            }

            if (j < (int)son.size()) {
                new_cost = dp[i][j] + (sumall - sum1[i] - sum2[j + 1]);
                if (new_cost < dp[i][j + 1]) {
                    dp[i][j + 1] = new_cost;
                    prov[i][j + 1] = false;
                }
            }
        }
    }

    i = aux.size();
    j = son.size();

    while (i != 0 || j != 0) {
        if (prov[i][j]) {
            dest.pb(aux[i - 1]);
            i--;
        } else {
            dest.pb(son[j - 1]);
            j--;
        }
    }

    reverse(dest.begin(), dest.end());

}

void dfs(int node) {
    for (int to : list[node]) dfs(to);

    if (list[node].empty() == false) {
        pair<int, int> best = mp(-1, -1);

        for (int i = 0; i < list[node].size(); i++)
            best = max(best, mp( (int)work[ id[ list[node][i]] ].size(), i ));

        swap(list[node][ list[node].size() - 1 ], list[node][best.second]);

        id[node] = id[ list[node].back() ];
        list[node].pop_back();
    } else {
        work[++cnt] = {node};
        id[node] = cnt;

        return;
    }

    for (int s : list[node])
        merge_it(work[ id[node] ], work[ id[s] ]);

    reverse(work[ id[node] ].begin(), work[ id[node] ].end());
    work[ id[node] ].pb(node);
    reverse(work[ id[node] ].begin(), work[ id[node] ].end());
}



int main()
{
    freopen("purification.in", "r", stdin);
    freopen("purification.out", "w", stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &cost[i]);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        x++;
        list[x].pb(i);
    }

    dfs(0);
    for (i = 1; i < (int)work[ id[0] ].size(); i++)
        ans += i * cost[work[ id[0] ][i]];

    printf("%d", ans);


    return 0;
}
