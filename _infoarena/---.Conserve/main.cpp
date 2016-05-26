#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 4153
#define inf 2000000000

int mod, n, i, j;
int v[maxN], v_mod[maxN];
bitset<maxN> prov[maxN];

int ss, dd;
int dp[2][maxN];

vector<int> id;

int main()
{
    freopen("conserve.in","r",stdin);
    freopen("conserve.out","w",stdout);

    scanf("%d%d", &mod, &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]), v_mod[i] = v[i] % mod;

    prov[0].reset();
    ss = 0; dd = 1;
    for (i = 1; i < mod; i++) dp[ss][i] = -inf;
    dp[ss][0] = 0;

    for (i = 1; i <= n; i++) {
        prov[i].reset();
        memcpy(dp[dd], dp[ss], sizeof(dp[ss]));


        for (j = 0; j < mod; j++) {
            int to = j + v_mod[i];
            if (to >= mod) to -= mod;

            if (dp[dd][to] < dp[ss][j] + v[i]) {
                dp[dd][to] = dp[ss][j] + v[i];
                prov[i][to] = 1;
            }
        }

        swap(ss, dd);
    }

    i = n; j = 0;
    while (i >= 1) {
        if (prov[i][j] == 1) {
            id.pb(i);
            j = (mod + j - v_mod[i]);
            if (j >= mod) j -= mod;
        }

        i--;
    }
    reverse(id.begin(), id.end());

    printf("%d\n%d\n", dp[ss][0], id.size());
    for (int e : id) printf("%d ", e);


    return 0;
}
