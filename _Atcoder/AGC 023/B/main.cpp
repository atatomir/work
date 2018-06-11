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

const int maxN = 311;

struct cvad {
    pair<int, int> a, b;
    int id;

    cvad() {}

    cvad(int p1, int p2, int p3, int p4, int _id) {
        a = mp(p1, p2);
        b = mp(p3, p4);
        id = _id;
    }

    bool operator<(const cvad& who)const {
        return mp(a, b) < mp(who.a, who.b);
    }

    bool operator==(const cvad& who)const {
        return mp(a, b) == mp(who.a, who.b);
    }
};

int n, i, j, x, y, xx, yy, dim, full, pos;
char s[maxN][maxN];
int data[maxN][maxN][2];
vector<cvad> ord;

void give(const cvad& act, int val) {
    static int id, x, y, tp;

    id = act.id;
    if (id < 0) {
        tp = 1;
        id = -id;
    } else {
        tp = 0;
    }

    x = (id - 1) / n;
    y = (id - 1) % n;

    data[x][y][tp] = val;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d\n", &n);
    for (i = 0; i < n; i++) {
        scanf("%s\n", s[i]);
        for (j = 0; j < n; j++)
            data[i][j][0] = data[i][j][1] = s[i][j] - 'a' + 1;
    }

    ord.reserve(n * n * 2);

    for (dim = 1; dim < n; dim <<= 1) {
        full = min(n, dim * 2);
        ord.clear();
        pos = 0;

        for (x = 0; x < n; x++) {
            for (y = 0; y < n; y++) {
                xx = (x + full - dim) % n;
                yy = (y + full - dim) % n;
                pos++;

                ord.pb(cvad(data[x][y][0],
                            data[x][yy][0],
                            data[xx][y][0],
                            data[xx][yy][0],
                            pos));

                ord.pb(cvad(data[x][y][1],
                            data[xx][y][1],
                            data[x][yy][1],
                            data[xx][yy][1],
                            -pos));
            }
        }

        sort(ord.begin(), ord.end());
        pos = 1;

        give(ord[0], pos);
        for (i = 1; i < ord.size(); i++) {
            if (!(ord[i - 1] == ord[i])) pos++;
            give(ord[i], pos);
        }
    }

    int ans = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (data[i][j][0] == data[i][j][1])
                ans++;

    printf("%d", ans);


    return 0;
}
