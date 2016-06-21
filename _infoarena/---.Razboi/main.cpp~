#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
 
using namespace std;
 
#define mp make_pair
#define pb push_back
#define ll long long
 
#define maxN 16011
 
int t, ti;
int n, i, x, y, c;
vector< pair<int, int> > list[maxN];
 
int gr[maxN], dist[maxN];
bool done[maxN];
priority_queue< pair<int, int> > H;
vector<int> aux;
 
int get_dist(int node) {
    int ans = 0;
 
    for (auto to : list[node])
        ans = max(ans, dist[to.first] + to.second);
 
    return ans;
}
 
void solve() {
    int i;
 
    if (n == 1) {
        printf("1\n");
        return;
    }
 
    for (i = 1; i <= n; i++) {
        done[i] = false;
        dist[i] = 0;
 
        if (gr[i] != 1) continue;
        done[i] = true;
        H.push(mp(-0, i));
    }
 
    aux.clear();
    while (!H.empty()) {
        int node = H.top().second;
        H.pop();
 
        aux.pb(node);
 
        for (auto to : list[node]) {
            if (done[to.first]) continue;
 
            dist[to.first] = max(dist[to.first], dist[node] + to.second);
            if (--gr[to.first] == 1) {
                done[to.first] = true;
                H.push(mp(-dist[to.first], to.first));
            }
        }
    }
 
    reverse(aux.begin(), aux.end());
    aux.resize(2);
 
    if (get_dist(aux[0]) != get_dist(aux[1])) aux.pop_back();
    sort(aux.begin(), aux.end());
 
    for (auto e : aux)
        printf("%d\n", e);
}
 
int main()
{
    freopen("razboi.in","r",stdin);
    freopen("razboi.out","w",stdout);
 
    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
 
        for (i = 1; i <= n; i++) list[i].clear(), gr[i] = 0;
        for (i = 1; i < n; i++) {
            scanf("%d%d%d", &x, &y, &c);
            list[x].pb(mp(y, c));
            list[y].pb(mp(x, c));
 
            gr[x]++; gr[y]++;
        }
 
        printf("Testul nr #%d\n", ti);
        solve();
    }
 
 
 
 
    return 0;
}
