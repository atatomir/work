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

#define maxN 200011

int n, i;
char s[maxN];
int cnt[maxN];
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (i = 1; i <= n; i++) cnt[s[i] - 'a']++;


    ans = (1LL * n * (n - 1)) / 2LL;
    for (i = 0; i < 26; i++)
        ans -= 1LL * (1LL * cnt[i] * (cnt[i] - 1)) / 2LL;

    cout << ans + 1;


    return 0;
}
