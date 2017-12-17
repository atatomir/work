#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 22
#define mod 100006288300009
#define base 413

const int gbase = 1000000;
const int gmax_dim = 100;

struct giant {
    ll data[gmax_dim + 11];

    giant() {
        memset(data, 0, sizeof(data));
    }

    giant(int x) {
        memset(data, 0, sizeof(data));
        data[1] = x;
    }

    void operator*=(ll nr) {
        int i;

        for (i = 1; i <= gmax_dim; i++)
            data[i] *= nr;
        for (i = 1; i <= gmax_dim; i++) {
            data[i + 1] += data[i] / gbase;
            data[i] %= gbase;
        }
    }

    void operator+=(giant who) {
        int i;

        for (i = 1; i <= gmax_dim; i++)
            data[i] += who.data[i];
        for (i = 1; i <= gmax_dim; i++) {
            data[i + 1] += data[i] / gbase;
            data[i] %= gbase;
        }
    }

    void operator/=(ll nr) {
        int i;

        for (i = gmax_dim; i > 0; i--) {
            data[i - 1] += (data[i] % nr) * gbase;
            data[i] /= nr;
        }
    }

    void operator<<=(int cnt) {
        while (cnt >= 20) {
            *this *= (1 << 20);
            cnt -= 20;
        }

        while (cnt > 0) {
            cnt--;
            *this *= 2;
        }
    }

    void print_dig(ll nr) {
        for (ll aux = gbase / 10; aux > 0; aux /= 10) {
            if (nr >= aux) break;
            cout << 0;
        }

        if (nr != 0) cout << nr;
    }

    void print() {
        int pos;

        for (pos = gmax_dim; data[pos] == 0; pos--);
        cerr << "Your number has " << pos << " magic digits\n";

        cout << data[pos];
        for (pos--; pos > 0; pos--)
            print_dig(data[pos]);
    }
};

int n, m, i, j;
int mat[maxN][maxN], aux[maxN][maxN];
pair<int, int> wh[maxN * maxN];
map<vector<int>, bool> M;

int go[maxN * maxN];
int to_add[maxN * maxN];
ll cnt;

giant sol, p2, act;

ll get_id() {
    ll ans;
    int i, j;

    ans = 0;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            ans = ans * base + mat[i][j];
            ans %= mod;
        }
    }

    return ans;
}

void mv_lines1() {
    int i, j;

    for (j = 1; j <= m; j++)
        mat[n + 1][j] = mat[1][j];

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            mat[i][j] = mat[i + 1][j];
}

void mv_lines2() {
    int i, j;

    for (j = 1; j <= m; j++)
        mat[0][j] = mat[n][j];

    for (i = n; i >= 1; i--)
        for (j = 1; j <= m; j++)
            mat[i][j] = mat[i - 1][j];
}

void mv_columns1() {
    int i, j;

    for (i = 1; i <= n; i++)
        mat[i][m + 1] = mat[i][1];

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            mat[i][j] = mat[i][j + 1];
}

void mv_columns2() {
    int i, j;

    for (i = 1; i <= n; i++)
        mat[i][0] = mat[i][m];

    for (i = 1; i <= n; i++)
        for (j = m; j >= 1; j--)
            mat[i][j] = mat[i][j - 1];
}

void rot180() {
    int i, j;

    memcpy(aux, mat, sizeof(mat));
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            mat[i][j] = aux[n - i + 1][m - j + 1];
}

void rot90() {
    int i, j;

    memcpy(aux, mat, sizeof(mat));
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            mat[n - j + 1][i] = aux[i][j];
}

void dfs(int node) {
    if (go[node] == 0) return;
    int aux = go[node];
    go[node] = 0;
    dfs(aux);
}

void add_to_sol() {
    int i, j, cyc;

    cnt++;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            go[(i - 1) * m + j] = mat[i][j];
        }
    }

    cyc = 0;
    for (i = 1; i <= n * m; i++)
        if (go[i] != 0)
            dfs(i), cyc++;

    to_add[cyc]++;
}

void solve() {
    vector<int> now = {};
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            now.pb(mat[i][j]);
    /*ll id = get_id();
    if (M[id]) return;
    M[id] = true;*/

    auto &e = M[now];
    if (e == true) return;
    e = true;

    add_to_sol();

    mv_lines1();
    solve();
    mv_lines2();

    mv_columns1();
    solve();
    mv_columns2();


    if (n == m) {
        rot90();
        solve();
        rot90();
        solve();
        rot90();
        solve();
        rot90();
    } else {
        rot180();
        solve();
        rot180();
    }
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> m;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            {mat[i][j] = (i - 1) * m + j; wh[mat[i][j]] = mp(i, j);}

    solve();

    sol = giant(0);
    p2 = giant(2);
    for (i = 1; i <= n * m; i++) {
        if (to_add[i]) {
            act = p2;
            act *= to_add[i];
            sol += act;
        }

        p2 <<= 1;
    }

    sol /= cnt;
    sol.print();
    cout << endl;

    cerr << cnt;
    if (sol.data[0] != 0)
        cerr << "Error!";

    return 0;
}
