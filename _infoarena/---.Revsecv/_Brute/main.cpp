#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define ll long long

int n, i, j, k;
char s[maxN];
ll ans;

int main()
{
    freopen("revsecv.in","r",stdin);
    freopen("revsecv.ok","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            int lim = (j - i + 1) / 2;

            for (k = 1; k <= lim; k++)
                if (s[i + k - 1] == s[j - k + 1])
                    ans++;
                else
                    break;
        }
    }

    printf("%lld", ans);

    return 0;
}
