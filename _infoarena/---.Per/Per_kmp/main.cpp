#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 6015

int n, k, i;
char s[maxN];
int pr[maxN];
int Answer;

void solve(int ind) {
    int u = 0;

    for (int i = ind + 2; i <= n; i++) {
        while (u != 0 && s[i] != s[ind + u + 1]) u = pr[u];

        if (s[i] == s[ind + u + 1]) u++;
        pr[i - ind] = u;


        if ( (i - ind) % (i - ind - u) == 0 )
            if ( ((i - ind) / (i - ind - u)) % k == 0 )
                Answer++;
    }
}

int main()
{
    freopen("per.in","r",stdin);
    freopen("per.out","w",stdout);

    scanf("%d%d\n%s", &n, &k, s + 1);

    for (i = 0; i < n; i++) solve(i);
    printf("%d", Answer);

    return 0;
}
