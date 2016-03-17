/*
 * Dijkstra with low costs + compression
 */

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
#define ll long long

#define maxN 555
#define maxDir 9

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 2);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();
            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }

};

Buffer fin("car.in", 1 << 20);


int defX[8] = {+1, +1, +1, 0, -1, -1, -1, 0};
int defY[8] = {-1, 0, +1, +1, +1, 0, -1, -1};
int defAng[8] = {0, 1, 2, 3, 4, 5, 6, 7};

int n, m, i, j, x, y, dir;
int xs, ys, xd, yd;
bool deny[maxN][maxN];

int dist[maxN][maxN][maxDir];
vector<int> H[maxN * maxN * 4 + 10];
int h_cnt, h_pos;

int ans;

int compress(int x, int y, int dir) {
    return (x << 12) + (y << 3) + dir;
}

int decompress(int val, int &x, int &y, int &dir) {
    dir = val & 7;
    val >>= 3;

    y = val & 511;
    val >>= 9;

    x = val;
}

int pay(int ang1, int ang2) {
    ang1 -= ang2;
    if (ang1 < 0) ang1 = -ang1;
    if (ang1 > 4) ang1 = 8 - ang1;

    return ang1;
}



int main()
{
    //freopen("car.in","r",stdin);
    freopen("car.out","w",stdout);

    fin >> n >> m;
    fin >> xs >> ys >> xd >> yd;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            fin >> x;
            if (x) deny[i][j] = true;
        }
    }

    for (i = 0; i <= n + 1; i++)
        deny[i][0] = deny[i][m + 1] = true;

    for (i = 0; i <= m + 1; i++)
        deny[0][i] = deny[n + 1][i] = true;


    //! start the engine
    for (i = 0; i < 8; i++) {
        dist[xs][ys][i] = 1;

        h_cnt++;
        H[1].pb(compress(xs, ys, i));
    }

    h_pos = 1;

    while (h_cnt) {
        while (H[h_pos].empty()) h_pos++;

        int now = H[h_pos][ H[h_pos].size() - 1 ];
        H[h_pos].pop_back();
        h_cnt--;

        decompress(now, x, y, dir);

        if (dist[x][y][dir] < h_pos) continue;

        if (x == xd && y == yd) {
            ans = h_pos;
            break;
        }

        for (i = 0; i < 8; i++) {
            int new_pay = dist[x][y][dir] + pay(dir, defAng[i]);

            if (dist[x][y][i] == 0 || dist[x][y][i] > new_pay) {
                dist[x][y][i] = new_pay;

                H[new_pay].pb(compress(x, y, i));
                h_cnt++;
            }
        }

        int xx = x + defX[dir];
        int yy = y + defY[dir];

        if (deny[xx][yy] == false)
        if (dist[xx][yy][dir] == 0 || dist[xx][yy][dir] > dist[x][y][dir] ) {
            dist[xx][yy][dir] = dist[x][y][dir];

            H[ dist[x][y][dir] ].pb(compress(xx, yy, dir));
            h_cnt++;
        }
    }

    if (ans == 0)
        printf("-1");
    else
        printf("%d", ans - 1);


    return 0;
}
