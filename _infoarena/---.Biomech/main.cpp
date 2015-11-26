#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxL 7
#define maxC 45
#define maxMove 10
#define ll long long
#define inf 1000000000000000000LL
#define pii pair<int, int>

ll d1[5][8][5][8];
ll d2[5][8][5][8];

class Matrix {
    public:
        int n = 40;
        ll data[5][8][5][8];

        int n1, r1, n2, r2, n3, r3;

        void go_inf() {
            for (n1 = 0; n1 < 5; n1++)
                for (r1 = 0; r1 < 8; r1++)
                    for (n2 = 0; n2 < 5; n2++)
                        for (r2 = 0; r2 < 8; r2++)
                            data[n1][r1][n2][r2] = inf;
        }

        void operator=(Matrix &who) {
            memcpy(data, who.data, sizeof(data));
        }
        void operator*=(Matrix &who) {
            memcpy(d1, data, sizeof(data));
            memcpy(d2, who.data, sizeof(data));

            go_inf();

            for (n1 = 0; n1 < 5; n1++)
                for (r1 = 0; r1 < 8; r1++)
                    for (n2 = 0; n2 < 5; n2++)
                        for (r2 = 0; r2 < 8; r2++)
                            for (n3 = 0; n3 < 5; n3++)
                                for (r3 = 0; r3 < 8; r3++)
                                    data[n1][r1][n3][r3] = min(data[n1][r1][n3][r3],
                                                               d1[n1][r1][n2][r2] + d2[n2][r2][n3][r3]);
        }
};

const int defX[8] = {-1, -1, 0, +1, +1, +1, 0, -1};
const int defY[8] = {0, +1, +1, +1, 0, -1, -1, -1};

ll t;
int i, j, k;
ll rot_pay[maxMove][maxMove];
ll move_pay[maxL][maxMove];

ll dp[maxL][maxC][maxMove];

int lim = 60;
Matrix work[65];
long long ans;
Matrix act, aux;

ll final_ans;

struct cmp {
    bool operator()(const pii& a, const pii& b)const {
        return a.first > b.first;
    }
};

priority_queue< pii, vector<pii>, cmp > H;

int compress(int x, int y, int rot) {
    return x + y * 10 + rot * 1000;
}

void compute_one_column(int ini_line, int ini_rot) {
    int i, j, k;

    while (!H.empty()) H.pop();

    for (i = 1; i <= 5; i++)
        for (j = 1; j <= 41; j++)
            for (k = 0; k < 8; k++)
                dp[i][j][k] = inf;

    dp[ini_line][21][ini_rot] = 0;
    H.push(mp(0, compress(ini_line, 21, ini_rot)));

    while (!H.empty()) {
        auto node = H.top(); H.pop();

        int x = node.second % 10;
        int y = (node.second / 10) % 100;
        int rot = node.second / 1000;

        if (dp[x][y][rot] < node.first) continue;

        //! -------- move ---------------

        int xx = x + defX[rot];
        int yy = y + defY[rot];

        if (!(xx < 1 || 5 < xx || yy < 1 || 41 < yy)) {
            int pos_pay = dp[x][y][rot] + move_pay[x][rot];
            if (dp[xx][yy][rot] > pos_pay) {
                dp[xx][yy][rot] = pos_pay;
                H.push(mp(pos_pay, compress(xx, yy, rot)));
            }
        }

        //! -------- rotate ------------

        for (i = 0; i < 8; i++) {
            int pos_pay = dp[x][y][rot] + rot_pay[rot][i];
            if (dp[x][y][i] > pos_pay) {
                dp[x][y][i] = pos_pay;
                H.push(mp(pos_pay, compress(x, y, i)));
            }
        }
    }
}

void make_matrix() {
    int i, k, j;

    for (i = 1; i <= lim; i++) {
        work[i] = work[i - 1];
        work[i] *= work[i];
    }
}

bool good() {
    for (int n1 = 2; n1 < 3; n1++)
        for (int r1 = 0; r1 < 8; r1++)
            for (int n2 = 0; n2 < 5; n2++)
                for (int r2 = 0; r2 < 8; r2++)
                    if (act.data[n1][r1][n2][r2] <= t)
                        return true;
    return false;
}

ll solve() {
    int i;
    bool found = false;
    ans = 0;

    for (i = lim; i >= 0; i--) {
        act = work[i];
        if (good()) {
            found = true;
            ans += 1LL << i;
            break;
        }
    }

    if (!found) {
        cerr << "0\n";
        return 0;
    }

    for (i--; i >= 0; i--) {
        aux = act;
        act *= work[i];

        if (good()) {
            ans += 1LL << i;
            continue;
        }

        act = aux;
    }

    cerr << ans << '\n';
    return ans;
}

void debug() {
    return ;

    for (int n1 = 0; n1 < 5; n1++)
        for (int r1 = 0; r1 < 8; r1++)
            for (int n2 = 0; n2 < 5; n2++)
                for (int r2 = 0; r2 < 8; r2++)
                    if (work[0].data[n1][r1][n2][r2] < t)
                        cerr << n1 << ' ' << r1 << ' ' << n2 << ' ' << r2 << '=' << work[0].data[n1][r1][n2][r2] << '\n';
}

int main()
{
    freopen("biomech.in","r",stdin);
    freopen("biomech.out","w",stdout);

    scanf("%lld", &t);
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            scanf("%lld", &rot_pay[i][j]);

    for (i = 1; i <= 5; i++)
        for (j = 0; j < 8; j++)
            scanf("%lld", &move_pay[i][j]);

    //! to right -----------------------------------

    work[0].go_inf();
    for (int line = 1; line <= 6; line++) {
        for (k = 0; k < 8; k++) {
            compute_one_column(line, k);

            for (i = 1; i <= 5; i++)
                for (j = 0; j < 8; j++)
                    work[0].data[line - 1][k][i - 1][j] = dp[i][22][j];
        }
    }

    make_matrix();

    debug();

    final_ans = solve();

    //! to left ------------------------------------

    work[0].go_inf();
    for (int line = 1; line <= 5; line++) {
        for (k = 0; k < 8; k++) {
            compute_one_column(line, k);

            for (i = 1; i <= 5; i++)
                for (j = 0; j < 8; j++)
                    work[0].data[line - 1][k][i - 1][j] = dp[i][20][j];
        }
    }

    make_matrix();

    debug();

    final_ans = max(final_ans, solve());

    //! conclusions ------------------------------------

    printf("%lld", final_ans);

    return 0;
}
