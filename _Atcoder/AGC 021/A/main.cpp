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

int n, i, sum, ans;
char s[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    for (i = 1; i <= n; i++) {
        if (s[i] == 0) continue;
        ans = max(ans, sum + (s[i] - '0' - 1) + 9 * (n - i));
        sum += s[i] - '0';
    }

    ans = max(ans, sum);
    cout << ans;


    return 0;
}
