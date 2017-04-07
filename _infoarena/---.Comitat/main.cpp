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

#define maxN 53

struct Point {
    int x, y;
    int id;

    bool operator<(const Point& who)const {
        int aux = x * who.y - y * who.x;
        if (aux == 0) return mp(x, y) < mp(who.x, who.y);
        return aux > 0;
    }
};

int n, i, j, k, l, L;
Point P[maxN];
short dp[maxN][maxN][maxN], from[maxN][maxN][maxN];
short dist[maxN][maxN];
short pre[maxN][maxN];

pair< pair<int, int> , pair<int, int> > best;
vector<int> ord;

int abss(int x) {
    if (x < 0) return -x;
    return x;
}

int cross(const Point& A, Point B, Point C) {
    B.x -= A.x;
    B.y -= A.y;

    C.x -= A.x;
    C.y -= A.y;

    return B.x * C.y - B.y * C.x;
}

pair< pair<int, int>, pair<int, int> > get_best(int i, int j, int k) {
    int aux;

    if (cross(P[1], P[j], P[k]) == 0) return mp(mp(i, i), mp(j, k));

    for (aux = 0; aux + 1 <= n && dp[i][j][k] + pre[k][aux + 1] <= L; aux++);
    return mp(mp(i + aux, i), mp(j, k));
}

void get(int node, int cnt) {
    if (cnt == 0) {
        ord.pb(node);
        return;
    }

    for (int fr = 2; fr < node; fr++) {
        if (cross(P[1], P[fr], P[node]) != 0) continue;
        if (pre[fr][cnt - 1] + dist[fr][node] != pre[node][cnt]) continue;
        get(fr, cnt - 1);
        ord.pb(node);
        break;
    }
}

int main()
{
    freopen("comitat.in","r",stdin);
    freopen("comitat.out","w",stdout);

    scanf("%d", &n);
    P[1] = {0, 0, 0};
    for (i = 1; i <= n; i++) scanf("%d%d", &P[i + 1].x, &P[i + 1].y), P[i + 1].id = i;
    scanf("%d", &L);

    n++;
    sort(P + 2, P + n + 1);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            dist[i][j] = abss(P[i].x - P[j].x) + abss(P[i].y - P[j].y);

    for (i = 0; i <= n; i++)
        for (j = 0; j <= n; j++)
            pre[i][j] = L + 1;

    for (i = 2; i <= n; i++) {
        pre[i][0] = dist[1][i];
        for (j = 0; j <= i; j++) {
            for (k = i + 1; k <= n && cross(P[1], P[i], P[k]) == 0; k++)
                pre[k][j + 1] = min((int)pre[k][j + 1], pre[i][j] + dist[i][k]);
        }
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            for (k = 1; k <= n; k++)
                dp[i][j][k] = L + 1;

    dp[1][1][1] = 0;
    best = mp(mp(1, 1), mp(1, 1));
    for (i = 2; i <= n; i++) best = max(best, mp(mp(2, 2), mp(1, i)));

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            for (k = 1; k <= n; k++) {
                if (dp[i][j][k] > L) continue;
                if (dp[i][j][k] + dist[k][1] <= L)
                    if (cross(P[j], P[k], P[l]) >= 0)
                        best = max(best, get_best(i, j, k));

                for (l = k + 1; l <= n; l++) {
                    if (cross(P[j], P[k], P[l]) < 0) continue;

                    if (dp[i + 1][k][l] > dp[i][j][k] + dist[k][l]) {
                        dp[i + 1][k][l] = dp[i][j][k] + dist[k][l];
                        from[i + 1][k][l] = j;
                    }
                }
            }
        }
    }

    printf("%d\n", best.first);

    if (best.first.first == 1) return 0;
    if (best.first.first == 2) {
        printf("%d", P[best.second.second].id);
        return 0;
    }

    int aux = best.first.first - best.first.second;
    i = best.first.second;
    j = best.second.first;
    k = best.second.second;

    get(k, aux);
    ord.pb(j);

    while (j != 1) {
        l = from[i][j][k];
        i--;
        k = j;
        j = l;

        if (j != 1) ord.pb(j);
    }

    for (auto e : ord) {
        printf("%d ", P[e].id);
        cerr << P[e].x << ' ' << P[e].y << '\n';
    }

    return 0;
}
