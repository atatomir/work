#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long


struct flow_edge {
    int to;
    int C, F;
};

struct big_flow {
    int i, dim, S, D;
    vector<flow_edge> edges;
    vector< vector<int> > list;
    int total_flow;

    vector<bool> us;
    vector<int> prov;
    queue<int> Q;

    void init(int _dim, int _S, int _D) {
        dim = _dim; S = _S; D = _D;
        edges.clear();
        list = vector< vector<int> >(dim + 11, vector<int>(0));
        us = vector<bool>(dim + 11, false);
        prov = vector<int>(dim + 11, 0);
    }

    void add_dir_edge(int x, int y, int cap) {
        edges.pb({y, cap, 0});
        list[x].pb(edges.size() - 1);
        edges.pb({x, 0, 0});
        list[y].pb(edges.size() - 1);
    }

    void add_edge(int x, int y, int cap) {
        edges.pb({y, cap, 0});
        list[x].pb(edges.size() - 1);
        edges.pb({x, cap, 0});
        list[y].pb(edges.size() - 1);
    }

    bool bellman() {
        int i;

        for (i = 0; i <= dim + 4; i++) {
            us[i] = false;
            prov[i] = 0;
        }

        us[S] = true;
        Q.push(S);

        while (!Q.empty()) {
            int node = Q.front(); Q.pop();
            if (node == D) continue;

            for (auto e : list[node]) {
                auto aux = edges[e];

                if (us[aux.to]) continue;
                if (aux.C == aux.F) continue;
                us[aux.to] = true;
                Q.push(aux.to);
                prov[aux.to] = e;
            }
        }

        if (!us[D]) return false;

        for (auto e : list[D]) {
            auto aux = edges[e];
            if (!us[aux.to]) continue;
            if (edges[e ^ 1].C == edges[e ^ 1].F) continue;

            prov[D] = e ^ 1;
            int ff = 1000000000;


            for (int node = D; node != S && ff > 0; node = edges[ prov[node] ^ 1 ].to)
                ff = min(ff, edges[prov[node]].C - edges[prov[node]].F);

            if (ff > 0)
            for (int node = D; node != S; node = edges[ prov[node] ^ 1 ].to) {
                edges[prov[node]].F += ff;
                edges[prov[node] ^ 1].F -= ff;
            }

            total_flow += ff;
        }

        return true;
    }

    int run() {
        total_flow = 0;
        while (bellman());
        return total_flow;
    }
};

int main()
{
    freopen("test.in","r",stdin);

    


    return 0;
}
