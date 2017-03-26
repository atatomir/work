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

#define maxN 600011

int n, k, i, l, r, inv;
char s[maxN];
int act[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d\n%s", &n, &k, s + 1);
    for (i = 1; i <= n; i++) act[i] = s[i] - 'A';
    l = 1; r = n; inv = 0;

    while (l <= n + 2 && k > 0) {
        k--;

        if ((act[l] ^ inv) == 0) {
            act[l] ^= 1;
        } else {
            l++; r++;
            inv ^= 1;
            act[r] = inv;
        }
    }


    if (n % 2 == 1)
        act[l] ^= k & 1;

    for (i = l; i <= r; i++)
        printf("%c", 'A' + (act[i] ^ inv));



    return 0;
}
