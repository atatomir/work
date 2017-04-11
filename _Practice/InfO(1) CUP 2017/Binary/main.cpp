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

#define maxN 2014
#define maxProc 1000000
#define mod 1000000007
#define inf 1000000000

const int def = 5;//2000;

int t, ti;
int n, i;

bool cnt[maxN][maxN];
int dist[maxN][maxN];

ll ans;
pair<int, int> best;
pair<int, int> proc[maxProc];

void pre() {
    int i, j;

    for (i = 0; i <= def; i++)
        for (j = 0; j <= def; j++)
            dist[i][j] = inf;

    cnt[0][1] = cnt[1][0] = 1;
    dist[0][1] = dist[1][0] = 0;

    for (i = 0; i <= def; i++) {
        for (j = 0; j <= def; j++) {
            //cnt[i][j] %= mod;
            if (i + j + 1 > def) continue;

            dist[i + j + 1][j] = min(dist[i + j + 1][j], dist[i][j] + 1);
            dist[i][i + j + 1] = min(dist[i][i + j + 1], dist[i][j] + 1);

            cnt[i + j + 1][j] |= cnt[i][j];
            cnt[i][i + j + 1] |= cnt[i][j];
        }
    }

    //freopen("err", "w", stderr);
    /*for (i = 0; i <= 30; i++) {
        for (j = 0; j <= 30; j++)
            if (dist[i][j] >= inf)
                cerr << '. ';
            else
                cerr << dist[i][j] << ' ';//(cnt[i][j] > 0 ? '#' : '.');
        cerr << '\n';
    }*/

    /*for (i = 0; i <= 30; i++) {
        for (j = 0; j <= 30; j++)
            cerr << (cnt[i][j] > 0 ? '#' : '.');
        cerr << '\n';
    }*/
}

void get_sol(int a, int b) {
    while (a > 0 || b > 0) {
        if (a > b) {
            printf("0 ");
            a -= b + 1;
        } else {
            printf("1 ");
            b -= a + 1;
        }
    }

    printf("\n");
}

int is_good(int a, int b) {
    int ans = 0;

    if (a <= def && b <= def) {
        if (cnt[a][b] == 0) return -1;
        return dist[a][b];
    }

    while (a > 0 && b > 0) {
        if (a == b) return -1;
        ans++;

        if (a > b) {
            a -= b + 1;
        } else {
            b -= a + 1;
        }
    }

    return ans + max(a, b);
}

void solve(int n) {
    int ans = 0;
    int i;
    pair<int, int> best = mp(inf, inf);

    if (proc[n].first != 0) {
        printf("%d\n", proc[n].first);
        get_sol(proc[n].second, n - proc[n].second);
        return;
    }

    for (i = 0; i < n - i; i++) {
        int aux = is_good(i, n - i);
        if (aux == -1) continue;
        ans += 2;
        best = min(best, mp(aux, i));
    }

    printf("%d\n", ans);
    get_sol(best.second, n - best.second);

    proc[n] = mp(ans, best.second);
}

int main()
{
    freopen("input","r",stdin);
    freopen("output","w",stdout);

    pre();

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        //n = ti;

        /*ans = 0;
        best = mp(inf, -1);

        for (i = 0; i <= n; i++) {
            ans += cnt[i][n - i];
            ans %= mod;
            best = min(best, mp(dist[i][n - i], 1LL * i));
        }

        printf("%lld\n", ans);
        get_sol(best.second, n - best.second);*/

        solve(n);
    }


    return 0;
}
