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
#define inf 2000000
#define pii pair<int, int>

#define maxN 1024

struct cmp {
    bool operator()(const pii& a, const pii& b)const {
        return a.first > b.first;
    }
};

int n, m, i, k, a, b, c;
vector< pair<int, int> > list[maxN];
vector< pair<int, int> > rev[maxN];
int gr[maxN];

vector<int> ways[maxN];
queue<int> Q;

priority_queue< pii, vector<pii>, cmp> H;
int pos[maxN];
int cost[maxN];

int main()
{
    freopen("pitici.in","r",stdin);
    freopen("pitici.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        list[a].pb(mp(b, c));
        rev[b].pb(mp(a, c));
        gr[b]++;
    }

    for (i = 1; i <= n; i++) {
        if (gr[i] == 0) {
            if (i == 1)
               ways[i].pb(0);
            else
                ways[i].pb(inf);

            Q.push(i);
        }
    }

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        //! add new nodes in Queue
        for (auto to : list[node])
            if (--gr[to.first] == 0)
                Q.push(to.first);

        //! compute actual node
        while (!H.empty()) H.pop();

        for (auto from : rev[node]) {
            pos[from.first] = 0;
            cost[from.first] = from.second;
            H.push(mp( ways[from.first][0] + cost[from.first], from.first ));
        }

        int limit = k;
        while (limit > 0 && !H.empty()) {
            limit--;
            auto now = H.top(); H.pop();

            ways[node].pb(now.first);

            if(++pos[now.second] < ways[now.second].size())
                H.push(mp( ways[now.second][ pos[now.second]] + cost[now.second], now.second  ));
        }

    }

    for (i = 0; i < k; i++)
        printf("%d ", ways[n][i]);

    return 0;
}
