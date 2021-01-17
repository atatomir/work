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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 200011;
const int maxLen = 2;

int n;
char s[maxN];
int dp[maxN][maxLen];

bool same(int i, int l1, int j, int l2) {
    //cerr << i << ' ' << l1 << ' ' << j << ' ' << l2 << '\n';
    if (l1 != l2) return false;

    for (int k = 0; k <= l1; k++)
        if (s[i - k] != s[j - k])
            return false;

    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s", s + 1);
    n = strlen(s + 1);
    s[0] = '@';

    for (int i = 1; i <= n; i++) {
        for (int len = 0; len < maxLen; len++) {
            dp[i][len] = -1;

            int j = i - len - 1;
            if (j < 0) break;

            for (int prv = 0; prv < maxLen; prv++) {
                int bg = j - prv;

                if (bg < 0) break;
                if (dp[j][prv] < 0) continue;

                if (!same(j, prv, i, len)) 
                    dp[i][len] = max(dp[i][len], dp[j][prv] + 1);
            }
        }
    }

    int answer = dp[n][0];
    for (int i = 1; i < maxLen; i++)
        answer = max(answer, dp[n][i]);
    cout << answer;


    return 0;
}
