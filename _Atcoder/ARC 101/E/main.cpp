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

#define debug(x) ;
//#define debug(x) cerr << #x << " = " << x << "\n";

const int maxN = 5011;
const ll mod = 1000000007;

void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

struct local_data {
    vector<ll> dp[2];

    void init() {
        dp[0] = {0, 1};
        dp[1] = {0, 0};
    }

    local_data operator*(const local_data& who) {
        local_data ans;
        int i, j, a, b, l1, l2;
        
        l1 = dp[0].size();
        l2 = who.dp[0].size();

        ans.dp[0] = ans.dp[1] = vector<ll>(l1 + l2 - 1, 0);

        for (a = 0; a < 2; a++) 
            for (i = 0; i < l1; i++) 
                for (b = 0; b < 2; b++) 
                    for (j = 0; j < l2; j++) 
                        add(ans.dp[a ^ b][i + j], (dp[a][i] * who.dp[b][j]) % mod);

        return ans;
    }
};

int n, i, x, y;
vector<int> list[maxN];
ll cnt[maxN];
local_data data[maxN];
ll sol;

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

ll poww(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    } 
    return ans;
}

void pre() {
    int i;

    cnt[0] = 1;
    for (i = 2; i <= n; i++) {
        cnt[i] = (cnt[i - 2] * (i - 1)) % mod;
    }

    for (i = 1; i <= n; i++) {
        debug(i);
        debug(cnt[i]);
    }
}

void dfs(int node, int root) {
    int len;
    data[node].init();

    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);
        data[node] = data[node] * data[to];
    }

    debug(node);
    debug(data[node].dp[0]);
    debug(data[node].dp[1]);
   
    len = data[node].dp[0].size();
    for (i = 2; i < len; i += 2) {
        add(data[node].dp[1][0], (data[node].dp[0][i] * cnt[i]) % mod);
        add(data[node].dp[0][0], (data[node].dp[1][i] * cnt[i]) % mod);
    }

    debug(node);
    debug(data[node].dp[0]);
    debug(data[node].dp[1]);
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i < n; i++) {
        cin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    pre();
    dfs(1, 0);
    sol = data[1].dp[1][0] + mod - data[1].dp[0][0];
    sol %= mod;

    cout << sol;

    return 0;
}
