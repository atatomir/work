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
const vector<string> ids = {"02"};

const ll inf = 1LL << 60;

const int maxN = 1024;
int R = 1;

const int per_gen = 100;
const int get_first = 0;
const int get_rand = 0;
const int get_mutated = 50;
const int get_combined = 50;
const int get_new = 0;

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

    void read() {
        ifstream rez("rez.txt");

        data.clear();
        for (int i = 1; i <= k; i++) {
            int a, b;
            rez >> a >> b;
            data.pb({a + 1, b + 1});
        }

        evaluate();
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
        for (int cnt = k / 10; cnt > 0; cnt--) {
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

        for (int i = 0; i < k / 10; i++)
            ans.data.pb(data[i]);

        for (int i = k / 10; i < k; i++)
            ans.data.pb(who.data[i]);

        ans.evaluate();

        return ans;
    }
};


vector<elem> act, nxt;
elem best;

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

void get_next_gen() {
    int i, a, b;

    nxt.clear();
    for (i = 0; i < get_first; i++) nxt.pb(act[i]);
    for (i = 0; i < get_rand; i++) nxt.pb(act[rand() % per_gen]);
    for (i = 0; i < get_combined; i++) {
        a = rand() % per_gen;
        b = rand() % per_gen;
        nxt.pb(act[a] + act[b]);
    }
    for (i = 0; i < get_mutated; i++) {
        nxt.pb(act[rand() % per_gen]);
        nxt.back().mutation();
    }
    for (i = 0; i < get_new; i++) {
        nxt.pb(act[0]);
        nxt.back().random();
    }

    for (auto e : act) nxt.pb(e);
    sort(nxt.begin(), nxt.end());
    nxt.resize(per_gen);
}

void solve(ifstream& fin, ofstream& fout) {
    int i, j, gen;


    fin >> n >> k >> w;
    for (i = 1; i <= n; i++) list[i].clear();

    R = 1;

    for (i = 1; i < n; i++) {
        fin >> x >> y; x++; y++;
        list[x].pb(y);
        list[y].pb(x);
    }

    act.resize(per_gen);
    for (auto& e: act) e.random();

    for (i = 0; i < 7; i++)
        act[i].read();

    for (gen = 1; gen <= 10000; gen++) {
        sort(act.begin(), act.end());
        if (act[0] < best) best = act[0];

        cerr << "#" << gen << ' ' << act[0].cost << ' ' << best.cost << '\n';
        for (i = 0; i < 10; i++) cerr << act[i].cost << ' ';
        cerr << '\n';

        get_next_gen();
        act = nxt;

        if (best.cost <= 512) break;
    }

    for (auto e : best.data) fout << e.x - 1 << ' ' << e.y - 1 << '\n';

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
