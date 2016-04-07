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

#define maxN 105
#define base 31
#define mod 666013

char aux[maxN][maxN];

struct Piece {
    int n, m, i, j;
    char data[maxN][maxN];

    void read() {
        memset(data, 0,sizeof(data));
        scanf("%d%d\n", &n, &m);
        for (i = 1; i <= n; i++)
            scanf("%s\n", data[i] + 1);
    }

    void swap_vert() {
        for (i = 1; i <= n; i++)
            for (j = 1; 2 * j <= m; j++)
                swap(data[i][j], data[i][m - j + 1]);
    }

    void swap_hori() {
        for (i = 1; 2 * i <= n; i++)
            for (j = 1; j <= m; j++)
                swap(data[i][j], data[n - i + 1][j]);
    }

    void rot90() {
        memcpy(aux, data, sizeof(data));

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                data[m - j + 1][i] = aux[i][j];

        swap(m, n);
    }

    int get_id() {
        int ans = 0;

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                if (data[i][j] == '.') continue;
                ans = (ans * base + data[i][j] - 'a' + 1) % mod;
            }
        }

        return ans;
    }

    void get_from(Piece& who, int x1, int y1, int x2, int y2) {
        memset(data, 0, sizeof(data));

        for (i = x1; i <= x2; i++)
            for (j = y1; j <= y2; j++)
                data[i - x1 + 1][j - y1 + 1] = who.data[i][j];

        n = x2 - x1 + 1;
        m = y2 - y1 + 1;
    }
};

int cnt, i, j, n, m;
Piece pattern;
Piece act;
Piece w1, w2, w3;
int id1, id2, id3;

unordered_map<int, int> how_many;
int ans;

void add_piece() {
    how_many[ act.get_id() ]++;
}

int main()
{
    freopen("bcs.in","r",stdin);
    freopen("bcs.out","w",stdout);

    scanf("%d\n", &cnt);
    pattern.read();

    for (i = 1; i <= cnt; i++) {
        act.read();

        add_piece();

        act.swap_hori();
        add_piece();
        act.swap_hori();

        act.swap_vert();
        add_piece();
        act.swap_vert();

        act.rot90();
        add_piece();

        act.rot90();
        add_piece();

        act.rot90();
        add_piece();
    }

    n = pattern.n;
    m = pattern.m;

    //! with hori
    for (i = 1; i < n; i++) {
        w1.get_from(pattern, 1, 1, i, m);
        id1 = w1.get_id();

        for (j = 1; j < m; j++) {
            w2.get_from(pattern, i + 1, 1, n, j);
            w3.get_from(pattern, i + 1, j + 1, n, m);

            id2 = w2.get_id();
            id3 = w3.get_id();

            ans += how_many[id1] * how_many[id2] * how_many[id3];
        }

        ans++;
    }


    printf("%d", (ans + 2) / 2);
    cerr << ans + 2;

    return 0;
}
