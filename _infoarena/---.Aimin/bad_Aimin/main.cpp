#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define inf 1000000000

int n, i;
int v[maxN];

set< pair<int, int> > nodes, edges;
int ans, node, aux, daux;

int main()
{
    freopen("aimin.in","r",stdin);
    freopen("aimin.out","w",stdout);

    nodes.clear();
    edges.clear();
    v[n] = inf;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);

        if(i > 1)
            nodes.insert(mp(i - 1, max(v[i - 1], v[i])));

        if (i > 1) {
            edges.insert(mp(max(v[i - 1], v[i]), i - 1));
        }
    }

    while (!edges.empty()) {
        auto it = edges.begin();

        node = it->second;
        ans = it->first + 1;
        edges.erase(it);

        /*for (auto it : edges)
            cerr << it.first << ' ';
        cerr << "\n";*/

        //! update left edge
        it = nodes.lower_bound(mp(node, 0));
        if (it != nodes.begin()) {
            it--;

            aux = it->first;
            daux = max(ans, it->second);

            edges.erase(mp(it->second, it->first));
            nodes.erase(it);

            nodes.insert(mp(aux, daux));
            edges.insert(mp(daux, aux));
        }

        //! update right edge
        it = nodes.lower_bound(mp(node, 0));
        auto act_node = it;
        it++;

        if (it != nodes.end()) {

            aux = node;
            daux = max(ans, it->second);

            edges.erase(mp(it->second, it->first));
            nodes.erase(it);

            nodes.erase(act_node);
            nodes.insert(mp(aux, daux));
            edges.insert(mp(daux, aux));

        }
    }

    printf("%d", ans);


    return 0;
}
