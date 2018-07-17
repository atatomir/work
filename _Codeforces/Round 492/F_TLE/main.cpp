#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 3018;
const ll mod = 1000000007;

int n, D, i, j, k, x, ss, dd;
vector<int> list[maxN];
int down[maxN];
ll dp[maxN][maxN], aux[2][maxN];
ll comb[maxN][maxN];
ll fact[maxN], rev[maxN];
ll here, sol, tms;

bool cmp(int a, int b) {
    return down[a] > down[b];
}

void dfs(int node) {
    int i, j, k, total;
    ll here, way;

    down[node] = 1;
    dp[node][1] = 1;

    for (auto to : list[node]) dfs(to);
    sort(list[node].begin(), list[node].end(), cmp);

    ss = 0; dd = 1;
    for (i = 1; i <= down[node]; i++) aux[ss][i] = dp[node][i];

    for (auto to : list[node]) {


        for (i = 1; i <= down[node]; i++) {
            for (j = 1; j <= down[to]; j++) {
                    way = (aux[ss][i] * dp[to][j]) % mod;

                for (k = min(i, j); k >= 0; k--) {
                    total = i + j - k;
                 
                    tms++;

                    here = (way * comb[total - 1][i - 1]) % mod;
                    aux[dd][total] = (aux[dd][total] + here * comb[i][k]) % mod;
                }    
            }
        }

        for (i = 1; i <= down[node]; i++) aux[ss][i] = 0;
        swap(ss, dd);
        down[node] += down[to];
    }

    for (i = 1; i <= down[node]; i++) {
        dp[node][i] = aux[ss][i];
        aux[ss][i] = 0;
    }
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

int main()
{
    freopen("test.in","r",stdin);

    /*freopen("test.out", "w", stdout);
    printf("1000 123123123\n");
    for (int i = 2; i <= 1000; i++) {
        printf("%d\n", (rand() % (i - 1)) + 1);
    }

    return 0;*/

    time_t t1 = clock();

    scanf("%d%d", &n, &D);
    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        
        x = (rand() % (i - 1)) + 1;

        list[x].pb(i);
    }

    for (i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }

    dfs(1);
    
    fact[0] = 1;
    rev[0] = 1;
    for (i = 1; i <= min(n, D); i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        rev[i] = (rev[i - 1] * (D - i + 1)) % mod;
    }

    for (i = 1; i <= min(n, D); i++)
        fact[i] = poww(fact[i], mod - 2);


    for (i = 1; i <= min(D, n); i++) {
        here = (dp[1][i] * fact[i]) % mod;
        here = (here * rev[i]) % mod;
        sol = (sol + here) % mod;
    }

    printf("%lld", sol);

    time_t t2 = clock();
    cerr << "\n\n Time: " << (1.00 * t2 - t1) / CLOCKS_PER_SEC << '\n';
    cerr << tms << '\n';

    return 0;
}
