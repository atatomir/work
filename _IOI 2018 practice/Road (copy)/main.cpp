#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <queue>
#include <ctime>
#include <cstdlib>

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

static const string in_id = "input_";
static const string out_id = "output_";
static const string end_id = ".txt";
//static const vector<string> ids = {"01", "02", "03", "04", "05", "06"};
static const vector<string> ids = {"02"};

static const int maxN = 1024;
static string in, out;

static int n, k, w, i, j, x, y, R;
vector<int> list[maxN];

queue<int> Q;
int dist[maxN];

int down[maxN];

void dfs(int node, int root) {
    down[node] = 1;

    for (auto to : list[node])
        if (to != root)
            dfs(to, node), down[node] += down[to];
}

int dfs2(int node, int root, int tar) {
    bool ok = (tar - down[node]) <= tar / 2;

    for (auto to : list[node]) {
        if (to == root) continue;
        int ans = dfs2(to, node, tar);
        if (ans) return ans;
        ok &= (down[to] <= tar / 2);
    }

    if (ok) return node;
    return 0;
}

void run_bfs(int n, int src) {
    int i, j;

    for (j = 1; j <= n; j++) dist[j] = 0;
    dist[src] = 1;
    Q.push(src);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        for (auto to : list[node])
            if (dist[to] == 0)
                dist[to] = dist[node] + 1, Q.push(to);
    }
}

pair<int, int> get_diam(int n) {
    pair<int, pair<int, int> > best = mp(0, mp(1, 1));
    int i, j;

    for (i = 1; i <= n; i++) {
        run_bfs(n, i);
        for (j = 1; j <= n; j++)
            best = max(best, mp(dist[j], mp(i, j)));
    }

    return best.second;
}

ll get_cost() {
    int i, j;
    ll ans = 0;

    for (i = 1; i <= n; i++) {
        run_bfs(n, i);
        for (j = i + 1; j <= n; j++) ans += 1LL * dist[j] - 1LL;
    }

    return ans;
}

ll get_cost_easy() {
    int i, j;
    ll ans = 0;

    for (i = 1; i <= n; i++) {
        if (n > 100 && i % 200 != 0) continue;

        run_bfs(n, i);
        for (j = i + 1; j <= n; j++) ans += 1LL * dist[j] - 1LL;
    }

    return ans;
}

pair<int, int> get_best(int n) {
    int i, j;
    pair<ll, pair<int, int> > best = mp(1LL << 60, mp(1, 1));
    vector<int> aux;


    for (i = R; i <= R; i++) {
        aux.clear();
        for (j = 1; j <= n; j++)
            if (i != j)
                aux.pb(j);

        random_shuffle(aux.begin(), aux.end());
        //aux.resize(min((int)aux.size(), 30));

        for (auto j : aux) {
            list[i].pb(j);
            list[j].pb(i);

            best = min(best, mp(get_cost_easy(), mp(i, j)));
            list[i].pop_back();
            list[j].pop_back();
        }
    }

    return best.second;
}

void solve(ifstream& fin, ofstream& fout) {
    int i, j;

    fin >> n >> k >> w;
    for (i = 1; i <= n; i++) list[i].clear();

    for (i = 1; i < n; i++) {
        fin >> x >> y; x++; y++;
        list[x].pb(y);
        list[y].pb(x);
    }

    R = (rand() % n) + 1;
    //dfs(1, 0);
    //R = dfs2(1, 0, down[1]);

    for (i = 1; i <= k; i++) {
        auto ans = get_best(n);
        list[ans.first].pb(ans.second);
        list[ans.second].pb(ans.first);
        fout << ans.first - 1 << ' ' << ans.second - 1 << '\n';

        if (i % 10 == 0) {
            cerr << in << ' ' << i << '/' << k << '\n';
            cerr << get_cost() << '\n';
        }
    }
}

int main()
{
    srand(time(NULL));

    for (auto id : ids) {
        in = in_id + id + end_id;
        out = out_id + id + end_id;

        cerr << in << ' ' << out << '\n';

        ifstream fin(in.c_str());
        ofstream fout(out.c_str());

        solve(fin, fout);

        fin.close();
        fout.close();
    }



    return 0;
}
