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

#define maxN 2018

int n, k, mod, i, j, x, y;
vector< vector<int> > sumb, sumw;
string c;
int ans;

int query(vector< vector<int> >& data, int x, int y, int xx, int yy) {
    int ans = data[xx][yy];
    if (x != 0) ans -= data[x - 1][yy];
    if (y != 0) ans -= data[xx][y - 1];
    if (x != 0 && y != 0) ans += data[x - 1][y - 1];
    return ans;
}

int add_square(vector< vector<int> >& data, int x, int y, int xx, int yy) {
    while (x >= mod) {
        x -= mod;
        xx -= mod;
    }

    while (y >= mod) {
        y -= mod;
        yy -= mod;
    }

    int ans = query(data, x, y, min(mod - 1, xx), min(mod - 1, yy));
    if (xx >= mod) ans += add_square(data, mod, y, xx, yy);
    if (yy >= mod) ans += add_square(data, x, mod, xx, yy);
    if (xx >= mod && yy >= mod) ans -= add_square(data, mod, mod, xx, yy);

    return ans;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n >> k; k *= 2;
    sumb = sumw = vector< vector<int> >(k + 2, vector<int>(k + 2, 0));

    for (i = 1; i <= n; i++) {
        cin >> x >> y >> c;

        if (c[0] == 'B')
            sumb[x % k][y % k]++;
        else
            sumw[x % k][y % k]++;
    }

    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            if (i != 0) {
                sumb[i][j] += sumb[i - 1][j];
                sumw[i][j] += sumw[i - 1][j];
            }

            if (j != 0) {
                sumb[i][j] += sumb[i][j - 1];
                sumw[i][j] += sumw[i][j - 1];
            }

            if (i * j != 0) {
                sumb[i][j] -= sumb[i - 1][j - 1];
                sumw[i][j] -= sumw[i - 1][j - 1];
            }
        }
    }

    mod = k;
    k >>= 1;

    for (i = 0; i < mod; i++) {

        for (j = 0; j < mod; j++) {
            int aux = 0;

            aux += add_square(sumb, i, j, i + k - 1, j + k - 1);
            aux += add_square(sumb, i + k, j + k, i + k + k - 1, j + k + k - 1);
            aux += add_square(sumw, i, j + k, i + k - 1, j + k + k - 1);
            aux += add_square(sumw, i + k, j, i + k + k - 1, j + k - 1);

            ans = max(ans, aux);
        }
    }

    cout << ans;


    return 0;
}
