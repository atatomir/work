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

#define maxN 73
#define mod 1000000007

int n, k, i;
int f[maxN], p[maxN];
string s, aux;

ll dp[4][maxN][2 * maxN]; //! stage, used, sum
ll cnt[maxN][maxN];
ll comb[maxN][maxN];

ll data[2][maxN];
ll ans;


void addit(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

void pre() {
    int st, i, j, k, dd;

    for (i = 0; i <= n + 1; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j];
            addit(comb[i][j], comb[i - 1][j - 1]);
        }
    }

    for (i = 0; i <= n; i++)
        dp[0][i][0] = 1;

    for (st = 0; st < 3; st++) {
        dd = (st <= 1 ? 1 : 2);

        for (i = 0; i <= n; i++) {
            for (j = 0; j <= i; j++) {
                if (dp[st][i][j] == 0) continue;
                for (k = 0; i + k <= n; k++) {
                    addit(dp[st + 1][i + k][j + dd * k], (dp[st][i][j] * comb[i + k][k]) % mod);
                }
            }
        }
    }

    for (i = 0; i <= n; i++)
        for (j = 0; j <= 2 * i; j++)
            cnt[i][j] = dp[3][i][j];
}

int get_first(int bg, char c) {
    while (bg < aux.size()) {
        if (aux[bg] == c) {
            aux[bg] = '.';
            return bg;
        }
        bg++;
    }

    return bg;
}

bool get_others(int bg, int cnt) {
    while (bg < aux.size() && cnt > 0) {
        if (aux[bg] != '.') {
            aux[bg] = '.';
            cnt--;
        }
        bg++;
    }
    return (cnt == 0);
}

bool check(int dim) {
    int i, need;

    need = 0;
    for (i = 1; i <= dim; i++) {
        if (f[i] == 1)
            need += 2;
        else
            need += f[i] * 2 - 2;
    }

    if (need > n + 1) return false;

    aux = s;
    for (i = 1; i <= dim; i++) {
        int pos_r = get_first(0, 'r');
        if (pos_r == aux.size()) return false;

        if (f[i] == 1) {
            p[i] = pos_r;
        } else {
            int pos_b = get_first(pos_r + 1, 'b');
            if (pos_b == aux.size()) return false;
            p[i] = pos_b;
        }
    }

    for (i = 1; i <= dim; i++) {
        if (f[i] <= 2) break;
        if (!get_others(p[i] + 1, f[i] - 2)) return false;
    }

    return true;
}

void add_to_solution(int dim) {
    int i, j, p, l, sz, to;
    static int iter = 0;


    if ( (++iter) % 50000 == 0)
        cerr << iter << '\n';


    //for (i = 1; i <= dim; i++) cerr << f[i] << ' ';
    //cerr << '\n';

    memset(data, 0, sizeof(data));
    data[0][0] = 1;

    for (i = 1; i <= dim; i = j) {
        for (j = i; j <= dim && f[i] == f[j]; j++);
        sz = j - i;

        if (f[i] == 1) {
            for (p = 0; p + sz * 2 <= n + 1; p++)
                addit(data[1][p + sz * 2], (data[0][p] * comb[j - 1][sz]) % mod );
        } else {
            for (p = 0; p <= n + 1; p++) {
                if (data[0][p] == 0) continue;

                for (l = 0; l <= n + 1; l++) {
                    to = p + sz * (2 * f[i] - 2) + l;
                    if (to > n + 1) break;

                    addit(data[1][to], (((data[0][p] * cnt[sz][l]) % mod) * comb[j - 1][sz]) % mod );
                }
            }
        }

        memcpy(data[0], data[1], sizeof(data[0]));
        memset(data[1], 0, sizeof(data[1]));
    }

    for (i = 0; i <= n + 1; i++) {
        ans += data[0][i] * comb[n + 1][i];
        ans %= mod;
    }
}

bool gen(int step) {
    if (!check(step - 1)) return false;
    add_to_solution(step - 1);

    for (int i = 1; i <= f[step - 1]; i++) {
        f[step] = i;
        if (!gen(step + 1)) break;
    }

    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> k >> s;
    pre();

    f[0] = (n + 3) / 2;
    gen(1);

    cout << ans;


    return 0;
}
