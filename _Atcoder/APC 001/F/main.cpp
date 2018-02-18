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

#define maxN 100011

const int bits = 15;
const int limit = 1 << bits;

int n, i, x, y, z, ans;
vector< pair<int, int> > list[maxN];
int dp[limit];
priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > H;
int tp;

void pre() {
    int i, j, to, aux, cnt = 0;

    for (i = 0; i < limit; i++) dp[i] = bits + 1;
    dp[0] = 0;
    H.push(mp(0, 0));

    while (!H.empty()) {
        int conf = H.top().second;
        int cost = H.top().first;
        H.pop();

        if (dp[conf] != cost) continue;
        cnt++;

        for (i = 0; i < bits; i++) {
            for (j = 0; j < bits; j++) {
                if (i == j) continue;
                to = conf ^ (1 << i) ^ (1 << j);

                aux = 1 << (((i + 1) ^ (j + 1)) - 1);
                if (conf & aux) continue;
                to ^= aux;

                if (dp[to] > dp[conf] + 1) {
                    dp[to] = dp[conf] + 1;
                    H.push(mp(dp[to], to));
                }
            }

            to = conf ^ (1 << i);
            if (dp[to] > dp[conf] + 1) {
                dp[to] = dp[conf] + 1;
                H.push(mp(dp[to], to));
            }
        }
    }

    //for (i = 0; i < 256; i++) cerr << dp[i] << ' ';
    //cerr << '\n';

    cerr << limit - cnt << '\n';
}

void dfs(int node, int root, int need) {
    int act = 0;

    for (auto to : list[node])
        if (to.first != root)
            dfs(to.first, node, to.second), act ^= to.second;

    if (node != 1 && act != need)
        tp ^= ((1 << (act ^ need)) >> 1), ans++;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    pre();
    for (i = 1; i < n; i++) {
        cin >> x >> y >> z;
        x++; y++;
        list[x].pb(mp(y, z));
        list[y].pb(mp(x, z));
    }

    dfs(1, 0, 0);
    ans += dp[tp];

    if (ans % 1) cerr << "Error";
    cout << ans / 2 << '\n';


    return 0;
}
