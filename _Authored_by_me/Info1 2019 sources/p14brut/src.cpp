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
    n = N;

    for (int i = 1; i <= n; i++) base.pb(i);
    while(ask(base) > 0) 
        random_shuffle(base.begin(), base.end());

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj[i].size() == 2 || adj[j].size() == 2) continue;
            swap(base[i], base[j]);

            int aux = ask(base);
            while (aux-- > 0) {
                adj[i].pb(j);
                adj[j].pb(i);
            
            }
            swap(base[i], base[j]);
        }
    } 

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

