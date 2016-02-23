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

#define maxN 1777

int n, m, i, cnt;
char A[maxN];
char B[maxN];

int ss, dd;
bool dp[2][maxN][2];

bool is_letter(char c) {
    return 'a' <= c && c <= 'z';
}

bool compute_it() {
    int i, j;

    memset(dp, 0, sizeof(dp));
    ss = 0;
    dd = 1;

    dp[ss][0][0] = dp[ss][0][1] = true;

    for (i = 1; i <= n; i++) {
        dp[dd][0][0] = dp[dd][0][1] = false;
        if (A[i] == '*') dp[dd][0][0] = dp[dd][0][1] = dp[ss][0][0];

        for (j = 1; j <= m; j++) {
            dp[dd][j][0] = false;

            if (is_letter(A[i])) {
                if (A[i] == B[j]) dp[dd][j][0] = dp[ss][j - 1][0];
            } else
            if (A[i] == '?') {
                dp[dd][j][0] = dp[ss][j - 1][0];
            } else {
                dp[dd][j][0] = (dp[ss][j][0] | dp[dd][j - 1][0]);
            }

            //! ---------------------------

            dp[dd][j][1] = false;

            if (is_letter(A[i])) {
                if (A[i] == B[j]) dp[dd][j][1] = dp[ss][j - 1][1];
                dp[dd][j][1] |= dp[ss][j][0];
            } else
            if (A[i] == '?') {
                dp[dd][j][1] = dp[ss][j - 1][1];
            } else {
                dp[dd][j][1] = (dp[ss][j][1] | dp[dd][j - 1][1]);
            }

            //cerr << dp[dd][j][0] << ' ';
        }
        //cerr << '\n';


        swap(ss, dd);
    }

    return dp[ss][m][1];
}

int main()
{
    freopen("sablon.in","r",stdin);
    freopen("sablon.out","w",stdout);

    scanf("%s\n%d\n", A + 1, &cnt);
    n = strlen(A + 1);


    for (i = 1; i <= cnt; i++) {
        memset(B, 0, sizeof(B));
        scanf("%s\n", B + 1);
        m = strlen(B + 1);

        if (compute_it())
            printf("1\n");
        else
            printf("0\n");
    }


    return 0;
}
