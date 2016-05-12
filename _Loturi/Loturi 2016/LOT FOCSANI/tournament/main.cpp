#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 55
#define inf 1000000001

int n, i, j;
int w[maxN];
int adj[maxN][maxN];

int sum[maxN];
int act[maxN][maxN];
int score[maxN];
bool dead[maxN];

vector<int> ans;
pair<int, int> best;

int all_of_them;
bool alrdn[maxN];

int need;

vector< pair<int, int> > aux;

vector<int> bul;
int b_cnt;

bool extract2(int node) {
    int i;

    aux.clear();

    dead[node] = true;
    for (int i : bul) {
        if (act[node][i] == 0) continue;

        int vv = min(act[node][i], need - score[node]);
        if (vv < 0) return false;

        score[node] += vv;
        sum[i] -= vv;
        sum[node] -= vv;
        act[node][i] -= vv;
        act[i][node] -= vv;

        if (dead[i] && act[i][node] != 0) return false;
    }

    return true;
}

bool check2(int R) {
    int i, j;

    memcpy(act, adj, sizeof(act));
    memcpy(sum, w, sizeof(sum));
    memcpy(score, w, sizeof(score));
    memset(dead, 0, sizeof(dead));

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            sum[i] += act[i][j];

    need = inf; extract2(R); need = score[R];
    for (i = 1; i <= n - 1; i++) {
        best = mp(inf, 0);
        for (j = 1; j <= n; j++)
            if (!dead[j])
                best = min(best, mp(sum[j], j));

        if (extract2(best.second) == false) return false;
        if (score[R] < score[best.second]) return false;
    }

    return true;
}




bool extract(int node) {
    int i;

    aux.clear();

    dead[node] = true;
    for (int i = 1; i <= n; i++) {
        if (!dead[i] || i == node) {
            aux.pb(mp(sum[i], i));
            continue;
        }
        if (act[node][i] == 0) continue;

        int vv = min(act[node][i], need - score[node]);
        if (vv < 0) return false;

        score[node] += vv;
        sum[i] -= vv;
        sum[node] -= vv;
        act[node][i] -= vv;
        act[i][node] -= vv;

        if (dead[i] && act[i][node] != 0) return false;
    }

    sort(aux.begin(), aux.end());
    reverse(aux.begin(), aux.end());

    for (auto ee : aux) {
        int i = ee.second;

        if (act[node][i] == 0) continue;

        int vv = min(act[node][i], need - score[node]);
        if (vv < 0) return false;

        score[node] += vv;
        sum[i] -= vv;
        sum[node] -= vv;
        act[node][i] -= vv;
        act[i][node] -= vv;

        if (dead[i] && act[i][node] != 0) return false;
    }

    return true;
}

bool check(int R) {
    int i, j;

    memcpy(act, adj, sizeof(act));
    memcpy(sum, w, sizeof(sum));
    memcpy(score, w, sizeof(score));
    memset(dead, 0, sizeof(dead));

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            sum[i] += act[i][j];

    need = inf; extract(R); need = score[R];
    for (i = 1; i <= n - 1; i++) {
        best = mp(inf, 0);
        for (j = 1; j <= n; j++)
            if (!dead[j])
                best = min(best, mp(sum[j], j));

        if (extract(best.second) == false) return false;
        if (score[R] < score[best.second]) return false;
    }

    return true;
}

void solve_small() {
    int i, j, k;
    vector< pair<int, int> > edge;

    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            for (k = 1; k <= adj[i][j]; k++)
                edge.pb(mp(i, j));

    int cnt = edge.size();
    int lim = 1 << cnt;

    for (int state = 0; state < lim; state++) {
        memcpy(score, w, sizeof(score));

        for (i = 0; i < cnt; i++)
            if ((state >> i) & 1)
                score[ edge[i].first ]++;
            else
                score[ edge[i].second ]++;

        int best = 0;
        for (i = 1; i <= n; i++) best = max(best, score[i]);
        for (i = 1; i <= n; i++)
            if (best == score[i]) {
                if (!alrdn[i]) ans.pb(i);
                alrdn[i] = true;
            }
    }
}

int main()
{
    freopen("tournament.in", "r", stdin);
    freopen("tournament.out", "w", stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &adj[i][j]), all_of_them += adj[i][j];


    for (i = 1; i <= n; i++) bul.pb(i);
    b_cnt = 5000000 / (n * n * n);

    all_of_them /= 2;
    if (all_of_them <= 20) {
        solve_small();
    } else {

        for (i = 1; i <= n; i++) {
            if (alrdn[i]) continue;
            if (check(i)) {
                if (!alrdn[i]) ans.pb(i);
                alrdn[i] = true;
            }
        }

        for (; b_cnt > 0; b_cnt--) {
            for (i = 1; i <= n; i++) {
                if (alrdn[i]) continue;
                if (check2(i)) {
                    if (!alrdn[i]) ans.pb(i);
                    alrdn[i] = true;
                }
            }

            random_shuffle(bul.begin(), bul.end());
        }

    }



    sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for (int e : ans)
        printf("%d ", e - 1);


    return 0;
}
