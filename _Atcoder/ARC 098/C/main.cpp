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

const int maxN = 300011;

int n, i, ans;
char s[maxN];
int  le[maxN], ri[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d\n%s", &n, s + 1);

    for (i = 1; i <= n; i++)
        le[i] = le[i - 1] + (s[i] == 'E' ? 0 : 1);

    for (i = n; i >= 1; i--)
        ri[i] = ri[i + 1] + (s[i] == 'W' ? 0 : 1);
    
    ans = n;
    for (i = 1; i <= n; i++)
        ans = min(ans, le[i - 1] + ri[i + 1]);

    printf("%d", ans);


    return 0;
}
