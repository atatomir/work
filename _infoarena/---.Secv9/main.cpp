#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n,i,S;
pair<int, int> Vect[maxN];
int p;

int ans = 0;
int added ;

int main()
{
    freopen("secv9.in","r",stdin);
    freopen("secv9.out","w",stdout);

    scanf("%d%d", &n, &S);
    for (i = 1; i <= n; i++) {
        scanf("%d", &Vect[i].first);
        Vect[i].first += Vect[i-1].first;
        Vect[i].second = i;
    }

    sort(Vect + 1, Vect + n + 1);

    p = 0; added = n + 1;
    for (i = 1; i <= n; i++) {
        if (Vect[i].first >= S) added = 0;
        while (Vect[p + 1].first + S <= Vect[i].first & p + 1 <= i)
            added = min(added, Vect[++p].second);

        ans = max(ans, Vect[i].second - added);
    }

    printf("%d", ans);

    return 0;
}
