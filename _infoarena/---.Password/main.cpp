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

int n, i;
char s[maxN];

int solve() {
    int best = 0;
    int pos = 1;
    int l = 0;

    while (pos < n && best + l + 1 < n) {
        if (s[best + l] == s[(pos + l) % n]) l++;
        else
        if (s[best + l] < s[(pos + l) % n]) pos += l + 1, l = 0;
        else
        if (s[best + l] > s[(pos + l) % n]) best = max(pos, best + l + 1), pos = best + 1, l = 0;
    }

    return best;
}

int main()
{
    freopen("password.in","r",stdin);
    freopen("password.out","w",stdout);

    scanf("%s", s);
    n = strlen(s);
    printf("%d", solve());

    return 0;
}
