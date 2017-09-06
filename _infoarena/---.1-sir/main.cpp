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

#define mod 194767
#define maxN 260

const int sz = (maxN * maxN) / 2;

int n, i, j, ss, dd, pp;
int S;
int dp[2][2 * sz + 2];

void add(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main()
{
    freopen("1-sir.in","r",stdin);
    freopen("1-sir.out","w",stdout);

    scanf("%d%d", &n, &S);

    ss = 0; dd = 1;
    dp[ss][sz] = 1;

    pp = 0;
    for (i = 1; i < n; i++) {
        pp += i;
        for (j = -pp; j <= pp; j++) dp[dd][sz + j] = 0;
        pp -= i;

        for (j = -pp; j <= pp; j++) {
            if (dp[ss][sz + j] == 0) continue;

            add(dp[dd][sz + j + i], dp[ss][sz + j]);
            add(dp[dd][sz + j - i], dp[ss][sz + j]);
        }

        pp += i;
        swap(ss, dd);
    }

    if (S < -sz || S > sz) {
        printf("0");
        return 0;
    }

    printf("%d", dp[ss][S + sz]);


    return 0;
}
