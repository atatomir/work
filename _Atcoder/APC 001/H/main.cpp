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

#define maxN 2018
#define inf 1000000000

const int White = 0;
const int Red = 1;
const int Blue = 2;
const int Black = 3;

int n, i, m, to_do;
vector<int> list[maxN];
int dad[maxN], v[maxN], wh[maxN];
int order[maxN], assoc[maxN], color[maxN];
bool done[maxN];
pair<int, int> best;
vector<int> sol;

void print() {
    for (int i = 0; i < n; i++) cerr << v[i] << ' ';
    cerr << '\n';
}

void dfs(int node) {
    order[++m] = node;
    assoc[node] = m;

    for (auto to : list[node])
        dfs(to);
}

void execute(int node) {
    int aux;

    if (node == 0) return;
    sol.pb(node);
    aux = v[0];

    for (; node != 0; node = dad[node]) {
        swap(v[node], aux);
        wh[v[node]] = node;
    }

    swap(v[0], aux);
    wh[v[0]] = node;

    //print();
}

bool check(int node) {
    for (auto to : list[node]) {
        if (assoc[v[node]] < assoc[v[to]])
            return false;
        if (!check(to)) return false;
    }

    return true;
}

void refr(vector<int>& data) {
    int i;
    for (i = 0; i < data.size(); i++) {
        if (done[data[i]]) {
            data[i] = data.back();
            data.pop_back();
            i--;
            continue;
        }
    }
}

void dfs_red(int node) {
    refr(list[node]);

    for (auto to : list[node])
        dfs_red(to);

    if (list[node].empty())
        color[node] = Red;

    if (list[node].size() == 1)
        color[node] = color[list[node][0]];

    to_do += (color[node] == Red);
}

void put_root() {
    int node = v[0];

    while (list[node].size()) node = list[node][0];
    while (color[v[node]] == Blue && assoc[v[0]] < assoc[v[node]] && node != 0) node = dad[node];

    color[v[0]] = Blue;
    execute(node);
}

void dfs_black(int node, int lvl) {
    if (color[v[node]] == Red || color[v[node]] == White)
        best = max(best, mp(lvl, node));
    for (auto to : list[node])
        dfs_black(to, lvl + 1);
}

void throw_root() {
    best = mp(0, 0);

    dfs_black(0, 0);
    color[v[0]] = Black;
    execute(best.second);
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i < n; i++) cin >> dad[i], list[dad[i]].pb(i);
    for (i = 0; i < n; i++) cin >> v[i], wh[v[i]] = i;

    //! RND
    /*n = 10;
    srand(time(NULL));
    for (i = 0; i < n; i++) list[i].clear();
    for (i = 1; i < n; i++) {
        dad[i] = rand() % i;
        list[dad[i]].pb(i);

        cerr << dad[i] << ' ';
    }
    cerr << '\n';

    for (i = 0; i < n; i++) v[i] = i;
    random_shuffle(v, v + n);
    for (i = 0; i < n; i++) wh[v[i]] = i, cerr << v[i] << ' ';
    cerr << "\n\n\n";
    */
    //!

    dfs(0);

    while (!done[v[0]]) {
        memset(color, 0, sizeof(color));
        to_do = 0;
        dfs_red(0);

        while (to_do > 0) {
            if (color[v[0]] == Red) {
                put_root();
                to_do--;
            } else {
                throw_root();
            }
        }

        for (i = 0; i < n; i++)
            if (color[i] == Blue)
                done[i] = true;
    }


    if (sol.size() > 25000) return -1;

    cout << sol.size() << '\n';
    for (auto e : sol) cout << e << '\n';

    for (i = 0; i < n; i++)
        if (v[i] != i)
            cerr << "Err";


    return 0;
}
