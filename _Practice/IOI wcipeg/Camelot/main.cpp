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

#define maxN 10
#define inf 1000000

int defX[8] = {+1, +2, +2, +1, -1, -2, -2, -1};
int defY[8] = {+2, +1, -1, -2, -2, -1, +1, +2};

int n, i, j;
int dist[maxN][maxN][maxN][maxN];
queue< pair<int, int> > Q;

pair<int, int> King;
vector< pair<int, int> > K;

int dim;
char s[maxN * maxN * 2];

int fully[maxN][maxN];
int ans = inf;

int bonus;



void print_fully() {
    int i, j;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            printf("%d ", fully[i][j]);
        printf("\n");
    }

    printf("\n\n");
}

int get_dist(int x, int y) {
    x -= King.first;
    y -= King.second;

    if (x < 0) x = -x;
    if (y < 0) y = -y;

    return x + y;
}

void preprocess(int st_x, int st_y) {
    int i, j, x, y;

    dist[st_x][st_y][st_x][st_y] = 1;
    Q.push(mp(st_x, st_y));

    while (!Q.empty()) {
        auto now = Q.front(); Q.pop();

        for (i = 0; i < 8; i++) {
            x = now.first + defX[i];
            y = now.second + defY[i];

            if (x < 1 || x > n || y < 1 || y > n) continue;
            if (dist[st_x][st_y][x][y] == 0) {
                dist[st_x][st_y][x][y] = dist[st_x][st_y][now.first][now.second] + 1;
                Q.push(mp(x, y));
            }
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (dist[st_x][st_y][i][j] == 0)
                dist[st_x][st_y][i][j] = inf;
            else
                dist[st_x][st_y][i][j]--;
}

void draw(int st_x, int st_y, int v) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fully[i][j] += v * dist[st_x][st_y][i][j];
}

pair<int, int> read_pos(int pos) {
    return mp( s[pos + 1] - '0', s[pos] - 'A' + 1 );
}

void test_matrix() {
    int i, j;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            ans = min(ans, fully[i][j] + bonus);
}

void test_knight(int id) {
    int i, j;

    draw(K[id].first, K[id].second, -1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            bonus = get_dist(i, j) + dist[K[id].first][K[id].second][i][j];

            draw(i, j, +1);

            test_matrix();

            draw(i, j, -1);
        }
    }

    draw(K[id].first, K[id].second, +1);
}



int main()
{
    freopen("test.in","r",stdin);

    n = 8;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            preprocess(i, j);

    scanf("%s", s + 1);
    dim = strlen(s + 1);

    King = read_pos(1);
    for (i = 3; i <= dim; i += 2)
        K.pb(read_pos(i));


    if (K.empty()) {
        printf("0");
        return 0;
    }

    for (auto e : K)
        draw(e.first, e.second, +1);

    for (i = 0; i < K.size(); i++)
        test_knight(i);


    printf("%d", ans);

    return 0;
}
