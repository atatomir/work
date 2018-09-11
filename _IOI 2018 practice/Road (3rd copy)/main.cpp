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

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const string in_id = "input_";
const string out_id = "output_";
const string end_id = ".txt";
const vector<string> ids = {"06"};

const ll inf = 1LL << 60;

const int maxN = 1024;
int R = 1;

string in, out;
static int n, k, w, i, j, x, y;
vector<int> list[maxN];

queue<int> Q;
int dist[maxN];

ll get_cost();


struct edge {
    int x, y;
};

struct elem {
    vector<edge> data;
    ll cost;

    bool operator<(const elem& who)const {
        return cost < who.cost;
    }

    void evaluate() {
        for (auto e : data) {
            list[e.x].pb(e.y);
            list[e.y].pb(e.x);
        }
        cost = get_cost();
        for (auto e : data) {
            list[e.x].pop_back();
            list[e.y].pop_back();
        }
    }

    elem() {
        data.clear();
        cost = inf;
    }

    void random() {
        data.clear();
        for (int i = 2; i <= n; i++) data.pb({R, i});
        random_shuffle(data.begin(), data.end());
        data.resize(k);

        evaluate();
    }

    void mutation() {
        for (int cnt = k / 2; cnt > 0; cnt--) {
            int id = (rand() % k);
            data[id] = {R, (rand() % (n - 1)) + 2};
        }

        evaluate();
    }

    elem operator+(elem& who) {
        elem ans;
        ans.data.clear();

        random_shuffle(data.begin(), data.end());
        random_shuffle(who.data.begin(), who.data.end());

        for (int i = 0; i < k / 2; i++)
            ans.data.pb(data[i]);

        for (int i = k / 2; i < k; i++)
            ans.data.pb(who.data[i]);

        ans.evaluate();

        return ans;
    }
};


vector<elem> act, nxt;
elem best;

vector<int> aux;

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

ll get_cost() {
    int i, j;
    ll ans = 0;

    for (i = 1; i <= n; i++) {
        run_bfs(n, i);
        for (j = i + 1; j <= n; j++) ans += 1LL * dist[j] - 1LL;
    }

    return ans;
}

void solve(ifstream& fin, ofstream& fout) {
    int i, j, gen, a, b;

    fin >> n >> k >> w;
    for (i = 1; i <= n; i++) list[i].clear();

    for (i = 1; i < n; i++) {
        fin >> x >> y; x++; y++;
        list[x].pb(y);
        list[y].pb(x);
    }

    ifstream rez("rez.txt");
    for (i = 1; i <= k; i++) {
        rez >> a >> b;
        aux.pb(b + 1);
    }

    pair<ll, ll> best = mp(inf, -1);

    for (i = 1; i <= n; i++) {
        for (auto e : aux) {
            list[i].pb(e);
            list[e].pb(i);
        }

        auto here = mp(get_cost(), 1LL * i);
        best = min(best, here);

        if (i % 100 == 0) cerr << i << ' ';

        for (auto e : aux) {
            list[i].pop_back();
            list[e].pop_back();
        }
    }

    cerr << best.first;
    for (auto e : aux)
        fout << best.second - 1 << ' ' << e - 1 << '\n';
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
