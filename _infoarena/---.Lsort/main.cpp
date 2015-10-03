#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n, i, j, x;
short where[maxN];
short aux[maxN][maxN];
int dp[maxN][maxN];
bool prov[maxN][maxN];
vector<int> ans;

int getPosition(int val, int l, int r) {
    //! returneaza unde s-ar plasa val printre elementele din intervalele [1, l - 1] si [r + 1, n]
    return aux[val][n] - aux[val][r] + aux[val][l - 1] + 1;
}

int compute(int l, int r) {
    if (dp[l][r] != 0) return dp[l][r];

    if (l == r) {
        int pos = getPosition(where[l], l , r);
        dp[l][r] = (r - l + 1) * pos;
    } else {
        int  pos = getPosition(where[l], l + 1, r);
        int v1 = (r - l + 1) * pos + compute(l + 1, r);

        /**/ pos = getPosition(where[r], l, r - 1);
        int v2 = (r - l + 1) * pos + compute(l, r - 1);

        if(v1 < v2) {
            dp[l][r] = v1;
            prov[l][r] = false; //! left
        } else {
            dp[l][r] = v2;
            prov[l][r] = true; //! right
        }
    }

    return dp[l][r];
}

int main()
{
    freopen("lsort.in","r",stdin);
    freopen("lsort.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        where[x] = i;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (where[j] < i)
                aux[i][j] = aux[i][j - 1] + 1;
            else
                aux[i][j] = aux[i][j - 1];
        }
    }

    cerr << compute(1, 4);

    printf("%d\n", compute(1, n));

    int l = 1, r = n;
    while (l <= r) {
        if (prov[l][r] == false) {
            ans.pb(l);
            l++;
        } else {
            ans.pb(r);
            r--;
        }
    }

    for (i = ans.size() - 1; i >= 0; i--) printf("%d ", ans[i]);

    return 0;
}
