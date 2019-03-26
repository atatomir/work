#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>


//#define testing


#ifndef testing
    #include "grader.h"
#endif

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long


#ifdef testing

const vector<int>  expected = {8, 9, 3, 2, 1, 7, 6, 5, 4, 10};

int query(vector<int> v) {
    int ans = 0;
    static int count = 0;
    count++;
    for (int i = 0; i < v.size(); i++)
        if (v[i] == expected[i])
            ans++;
    
    cerr << count << "-";
    for (auto e: v) cerr << e << ' ';
    cerr << "=> " << ans << "\n";
    return ans;
}
#endif

const int maxN = 555;

int n;
vector<int> base;
vector<int> adj[maxN];
bool used[maxN];
vector<int> cycle, solution;

int ask(vector<int>& v) {
    int ans = query(v);
    if (ans == n) exit(0);
    return ans;
}

int ask_pairs(vector< pair<int, int> >& pairs, int cnt) {
    vector<int> aux = base;
    for (int i = 0; i < pairs.size() && i <= cnt; i++)
        swap(aux[pairs[i].first], aux[pairs[i].second]);
    return ask(aux);
}

void divide(vector< pair<int, int> >& pairs, int l, int r, int total) {
    if (l == r) {
        adj[pairs[l].first].pb(pairs[l].second);
        adj[pairs[l].second].pb(pairs[l].first);
        return;
    }

    vector< pair<int, int> > aux = {};
    int mid = (l + r) >> 1;
    for (int i = l; i <= mid; i++) aux.pb(pairs[i]);
    
    int le = ask_pairs(aux, n);
    int ri = total - le;
    if (le > 0) divide(pairs, l, mid, le);
    if (ri > 0) divide(pairs, mid + 1, r, ri);
}

void check_pairs(int sum) {
    int i, target;
    vector< pair<int, int> > pairs = {};

    for (i = 0; i < n; i++) {
        int j = (sum + n - i) % n;
        if (i < j && adj[i].size() < 2 && adj[j].size() < 2)  
            pairs.pb(mp(i, j));
    }

    target = ask_pairs(pairs, n);
    if (target > 0)
        divide(pairs, 0, pairs.size() - 1, target);
    return;

    int m = pairs.size();
    int act = 0;
    target = ask_pairs(pairs, n);
    int take = -1;

    while (act < target) {
        for (int step = 1 << 10; step > 0; step >>= 1)
            if (take + step < m && ask_pairs(pairs, take + step) == act)
                take += step;

        take++;
        act = ask_pairs(pairs, take);
        adj[pairs[take].first].pb(pairs[take].second);
        adj[pairs[take].second].pb(pairs[take].first);
    }
}

void dfs(int node) {
    used[node] = true;
    cycle.pb(node);
    for (auto to: adj[node])
        if (!used[to])
            dfs(to);
}

void try_cycle() {
    vector< pair<int, int> > pairs = {};
    for (int i = 0; i + 1 < cycle.size(); i++)
        pairs.pb(mp(cycle[i], cycle[i + 1]));

    if (ask_pairs(pairs, n) == 0) 
        reverse(pairs.begin(), pairs.end());

    for (auto e : pairs)
        swap(solution[e.first], solution[e.second]);
}

void solve(int N) {
    return;
    n = N;

    for (int i = 1; i <= n; i++) base.pb(i);
    while(ask(base) > 0) 
        random_shuffle(base.begin(), base.end());

    for (int i = 0; i < n; i++)
        check_pairs(i);

    solution = base;
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        cycle.clear();
        dfs(i);
        try_cycle();
    }
    ask(solution);
}   

#ifdef testing
int main() {
    solve(10);
    return 0;
}
#endif

