#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n, i, j;
char s[maxN][maxN], aux[maxN][maxN];
short up_left[maxN][maxN], up_right[maxN][maxN], _left[maxN][maxN];

int aib[2][maxN];
vector<int> rez[maxN];
int ans;

void preprocess() {
    int i, j;

    memset(_left, 0, sizeof(_left));
    memset(up_left, 0, sizeof(up_left));
    memset(up_right, 0, sizeof(up_right));

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (s[i][j] == '0') continue;

            up_left[i][j] = up_left[i - 1][j - 1] + 1;
            up_right[i][j] = up_right[i - 1][j + 1] + 1;
            _left[i][j] = _left[i][j - 1] + 1;
        }
    }
}

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void aib_clear() {
    memset(aib[0], 0, sizeof(aib[0]));
    memset(aib[1], 0, sizeof(aib[1]));

    for (int i = 1; i <= n; i++)
        rez[i].clear();
    rez[n + 1].clear();
}

void aib_add(int id, int pos, int v) {
    while (pos <= n) {
        aib[id][pos] += v;
        pos += zrs(pos);
    }
}

int aib_sum(int id, int pos) {
    int ans = 0;
    while (pos > 0) {
        ans += aib[id][pos];
        pos -= zrs(pos);
    }
    return ans;
}

void solve(int line) {
    int i, j;

    aib_clear();

    for (j = 1; j <= n; j++) {
        for (auto who : rez[j]){
            aib_add(who % 2, who, -1);
        }

        int diag = up_left[line][j];
        int base = _left[line][j];
        base = min(base, 2 * diag - 1);

        if (s[line][j] == '0') continue;
        ans += aib_sum(j % 2, j) - aib_sum(j % 2, j - base);

        int wh = j + up_right[line][j] * 2 - 1;
        wh = min(wh, n + 1);

        rez[wh].pb(j);
        aib_add(j % 2, j, +1);
    }
}

void rotate_matrix() {
    memcpy(aux, s, sizeof(s));
    memset(s, 0, sizeof(s));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            s[j][n - i + 1] = aux[i][j];

    /*for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cerr << s[i][j];
        }
        cerr << '\n';
    }
    cerr << '\n';
    */
}

int main()
{
    freopen("piramid.in","r",stdin);
    freopen("piramid.out","w",stdout);

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++)
        scanf("%s\n", s[i] + 1);

    for (int step = 0; step < 4; step++) {
        if (step > 0)
            rotate_matrix();

        preprocess();
        for (i = 1; i <= n; i++)
            solve(i);

        cerr << step << ' ' << ans << '\n';
    }

    printf("%d", ans);
    cerr << ans;

    return 0;
}
