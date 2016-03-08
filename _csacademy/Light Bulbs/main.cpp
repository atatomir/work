#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 111

int n, i, last;
char s[maxN];
ll dp[maxN];

int main() {
    freopen("bulbs.in", "r", stdin);
    freopen("bulbs.out", "w", stdout);


    scanf("%s", s + 1);
    n = strlen(s + 1);

    reverse(s + 1, s + n + 1);
    while (n > 0 && s[n] == '0') n--;

    if (n == 0) {
        printf("0");
        return 0;
    }

    if (n == 1) {
        printf("1");
        return 0;
    }

    dp[1] = 0;
    if (s[1] == '0') dp[1] = 1;

    last = 0;
    if (s[1] == '1') last = 1;

    for (i = 2; i <= n; i++) {
        if (s[i] == '1') {
            if (last == 0)
                dp[i] = 0;
            else
                dp[i] = dp[last - 1] + 1 + (1LL << (last - 1)) - 1;
        } else {
           dp[i] = dp[i - 1] + (1LL << (i - 1));
        }

        if (s[i] == '1') last = i;
        //printf("%d - %lld\n", i, dp[i]);
    }

    printf("%lld", dp[n - 1] + 1 + (1LL << (n - 1)) - 1);
}
