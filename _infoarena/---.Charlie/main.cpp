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

#define maxN 100011

int n, i, op, best;
char s[maxN];

int dp[maxN];
vector<char> S;
int pay;

int main()
{
    freopen("charlie.in","r",stdin);
    freopen("charlie.out","w",stdout);

    scanf("%d\n%s", &op, s + 1);
    n = strlen(s + 1);

    if (op == 1) {
        dp[1] = 1;
        dp[2] = 1;
        if (s[1] > s[2]) dp[2]++;

        best = dp[2];

        for (i = 3; i <= n; i++) {
            dp[i] = 1;
            if (s[i - 1] > s[i]) dp[i]++;

            if (s[i - 2] < s[i - 1] && s[i - 1] > s[i])
                dp[i] = dp[i - 1] + 1;
            if (s[i - 2] > s[i - 1] && s[i - 1] < s[i])
                dp[i] = dp[i - 1] + 1;
            best = max(best, dp[i]);
        }

        if (best % 2 == 0) best--;
        printf("%d", best);
    } else {
        S.pb(s[1]);
        S.pb(s[2]);

        for (i = 3; i <= n; i++) {
            while (S.size() >= 2) {
                char a = S[ S.size() - 2 ];
                char b = S[ S.size() - 1 ];

                if (a > b && b < s[i]) {
                    S.pop_back();
                    pay += max(a, s[i]) - 'a' + 1;
                } else {
                    break;
                }
            }

            S.pb(s[i]);
        }

        S.pb('\0');
        printf("%s\n%d\n", &S[0], pay);
    }


    return 0;
}
