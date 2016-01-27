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

int n, i, t, test;
char A[maxN];
char B[maxN];

int dp_l[maxN];
int dp_r[maxN];
int diff_l[maxN], diff_r[maxN];

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d\n", &t);
    for (test = 1; test <= t; test++) {
        cerr << "S" << test << '\n';

        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        memset(diff_l, 0, sizeof(diff_l));
        memset(diff_r, 0, sizeof(diff_r));
        memset(dp_l, 0, sizeof(dp_l));
        memset(dp_r, 0, sizeof(dp_r));

        scanf("%d\n%s\n%s\n", &n, A + 1, B + 1);

        for (i = 1; i <= n; i++) {
            if (B[i] == B[i - 1])
                diff_l[i] = diff_l[i - 1];
            else
                diff_l[i] = diff_l[i - 1] + 1;

            if (A[i] == B[i])
                dp_l[i] = dp_l[i - 1];
            else
                dp_l[i] = diff_l[i];
        }


        for (i = n; i > 0; i--) {
            if (B[i] == B[i + 1])
                diff_r[i] = diff_r[i + 1];
            else
                diff_r[i] = diff_r[i + 1] + 1;

            if (A[i] == B[i])
                dp_r[i] = dp_r[i + 1];
            else
                dp_r[i] = diff_r[i];
        }

        int ans = 100000;
        for (i = 0; i <= n; i++)
            ans = min(ans, max(dp_l[i], dp_r[i + 1]) );

        printf("Case #%d: %d\n", test, ans);
    }


    return 0;
}
