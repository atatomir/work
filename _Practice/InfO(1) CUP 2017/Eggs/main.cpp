#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

//#define EVAL

#define maxN 533

int n, i, cnt, need;
vector<int> list[maxN];
bool can_be[maxN], us[maxN];
vector<int> aux;


int query(vector<int> v);

void dfs(int node, int root) {
    if (need == 0) return;
    aux.pb(node);
    us[node] = true;

    if (can_be[node]) need--;
    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);
    }
}

void make_a_query() {
    int i, pos, ans;

    memset(us, 0, sizeof(us));
    need = cnt / 2;
    aux.clear();

    dfs(1, 0);
    ans = query(aux);

    cnt = 0;
    for (i = 1; i <= n; i++) {
        if (us[i] && ans == 0) can_be[i] = false;
        if (!us[i] && ans == 1) can_be[i] = false;
        if (can_be[i]) cnt++;
    }
}

int findEgg(int N, vector < pair < int, int > > bridges) {
    n = cnt = N;
    for (i = 1; i <= n; i++) {
        list[i].clear();
        can_be[i] = true;
    }

    for (auto e : bridges) {
        list[e.first].pb(e.second);
        list[e.second].pb(e.first);
    }

    while (cnt > 1)
        make_a_query();

    for (i = 1; can_be[i] == false; i++);
    return i;
}


/// -----------------------------------------------------

#ifndef EVAL
int X, Q;
vector < int > g[512+10];

int main() {
    ifstream fin("input");
    ofstream fout("output");

    int n, nr;
    vector < pair < int, int > > v;
    vector < int > Eggs;

    fin >> n >> nr; //there are nr Easter Eggs
    for (int i = 1; i <= nr; ++i) {
        int x; fin >> x; //the i-th Easter Eggs
        Eggs.push_back(x);
    }

    //the bridges
    for (int i = 1; i < n; ++i) {
        int x, y; fin >> x >> y;
        v.push_back({x, y});
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (vector < int > :: iterator it = Eggs.begin(); it != Eggs.end(); ++it) {
        Q = 0; X = *it;
        fout << findEgg(n, v) << '\n';
        fout << Q << '\n';
        fout << '\n';

    }
}

bool used[512+10], is[512+10];

void browse(int node) {
    used[node] = 1;
    for (vector < int > :: iterator it = g[node].begin(); it != g[node].end(); ++it) {
        if (used[*it]) continue;
        if (is[*it]) browse(*it);
    }
}

bool beautiful(vector < int > v) {
    int n = (int)v.size();

    memset(used, 0, sizeof(used));
    memset(is, 0, sizeof(is));

    for (int i = 0; i < n; ++i)
        is[v[i]] = 1;

    browse(v[0]);
    for (int i = 0; i < n; ++i)
        if (!used[v[i]]) return 0;
    return 1;
}

int query(vector < int > v) {
    if (!beautiful(v)) {
        printf("The query-islands are not beautiful");
        exit(0);
    }

    bool res = 0; Q++;
    for (vector < int > :: iterator it = v.begin(); it != v.end(); ++it)
        res |= (X == *it);
    return res;
}
#endif
