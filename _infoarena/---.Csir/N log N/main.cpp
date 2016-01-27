#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 50011

int t, n, i;
char s[maxN];
int dp[maxN];
vector<int> gr;

bool is_good() {
    int i;

    bool good = true;
    for (i = 2; i <= n; i++)
        if (s[i] != s[1])
            good = false;
    if (good) return true;

    good = (n % 2 == 0);
    for (i = 2; i <= n; i++)
        if (s[i] == s[i - 1])
            good = false;
    if (good) return true;

    //! ---------------------------------
    s[n + 1] = s[1];
    bool two_a = false;
    bool two_b = false;

    for (i = 1; i <= n; i++) {
        two_a |= (s[i] == s[i + 1] && s[i] == 'A');
        two_b |= (s[i] == s[i + 1] && s[i] == 'B');
    }

    if (two_a && two_b) return false;
    if (two_b)
        for (i = 1; i <= n; i++)
            s[i] = (s[i] == 'A' ? 'B' : 'A');

    //! ---------------------------------
    gr.clear();

    for (i = 1; i <= n; i++) {
        if (s[i] == 'B')
            dp[i] = 0;
        else
            dp[i] = dp[i - 1] + 1;
    }

    s[n + 1] = 'B';
    for (i = 1; i <= n + 1; i++)
        if (s[i] == 'B' && s[i - 1] == 'A')
            gr.pb(dp[i - 1]);

    if (s[1] == 'A' && s[n] == 'A')
        gr[0] += gr[ gr.size() - 1 ], gr.pop_back();

    int mini = gr[0];
    int maxi = gr[0];
    for (auto u : gr) {
        mini = min(mini, u);
        maxi = max(maxi, u);
    }

    if (maxi - mini > 1) return false;

    n = 0;
    for (auto u : gr)
        s[++n] = (u == mini ? 'A' : 'B');

    return is_good();
}

int main()
{
    freopen("csir.in","r",stdin);
    freopen("csir.out","w",stdout);

    scanf("%d\n", &t);
    for (i = 1; i <= t; i++) {
        memset(s, 0, sizeof(s));
        scanf("%s\n", s + 1);
        n = strlen(s + 1);

        if (is_good())
            printf("1\n");
        else
            printf("0\n");
    }



    return 0;
}
