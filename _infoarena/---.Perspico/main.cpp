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

#define maxN 66

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, m, i, j;
int act[maxN][maxN], target[maxN][maxN];
pair<short, short> wh[maxN * maxN];

bool us[maxN][maxN];
pair<short, short> prov[maxN][maxN];
queue< pair<short, short> > Q;
vector< pair<short, short> > way, subway;
vector<int> ans;

string s;

void print_table() {
    int i, j;

    return;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++)
            cerr << act[i][j] << ' ';
        cerr << '\n';
    }

    cerr << "\n\n";
}

void exch(int x2, int y2) {
    //! first element is 0
    static int x1, y1;

    x1 = wh[0].first;
    y1 = wh[0].second;

    swap(act[x1][y1], act[x2][y2]);
    swap(wh[ act[x1][y1] ], wh[ act[x2][y2] ]);

    print_table();

    if (x1 == x2) {
        if (y2 < y1)
            ans.pb(4);
        else
            ans.pb(2);
    } else {
        if (x2 < x1)
            ans.pb(1);
        else
            ans.pb(3);
    }

}

void bfs(int inix, int iniy, int destx, int desty) {
    static vector< pair<int, int> > auxi = {};

    for (auto e : auxi) prov[e.first][e.second] = mp(0, 0);
    while (!Q.empty()) Q.pop();
    auxi = {mp(inix, iniy)};

    Q.push(mp(inix, iniy));
    prov[inix][iniy] = mp(-1, -1);

    while (!Q.empty() && prov[destx][desty] == mp((short)0, (short)0)) {
        inix = Q.front().first;
        iniy = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int xx = inix + defX[i];
            int yy = iniy + defY[i];

            if (prov[xx][yy] == mp((short)0, (short)0) && us[xx][yy] == false) {
                prov[xx][yy] = mp(inix, iniy);
                Q.push(mp(xx, yy));
                auxi.pb(mp(xx, yy));

                if (xx == destx && yy == desty)
                    break;
            }
        }
    }

}

bool get_way(int x, int y, vector< pair<short, short> >& way ) {
    if (prov[x][y] == mp((short)0, (short)0))
        return false;

    while (prov[x][y] != mp((short)-1, (short)-1)) {
        way.pb(mp(x, y));

        int xx = prov[x][y].first;
        int yy = prov[x][y].second;

        x = xx;
        y = yy;
    }

    way.pb(mp(x, y));
    return true;
}

void move_zero(int x, int y) {
    int i;

    bfs(x, y, wh[0].first, wh[0].second);
    subway.clear();
    get_way(wh[0].first, wh[0].second, subway);

    for (i = 1; i < subway.size(); i++) {
        exch(subway[i].first, subway[i].second);
    }
}

bool move_element(int val, int x, int y) {
    int posx = wh[val].first;
    int posy = wh[val].second;
    int i;

    if (x == posx && y == posy) return true;

    bfs(x, y, posx, posy);
    way.clear();
    if (!get_way(posx, posy, way)) {
        cerr << "err";
        exit(-1);
        return false;
    }

    for (i = 1; i < way.size(); i++) {
        us[wh[val].first][wh[val].second] = true;
        move_zero(way[i].first, way[i].second);
        us[wh[val].first][wh[val].second] = false;

        exch(way[i - 1].first, way[i - 1].second);
    }

    return true;
}

bool move_element_easy(int val, int x, int y) {
    int posx = wh[val].first;
    int posy = wh[val].second;
    int i;

    if (x == posx && y == posy) return true;
    way = {mp(posx, posy)};

    while (posy < y) {
        posy++;
        way.pb(mp(posx, posy));
    }

    while (posy > y) {
        posy--;
        way.pb(mp(posx, posy));
    }

    while (posx < x) {
        posx++;
        way.pb(mp(posx, posy));
    }

    while (posx > x) {
        posx--;
        way.pb(mp(posx, posy));
    }

    for (i = 1; i < way.size(); i++) {
        us[wh[val].first][wh[val].second] = true;
        move_zero(way[i].first, way[i].second);
        us[wh[val].first][wh[val].second] = false;

        exch(way[i - 1].first, way[i - 1].second);
    }

    return true;
}


bool check() {
    if (target[n - 1][m - 1] != act[n - 1][m - 1]) return false;
    if (target[n][m - 1] != act[n][m - 1]) return false;
    if (target[n - 1][m] != act[n - 1][m]) return false;
    if (target[n][m] != act[n][m]) return false;
    return true;
}

int main()
{
    freopen("perspico.in", "r", stdin);
    freopen("perspico.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &act[i][j]);
            wh[act[i][j]] = mp(i, j);

            target[i][j] = ((i - 1) * m + j) % (n * m);
        }
    }


    for (i = 0; i <= n + 1; i++)
        us[i][0] = us[i][m + 1] = true;

    for (i = 0; i <= m + 1; i++)
        us[0][i] = us[n + 1][i] = true;

    for (i = 1; i <= n - 2; i++) {
        for (j = 1; j <= m - 2; j++) {
            move_element_easy(target[i][j], i, j);
            us[i][j] = true;
        }

        move_element(target[i][m - 1], i, m - 1);
        us[i][m - 1] = true;
        move_element(target[i][m], i + 1, m);
        us[i + 1][m] = true;

        if (wh[0] == mp((short)i, (short)m)) {
            exch(i + 1, m);
            us[i][m] = true;
            us[i + 1][m] = false;
        } else {
            move_zero(i + 1, m - 2);
            us[i][m - 1] = us[i + 1][m] = false;

            exch(i, m - 2);
            exch(i, m - 1);
            exch(i, m);
            exch(i + 1, m);
            exch(i + 1, m - 1);
            exch(i, m - 1);
            exch(i, m - 2);
            exch(i + 1, m - 2);

            us[i][m - 1] = us[i][m] = true;
        }
    }

    for (j = 1; j <= m - 2; j++) {
        if (act[n - 1][j] == target[n - 1][j] &&
            act[n][j] == 0 && act[n][j + 1] == target[n][j]) {

            exch(n, j + 1);
        } else {
            move_element(target[n - 1][j], n - 1, j);
            us[n - 1][j] = true;
            move_element(target[n][j], n, j + 1);

            if (wh[0] == mp((short)n, (short)j)) {
                exch(n, j + 1);
            } else {

                move_element(target[n][j], n, j + 2);
                us[n][j + 2] = true;
                us[n - 1][j] = true;

                move_zero(n, j);
                us[n][j + 2] = us[n - 1][j] = false;

                exch(n - 1, j);
                exch(n - 1, j + 1);
                exch(n, j + 1);
                exch(n, j + 2);
                exch(n - 1, j + 2);
                move_zero(n - 1, j);
                exch(n, j);
                exch(n, j + 1);
            }
        }

        us[n - 1][j] = us[n][j] = true;
    }

    move_zero(n, m);
    while (!check()) {
        exch(n - 1, m);
        exch(n - 1, m - 1);
        exch(n, m - 1);
        exch(n, m);
    }

    for (auto e : ans) {
        s += (char)'0' + e;
        s += ' ';
    }


    cout << s;
    cerr << s.size() << '\n';


    return 0;
}
