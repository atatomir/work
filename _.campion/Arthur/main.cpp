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

#define maxN 211
#define Point pair<int, int>
#define inf 1000000

int defX[8] = {-2, -1, +1, +2, +2, +1, -1, -2};
int defY[8] = {+1, +2, +2, +1, -1, -2, -2, -1};

int defX2[8] = {0, 0, -1, 1, -1, 1, -1, 1};
int defY2[8] = {-1, 1, 0, 0, -1, 1, 1, -1};

int n, m, k, p, i, j;
Point Han[maxN];

int dist[maxN][maxN];
Point from[maxN][maxN];
queue<Point> Q;

int roy[maxN][maxN];
int rez[maxN][maxN];

priority_queue< pair<int, int> > H;
int dijk[maxN];
int dijk_prov[maxN];
vector<int> way;
vector<Point> ans;



int abss(int x) {
    if (x < 0) return -x;
    return x;
}

int foot_dist(int id, int id2) {
    Point act = Han[id2];
    return max(abss(act.first - Han[id].first), abss(act.second - Han[id].second));
}

void compute_from(Point act, int id) {
    int i, j;
    Point aux;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            dist[i][j] = k + 2;

    dist[act.first][act.second] = 0;
    Q.push(act);

    while (!Q.empty()) {
        act = Q.front(); Q.pop();

        for (i = 0; i < 8; i++) {
            aux = act;
            aux.first += defX[i];
            aux.second += defY[i];

            if (dist[aux.first][aux.second] > dist[act.first][act.second] + 1) {
                dist[aux.first][aux.second] = dist[act.first][act.second] + 1;
                from[aux.first][aux.second] = act;
                Q.push(aux);
            }
        }
    }

    for (i = 1; i <= p; i++) {
        act = Han[i];
        int on_foot = foot_dist(id, i);


        if (dist[act.first][act.second] > k) dist[act.first][act.second] = inf;
        roy[id][i] = dist[act.first][act.second];
        roy[id][i] = min(roy[id][i],  on_foot);

        if (i == 1 || id == 1)
            roy[id][i] = on_foot;
    }
}

void compute_from_foot(Point act, int id) {
    int i, j;
    Point aux;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            dist[i][j] = inf;

    dist[act.first][act.second] = 0;
    Q.push(act);

    while (!Q.empty()) {
        act = Q.front(); Q.pop();

        for (i = 0; i < 8; i++) {
            aux = act;
            aux.first += defX2[i];
            aux.second += defY2[i];

            if (dist[aux.first][aux.second] > dist[act.first][act.second] + 1) {
                dist[aux.first][aux.second] = dist[act.first][act.second] + 1;
                from[aux.first][aux.second] = act;
                Q.push(aux);
            }
        }
    }

    for (i = 1; i <= p; i++) {
        act = Han[i];
        roy[id][i] = dist[act.first][act.second];
    }
}

/*void roy_floyd() {
    int i, j, t;

    for (t = 1; t <= p; t++)
        for (i = 1; i <= p; i++)
            for (j = 1; j <= p; j++)
                roy[i][j] = min(roy[i][j], roy[i][t] + roy[t][j]);
}*/

int get_way() {
    int i, j;

    while (!H.empty()) H.pop();
    for (i = 1; i <= p; i++) dijk[i] = inf;
    dijk[1] = 0;
    H.push(mp(0, 1));

    while (!H.empty()) {
        pair<int, int> act = H.top(); H.pop();
        int cost = -act.first;
        int id = act.second;

        if (dijk[id] < cost) continue;
        if (id == p) break;

        for (i = 1; i <= p; i++) {
            if (dijk[i] > dijk[id] + roy[id][i]) {
                dijk[i] = dijk[id] + roy[id][i];
                dijk_prov[i] = id;
                H.push(mp(-dijk[i], i));
            }
        }
    }

    way.clear();

    i = p;
    way.pb(i);

    while (i != 1) {
        i = dijk_prov[i];
        way.pb(i);
    }

    reverse(way.begin(), way.end());

    return dijk[p];
}

void add_way(int ids, int idd) {
    if (rez[ids][idd] == foot_dist(ids, idd))
        compute_from_foot(Han[idd], idd);
    else
        compute_from(Han[idd], idd);

    int x = Han[ids].first;
    int y = Han[ids].second;

    while (mp(x, y) != Han[idd]) {
        ans.pb(mp(x, y));

        Point nxt = from[x][y];
        x = nxt.first;
        y = nxt.second;
    }
}


int main()
{
    freopen("arthur.in","r",stdin);
    freopen("arthur.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &k, &p);
    scanf("%d%d", &Han[1].first, &Han[1].second);
    scanf("%d%d", &Han[p + 2].first, &Han[p + 2].second);

    for (i = 1; i <= p; i++) scanf("%d%d", &Han[i + 1].first, &Han[i + 1].second);

    p += 2;
    for (i = 1; i <= p; i++)
        compute_from(Han[i], i);

    printf("%d\n", get_way());

    memcpy(rez, roy, sizeof(roy));

    for (i = 1; i < way.size(); i++)
        add_way(way[i - 1], way[i]);
    ans.pb(Han[p]);

    for (i = 0; i < ans.size(); i++)
        printf("%d %d\n", ans[i].first, ans[i].second);

    return 0;
}
