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

int n, k, kk, i, bit, p1, p2;
vector< pair<int, int> > edge;


int main()
{
    freopen("cutit.in","r",stdin);
    freopen("cutit.out","w",stdout);

    scanf("%d", &k);

    n = 1;
    for (bit = 20; k > 0; bit--) {
        if (k >= (1 << bit) - 1) {
            k -= (1 << bit) - 1;
            for (p1 = 1; p1 <= bit + 1; p1++)
                for (p2 = p1 + 1; p2 <= bit + 1; p2++)
                    edge.pb(mp(n + p1 - 1, n + p2 - 1));
            n += bit;
            bit++;
        }
    }

    printf("%d %d\n", n, edge.size());
    for (auto e : edge)
        printf("%d %d\n", e.first, e.second);


    return 0;
}
