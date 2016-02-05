#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define def 100000.00
#define maxN 84
#define eps 1e-9

const ll defX[7] = {0, +1, -1, 0, 0, 0, 0};
const ll defY[7] = {0, 0, 0, +1, -1, 0, 0};
const ll defZ[7] = {0, 0, 0, 0, 0, +1, -1};

const int moveX[6] = {-1, 1, 0, 0, 0, 0};
const int moveY[6] = {0, 0, -1, 1, 0, 0};
const int moveZ[6] = {0, 0, 0, 0, -1, 1};

struct Cloud {
    ll x1, y1, z1;
    ll x2, y2, z2;
    int dir;

    void read() {
        double aux;

        scanf("%lf", &aux);
        x1 = aux * def;
        scanf("%lf", &aux);
        y1 = aux * def;
        scanf("%lf", &aux);
        z1 = aux * def;

        scanf("%lf", &aux);
        x2 = aux * def;
        scanf("%lf", &aux);
        y2 = aux * def;
        scanf("%lf", &aux);
        z2 = aux * def;


        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        if (z1 > z2) swap(z1, z2);

        scanf("%d", &dir);
    }

    void move() {
        x1 += defX[dir] * def;
        x2 += defX[dir] * def;

        y1 += defY[dir] * def;
        y2 += defY[dir] * def;

        z1 += defZ[dir] * def;
        z2 += defZ[dir] * def;
    }
};

int n, t, i, a, b, c;
Cloud v[maxN];

vector<int> norm_x;
vector<int> norm_y;
vector<int> norm_z;
unordered_map<int, int> pos_x, pos_y, pos_z;

double vol[maxN][maxN][maxN];
short smen[maxN][maxN][maxN];
double aux;

double ans;
int id;

void dfs(int x, int y, int z) {
    aux += vol[x - 1][y - 1][z - 1];
    smen[x][y][z] = 0;

    for (int i = 0; i < 6; i++) {
        int xx = x + moveX[i];
        int yy = y + moveY[i];
        int zz = z + moveZ[i];

        if (smen[xx][yy][zz] > 0.00)
            dfs(xx, yy, zz);
    }
}

double solve() {
    int i, j, k;

    norm_x.clear();
    norm_y.clear();
    norm_z.clear();

    for (i = 1; i <= n; i++) {
        norm_x.pb(v[i].x1);
        norm_x.pb(v[i].x2);

        norm_y.pb(v[i].y1);
        norm_y.pb(v[i].y2);

        norm_z.pb(v[i].z1);
        norm_z.pb(v[i].z2);
    }

    sort(norm_x.begin(), norm_x.end());
    norm_x.resize( unique(norm_x.begin(), norm_x.end()) - norm_x.begin() );
    pos_x.clear();
    for (i = 0; i < norm_x.size(); i++)
        pos_x[norm_x[i]] = i;

    sort(norm_y.begin(), norm_y.end());
    norm_y.resize( unique(norm_y.begin(), norm_y.end()) - norm_y.begin() );
    pos_y.clear();
    for (i = 0; i < norm_y.size(); i++)
        pos_y[norm_y[i]] = i;

    sort(norm_z.begin(), norm_z.end());
    norm_z.resize( unique(norm_z.begin(), norm_z.end()) - norm_z.begin() );
    pos_z.clear();
    for (i = 0; i < norm_z.size(); i++)
        pos_z[norm_z[i]] = i;

    //! no need to refresh
    //memset(vol, 0, sizeof(vol));
    //memset(smen, 0, sizeof(smen));

    a = norm_x.size();
    b = norm_y.size();
    c = norm_z.size();

    double dx, dy, dz;
    for (i = 0; i < a - 1; i++) {
        dx = 1.00 * (norm_x[i + 1] - norm_x[i]) / def;

        for (j = 0; j < b - 1; j++) {
            dy = 1.00 * (norm_y[j + 1] - norm_y[j]) / def;

            for (k = 0; k < c - 1; k++) {
                dz = 1.00 * (norm_z[k + 1] - norm_z[k]) / def;

                vol[i][j][k] = dx * dy * dz;
            }
        }
    }

    for (i = 1; i <= n; i++) {
        int xx1 = pos_x[ v[i].x1 ] + 1;
        int xx2 = pos_x[ v[i].x2 ] + 1;

        int yy1 = pos_y[ v[i].y1 ] + 1;
        int yy2 = pos_y[ v[i].y2 ] + 1;

        int zz1 = pos_z[ v[i].z1 ] + 1;
        int zz2 = pos_z[ v[i].z2 ] + 1;

        smen[xx1][yy1][zz1]++;
        smen[xx1][yy1][zz2]--;
        smen[xx1][yy2][zz1]--;
        smen[xx1][yy2][zz2]++;
        smen[xx2][yy1][zz1]--;
        smen[xx2][yy1][zz2]++;
        smen[xx2][yy2][zz1]++;
        smen[xx2][yy2][zz2]--;
    }

    double ans = 0.00;
    for (i = 1; i <= a; i++) {
        for (j = 1; j <= b; j++) {
            for (k = 1; k <= c; k++) {
                smen[i][j][k] = smen[i][j][k]; //! obvious..
                smen[i][j][k] += smen[i][j][k - 1];
                smen[i][j][k] += smen[i][j - 1][k];
                smen[i][j][k] -= smen[i][j - 1][k - 1];
                smen[i][j][k] += smen[i - 1][j][k];
                smen[i][j][k] -= smen[i - 1][j][k - 1];
                smen[i][j][k] -= smen[i - 1][j - 1][k];
                smen[i][j][k] += smen[i - 1][j - 1][k - 1];
            }
        }
    }

    for (i = 1; i <= a; i++) {
        for (j = 1; j <= b; j++) {
            for (k = 1; k <= c; k++) {
                if (smen[i][j][k] > 0) {
                    aux = 0;
                    dfs(i, j, k);
                    ans = max(ans, aux);
                }
            }
        }
    }

    for (i = 1; i <= n; i++)
        v[i].move();

    return ans;
}

int main()
{
    freopen("zuzu.in","r",stdin);
    freopen("zuzu.out","w",stdout);

    scanf("%d%d", &n, &t);
    for (i = 1; i <= n; i++) {
        v[i].read();
    }

    for (i = 0; i < t; i++) {
        double now = solve();

        if (now > ans + eps) {
            ans = now;
            id = i;
        }
    }

    printf("%d %d", (int)ans, id);
    cerr << ans << ' ' << id;

    return 0;
}
