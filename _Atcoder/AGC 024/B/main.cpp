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

const int maxN = 200011;

int n, i, x, ans;
int dp[maxN];

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> x;
        dp[x] = dp[x - 1] + 1;
        ans = max(ans, dp[x]);
    }

    cout << n - ans;


    return 0;
}
