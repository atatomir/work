#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 611

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};
const char ch[4] = {'N', 'S', 'W', 'E'};

struct Point {
    int x, y;
};

int t, ti;
int n, m, k, i, j;
pair<Point, Point> Pipe[maxN];
int mat[maxN][maxN];
bool found;

vector< vector<char> > act;
const vector<int> p = {0, 1, 2, 3};

int cnt;
int data[maxN][maxN];

void dfs(int x, int y) {
    data[x][y] = -1;
    for (int i = 0; i < 4; i++) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (data[xx][yy] == 0)
            dfs(xx, yy);
    }
}

bool bfs(int id) {
    int x = Pipe[id].first.x;
    int y = Pipe[id].first.y;
    int xx = Pipe[id].second.x;
    int yy = Pipe[id].second.y;

    for (i = 0; i <= n + 1; i++)
        for (j = 0; j <= m + 1; j++)
            data[i][j] = mat[i][j];

    data[x][y] = data[xx][yy] = 0;
    dfs(x, y);
    if (data[xx][yy] == 0) {
        //cerr << "useful";
        return false;
    }
    return true;
}

bool check(int x, int y, int id) {
    int i, j, cnt;

    for (int col = id + 1; col <= k; col++)
        if (!bfs(col))
            return false;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (abs(x - i) + abs(y - j) <= 1) continue;
            if (mat[i][j] != 0) continue;

            cnt = 0;
            for (int p = 0; p < 4; p++)
                if (mat[i + defX[p]][j + defY[p]] != -1)
                    cnt++;

            if (cnt <= 0)
                return false;
        }
    }

    return true;
}

void solve(int id, int x, int y) {
    int i, j;

    //cnt = (cnt + 1) % 5;
    //if (cnt == 0) return;

    if (act.size() > 0) {
        if (act.back().size() >= 3) {
            if (act.back().back() == act.back()[act.back().size() - 1])
                if (act.back().back() == act.back()[act.back().size() - 2])
                    return;
        }
    }

    //if (id >= 8) cerr << id << '\n';
    assert(act.size() <= k + 2);

    if (id == k + 1) {
        found = true;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if (mat[i][j] == 0)
                    found = false;

        if (!found) return;

        cerr << "solved test " << ti << '\n';

        assert(act.size() > 0);
        act.pop_back();
        cout << act.size() << '\n';
        for (auto v : act) {
            for (auto e : v) cout << e;
            cout << '\n';
        }
        act.push_back({});

        return;
    }

    if (!check(x, y, id)) return;

    assert(x >= 1 && x <= n);
    assert(y >= 1 && y <= m);


    if (mat[x][y] == 2 * id) {
        assert(act.size() > 0);
        act.pb({});
        solve(id + 1, Pipe[id + 1].first.x, Pipe[id + 1].first.y);
        assert(act.size() > 0);
        act.pop_back();
        return;
    }

    if (x != Pipe[id].first.x || y != Pipe[id].first.y)
        mat[x][y] = -1;

    vector<int> aux = p;
    random_shuffle(aux.begin(), aux.end());

    for (auto i : aux) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (mat[xx][yy] == 0 || mat[xx][yy] == 2 * id) {
            assert(act.size() > 0);

            act[act.size() - 1].pb(ch[i]);
            solve(id, xx, yy);

            assert(act[act.size() - 1].size() > 0);
            act[act.size() - 1].pop_back();
            if (found) break;
        }
    }


    if (x != Pipe[id].first.x || y != Pipe[id].first.y)
        mat[x][y] = 0;
}

int main()
{
    srand(time(NULL));

    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);

    cin >> t;
    for (ti = 1; ti <= t; ti++) {
        memset(mat, 0, sizeof(mat));
        cin >> m >> n;
        cin >> k;

        for (i = 0; i <= n + 1; i++)
            mat[i][0] = mat[i][m + 1] = -1;

        for (i = 0; i <= m + 1; i++)
            mat[0][i] = mat[n + 1][i] = -1;

        for (i = 1; i <= k; i++) {
            cin >> Pipe[i].first.y >> Pipe[i].first.x;
            cin >> Pipe[i].second.y >> Pipe[i].second.x;

            mat[Pipe[i].first.x][Pipe[i].first.y] = 2 * i - 1;
            mat[Pipe[i].second.x][Pipe[i].second.y] = 2 * i;
        }

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) cerr << mat[i][j] << ' ';
            cerr << '\n';
        }
        cerr << '\n';


        found = false;
        act = {{}};
        solve(1, Pipe[1].first.x, Pipe[1].first.y);
    }


    return 0;
}
