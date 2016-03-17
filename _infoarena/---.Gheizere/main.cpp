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

#define maxN 256
#define maxP 1024

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

struct gheizer {
    int x, y, r;
    int wait, deny;

    void read() {
        scanf("%d%d%d%d%d", &x, &y, &r, &wait, &deny);
    }
};

int n, m, i, j, v, e, p;

int ss, dd;
int dead[maxN][maxN];
int dp[2][maxN][maxN];

gheizer G[maxP];

int pos;
vector< pair<int, int> > Events;

void add_events(gheizer now, int id) {
    int bonus = 0;

    while (bonus <= maxP) {
        Events.pb(mp(bonus + now.wait + 1, id));
        Events.pb(mp(bonus + now.wait + now.deny + 1, -id));

        bonus += now.wait + now.deny;
    }
}

void modif(int id) {
    int val = +1;

    if (id < 0) {
        val = -1;
        id = -id;
    }

    int lim_min_x = max(1, G[id].x - G[id].r);
    int lim_max_x = min(n, G[id].x + G[id].r);
    int lim_min_y = max(1, G[id].y - G[id].r);
    int lim_max_y = min(m, G[id].y + G[id].r);

    for (int i = lim_min_x; i <= lim_max_x; i++)
        for (int j = lim_min_y; j <= lim_max_y; j++)
            dead[i][j] += val;
}

int main()
{
    freopen("gheizere.in","r",stdin);
    freopen("gheizere.out","w",stdout);

    scanf("%d%d%d%d%d", &n, &m, &p, &v, &e);
    for (i = 1; i <= p; i++) {
        G[i].read();
        add_events(G[i], i);
    }

    sort(Events.begin(), Events.end());

    pos = 0;
    ss = 0; dd = 1;
    dp[ss][v][1] = true;

    for (int act_time = 2; act_time < maxP; act_time++) {
        while (pos < Events.size()) {
            if (Events[pos].first > act_time) break;

            modif(Events[pos].second);
            pos++;
        }

        memset(dp[dd], 0, sizeof(dp[dd]));

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                for (int dir = 0; dir < 4; dir++)
                    dp[dd][i][j] |= dp[ss][i + defX[dir]][j + defY[dir]];

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if (dead[i][j])
                    dp[dd][i][j] = false;

        if (dp[dd][e][m] == true) {
            printf("%d", act_time);
            return 0;
        }

        swap(ss, dd);
    }


    return 0;
}
