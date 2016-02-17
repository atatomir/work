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

int n, pos, i, best;
char s[maxN];

int cnt;

int st[maxN];
int sz[maxN];

int work[maxN];

int dp[maxN];
int how;

int read_number() {
    how++;

    int ind = 1;

    if (s[pos] == '-') {
        ind = -1;
        pos++;
    }

    int ans = 0;
    while (pos <= n && '0' <= s[pos] && s[pos] <= '9') {
        ans = ans * 10 + s[pos] - '0';
        pos++;
    }

    return ans * ind;
}

int main()
{
    freopen("expresie2.in","r",stdin);
    freopen("expresie2.out","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    st[1] = 1;
    sz[1] = 0;

    int last = 0;

    cnt = 1;
    for (pos = 1; pos <= n; ) {

        if (s[pos] == ',') {
            pos++;
            continue;
        }

        if (s[pos] == '(' || s[pos] == '[') {
            cnt++;
            st[cnt] = st[cnt - 1] + sz[cnt - 1];
            sz[cnt] = 0;

            pos++;
            continue;
        }

        if (s[pos] == ')') {
            dp[ st[cnt] ] = best = work[ st[cnt] ];
            for (i = st[cnt] + 1; i < st[cnt] + sz[cnt]; i++) {
                dp[i] = work[i];
                if (dp[i - 1] >= 0) dp[i] += dp[i - 1];

                best = max(best, dp[i]);
            }

            cnt--;
            work[ st[cnt] + sz[cnt] ] = best;
            sz[cnt]++;

            pos++;

            continue;
        }

        if (s[pos] == ']') {
            sort(work + st[cnt], work + st[cnt] + sz[cnt]);
            int wh = (sz[cnt] + 1) / 2;
            int val = work[ st[cnt] + wh - 1 ];

            cnt--;
            work[st[cnt] + sz[cnt]] = val;
            sz[cnt]++;

            pos++;

            continue;
        }

        work[ st[cnt] + sz[cnt] ] = read_number();
        sz[cnt]++;
    }

    int summi = 0;
    for (i = 1; i <= sz[1]; i++) summi += work[i];

    printf("%d\n%d", how, summi);

    return 0;
}
