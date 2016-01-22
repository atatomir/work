#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
 
#define maxN 100011
#define mod 666013
#define ll long long
 
int n, i, x, y;
vector<int> list[maxN];
bool us[maxN];
 
int how[maxN];
ll dp[maxN];
 
ll fact[maxN];
ll inv[maxN];
 
ll my_pow(ll a, ll b) {
    ll ans = 1;
 
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
 
    return ans;
}
 
void preproc() {
    int i;
    int lim = 100000;
 
    fact[1] = inv[1] = 1;
    fact[0] = inv[0] = 1;
    for (i = 2; i <= lim; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = my_pow(fact[i], mod - 2);
    }
}
 
ll comb(int n, int k) {
    ll ans = (fact[n] * inv[k]) % mod;
    return (ans * inv[n - k]) % mod;
}
 
void dfs(int node) {
    int i;
 
    us[node] = true;
 
    for (i = 0; i < list[node].size(); i++) {
        int to = list[node][i];
 
        if (us[to]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }
 
        dfs(to);
        how[node] += how[to];
    }
 
    int aux = how[node];
 
    dp[node] = 1;
    for (i = 0; i < list[node].size() ; i++) {
        int to = list[node][i];
 
        dp[node] = (dp[node] * dp[to]) % mod;
        dp[node] = (dp[node] * comb(aux, how[to])) % mod;
        aux -= how[to];
    }
 
 
    how[node]++;
}
 
int main()
{
    freopen("arbore4.in", "r", stdin);
    freopen("arbore4.out", "w", stdout);
 
    preproc();
    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }
 
    dfs(1);
    printf("%lld", dp[1]);
 
    return 0;
}
