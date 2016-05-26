#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define pb push_back
#define mp make_pair

#define maxN 55
#define inf (1LL << 60)

int n, i, j, cnt;
ll x;
ll a[maxN][maxN];
ll b[maxN][maxN];
ll rez[maxN][maxN];

ll ans = inf;

bool check() {
    int i, j;

    if (ans == inf) return false;

    for (i = 1; i < n; i++)
        for (j = 1; j < n; j++)
            if (rez[i][j] + rez[i + 1][j + 1] != rez[i + 1][j] + rez[i][j + 1])
                return false;


    return true;
}

void solve(int ln, int co) {
    int i, j;
    ll act_ans = 0;
    ll aux;

    //! incercam sa bulanim / rezolvam cu greedy
    for (i = 1; i <= n; i++) b[ln][i] = a[ln][i], b[i][co] = a[i][co], act_ans += a[ln][i] + a[i][co];

    for (i = 1; i <= n; i++) {
        if (i == ln) continue;

        for (j = 1; j <= n; j++) {
            if (j == co) continue;

            aux = b[ln][j] + b[i][co] - b[ln][co];
            if (aux < a[i][j]) return;

            act_ans += aux;
            b[i][j] = aux;
        }
    }

    act_ans -= b[ln][co];

    if (act_ans < ans) {
        ans = act_ans;
        memcpy(rez, b, sizeof(rez));
    }
}

void solve2(int ln) {
    int i, j;
    ll aux;
    ll act_ans = 0;

    //! incercam sa bulanim / rezolvam cu greedy
    for (i = 1; i <= n; i++) b[1][i] = a[ln][i];

    for (i = 2; i <= n; i++) {
        aux = a[i][1];
        for (j = 2; j <= n; j++)
            aux = max(aux, b[1][1] + a[i][j] - b[1][j]);

        b[i][1] = aux;
        for (j = 2; j <= n; j++)
            b[i][j] = b[1][j] + b[i][1] - b[1][1];
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            act_ans += b[i][j];

    if (act_ans < ans) {
        ans = act_ans;
        memcpy(rez, b, sizeof(rez));
    }
}

void solve3(ll co) {
    int i, j;
    ll aux;
    ll act_ans = 0;

    //! incercam sa bulanim / rezolvam cu greedy
    for (i = 1; i <= n; i++) b[i][1] = a[i][co];

    for (j = 2; j <= n; j++) {
        aux = a[1][j];

        for (i = 2; i <= n; i++)
            aux = max(aux, a[i][j] - b[i][1] + b[1][1]);

        b[1][j] = aux;
        for (i = 2; i <= n; i++)
            b[i][j] = b[1][j] + b[i][1] - b[1][1];
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            act_ans += b[i][j];

    if (act_ans < ans) {
        ans = act_ans;
        memcpy(rez, b, sizeof(rez));
    }
}

void solve4() {
    int i, j;
    pair<ll, int> best;

    for (j = 1; j <= n; j++) {
        best = mp(-1, -1);
        for (i = 1; i <= n; i++)
            best = max(best, mp(a[i][j], i));

        a[n + 1][j] = best.first;
    }

    solve2(n + 1);
}

void solve5() {
    int i, j;
    pair<ll, int> best;

    for (j = 1; j <= n; j++) {
        best = mp(inf, -1);
        for (i = 1; i <= n; i++)
            best = min(best, mp(a[i][j], i));

        a[n + 1][j] = best.first;
    }

    solve2(n + 1);
}

void solve6() {
    int i, j;
    pair<ll, int> best;

    for (i = 1; i <= n; i++) {
        best = mp(-1, -1);
        for (j = 1; j <= n; j++)
            best = max(best, mp(a[i][j], i));

        a[i][n + 1] = best.first;
    }

    solve3(n + 1);
}

void solve7() {
    int i, j;
    pair<ll, int> best;

    for (i = 1; i <= n; i++) {
        best = mp(inf, -1);
        for (j = 1; j <= n; j++)
            best = min(best, mp(a[i][j], i));

        a[i][n + 1] = best.first;
    }

    solve3(n + 1);
}

void great_solve() {
    int i, j;
    int best;

    for (i = 1; i <= n; i++) a[n + 1][i] = a[1][i];
    solve2(n + 1);

    for (int step = n; step > 0; step--) {
        /*best = 2;
        for (i = 2; i <= n; i++)
            if (b[i][1] > b[best][i])
                best = i;*/

        for (i = 1; i <= n; i++) a[n + 1][i]++;
        solve2(n + 1);
    }
}

void great_solve2() {
    int i, j;
    int best;

    for (i = 1; i <= n; i++) a[n + 1][i] = a[1][i];
    solve2(n + 1);

    for (int step = n * 2 / 3; step > 0; step--) {
        pair<ll, int> best = mp(-1, -1);

        for (i = 1; i <= n; i++)
            best = max(best, mp(b[i][1], i));

        int ln = best.second;
        for (i = 2; i <= n; i++)
            if (b[ln][i] == a[ln][i])
                a[n + 1][i]++;

        solve2(n + 1);
    }
}

int main()
{
    freopen("echilibrare.in", "r", stdin);
    freopen("echilibrare.out", "w", stdout);

    while (scanf("%lld", &x) == 1) cnt++;
    n = sqrt(cnt);

    freopen("echilibrare.in", "r", stdin);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%lld", &a[i][j]);


    if (n == 1) {
        ans = a[1][1];
        printf("%d\n%d\n", ans, ans);
        return 0;
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            solve(i, j);

    for (i = 1; i <= n; i++)
        solve2(i);

    for (i = 1; i <= n; i++)
        solve3(i);

    solve4();
    solve5();
    solve6();
    solve7();
    great_solve();
    great_solve2();

    if (!check()) {
        cerr << "err";

        ll best = 0;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                best = max(best, a[i][j]);

        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                rez[i][j] = best;

        ans = 1LL * best * n * n;
    }


    printf("%lld\n", ans);
    for (i = 1; i <= n; i++, printf("\n"))
        for (j = 1; j <= n; j++)
            printf("%lld ", rez[i][j]);


    return 0;
}
