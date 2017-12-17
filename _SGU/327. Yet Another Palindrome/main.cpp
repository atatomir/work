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

#define maxN 28
#define inf 10000000

int n, i, j, limit, conf;
string s[maxN], rs[maxN];
pair<int, int> dp[1 << 14][maxN];

int prem[maxN][maxN];
pair<int, int> ans;

void upd(pair<int, int> &a, pair<int, int> b) {
    a = min(a, b);
}

bool a_in_b(string A, string B) {
    int i, j, dim;
    bool ok = false;

    dim = A.size();
    for (i = 0; i + dim - 1 < B.size(); i++) {
        ok = true;

        for (j = 0; j < dim; j++)
            if (A[j] != B[i + j])
                ok = false;

        if (ok) return true;
    }

    return false;
}

bool is_palind(string A, int p1, int p2) {
    while (p1 < p2) {
        if (A[p1] != A[p2])
            return false;
        p1++; p2--;
    }
    return true;
}

int best_palind(string A) {
    int i, j, cnt;
    int ans = 2 * A.size() - 1;

    for (i = 0; i < A.size(); i++)
        if (is_palind(A, 0, i))
            ans = min(ans, 2 * (int)A.size() - (i + 1));

    return ans;
}

int match(string A, string B) {
    int i, j, p1, p2;
    bool ok;

    int d1 = A.size();
    int d2 = B.size();

    for (i = min(d1, d2); i > 0; i--) {
        p1 = d1 - i;
        p2 = 0;

        ok = true;
        for (j = 0; j < i; j++) {
            if (A[p1] != B[p2]) {
                ok = false;
                break;
            }

            p1++; p2++;
        }

        if (ok) return 2 * (A.size() - i);
    }

    return 2 * A.size();
}

void app_left(string& A, string B, int cnt) {
    while (B.size() > cnt) B.pop_back();
    A = B + A;
}

void app_right(string& A, string B, int cnt) {
    reverse(A.begin(), A.end());
    app_left(A, B, cnt);
    reverse(A.begin(), A.end());
}

void recons(int who) {
    int i, act, conf, old, dd, old2;
    vector<int> ord;
    string sol, rsol;

    ord.clear();
    act = who;
    conf = limit - 1;

    while (conf != 0) {
        ord.pb(act);

        old = conf;
        old2 = act;
        if (act >= n) act -= n;

        conf ^= 1 << act;
        act = dp[old][old2].second;
    }

    reverse(ord.begin(), ord.end());
    if (ord[0] < n) ord[0] += n;
    else            ord[0] -= n;

    for (auto e : ord) cerr << e << ' ';

    sol = s[ord[0]];
    rsol = sol;
    reverse(rsol.begin(), rsol.end());

    dd = 2 * sol.size() - best_palind(sol);
    app_left(sol, rsol, sol.size() - dd);

    for (i = 1; i < ord.size(); i++) {
        int id = ord[i];

        int dm = match(s[id], sol);
        app_left(sol, s[id], dm / 2);
        app_right(sol, s[id], dm / 2);
    }

    cout << sol;

    if (sol.size() != ans.first)
        cerr << "ERROR";
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> s[i];
        rs[i] = s[i];
        reverse(rs[i].begin(), rs[i].end());
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) continue;
            if (a_in_b(s[i], s[j])) {
                s[i] = s[n - 1];
                rs[i] = rs[n - 1];
                n--; i--;
                break;
            }

            if (a_in_b(rs[i], s[j])) {
                s[i] = s[n - 1];
                rs[i] = rs[n - 1];
                n--; i--;
                break;
            }
        }
    }

    limit = 1 << n;
    for (i = 0; i < limit; i++)
        for (j = 0; j < 2 * n; j++)
            dp[i][j] = mp(inf, -2);

    for (i = 0; i < n; i++) {
        s[n + i] = rs[i];
        rs[n + i] = s[i];
    }

    for (i = 0; i < 2 * n; i++) {
        for (j = 0; j < 2 * n; j++)
            prem[i][j] = match(s[i], s[j]);
    }

    for (i = 0; i < n; i++) {
        dp[1 << i][i] = mp(best_palind(s[i + n]), -1);
        dp[1 << i][n + i] = mp(best_palind(s[i]), -1);
    }


    for (conf = 0; conf < limit; conf++) {
        for (i = 0; i < 2 * n; i++) {
            if (dp[conf][i].first >= inf) continue;

            for (j = 0; j < n; j++) {
                if ((conf >> j) & 1) continue;
                upd(dp[conf | (1 << j)][j], mp(dp[conf][i].first + prem[j][i], i));
                upd(dp[conf | (1 << j)][j + n], mp(dp[conf][i].first + prem[j + n][i], i));
            }

        }
    }

    ans = mp(inf, -2);
    for (i = 0; i < 2 * n; i++)
        ans = min(ans, mp(dp[limit - 1][i].first, i));

    recons(ans.second);


    return 0;
}
