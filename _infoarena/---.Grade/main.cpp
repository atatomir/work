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

#define maxN 5011

int n, i, x;
int gr[maxN];

int main()
{
    freopen("grade.in","r",stdin);
    freopen("grade.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &gr[i]), x += gr[i];
    sort(gr + 1, gr + n + 1);

    for (x /= 2; x > 0; x--) {
        int pos = lower_bound(gr + 1, gr + n + 1, gr[n]) - gr;
        int pos2 = lower_bound(gr + 1, gr + n + 1, 1) - gr;
        if (pos == pos2) pos++;

        printf("%d %d\n", pos, pos2);
        gr[pos]--;
        gr[pos2]--;
    }




    return 0;
}
