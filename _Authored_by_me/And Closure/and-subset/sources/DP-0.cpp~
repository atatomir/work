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

#define maxN 1000011

const int limit = 1000000;

int n, i, conf, x;
bool dp[maxN];
int answer;

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);

    scanf("%d", &n);

    dp[0] = true;
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        dp[x] = true;

        for (conf = 0; conf <= limit; conf++) {
            dp[conf & x] |= dp[conf];
        }
    }

    for (conf = 0; conf <= limit; conf++)
        if (dp[conf])
            answer++;

    printf("%d\n", answer);
    for (conf = 0; conf <= limit; conf++)
        if (dp[conf])
            printf("%d ", conf);


    return 0;
}
