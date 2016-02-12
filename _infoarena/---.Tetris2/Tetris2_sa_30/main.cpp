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

#define maxN 611
#define maxLog 7

struct Position {
    int p1, p2, p3, p4;
    int x, y;
    pair< pair<int, int>, pair<int, int> > aux;

    Position() {}
    Position(int _p1, int _p2, int _p3, int _p4, int _x, int _y) {
        p1 = _p1; p2 = _p2;
        p3 = _p3; p4 = _p4;
        x = _x; y = _y;
        aux = mp(mp(p1, p2), mp(p3, p4));
    }

    bool operator==(const Position& who) {
        return aux == who.aux;
    }

    bool operator<(const Position& who)const {
        return aux < who.aux;
    }
};

int n, m, i, j, dim;
int A[maxN][maxN];
vector< Position > aux;
int sa[maxLog][maxN][maxN];
int limit = 0;
int ans;

void compute_diff() {
    int i, j;

    aux.clear();
    for (i = 2; i <= dim; i++) {
        for (j = 2; j <= dim; j++) {
            aux.pb( Position(A[i][j] - A[i - 1][j - 1],
                             A[i][j] - A[i - 1][j],
                             A[i][j] - A[i][j - 1],
                             0,
                             i,
                             j) );
        }
    }

    sort(aux.begin(), aux.end());
    A[ aux[0].x ][ aux[0].y ] = 0;
    for (i = 1; i < aux.size(); i++) {
        if (aux[i - 1] == aux[i])
            A[ aux[i].x ][ aux[i].y ] = A[ aux[i - 1].x ][ aux[i - 1].y ];
        else
            A[ aux[i].x ][ aux[i].y ] = A[ aux[i - 1].x ][ aux[i - 1].y ] + 1;
    }
    aux.clear();
}

void compute_sa() {
    int i, j, act;

    while (limit + 1 < maxLog && (1 << (limit + 1)) <= m - 1) limit++;

    memcpy(sa[0], A, sizeof(A));
    for (act = 1; act <= limit; act++) {
        aux.clear();
        int how = (1 << act);

        for (i = 1; i + how - 1 <= dim; i++) {
            for (j = 1; j + how - 1 <= dim; j++) {
                aux.pb( Position(sa[act - 1][i][j],
                                 sa[act - 1][i + how / 2][j],
                                 sa[act - 1][i][j + how / 2],
                                 sa[act - 1][i + how / 2][j + how / 2],
                                 i,
                                 j) );
            }
        }

        sort(aux.begin(), aux.end());

        sa[act][ aux[0].x ][ aux[0].y ] = 0;
        for (i = 1; i < aux.size(); i++)
            if (aux[i - 1] == aux[i])
                sa[act][ aux[i].x ][ aux[i].y ] = sa[act][ aux[i - 1].x ][ aux[i - 1].y ];
            else
                sa[act][ aux[i].x ][ aux[i].y ] = sa[act][ aux[i - 1].x ][ aux[i - 1].y ] + 1;
    }
}

Position get_for(int x1, int y1) {
    int how = 1 << limit;
    return Position(sa[limit][x1][y1],
                    sa[limit][x1 + m - how][y1],
                    sa[limit][x1][y1 + m - how],
                    sa[limit][x1 + m - how][y1 + m - how],
                    x1,
                    y1);
}

int main()
{
    freopen("tetris2.in","r",stdin);
    freopen("tetris2.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &A[i][j]);

    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &A[i][j + n]);
            A[i][j + n] *= -1;
        }
    }

    if (m == 1) {
        printf("%d", n * n);
        cerr << n * n;
        return 0;
    }

    dim = n + m;
    compute_diff();
    compute_sa();

    m--;
    Position target = get_for(2, n + 2);
    for (i = 2; i + m - 1 <= n; i++)
        for (j = 2; j + m - 1 <= n; j++)
            if (target == get_for(i, j))
                ans++;

    printf("%d", ans);
    cerr << ans;

    return 0;
}
